/*!
 * @brief     Device level API implementation
 *
 * @copyright copyright(c) 2018 analog devices, inc. all rights reserved.
 *            This software is proprietary to Analog Devices, Inc. and its
 *            licensor. By using this software you agree to the terms of the
 *            associated analog devices software license agreement.
 */

/*!
 * @addtogroup __HMC7044_DEVICE_API__
 * @{
 */

/*============= I N C L U D E S ============*/
#include "adi_utils.h"
#include "adi_hmc7044.h"
#include "hmc7044_hal.h"
#include "hmc7044_reg.h"

/*============= D E F I N E S ==============*/

/*============= D A T A ====================*/
static uint8_t hmc7044_api_revision[3] = {0,1,2};
static adi_cms_reg_data_t ADI_RECOMMENDED_INIT_TBL[] = {
    {0x09F,0x4D},
    {0x0A0,0xDF},
    {0x0A5,0x06},
    {0x0A8,0x06},
    {0x0B0,0x04},
};

/*============= C O D E ====================*/
int32_t adi_hmc7044_device_hw_open(adi_hmc7044_device_t *device)
{
    int32_t err;

    if (device == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_HANDLE_PTR;
    }
    if (device->hal_info.spi_xfer == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_XFER_PTR;
    }
    if (device->hal_info.delay_us == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_DELAYUS_PTR;
    }

    err = hmc7044_hw_open(device);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }

#if 0 /*TODO: Finalise:Data sheet says its recommended but may be not required*/
    err = hmc7044_hw_reset(device);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }
#endif

    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_device_hw_close(adi_hmc7044_device_t *device)
{
    int32_t err;

#if 0 /*TODO: Finalise:Data sheet says its recommended but may be not required*/
    err = hmc7044_hw_reset(device);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }
#endif

    err = hmc7044_hw_close(device);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }

    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_device_sleep_set(adi_hmc7044_device_t *device, uint8_t sleepmode)
{
	int32_t err;
	uint8_t reg_val;
	if (device == ADI_INVALID_POINTER) {
		return API_CMS_ERROR_INVALID_HANDLE_PTR;
	}

	err = hmc7044_spi_reg_get(device, HMC7044_GLOBAL_REQUEST_MODE_CTRL_REG, &reg_val);
	if (err != API_CMS_ERROR_OK) {
		return err;
	}
	reg_val &= (sleepmode);
	err = hmc7044_spi_reg_set(device, HMC7044_GLOBAL_REQUEST_MODE_CTRL_REG, reg_val);
	if (err != API_CMS_ERROR_OK) {
		return err;
	}

	return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_device_init(adi_hmc7044_device_t *device)
{
    int32_t err;
    if (device == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_HANDLE_PTR;
    }

    err = hmc7044_spi_reg_tbl_set(device, &ADI_RECOMMENDED_INIT_TBL[0],
        ADI_UTILS_ARRAY_SIZE(ADI_RECOMMENDED_INIT_TBL));
    if (err != API_CMS_ERROR_OK) {
        return err;
    }

    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_device_reset(adi_hmc7044_device_t *device, uint8_t hw_reset)
{
    int32_t err;
    if (device == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_HANDLE_PTR;
    }

    if (hw_reset > 1) {
        return API_CMS_ERROR_INVALID_PARAM;
    }

    if (hw_reset) {
        err = hmc7044_hw_reset(device);
        if (err != API_CMS_ERROR_OK) {
            return err;
        }
    } else {
        err = hmc7044_spi_reg_set(device,
                HMC7044_GLOBAL_SW_RESET_CTRL_REG, HMC7044_SOFT_RESET);
        if (err != API_CMS_ERROR_OK) {
            return err;
        }
        err = hmc7044_sw_delay_us(device, HMC7044_SPI_RESET_PERIOD_US);
        if (err != API_CMS_ERROR_OK) {
            return err;
        }
        err = hmc7044_spi_reg_set(device, HMC7044_GLOBAL_SW_RESET_CTRL_REG, 0x0);
        if (err != API_CMS_ERROR_OK) {
            return err;
        }
    }

    err = hmc7044_sw_delay_us(device, HMC7044_SPI_RESET_PERIOD_US);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }

    err = hmc7044_spi_reg_tbl_set(device, &ADI_RECOMMENDED_INIT_TBL[0],
        ADI_UTILS_ARRAY_SIZE(ADI_RECOMMENDED_INIT_TBL));
    if (err != API_CMS_ERROR_OK) {
        return err;
    }

    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_device_deinit(adi_hmc7044_device_t *device)
{
    if (device == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_HANDLE_PTR;
    }
    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_device_chip_id_get(adi_hmc7044_device_t *device, adi_cms_chip_id_t *chip_id)
{
    int err;
    uint8_t tmp_reg[3];

    if (device == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_HANDLE_PTR;
    }
    if (chip_id == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_PARAM;
    }

    err = hmc7044_spi_reg_get(device, HMC7044_CHIP_ID_0_REG, &tmp_reg[0]);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }
    err = hmc7044_spi_reg_get(device, HMC7044_CHIP_ID_1_REG, &tmp_reg[1]);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }
    err = hmc7044_spi_reg_get(device, HMC7044_CHIP_ID_2_REG, &tmp_reg[2]);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }

    /*TODO: Get details on this*/
    chip_id->dev_revision = tmp_reg[0];
    chip_id->prod_id = (((uint16_t) tmp_reg[2]) << 8);
    chip_id->prod_id |= (tmp_reg[1]);

    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_device_spi_register_set(adi_hmc7044_device_t *device, uint16_t addr, uint8_t val)
{
    return hmc7044_spi_reg_set(device, addr, val);
}

int32_t adi_hmc7044_device_spi_register_get(adi_hmc7044_device_t *device, uint16_t addr, uint8_t *val)
{
    return hmc7044_spi_reg_get(device, addr, val);
}

int32_t adi_hmc7044_device_api_revision_get(adi_hmc7044_device_t *device, uint8_t *rev_major,
        uint8_t *rev_minor, uint8_t *rev_rc)
{
    int32_t err;

    if (device == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_HANDLE_PTR;
    }
    err = API_CMS_ERROR_OK;
    if (rev_major != ADI_INVALID_POINTER) {
        *rev_major = hmc7044_api_revision[0];
    } else {
        err = API_CMS_ERROR_INVALID_PARAM;
    }
    if (rev_minor != ADI_INVALID_POINTER) {
        *rev_minor = hmc7044_api_revision[1];
    } else {
        err = API_CMS_ERROR_INVALID_PARAM;
    }
    if(rev_rc != ADI_INVALID_POINTER) {
        *rev_rc = hmc7044_api_revision[2];
    } else {
        err = API_CMS_ERROR_INVALID_PARAM;
    }

    return err;
}

int32_t adi_hmc7044_device_trigger_restart(adi_hmc7044_device_t *device)
{
    uint8_t reg_val;
    int32_t err;
    if (device == ADI_INVALID_POINTER) {
        return API_CMS_ERROR_INVALID_HANDLE_PTR;
    }

    err = hmc7044_spi_reg_get(device, HMC7044_GLOBAL_SW_RESET_CTRL_REG, &reg_val);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }
    reg_val |= HMC7044_RESET_DIV_FSM;
    err = hmc7044_spi_reg_set(device, HMC7044_GLOBAL_SW_RESET_CTRL_REG, reg_val);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }
    err = hmc7044_sw_delay_us(device, HMC7044_DIV_RESET_PERIOD_US);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }
    reg_val &= (~HMC7044_RESET_DIV_FSM);
    err = hmc7044_spi_reg_set(device, HMC7044_GLOBAL_SW_RESET_CTRL_REG, reg_val);
    if (err != API_CMS_ERROR_OK) {
        return err;
    }

    return API_CMS_ERROR_OK;
}

int32_t adi_hmc7044_gpi_config_set(adi_hmc7044_device_t *device, uint8_t index, uint8_t config)
{
	int32_t err;
	if (device == ADI_INVALID_POINTER) {
		return API_CMS_ERROR_INVALID_HANDLE_PTR;
	}

	if ((index >= HMC7044_NOF_GPIO_MAX)) {
		return API_CMS_ERROR_INVALID_PARAM;
	}

	err = adi_hmc7044_device_spi_register_set(device, (HMC7044_GPI_CTRL_1_REG + index), config);
	return err;
}

int32_t adi_hmc7044_gpo_config_set(adi_hmc7044_device_t *device, uint8_t index, uint8_t config)
{
	int32_t err;
	if (device == ADI_INVALID_POINTER) {
		return API_CMS_ERROR_INVALID_HANDLE_PTR;
	}

	if ((index >= HMC7044_NOF_GPIO_MAX)) {
		return API_CMS_ERROR_INVALID_PARAM;
	}

	err = adi_hmc7044_device_spi_register_set(device, (HMC7044_GPO_CTRL_1_REG + index), config);
	return err;
}

/*! @! */
