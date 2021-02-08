set(libmovavg_SRCS
    libmovavg.h
    libmovavg.cpp
)

# Declare the library
add_library(libmovavg STATIC
    ${libmovavg_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(libmovavg PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
