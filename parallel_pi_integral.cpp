#include <iostream>
#include <iomanip>
#include <oneapi/tbb.h>
#include <oneapi/tbb/info.h>
#include <oneapi/tbb/parallel_for.h>
#include <oneapi/tbb/task_arena.h>
#include <boost/atomic.hpp>
//#include <mutex>

int main()
 {
  int num_steps = 1<<20;
  double pi = 0.;
  double step = 1.0/(double) num_steps;
  boost::atomic<double> sum; // Figo
  // std::mutex mu; // Se usassi mutex
  sum = 0.;

  // Not parallelized
  //for (int i=0; i< num_steps; i++){
  //  auto x = (i+0.5)*step;
  //  sum = sum + 4.0/(1.0+x*x);
  //}

 // Parallelized
 oneapi::tbb::parallel_for(
    oneapi::tbb::blocked_range<int>(0,num_steps),
    [&](const oneapi::tbb::blocked_range<int>& range)
    {
        for(int i = range.begin(); i< range.end(); ++i)
        {
            auto x = (i+0.5)*step;

            //std::lock_guard l(mu);
            //sum += sum ...

            sum.fetch_add( 4.0/(1.0+x*x) );
        }
    });
  
  pi = step * sum;
  std::cout << "sum: " << std::setprecision (15) << pi << std::endl;
 }