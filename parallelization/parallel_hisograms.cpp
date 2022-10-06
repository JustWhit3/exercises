#include <iostream>
#include <random>

int main(){
  std::random_device rd;
  std::default_random_engine eng{rd()};
  std::uniform_real_distribution<float> normal_dist{0, 20};
}