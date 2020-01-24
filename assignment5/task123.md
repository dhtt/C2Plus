
1.  A common variable counter is incremented from 5 threads 5000 times. The result is 24756. How is that possible? (1 P.)
    When increment function is called, the current value held by the object is retrieved, incremented and returned in count. The read and write operations on the same object of all threads that are running concurrently may overlap each other in execution. This is an example of "race condition" and results in inconsistent outcomes within each run. 
2.  How could you correct the problem? Provide a short code example. (2 P.)
    ```
    struct Counter{
	    std::mutex::mutex;
	    int value;
	    Counter() value(0){}
	    void increment(){
		    std::lock_guard<std::mutex> _(mutex);
		    ++value;
		    } 
    };
    ```
3.  Why should lock_guard be preferred to explicit locking? (1 P.)
    Lock_guard simplifies the codes as users do not need to combine lock and unlock and reduces the risk of having a dead-lock since lock is released when it goes out of scope thanks to the lock_guard destructor. Thus it is more prefered in the context of explicit locking. 
4.  What is an alternative to locking variables and why? (1 P.)
    Alternative to locking variables, users can avail atomic functions/operations which can be faster than locking as they are implemented with lock-free operations, while maintaining  safety in multithread environments like lock mutex.
5.  Can multiple threads access a variable that is read-only safely without locking? (1 P.)
    A read-only variable can be accessed by multiple threads without locking. No modification is allowed after the variable is initialized so it is immutable and thread-safe. 
6.  Which type of mutex would you use if you have multiple threads reading from the same value and only one writing to the value? Provide a short code example. (2 P.)
    shared_mutex would be a good choice here as it provides  shared and exclusive access at the same time. The thread responsible for writing would acquire the exclusive lock, while all others with reading function acquire the shared lock.
    ```
    struct read_and_write{
	    std::shared_mutex mutex; 
	    void write_fun() {
		    std::lock_guard<std::shared_mutex> lock(mutex);
		    //write...
	    }
	    void read_fun() {
		    std::shared_lock<std::shared_mutex> lock(mutex);
		    //read ...
	    }
    };
    ```

7.  How would you parallelize a for loop with the Intel TBB? How with OpenMP? (2 P.)
Intel TBB: A for loop could be parallelized by parallel_for or parallel_for_each with the lower bound, the upper bound and a loop body, usually wrapped in a lambda expression, as arguments. The loop body would be called in parallel by the threads created by Intel TBB.
OpenMP: Include "#pragma omp prallel for" before a for loop to parallelized the loop.
