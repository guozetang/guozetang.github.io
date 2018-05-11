---
title: Linux内核分析课程6_进程创建
date: 2015-03-07 13:04:27
categories: Linux
tags: Linux kernel
---
Linux内核课第六周作业。本文在云课堂中实验楼完成。  
原创作品转载请注明出处 [《Linux内核分析》MOOC课程](http://mooc.study.163.com/course/USTC-1000029000)  
# fork()系统调用
## 预备知识
这里先列出一些必要的预备知识，对linux下进程机制比较熟悉的朋友可以略过。  
1. 进程可以看做程序的一次执行过程。在linux下，每个进程有唯一的PID标识进程。PID是一个从1到32768的正整数，其中1一般是特殊进程init，其它进程从2开始依次编号。当用完32768后，从2重新开始。  
2. linux中有一个叫进程表的结构用来存储当前正在运行的进程。可以使用“ps aux”命令查看所有正在运行的进程。  
3. 进程在linux中呈树状结构，init为根节点，其它进程均有父进程，某进程的父进程就是启动这个进程的进程，这个进程叫做父进程的子进程。  
> [上述摘自:[从一道面试题谈linux下fork的运行机制\]
](http://www.cnblogs.com/leoo2sk/archive/2009/12/11/talk-about-fork-in-linux.html)	  

<!-- more -->
下面分析一个简单的例子:
```C
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	int main(int argc, char * argv[])
	{
	    int pid;
	    /* fork another process */
	    pid = fork();
	    if (pid < 0) 
	    { 
	        /* error occurred */
	        fprintf(stderr,"Fork Failed!");
	        exit(-1);
	    } 
	    else if (pid == 0) 
	    {
	        /* child process */
	        printf("This is Child Process!\n");
	    } 
	    else 
	    {  
	        /* parent process  */
	        printf("This is Parent Process!\n");
	        /* parent will wait for the child to complete*/
	        wait(NULL);
	        printf("Child Complete!\n");
	    }
	}
```
比较简单,运行结果为:
``` 
This is Child Process!
This is Parent Process!
Child Complete!
```

**在pid = fork()前,只有一个进程执行这段代码**,但在这条语句滞后,就有两个进程在执行后面的代码了,接下来的代码是:
`if(pid.....)`  
补充: fork语句的返回值,fork系统调用调用一次, 返回两次, 在这里有可能有三种返回值
- 在父进程中，**fork返回新创建子进程的进程ID；**
- 在子进程中，fork返回0；
- 如果出现错误，fork返回一个负值；  
所有在这段代码中, 如果pid = fork()执行成功, 那就有两个进程了, 一个父进程和一个子进程, 在子进程中，fork函数返回0，在父进程中，fork返回新创建子进程的进程ID。我们可以通过fork返回的值来判断当前进程是子进程还是父进程。  

fork出错可能有两种原因： 
- 当前的进程数已经达到了系统规定的上限，这时errno的值被设置为EAGAIN。系统内存不足，这时errno的值被设置为ENOMEM。
- 创建新进程成功后，系统中出现两个基本完全相同的进程，**这两个进程执行没有固定的先后顺序，哪个进程先执行要看系统的进程调度策略**。
> 参考博文: [linux中fork（）函数详解（原创！！实例讲解）](http://blog.csdn.net/jason314/article/details/5640969)
  
	 
# fork对应的系统调用过程
在 Linux 内核中,供用户创建进程的系统调用fork()函数的响应函数是 sys_fork()、sys_clone()、sys_vfork()。  
这三个函数**都是通过调用内核函数 do_fork() 来实现的**。根据调用时所使用的 clone_flags 参数不同，do_fork() 函数完成的工作也各异。下面分析do_fork(), 该函数主要作用是复制原来的进程成为另一个新的进程，它完成了整个进程的创建过程。
## do_fork()函数的几个参数:
- clone_flags：该标志位的4个字节分为两部分。最低的一个字节为子进程结束时发送给父进程的信号代码，通常为SIGCHLD；剩余的三个字节则是各种clone标志的组合。通过clone标志可以有选择的对父进程的资源进行复制。例如CLONE_VM表示共享内存描述符合所有的页表； CLONE_FS共享根目录和当前工作目录所在的表以及权限掩码。

- statck_start：子进程用户态堆栈的地址；  
- regs：指向pt_regs结构体的指针。当系统发生系统调用，即用户进程从用户态切换到内核态时，该结构体保存通用寄存器中的值，并被存放于内核态的堆栈中；  
  
- stack_size：未被使用，通常被赋值为0；  
- parent_tidptr：父进程在用户态下pid的地址，该参数在CLONE_PARENT_SETTID标志被设定时有意义； 
  
- child_tidptr：子进程在用户态下pid的地址，该参数在CLONE_CHILD_SETTID标志被设定时有意义。

## do_fork() 函数生成一个新的进程
- 建立进程控制结构并赋初值，使其成为进程映像。这个过程完成以下内容。   
> 1. 在内存中分配一个 task_struct 数据结构，以代表即将产生的新进程。
> 2. 把父进程 PCB 的内容复制到新进程的 PCB 中。
> 3. **为新进程分配一个唯一的进程标识号 PID 和 user_struct 结构。**然后检查用户具有执行一个新进程所必须具有的资源。
> 4. 重新设置 task_struct 结构中那些与父进程值不同的数据成员。
> 5. 设置进程管理信息，根据所提供的 clone_flags 参数值，决定是否对父进程 task_struct 中的指针 fs 、files 指针等所选择的部分进行拷贝，如果 clone_flags 参数指明的是共享而不是拷贝，则将其计数器 count 的值加 1 ，否则就拷贝新进程所需要的相关信息内容 PCB 。这个地方是区分 sys_fork() 还是 sys_clone() 。

- 必须为新进程的执行设置跟踪进程执行情况的相关内核数据结构。包括 任务数组、自由时间列表 tarray_freelist 以及 pidhash[] 数组。这部分完成如下内容：
> 1. 把新进程加入到进程链表中 
> 2. 把新进程加入到 pidhash 散列表中，并增加任务计数值。
> 3. 通过拷贝父进程的上、下文来初始化硬件的上下文（TSS段、LDT以及 GDT）。
  
- 启动调度程序，使子进程获得运行的机会。这部分完成以下动作：
> 1. 设置新的就绪队列状态 TASK_RUNING , 并将新进程挂到就绪队列中，并重新启动调度程序使其运行。
> 2. 向父进程返回子进程的 PID，设置子进程从 do_fork() 返回 0 值。 

```C
	int do_fork(unsigned long clone_flags,unsigned long stack_start, struct pt_regs *regs,
	                unsigned long stack_size)
	{
	        int                   retval;
	        struct  task_struct   *p;
	        struct  completion    vfork;

        retval = -EPERM ;

        if ( clone_flags & CLONE_PID )
        {
              if ( current->pid )
                      goto fork_out;
        }

        reval = -ENOMEM ;
        
        p = alloc_task_struct();    // 分配内存建立新进程的 task_struct 结构
        if ( !p )
               goto fork_out;

        *p = *current ;  //将当前进程的 task_struct 结构的内容复制给新进程的 PCB结构

        retval = -EAGAIN;

        //下面代码对父、子进程 task_struct 结构中不同值的数据成员进行赋值

        if ( atomic_read ( &p->user->processes ) >= p->rlim[RLIMIT_NPROC].rlim_cur
                && !capable( CAP_SYS_ADMIN ) && !capable( CAP_SYS_RESOURCE ))
                goto bad_fork_free;

        atomic_inc ( &p->user->__count);   //count 计数器加 1
        atomic_inc ( &p->user->processes); //进程数加 1

        if ( nr_threads >= max_threads )
               goto bad_fork_cleanup_count ;

        get_exec_domain( p->exec_domain );

        if ( p->binfmt && p->binfmt->module )
                  __MOD_INC_USE_COUNT( p->binfmt->module ); //可执行文件 binfmt 结构共享计数 + 1 
        p->did_exec = 0 ;                                   //进程未执行
        p->swappable = 0 ;                                  //进程不可换出
        p->state = TASK_UNINTERRUPTIBLE ;                   //置进程状态
        copy_flags( clone_flags,p );                        //拷贝进程标志位
        p->pid = get_pid( clone_flags );                    //为新进程分配进程标志号
        p->run_list.next = NULL ;
        p->run_list.prev = NULL ;
        p->run_list.cptr = NULL ;

        init_waitqueue_head( &p->wait_childexit );          //初始化 wait_childexit 队列

        p->vfork_done  = NULL ;

        if ( clone_flags & CLONE_VFORK ) {
               p->vfork_done = &vfork ; 
               init_completion(&vfork) ;
        }

        spin_lock_init( &p->alloc_lock );

        p->sigpending = 0 ;

        init_sigpending( &p->pending );
        p->it_real_value = p->it_virt_value = p->it_prof_value = 0 ; //初始化时间数据成员
        p->it_real_incr = p->it_virt_incr = p->it_prof_incr = 0 ;    //初始化定时器结构
        init_timer( &p->real_timer );
        p->real_timer.data = (unsigned long)p;
        p->leader = 0 ;
        p->tty_old_pgrp = 0 ;
        p->times.tms_utime = p->times.tms_stime = 0 ;                 //初始化进程的各种运行时间
        p->times.tms_cutime = p->times.tms_cstime = 0 ;
	#ifdef CONFIG_SMP                 //初始化对称处理器成员
	   {
	        int      i;
	        p->cpus_runnable = ~0UL;
	        p->processor = current->processor ;
	        for( i = 0 ; i < smp_num_cpus ; i++ )
	                 p->per_cpu_utime[ i ] = p->per_cpu_stime[ i ] = 0;
	        spin_lock_init ( &p->sigmask_lock );
	    }

	#endif
        p->lock_depth = -1 ;        // 注意：这里 -1 代表 no ,表示在上下文切换时，内核不上锁
        p->start_time = jiffies ;   // 设置进程的起始时间

        INIT_LIST_HEAD ( &p->local_pages );
        retval = -ENOMEM ;

        if ( copy_files ( clone_flags , p ))      //拷贝父进程的 files 指针，共享父进程已打开的文件
                goto bad_fork_cleanup ;

        if ( copy_fs ( clone_flags , p ))         //拷贝父进程的 fs 指针，共享父进程文件系统
                goto bad_fork_cleanup_files ;

        if ( copy_sighand ( clone_flags , p ))    //子进程共享父进程的信号处理函数指针
                goto bad_fork_cleanup_fs ;

        if ( copy_mm ( clone_flags , p ))
                goto bad_fork_cleanup_mm ;        //拷贝父进程的 mm 信息，共享存储管理信息

        retval = copy_thread( 0 , clone_flags , stack_start, stack_size , p regs );
                                                  //初始化 TSS、LDT以及GDT项

        if ( retval )
                goto bad_fork_cleanup_mm ;

        p->semundo = NULL ;                       //初始化信号量成员

        p->prent_exec_id = p-self_exec_id ;

        p->swappable = 1 ;                        //进程占用的内存页面可换出

        p->exit_signal = clone_flag & CSIGNAL ;

        p->pdeatch_signal = 0 ;                   //注意：这里是父进程消亡后发送的信号

        p->counter = (current->counter + 1) >> 1 ;//进程动态优先级，这里设置成父进程的一半,应注意的是，这里是采用位操作来实现的。

        current->counter >> =1;

        if ( !current->counter )
                current->need_resched = 1 ;        //置位重新调度标记，实际上从这个地方开始，分裂成了父子两个进程。
        
        retval = p->pid ;

        p->tpid = retval ;
        INIT_LIST_HEAD( &p->thread_group );

        write_lock_irq( &tasklist_lock );

        p->p_opptr = current->p_opptr ;
        p->p_pptr = current->p_pptr ;

        if ( !( clone_flags & (CLONE_PARENT | CLONE_THREAD ))) {
                 p->opptr = current ;
                 if ( !(p->ptrace & PT_PTRACED) )
                         p->p_pptr = current ;
        }

        if ( clone_flags & CLONE_THREAD ){
                 p->tpid = current->tpid ;
                 list_add ( &p->thread_group,&current->thread_group );
        }

        SET_LINKS(p);

        hash_pid(p);
        nr_threads++;

        write_unlock_irq( &tasklist_lock );
        if ( p->ptrace & PT_PTRACED )
                  send_sig( SIGSTOP , p ,1 );
        wake_up_process(p);        //把新进程加入运行队列，并启动调度程序重新调度，使新进程获得运行机会
        ++total_forks ; 
        if ( clone_flags & CLONE_VFRK )
                  wait_for_completion(&vfork);

        //以下是出错处理部分
        fork_out:
                  return retval;
        bad_fork_cleanup_mm:
                  exit_mm(p);
        bad_fork_cleanup_sighand:
                  exit_sighand(p);
        bad_fork_cleanup_fs:
                  exit_fs(p);
        bad_fork_cleanup_files:
                  exit_files(p);

        bad_fork_cleanup:
                  put_exec_domain( p->exec_domain );

                  if ( p->binfmt && p->binfmt->module )
                                __MOD_DEC_USE_COUNT( p->binfmt->module );
        bad_fork_cleanup_count:
                  atomic_dec( &p->user->processes );
                  free_uid ( p->user );
        bad_fork_free:
                  free_task_struct(p);
                  goto fork_out;
	}
```

# 三.实验
实验是在实验楼完成的:
   ![这里写图片描述](http://img.blog.csdn.net/20150412211133964)


  总结:
  1.新进程的执行起点为: ret_form_fork
  当他从ret_from_fork退出时，会从堆栈中弹出原来保存的eip，而ip指向kernel_thread_helper, 

  至此kernel_thread_helper被调用，他就能够运行我们的指定的函数了do_exit(). 
  do_fork的执行流程可如下图表示:
![这里写图片描述](http://img.blog.csdn.net/20150412205951386)
图摘自:[Linux进程切换](http://www.ahlinux.com/start/base/6893.html)