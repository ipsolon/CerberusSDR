/*!
 * @brief     API header file
 *            This file contains all the publicly exposed methods and data
 *            structures to interface with API.
 *
 * @copyright copyright(c) 2018 analog devices, inc. all rights reserved.
 *            This software is proprietary to Analog Devices, Inc. and its
 *            licensor. By using this software you agree to the terms of the
 *            associated analog devices software license agreement.
 */

/*!
 * @addtogroup __ADI_HMC7044__
 * @{
 */
#ifndef __ADI_HMC7044_H__
#define __ADI_HMC7044_H__

/*============= I N C L U D E S ============*/
#include "adi_cms_api_common.h"
#include "spi.h"

/*============= D E F I N E S ==============*/
#define HMC7044_NOF_OP_CH					14
#define HMC7044_CH_DIV_MAX					4095
#define HMC7044_SLIP_DELAY_MAX				4095
#define HMC7044_SPI_RESET_PERIOD_US         10
#define HMC7044_DIV_RESET_PERIOD_US         5000
#define HMC7044_NOF_CLK_IN					4
#define HMC7044_NOF_GPIO_MAX				4
#define HMC7044_PLL2_R_DIV_MAX				4095
#define HMC7044_HW_RESET_PERIOD_US			10
#define HMC7044_REF_CLK_FREQ_HZ_MIN			150
#define HMC7044_REF_CLK_FREQ_HZ_MAX 		800000000ull
#define HMC7044_VCXO_CLK_FREQ_HZ_MIN		10000000ull
#define HMC7044_VCXO_CLK_FREQ_HZ_MAX		500000000ull
#define HMC7044_PD1_CLK_FREQ_HZ_MIN			150
#define HMC7044_PD1_CLK_FREQ_HZ_MAX			50000000ull
#define HMC7044_PD2_CLK_FREQ_HZ_MIN			150
#define HMC7044_PD2_CLK_FREQ_HZ_MAX			250000000ull
#define HMC7044_LCM_CLK_FREQ_HZ_MIN			150
#define HMC7044_LCM_CLK_FREQ_HZ_MAX			123000000ull
#define HMC7044_VCO_CLK_FREQ_HZ_MIN			2650000000ull
#define HMC7044_VCO_CLK_FREQ_HZ_MAX			3550000000ull
#define HMC7044_PLL1REF_CLK_FREQ_HZ_MIN		30000000ull
#define HMC7044_PLL1REF_CLK_FREQ_HZ_MAX		40000000ull
#define HMC7044_PLL2REF_CLK_DB_FREQ_HZ_MIN	10000000ull
#define HMC7044_PLL2REF_CLK_DB_FREQ_HZ_MAX	125000000ull

typedef enum {
	HMC7044_OP_CH_0  = 0x0001,
	HMC7044_OP_CH_1  = 0x0002,
	HMC7044_OP_CH_2  = 0x0004,
	HMC7044_OP_CH_3  = 0x0008,
	HMC7044_OP_CH_4  = 0x0010,
	HMC7044_OP_CH_5  = 0x0020,
	HMC7044_OP_CH_6  = 0x0040,
	HMC7044_OP_CH_7  = 0x0080,
	HMC7044_OP_CH_8  = 0x0100,
	HMC7044_OP_CH_9  = 0x0200,
	HMC7044_OP_CH_10 = 0x0400,
	HMC7044_OP_CH_11 = 0x0800,
	HMC7044_OP_CH_12 = 0x1000,
	HMC7044_OP_CH_13 = 0x2000,
	HMC7044_OP_CH_ALL = 0x3FFF
}adi_hmc7044_op_ch_e;

typedef enum {
	HMC7044_CLK_IN_0  = 0x1,
	HMC7044_CLK_IN_1  = 0x2,
	HMC7044_CLK_IN_2  = 0x4,
	HMC7044_CLK_IN_3  = 0x8,
	HMC7044_CLK_IN_ALL = 0XF
}adi_hmc7044_clk_in_e;

typedef enum {
    HMC7044_OP_SIG_CH_DIV = 0x0,
    HMC7044_OP_SIG_ANALOG_DELAY = 0x1,
    HMC7044_OP_SIG_CH_PAIR = 0x2,
    HMC7044_OP_SIG_IP_VC0 = 0x3,
    HMC7044_OP_SIG_INVALID = 0x4
}adi_hmc7044_op_source_e;

typedef struct {
    adi_cms_signal_type_e mode;                 /*!< Output Driver Mode */
    adi_cms_signal_impedance_type_e impedance;  /*!< Output Driver Impedance */
    uint8_t dynamic_driver_en;                  /*!< Dynamic Driver Mode Enable */
    uint8_t force_mute_en;                      /*!< Force Mute Enable */
}adi_hmc7044_op_driver_config_t;

typedef enum {
    IPBUFFER_INTERNAL_100_OHM_EN = 0x1,
    IPBUFFER_AC_COUPLED_MODE_EN  = 0x2,
    IPBUFFER_LVPECL_MODE_EN = 0x4,
    IPBUFFER_HIGH_Z_MODE_EN = 0x8,
    IPBUFFER_CONFIG_MAX = 0xF
}adi_hmc7044_ip_buffer_settings_e;

typedef struct {
    void *                user_data;
    adi_spi_xfer_t        spi_xfer;             /*!< Function Pointer to HAL SPI access function */
    adi_delay_us_t        delay_us;             /*!< Function Pointer to HAL delay function */
    adi_hw_open_t         hw_open;              /*!< Function Pointer to HAL initialization function */
    adi_hw_close_t        hw_close;             /*!< Function Pointer to HAL De-initialization function */
    adi_reset_pin_ctrl_t  reset_pin_ctrl;       /*!< Function Pointer to HAL RESETB Pin Control Function */
}adi_hmc7044_hal_t;

typedef struct {
    uint8_t  dev_prod_id;                       /*!< Product ID */
}adi_hmc7044_info_t;

typedef struct {
    adi_hmc7044_hal_t  hal_info;                /*!< HAL information */
    adi_hmc7044_info_t dev_info;                /*!< DEV information */
//    XSpi *hmc7044_spi;	// spi
}adi_hmc7044_device_t;

/*============= E X P O R T S ==============*/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  Open device
 *
 * @param  device Pointer to the device structure
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_INVALID_SPI_XFER_PTR   Invalid HAL SPI XFER FUNCTION
 * @return API_CMS_ERROR_INVALID_DELAYUS_PTR    Invalid HAL SPI XFER FUNCTION
 * @return API_CMS_ERROR_DELAY_US               Invalid HAL SPI XFER FUNCTION
 */
 int32_t adi_hmc7044_device_hw_open(adi_hmc7044_device_t *device);

 /**
 * @brief  Close device
 *
 * @param  device Pointer to the device structure
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_INVALID_DELAYUS_PTR    Invalid HAL SPI XFER FUNCTION
 * @return API_CMS_ERROR_DELAY_US               Invalid HAL SPI XFER FUNCTION
 */
 int32_t adi_hmc7044_device_hw_close(adi_hmc7044_device_t *device);

/**
 * @brief  Initialize device
 *         This API must be called first before any other API calls.
 *         It performs internal API initialization of the memory and API states.
 *         If device member hw_open is not NULL it shall call the function
 *         to which it points. This feature may be used to get and initialize the
 *         hardware resources required by the API and the device.
 *         For example GPIO, SPI etc.
 *         Its is recommended to call the Reset API after this API to ensure all
 *         SPI registers are reset to ADI recommended defaults.
 *
 * @param  device Pointer to the device structure
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 */
int32_t adi_hmc7044_device_init(adi_hmc7044_device_t *device);

/**
 * @brief  put device to sleep mode
 *
 * @param  device								Pointer to the device structure
 * @param  sleepmode							indicate whether hmc7044 is used
 *												1 - put hmc7044 to sleep
 *												0 - enable hmc7044
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 */
int32_t adi_hmc7044_device_sleep_set(adi_hmc7044_device_t *device, uint8_t sleepmode);

/**
 * @brief  De-initialize device.
 *         This API must be called last. No other API should be called after this call.
 *         It performs internal API De-initialization of the memory and API states.
 *         If device member hw_close is not NULL it shall call the function
 *         to which it points. This feature may be used to De-initialize and release
 *         any hardware resources required by the API and the device.
 *         For example GPIO, SPI etc.
 *
 * @param  device Pointer to the device structure
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 */
int32_t adi_hmc7044_device_deinit(adi_hmc7044_device_t *device);

/**
 * @brief  Reset device
 *         Issues a hard reset or soft reset of the device.
 *         Performs a full reset of device via the hardware pin (hard) or
 *         via the SPI register (soft).
 *         Resetting all SPI registers to default and triggering the required
 *         initialization sequence.
 *
 * @param  device   Pointer to the device structure.
 * @param  hw_reset A parameter to indicate if the reset issues is to be via the
 *                  hardware pin or SPI register.
 *                  A value of 1 indicates a hardware reset is required.
 *                  A value of 0 indicates a software reset is required.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_device_reset(adi_hmc7044_device_t *device, uint8_t hw_reset);

/**
 * @brief  Get Device Chip ID
 *
 * @param  device   Pointer to the device structure.
 * @param  chip_id  A pointer to a variable of type adi_chip_id_t
 *                  to return the details of the device id.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_device_chip_id_get(adi_hmc7044_device_t *device, adi_cms_chip_id_t *chip_id);

/**
 * @brief  Get API Revision Data
 *
 * @param  device    Pointer to the device structure.
 * @param  rev_major Pointer to variable to store the Major Revision Number
 * @param  rev_minor Pointer to variable to store the Minor Revision Number
 * @param  rev_rc    Pointer to variable to store the RC Revision Number
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_device_api_revision_get(adi_hmc7044_device_t *device, uint8_t *rev_major,
    uint8_t *rev_minor, uint8_t *rev_rc);

/**
 * @brief Perform SPI register write access to device
 *
 * @param device   Pointer to the device structure
 * @param address  SPI address to which the value of data parameter shall be written
 * @param data     8-bit value to be written to SPI register defined
 *                 by the address parameter.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_device_spi_register_set(adi_hmc7044_device_t *device, uint16_t addr, uint8_t val);

/**
 * @brief Perform SPI register read access to device.
 *
 *
 * @param device   Pointer to the device structure
 * @param address  SPI address from which the value of data parameter shall be read,
 * @param data     Pointer to an 8-bit variable to which the value of the
 *                 SPI register at the address defined by address parameter
 *                 shall be stored.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_device_spi_register_get(adi_hmc7044_device_t *device, uint16_t addr, uint8_t *val);

/**
 * @brief Trigger Internal Dividers and FSM restart via SPI
 *
 *
 * @param device   Pointer to the device structure
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_device_trigger_restart(adi_hmc7044_device_t *device);

/**
 * @brief Configure and enable GPI
 *
 *
 * @param device   Pointer to the device structure
 * @param index    Reference GPI index. Range 0 to 3
 *
 * @param config   Setting for GPI
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_gpi_config_set(adi_hmc7044_device_t *device, uint8_t index, uint8_t config);

/**
 * @brief Configure and enable GPO
 *
 *
 * @param device   Pointer to the device structure
 * @param index    Reference GPO index. Range 0 to 3
 *
 * @param enable   Config setting for GPO
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_gpo_config_set(adi_hmc7044_device_t *device, uint8_t index, uint8_t config);
/**
 * @brief Configure and enable Reference Clock Inputs
 *
 *
 * @param device   Pointer to the device structure
 * @param clk_in   Reference clock Input index. Range 0 to 3
 * @param config   Input Buffer Configuration for Reference Clock Input.
 *                 Refer to adi_hmc7044_ip_buffer_settings_e for configuration mask settings.
 *                 For example for ac coupled inputs with 100 Ohm internal termination.
 *                 Set config to IPBUFFER_INTERNAL_100_OHM_EN | PBUFFER_AC_COUPLED_MODE_EN
 * @param enable   Enable setting for Reference clock.
 *                 0 Disable Input
 *                 1 Enable Input
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_input_reference_set(adi_hmc7044_device_t *device, uint8_t clk_in, uint8_t config, uint8_t enable);

/**
 * @brief Set the input reference priority order
 *
 *
 * @param device     Pointer to the device structure
 * @param priority   Pointer to clock reference priority list.
 *                   where priority[0]
 *                   value represents the clock input index with the highest priority.
 * @param nof_ref    Size of/ Number of clock reference priority list. Range 1 to 4
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_input_reference_priority_set(adi_hmc7044_device_t *device, uint8_t priority[4], uint8_t nof_ref);

/**
 * @brief  Configure the operation during Loss of Signal(LOS)
 *
 * @param device         Pointer to the device structure
 * @param timer_cycles   Setting to configure the number of timer cycle to wait
 *                       before exiting LOS state after reference becomes valid.
 *                       Where the set value x, translatest 2^x timer cycles.
 *                       Valid Range 0 to 7
 *                       For example
 *                       0 - no wait
 *                       7 - 128 timer cycles.
 * @param ip_prescaler   LOS operation bypasses input prescaler.
 *                       1 - bypass input prescaler
 *                       0 - do not bypass input prescaler
 * @param vcxo_prescaler LOS operation uses VCXO prescaler.
 *                       1 - Use VCXO prescaler
 *                       0 - do not Use VCXO prescaler
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_input_reference_los_config_set(adi_hmc7044_device_t *device,
        uint8_t timer_cycles, uint8_t prescaler_bypass, uint8_t vcxo_prescaler_en);

/**
 * @brief  Configure the Input Reference Input Prescaler LCM Dividers
 *
 * @param device         Pointer to the device structure
 * @param clk_in         Reference Clock input index. Range 0 to 3
 * @param lcm_div        Value of prescaler divider setpoint 1 to 255
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_input_reference_prescaler_config_set(adi_hmc7044_device_t *device,
        uint8_t clk_in, uint8_t lcm_div);

/**
 * @brief  Configure the Oscillator Input Prescaler LCM Divider
 *
 * @param device         Pointer to the device structure
 * @param lcm_div        Value of prescaler divider setpoint 1 to 255
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_input_reference_oscin_prescaler_config_set(adi_hmc7044_device_t *device, uint8_t lcm_div);

/**
 * @brief  Configure the PLL1 PFD
 *
 * @param device    Pointer to the device structure
 * @param r_div     RefA input divider. 16-bit Value
 * @param n_div     Feedback divider to PLL1 16-bit Value
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_pll1_config_set(adi_hmc7044_device_t *device, uint16_t r_div, uint16_t n_div);

/**
 * @brief  Configure the PLL2 PFD
 *
 * @param device       Pointer to the device structure
 * @param freq_dbl_en  Enable Pre-divider Frequency Doubler
 * @param r_div        PLL2 R divider. 12 bit vlaue Range 1 to 4095
 * @param n_div        16 Bit Feedback divider to PLL2
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_pll2_config_set(adi_hmc7044_device_t *device, uint8_t freq_dbl_en, uint16_t r_div, uint16_t n_div);

/**
 * @brief  Get pll lock status
 *
 * @param  device   Pointer to the device structure.
 * @param  status   Pointer to pll1 and pll2 lock status
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_hmc7044_device_pll_lock_status_get(adi_hmc7044_device_t *device, uint8_t *status);

/**
 * @brief  Configure the Output Driver Controls
 *
 * @param device       Pointer to the device structure
 * @param output_ch    Ouput Channel Index. Range 0-13
 * @param output_sel   Output Signal Selection
 * @param ch_div       Ouput Channel Divider setting Range 1-4049
 * @param mode         Performace mode Enable
 *                     1- High Performance Mode Enabled
 *                     0- Normal Output Mode Enabled
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_output_config_set(adi_hmc7044_device_t *device, uint8_t output_ch,
            adi_hmc7044_op_source_e output_sel, uint16_t ch_div, uint8_t mode, uint8_t enable);

/**
 * @brief  Configure the Output Driver Controls
 *
 * @param device       Pointer to the device structure
 * @param output_ch    Ouput Channel Index.
 * @param config       A pointer to a structure defining the desired Output Driver Configuration.
 *        mode         Output Signal Type. Valid options CML, LVPECL, LVDS or CMOS.
 *        impedance    Output Signal Impedendence.
 *                     Valid Options: Internal Resistor Disabled, 100 Ohm, 50 Ohm
 *        dynamic_driver_en   Dynamic Driver Control for Pulse Generator Mode Only
 *                            0 - Driver Enable Controlled by Channel Enable
 *                            1 - Driver Dynamically Enabled with Pulse Gen Events.
 *        force_mute_en       Idle at Logic 0 Mode Enable for Pulse Generator Mode Only
 *                            0 - Normal Mode
 *                            1 - Force to Logic 0
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_output_driver_config_set(adi_hmc7044_device_t *device,
        uint8_t output_ch, adi_hmc7044_op_driver_config_t *config);

/**
 * @brief  Configure the Output Analog and Digital Delay Adjustments
 *
 * @param device       Pointer to the device structure
 * @param output_ch    Ouput Channel Index.
 * @param course_adj   Digital Course Delay Adjustment in 1/2 VCO Clk Step sizesd.Range 0-17
 * @param fine_adj     Analog Fine Delay Adjustment in 25ps. Range 0 to 24.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_output_delay_set(adi_hmc7044_device_t *device,
                uint8_t output_ch, uint8_t coarse_adj, uint8_t fine_adj);

/**
 * @brief  Configure the Output Analog and Digital Delay Adjustments
 *
 * @param device        Pointer to the device structure
 * @param output_ch     Ouput Channel Index.
 * @param startup_mode  Set the channel start mode. Range 0-1
 *                      0 - Asynchronous
 *                      1 - Dynamic / Pulse Generator Mode
 * @param slip_mode_en  Slip Event Enable Setting. Channel processes Slip events. Range 0-1
 * @param sync_mode_en  Sync Event Enable Setting. Channel Process Sync Events. Range 0-1.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_output_sync_config_set(adi_hmc7044_device_t *device, uint8_t output_ch,
                uint8_t startup_mode, uint8_t slip_mode_en, uint8_t sync_mode_en);

/**
 * @brief  Configure the Channel For Multislip Configuration
 *
 * @param device        Pointer to the device structure
 * @param output_ch     Ouput Channel Index.
 * @param multi_slip_en Multi Slip Enable Setting.Range 0-1.
 * @param slip_delay    Multi Slip Delay Setting in VCO cycles. Range 0-4095.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_output_multi_slip_config_set(adi_hmc7044_device_t *device,
            uint8_t output_ch, uint8_t multi_slip_en, uint16_t slip_delay);

/**
 * @brief  Configure the Output Enable
 * Note: All configuration setting should be completed before enabling.
 *
 * @param device       Pointer to the device structure
 * @param enable       Output Signal Enable Range 0-1
 *                     0 - Disable
 *                     1 - Enable.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_output_enable_set(adi_hmc7044_device_t *device, uint8_t output_ch, uint8_t en);

/**
 * @brief  Configure the Output performance setting
 * Note: All configuration setting should be completed before enabling.
 *
 * @param device       Pointer to the device structure
 * @param enable       optimum performance enable
 *					   0 - disable
 *					   1 - enable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_output_performance_set(adi_hmc7044_device_t *device, uint8_t enable);

/**
 * @brief  HMC register update
 *
 * @param device       Pointer to the device structure
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_reg_update(adi_hmc7044_device_t *device);

/**
 * @brief  VCO enable
 *
 * @param device       Pointer to the device structure
 * @param disable	   internal enable
 *					   0 - disable
 *					   1 - enable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_vco_enable_set(adi_hmc7044_device_t *device, uint8_t enable);

/**
 * @brief  set up R1 N1 R2 N2 for pll config
 *
 * @param device       		   Pointer to the device structure
 * @param ref_clk_freq_hz	   on board osc ref clk
 * @param pfd1_freq_hz		   phase frequency detector for pll1
 * @param pfd2_freq_hz		   phase frequency detector for pll2
 * @param dist_freq_hz		   Distribution frequency
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_distribution_clk_config(adi_hmc7044_device_t *device, uint64_t ref_clk_freq_hz, uint64_t pfd1_freq_hz, uint64_t dist_freq_hz, uint64_t pfd2_freq_hz);

/**
 * @brief  HMC7044 clock configuration top level API
 *
 * @param device                    Pointer to the device structure
 * @param ref_ch				    Channel mask of Clock Input reference source
 * @param ref_clk_freq_hz           Ref clk from clock input channel
 * @param ref_priority				Ref clk priority
 * @param fvcxo_clk_freq_hz         Desired fvcxo clk frequency
 * @param output_ch                 Channel mask of desired output channel
 * @param output_freq_hz[14]        Desired generated clocks on desired output channel
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_clk_config(adi_hmc7044_device_t *device, adi_hmc7044_clk_in_e ref_ch, uint8_t ref_priority[4], uint64_t ref_clk_freq_hz, uint64_t fvcxo_clk_freq_hz, uint16_t output_ch, uint64_t output_freq_hz[14]);

/**
 * @brief  HMC7044 pll configuration
 *
 * @param device                    Pointer to the device structure
 * @param ref_ch                  Channel mask of Clock Input reference source
 * @param ref_clk_freq_hz           Ref clk from clock input channel
 * @param fvcxo_clk_freq_hz         Desired fvcxo clk frequency
 * @param fpfd1_freq_hz             Phase frequency detector for pll1
 * @param fvco_freq_hz              Desired fvco clk frequency
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return API_CMS_ERROR_INVALID_HANDLE_PARAM   Invalid Device Handle
 * @return API_CMS_ERROR_SPI_XFER               SPI Access Failed
 * @return API_CMS_ERROR_INVALID_PARAM          Invalid Parameter
 */
int32_t adi_hmc7044_pll_config(adi_hmc7044_device_t *device, adi_hmc7044_clk_in_e ref_ch, uint64_t ref_clk_freq_hz, uint64_t fvcxo_clk_freq_hz, uint64_t fpfd1_freq_hz, uint64_t fvco_freq_hz);

#ifdef __cplusplus
}
#endif

#endif /* __ADI_HMC7044_H__ */
/*! @} */
