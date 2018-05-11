---
title: Linux内核分析课程5_System call中断处理过程
date: 2015-03-01 13:04:27
categories: Linux内核分析课程
tags: Linux
---
﻿
　　Linux内核课第四周作业。本文在云课堂中实验楼完成。
　　唐国泽 原创作品转载请注明出处 《Linux内核分析》MOOC课程http://mooc.study.163.com/course/USTC-1000029000
****
　　主要内容：
　　1.调试sys_exit()
　　2.系统调用源代码分析
　　3.系统调用小结

#一.加入自定义的系统调用CallExit.
　　修改menu/test.c文件，加入自己定义的系统调用函数。
```c#
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include "menu.h"
	#include<sys/types.h>
	#include<unistd.h>
	#define FONTSIZE 10
	......
	......
	int CallExit(int argc,char *argvs)
	{
	    pid_t pc,pr;
	    int t;
	    pc =fork();
	    if(pc < 0)
	        printf("Fork error!\n");
	    else if(pc == 0){
	        printf("This is child process with pid of %d\n",getpid());
	        sleep(5);
	    }
	    else{
	        pr=wait(NULL);
	        printf("I catched a child process with pid of %d\n",pr);
	    }
	    exit(0);
	}
	int CallExit_asm(int argc,char *argvs)
	{
	    pid_t pc,pr;
	    int t;
	    pc =fork();
	    if(pc < 0)
	        printf("Fork error!\n");
	    else if(pc == 0){
	        printf("This is child process with pid of %d\n",getpid());
	        sleep(5);
	    }
	    else{
	        pr=wait(NULL);
	        printf("I catched a child process with pid of %d\n",pr);
	    }
	
	    asm volatile(
	            "mov $0x1,%%eax\n\t"
	            "mov $0x0,%%ebx\n\t"
	            "int $0x80\n\t"
	            "mov %%eax,%0\n\t"
	            :"=m" (t)
	            );
	}

	int main()
	{
	    PrintMenuOS();
	    SetPrompt("MenuOS>>");
	    MenuConfig("version","MenuOS V1.0(Based on Linux 3.18.6)",NULL);
	    MenuConfig("quit","Quit from MenuOS",Quit);
	    MenuConfig("time","Show System Time",Time);
	    MenuConfig("time-asm","Show System Time(asm)",TimeAsm);
	    **MenuConfig("CallExit","Exit Systemcall",CallExit);**
	    **MenuConfig("CallExit_asm","Exit_asm Systemcall",CallExit_asm);**
	    ExecuteMenu();
	}
```
　　即在main函数中，加入相应的系统调用定义，讲CallExit和CallExit_asm加入到其中去，在QEMU中启动系统之后可以输入help看到，我们的命令中多了两条命令。

　　![系统启动时，命令中有了多的系统调用函数](http://img.blog.csdn.net/20150405172545647)　
　可惜在进行系统调用测试的时候出现了问题，导致系统崩溃了，暂时还没有测试出来代码中是什么地方出现了问题，会继续调试找出问题的地方。
　　![调试的时候出现问题的图片](http://img.blog.csdn.net/20150405181638295)

　　关于老师视频中提到的不能调试sys_time的一些分析：
　　[Linux Kernel代码艺术——系统调用宏定义](http://www.cnblogs.com/hazir/p/syscall_marco_define.html)
　　可以参考这一篇文章中的内容，在2.6.28之前的内核代码中，系统调用的时候是直接调用处理函数的，但出现了漏洞CVE-2009-0029漏洞之后，就是通过宏定义的方式来处理系统调用函数了。
　　
#二.系统调用源代码分析
　　
```asm
	# system call handler stub
	ENTRY(system_call)				//所有系统调用函数的入口处
		RING0_INT_FRAME			# can't unwind into user space anyway
		ASM_CLAC
		pushl_cfi %eax				# 保存系统调用号
		SAVE_ALL					# 保护现场
		GET_THREAD_INFO(%ebp)　#保存当前信息到ebp中
		# system call tracing in operation / emulation
		testl $_TIF_WORK_SYSCALL_ENTRY,TI_flags(%ebp)
		jnz syscall_trace_entry
		##判断是否是trace相关的调用
		##判断系统调用号是否超出了最大值255
		cmpl $(NR_syscalls), %eax
		jae syscall_badsys
	syscall_call:
		call *sys_call_table(,%eax,4)		//由系统调用表中的对应系统调用号找服务函数
	syscall_after_call:
		movl %eax,PT_EAX(%esp)		# store the return value
	#系统调用返回
	syscall_exit:　　　
		LOCKDEP_SYS_EXIT
		DISABLE_INTERRUPTS(CLBR_ANY)	# make sure we don't miss an interrupt
						# setting need_resched or sigpending
						# between sampling and the iret
		TRACE_IRQS_OFF
		movl TI_flags(%ebp), %ecx
		
		##退出系统调用之前，检查是否需要处理信号
		testl $_TIF_ALLWORK_MASK, %ecx	# current->work
		jne syscall_exit_work
	#恢复处理器工作
	restore_all:
		TRACE_IRQS_IRET
	restore_all_notrace:
	#ifdef CONFIG_X86_ESPFIX32
		movl PT_EFLAGS(%esp), %eax	# mix EFLAGS, SS and CS
		# Warning: PT_OLDSS(%esp) contains the wrong/random values if we
		# are returning to the kernel.
		# See comments in process.c:copy_thread() for details.
		movb PT_OLDSS(%esp), %ah
		movb PT_CS(%esp), %al
		andl $(X86_EFLAGS_VM | (SEGMENT_TI_MASK << 8) | SEGMENT_RPL_MASK), %eax
		cmpl $((SEGMENT_LDT << 8) | USER_RPL), %eax
		CFI_REMEMBER_STATE
		je ldt_ss			# returning to user-space with LDT SS
	#endif
	restore_nocheck:
		RESTORE_REGS 4			# skip orig_eax/error_code
	irq_return:
		INTERRUPT_RETURN　　//中断系统调用的处理过程，结束点iret
	.section .fixup,"ax"
	ENTRY(iret_exc)
		pushl $0			# no error code
		pushl $do_iret_error
		jmp error_code
	.previous
		_ASM_EXTABLE(irq_return,iret_exc)
	
	#ifdef CONFIG_X86_ESPFIX32
		CFI_RESTORE_STATE
	ldt_ss:
	#ifdef CONFIG_PARAVIRT
		cmpl $0, pv_info+PARAVIRT_enabled
		jne restore_nocheck
	#endif
	#define GDT_ESPFIX_SS PER_CPU_VAR(gdt_page) + (GDT_ENTRY_ESPFIX_SS * 8)
		mov %esp, %edx			/* load kernel esp */
		mov PT_OLDESP(%esp), %eax	/* load userspace esp */
		mov %dx, %ax			/* eax: new kernel esp */
		sub %eax, %edx			/* offset (low word is 0) */
		shr $16, %edx
		mov %dl, GDT_ESPFIX_SS + 4 /* bits 16..23 */
		mov %dh, GDT_ESPFIX_SS + 7 /* bits 24..31 */
		pushl_cfi $__ESPFIX_SS
		pushl_cfi %eax			/* new kernel esp */
		/* Disable interrupts, but do not irqtrace this section: we
		 * will soon execute iret and the tracer was already set to
		 * the irqstate after the iret */
		DISABLE_INTERRUPTS(CLBR_EAX)
		lss (%esp), %esp		/* switch to espfix segment */
		CFI_ADJUST_CFA_OFFSET -8
		jmp restore_nocheck
	#endif
		CFI_ENDPROC
	ENDPROC(system_call)
	
	# perform work that needs to be done immediately before resumption
		ALIGN
		RING0_PTREGS_FRAME		# can't unwind into user space anyway
	
	work_pending:
		testb $_TIF_NEED_RESCHED, %cl  #检查是否需要重新调度
		jz work_notifysig　　#不需要重新调度，调到work_notifysig
	
	work_resched:		　　　#重新调度
		call schedule		#进程调度
		LOCKDEP_SYS_EXIT
		DISABLE_INTERRUPTS(CLBR_ANY)	# make sure we don't miss an interrupt
						# setting need_resched or sigpending
						# between sampling and the iret
		TRACE_IRQS_OFF
		movl TI_flags(%ebp), %ecx
		andl $_TIF_WORK_MASK, %ecx	# is there any work to be done other
						# than syscall tracing?
		jz restore_all　　//没有其余事情，则恢复现场
		testb $_TIF_NEED_RESCHED, %cl
		jnz work_resched
	
	work_notifysig:				# deal with pending signals and
						# notify-resume requests
	#ifdef CONFIG_VM86
		testl $X86_EFLAGS_VM, PT_EFLAGS(%esp)
		movl %esp, %eax
		jne work_notifysig_v86		# returning to kernel-space or
						# vm86-space
	1:
	#else
		movl %esp, %eax
	#endif
		TRACE_IRQS_ON
		ENABLE_INTERRUPTS(CLBR_NONE)
		movb PT_CS(%esp), %bl
		andb $SEGMENT_RPL_MASK, %bl
		cmpb $USER_RPL, %bl
		jb resume_kernel
		xorl %edx, %edx
		call do_notify_resume　　#进行信号处理
		jmp resume_userspace
	
	#ifdef CONFIG_VM86
		ALIGN
	work_notifysig_v86:
		pushl_cfi %ecx			# save ti_flags for do_notify_resume
		call save_v86_state		# %eax contains pt_regs pointer
		popl_cfi %ecx
		movl %eax, %esp
		jmp 1b
	#endif
	END(work_pending)
	
		# perform syscall exit tracing
		ALIGN
	syscall_trace_entry:
		movl $-ENOSYS,PT_EAX(%esp)
		movl %esp, %eax
		call syscall_trace_enter
		/* What it returned is what we'll actually use.  */
		cmpl $(NR_syscalls), %eax
		jnae syscall_call
		jmp syscall_exit
	END(syscall_trace_entry)
	
		# perform syscall exit tracing
		ALIGN
	syscall_exit_work:		#完成其他工作
		testl $_TIF_WORK_SYSCALL_EXIT, %ecx
	 #检查是否系统调用跟踪,审计,单步执行,不需要则跳到work_pending(进行调度,信号处理)  
		jz work_pending
		TRACE_IRQS_ON
		ENABLE_INTERRUPTS(CLBR_ANY)	# could let syscall_trace_leave() call
						# schedule() instead
		movl %esp, %eax
		call syscall_trace_leave
		jmp resume_userspace
	END(syscall_exit_work)
		CFI_ENDPROC
	
		RING0_INT_FRAME			# can't unwind into user space anyway
	syscall_fault:
		ASM_CLAC
		GET_THREAD_INFO(%ebp)
		movl $-EFAULT,PT_EAX(%esp)
		jmp resume_userspace
	END(syscall_fault)
	
	syscall_badsys:
		movl $-ENOSYS,%eax
		jmp syscall_after_call
	END(syscall_badsys)
	
	sysenter_badsys:
		movl $-ENOSYS,%eax
		jmp sysenter_after_call
	END(sysenter_badsys)
		CFI_ENDPROC
	
	.macro FIXUP_ESPFIX_STACK
	/*
	 * Switch back for ESPFIX stack to the normal zerobased stack
	 *
	 * We can't call C functions using the ESPFIX stack. This code reads
	 * the high word of the segment base from the GDT and swiches to the
	 * normal stack and adjusts ESP with the matching offset.
	 */
	#ifdef CONFIG_X86_ESPFIX32
		/* fixup the stack */
		mov GDT_ESPFIX_SS + 4, %al /* bits 16..23 */
		mov GDT_ESPFIX_SS + 7, %ah /* bits 24..31 */
		shl $16, %eax
		addl %esp, %eax			/* the adjusted stack pointer */
		pushl_cfi $__KERNEL_DS
		pushl_cfi %eax
		lss (%esp), %esp		/* switch to the normal stack segment */
		CFI_ADJUST_CFA_OFFSET -8
	#endif
	.endm
	.macro UNWIND_ESPFIX_STACK
```

   SAVE_ALL保存现场函数的宏定义如下图所示：
![这里写图片描述](http://img.blog.csdn.net/20150405185021135)
	  

#三.系统调用小结
　　系统调用流程小结：

　　1.执行用户程序(如:fork,exit) 
　　2.根据glibc中的函数实现，取得系统调用号并执行int $0x80产生中断。
　　3.进行地址空间的转换和堆栈的切换，执行SAVE_ALL。（进行内核模式）
　　4.进行中断处理，根据系统调用表调用内核函数。
　　5.执行内核函数。
　　6.执行RESTORE_ALL并返回用户模式
　　类似中断处理过程，可以知道，在中断当中这个整体的框架是不变化的的，只是相应的系统调用号和处理函数之间的转化变化成了中断号和中断处理函数之间的转化。
```flow
st=>start: int0x80->ENTRY(system_call)
e=>end: Ende|future:>http://www.google.com
op1=>operation: SAVE_ALL(保存现场)|past
op2=>operation: call *sys_call_table
op3=>operation: 系统调用处理程序将返回值存入eax
cond1=>condition: 是否有其他信号或调度
io=>inputoutput: 处理其他信号|future
cond2=>condition: 是否有调度信号
op4=>operation: call_schedule（进程调度）
op5=>operation: RESTORE_ALL(恢复现场)
op6=>operation: INTRRRUPT_RET(iret)
　　返回用户进程
op7=>operation: 保存中断，调用上下文，调度
op8=>operation: 未来再调度回来
cond3=>condition: 是否有退出信号


st->op1->op2->op3->cond1
cond1(no,lift)->op5->op6
cond1(yes,right)->io->cond3(no)->cond2(yes)->op4->op7->op8
op8(right)->op5
cond2(no,right)->op5

```

