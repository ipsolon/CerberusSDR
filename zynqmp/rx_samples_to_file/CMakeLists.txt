project(SAMPLES_TO_FILE)

add_executable(rx_samples_to_file rx_samples_to_file.cpp)
set_target_properties(rx_samples_to_file PROPERTIES
                                         CXX_STANDARD 11
                                         CXX_STANDARD_REQUIRED ON
                                         CXX_EXTENSIONS OFF)

target_include_directories(rx_samples_to_file PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(rx_samples_to_file ${Boost_LIBRARIES} )
install(TARGETS rx_samples_to_file DESTINATION bin)