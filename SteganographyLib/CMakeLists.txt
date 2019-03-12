include_directories( ${OpenCV_INCLUDE_DIRS} )

add_library(SteganographyLib Steganograph.h Steganograph.cpp)
target_link_libraries( SteganographyLib ${OpenCV_LIBS} )
