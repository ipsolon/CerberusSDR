
project(HMC7044_CONFIG)

set(SOURCE_FILES src/adi_hmc7044_device.c
                 src/adi_hmc7044_output_ch.c
                 src/adi_hmc7044_pll.c
                 src/adi_utils.c
                 src/main.c
                 src/command_line_parser.c
                 src/fpga_axi.c
                 src/hmc7044_hal.c
                 src/spi.c
                 src/timer.c
                 src/uc_settings.c)

add_executable(hmc7044_config  ${SOURCE_FILES})
target_include_directories(hmc7044_config PUBLIC ${PROJECT_SOURCE_DIR}/include )

install(TARGETS   hmc7044_config DESTINATION bin)
install(DIRECTORY hmc7044_data   DESTINATION bin)

