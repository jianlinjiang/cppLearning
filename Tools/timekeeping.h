#include<sys/time.h>
#include<chrono>
class WatchPoint{
    struct timespec start_ts;
    bool is_started;
    
    public:
        void start() noexcept{
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&this->start_ts);
            this->is_started = true;
        }

        long get_ns() const noexcept{
            struct timespec end_ts;
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end_ts);    //CPU花在进程处理的时间，与时钟时间不同，且不计算进程被挂起的时间
            long s = end_ts.tv_sec - this->start_ts.tv_sec;
            long ns = s * 1000000000L + end_ts.tv_nsec - this->start_ts.tv_nsec;    //可能会有溢出的情况
            return ns;
        }

        double get_ms() const noexcept{
            return get_ns() / 1000000.0;
        }
};