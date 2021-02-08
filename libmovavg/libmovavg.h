#ifndef __LIBMOVAVG_H__
#define __LIBMOVAVG_H__
#include <cstddef>
#include <algorithm>
#include <vector>

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
        else
        {
            T& oldest = samples_[num_samples_++ % N];
            total_ += sample - oldest;
            oldest = sample;
        }
    }

    operator double() const { return total_ / std::min(num_samples_, N); }

  private:
    size_t N = 1;
    std::vector<T> samples_;
    size_t num_samples_{0};
    Total total_{0};
};


#endif // __LIBMOVAVG_H__