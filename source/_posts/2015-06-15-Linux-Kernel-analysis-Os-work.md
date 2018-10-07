---
title: Linux内核分析课程2_操作系统是如何工作的
date: 2015-03-01 13:04:27
updated: 2015-04-01 13:04:27
categories: Linux
tags: Linux kernel
---

Linux内核课第二周作业。本文在云课堂中实验楼完成。  
[唐国泽](http://guozet.me/about/) 原创作品转载请注明出处.  
[《Linux内核分析》MOOC课程](http://mooc.study.163.com/course/USTC-1000029000)

<!--more-->

# 计算机是如何工作的（小结）

## 概念

计算机的工作，一言以蔽之：执行程序的过程；也就是存储程序和[程序控制](http://baike.baidu.com/view/922446.htm)的过程。

- 存储程序计算机工作模型，计算机系统最最基础性的逻辑结构
- 函数调用堆栈，高级语言得以运行的基础
- 中断，多道程序操作系统的基点
    

## 以例分析

[一个简单的中断的例子](https://github.com/mengning/mykernel "mykernel")(点击进入)

### 简要分析mymain.c与myinterrupt.c

```c
void __init my_start_kernel(void)  // mymain.c中主要内容
{
  int i = 0;
  while (1) {
    i++;
    if (i % 100000 == 0)  //每循环十万次打印一次my_start_kernel here
      printk(KERN_NOTICE "my_start_kernel here %d \n", i);
  }
}

void my_timer_handler(void)  //每次时钟中断调用一次 myinterrupt.c中主要内容
{
  printk(KERN_NOTICE
         "\n>>>>>>>>>>>>>>>>>my_timer_handler here<<<<<<<<<<<<<<<<<<\n\n");
}
```

可见，这只是一个很简单的时钟中断演示实验，执行结果如下所示：

![](/images/in-post/2015-06-15-Linux-Kernel-analysis-Os-work/2018-09-19-01-12-35.png)

可以清楚的看到，时钟每记数到十万的时候，打印一个my_start_kernel here，时钟中断的时候执行my_time_hander here.

### 在第一个的基础上进行时间片轮转多道程序的小os.

**主要对mypcb.h, mymain.c 和myinterrupt.c这三个文件进行分析**

1. mypcb.h

```c
/ * linux/mykernel/**mypcb.h**
* Kernel internal PCB types
* Copyright (C) 2013 Mengning
*/
#define MAX_TASK_NUM 4
#define KERNEL_STACK_SIZE 1024*8
/* CPU-specific state of this task */
struct Thread {//给任务定义一个eip和esp
    unsigned longip;
    unsigned longsp;
};

typedef struct PCB{
    int pid;//任务编号
    volatile long state;/* -1 unrunnable, 0 runnable, >0 stopped */
    char stack[KERNEL_STACK_SIZE]; //定义栈空间
    /* CPU-specific state of this task */
    struct Thread thread; //定义进程的结构体thread, 其中有eip和esp
    unsigned longtask_entry;//任务的函数起始处, 也就是任务第一次执行的起始位置
    struct PCB *next;//一个任务链表, 指向下一个任务
}tPCB;

void my_schedule(void);//任务调动函数**
```

2. mymain.c

```c
/* linux/mykernel/mymain.c
* Kernel internal my_start_kernel
* Copyright (C) 2013 Mengning
*/
#include <linux/types.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/tty.h>
#include <linux/vmalloc.h>
#include "mypcb.h" //引入其中两个结构体表示**

tPCB task[MAX_TASK_NUM];//定义两个数组
tPCB * my_current_task = NULL;
volatile int my_need_sched = 0;//定义是否调度, 1则调度, 0则不调度
void my_process(void);
void __init my_start_kernel(void) **//起始函数位置**
{
    int pid = 0;
    int i;
    /* Initialize process 0*/
    task[pid].pid = pid;
    task[pid].state = 0;/* -1 unrunnable, 0 runnable, >0 stopped */
    task[pid].task_entry = task[pid].thread.ip = (unsigned long)my_process;
    task[pid].thread.sp = (unsigned long)&task[pid].stack[KERNEL_STACK_SIZE-1]; //0号进程栈在最开始的位置**
    task[pid].next = &task[pid];//下一个任务也是自己，在这里，其他任务还没有创建

    /*fork more process *///创建多个任务
    for(i=1;i<MAX_TASK_NUM;i++)
    {
        memcpy(&task[i],&task[0],sizeof(tPCB));//复制0号进程的结构形式
        task[i].pid = i;
        task[i].state = -1;//初始的任务(除0号进程外)都设置成未运行
        task[i].thread.sp = (unsigned long)&task[i].stack[KERNEL_STACK_SIZE-1];
        task[i].next = task[i-1].next;//新fork的进程加到进程链表的尾部, 该新建任务的next指向上一个任务的next,也就是自己（最后一个）
        task[i-1].next = &task[i]; //配置上一个任务的next指向这时候新创建的任务
    }
    /* start process 0 by task[0] */
    pid = 0;
    my_current_task = &task[pid];//先让0号进程先执行
    asm volatile(
        "movl %1,%%esp\n\t"  /* set task[pid].thread.sp to esp */
        "pushl %1\n\t"  /* push ebp ,当前esp=ebp*/
        "pushl %0\n\t"  /* push task[pid].thread.ip */
        "ret\n\t"  /* pop task[pid].thread.ip to eip */
        "popl %%ebp\n\t"
        :
        : "c" (task[pid].thread.ip),"d" (task[pid].thread.sp)
    );
}

void my_process(void)
{
    int i = 0;
    while(1)
{
    i++;
    if(i%10000000 == 0)
{
    printk(KERN_NOTICE "this is process %d -\n",my_current_task->pid);
    if(my_need_sched == 1)//判断是否调度；该值可有itnerrupt.c中的函数来配置
    {
        my_need_sched = 0;
        my_schedule();  //主动调动的机制
    }
        printk(KERN_NOTICE "this is process %d +\n",my_current_task->pid);
    }
}
}
```

3. myinterrupt.c

```c
/* linux/mykernel/myinterrupt.c
* Kernel internal my_timer_handler
* Copyright (C) 2013 Mengning

*/

#include <linux/types.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/tty.h>
#include <linux/vmalloc.h>
#include "mypcb.h"
extern tPCB task[MAX_TASK_NUM];
extern tPCB * my_current_task;
extern volatile int my_need_sched;
volatile int time_count = 0;

/*
* Called by timer interrupt.
* it runs in the name of current running process,
* so it use kernel stack of current running process
*/

void my_timer_handler(void)
{
#if 1
    if(time_count%1000 == 0 && my_need_sched != 1)//时钟中断1000次的时候，调度一次, 配置调度值为1
    {
        printk(KERN_NOTICE ">>>my_timer_handler here<<<\n");
        my_need_sched = 1;
    }
    time_count ++ ;
#endif
    return;
}

void my_schedule(void) //调度函数, 核心函数
{
    tPCB * next;//定义两个指针
    tPCB * prev;

    if(my_current_task == NULL  //当前进程和下一进程为空, 即没有任务, 返回
    || my_current_task->next == NULL)
    {
        return;
    }
    printk(KERN_NOTICE ">>>my_schedule<<<\n");
    /* 在调度函数中, next指向的是下一个将要被调度的任务, prev指向的是当前正在运行的任务*/
    /* schedule */
    next = my_current_task->next;//把当前进程的下一个进程赋值给next，当前进程赋值给prev
    prev = my_current_task;

    if(next->state == 0)/* -1 unrunnable, 0 runnable, >0 stopped */ //如果下一个任务不是第一次被调度, 则执行
    {
        /* switch to next process——这个时候下一个进程有进程上下文 */
        asm volatile(
        "pushl %%ebp\n\t"  /* save 当前进程 ebp */
        "movl %%esp,%0\n\t"  /* save 当前 esp 赋值到prev.thread.sp */
        "movl %2,%%esp\n\t" /* restore 下一个进程的sp到 esp */
        "movl $1f,%1\n\t" /* save 当前进程的 eip */
        "pushl %3\n\t"  //保存下一个进程eip保存到栈里面
        "ret\n\t"  /* restore eip */
        "1:\t" /* next process start here */
        "popl %%ebp\n\t"**
        : "=m" (prev->thread.sp),"=m" (prev->thread.ip)**
        : "m" (next->thread.sp),"m" (next->thread.ip)**
        );
        my_current_task = next;
        printk(KERN_NOTICE ">>>switch %d to %d<<<\n",prev->pid,next->pid);
    }
    else//下一个进程为第一次运行时,没有进程上下文, 则以下面这种方式来处理
    {
        next->state = 0;
        my_current_task = next;
        printk(KERN_NOTICE ">>>switch %d to %d<<<\n",prev->pid,next->pid);
        /* switch to new process */
        asm volatile(
            "pushl %%ebp\n\t"  /* save ebp */
            "movl %%esp,%0\n\t"  /* save esp */x`
            "movl %2,%%esp\n\t" /* restore esp */
            "movl %2,%%ebp\n\t" /* restore ebp */
            "movl $1f,%1\n\t" /* save eip */
            "pushl %3\n\t"**
            "ret\n\t"  /* restore eip */**
            : "=m" (prev->thread.sp),"=m" (prev->thread.ip)
            : "m" (next->thread.sp),"m" (next->thread.ip)
        );
    }
    return;
}
```

以新任务切换为例进行堆栈变化分析：

![](/images/in-post/2015-06-15-Linux-Kernel-analysis-Os-work/2018-09-19-01-15-18.gif)

执行结果如下图所示：

![](/images/in-post/2015-06-15-Linux-Kernel-analysis-Os-work/2018-09-19-01-15-09.png)