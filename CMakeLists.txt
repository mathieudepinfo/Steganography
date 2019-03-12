cmake_minimum_required (VERSION 2.6)
project (Steganography)

set(OpenCV_DIR C:/opencv/build/x64/vc15)
set(OpenCV_INCLUDE_DIRS C:/opencv/build/include)

set(OpenCV_LIBD C:/opencv/build/x64/vc15/lib/opencv_world342d.lib)
set(OpenCV_LIB C:/opencv/build/x64/vc15/lib/opencv_world342.lib)

set(LIB ${CMAKE_BINARY_DIR}/lib/Release)
set(LIBD ${CMAKE_BINARY_DIR}/lib/Debug)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(SteganographyLib)
add_subdirectory(PartA_encoder)
add_subdirectory(PartB_encoder)
add_subdirectory(PartC_encoder)
add_subdirectory(PartD_encoder)
add_subdirectory(PartE_encoder)
add_subdirectory(PartA_decoder)
add_subdirectory(PartB_decoder)
add_subdirectory(PartD_decoder)
add_subdirectory(PartE_decoder)

file(COPY ImageSrc DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ImagesA DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ImagesB DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ImagesC DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ImagesD DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ImagesE DESTINATION ${PROJECT_BINARY_DIR})