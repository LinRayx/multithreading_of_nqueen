#include "ThreadPool.h"
#include <iostream>
#include <memory>
#include <chrono>
#define NUMBER_OF_THREADS 8


static int cnt = 0;
const static int n = 15;

/*
 第 i 个皇后
 pie -> [n-1-i, 2n-1-i]
 na ->  [n-1-i, 2n-1-i]
 
 
 */
int dfs(int i, int col, int pie, int na) {
   // std::thread::id id = std::this_thread::get_id();
   // std::cout << id << std::endl;
    int res = 0;
    int t = ((1<<n) -1) & ~(col|(pie >> i) | (na >> (n-1-i)));
    while(t) {
        int pos = t&(-t);
        t ^= pos;
        if(i == n-1) {
            res++;
            
        }
        else {
            col ^= pos;
            pie ^= (pos << i);
            na ^= (pos << (n-i-1));
            res += dfs(i+1, col, pie, na);
            col ^= pos;
            pie ^= (pos << i);
            na ^= (pos << (n-i-1));
        }
    }

    return res;
}

int main() {
    using namespace std;
    using namespace std::chrono;
    auto start = system_clock::now();
 
    ThreadPool *threadPool = new ThreadPool(5);
    
    
       
        
        for(int i = 0; i < n; ++i) {
            std::function<int(int ,int ,int ,int)> func = dfs;
            cnt += threadPool->enqueue(func, 1,(1<<i), (1<<i), (1<<(n-1+i))).get();

        }

    
    std::cout << cnt << std::endl;
    auto end   = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout <<  "多线程n皇后花费了"
    << double(duration.count()) * microseconds::period::num / microseconds::period::den
    << "秒" << endl;


    
    auto start2 = system_clock::now();
    cout << dfs(0,0,0,0) << endl;
    auto end2   = system_clock::now();
    auto duration2 = duration_cast<microseconds>(end2 - start2);
    cout <<  "单线程n皇后花费了"
    << double(duration2.count()) * microseconds::period::num / microseconds::period::den
    << "秒" << endl;
    return 0;
}

 
