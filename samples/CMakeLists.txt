add_library(matrix_lib INTERFACE)
target_sources(matrix_lib INTERFACE utmatrix.h)

target_include_directories(matrix_lib INTERFACE "${MP2_INCLUDE}")

if(MSVC)
    add_custom_target(matrix_lib.headers SOURCES "${MP2_INCLUDE}/utmatrix.h")
endif()

add_executable(sample_matrix sample_matrix.cpp)
target_link_libraries(sample_matrix INTERFACE matrix_lib)

#https://stackoverflow.com/questions/39887352/how-to-create-a-cmake-header-only-library-that-depends-on-external-header-files/39889958