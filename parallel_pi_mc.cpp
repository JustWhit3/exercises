#include <iostream>
#include <random>
#include <mutex>
#include <oneapi/tbb.h>
#include <oneapi/tbb/info.h>
#include <oneapi/tbb/parallel_for.h>
#include <oneapi/tbb/task_arena.h>

int main()
 {
  std::random_device rd;
  std::default_random_engine eng{rd()};
  std::uniform_real_distribution<double> uniform_dist{-1, 1};
  size_t N = 10000000;
  int N_int = 0;
  std::mutex mu;

  // Normal
  //for(int i=0; i<N; i++) {
  //  double x = uniform_dist(eng);
  //  double y = uniform_dist(eng);
  //  double r = (x*x) + (y*y);
  //  
  //  if(r<1.0) { N_int += 1; }
  // }

  // Parallelized
 oneapi::tbb::parallel_for(
    oneapi::tbb::blocked_range<int>(0,N),
    [&](const oneapi::tbb::blocked_range<int>& range)
    {
        for(int i = range.begin(); i< range.end(); ++i)
        {
            double x = uniform_dist(eng);
            double y = uniform_dist(eng);
            double r = (x*x) + (y*y);
            
            std::lock_guard l(mu);
            if(r<1.0) { N_int += 1; }
        }
    });


  std::cout << "pi = " << 4.0 * static_cast<double>(N_int)/static_cast<double>(N) << "\n";
 }