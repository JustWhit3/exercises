#include <iostream>
#include <random>
#include <vector>
#include <mutex>
#include <oneapi/tbb.h>
#include <oneapi/tbb/info.h>
#include <oneapi/tbb/parallel_for.h>
#include <oneapi/tbb/task_arena.h>

struct Histogram
 {
   void fill_bin( double value )
    {
     bins[value] += 1;
    }
  
  private:

   std::vector<int> bins = std::vector<int>(100);
   static constexpr int16_t width = 5;
 };

int main()
 {
  std::default_random_engine generator;
  std::normal_distribution<double> distribution{0, 20};
  std::mutex mu;
  
  Histogram histo;

  oneapi::tbb::parallel_for(
     oneapi::tbb::blocked_range<int>(0,500000000),
     [&](const oneapi::tbb::blocked_range<int>& range)
     {
         for(int i = range.begin(); i< range.end(); ++i)
         {
             double no = distribution(generator);
             std::lock_guard l(mu);
             histo.fill_bin( no );
         }
     });
 }