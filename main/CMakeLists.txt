set(Main_SRCS
    main.cpp
)

add_executable(movavg
    ${Main_SRCS}
)


set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS program_options REQUIRED)  
include_directories(${Boost_INCLUDE_DIRS}) 


# Specify here the libraries this program depends on
target_link_libraries(movavg libmovavg )
target_link_libraries(movavg ${Boost_LIBRARIES} )
 

install(TARGETS movavg DESTINATION bin)
