set(Main_SRCS
cxxopts.hpp    
libmovavg.h
libmovavg.cpp
main.cpp

)

add_executable(movavg
    ${Main_SRCS}
)




 

install(TARGETS movavg DESTINATION bin)
