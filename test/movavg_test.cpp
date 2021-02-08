#include "gtest/gtest.h"
#include "libmovavg.h"


TEST(Movag, few_elements)
{
    Moving_Average<double, double> ma;
    ma.setSizeOf(10); 
    ma(10); 
    ma(14); 
    ma(20); 
    ma(8);
    
  EXPECT_EQ(ma, 13);
}


