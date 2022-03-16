project(ZYNQMP)

find_package(Boost 1.68 COMPONENTS system program_options)

add_subdirectory(hmc7044_config)
add_subdirectory(rx_samples_to_file)

