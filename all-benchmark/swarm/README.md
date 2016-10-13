# what is it?
 - 本程序实现了基数排序算法.

# how to run?
 - 参数已经作为默认值写入，直接运行即可。

# introduction
 1. 程序有main和4个子线程。
 2. 4个子线程的数据。
 > 都是分配在同一块内存。
 > 线程ID为0的负责malloc内存。
 > 每个线程通过不同的偏移量访问自己的数据。
 3. 1.73M expr, so it can not solve.

 3. 通过SWARM_Barrier()保持4个线程同步工作。

 > 若某些SWARM_Barrier()注释掉，则可能导致内存还没有分配就使用的情况，导致BUG。

 4. 程序计算函数为radixsort_swarm_s3();其中调用了两次countsort_swarm();
 
# bug1
 - 在两个SWARM_Barrier()中添加全局变量，不上锁的话会触发assert。\

# bug2
 - 4个线程调度虽然是随机的，但是由于SWARM_Barrier()的存在总可以保证线程0优先执行。
 - 设定在特殊的调度下线程0最后执行就会触发assert。