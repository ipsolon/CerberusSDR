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
 * @addtogroup __ADI_AD9082__
 * @{
 */
#ifndef __ADI_AD9082_H__
#define __ADI_AD9082_H__

/*============= I N C L U D E S ============*/
#include "adi_cms_api_common.h"
#include "spi.h"

/*============= D E F I N E S ==============*/
#define AD9082_ID                     0x9082
#define AD9082_REF_CLK_FREQ_HZ_MIN    100000000ull    /*!< 100 MHz */
#define AD9082_REF_CLK_FREQ_HZ_MAX    2000000000ull   /*!< 2   GHz */
#define AD9082_ADC_CLK_FREQ_HZ_MIN    1500000000ull   /*!< 1.5 GHz */
#define AD9082_ADC_CLK_FREQ_HZ_MAX    6000000000ull   /*!< 6   GHz */
#define AD9082_DAC_CLK_FREQ_HZ_MIN    3000000000ull   /*!< 3   GHz */
#define AD9082_DAC_CLK_FREQ_HZ_MAX    12000000000ull  /*!< 12  GHz */

/*!
 * @brief Enumerates Chip Output Resolution
 */
typedef enum {
    AD9082_CHIP_OUT_RES_16BIT = 0x0,                  /*!< 16Bit */
    AD9082_CHIP_OUT_RES_15BIT = 0x1,                  /*!< 15Bit */
    AD9082_CHIP_OUT_RES_14BIT = 0x2,                  /*!< 14Bit */
    AD9082_CHIP_OUT_RES_13BIT = 0x3,                  /*!< 13Bit */
    AD9082_CHIP_OUT_RES_12BIT = 0x4,                  /*!< 12Bit */
    AD9082_CHIP_OUT_RES_11BIT = 0x5,                  /*!< 11Bit */
    AD9082_CHIP_OUT_RES_10BIT = 0x6,                  /*!< 10Bit */
    AD9082_CHIP_OUT_RES_09BIT = 0x7,                  /*!<  9Bit */
    AD9082_CHIP_OUT_RES_08BIT = 0x8                   /*!<  8Bit */
}adi_ad9082_chip_output_res_e;

/*!
 * @brief Enumerates DAC Select
 */
typedef enum {
    AD9082_DAC_NONE = 0x0,                            /*!< No DAC */
    AD9082_DAC_0 = 0x1,                               /*!< DAC0 */
    AD9082_DAC_1 = 0x2,                               /*!< DAC1 */
    AD9082_DAC_2 = 0x4,                               /*!< DAC2 */
    AD9082_DAC_3 = 0x8,                               /*!< DAC3 */
    AD9082_DAC_ALL = 0x0F                             /*!< ALL DACs */
}adi_ad9082_dac_select_e;

/*!
 * @brief Enumerates DAC Channel Select
 */
typedef enum {
    AD9082_DAC_CH_NONE = 0x00,                        /*!< No Channel */
    AD9082_DAC_CH_0 = 0x01,                           /*!< Channel 0 */
    AD9082_DAC_CH_1 = 0x02,                           /*!< Channel 1 */
    AD9082_DAC_CH_2 = 0x04,                           /*!< Channel 2 */
    AD9082_DAC_CH_3 = 0x08,                           /*!< Channel 3 */
    AD9082_DAC_CH_4 = 0x10,                           /*!< Channel 4 */
    AD9082_DAC_CH_5 = 0x20,                           /*!< Channel 5 */
    AD9082_DAC_CH_6 = 0x40,                           /*!< Channel 6 */
    AD9082_DAC_CH_7 = 0x80,                           /*!< Channel 7 */
    AD9082_DAC_CH_ALL = 0xFF                          /*!< ALL Channels */
}adi_ad9082_dac_channel_select_e;

/*!
 * @brief Enumerates ADC Select
 */
typedef enum {
    AD9082_ADC_NONE = 0x0,                            /*!< No ADC */
    AD9082_ADC_0 = 0x1,                               /*!< ADC0 */
    AD9082_ADC_1 = 0x2,                               /*!< ADC1 */
    AD9082_ADC_2 = 0x4,                               /*!< ADC2 */
    AD9082_ADC_3 = 0x8,                               /*!< ADC3 */
    AD9082_ADC_ALL = 0x0F                             /*!< ALL ADCs */
}adi_ad9082_adc_select_e;

/*!
 * @brief Enumerates ADC NCO Modes
 */
typedef enum {
    AD9082_ADC_NCO_VIF = 0,                           /*!< Variable IF Mode */
    AD9082_ADC_NCO_ZIF = 1,                           /*!< Zero IF Mode */
    AD9082_ADC_NCO_FS_4_IF = 2,                       /*!< Fs/4 Hz IF Mode */
    AD9082_ADC_NCO_TEST = 3,                          /*!< Test Mode */
    AD9082_ADC_NCO_INVALID = 4                        /*!< Invalid NCO Mode */
}adi_ad9082_adc_nco_mode_e;

/*!
 * @brief Enumerates ADC->Coarse DDC CrossBar
 */
typedef enum {
    AD9082_ADC_4_ADC_REAL_MODE = 0,                   /*!< Quad ADC Real Mode */
    AD9082_ADC_4_ADC_COMP_MODE = 1,                   /*!< Quad ADC Complex Mode */
    AD9082_ADC_2_ADC_REAL_MODE = 2,                   /*!< Dual ADC Real Mode */
    AD9082_ADC_2_ADC_COMP_MODE = 3                    /*!< Dual ADC Complex MOde */
}adi_ad9082_adc_adc_to_cddc_xbar_e;

/*!
 * @brief Enumerates Coarse DDC0/1->Fine DDC0 CrossBar
 */
typedef enum {
    AD9082_ADC_CDDC0_TO_FDDC0 = 0,
    AD9082_ADC_CDDC1_TO_FDDC0 = 1
} adi_ad9082_adc_cddc_to_fddc0_xbar_e;

/*!
 * @brief Enumerates Coarse DDC0/1->Fine DDC1 CrossBar
 */
typedef enum {
    AD9082_ADC_CDDC0_TO_FDDC1 = 0,
    AD9082_ADC_CDDC1_TO_FDDC1 = 2
} adi_ad9082_adc_cddc_to_fddc1_xbar_e;

/*!
 * @brief Enumerates Coarse DDC0/1->Fine DDC2 CrossBar
 */
typedef enum {
    AD9082_ADC_CDDC0_TO_FDDC2 = 0,
    AD9082_ADC_CDDC1_TO_FDDC2 = 4
} adi_ad9082_adc_cddc_to_fddc2_xbar_e;

/*!
 * @brief Enumerates Coarse DDC0/1->Fine DDC3 CrossBar
 */
typedef enum {
    AD9082_ADC_CDDC0_TO_FDDC3 = 0,
    AD9082_ADC_CDDC1_TO_FDDC3 = 8
} adi_ad9082_adc_cddc_to_fddc3_xbar_e;

/*!
 * @brief Enumerates Coarse DDC2/3->Fine DDC4 CrossBar
 */
typedef enum {
    AD9082_ADC_CDDC2_TO_FDDC4 = 0,
    AD9082_ADC_CDDC3_TO_FDDC4 = 0x10
} adi_ad9082_adc_cddc_to_fddc4_xbar_e;

/*!
 * @brief Enumerates Coarse DDC2/3->Fine DDC5 CrossBar
 */
typedef enum {
    AD9082_ADC_CDDC2_TO_FDDC5 = 0,
    AD9082_ADC_CDDC3_TO_FDDC5 = 0x20
} adi_ad9082_adc_cddc_to_fddc5_xbar_e;

/*!
 * @brief Enumerates Coarse DDC2/3->Fine DDC6 CrossBar
 */
typedef enum {
    AD9082_ADC_CDDC2_TO_FDDC6 = 0,
    AD9082_ADC_CDDC3_TO_FDDC6 = 0x40
} adi_ad9082_adc_cddc_to_fddc6_xbar_e;

/*!
 * @brief Enumerates Coarse DDC2/3->Fine DDC7 CrossBar
 */
typedef enum {
    AD9082_ADC_CDDC2_TO_FDDC7 = 0,
    AD9082_ADC_CDDC3_TO_FDDC7 = 0x80
} adi_ad9082_adc_cddc_to_fddc7_xbar_e;

/*!
 * @brief Enumerates ADC coarse DDC select
 */
typedef enum {
    AD9082_ADC_CDDC_NONE = 0x00,                      /*!< No COARSE DDC */
    AD9082_ADC_CDDC_0 = 0x01,                         /*!< COARSE DDC 0 */
    AD9082_ADC_CDDC_1 = 0x02,                         /*!< COARSE DDC 1 */
    AD9082_ADC_CDDC_2 = 0x04,                         /*!< COARSE DDC 2 */
    AD9082_ADC_CDDC_3 = 0x08,                         /*!< COARSE DDC 3 */
    AD9082_ADC_CDDC_ALL = 0x0F                        /*!< ALL COARSE DDCs */
}adi_ad9082_adc_coarse_ddc_select_e;

/*!
 * @brief Enumerates ADC fine DDC select
 */
typedef enum {
    AD9082_ADC_FDDC_NONE = 0x00,                      /*!< No FINE DDC */
    AD9082_ADC_FDDC_0 = 0x01,                         /*!< FINE DDC 0 */
    AD9082_ADC_FDDC_1 = 0x02,                         /*!< FINE DDC 1 */
    AD9082_ADC_FDDC_2 = 0x04,                         /*!< FINE DDC 2 */
    AD9082_ADC_FDDC_3 = 0x08,                         /*!< FINE DDC 3 */
    AD9082_ADC_FDDC_4 = 0x10,                         /*!< FINE DDC 4 */
    AD9082_ADC_FDDC_5 = 0x20,                         /*!< FINE DDC 5 */
    AD9082_ADC_FDDC_6 = 0x40,                         /*!< FINE DDC 6 */
    AD9082_ADC_FDDC_7 = 0x80,                         /*!< FINE DDC 7 */
    AD9082_ADC_FDDC_ALL = 0xFF                        /*!< ALL FINE DDCs */
}adi_ad9082_adc_fine_ddc_select_e;

/*!
 * @brief Enumerates ADC Coarse DDC decimation
 */
typedef enum {
    AD9082_CDDC_DCM_1  = 0xC,                         /*!< Decimate by 1 */
    AD9082_CDDC_DCM_2  = 0x0,                         /*!< Decimate by 2 */
    AD9082_CDDC_DCM_3  = 0x8,                         /*!< Decimate by 3 */
    AD9082_CDDC_DCM_4  = 0x1,                         /*!< Decimate by 4 */
    AD9082_CDDC_DCM_6  = 0x5,                         /*!< Decimate by 6 */
    AD9082_CDDC_DCM_8  = 0x2,                         /*!< Decimate by 8 */
    AD9082_CDDC_DCM_9  = 0x9,                         /*!< Decimate by 9 */
    AD9082_CDDC_DCM_12 = 0x6,                         /*!< Decimate by 12 */
    AD9082_CDDC_DCM_16 = 0x3,                         /*!< Decimate by 16 */
    AD9082_CDDC_DCM_18 = 0xA,                         /*!< Decimate by 18 */
    AD9082_CDDC_DCM_24 = 0x7,                         /*!< Decimate by 24 */
    AD9082_CDDC_DCM_36 = 0xB                          /*!< Decimate by 36 */
}adi_ad9082_adc_coarse_ddc_dcm_e;

/*!
* @brief Enumerates ADC Fine DDC decimation
*/
typedef enum {
    AD9082_FDDC_DCM_1  = 0x8,                         /*!< Decimate by 1 */
    AD9082_FDDC_DCM_2  = 0x0,                         /*!< Decimate by 2 */
    AD9082_FDDC_DCM_3  = 0x4,                         /*!< Decimate by 3 */
    AD9082_FDDC_DCM_4  = 0x1,                         /*!< Decimate by 4 */
    AD9082_FDDC_DCM_6  = 0x5,                         /*!< Decimate by 6 */
    AD9082_FDDC_DCM_8  = 0x2,                         /*!< Decimate by 8 */
    AD9082_FDDC_DCM_12 = 0x6,                         /*!< Decimate by 12 */
    AD9082_FDDC_DCM_16 = 0x3,                         /*!< Decimate by 16 */
    AD9082_FDDC_DCM_24 = 0x7,                         /*!< Decimate by 24 */
}adi_ad9082_adc_fine_ddc_dcm_e;

/*!
* @brief Enumerates ADC Fine DDC I/Q Converter
*/
typedef enum {
    AD9082_FDDC_0_I = 0x0,                            /*!< FDDC0 I */
    AD9082_FDDC_0_Q = 0x1,                            /*!< FDDC0 Q */
    AD9082_FDDC_1_I = 0x2,                            /*!< FDDC1 I */
    AD9082_FDDC_1_Q = 0x3,                            /*!< FDDC1 Q */
    AD9082_FDDC_2_I = 0x4,                            /*!< FDDC2 I */
    AD9082_FDDC_2_Q = 0x5,                            /*!< FDDC2 Q */
    AD9082_FDDC_3_I = 0x6,                            /*!< FDDC3 I */
    AD9082_FDDC_3_Q = 0x7,                            /*!< FDDC3 Q */
    AD9082_FDDC_4_I = 0x8,                            /*!< FDDC4 I */
    AD9082_FDDC_4_Q = 0x9,                            /*!< FDDC4 Q */
    AD9082_FDDC_5_I = 0xA,                            /*!< FDDC5 I */
    AD9082_FDDC_5_Q = 0xB,                            /*!< FDDC5 Q */
    AD9082_FDDC_6_I = 0xC,                            /*!< FDDC6 I */
    AD9082_FDDC_6_Q = 0xD,                            /*!< FDDC6 Q */
    AD9082_FDDC_7_I = 0xE,                            /*!< FDDC7 I */
    AD9082_FDDC_7_Q = 0xF,                            /*!< FDDC7 Q */
}adi_ad9082_adc_fine_ddc_converter_e;

/*!
 *@brief Enumerates ADC Nyquist Zone
 */
typedef enum {
    AD9082_ADC_NYQUIST_ZONE_ODD = 0x00,               /*!< odd  zone */
    AD9082_ADC_NYQUIST_ZONE_EVEN = 0x01               /*!< even zone */
} adi_ad9082_adc_nyquist_zone_e;

/*!
 *@brief Enumerates PFIR Control Page
 */
typedef enum {
    AD9082_ADC_PFIR_ADC_PAIR0 = 0x01,                 /*!< PFIR ADC Pair0 */
    AD9082_ADC_PFIR_ADC_PAIR1 = 0x02,                 /*!< PFIR ADC Pair1 */
    AD9082_ADC_PFIR_ADC_PAIR_ALL = 0x03               /*!< PFIR ADC Pair All */
} adi_ad9082_adc_pfir_ctl_page_e;

/*!
 *@brief Enumerates PFIR Coefficient Page
 */
typedef enum {
    AD9082_ADC_PFIR_COEFF_PAGE0 = 0x01,               /*!< PFIR Coefficient Page0 */
    AD9082_ADC_PFIR_COEFF_PAGE1 = 0x02,               /*!< PFIR Coefficient Page1 */
    AD9082_ADC_PFIR_COEFF_PAGE2 = 0x04,               /*!< PFIR Coefficient Page2 */
    AD9082_ADC_PFIR_COEFF_PAGE3 = 0x08,               /*!< PFIR Coefficient Page3 */
    AD9082_ADC_PFIR_COEFF_PAGE_ALL = 0x0F             /*!< PFIR Coefficient Page All */
} adi_ad9082_adc_pfir_coeff_page_e;

/*!
 *@brief Enumerates ADC PFIR I-Mode
 */
typedef enum {
   AD9082_ADC_PFIR_I_MODE_DISABLE = 0x0,              /*!< Disabled (filters bypassed) */
   AD9082_ADC_PFIR_I_MODE_RN = 0x1,                   /*!< Real N-Tap Filter for each I/Q channel (X only) */
   AD9082_ADC_PFIR_I_MODE_R2N = 0x2,                  /*!< Real 2 * N-Tap Filter for each I/Q channel (X and Y together) */
   AD9082_ADC_PFIR_I_MODE_R2CN = 0x4,                 /*!< Real set of two cascaded N-Tap Filters for each I/Q channel (X then Y cascaded) */
   AD9082_ADC_PFIR_I_MODE_4RN = 0x5                   /*!< Full Complex Filter using Four Real N-Tap Filters for the I/Q channels */
} adi_ad9082_adc_pfir_i_mode_e;

/*!
 *@brief Enumerates ADC PFIR Q-Mode
 */
typedef enum {
   AD9082_ADC_PFIR_Q_MODE_DISABLE = 0x0,              /*!< Disabled (filters bypassed) */
   AD9082_ADC_PFIR_Q_MODE_RN = 0x1,                   /*!< Real N-Tap Filter for each I/Q channel (X only) */
   AD9082_ADC_PFIR_Q_MODE_R2N = 0x2,                  /*!< Real 2 * N-Tap Filter for each I/Q channel (X and Y together) */
   AD9082_ADC_PFIR_Q_MODE_R2CN = 0x4,                 /*!< Real set of two cascaded N-Tap Filters for each I/Q channel (X then Y cascaded) */
   AD9082_ADC_PFIR_Q_MODE_4RN = 0x5                   /*!< Full Complex Filter using Four Real N-Tap Filters for the I/Q channels */
} adi_ad9082_adc_pfir_q_mode_e;

/*!
 *@brief Enumerates ADC PFIR Gain
 */
typedef enum {
   AD9082_ADC_PFIR_GAIN_N12DB = 0x6,                  /*!< -12dB */
   AD9082_ADC_PFIR_GAIN_N6DB = 0x7,                   /*!<  -6dB */
   AD9082_ADC_PFIR_GAIN_0DB = 0x0,                    /*!<   0dB */
   AD9082_ADC_PFIR_GAIN_P6DB = 0x1,                   /*!<   6dB */
   AD9082_ADC_PFIR_GAIN_P12DB = 0x2                   /*!<  12dB */
} adi_ad9082_adc_pfir_gain_e;

/*!
 * @brief Enumerates Link Select
 */
typedef enum {
    AD9082_LINK_NONE = 0x0,                           /*!< No Link */
    AD9082_LINK_0 = 0x1,                              /*!< Link 0 */
    AD9082_LINK_1 = 0x2,                              /*!< Link 1 */
    AD9082_LINK_ALL = 0x3                             /*!< All Links */
}adi_ad9082_jesd_link_select_e;

/*!
 * @brief Enumerates Reset Operation
 */
typedef enum {
    AD9082_SOFT_RESET = 0,                            /*!< Soft reset */
    AD9082_HARD_RESET = 1,                            /*!< Hard reset */
    AD9082_SOFT_RESET_AND_INIT = 2,                   /*!< Soft reset then init */
    AD9082_HARD_RESET_AND_INIT = 3                    /*!< Hard reset then init */
}adi_ad9082_reset_e;

/*!
 * @brief Enumerates ADC Test Mode Type
 */
typedef enum {
    AD9082_TMODE_OFF         = 0x0,                   /*!< Normal Operation */
    AD9082_TMODE_MIDSCALE    = 0x1,                   /*!< Midscale short */
    AD9082_TMODE_POS_FULL    = 0x2,                   /*!< Positive Full-Scale */
    AD9082_TMODE_NEG_FULL    = 0x3,                   /*!< Negative Full-Scale */
    AD9082_TMODE_ALT_CHECKER = 0x4,                   /*!< Alternating Checker Board */
    AD9082_TMODE_PN9         = 0x5,                   /*!< PN9 Sequence */
    AD9082_TMODE_PN23        = 0x6,                   /*!< PN23 Sequence */
    AD9082_TMODE_1_0_TOGG    = 0x7,                   /*!< 1/0 Word Toggle */
    AD9082_TMODE_USER_PAT    = 0x8,                   /*!< User Pattern Test Mode */
    AD9082_TMODE_PN7         = 0x9,                   /*!< PN7 Sequence */
    AD9082_TMODE_PN15        = 0xA,                   /*!< PN15 Sequence */
    AD9082_TMODE_PN31        = 0xB,                   /*!< PN31 Sequence */
    AD9082_TMODE_UNUSED_1    = 0xC,                   /*!< Unused */
    AD9082_TMODE_UNUSED_2    = 0xD,                   /*!< Unused */
    AD9082_TMODE_UNUSED_3    = 0xE,                   /*!< Unused */
    AD9082_TMODE_RAMP        = 0xF                    /*!< Ramp output */
}adi_ad9082_tmode_type_e;

/*!
 * @brief JESD PRBS Test Result Structure
 */
typedef struct {
    uint32_t phy_prbs_err_cnt;                      /*!< PRBS Test Error Count */
    uint8_t  phy_prbs_pass;                         /*!< PRBS Test Status */
    uint8_t  phy_src_err_cnt;                       /*!< PRBS Test Source Error Count */
}adi_ad9082_prbs_test_t;

/*!
 * @brief Device Hardware Abstract Layer Structure
 */
typedef struct {
    void *                    user_data;
    adi_cms_spi_sdo_config_e  sdo;                  /*!< SPI interface 3/4 wire mode configuration */
    adi_cms_spi_msb_config_e  msb;                  /*!< SPI interface MSB/LSB bit order configuration */
    adi_cms_spi_addr_inc_e    addr_inc;             /*!< SPI interface address increment configuration */
    adi_cms_signal_type_e     syncoutb;             /*!< Desired Signal type for SYNCOUTB signal */
    adi_cms_signal_coupling_e sysref;               /*!< Desired Input coupling for SysRef signal */

    adi_spi_xfer_t            spi_xfer;             /*!< Function Pointer to HAL SPI access function */
    adi_delay_us_t            delay_us;             /*!< Function Pointer to HAL delay function */
    adi_hw_open_t             hw_open;              /*!< Function Pointer to HAL initialization function */
    adi_hw_close_t            hw_close;             /*!< Function Pointer to HAL De-initialization function */
    adi_log_write_t           log_write;            /*!< Function Pointer to HAL log write function */
    adi_tx_en_pin_ctrl_t      tx_en_pin_ctrl;       /*!< Function Pointer to HAL TX_ENABLE Pin Control function */
    adi_reset_pin_ctrl_t      reset_pin_ctrl;       /*!< Function Pointer to HAL RESETB Pin Control Function */
}adi_ad9082_hal_t;

/*!
 * @brief Device Internal Information Structure
 */
typedef struct {
    /* passed by user and set by API */
    uint64_t dev_freq_hz;                           /*!< Device Clock Frequency in Hz */
    uint64_t dac_freq_hz;                           /*!< DAC Clock Frequency in Hz. 1.5GHz ~ 12GHz */
    uint64_t adc_freq_hz;                           /*!< ADC Clock Frequency in Hz. 1.5GHz ~ 6 GHz */
}adi_ad9082_info_t;

/*!
 * @brief Device Structure
 */
typedef struct {
    adi_ad9082_hal_t  hal_info;
    adi_ad9082_info_t dev_info;
//    XSpi *ad9082_spi;	// spi
}adi_ad9082_device_t;

/*============= E X P O R T S ==============*/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  Open hardware platform
 *
 * @param  device Pointer to the device structure
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
 int32_t adi_ad9082_device_hw_open(adi_ad9082_device_t *device);

 /**
 * @brief  Close hardware platform
 *
 * @param  device Pointer to the device structure
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
 int32_t adi_ad9082_device_hw_close(adi_ad9082_device_t *device);

/**
 * @brief  Initialize ad9082 device
 *
 * @param  device Pointer to the device structure
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_init(adi_ad9082_device_t *device);

/**
 * @brief  De-initialize device.
 *
 * @param  device Pointer to the device structure
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_deinit(adi_ad9082_device_t *device);

/**
 * @brief  Perform SPI interface configuration
 *
 * @param  device Pointer to the device structure
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_spi_config(adi_ad9082_device_t *device);

/**
 * @brief  Perform SPI register write access to device
 *
 * @param  device   Pointer to the device structure
 * @param  addr     SPI address to which the value of data parameter shall be written
 * @param  data     8-bit value to be written to SPI register defined by the address parameter.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_spi_register_set(adi_ad9082_device_t *device, uint16_t addr, uint8_t data);

/**
 * @brief  Perform SPI register read access to device
 *
 *
 * @param  device   Pointer to the device structure
 * @param  addr     SPI address from which the value of data parameter shall be read,
 * @param  data     Pointer to an 8-bit variable to which the value of the
 *                  SPI register at the address defined by address parameter shall be stored.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_spi_register_get(adi_ad9082_device_t *device, uint16_t addr, uint8_t *data);

/**
 * @brief  Perform SPI write access to device JRX cbus registers
 *
 * @param  device   Pointer to the device structure
 * @param  addr     SPI address to which the value of data parameter shall be written
 * @param  data     8-bit value to be written to SPI register defined by the address parameter.
 * @param  lane     lane index, 0 ~ 7
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_cbusjrx_register_set(adi_ad9082_device_t *device, uint8_t addr, uint8_t  data, uint8_t lane);

/**
 * @brief  Perform SPI read access to device JRX cbus registers
 *
 *
 * @param  device   Pointer to the device structure
 * @param  address  SPI address from which the value of data parameter shall be read,
 * @param  data     Pointer to an 8-bit variable to which the value of the
 *                  SPI register at the address defined by address parameter shall be stored.
 * @param  lane     lane index, 0 ~ 7
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_cbusjrx_register_get(adi_ad9082_device_t *device, uint8_t addr, uint8_t* data, uint8_t lane);

/**
 * @brief  Perform SPI write access to device JTX cbus registers
 *
 * @param  device   Pointer to the device structure
 * @param  addr     SPI address to which the value of data parameter shall be written
 * @param  data     8-bit value to be written to SPI register defined by the address parameter.
 * @param  lane     lane index, 0 ~ 7
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_cbusjtx_register_set(adi_ad9082_device_t *device, uint8_t addr, uint8_t  data, uint8_t lane);

/**
 * @brief  Perform SPI read access to device JTX cbus registers
 *
 *
 * @param  device   Pointer to the device structure
 * @param  address  SPI address from which the value of data parameter shall be read,
 * @param  data     Pointer to an 8-bit variable to which the value of the
 *                  SPI register at the address defined by address parameter shall be stored.
 * @param  lane     lane index, 0 ~ 7
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_cbusjtx_register_get(adi_ad9082_device_t *device, uint8_t addr, uint8_t* data, uint8_t lane);

/**
 * @brief  Perform SPI write access to device PLL cbus registers
 *
 * @param  device   Pointer to the device structure
 * @param  addr     SPI address to which the value of data parameter shall be written
 * @param  data     8-bit value to be written to SPI register defined by the address parameter.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_cbuspll_register_set(adi_ad9082_device_t *device, uint8_t addr, uint8_t  data);

/**
 * @brief  Perform SPI read access to device PLL cbus registers
 *
 *
 * @param  device   Pointer to the device structure
 * @param  address  SPI address from which the value of data parameter shall be read,
 * @param  data     Pointer to an 8-bit variable to which the value of the
 *                  SPI register at the address defined by address parameter shall be stored.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_cbuspll_register_get(adi_ad9082_device_t *device, uint8_t addr, uint8_t* data);

/**
 * @brief  Reset device
 *         Issues a hard reset or soft reset of the device.
 *         Performs a full reset of device via the hardware pin (hard) or
 *         via the SPI register (soft).
 *         Resetting all SPI registers to default and triggering the required
 *         initialization sequence.
 *
 * @param  device    Pointer to the device structure
 * @param  operation A parameter to indicate reset operation. @see adi_ad9082_reset_e
 *                   AD9082_SOFT_RESET indicates a software reset is required.
 *                   AD9082_HARD_RESET indicates a hardware reset is required.
 *                   AD9082_SOFT_RESET_AND_INIT indicates a software reset + initialization is required.
 *                   AD9082_HARD_RESET_AND_INIT indicates a hardware reset + initialization is required.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_reset(adi_ad9082_device_t *device, adi_ad9082_reset_e operation);

/**
 * @brief  Get pll lock status
 *
 * @param  device     Pointer to the device structure
 * @param  status     Pointer to pll lock fast (bit1) and slow status (bit0)
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_clk_pll_lock_status_get(adi_ad9082_device_t *device, uint8_t *status);

/**
 * @brief  Configure the clock circuitry based on the desired clocks frequencies
 *
 * @param  device     Pointer to the device structure
 * @param  dac_clk_hz Desired dac clock frequency
 * @param  adc_clk_hz Desired adc clock frequency
 * @param  ref_clk_hz Reference clock frequency
 * @param  pll_en     PLL enable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_clk_config_set(adi_ad9082_device_t *device, uint64_t dac_clk_hz,
    uint64_t adc_clk_hz, uint64_t ref_clk_hz, uint8_t pll_en);

/**
 * @brief  power up/down analog clock receiver
 *
 * @param  device   Pointer to the device structure
 * @param  enable   Enable clock receiver
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_aclk_receiver_enable_set(adi_ad9082_device_t *device, uint8_t enable);

/**
 * @brief  Get chip identification data
 *         Read-back product type, identification and revision data
 *
 * @param  device   Pointer to the device structure.
 * @param  chip_id  Pointer to a variable of type adi_cms_chip_id_t to
 *                  which the product data read-back from chip shall be stored.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_chip_id_get(adi_ad9082_device_t *device, adi_cms_chip_id_t *chip_id);

/**
 * @brief  Get API revision
 *
 * @param  device    Pointer to the device structure.
 * @param  rev_major Pointer to variable to store the major revision
 * @param  rev_minor Pointer to variable to store the minor revision
 * @param  rev_rc    Pointer to variable to store the rc    revision
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_api_revision_get(adi_ad9082_device_t *device, uint8_t *rev_major,
    uint8_t *rev_minor, uint8_t *rev_rc);

/**
 * @brief  Get Firmware revision
 *
 * @param  device    Pointer to the device structure.
 * @param  rev       Pointer to variable to store the firmware revision
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_firmware_revision_get(adi_ad9082_device_t *device, uint32_t *rev);

/**
 * @brief  Get Firmware patch revision
 *
 * @param  device    Pointer to the device structure.
 * @param  rev       Pointer to variable to store the firmware patch revision
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_firmware_patch_revision_get(adi_ad9082_device_t *device, uint32_t *rev);

/**
 * @brief  Startup Tx
 *
 * @param  device         Pointer to the device structure
 * @param  main_interp    Main interpolator
 * @param  chan_interp    Channel interpolator
 * @param  dac_chan       Enabled channels for each DAC
 * @param  main_shift     Main    NCO shift
 * @param  chan_shift     Channel NCO shift
 * @param  jesd_param     JRX JESD link settings
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_startup_tx(adi_ad9082_device_t *device, uint8_t main_interp,  uint8_t chan_interp,
    uint8_t dac_chan[4], int64_t main_shift[4], int64_t chan_shift[8], adi_cms_jesd_param_t *jesd_param);

/**
 * @brief  Startup Rx
 *
 * @param  device         Pointer to the device structure
 * @param  cddcs          Coarse DDC selection
 * @param  fddcs          Fine   DDC selection
 * @param  cddc_shift     Coarse DDC NCO shift
 * @param  fddc_shift     Foarse DDC NCO shift
 * @param  cddc_dcm       Coarse DDC decimation value
 * @param  fddc_dcm       Fine   DDC decimation value
 * @param  cc2r_en        Coase  DDC complex-to-real enable
 * @param  fc2r_en        Fine   DDC complex-to-real enable
 * @param  jesd_param     JTX JESD link settings
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_device_startup_rx(adi_ad9082_device_t *device, uint8_t cddcs, uint8_t fddcs,
    int64_t cddc_shift[4], int64_t fddc_shift[8], uint8_t cddc_dcm[4], uint8_t fddc_dcm[8],
    uint8_t cc2r_en[4], uint8_t fc2r_en[8], adi_cms_jesd_param_t jesd_param[2]);

/**
 * @brief  Select active DACs
 *
 * @param  device   Pointer to the device structure
 * @param  dacs     DAC mask
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_select_set(adi_ad9082_device_t *device, uint8_t dacs);

/**
 * @brief  Select active channels
 *
 * @param  device   Pointer to the device structure
 * @param  channels Channel Mask
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_chan_select_set(adi_ad9082_device_t *device, uint8_t channels);

/**
 * @brief  Select active DACs and active channels
 *
 * @param  device   Pointer to the device structure
 * @param  dacs     DAC mask
 * @param  channels Channel Mask
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_duc_select_set(adi_ad9082_device_t *device, uint8_t dacs, uint8_t channels);

/**
 * @brief  Power up or Power down Dac
 *
 * @param  device   Pointer to the device structure
 * @param  dacs     Target DAC to power up
 * @param  enable   Enable setting for dac power.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_power_up_set(adi_ad9082_device_t *device, uint8_t dacs, uint8_t enable);

/**
 * @brief  Enable test tone generation
 *
 * @param  device   Pointer to the device structure
 * @param  channels Channel mask
 * @param  enable   1:enable, 0:disable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_dc_test_tone_en_set(adi_ad9082_device_t *device, uint8_t channels, uint8_t enable);

/**
 * @brief  DC test tone amplitude setting
 *
 * @param  device   Pointer to the device structure
 * @param  channels Channel mask
 * @param  offset   Test tone offset value
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_dc_test_tone_offset_set(adi_ad9082_device_t *device, uint8_t channels, uint16_t offset);

/**
 * @brief  DC test tone amplitude setting
 *
 * @param  device    Pointer to the device structure
 * @param  channels  Channel mask
 * @param  offset_db Test tone offset in dB
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_dc_test_tone_offset_db_set(adi_ad9082_device_t *device, uint8_t channels, int8_t offset_db);

/**
 * @brief  Enable test tone generation
 *
 * @param  device   Pointer to the device structure
 * @param  dacs     DAC mask
 * @param  enable   1:enable, 0:disable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_duc_main_dc_test_tone_en_set(adi_ad9082_device_t *device, uint8_t dacs, uint8_t enable);

/**
 * @brief  DC test tone amplitude setting
 *
 * @param  device   Pointer to the device structure
 * @param  dacs     DAC mask
 * @param  offset   Test tone offset value
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_duc_main_dc_test_tone_offset_set(adi_ad9082_device_t *device, uint8_t dacs, uint16_t offset);

/**
 * @brief  DC test tone amplitude setting
 *
 * @param  device    Pointer to the device structure
 * @param  dacs      DAC mask
 * @param  offset_db Test tone offset in dB
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_duc_main_dc_test_tone_offset_db_set(adi_ad9082_device_t *device, uint8_t dacs, int8_t offset_db);

/**
 * @brief  Set DDSM working mode
 *
 * @param  device   Pointer to the device structure
 * @param  ddsms    DDSM group (0x1, 0x2 or 0x3)
 * @param  mode     DDSM working mode
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_ddsm_mode_set(adi_ad9082_device_t *device, uint8_t ddsms, uint8_t mode);

/**
 * @brief  Set Fine DUC gain
 *
 * @param  device   Pointer to the device structure
 * @param  channels Channel mask
 * @param  gain     Gain value
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_duc_nco_gain_set(adi_ad9082_device_t *device, uint8_t channels, uint16_t gain);

/**
 * @brief  Set Fine DUC gain
 *
 * @param  device   Pointer to the device structure
 * @param  channels Channel mask
 * @param  gain_db  Gain value in dB
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_duc_nco_gain_db_set(adi_ad9082_device_t *device, uint8_t channels, int8_t gain_db);

/**
 * @brief  Enable NCO on DAC and Channels
 *
 * @param  device   Pointer to the device structure
 * @param  dacs     DAC mask
 * @param  channels Channel mask
 * @param  enable   NCO enable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_duc_nco_enable_set(adi_ad9082_device_t *device, uint8_t dacs,
    uint8_t channels, uint8_t enable);

/**
 * @brief  Enable phase offset for the NCOs on the DAC and Channels
 *
 * @param  device   Pointer to the device structure
 * @param  dacs     DAC mask
 * @param  dacs_po  Desired DAC channel NCO phase offset
 * @param  channels Channel mask
 * @param  chs_po   Desired fine NCO phase offset
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_duc_nco_phase_offset_set(adi_ad9082_device_t *device, uint8_t dacs, uint16_t dacs_po, uint8_t channels, uint16_t chs_po);

/**
 * @brief  Configure NCO's FTW
 *
 * @param  device      Pointer to the device structure
 * @param  dacs        DAC mask, like AD9082_DAC_0, ...
 * @param  channels    Channel mask, like AD9082_DAC_CH_0, ...
 * @param  ftw         48bit frequency tuning word
 * @param  acc_modulus
 * @param  acc_delta
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_duc_nco_ftw_set(adi_ad9082_device_t *device, uint8_t dacs, uint8_t channels, uint64_t ftw, uint64_t acc_modulus, uint64_t acc_delta);

/**
 * @brief  Configure NCO Shift Freq
 *
 * @param  device       Pointer to the device structure
 * @param  dacs         DAC mask, like AD9082_DAC_0, ...
 * @param  channels     Channel mask, like AD9082_DAC_CH_0, ...
 * @param  nco_shift_hz NCO shift freq in Hz
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_duc_nco_set(adi_ad9082_device_t *device, uint8_t dacs, uint8_t channels, int64_t nco_shift_hz);

/**
 * @brief  Configure Main NCO's FFH FTW
 *
 * @param  device     Pointer to the device structure
 * @param  dacs       DAC mask, like AD9082_DAC_0, ...
 * @param  hopf_index Select which hopping frequency tuning word to set (1 ~ 31)
 * @param  hopf_ftw   32bit hopping frequency tuning word
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_duc_main_nco_hopf_ftw_set(adi_ad9082_device_t *device, uint8_t dacs, uint8_t hopf_index, uint32_t hopf_ftw);

/**
 * @brief  Configure Main NCO's FFH mode
 *
 * @param  device    Pointer to the device structure
 * @param  dacs      DAC mask, like AD9082_DAC_0, ...
 * @param  hopf_mode hopping mode
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_duc_main_nco_hopf_mode_set(adi_ad9082_device_t *device, uint8_t dacs, uint8_t hopf_mode);

/**
 * @brief  Select Which Main NCO's Hopping Frequency to use
 *
 * @param  device     Pointer to the device structure
 * @param  dacs       DAC mask, like AD9082_DAC_0, ...
 * @param  hopf_index Select which hopping frequency tuning word to use (0 ~ 31)
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_duc_main_nco_hopf_select_set(adi_ad9082_device_t *device, uint8_t dacs, uint8_t hopf_index);

/**
 * @brief  Configure the Digital Up Conversion Channels
 *
 * @param  device      Pointer to the device structure
 * @param  main_interp Main interpolation
 * @param  ch_interp   Channel interpolation
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_interpolation_set(adi_ad9082_device_t *device, uint8_t main_interp, uint8_t ch_interp);

/**
 * @brief  Set Main DAC to Channel Xbar
 *
 * @param  device     Pointer to the device structure
 * @param  dac        Target DAC Channel Output
 * @param  channel    Channel to be mapped to target DAC Channel Output
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_xbar_set(adi_ad9082_device_t *device, uint8_t dacs, uint8_t channel);

/**
 * @brief  Enalbe DAC's interrupts
 *
 * @param  device     Pointer to the device structure
 * @param  mask0      Interrupt mask 0 (bit0: PRBS_I, bit1: PRBS_Q)
 * @param  mask1      Interrupt mask 1 (bit2: HWIPERR0, bit3: PAERR0, bit6: HWIPERR1, bit7: PAERR1)
 * @param  mask2      Interrupt mask 2 (bit2: HWIPERR2, bit3: PAERR2, bit6: HWIPERR3, bit7: PAERR3)
 * @param  mask3      Interrupt mask 3
 *                        bit0: PLL_LOCK_FAST, bit1: PLL_LOCK_SLOW,
 *                        bit2: PLL_LOST_FAST, bit3: PLL_LOST_SLOW,
 *                        bit4: DLL_LOCK01,    bit5: DLL_LOST01
 *                        bit6: DLL_LOCK23,    bit5: DLL_LOST23
 * @param  mask4      Interrupt mask 4 (bit0~3: DLL out of range, bit4~7: DLL in range)
 * @param  enable     Enable (1) or disable (0) masked interrupts
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_irqs_enable_set(adi_ad9082_device_t *device, uint8_t mask0,
    uint8_t mask1, uint8_t mask2, uint8_t mask3, uint8_t mask4, uint8_t enable);

/**
 * @brief  Set Pa protection on DAC outputs
 *
 * @param  device     Pointer to the device structure
 * @param  dacs       Target DAC Channel Outputs of for PA Protection
 * @param  enable     Desired enable status
 *                        1 To enable DAC data
 *                        0 To blank DAC data
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_pa_protect_set(adi_ad9082_device_t *device, uint8_t dacs, uint8_t enable);

/**
 * @brief  Configure DAC NCO or DAC Channel NCO based on desired frequency
 *
 * @param  device       Pointer to the device structure
 * @param  dacs         Target DAC NCO, set to AD9082_DAC_NONE if configuring DAC Channel NCO
 * @param  channels     Target DAC Channel NCO, set to AD9082_DAC_CH_NONE if configuring DAC NCO
 * @param  nco_shift_hz Desired NCO frequency.
 * @param  amplitude    Desired NCO test tone amplitude
 * @param  test_tone_en Enable test tone
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_nco_set(adi_ad9082_device_t *device, uint8_t dacs, uint8_t channels,
    int64_t nco_shift_hz, int8_t amplitude, uint8_t test_tone_en);

/**
 * @brief  Set Enable on DAC outputs
 *
 * @param  device  Pointer to the device structure
 * @param  dacs    Target DAC Channel to enable data output
 * @param  enable  Desired enable status
 *                      1 To enable DAC data
 *                      0 To blank  DAC data
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_tx_enable_set(adi_ad9082_device_t *device, uint8_t dacs, uint8_t enable);

/**
 * @brief  Set full scale current of DAC outputs
 *
 * @param  device  Pointer to the device structure
 * @param  dacs    Target DAC Channel to enable data output
 * @param  mA      Desired current value in mA
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_fsc_set(adi_ad9082_device_t *device, uint8_t dacs, double mA);

/**
 * @brief  Set Enable on modules of DAC
 *
 * @param  device  Pointer to the device structure
 * @param  enable  Desired enable status
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_dac_spi_enable_set(adi_ad9082_device_t *device, uint8_t enable);

/**
 * @brief  Power up or Power down ADCs
 *
 * @param  device   Pointer to the device structure
 * @param  dacs     Target ADC to power up
 * @param  enable   Enable setting for adc power.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_power_up_set(adi_ad9082_device_t *device, uint8_t adcs, uint8_t enable);

/**
 * @brief  Read back the current ADC clock frequency
 *
 * @param  device     Pointer to the device structure
 * @param  adc_clk_hz Pointer to variable to store the current clk frequency in Hz
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_clk_freq_get(adi_ad9082_device_t *device, uint64_t *adc_clk_hz);

/**
 * @brief  Configure adc to cddc cross-bar
 *
 * @param  device           Pointer to the device structure
 * @param  adc_cddc_xbar    Configure ADC to Coarse DDC Crossbar, @see adi_ad9082_adc_adc_to_cddc_xbar_e
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_adc2cddc_xbar_set(adi_ad9082_device_t *device, uint8_t adc_cddc_xbar);

/**
 * @brief  Configure the rx data path cross-bar
 *
 * @param  device           Pointer to the device structure
 * @param  cddc_fddc_xbar   Configure Coarse to Fine DDC Crossbar
 *                              Bit[0] - 0/1 connects CDDC0/1 to FDDC0
 *                              Bit[1] - 0/1 connects CDDC0/1 to FDDC1
 *                              Bit[2] - 0/1 connects CDDC0/1 to FDDC2
 *                              Bit[3] - 0/1 connects CDDC0/1 to FDDC3
 *                              Bit[4] - 0/1 connects CDDC2/3 to FDDC4
 *                              Bit[5] - 0/1 connects CDDC2/3 to FDDC5
 *                              Bit[6] - 0/1 connects CDDC2/3 to FDDC6
 *                              Bit[7] - 0/1 connects CDDC2/3 to FDDC7
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_cddc2fddc_xbar_set(adi_ad9082_device_t *device, uint8_t cddc_fddc_xbar);

/**
 * @brief  Configure the rx data path cross-bar
 *
 * @param  device           Pointer to the device structure
 * @param  adc_cddc_xbar    Configure ADC to Coarse DDC Crossbar, @see adi_ad9082_adc_adc_to_cddc_xbar_e
 * @param  cddc_fddc_xbar   Configure Coarse to Fine DDC Crossbar
 *                              Bit[0] - 0/1 connects CDDC0/1 to FDDC0
 *                              Bit[1] - 0/1 connects CDDC0/1 to FDDC1
 *                              Bit[2] - 0/1 connects CDDC0/1 to FDDC2
 *                              Bit[3] - 0/1 connects CDDC0/1 to FDDC3
 *                              Bit[4] - 0/1 connects CDDC2/3 to FDDC4
 *                              Bit[5] - 0/1 connects CDDC2/3 to FDDC5
 *                              Bit[6] - 0/1 connects CDDC2/3 to FDDC6
 *                              Bit[7] - 0/1 connects CDDC2/3 to FDDC7
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_xbar_set(adi_ad9082_device_t *device, uint8_t adc_cddc_xbar, uint8_t cddc_fddc_xbar);

/**
 * @brief  Get the rx data path cross-bar
 *
 * @param  device           Pointer to the device structure
 * @param  adc_cddc_xbar    ADC to coarse DDC Crossbar
 * @param  cddc_fddc_xbar   Coarse to fine DDC Crossbar
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_xbar_get(adi_ad9082_device_t *device, uint8_t *adc_cddc_xbar, uint8_t *cddc_fddc_xbar);

/**
 * @brief  Configure the chip decimation ratio
 *
 * @param  device   Pointer to the device structure
 * @param  links    JESD links selection
 * @param  dcm      Value of total decimation
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_chip_dcm_ratio_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links, uint8_t dcm);

/**
 * @brief  Page the targeted coarse DDCs
 *
 * @param  device   Pointer to the device structure
 * @param  cddcs    Coarse DDCs selection
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_coarse_select_set(adi_ad9082_device_t *device, uint8_t cddcs);

/**
 * @brief  Configure the coarse DDC C2R and decimation setting
 *
 * @param  device   Pointer to the device structure
 * @param  cddcs    Mask index to the target coarse DDCs
 * @param  c2r_en   Complex to real enable
 * @param  dcm      Value of desired decimation for the coarse DDCs
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_coarse_config_set(adi_ad9082_device_t *device, uint8_t cddcs,
    uint8_t c2r_en, adi_ad9082_adc_coarse_ddc_dcm_e dcm);

/**
 * @brief  Configure the coarse DDC decimation
 *
 * @param  device   Pointer to the device structure
 * @param  cddcs    Mask index to the target coarse DDCs
 * @param  dcm      Value of desired decimation for the coarse DDCs
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_coarse_dcm_set(adi_ad9082_device_t *device, uint8_t cddcs,
    adi_ad9082_adc_coarse_ddc_dcm_e dcm);

/**
 * @brief  Configure the coarse DDC C2R (complex to real)
 *
 * @param  device   Pointer to the device structure
 * @param  cddcs    Mask index to the target coarse DDCs
 * @param  c2r_en   Complex to real enable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_coarse_c2r_set(adi_ad9082_device_t *device, uint8_t cddcs,
    uint8_t c2r_en);

/**
 * @brief  Configure the coarse DDC gain block
 *
 * @param  device   Pointer to the device structure
 * @param  cddcs    Mask index to the target coarse DDCs
 * @param  gain     Value of desired gain. 0: no gain. 1: 6dB gain
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_coarse_gain_set(adi_ad9082_device_t *device, uint8_t cddcs,
    uint8_t gain);

/**
 * @brief  Configure NCO frequency and modulus for the coarse DDCs
 *
 * @param  device     Pointer to the device structure
 * @param  cddcs      Mask index to the target coarse DDCs
 * @param  ftw        Value of frequency tuning word
 * @param  modulus_a  Value of modulus A word
 * @param  modulus_b  Value of modulus B word
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_coarse_nco_ftw_set(adi_ad9082_device_t *device, uint8_t cddcs,
    uint64_t ftw, uint64_t modulus_a, uint64_t modulus_b);

/**
 * @brief  Get NCO frequency and modulus for the coarse DDCs
 *
 * @param  device     Pointer to the device structure
 * @param  cddc       Mask index to the target coarse DDC
 * @param  ftw        Pointer of frequency tuning word
 * @param  modulus_a  Pointer of modulus A word
 * @param  modulus_b  Pointer of modulus B word
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_coarse_nco_ftw_get(adi_ad9082_device_t *device, uint8_t cddc,
    uint64_t *ftw, uint64_t *modulus_a, uint64_t *modulus_b);

/**
 * @brief  Configure NCO mode for the coarse DDCs
 *
 * @param  device     Pointer to the device structure
 * @param  cddcs      Mask index to the target coarse DDCs
 * @param  nco_mode   NCO mode selection
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_coarse_nco_mode_set(adi_ad9082_device_t *device, uint8_t cddcs,
    adi_ad9082_adc_nco_mode_e nco_mode);

/**
 * @brief  Enable NCO for the coarse DDCs
 *
 * @param  device     Pointer to the device structure
 * @param  cddcs      Mask index to the target coarse DDCs
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_coarse_nco_enable_set(adi_ad9082_device_t *device, uint8_t cddcs);

/**
 * @brief  Page the targeted fine DDCs
 *
 * @param  device    Pointer to the device structure
 * @param  fddcs     Fine DDCs selection
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_fine_select_set(adi_ad9082_device_t *device, uint8_t fddcs);

/**
 * @brief  Configure the fine DDC decimation setting
 *
 * @param  device   Pointer to the device structure
 * @param  fddcs    Mask index to the target fine DDCs
 * @param  c2r_en   Complex to real enable
 * @param  dcm      Value of desired decimation for the fine DDCs
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_fine_config_set(adi_ad9082_device_t *device, uint8_t fddcs,
    uint8_t c2r_en, adi_ad9082_adc_fine_ddc_dcm_e dcm);

/**
 * @brief  Configure NCO frequency and modulus for the fine DDCs
 *
 * @param  device     Pointer to the device structure
 * @param  fddcs      Mask index to the target fine DDCs
 * @param  dcm        Value of overall decimation (= fddc_dcm * cddc_dcm, or fddc_dcm * cddc_dcm / 2 if C2R enabled
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_fine_overall_dcm_set(adi_ad9082_device_t *device, uint8_t fddcs,
    uint8_t dcm);

/**
 * @brief  Configure the fine DDC gain block
 *
 * @param  device   Pointer to the device structure
 * @param  fddcs    Mask index to the target fine DDCs
 * @param  gain     Value of desired gain
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_fine_gain_set(adi_ad9082_device_t *device, uint8_t fddcs,
    uint8_t gain);

/**
 * @brief  Configure NCO frequency and modulus for the fine DDCs
 *
 * @param  device     Pointer to the device structure
 * @param  fddcs      Mask index to the target fine DDCs
 * @param  ftw        Value of frequency tuning word
 * @param  modulus_a  Value of modulus A word
 * @param  modulus_b  Value of modulus B word
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_fine_nco_ftw_set(adi_ad9082_device_t *device, uint8_t fddcs,
    uint64_t ftw, uint64_t modulus_a, uint64_t modulus_b);

/**
 * @brief  Get NCO frequency and modulus for the fine DDC
 *
 * @param  device     Pointer to the device structure
 * @param  fddc       Mask index to the target fine DDC
 * @param  ftw        Pointer of frequency tuning word
 * @param  modulus_a  Pointer of modulus A word
 * @param  modulus_b  Pointer of modulus B word
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_fine_nco_ftw_get(adi_ad9082_device_t *device, uint8_t fddc,
    uint64_t *ftw, uint64_t *modulus_a, uint64_t *modulus_b);

/**
 * @brief  Configure NCO mode for the fine DDCs
 *
 * @param  device     Pointer to the device structure
 * @param  fddcs      Mask index to the target fine DDCs
 * @param  nco_mode   NCO mode selection
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_fine_nco_mode_set(adi_ad9082_device_t *device, uint8_t fddcs,
    adi_ad9082_adc_nco_mode_e nco_mode);

/**
 * @brief  Enable NCO for the fine DDCs
 *
 * @param  device     Pointer to the device structure
 * @param  fddcs      Mask index to the target fine DDCs
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_ddc_fine_nco_enable_set(adi_ad9082_device_t *device, uint8_t fddcs);

/**
 * @brief  ADC configuration
 *
 * @param  device       Pointer to the device structure
 * @param  cddcs        Mask index to the target coarse DDCs
 * @param  fddcs        Mask index to the target fine DDCs
 * @param  cddc_shift   Coarse DDC NCO shift
 * @param  fddc_shift   Fine   DDC NCO shift
 * @param  cddc_dcm     Coarse DDC decimation value
 * @param  fddc_dcm     Fine   DDC decimation value
 * @param  cc2r_en      Coarse DDC complex to real enable
 * @param  fc2r_en      Fine   DDC complex to real enable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_config(adi_ad9082_device_t *device, uint8_t cddcs, uint8_t fddcs,
    int64_t cddc_shift[4], int64_t fddc_shift[8], uint8_t cddc_dcm[4], uint8_t fddc_dcm[8],
    uint8_t cc2r_en[4], uint8_t fc2r_en[8]);

/**
 * @brief  enable adc clock out driver
 *
 * @param  device     Pointer to the device structure
 * @param  enable     1:Enable, 0:Disable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_clk_out_enable_set(adi_ad9082_device_t *device, uint8_t enable);

/**
 * @brief  enable adc clock divider
 *
 * @param  device     Pointer to the device structure
 * @param  enable     1:Enable, 0:Disable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_clk_enable_set(adi_ad9082_device_t *device, uint8_t enable);

/**
 * @brief  configure adc clock divider and enable adc clk
 *
 * @param  device     Pointer to the device structure
 * @param  div        Divider setting
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_clk_div_set(adi_ad9082_device_t *device, uint8_t div);

/**
 * @brief  Set ADC Nyquist zone
 *
 * @param  device         Pointer to the device structure
 * @param  zone           AD9082_ADC_NYQUIST_ZONE_ODD / AD9082_ADC_NYQUIST_ZONE_EVEN
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_nyquist_zone_set(adi_ad9082_device_t *device, adi_ad9082_adc_nyquist_zone_e zone);

/**
 * @brief  Set ADC test mode
 *
 * @param  device         Pointer to the device structure
 * @param  tmode_i_type   I test mode type
 * @param  tmode_q_type   Q test mode type
 * @param  link           Target link
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_test_mode_config_set(adi_ad9082_device_t *device, adi_ad9082_tmode_type_e tmode_i_type,
    adi_ad9082_tmode_type_e tmode_q_type, adi_ad9082_jesd_link_select_e links);

/**
 * @brief  Set PFIR control page
 *
 * @param  device         Pointer to the device structure
 * @param  page           PFIR control page @see adi_ad9082_adc_pfir_ctl_page_e
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_pfir_ctl_page_set(adi_ad9082_device_t *device, uint8_t page);

/**
 * @brief  Set PFIR coefficient page
 *
 * @param  device         Pointer to the device structure
 * @param  page           PFIR coefficient page @see adi_ad9082_adc_pfir_coeff_page_e
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_pfir_coeff_page_set(adi_ad9082_device_t *device, uint8_t page);

/**
 * @brief  Set PFIR I-mode
 *
 * @param  device         Pointer to the device structure
 * @param  ctl_pages      PFIR control pages @see adi_ad9082_adc_pfir_ctl_page_e
 * @param  i_mode         PFIR i-mode @see adi_ad9082_adc_pfir_i_mode_e
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_pfir_i_mode_set(adi_ad9082_device_t *device, uint8_t ctl_pages, adi_ad9082_adc_pfir_i_mode_e i_mode);

/**
 * @brief  Set PFIR Q-mode
 *
 * @param  device         Pointer to the device structure
 * @param  ctl_pages      PFIR control pages @see adi_ad9082_adc_pfir_ctl_page_e
 * @param  q_mode         PFIR q-mode @see adi_ad9082_adc_pfir_q_mode_e
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_pfir_q_mode_set(adi_ad9082_device_t *device, uint8_t ctl_pages, adi_ad9082_adc_pfir_q_mode_e q_mode);

/**
 * @brief  Set PFIR I Gain
 *
 * @param  device         Pointer to the device structure
 * @param  ctl_pages      PFIR control pages @see adi_ad9082_adc_pfir_ctl_page_e
 * @param  ix_gain        PFIR Ix gain @see adi_ad9082_adc_pfir_gain_e
 * @param  iy_gain        PFIR Iy gain @see adi_ad9082_adc_pfir_gain_e
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_pfir_i_gain_set(adi_ad9082_device_t *device, uint8_t ctl_pages, adi_ad9082_adc_pfir_gain_e ix_gain, adi_ad9082_adc_pfir_gain_e iy_gain);

/**
 * @brief  Set PFIR Q Gain
 *
 * @param  device         Pointer to the device structure
 * @param  ctl_pages      PFIR control pages @see adi_ad9082_adc_pfir_ctl_page_e
 * @param  qx_gain        PFIR Qx gain @see adi_ad9082_adc_pfir_gain_e
 * @param  qy_gain        PFIR Qy gain @see adi_ad9082_adc_pfir_gain_e
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_pfir_q_gain_set(adi_ad9082_device_t *device, uint8_t ctl_pages, adi_ad9082_adc_pfir_gain_e qx_gain, adi_ad9082_adc_pfir_gain_e qy_gain);

/**
 * @brief  Set PFIR Delay for Half Complex Mode
 *
 * @param  device         Pointer to the device structure
 * @param  ctl_pages      PFIR control pages @see adi_ad9082_adc_pfir_ctl_page_e
 * @param  delay          Delay value (<= 0xff)
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_pfir_half_complex_delay_set(adi_ad9082_device_t *device, uint8_t ctl_pages, uint8_t delay);

/**
 * @brief  Set PFIR Delay for Half Complex Mode
 *
 * @param  device         Pointer to the device structure
 * @param  ctl_pages      PFIR control pages @see adi_ad9082_adc_pfir_ctl_page_e
 * @param  enable         Enable PFIR coefficients transfer
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_pfir_coeff_xfer_set(adi_ad9082_device_t *device, uint8_t ctl_pages, uint8_t enable);

/**
 * @brief  Set PFIR I Programmable Delay Line Setting For Image Cancellation Filter
 *
 * @param  device         Pointer to the device structure
 * @param  ctl_pages      PFIR control pages @see adi_ad9082_adc_pfir_ctl_page_e
 * @param  delay          Delay value (<= 0x7f)
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_pfir_hc_prog_delay_set(adi_ad9082_device_t *device, uint8_t coeff_pages, uint8_t delay);

/**
 * @brief  Set PFIR Quard Mode
 *
 * @param  device         Pointer to the device structure
 * @param  ctl_pages      PFIR control pages @see adi_ad9082_adc_pfir_ctl_page_e
 * @param  enable         Enable quad mode or not
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_pfir_quad_mode_set(adi_ad9082_device_t *device, uint8_t ctl_pages, uint8_t enable);

/**
 * @brief  Set PFIR Coefficients Load Selection
 *
 * @param  device         Pointer to the device structure
 * @param  ctl_pages      PFIR control pages @see adi_ad9082_adc_pfir_ctl_page_e
 * @param  sel            Load selection
 *                            bit 0: real_i load,       bit 1: real_q load
 *                            bit 2: real_cross_i load, bit 3: real_cross_q load
 *                            bit 4: complex load,      bit 5: coeff clear
 *                            bit 6: vle coeff,         bit 7: gpio config1
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_pfir_coeff_load_sel_set(adi_ad9082_device_t *device, uint8_t ctl_pages, uint8_t sel);

/**
 * @brief  Set PFIR Coefficient Page
 *
 * @param  device         Pointer to the device structure
 * @param  ctl_pages      PFIR control pages @see adi_ad9082_adc_pfir_ctl_page_e
 * @param  sel            Coefficient page selection
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_pfir_rd_coeff_page_sel_set(adi_ad9082_device_t *device, uint8_t ctl_pages, uint8_t sel);

/**
 * @brief  Set PFIR Coefficient
 *
 * @param  device         Pointer to the device structure
 * @param  ctl_pages      PFIR control pages @see adi_ad9082_adc_pfir_ctl_page_e
 * @param  index          Coefficient index (0~191)
 * @param  coeff          Coefficient value
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_pfir_coeff_set(adi_ad9082_device_t *device, uint8_t coeff_pages, uint8_t index, uint16_t coeff);

/**
 * @brief  Set PFIR Coefficient
 *
 * @param  device         Pointer to the device structure
 * @param  ctl_pages      PFIR control pages @see adi_ad9082_adc_pfir_ctl_page_e
 * @param  coeffs         Coefficient value array (size >= 192) pointer
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_adc_pfir_coeffs_set(adi_ad9082_device_t *device, uint8_t coeff_pages, uint16_t* coeffs);

/**
 * @brief  Select jesd rx link
 *
 * @param  device         Pointer to the device structure
 * @param  links          Target link
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_rx_link_select_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links);

/**
 * @brief  Enable or disable the descrambler
 *
 * @param  device     Pointer to the device structure
 * @param  links      Target link
 * @param  dsr_en     1:Enable, 0:Disable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_rx_descrambler_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t dsr_en);

/**
 * @brief  Enable or disable data invert on a particular lane for Rx
 *
 * @param  device          Pointer to the device structure
 * @param  links           Target link
 * @param  logical_lane    Logical lane number
 * @param  invert_en       1:Enable, 0:Disable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_rx_lane_invert_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t logical_lane, uint8_t invert_en);

/**
 * @brief  Configure the JESD Rx lane cross bar
 *
 * @param  device          Pointer to the device structure
 * @param  links           Target link
 * @param  physical_lane   Physical lane number
 * @param  logical_lane    Logical lane number
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_rx_lane_xbar_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t physical_lane, uint8_t logical_lane);

/**
 * @brief  Configure the Rx link settings
 *
 * @param  device     Pointer to the device structure
 * @param  links      Target link
 * @param  jesd_param l,f,k,m,s,n,np,hd,dscr,did,lid, etc.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_rx_link_config_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    adi_cms_jesd_param_t *jesd_param);

/**
 * @brief  Enable or disable the JESD link for Rx
 *
 * @param  device     Pointer to the device structure
 * @param  links      Target link
 * @param  link_en    1:Enable, 0:Disable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_rx_link_enable_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t link_en);

/**
 * @brief  JRX link bring up (setting up JESD PLL, etc.)
 *
 * @param  device     Pointer to the device structure
 * @param  links      Target link
 * @param  lanes      Target lanes to enable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_rx_bring_up(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t lanes);

/**
 * @brief  JRX sysref enable setting
 *
 * @param  device     Pointer to the device structure
 * @param  enable     1:Enable, 0:Disable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_rx_sysref_enable_set(adi_ad9082_device_t *device, uint8_t enable);

/**
 * @brief  Set LMFC delay
 *
 * @param  device Pointer to the device structure
 * @param  links  Target link
 * @param  delay  Phase adjustment in conv_clk cycles. Maximum value is k*s/ns.
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_rx_lmfc_delay_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint16_t delay);

/**
 * @brief  Set JRX SYNC# signal mode
 *
 * @param  device     Pointer to the device structure
 * @param  links      Target link
 * @param  sync_mode  0: '1', 1: sync# signal from link0, 2: sync# signal from link1, 3: ANDed sync# signal from link0 & link1
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_rx_sync_mode_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t sync_mode);

/**
* @brief  Read jesd jrx link configuration status
*
* @param  device        Pointer to the device structure
* @param  cfg_valid     Pointer to variable to store the jrx link status
*
* @return API_CMS_ERROR_OK                     API Completed Successfully
* @return <0                                   Failed. Check adi_cms_error_e for details.
*/
int32_t adi_ad9082_jesd_rx_config_status_get(adi_ad9082_device_t *device, uint8_t *cfg_valid);

/**
 * @brief  Get jrx link status
 *
 * @param  device     Pointer to the device structure
 * @param  links      Target link
 * @param  status     Pointer to link status of each lane
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_rx_link_status_get(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint16_t *status);

/**
 * @brief  Select jesd tx link
 *
 * @param  device     Pointer to the device structure
 * @param  links      Target link
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_link_select_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links);

/**
 * @brief  Configure the Tx link settings
 *
 * @param  device     Pointer to the device structure
 * @param  links      Target link select
 * @param  jesd_param l,f,k,m,s,n,np,hd,scr,did,bid
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_link_config_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    adi_cms_jesd_param_t *jesd_param);

/**
 * @brief  Enable or disable the scrambler
 *
 * @param  device     Pointer to the device structure
 * @param  links      Target link select
 * @param  scr_en     1:Enable, 0:Disable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_scrambler_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t scr_en);

/**
 * @brief  Startup serializer
 *
 * @param  device     Pointer to the device structure
 * @param  lanes      Active lanes
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_startup_ser(adi_ad9082_device_t *device, uint8_t lanes);

/**
 * @brief  Enable or disable data invert on a particular lane for Tx
 *
 * @param  device          Pointer to the device structure
 * @param  links           Target link select
 * @param  physical_lane   Physical lane number
 * @param  invert_en       1:Enable, 0:Disable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_lane_invert_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t physical_lane, uint8_t invert_en);

/**
 * @brief  Configure the JESD Tx lane cross bar
 *
 * @param  device          Pointer to the device structure
 * @param  links           Target link select
 * @param  physical_lane   Physical lane number
 * @param  logical_lane    Logical lane number
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_lane_xbar_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t physical_lane, uint8_t logical_lane);

/**
 * @brief  Select virtual converter
 *
 * @param  device          Pointer to the device structure
 * @param  links           Target link select
 * @param  conv_index      Converter select index
 * @param  val             Converter select value (virutal converter index)
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_conv_sel_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t conv_index, uint8_t val);

/**
 * @brief  Configure cross bar between coarse DDC and fine DDC
 *
 * @param  device          Pointer to the device structure
 * @param  links           Target link select
 * @param  converters      Converters having FBW output
 *                             Bit[0] - converter 0
 *                             Bit[1] - converter 1
 *                             ...
 *                             Bit[F] - converter F
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_fbw_sel_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint16_t converters);

/**
 * @brief  Configure chip output resolution
 *
 * @param  device          Pointer to the device structure
 * @param  links           Target link select
 * @param  resolution      Chip output resolution, @see adi_ad9082_chip_output_res_e
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_res_sel_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t resolution);

/**
 * @brief  Enable virtual converter test mode
 *
 * @param  device          Pointer to the device structure
 * @param  links           Target link select
 * @param  enable          Enable test mode, bit0 - virtual converter0, bit1 - virtual converter1, ...
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_conv_test_mode_enable_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint16_t enable);

/**
 * @brief  Configure the lid for each lane
 *
 * @param  device          Pointer to the device structure
 * @param  links           Target link select
 * @param  lane            lane index
 * @param  val             the val of lid
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_lid_cfg_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t lane, uint8_t val);

/**
 * @brief  Force JESD Tx links reset
 *
 * @param  device     Pointer to the device structure
 * @param  reset      1:Enable, 0:Disable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_link_reset(adi_ad9082_device_t *device, uint8_t reset);

/**
 * @brief  Enable or disable the JESD link for Tx
 *
 * @param  device     Pointer to the device structure
 * @param  links      Target link select
 * @param  link_en    1:Enable, 0:Disable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_link_enable_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t link_en);

/**
 * @brief  JTX link bring up
 *
 * @param  device     Pointer to the device structure
 * @param  links      Target link select
 * @param  lanes      Active lanes
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_bring_up(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t lanes);

/**
 * @brief  Get jtx link status
 *
 * @param  device       Pointer to the device structure
 * @param  links        Target link select
 * @param  status       Pointer to jtx status
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_link_status_get(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint16_t *status);

/**
 * @brief  Set JTX SYNC# signal mode
 *
 * @param  device     Pointer to the device structure
 * @param  links      Target link
 * @param  sync_mode  0 : sync0# as link sync source, 1: sync1# as link sync source
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_sync_mode_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t sync_mode);

/**
 * @brief  Start onshot sync
 *
 * @param  device       Pointer to the device structure
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_oneshot_sync(adi_ad9082_device_t *device);

/**
 * @brief  Run PRBS Test for JESD Receiver
 *
 * @param device         Pointer to the device reference handle.
 * @param prbs_pattern   PRBS pattern identifier,
 *                       R0: PRBS7, PRBS15, PRBS31
 *                       R1: PRBS7, PRBS9, PRBS15, PRBS31
 * @param time_sec       Seconds for PRBS test
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_rx_phy_prbs_test_start_stop(adi_ad9082_device_t *device,
    adi_cms_jesd_prbs_pattern_e prbs_pattern, uint32_t time_sec);

/**
 * @brief  Get PRBS test result for JRX
 *
 * @param device         Pointer to the device reference handle.
 * @param lanes          lane index (0~7)
 * @param prbs_rx_result @see adi_ad9082_prbs_test_t
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_rx_phy_prbs_test_result_get(adi_ad9082_device_t *device, uint8_t lane,
    adi_ad9082_prbs_test_t *prbs_rx_result);

/**
 * @brief  Run PRBS Test for JESD Receiver
 *
 * @param device         Pointer to the device reference handle.
 * @param prbs_pattern   PRBS pattern identifier, @see adi_cms_jesd_prbs_pattern_e
 *                       R0: PRBS7, PRBS15, PRBS31
 *                       R1: PRBS7, PRBS9, PRBS15, PRBS31
 * @param lanes          lane index (0~7)
 * @param prbs_rx_result @see adi_ad9082_prbs_test_t
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_rx_phy_prbs_test(adi_ad9082_device_t *device, adi_cms_jesd_prbs_pattern_e prbs_pattern,
    uint8_t lane, adi_ad9082_prbs_test_t *prbs_rx_result);

/**
 * @brief  Run Lane Loopback Test for JESD Transmitter
 *
 * @param device         Pointer to the device reference handle.
 * @param links          Target link
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_lane_loopback_test(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links);

/**
 * @brief  Run Checker Board Test for JESD Transmitter
 *
 * @param device         Pointer to the device reference handle.
 * @param links          Target link
 * @param data_source    0:sample, 1:phy, 2:scrambler input
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_checker_board_test(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t date_source);

/**
 * @brief  Run Word Toggle Test for JESD Transmitter
 *
 * @param device         Pointer to the device reference handle.
 * @param links          Target link
 * @param data_source    0:sample, 1:phy, 2:scrambler input
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_word_toggle_test(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t date_source);

/**
 * @brief  Run Ramp Pattern Test for JESD Transmitter
 *
 * @param device         Pointer to the device reference handle.
 * @param links          Target link
 * @param data_source    0:sample, 1:phy, 2:scrambler input
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_ramp_test(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t date_source);

/**
 * @brief  Run Repeated User Pattern Test for JESD Transmitter
 *
 * @param device         Pointer to the device reference handle.
 * @param links          Target link
 * @param data_source    0:sample, 1:phy, 2:scrambler input
 * @param data           user data
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_repeat_user_data_test(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t date_source, uint8_t data[9]);

/**
 * @brief  Run PRBS Test for JESD Transmitter
 *
 * @param device         Pointer to the device reference handle.
 * @param links          Target link
 * @param prbs_pattern   PRBS pattern identifier, @see adi_ad9082_jesd_link_select_e
 *                       PRBS7, PRBS15, PRBS31
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_phy_prbs_test(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    adi_cms_jesd_prbs_pattern_e prbs_pattern);

/**
 * @brief  Enable ILAS Test Mode (Repeated ILAS)
 *
 * @param device         Pointer to the device reference handle
 * @param links          Target link
 * @param enable         Test mode enable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_ilas_test_mode_enable_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t enable);

/**
 * @brief  Enable Continuous D21.5 Test Mode
 *
 * @param device         Pointer to the device reference handle
 * @param links          Target link
 * @param lane_id        Lane index (0~7)
 * @param enable         Test mode enable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_continuous_d215_enable_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t lane_id, uint8_t enable);

/**
 * @brief  Enable RPAT Test Mode
 *
 * @param device         Pointer to the device reference handle
 * @param links          Target link
 * @param lane_id        Lane index (0~7)
 * @param enable         Test mode enable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_rpat_enable_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t lane_id, uint8_t enable);

/**
 * @brief  Enable JSPAT Test Mode
 *
 * @param device         Pointer to the device reference handle
 * @param links          Target link
 * @param lane_id        Lane index (0~7)
 * @param enable         Test mode enable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_jspat_enable_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t lane_id, uint8_t enable);

/**
 * @brief  Enable JTSPAT Test Mode
 *
 * @param device         Pointer to the device reference handle
 * @param links          Target link
 * @param lane_id        Lane index (0~7)
 * @param enable         Test mode enable
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_tx_jtspat_enable_set(adi_ad9082_device_t *device, adi_ad9082_jesd_link_select_e links,
    uint8_t lane_id, uint8_t enable);

/**
 * @brief  Set loop back mode
 *
 * @param device         Pointer to the device reference handle.
 * @param mode           loop back mode (0/1/2/3/4)
 *
 * @return API_CMS_ERROR_OK                     API Completed Successfully
 * @return <0                                   Failed. Check adi_cms_error_e for details.
 */
int32_t adi_ad9082_jesd_loopback_mode_set(adi_ad9082_device_t *device, uint8_t mode);

#ifdef __cplusplus
}
#endif

#endif /* __ADI_AD9082_H__ */
/*! @} */
