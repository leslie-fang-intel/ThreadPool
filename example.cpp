#include <iostream>
#include <vector>
#include <chrono>

#include "ThreadPool.h"

int main()
{
    ThreadPool pool(1);
    std::vector< std::future<int> > results;

    int i = 0;
    timestamp1 = std::chrono::high_resolution_clock::now();
    auto res_future = pool.enqueue([i] {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return i*i;
        });
    auto res = res_future.get();
    timestamp4 = std::chrono::high_resolution_clock::now();

    std::cout<<"res is: "<<res<<std::endl;
    float submit_time_us = std::chrono::duration_cast<std::chrono::nanoseconds>(
                             timestamp2 - timestamp1).count() / 1000.0;
    std::cout<<"submit_time_us is: "<<submit_time_us<<" us"<<std::endl;

    float execution_time_us = std::chrono::duration_cast<std::chrono::nanoseconds>(
                             timestamp3 - timestamp2).count() / 1000.0;
    std::cout<<"execution_time_us is: "<<execution_time_us<<" us"<<std::endl;

    float join_time_us = std::chrono::duration_cast<std::chrono::nanoseconds>(
                             timestamp4 - timestamp3).count() / 1000.0;
    std::cout<<"join_time_us is: "<<join_time_us<<" us"<<std::endl;

    float total_time_us = std::chrono::duration_cast<std::chrono::nanoseconds>(
                             timestamp4 - timestamp1).count() / 1000.0;
    std::cout<<"total_time_us is: "<<total_time_us<<" us"<<std::endl;

    return 0;
}
