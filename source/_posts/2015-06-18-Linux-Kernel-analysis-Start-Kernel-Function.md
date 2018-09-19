---
title: Linux内核分析课程3_start_kernel()函数分析
date: 2015-03-01 13:04:27
updated: 2015-04-01 13:04:27
categories: Linux
tags: Linux kernel
---

Linux内核课第三周作业。本文在云课堂中实验楼完成。  
[唐国泽](http://guozet.me/about/) 原创作品转载请注明出处.  
[《Linux内核分析》MOOC课程](http://mooc.study.163.com/course/USTC-1000029000)

<!--more-->

# 分析Start_kernel函数

我使用的是linux-2.6.14的源代码来分析的。在这里突出重点，主要来分析start_kernel这个函数中的大致实现。开机启动到start_kernel这个过程主要是汇编来实现的，具体可参考

- [linux kernel 从入口到start_kernel 的代码分析](https://blog.csdn.net/aaronychen/article/details/2838341)

start_kernel()这个函数是内核由引导程序引导以后，由自解压程序解压以后执行的第一个函数，可以认为是整个内核的入口函数，start_kernel()做的工作就是线性的初始化一些内核的基础机制，如中断，内存管理，进程管理，信号，文件系统，KO等！最后就启动一个init线程，init线程再读取文件系统里的init程序，做为系统的第一个进程而存在！

start_kernel源码如下：

```cpp
<span style="font-size:14px;">asmlinkage void __init start_kernel(void)
{
    char * command_line; //命令行，用来存放bootloader传递过来的参数
    extern struct kernel_param __start___param[], __stop___param[];<span style="font-family: Arial, Helvetica, sans-serif; font-size: 12px;">//这两个变量为地址指针，指向内核启动参数处理相关结构体在内存的位置， </span>
    lock_kernel();<span style="font-family: Arial, Helvetica, sans-serif; font-size: 12px;">//建立一个哈希表(hash tables)，就是一个前后指向的指针结构体数组。</span><span style="font-family: Arial, Helvetica, sans-serif; font-size: 12px;">【函数的主要作用是初始化锁的状态跟踪模块。由于内核大量使用锁来进行多进程多处理器的同步操作，死锁就会在代码不合理的时候出现，但是要定位哪个锁比较困难，用哈希表可以跟踪锁的使用状态。死锁情况：一个进程递归加锁同一把锁；同一把锁在两次中断中加锁；几把锁形成闭环死锁】</span>
    page_address_init(); //初始化高端内存的映射表 
    printk(KERN_NOTICE); //打印信息
    printk(linux_banner); //打印Linux的版本信息
    setup_arch(&command_line); <span style="font-family: Arial, Helvetica, sans-serif; font-size: 12px;">//内核架构相关初始化函数，是非常重要的一个初始化步骤。其中包含了处理器相关参数的初始化、内核启动参数(tagged list)的获取和前期处理、内存子系统的早期初始化(bootmem分配器)</span>
<span style="font-family: Arial, Helvetica, sans-serif; font-size: 12px;">       setup_per_cpu_areas();</span>
    smp_prepare_boot_cpu();//为SMP系统里引导CPU(boot-cpu)进行准备工作。在ARM系统单核里是空函数
    sched_init();<span style="white-space:pre">	</span>//对进程调度器的数据结构进行初始化，创建运行队列，设置当前任务的空线程，当前任务的调度策略为CFS调度器 
    preempt_disable(); //关闭优先级调度。由于每个进程任务都有优先级，目前系统还没有完全初始化，还不能打开优先级调度。 
    build_all_zonelists();
    page_alloc_init();  //设置内存页分配通知器
    printk(KERN_NOTICE "Kernel command line: %s\n", saved_command_line); //输出命令参数到显示终端
    parse_early_param(); //解析cmdline中的启动参数
    parse_args("Booting kernel", command_line, __start___param,
           __stop___param - __start___param,
           &unknown_bootoption);
    //这行代码主要对传入内核参数进行解释，如果不能识别的命令就调用最后参数的函数
    sort_main_extable();//对内核异常表(exception table)按照异常向量号大小进行排序，以便加速访问
    trap_init(); //对内核陷阱异常进行初始化，初始化一些中断向量，在ARM系统里是空函数，没有任何的初始化 
    rcu_init(); //初始化直接读拷贝更新的锁机制。 Read-Copy Update 【RCU主要提供在读取数据机会比较多，但更新比较的少的场合，这样减少读取数据锁的性能低下的问题。】 
    init_IRQ();<span style="white-space:pre">	</span>//对应架构特定的中断初始化函数，在ARM中就是machine_desc->init_irq()，就是运行设备描述结构体中的init_irq函数[arch/arm/mach-msm/board-xxx.c]
    pidhash_init();
    init_timers();<span style="white-space:pre">	</span>
    //初始化引导CPU的时钟相关的数据结构，注册时钟的回调函数，当时钟到达时可以回调时钟处理函数，最后初始化时钟软件中断处理
    //初始化定时器,开启定时器软中断服务以及注册服务程序以及初始化各CPU中的tev_base等init_timers()->run_timer_softirq()->__run_timers()..

    softirq_init();
    //初始化软件中断，软件中断与硬件中断区别就是中断发生时，软件中断是使用线程来监视中断信号，而硬件中断是使用CPU硬件来监视中断。
    time_init();  //初始化系统时钟。开启一个硬件定时器，开始产生系统时钟就是system_timer的初始化,arch/arm/mach-msm/board-*.c 
    console_init();
    if (panic_later)
        panic(panic_later, panic_param);
    profile_init();
    local_irq_enable();
#ifdef CONFIG_BLK_DEV_INITRD
    if (initrd_start && !initrd_below_start_ok &&
            initrd_start < min_low_pfn << PAGE_SHIFT) {
        printk(KERN_CRIT "initrd overwritten (0x%08lx < 0x%08lx) - "
            "disabling it.\n",initrd_start,min_low_pfn << PAGE_SHIFT);
        initrd_start = 0;
    }
#endif
    vfs_caches_init_early(); //前期虚拟文件系统(vfs)的缓存初始化
    mem_init(); //初始化内存并计算可用内存大小;标记哪些内存可以使用，并且告诉系统有多少内存可以使用，当然是除了内核使用的内存以外
    kmem_cache_init(); // 初始化SLAB缓存分配器  
    setup_per_cpu_pageset();
    numa_policy_init();
    if (late_time_init)
        late_time_init();
    calibrate_delay();
    pidmap_init(); //进程号位图初始化，一般用一个page来指示所有的进程PID占用情况 
    pgtable_cache_init();
    prio_tree_init(); //初始化内核基于radix树的优先级搜索树(PST)，初始化结构体
    anon_vma_init();  //初始化反向映射的匿名内存，提供反向查找内存的结构指针位置，快速地回收内存。
#ifdef CONFIG_X86
    if (efi_enabled)
        efi_enter_virtual_mode();
#endif
    fork_init(num_physpages); //初始化kernel的fork()环境。Linux下应用程序执行是靠系统调用fork()完成，fork_init所完成的工作就是确定可以fork()的线程的数量，然后是初始化init_task进程
    proc_caches_init();  //进程缓存初始化，为进程初始化创建机制所需的其他数据结构申请空间 
    buffer_init();  //初始化文件系统的缓冲区，并计算最大可以使用的文件缓存。
    unnamed_dev_init(); //初始化一个虚拟文件系统使用的哑文件
    key_init();  //没有键盘则为空，如果有键盘，则为键盘分配一个高速缓存
    security_init();
    vfs_caches_init(num_physpages); //初始化虚拟文件系统
    radix_tree_init();
    signals_init(); //初始化内核信号队列….
    page_writeback_init(); //页面写机制初始化
#ifdef CONFIG_PROC_FS
    proc_root_init();
    //初始化系统进程文件系统，主要提供内核与用户进行交互的平台，方便用户实时查看进程的信息。
#endif
    cpuset_init(); //初始化CPUSET，CPUSET主要为控制组提供CPU和内存节点的管理的结构。
    check_bugs(); //检查CPU配置、FPU等是否非法使用不具备的功能，检查CPU BUG，软件规避BUG
    acpi_early_init(); /* before LAPIC and SMP init */
    rest_init(); //最后实际进入reset_init()函数，包括所有剩下的硬件驱动，线程初始化等过程…这也最终完成start_kernel的启动过程。
}</span>

```

接下来分析init进程的创建和执行：
![](/images/in-post/2015-06-18-Linux-Kernel-analysis-Start-Kernel-Function/2018-09-19-01-21-04.png)

![](/images/in-post/2015-06-18-Linux-Kernel-analysis-Start-Kernel-Function/2018-09-19-01-21-19.png)

`start_kernel() -> rest_init() -> kernel_init() -> 启动init进程;`

rest_init函数中创建的一个内核线程kernel_init，调用该内核线程之后，该线程要完成的任务是启动init进程，也就是我们所谓的１号进程，是系统启动后的第一个进程。大致可如下表示：
0号进程(rest_init)->1号内核进程（kernel_init）->1号用户进程（init进程）
同时０号进程rest_init中最后会调用一个idle的进程，idle进程是在系统中没有任何任务执行的时候，该任务开始工作。

# 实验：内核调试

![](/images/in-post/2015-06-18-Linux-Kernel-analysis-Start-Kernel-Function/2018-09-19-01-22-15.png)

![](/images/in-post/2015-06-18-Linux-Kernel-analysis-Start-Kernel-Function/2018-09-19-01-22-25.png)

![](/images/in-post/2015-06-18-Linux-Kernel-analysis-Start-Kernel-Function/2018-09-19-01-22-34.png)