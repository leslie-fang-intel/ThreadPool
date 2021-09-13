#include <iostream>
#include <vector>
#include <chrono>

#include "ThreadPool.h"

int main()
{
    ThreadPool pool(1);
    std::vector< std::future<int> > results;


    asm volatile ( "CPUID\n\t"
                "RDTSC\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::"%rax", "%rbx", "%rcx", "%rdx");

    asm volatile ( "CPUID\n\t"
                "RDTSC\n\t"
                "CPUID\n\t"
                "RDTSC\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::"%rax", "%rbx", "%rcx", "%rdx");

    asm volatile ("CPUID\n\t"
    "RDTSC\n\t"::: "%rax", "%rbx", "%rcx", "%rdx");

    int i = 0;
    //timestamp1 = std::chrono::high_resolution_clock::now();
    asm volatile ( "CPUID\n\t"
            "RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::"%rax", "%rbx", "%rcx", "%rdx");
    auto res_future = pool.enqueue([i] {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return i*i;
        });
    auto res = res_future.get();
    //timestamp4 = std::chrono::high_resolution_clock::now();

    timestamp1 = ( ((uint64_t)cycles_high << 32) | cycles_low );
    timestamp2 = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
    std::cout<<timestamp1<<std::endl;
    std::cout<<timestamp2<<std::endl;
    std::cout<<"timestamp2 - timestamp1(submit time clock): "<<timestamp2-timestamp1<<std::endl;
    return 0;
}
