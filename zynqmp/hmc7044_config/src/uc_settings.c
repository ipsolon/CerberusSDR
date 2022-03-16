/*!
 * @brief     Use Case Settings
 *
 * @copyright copyright(c) 2018 analog devices, inc. all rights reserved.
 *            This software is proprietary to Analog Devices, Inc. and its
 *            licensor. By using this software you agree to the terms of the
 *            associated analog devices software license agreement.
 */

/*!
 * @addtogroup __ADI_AD9082_APP__
 * @{
 */

/*============= I N C L U D E S ============*/
#include <stdio.h>
#include <unistd.h>
#include "adi_ad9082.h"

/*============= D A T A ====================*/
uint64_t clk_hz[][4] = {
    /*          dev_ref             fpga_ref            dac_clk              adc_clk  */
    { (uint64_t)122.88e6, (uint64_t)122.88e6, (uint64_t)5898.24e6, (uint64_t)2949.12e6 }, /* uc0,  NCO                         */
    { (uint64_t)122.88e6, (uint64_t)737.28e6, (uint64_t)5898.24e6, (uint64_t)2949.12e6 }, /* uc1,  B,     194:392,      14Gbps */
    { (uint64_t)122.88e6, (uint64_t)737.28e6, (uint64_t)8847.36e6, (uint64_t)2949.12e6 }, /* uc2,  B,     214:392,      14Gbps */
    { (uint64_t)122.88e6, (uint64_t)368.64e6, (uint64_t)5898.24e6, (uint64_t)2949.12e6 }, /* uc3,  B,     473:360 |360,  7Gbps */
    { (uint64_t)122.88e6, (uint64_t)368.64e6, (uint64_t)8847.36e6, (uint64_t)2949.12e6 }, /* uc4,  B,     440:360 |360,  7Gbps */
    { (uint64_t)384.00e6, (uint64_t)768.00e6, (uint64_t)6144.00e6, (uint64_t)3072.00e6 }, /* uc5,  B,     263:1088|411, 15Gbps, FBW+C2R */
    { (uint64_t)384.00e6, (uint64_t)768.00e6, (uint64_t)6144.00e6, (uint64_t)3072.00e6 }, /* uc6,  B,     258:411 |411, 15Gbps */
    { (uint64_t)384.00e6, (uint64_t)768.00e6, (uint64_t)6144.00e6, (uint64_t)3072.00e6 }, /* uc7,  B, 266|266:411 |411, 15Gbps */
    { (uint64_t)384.00e6, (uint64_t)768.00e6, (uint64_t)6144.00e6, (uint64_t)3072.00e6 }, /* uc8,  B,     263:1087|411, 15Gbps, FBW-C2R */
    { (uint64_t)122.88e6, (uint64_t)737.28e6, (uint64_t)5898.24e6, (uint64_t)2949.12e6 }, /* uc9,  B,     258:502,      14Gbps */
    { (uint64_t)122.88e6, (uint64_t)122.88e6, (uint64_t)5898.24e6, (uint64_t)1474.56e6 }, /* uc10, C,     378:226,       8Gbps */
    { (uint64_t)122.88e6, (uint64_t)245.76e6, (uint64_t)11796.48e6,(uint64_t)2949.12e6 }, /* uc11, C,     378:226,      16Gbps */
    { (uint64_t)122.88e6, (uint64_t)368.64e6, (uint64_t)11796.48e6,(uint64_t)2949.12e6 }, /* uc12, C,      91:234,      24Gbps */
    { (uint64_t)125e6,    (uint64_t)250e6,    (uint64_t)12000e6,   (uint64_t)4000e6    }, /* uc13, C,     378:227,      16Gbps, LoopBack */
    { (uint64_t)125e6,    (uint64_t)375e6,    (uint64_t)6000e6,    (uint64_t)3000e6    }, /* uc14, C,      88:252,      24Gbps */
};
uint8_t tx_dac_chan_xbar[][4] = {
    { AD9082_DAC_CH_0,  AD9082_DAC_CH_0,  AD9082_DAC_CH_0,  AD9082_DAC_CH_0 }, /* uc0 */
    { AD9082_DAC_CH_0,  AD9082_DAC_CH_1,  AD9082_DAC_CH_2,  AD9082_DAC_CH_3 }, /* uc1 */
    { AD9082_DAC_CH_0 | AD9082_DAC_CH_1,  AD9082_DAC_CH_2 | AD9082_DAC_CH_3,  AD9082_DAC_CH_4 | AD9082_DAC_CH_5,  AD9082_DAC_CH_6 | AD9082_DAC_CH_7 }, /* uc2 */
    { AD9082_DAC_CH_0,  AD9082_DAC_CH_1,  AD9082_DAC_CH_2,  AD9082_DAC_CH_3 }, /* uc3 */
    { AD9082_DAC_CH_0 | AD9082_DAC_CH_1,  AD9082_DAC_CH_2,  AD9082_DAC_CH_2,  AD9082_DAC_CH_3 }, /* uc4 */
    { AD9082_DAC_CH_0,  AD9082_DAC_CH_1,  AD9082_DAC_CH_2,  AD9082_DAC_CH_3 }, /* uc5 */
    { AD9082_DAC_CH_2,  AD9082_DAC_CH_0,  AD9082_DAC_CH_3,  AD9082_DAC_CH_1 }, /* uc6 */
    { AD9082_DAC_CH_1,  AD9082_DAC_CH_0,  AD9082_DAC_CH_3,  AD9082_DAC_CH_2 }, /* uc7 */
    { AD9082_DAC_CH_0,  AD9082_DAC_CH_1,  AD9082_DAC_CH_2,  AD9082_DAC_CH_3 }, /* uc8 */
    { AD9082_DAC_CH_0,  AD9082_DAC_CH_1,  AD9082_DAC_CH_2,  AD9082_DAC_CH_3 }, /* uc9 */
    { AD9082_DAC_CH_0,  AD9082_DAC_CH_1,  AD9082_DAC_CH_2,  AD9082_DAC_CH_3 }, /* uc10*/
    { AD9082_DAC_CH_0,  AD9082_DAC_CH_1,  AD9082_DAC_CH_2,  AD9082_DAC_CH_3 }, /* uc11*/
    { AD9082_DAC_CH_0 | AD9082_DAC_CH_1,  AD9082_DAC_CH_2 | AD9082_DAC_CH_3,  AD9082_DAC_CH_4 | AD9082_DAC_CH_5,  AD9082_DAC_CH_6 | AD9082_DAC_CH_7 }, /* uc12 */
    { AD9082_DAC_CH_0,  AD9082_DAC_CH_1,  AD9082_DAC_CH_2,  AD9082_DAC_CH_3 }, /* uc13*/
    { AD9082_DAC_CH_0 | AD9082_DAC_CH_1,  AD9082_DAC_CH_2 | AD9082_DAC_CH_3,  AD9082_DAC_CH_4 | AD9082_DAC_CH_5,  AD9082_DAC_CH_6 | AD9082_DAC_CH_7 }, /* uc14 */
};
int8_t  tx_chan_gain[][8] = {
    {  0, -12, -12,   0, -12, -12, -12, -12 }, /* uc0 */
    {  0,   0,   0,   0,   0,   0,   0,   0 }, /* uc1 */
    { -7,   0,   0,   0,   0,   0,   0,   0 }, /* uc2 */
    { -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9 }, /* uc3 */
    {-12, -12, -12, -12, -12, -12, -12, -12 }, /* uc4 */
    { -7,  -7,  -7,  -7,  -7,  -7,  -7,  -7 }, /* uc5 */
    { -7,  -7,  -7,  -7,  -7,  -7,  -7,  -7 }, /* uc6 */
    { -7,  -7,  -7,  -7,  -7,  -7,  -7,  -7 }, /* uc7 */
    { -7,  -7,  -7,  -7,  -7,  -7,  -7,  -7 }, /* uc8 */
    {  0,   0,   0,   0,   0,   0,   0,   0 }, /* uc9 */
    {  0,   0,   0,   0,   0,   0,   0,   0 }, /* uc10*/
    {  0,   0,   0,   0,   0,   0,   0,   0 }, /* uc11*/
    {  0,   0,   0,   0,   0,   0,   0,   0 }, /* uc12*/
    {  0,   0,   0,   0,   0,   0,   0,   0 }, /* uc13*/
    {  0,   0,   0,   0,   0,   0,   0,   0 }, /* uc14*/
};
int64_t tx_main_shift[][4] = {
    { 1000.00e6, 1000.00e6, 1000.00e6, 1000.00e6 }, /* uc0 */
    { 1842.50e6, 1842.50e6, 1842.50e6, 1842.50e6 }, /* uc1 */
    { 1991.25e6, 1991.25e6, 1991.25e6, 1991.25e6 }, /* uc2 */
    { 1842.50e6, 1842.50e6, 0,         0         }, /* uc3 */
    { 1991.25e6, 1991.25e6, 0,         0         }, /* uc4 */
    { 672.00e6,  0,         0,         0         }, /* uc5 */
    { 0,         396.00e6,  0,         396.00e6  }, /* uc6 */
    { 0,         396.00e6,  0,         396.00e6  }, /* uc7 */
    { 672.00e6,  0,         0,         0         }, /* uc8 */
    { 1000.00e6, 1000.00e6, 0,         0         }, /* uc9 */
    { 0,         0,         0,         0         }, /* uc10*/
    { 0,         0,         0,         0         }, /* uc11*/
    { 1000e6,    1000e6,    1000e6,    1000e6    }, /* uc12*/
    { 3000e6,    3000e6,    3000e6,    3000e6    }, /* uc13*/
    { 3000e6,    3000e6,    3000e6,    3000e6    }, /* uc14*/
};
int64_t tx_chan_shift[][8] = {
    { 100e6,     100e4,    100e6,     100e6,    200e6,     150e6,    200e6,     150e6    }, /* uc0 */
    { 0,         0,        0,         0,        0,         0,        0,         0        }, /* uc1 */
    { -148.75e6, 148.75e6, -148.75e6, 148.75e6, -148.75e6, 148.75e6, -148.75e6, 148.75e6 }, /* uc2 */
    { 0,         0,        0,         0,        0,         0,        0,         0        }, /* uc3 */
    { -148.75e6, 148.75e6, 0,         0,        0,         0,        0,         0        }, /* uc4 */
    { 0,         0,        0,         0,        0,         0,        0,         0        }, /* uc5 */
    { 0,         0,        0,         0,        0,         0,        0,         0        }, /* uc6 */
    { 0,         0,        0,         0,        0,         0,        0,         0        }, /* uc7 */
    { 0,         0,        0,         0,        0,         0,        0,         0        }, /* uc8 */
    { 0,         0,        0,         0,        0,         0,        0,         0        }, /* uc9 */
    { 0,         0,        0,         0,        0,         0,        0,         0        }, /* uc10*/
    { 0,         0,        0,         0,        0,         0,        0,         0        }, /* uc11*/
    { 0,         0,        0,         0,        0,         0,        0,         0        }, /* uc12*/
    { 0,         0,        0,         0,        0,         0,        0,         0        }, /* uc13*/
    { 0,         0,        0,         0,        0,         0,        0,         0        }, /* uc14*/
};
uint8_t tx_interp[][2] = {
    /* main, chan */
    {   8,    2   }, /* uc0 */
    {   4,    4   }, /* uc1 */
    {   6,    4   }, /* uc2 */
    {   4,    4   }, /* uc3 */
    {   6,    4   }, /* uc4 */
    {   4,    1   }, /* uc5 */
    {   4,    1   }, /* uc6 */
    {   4,    1   }, /* uc7 */
    {   4,    1   }, /* uc8 */
    {   4,    1   }, /* uc9 */
    {  12,    1   }, /* uc10*/
    {  12,    1   }, /* uc11*/
    {   8,    2   }, /* uc12*/
    {  12,    1   }, /* uc13*/
    {   4,    2   }, /* uc14*/
};
uint8_t rx_cddc_select = AD9082_ADC_CDDC_ALL; /* uc */
uint8_t rx_fddc_select[] = {
    AD9082_ADC_FDDC_0 | AD9082_ADC_FDDC_1 | AD9082_ADC_FDDC_4 | AD9082_ADC_FDDC_5,  /* uc0 */
    AD9082_ADC_FDDC_0 | AD9082_ADC_FDDC_1 | AD9082_ADC_FDDC_4 | AD9082_ADC_FDDC_5,  /* uc1 */
    AD9082_ADC_FDDC_0 | AD9082_ADC_FDDC_1 | AD9082_ADC_FDDC_4 | AD9082_ADC_FDDC_5,  /* uc2 */
    AD9082_ADC_FDDC_0 | AD9082_ADC_FDDC_1,  /* uc3 */
    AD9082_ADC_FDDC_0 | AD9082_ADC_FDDC_1,  /* uc4 */
    AD9082_ADC_FDDC_0 | AD9082_ADC_FDDC_1 | AD9082_ADC_FDDC_4,  /* uc5 */
    AD9082_ADC_FDDC_0 | AD9082_ADC_FDDC_1 | AD9082_ADC_FDDC_4 | AD9082_ADC_FDDC_5,  /* uc6 */
    AD9082_ADC_FDDC_0 | AD9082_ADC_FDDC_1 | AD9082_ADC_FDDC_4 | AD9082_ADC_FDDC_5,  /* uc7 */
    AD9082_ADC_FDDC_0 | AD9082_ADC_FDDC_1 | AD9082_ADC_FDDC_4,  /* uc8 */
    AD9082_ADC_FDDC_0 | AD9082_ADC_FDDC_1,  /* uc9 */
    AD9082_ADC_FDDC_0 | AD9082_ADC_FDDC_1 | AD9082_ADC_FDDC_4 | AD9082_ADC_FDDC_5,  /* uc10*/
    AD9082_ADC_FDDC_0 | AD9082_ADC_FDDC_1 | AD9082_ADC_FDDC_4 | AD9082_ADC_FDDC_5,  /* uc11*/
    AD9082_ADC_FDDC_ALL,  /* uc12*/
    AD9082_ADC_FDDC_0 | AD9082_ADC_FDDC_1 | AD9082_ADC_FDDC_4 | AD9082_ADC_FDDC_5,  /* uc13*/
    AD9082_ADC_FDDC_0 | AD9082_ADC_FDDC_1,  /* uc14*/
};
int64_t rx_cddc_shift[][4] = {
    { 0,        0,        0,      0     }, /* uc0 */
    { 1842.5e6, 1842.5e6, 350e6,  350e6 }, /* uc1 */
    { 1842.5e6, 1842.5e6, 350e6,  350e6 }, /* uc2 */
    { 1842.5e6, 350e6,    0,      0     }, /* uc3 */
    { 1842.5e6, 350e6,    0,      0     }, /* uc4 */
    { 396e6,    55e6,     768e6,  0     }, /* uc5 */
    { 396e6,    396e6,    396e6,  396e6 }, /* uc6 */
    { 396e6,    396e6,    396e6,  396e6 }, /* uc7 */
    { 396e6,    55e6,     0,      0     }, /* uc8 */
    { 0,        0,        0,      0     }, /* uc9 */
    { 366e6,    376e6,    386e6,  396e6 }, /* uc10*/
    { 366e6,    376e6,    386e6,  396e6 }, /* uc11*/
    { 1000e6,   1000e6,   1000e6, 1000e6}, /* uc12*/
    { 3000e6,   3000e6,   3000e6, 3000e6}, /* uc13*/
    { 0,        0,        0,      0     }, /* uc14*/
};
int64_t rx_fddc_shift[8] = { 0, 0, 0, 0, 0, 0, 0, 0 }; /* uc */
uint8_t rx_cddc_dcm[][4] = {
    { AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2 }, /* uc0 */
    { AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2 }, /* uc1 */
    { AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2 }, /* uc2 */
    { AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2 }, /* uc3 */
    { AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2 }, /* uc4 */
    { AD9082_CDDC_DCM_4, AD9082_CDDC_DCM_4, AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_4 }, /* uc5 */
    { AD9082_CDDC_DCM_4, AD9082_CDDC_DCM_4, AD9082_CDDC_DCM_4, AD9082_CDDC_DCM_4 }, /* uc6 */
    { AD9082_CDDC_DCM_4, AD9082_CDDC_DCM_4, AD9082_CDDC_DCM_4, AD9082_CDDC_DCM_4 }, /* uc7 */
    { AD9082_CDDC_DCM_4, AD9082_CDDC_DCM_4, AD9082_CDDC_DCM_1, AD9082_CDDC_DCM_4 }, /* uc8 */
    { AD9082_CDDC_DCM_1, AD9082_CDDC_DCM_1, AD9082_CDDC_DCM_1, AD9082_CDDC_DCM_1 }, /* uc9 */
    { AD9082_CDDC_DCM_3, AD9082_CDDC_DCM_3, AD9082_CDDC_DCM_3, AD9082_CDDC_DCM_3 }, /* uc10*/
    { AD9082_CDDC_DCM_3, AD9082_CDDC_DCM_3, AD9082_CDDC_DCM_3, AD9082_CDDC_DCM_3 }, /* uc11*/
    { AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2, AD9082_CDDC_DCM_2 }, /* uc12*/
    { AD9082_CDDC_DCM_4, AD9082_CDDC_DCM_4, AD9082_CDDC_DCM_4, AD9082_CDDC_DCM_4 }, /* uc13*/
    { AD9082_CDDC_DCM_1, AD9082_CDDC_DCM_1, AD9082_CDDC_DCM_1, AD9082_CDDC_DCM_1 }, /* uc14*/
};
uint8_t rx_fddc_dcm[][8] = {
    { AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0, AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0 }, /* uc0 */
    { AD9082_FDDC_DCM_4, AD9082_FDDC_DCM_4, 0, 0, AD9082_FDDC_DCM_4, AD9082_FDDC_DCM_4, 0, 0 }, /* uc1 */
    { AD9082_FDDC_DCM_4, AD9082_FDDC_DCM_4, 0, 0, AD9082_FDDC_DCM_4, AD9082_FDDC_DCM_4, 0, 0 }, /* uc2 */
    { AD9082_FDDC_DCM_4, AD9082_FDDC_DCM_4, 0, 0, AD9082_FDDC_DCM_4, AD9082_FDDC_DCM_4, 0, 0 }, /* uc3 */
    { AD9082_FDDC_DCM_4, AD9082_FDDC_DCM_4, 0, 0, AD9082_FDDC_DCM_4, AD9082_FDDC_DCM_4, 0, 0 }, /* uc4 */
    { AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0, AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0 }, /* uc5 */
    { AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0, AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0 }, /* uc6 */
    { AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0, AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0 }, /* uc7 */
    { AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0, AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0 }, /* uc8 */
    { AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0, AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0 }, /* uc9 */
    { AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0, AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0 }, /* uc10*/
    { AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0, AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0 }, /* uc11*/
    { AD9082_FDDC_DCM_2, AD9082_FDDC_DCM_2, AD9082_FDDC_DCM_2, AD9082_FDDC_DCM_2, AD9082_FDDC_DCM_2, AD9082_FDDC_DCM_2, AD9082_FDDC_DCM_2, AD9082_FDDC_DCM_2 }, /* uc12*/
    { AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0, AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0 }, /* uc13*/
    { AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0, AD9082_FDDC_DCM_1, AD9082_FDDC_DCM_1, 0, 0 }, /* uc14*/
};
uint8_t rx_chip_dcm[][2] = {
    /*L0, L1*/
    { 0,  0 }, /* uc0 */
    { 8,  0 }, /* uc1 */
    { 8,  0 }, /* uc2 */
    { 8,  8 }, /* uc3 */
    { 8,  8 }, /* uc4 */
    { 1,  4 }, /* uc5 */
    { 4,  4 }, /* uc6 */
    { 4,  4 }, /* uc7 */
    { 1,  4 }, /* uc8 */
    { 1,  0 }, /* uc9 */
    { 3,  0 }, /* uc10*/
    { 3,  0 }, /* uc11*/
    { 4,  0 }, /* uc12*/
    { 4,  0 }, /* uc13*/
    { 1,  0 }, /* uc14*/
};
uint8_t rx_cddc_c2r[][4] = {
    { 0, 0, 0, 0 }, /* uc0 */
    { 0, 0, 0, 0 }, /* uc1 */
    { 0, 0, 0, 0 }, /* uc2 */
    { 0, 0, 0, 0 }, /* uc3 */
    { 0, 0, 0, 0 }, /* uc4 */
    { 0, 0, 1, 0 }, /* uc5 */
    { 0, 0, 0, 0 }, /* uc6 */
    { 0, 0, 0, 0 }, /* uc7 */
    { 0, 0, 0, 0 }, /* uc8 */
    { 0, 0, 0, 0 }, /* uc9 */
    { 0, 0, 0, 0 }, /* uc10*/
    { 0, 0, 0, 0 }, /* uc11*/
    { 0, 0, 0, 0 }, /* uc12*/
    { 0, 0, 0, 0 }, /* uc13*/
    { 0, 0, 0, 0 }, /* uc14*/
};
uint8_t rx_fddc_c2r[8] = { 0, 0, 0, 0, 0, 0, 0, 0 }; /* uc */
uint8_t jtx_link0_converter_select[][16] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc0 */
    { AD9082_FDDC_0_I, AD9082_FDDC_0_Q, AD9082_FDDC_1_I, AD9082_FDDC_1_Q, AD9082_FDDC_4_I, AD9082_FDDC_4_Q, AD9082_FDDC_5_I, AD9082_FDDC_5_Q, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc1 */
    { AD9082_FDDC_0_I, AD9082_FDDC_0_Q, AD9082_FDDC_1_I, AD9082_FDDC_1_Q, AD9082_FDDC_4_I, AD9082_FDDC_4_Q, AD9082_FDDC_5_I, AD9082_FDDC_5_Q, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc2 */
    { AD9082_FDDC_0_I, AD9082_FDDC_0_Q, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc3 */
    { AD9082_FDDC_0_I, AD9082_FDDC_0_Q, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc4 */
    { AD9082_FDDC_4_I, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc5 */
    { AD9082_FDDC_0_I, AD9082_FDDC_0_Q, AD9082_FDDC_1_I, AD9082_FDDC_1_Q, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc6 */
    { AD9082_FDDC_0_I, AD9082_FDDC_0_Q, AD9082_FDDC_1_I, AD9082_FDDC_1_Q, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc7 */
    { AD9082_FDDC_4_I, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc8 */
    { AD9082_FDDC_0_I, AD9082_FDDC_1_I, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc9 */
    { AD9082_FDDC_0_I, AD9082_FDDC_0_Q, AD9082_FDDC_1_I, AD9082_FDDC_1_Q, AD9082_FDDC_4_I, AD9082_FDDC_4_Q, AD9082_FDDC_5_I, AD9082_FDDC_5_Q, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc10*/
    { AD9082_FDDC_0_I, AD9082_FDDC_0_Q, AD9082_FDDC_1_I, AD9082_FDDC_1_Q, AD9082_FDDC_4_I, AD9082_FDDC_4_Q, AD9082_FDDC_5_I, AD9082_FDDC_5_Q, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc11*/
    { AD9082_FDDC_0_I, AD9082_FDDC_0_Q, AD9082_FDDC_1_I, AD9082_FDDC_1_Q, AD9082_FDDC_2_I, AD9082_FDDC_2_Q, AD9082_FDDC_3_I, AD9082_FDDC_3_Q, AD9082_FDDC_4_I, AD9082_FDDC_4_Q, AD9082_FDDC_5_I, AD9082_FDDC_5_Q, AD9082_FDDC_6_I, AD9082_FDDC_6_Q, AD9082_FDDC_7_I, AD9082_FDDC_7_Q }, /* uc12*/
    { AD9082_FDDC_0_I, AD9082_FDDC_0_Q, AD9082_FDDC_1_I, AD9082_FDDC_1_Q, AD9082_FDDC_4_I, AD9082_FDDC_4_Q, AD9082_FDDC_5_I, AD9082_FDDC_5_Q, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc13*/
    { AD9082_FDDC_0_I, AD9082_FDDC_0_Q, AD9082_FDDC_1_I, AD9082_FDDC_1_Q, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc14*/
};
uint8_t jtx_link1_converter_select[][16] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc0 */
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc1 */
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc2 */
    { AD9082_FDDC_1_I, AD9082_FDDC_1_Q, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc3 */
    { AD9082_FDDC_1_I, AD9082_FDDC_1_Q, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc4 */
    { AD9082_FDDC_0_I, AD9082_FDDC_0_Q, AD9082_FDDC_1_I, AD9082_FDDC_1_Q, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc5 */
    { AD9082_FDDC_4_I, AD9082_FDDC_4_Q, AD9082_FDDC_5_I, AD9082_FDDC_5_Q, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc6 */
    { AD9082_FDDC_4_I, AD9082_FDDC_4_Q, AD9082_FDDC_5_I, AD9082_FDDC_5_Q, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc7 */
    { AD9082_FDDC_0_I, AD9082_FDDC_0_Q, AD9082_FDDC_1_I, AD9082_FDDC_1_Q, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc8 */
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc9 */
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc10*/
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc11*/
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc12*/
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc13*/
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* uc14*/
};
uint8_t jrx_link0_logiclane_mapping[8]        = { 0, 1, 2, 3, 4, 5, 6, 7 }; /* uc */
uint8_t jrx_link1_logiclane_mapping[8]        = { 4, 5, 6, 7, 0, 1, 2, 3 }; /* uc */
uint8_t jtx_link0_logiclane_mapping_pe_brd[8] = { 0, 1, 2, 3, 4, 5, 6, 7 }; /* uc */
uint8_t jtx_link1_logiclane_mapping_pe_brd[8] = { 4, 5, 6, 7, 0, 1, 2, 3 }; /* uc */
uint8_t jtx_link0_logiclane_mapping_ce_brd[8] = { 6, 4, 3, 2, 1, 0, 7, 5 }; /* uc */
uint8_t jtx_link1_logiclane_mapping_ce_brd[8] = { 2, 0, 7, 7, 7, 7, 3, 1 }; /* uc */
adi_cms_jesd_param_t jrx_param[] = {
      /*L   F   M   S   HD  K    N    N'   CF  CS DID BID LID  SC SCR Dual V  Mode */
      { 4,  4,  8,  1,  0,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  2,  16 }, /* uc0 : nco test     */
      { 4,  4,  8,  1,  0,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  1,  9, }, /* uc1 : txmode = 194 */
      { 8,  4,  16, 1,  0,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  1,  16 }, /* uc2 : txmode = 214 */
      { 4,  2,  4,  1,  0,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  1,  10 }, /* uc3 : txmode = 437 */
      { 4,  2,  4,  1,  0,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  1,  10 }, /* uc4 : txmode = 440 */
      { 4,  1,  2,  1,  0,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  1,  62 }, /* uc5 : txmode = 263 */
      { 8,  1,  4,  1,  0,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  1,  17 }, /* uc6 : txmode = 258 */
      { 4,  1,  2,  1,  0,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  1,  1,  62 }, /* uc7 : txmode = 266 */
      { 4,  1,  2,  1,  0,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  1,  62 }, /* uc8 : txmode = 263 */
      { 8,  1,  4,  1,  0,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  1,  17 }, /* uc9 : txmode = 258 */
      { 8,  2,  8,  1,  0,  128, 16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  2,  15 }, /* uc10: txmode = 378 */
      { 8,  2,  8,  1,  0,  128, 16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  2,  15 }, /* uc11: txmode = 378 */
      { 8,  4,  16, 1,  0,  64,  16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  2,  16 }, /* uc12: txmode = 91  */
      { 8,  2,  8,  1,  0,  128, 16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  2,  15 }, /* uc13: txmode = 378 */
      { 8,  4,  16, 1,  0,  64,  16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  2,  16 }, /* uc14: txmode = 88 */
};
adi_cms_jesd_param_t jtx_param[][2] = {
      /*L   F   M   S   HD  K    N    N'   CF  CS DID BID LID  SC SCR Dual V  Mode C2R ModeS */
    { { 0,  0,  0,  0,  0,  0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,  0 } }, /* uc0 : nco test     */
    { { 4,  4,  8,  1,  1,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  1,  10,  0,  0 } }, /* uc1 : rxmode = 392 */
    { { 4,  4,  8,  1,  1,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  1,  10,  0,  0 } }, /* uc2 : rxmode = 392 */
    { { 2,  2,  2,  1,  1,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  1,  1,  7,   0,  0 },   /* uc3 : rxmode = 360/360 */
      { 2,  2,  2,  1,  1,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  1,  1,  7,   0,  0 } },
    { { 2,  2,  2,  1,  1,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  1,  1,  7,   0,  0 },   /* uc4 : rxmode = 360/360 */
      { 2,  2,  2,  1,  1,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  1,  1,  7,   0,  0 } },
    { { 4,  1,  1,  2,  1,  32,  12,  16,  0,  0,  0,  0,  0,  0,  1,  1,  1,  13,  1,  0 },   /* uc5 : rxmode = 1088/411*/
      { 4,  2,  4,  1,  1,  32,  12,  16,  0,  0,  0,  0,  0,  0,  1,  1,  1,  11,  0,  0 } },
    { { 4,  2,  4,  1,  1,  32,  12,  16,  0,  0,  0,  0,  0,  0,  1,  1,  1,  11,  0,  0 },   /* uc6 : rxmode = 411/411 */
      { 4,  2,  4,  1,  1,  32,  12,  16,  0,  0,  0,  0,  0,  0,  1,  1,  1,  11,  0,  0 } },
    { { 4,  2,  4,  1,  1,  32,  12,  16,  0,  0,  0,  0,  0,  0,  1,  1,  1,  11,  0,  0 },   /* uc7 : rxmode = 411/411 */
      { 4,  2,  4,  1,  1,  32,  12,  16,  0,  0,  0,  0,  0,  0,  1,  1,  1,  11,  0,  0 } },
    { { 4,  1,  1,  2,  1,  32,  12,  16,  0,  0,  0,  0,  0,  0,  1,  1,  1,  13,  1,  0 },   /* uc8 : rxmode = 1087/411*/
      { 4,  2,  4,  1,  1,  32,  12,  16,  0,  0,  0,  0,  0,  0,  1,  1,  1,  11,  0,  0 } },
    { { 8,  1,  2,  2,  1,  32,  16,  16,  0,  0,  0,  0,  0,  0,  1,  0,  1,  19,  0,  0 } }, /* uc9 : rxmode = 502 */
    { { 8,  2,  8,  1,  0,  128, 12,  16,  0,  0,  0,  0,  0,  0,  1,  0,  2,  16,  0,  0 } }, /* uc10: rxmode = 226 */
    { { 8,  2,  8,  1,  0,  128, 12,  16,  0,  0,  0,  0,  0,  0,  1,  0,  2,  16,  0,  0 } }, /* uc11: rxmode = 226 */
    { { 8,  4,  16, 1,  0,  64,  12,  16,  0,  0,  0,  0,  0,  0,  1,  0,  2,  17,  0,  0 } }, /* uc12: rxmode = 234 */
    { { 8,  2,  8,  1,  0,  128, 12,  16,  0,  0,  0,  0,  0,  0,  1,  0,  2,  16,  0,  0 } }, /* uc13: rxmode = 227 */
    { { 8,  1,  4,  1,  0,  256, 12,  16,  0,  0,  0,  0,  0,  0,  1,  0,  2,  18,  0,  0 } }, /* uc14: rxmode = 252 */
};
