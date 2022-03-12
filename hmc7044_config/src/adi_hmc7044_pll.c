/*!
 * @brief     DUAL PLL Clock Multiplier Support API implementation
 *
 * @copyright copyright(c) 2018 analog devices, inc. all rights reserved.
 *            This software is proprietary to Analog Devices, Inc. and its
 *            licensor. By using this software you agree to the terms of the
 *            associated analog devices software license agreement.
 */

/*!
 * @addtogroup __HMC7044_PLL_API__
 * @{
 */

/*============= I N C L U D E S ============*/
#include <stdlib.h>
#include "adi_utils.h"
#include "adi_hmc7044.h"
#include "hmc7044_hal.h"
#include "hmc7044_reg.h"

/*============= D E F I N E S ==============*/
uint64_t gcd(uint64_t value1, uint64_t value2);
uint64_t lcm(uint64_t value1, uint64_t value2);

/*============= C O D E ====================*/
int32_t adi_hmc7044_input_reference_set(adi_hmc7044_device_t *device,
        uint8_t clk_in, uint8_t config, uint8_t enable)
{
    int32_t err;
    uint16_t reg_addr;
    if (device == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_HANDLE_PTR;
    }
    if (clk_in >= HMC7044_NOF_CLK_IN || (enable > 1)) {
        return API_CMS_ERROR_INVALID_PARAM;
    }
    if (((config & IPBUFFER_HIGH_Z_MODE_EN)     && (config & IPBUFFER_AC_COUPLED_MODE_EN)) ||
        ((config & IPBUFFER_HIGH_Z_MODE_EN)     && (config & IPBUFFER_LVPECL_MODE_EN)) ||
        ((config & IPBUFFER_AC_COUPLED_MODE_EN) && (config & IPBUFFER_LVPECL_MODE_EN)) ||
        ((config > IPBUFFER_CONFIG_MAX))) {
        return API_CMS_ERROR_INVALID_PARAM;
    }

    reg_addr = ((clk_in * HMC7044_CLK_IP_BUFF_OFFSET) + HMC7044_CLK_IP_BUFF_BASE_REG);
    err = adi_hmc7044_device_spi_register_set(device, reg_addr, ((config <<1) | (enable)));
    if (err != API_CMS_ERROR_OK) {
        return err;
    }

    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_input_reference_priority_set(adi_hmc7044_device_t *device,
        uint8_t priority[4], uint8_t nof_ref)
{
    int32_t err;
    uint8_t i;
    uint8_t reg_val = 0x0;
    if (device == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_HANDLE_PTR;
    }
    if ((priority == ADI_INVALID_POINTER) ||
        (nof_ref > HMC7044_NOF_CLK_IN) ||
        (nof_ref < 1)) {
        return API_CMS_ERROR_INVALID_PARAM;
    }
    for (i=0; i<HMC7044_NOF_CLK_IN; i++) {
        if (i < nof_ref) {
            reg_val |= priority[i] << (2*i);
        } else {
            reg_val |= priority[nof_ref-1] << (2*i);
        }
    }
    err = adi_hmc7044_device_spi_register_set(device, HMC7044_CLK_IP_PRIORITY_REG, reg_val);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }

    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_input_reference_los_config_set(adi_hmc7044_device_t *device,
        uint8_t timer_cycles, uint8_t prescaler_bypass, uint8_t vcxo_prescaler_en)
{
    int32_t err;
    uint8_t reg_val = 0x0;
    if (device == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_HANDLE_PTR;
    }
    if (timer_cycles > HMC7044_PLL1_LOS_VALID_TIMER(ADI_UTILS_ALL)) {
        return API_CMS_ERROR_INVALID_PARAM;
    }
    if ((prescaler_bypass > 1) || (vcxo_prescaler_en > 1)) {
        return API_CMS_ERROR_INVALID_PARAM;
    }
    err = adi_hmc7044_device_spi_register_set(device, HMC7044_PLL1_LOS_TIMER_CTRL_REG, timer_cycles);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }
    reg_val |= prescaler_bypass  ? HMC7044_LOS_INPUT_PRESCALER_BYPASS : 0x0;
    reg_val |= vcxo_prescaler_en ? HMC7044_LOS_VCXO_PRESCALER_EN : 0x0;
    err = adi_hmc7044_device_spi_register_set(device, HMC7044_PLL1_LOS_MODE_REG, reg_val);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }

    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_input_reference_prescaler_config_set(adi_hmc7044_device_t *device,
        uint8_t clk_in, uint8_t lcm_div)
{
    int32_t err;
    uint8_t reg_addr;
    if (device == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_HANDLE_PTR;
    }
    if ((clk_in >= HMC7044_NOF_CLK_IN) || (lcm_div < 1)) {
        return API_CMS_ERROR_INVALID_PARAM;
    }
    reg_addr = (clk_in * HMC7044_CLKINX_PRESCALER_OFFSET) + HMC7044_CLKINX_PRESCALER_BASE_REG;
    err = adi_hmc7044_device_spi_register_set(device, reg_addr, lcm_div);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }

    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_input_reference_oscin_prescaler_config_set(adi_hmc7044_device_t *device, uint8_t lcm_div)
{
    int32_t err;

    if (device == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_HANDLE_PTR;
    }
    if (lcm_div < 1) {
        return API_CMS_ERROR_INVALID_PARAM;
    }
    err = adi_hmc7044_device_spi_register_set(device, HMC7044_OSCIN_PRESCALER_REG, lcm_div);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }

    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_pll1_config_set(adi_hmc7044_device_t *device, uint16_t r_div, uint16_t n_div)
{
    int32_t err;

    if (device == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_HANDLE_PTR;
    }

    if ((r_div < 1) || (n_div < 1 ))  {
        return API_CMS_ERROR_INVALID_PARAM;
    }

    err = adi_hmc7044_device_spi_register_set(device, HMC7044_PLL1_R_DIV_LSB_REG, ((uint8_t) (r_div & 0xFF)));
    if (err != API_CMS_ERROR_OK) {
        return err;
    }
    err = adi_hmc7044_device_spi_register_set(device, HMC7044_PLL1_R_DIV_MSB_REG, ((uint8_t) ((r_div >>8) & 0xFF)));
    if (err != API_CMS_ERROR_OK) {
        return err;
    }
    err = adi_hmc7044_device_spi_register_set(device, HMC7044_PLL1_N_DIV_LSB_REG, ((uint8_t) (n_div & 0xFF)));
    if (err != API_CMS_ERROR_OK) {
        return err;
    }
    err = adi_hmc7044_device_spi_register_set(device, HMC7044_PLL1_N_DIV_MSB_REG, ((uint8_t) ((n_div >>8) & 0xFF)));
    if (err != API_CMS_ERROR_OK) {
        return err;
    }

    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_pll2_config_set(adi_hmc7044_device_t *device, uint8_t freq_dbl_en, uint16_t r_div, uint16_t n_div)
{
    int32_t err;
    uint8_t reg_val = 0x0;

    if (device == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_HANDLE_PTR;
    }
    if ((r_div < 1) || (n_div < 1) || (r_div > HMC7044_PLL2_R_DIV_MAX ))  {
        return API_CMS_ERROR_INVALID_PARAM;
    }
    if (freq_dbl_en > 1)  {
        return API_CMS_ERROR_INVALID_PARAM;
    }
    err = adi_hmc7044_device_spi_register_set(device, HMC7044_PLL2_R_DIV_LSB_REG, ((uint8_t) (r_div & 0xFF)));
    if (err != API_CMS_ERROR_OK) {
        return err;
    }
    err = adi_hmc7044_device_spi_register_set(device, HMC7044_PLL2_R_DIV_MSB_REG, ((uint8_t) ((r_div >>8) & 0xFF)));
    if (err != API_CMS_ERROR_OK) {
        return err;
    }
    err = adi_hmc7044_device_spi_register_set(device, HMC7044_PLL2_N_DIV_LSB_REG, ((uint8_t) (n_div & 0xFF)));
    if (err != API_CMS_ERROR_OK) {
        return err;
    }
    err = adi_hmc7044_device_spi_register_set(device, HMC7044_PLL2_N_DIV_MSB_REG, ((uint8_t) ((n_div >>8) & 0xFF)));
    if (err != API_CMS_ERROR_OK) {
        return err;
    }
    reg_val = freq_dbl_en ? HMC7044_PLL2_FREQ_DOUBLER_EN : 0x0;
    err = adi_hmc7044_device_spi_register_set(device, HMC7044_PLL2_FREQ_DOUBLER_REG, reg_val);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }

    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_device_pll_lock_status_get(adi_hmc7044_device_t *device, uint8_t *status)
{
	int32_t err;
	if (err = adi_hmc7044_device_spi_register_get(device, 0x7D, status), err != API_CMS_ERROR_OK)
		return err;

	if ((*status & 0x01) == 0) {
		return API_CMS_ERROR_PLL_NOT_LOCKED;
	}
	return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_reg_update(adi_hmc7044_device_t *device)
{
    int32_t err;

    hmc7044_sw_delay_us(device, 1000);
    err = adi_hmc7044_device_spi_register_set(device, HMC7044_GLOBAL_REQUEST_MODE_CTRL_REG, 0x62);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }
    hmc7044_sw_delay_us(device, 1000);
    err = adi_hmc7044_device_spi_register_set(device, HMC7044_GLOBAL_REQUEST_MODE_CTRL_REG, 0x60);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }

    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_vco_enable_set(adi_hmc7044_device_t *device, uint8_t enable)
{
    int32_t err;

    if (enable == 0) {
        err =  adi_hmc7044_device_spi_register_set(device, HMC7044_GLOBAL_ENABLE_CTRL_REG, 0x37);
        if (err != API_CMS_ERROR_OK) {
            return err;
        }
        return API_CMS_ERROR_OK;
    }

    /* set vco high */
    err =  adi_hmc7044_device_spi_register_set(device, HMC7044_GLOBAL_ENABLE_CTRL_REG, 0x2f);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }

    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_distribution_clk_config(adi_hmc7044_device_t *device, uint64_t ref_clk_freq_hz,
        uint64_t pfd1_freq_hz, uint64_t dist_freq_hz, uint64_t pfd2_freq_hz)
{
    int32_t  err;
    uint64_t R1, N1, N2, R2, Ra;

    if (ref_clk_freq_hz > 800e6 || ref_clk_freq_hz < 0.00015e6) {
        return API_CMS_ERROR_INVALID_PARAM;
    }
    if (dist_freq_hz == 0 || pfd1_freq_hz == 0) {
        return API_CMS_ERROR_INVALID_PARAM;
    }

    if (ref_clk_freq_hz % (pfd1_freq_hz * 4) == 0) {
        Ra = ref_clk_freq_hz / pfd1_freq_hz / 4;
        if (Ra > 65535) {
            return API_CMS_ERROR_ERROR;
        }
    } else {
        return API_CMS_ERROR_INVALID_PARAM;
    }

    R1 = ref_clk_freq_hz / pfd1_freq_hz / 4;
    N2 = dist_freq_hz / pfd2_freq_hz;
    N1 = 245.76e6 / pfd1_freq_hz / 2;
    R2 = 2 * 122.88e6 / pfd2_freq_hz;

    err = adi_hmc7044_pll1_config_set(device, R1, N1);
    if ( err != API_CMS_ERROR_OK) {
        return err;
    }
	if (err = adi_hmc7044_gpi_config_set(device, 0, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpi_config_set(device, 1, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpi_config_set(device, 2, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpi_config_set(device, 3, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpo_config_set(device, 0, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpo_config_set(device, 1, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpo_config_set(device, 2, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpo_config_set(device, 3, 0), err != API_CMS_ERROR_OK)
		return err;
    err = adi_hmc7044_pll2_config_set(device, 0x0, R2, N2);
    if (err!= API_CMS_ERROR_OK) {
        return err;
    }

    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_clk_config(adi_hmc7044_device_t *device, adi_hmc7044_clk_in_e ref_ch, uint8_t ref_priority[4], uint64_t ref_clk_freq_hz, uint64_t fvcxo_clk_freq_hz, uint16_t output_ch, uint64_t output_clk_freq_hz[14])
{
	int32_t err;
    uint64_t flcm_clk_hz, pfd1_clk_hz, pfd2_clk_hz, vcxo_prescaler, pll2ref_clk_hz, pfd2_lcm_hz, pfd2_gcd_hz,fvco_clk_hz = 2949.12e6;
	uint64_t R1, N1, N2, R2, output_chan_divider;
	uint64_t i = 0;

	/*range check*/
	if (device == ADI_INVALID_POINTER) {
		return API_CMS_ERROR_INVALID_HANDLE_PTR;
	}

	if (ref_ch > HMC7044_CLK_IN_ALL) {
		return API_CMS_ERROR_INVALID_HANDLE_PTR;
	}

	if ((ref_clk_freq_hz > HMC7044_REF_CLK_FREQ_HZ_MAX || ref_clk_freq_hz< HMC7044_REF_CLK_FREQ_HZ_MIN)) {
		return API_CMS_ERROR_INVALID_PARAM;
	}

	if (fvcxo_clk_freq_hz < HMC7044_VCXO_CLK_FREQ_HZ_MIN || fvcxo_clk_freq_hz > HMC7044_VCXO_CLK_FREQ_HZ_MAX) {
		return API_CMS_ERROR_INVALID_PARAM;
	}

	for (i = 0; i < HMC7044_NOF_OP_CH; i++) {
		if (output_clk_freq_hz[i]) {
			uint16_t opchan = 1 << i;
			if ((output_ch & opchan) != opchan) {
				return API_CMS_ERROR_INVALID_PARAM;
			}
		}
	}

	/*enable clkin*/
	if (err = adi_hmc7044_input_reference_set(device, 0, IPBUFFER_INTERNAL_100_OHM_EN | IPBUFFER_AC_COUPLED_MODE_EN, (ref_ch & HMC7044_CLK_IN_0)), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_set(device, 1, IPBUFFER_INTERNAL_100_OHM_EN | IPBUFFER_AC_COUPLED_MODE_EN, (ref_ch & HMC7044_CLK_IN_1) >> 1), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_set(device, 2, IPBUFFER_INTERNAL_100_OHM_EN | IPBUFFER_AC_COUPLED_MODE_EN, (ref_ch & HMC7044_CLK_IN_2) >> 2), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_set(device, 3, IPBUFFER_INTERNAL_100_OHM_EN | IPBUFFER_AC_COUPLED_MODE_EN, (ref_ch & HMC7044_CLK_IN_3) >> 3), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_priority_set(device, ref_priority, 4), err != API_CMS_ERROR_OK)
		return err;

	/*calculate fLCM, typical range to be 30~40 MHz*/
	flcm_clk_hz = ref_clk_freq_hz;

	/*scale flcm to 30-40 range*/
	if (ref_clk_freq_hz > HMC7044_PLL1REF_CLK_FREQ_HZ_MAX || ref_clk_freq_hz < HMC7044_PLL1REF_CLK_FREQ_HZ_MIN) {
		uint8_t div = ref_clk_freq_hz / HMC7044_PLL1REF_CLK_FREQ_HZ_MIN;
		flcm_clk_hz = ref_clk_freq_hz / div;
	}

	/*calculate vcxo prescaler*/
	if (fvcxo_clk_freq_hz % flcm_clk_hz != 0) {
		return API_CMS_ERROR_ERROR;
	}
	vcxo_prescaler = fvcxo_clk_freq_hz / flcm_clk_hz;

	if (err = adi_hmc7044_input_reference_los_config_set(device, 7, 0, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_prescaler_config_set(device, 0, vcxo_prescaler), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_prescaler_config_set(device, 1, vcxo_prescaler), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_prescaler_config_set(device, 2, vcxo_prescaler), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_prescaler_config_set(device, 3, vcxo_prescaler), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_oscin_prescaler_config_set(device, vcxo_prescaler), err != API_CMS_ERROR_OK)
		return err;

	/*calculate fPFD1*/
	pfd1_clk_hz = gcd(flcm_clk_hz, fvcxo_clk_freq_hz);
	if (fvcxo_clk_freq_hz / 65535 > pfd1_clk_hz) {
		return API_CMS_ERROR_ERROR;
	}

	/* calculate pll2ref*/
	pll2ref_clk_hz = fvcxo_clk_freq_hz <= HMC7044_PLL2REF_CLK_DB_FREQ_HZ_MAX ? 2 * fvcxo_clk_freq_hz : fvcxo_clk_freq_hz;

	/*calculate fvco*/
	pfd2_gcd_hz = pll2ref_clk_hz;
	for (i = 0; i < HMC7044_NOF_OP_CH; i++) {
		if (output_clk_freq_hz[i]) {
			pfd2_gcd_hz = gcd(pfd2_gcd_hz, output_clk_freq_hz[i]);
		}
	}


	pfd2_lcm_hz = pfd2_gcd_hz;
	for (i = 0; i < HMC7044_NOF_OP_CH; i++) {
		if (output_clk_freq_hz[i]) {
			pfd2_lcm_hz = lcm(pfd2_lcm_hz, output_clk_freq_hz[i]);
		}
	}

	uint64_t  fdist;
	for (uint64_t k = 0; k < HMC7044_PLL2_R_DIV_MAX; k++) {
		fdist = k * pfd2_lcm_hz;
		if (fdist > HMC7044_VCO_CLK_FREQ_HZ_MIN && fdist < HMC7044_VCO_CLK_FREQ_HZ_MAX) {
			/*check output divider, should be 1,3,5 or even numbers*/
			for (i = 0; i < HMC7044_NOF_OP_CH; i++) {
				if (output_clk_freq_hz[i]) {
					output_chan_divider = fdist / output_clk_freq_hz[i];
					if (output_chan_divider % 2 != 0) {
						if (output_chan_divider != 1 || output_chan_divider != 3 || output_chan_divider != 5) {
							break;
						}
					}
				}
			}
			if (i == HMC7044_NOF_OP_CH) {
				fvco_clk_hz = fdist;
				break;
			}
		}
	}

	/*calculate fpfd2*/
	pfd2_clk_hz = gcd(fvco_clk_hz, pll2ref_clk_hz);

	if (pfd2_clk_hz < HMC7044_PD2_CLK_FREQ_HZ_MIN || pfd2_clk_hz > HMC7044_PD2_CLK_FREQ_HZ_MAX) {
		return API_CMS_ERROR_ERROR;
	}
	/*calculate R1, N1, R2, N2*/
	R1 = flcm_clk_hz / pfd1_clk_hz;
	N1 = fvcxo_clk_freq_hz / pfd1_clk_hz;
	R2 = pll2ref_clk_hz / pfd2_clk_hz;
	N2 = fvco_clk_hz / pfd2_clk_hz;

	/*pll config*/
	if (err = adi_hmc7044_pll1_config_set(device, R1, N1), err != API_CMS_ERROR_OK)
		return err;

	if (err = adi_hmc7044_gpi_config_set(device, 0, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpi_config_set(device, 1, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpi_config_set(device, 2, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpi_config_set(device, 3, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpo_config_set(device, 0, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpo_config_set(device, 1, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpo_config_set(device, 2, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpo_config_set(device, 3, 0), err != API_CMS_ERROR_OK)
		return err;

	if (err = adi_hmc7044_pll2_config_set(device, 0x0, R2, N2), err != API_CMS_ERROR_OK)
		return err;

	if (err = adi_hmc7044_gpo_config_set(device, 0, 0x2b), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_output_performance_set(device, 1), err != API_CMS_ERROR_OK)
		return err;

	/*output config*/
	adi_hmc7044_op_driver_config_t hmc_driver_config;
	hmc_driver_config.mode = SIGNAL_CML;
	hmc_driver_config.impedance = ADI_CMS_INTERNAL_RESISTOR_50_OHM;
	hmc_driver_config.force_mute_en = 0;
	hmc_driver_config.dynamic_driver_en = 0;

	for (i = 0; i < HMC7044_NOF_OP_CH; i++) {
		if ((output_ch >> i & 0x1)) {
			if (err = adi_hmc7044_output_config_set(device, i, HMC7044_OP_SIG_CH_DIV, fvco_clk_hz / output_clk_freq_hz[i], 0 , 1), err != API_CMS_ERROR_OK)
				return err;
			if (adi_hmc7044_output_driver_config_set(device, i, &hmc_driver_config), err != API_CMS_ERROR_OK)
				return err;
		}
	}
	if (err = adi_hmc7044_output_config_set(device, 3, HMC7044_OP_SIG_CH_DIV, 0x40, 0, 1), err != API_CMS_ERROR_OK)
		return err;
	if (adi_hmc7044_output_driver_config_set(device, 3, &hmc_driver_config), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_output_config_set(device, 13, HMC7044_OP_SIG_CH_DIV, 0x40, 0, 1), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_output_driver_config_set(device, 13, &hmc_driver_config), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_output_multi_slip_config_set(device, 13, 0, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_vco_enable_set(device, 1), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_reg_update(device), err != API_CMS_ERROR_OK)
		return err;
	return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_pll_config(adi_hmc7044_device_t *device, adi_hmc7044_clk_in_e ref_ch, uint64_t ref_clk_freq_hz, uint64_t fvcxo_clk_freq_hz, uint64_t fpfd1_freq_hz, uint64_t fvco_freq_hz){
	int32_t err;
	uint64_t flcm_clk_hz, pfd1_clk_hz, pfd2_clk_hz, vcxo_prescaler, pll2ref_clk_hz;
	uint64_t R1, N1, N2, R2;
	uint8_t  hmc_priority[] = { 0, 1, 2, 3 };

	/*range check*/
	if (device == ADI_INVALID_POINTER) {
		return API_CMS_ERROR_INVALID_HANDLE_PTR;
	}

	if (ref_ch > HMC7044_CLK_IN_ALL) {
		return API_CMS_ERROR_INVALID_HANDLE_PTR;
	}

	if ((ref_clk_freq_hz > HMC7044_REF_CLK_FREQ_HZ_MAX || ref_clk_freq_hz < HMC7044_REF_CLK_FREQ_HZ_MIN)) {
		return API_CMS_ERROR_INVALID_PARAM;
	}

	if (fvcxo_clk_freq_hz < HMC7044_VCXO_CLK_FREQ_HZ_MIN || fvcxo_clk_freq_hz > HMC7044_VCXO_CLK_FREQ_HZ_MAX) {
		return API_CMS_ERROR_INVALID_PARAM;
	}

	/*enable clkin*/
	if (err = adi_hmc7044_input_reference_set(device, 0, IPBUFFER_INTERNAL_100_OHM_EN | IPBUFFER_AC_COUPLED_MODE_EN, (ref_ch & HMC7044_CLK_IN_0)), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_set(device, 1, IPBUFFER_INTERNAL_100_OHM_EN | IPBUFFER_AC_COUPLED_MODE_EN, (ref_ch & HMC7044_CLK_IN_1) >> 1), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_set(device, 2, IPBUFFER_INTERNAL_100_OHM_EN | IPBUFFER_AC_COUPLED_MODE_EN, (ref_ch & HMC7044_CLK_IN_2) >> 2), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_set(device, 3, IPBUFFER_INTERNAL_100_OHM_EN | IPBUFFER_AC_COUPLED_MODE_EN, (ref_ch & HMC7044_CLK_IN_3) >> 3), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_priority_set(device, hmc_priority, 4), err != API_CMS_ERROR_OK)
		return err;

	/*calculate fLCM, typical range to be 30~40 MHz*/
	flcm_clk_hz = ref_clk_freq_hz;

	/*scale flcm to 30-40 range*/
	if (ref_clk_freq_hz > HMC7044_PLL1REF_CLK_FREQ_HZ_MAX || ref_clk_freq_hz < HMC7044_PLL1REF_CLK_FREQ_HZ_MIN) {
		uint8_t div = ref_clk_freq_hz / HMC7044_PLL1REF_CLK_FREQ_HZ_MIN;
		flcm_clk_hz = ref_clk_freq_hz / div;
	}
	/*calculate vcxo prescaler*/
	if (fvcxo_clk_freq_hz % flcm_clk_hz != 0) {
		return API_CMS_ERROR_ERROR;
	}
	vcxo_prescaler = fvcxo_clk_freq_hz / flcm_clk_hz;

	if (err = adi_hmc7044_input_reference_los_config_set(device, 7, 0, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_prescaler_config_set(device, 0, vcxo_prescaler), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_prescaler_config_set(device, 1, vcxo_prescaler), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_prescaler_config_set(device, 2, vcxo_prescaler), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_prescaler_config_set(device, 3, vcxo_prescaler), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_input_reference_oscin_prescaler_config_set(device, vcxo_prescaler), err != API_CMS_ERROR_OK)
		return err;

	/*calculate fPFD1*/
	pfd1_clk_hz = gcd(flcm_clk_hz, fvcxo_clk_freq_hz);
	if (fvcxo_clk_freq_hz / 65535 > pfd1_clk_hz) {
		return API_CMS_ERROR_ERROR;
	}

	/* calculate pll2ref*/
	pll2ref_clk_hz = fvcxo_clk_freq_hz <= 125e6 ? 2 * fvcxo_clk_freq_hz : fvcxo_clk_freq_hz;

	/*calculate fpfd2*/
	pfd2_clk_hz = gcd(fvco_freq_hz, pll2ref_clk_hz);

	/*calculate R1, N1, R2, N2*/
	R1 = flcm_clk_hz / pfd1_clk_hz;
	N1 = fvcxo_clk_freq_hz / pfd1_clk_hz;
	R2 = pll2ref_clk_hz / pfd2_clk_hz;
	N2 = fvco_freq_hz / pfd2_clk_hz;

	/*pll config*/
	if (err = adi_hmc7044_pll1_config_set(device, R1, N1), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpi_config_set(device, 0, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpi_config_set(device, 1, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpi_config_set(device, 2, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpi_config_set(device, 3, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpo_config_set(device, 0, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpo_config_set(device, 1, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpo_config_set(device, 2, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpo_config_set(device, 3, 0), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_pll2_config_set(device, 0x0, R2, N2), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_gpo_config_set(device, 0, 0x2b), err != API_CMS_ERROR_OK)
		return err;
	if (err = adi_hmc7044_output_performance_set(device, 1), err != API_CMS_ERROR_OK)
		return err;
	return API_CMS_ERROR_OK;
}

uint64_t gcd(uint64_t value1, uint64_t value2)
{
	uint64_t maxvalue;
	while (value1 != 0 && value2 != 0) {
		if (value1 > value2){
			value1 %= value2;
		}
		else {
			value2 %= value1;
		}
	}
	maxvalue = value1 > value2 ? value1 : value2;
	return maxvalue;
}

uint64_t lcm(uint64_t value1, uint64_t value2)
{
	if (value1 == 0 && value2 == 0) {
		return 0;
	}
	else {
		return (value1 * value2) / gcd(value1, value2);
	}
}

/*! @! */
