---
title: Some ways to run a task in the background.
date: 2018-10-19 16:26:46
updated: 2018-10-19 16:26:46
categories: Linux
tags: Linux
---

![](/images/in-post/2018-10-19-Linux-Run-Task-Background/2018-10-19-18-03-04.png)

When we use Linux system, we often want to run some task in the background. Most of time, we hope the task can run in a long-term until we power off the laptop. So, I would like to discuss a few ways to implement this goal.

## Use the &

We can add the `&` symbol after the command. Then this task will run until you kill this terminal.

```bash
$ ./test.sh &
$ jobs
```

In this case, you can use the `jobs` command to get the background tasks which begin in this bash. However, when you close this terminal or bash. All of the tasks which were created in this bash will be closed.

但是如上方到后台执行的进程，其父进程还是当前终端shell的进程，而一旦父进程退出，则会发送hangup信号给所有子进程，子进程收到hangup以后也会退出。如果我们要在退出shell的时候继续运行进程，则需要使用nohup忽略hangup信号，或者setsid将将父进程设为init进程(进程号为1)：

```bash
# nohup ./rsync.sh &

# setsid ./rsync.sh &
或
# (./rsync.sh &)        ////在一个subshell中执行
# ps -ef|grep rsync
```

```bash
bg %1
%1
```

