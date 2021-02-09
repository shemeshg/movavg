#ifndef __LIBMOVAVG_H__
#define __LIBMOVAVG_H__
#include <cstddef>
#include <algorithm>
#include <vector>

/*
Probably next time I should have used std::accumulate
https://stackoverflow.com/questions/7616511/calculate-mean-and-standard-deviation-from-a-vector-of-samples-in-c-using-boos
*/

template <typename T, typename Total>
class Moving_Average
{
  public:
    void setSizeOf(size_t i){
      N = i;
      samples_.resize(N);
    }

    void operator()(T sample)
    {
        if (num_samples_ < N)
        {
            samples_[num_samples_++] = sample;
            total_ += sample;
        }
        else if(N == 0){
          total_ += sample;
          num_samples_++;
        }
        else
        {
            T& oldest = samples_[num_samples_++ % N];
            total_ += sample - oldest;
            oldest = sample;
        }
    }

    operator double() const { 
      if (N ==0){return total_ / num_samples_;}
      return total_ / std::min(num_samples_, N); 
    }

    bool isNull(){
      return num_samples_ == 0;
    }

  private:
    size_t N = 1;
    std::vector<T> samples_;
    size_t num_samples_{0};
    Total total_{0};
};


#endif // __LIBMOVAVG_H__