//adhishvairagade
#ifndef INC_BQ25792_H_
#define INC_BQ25792_H_

#include "stm32l4xx_hal.h"

#define BQ25792_ADRESS              (0x6B<<1)
#define BQ25792_MINIMAL_SYSTEM_VOLTAGE       0x00
#define BQ25792_CHARGE_VOLTAGE_LIMIT        0x01
#define BQ25792_CHARGE_CURRENT_LIMIT        0x03
#define BQ25792_INPUT_VOLTAGE_LIMIT         0x05
#define BQ25792_INPUT_CURRENT_LIMIT         0x06
#define BQ25792_PRECHARGE_CONTROL          0x08
#define BQ25792_TERMINATION_CONTROL        0x09
#define BQ25792_RECHARGE_CONTROL           0x0A
#define BQ25792_VOTG_REGULATION            0x0B
#define BQ25792_IOTG_REGULATION            0x0D
#define BQ25792_TIMER_CONTROL             0x0E
#define BQ25792_CHARGER_CONTROL_0          0x0F
#define BQ25792_CHARGER_CONTROL_1          0x10
#define BQ25792_CHARGER_CONTROL_2          0x11
#define BQ25792_CHARGER_CONTROL_3          0x12
#define BQ25792_CHARGER_CONTROL_4          0x13
#define BQ25792_CHARGER_CONTROL_5          0x14
#define BQ25792_TEMPERATURE_CONTROL        0x16
#define BQ25792_NTC_CONTROL_0              0x17
#define BQ25792_NTC_CONTROL_1              0x18
#define BQ25792_ICO_CURRENT_LIMIT          0x19
#define BQ25792_CHARGER_STATUS_0           0x1B
#define BQ25792_CHARGER_STATUS_1           0x1C
#define BQ25792_CHARGER_STATUS_2           0x1D
#define BQ25792_CHARGER_STATUS_3           0x1E
#define BQ25792_CHARGER_STATUS_4           0x1F
#define BQ25792_FAULT_STATUS_0             0x20
#define BQ25792_FAULT_STATUS_1             0x21
#define BQ25792_CHARGER_FLAG_0             0x22
#define BQ25792_CHARGER_FLAG_1             0x23
#define BQ25792_CHARGER_FLAG_2             0x24
#define BQ25792_CHARGER_FLAG_3             0x25
#define BQ25792_FAULT_FLAG_0               0x26
#define BQ25792_FAULT_FLAG_1               0x27
#define BQ25792_CHARGER_MASK_0             0x28
#define BQ25792_CHARGER_MASK_1             0x29
#define BQ25792_CHARGER_MASK_2             0x2A
#define BQ25792_CHARGER_MASK_3             0x2B
#define BQ25792_FAULT_MASK_0               0x2C
#define BQ25792_FAULT_MASK_1               0x2D
#define BQ25792_ADC_CONTROL               0x2E
#define BQ25792_ADC_FUNCTION_DISABLE_0     0x2F
#define BQ25792_ADC_FUNCTION_DISABLE_1     0x30
#define BQ25792_IBUS_ADC                  0x31
#define BQ25792_IBAT_ADC                  0x33
#define BQ25792_VBUS_ADC                  0x35
#define BQ25792_VAC1_ADC                  0x37
#define BQ25792_VAC2_ADC                  0x39
#define BQ25792_VBAT_ADC                  0x3B
#define BQ25792_VSYS_ADC                  0x3D
#define BQ25792_TS_ADC                    0x3F
#define BQ25792_TDIE_ADC                  0x41
#define BQ25792_DP_ADC                    0x43
#define BQ25792_DM_ADC                    0x45
#define BQ25792_DPDM_DRIVER                0x47
#define BQ25792_PART_INFO                  0x48

#define BQ25792_ADC_CONTROL_EN            (1<<7)
#define BQ25792_ADC_CONTROL_RATE_SINGLE     (1<<6)
#define BQ25792_ADC_CONTROL_RATE_CONTINUOUS (0<<6)
#define BQ25792_ADC_CONTROL_SAMPLE_15B     (0<<4)
#define BQ25792_ADC_CONTROL_SAMPLE_14B     (1<<4)
#define BQ25792_ADC_CONTROL_SAMPLE_13B     (2<<4)
#define BQ25792_ADC_CONTROL_SAMPLE_12B     (3<<4)
#define BQ25792_ADC_CONTROL_AVG            (1<<3)
#define BQ25792_ADC_CONTROL_AVG_INIT       (1<<2)

#define BQ25792_CHARGER_CONTROL_0_EN_AUTO_IBATDIS  (1<<7)
#define BQ25792_CHARGER_CONTROL_0_FORCE_IBATDIS     (1<<6)
#define BQ25792_CHARGER_CONTROL_0_EN_CHG            (1<<5)
#define BQ25792_CHARGER_CONTROL_0_EN_ICO            (1<<4)
#define BQ25792_CHARGER_CONTROL_0_FORCE_ICO         (1<<3)
#define BQ25792_CHARGER_CONTROL_0_EN_HIZ            (1<<2)
#define BQ25792_CHARGER_CONTROL_0_EN_TERM           (1<<1)

#define BQ25792_CHARGER_CONTROL_1_VAC_OVP_MASK      (2<<4)
#define BQ25792_CHARGER_CONTROL_1_VAC_OVP_26V       (0<<4)
#define BQ25792_CHARGER_CONTROL_1_VAC_OVP_18V       (1<<4)
#define BQ25792_CHARGER_CONTROL_1_VAC_OVP_12V       (2<<4)
#define BQ25792_CHARGER_CONTROL_1_VAC_OVP_7V        (3<<4)
#define BQ25792_CHARGER_CONTROL_1_WD_RST            (1<<3)
#define BQ25792_CHARGER_CONTROL_1_WATCHDOG_MASK     (7<<0)
#define BQ25792_CHARGER_CONTROL_1_WATCHDOG_DISABLE  (0<<0)
#define BQ25792_CHARGER_CONTROL_1_WATCHDOG_500MS    (1<<0)
#define BQ25792_CHARGER_CONTROL_1_WATCHDOG_1S       (2<<0)
#define BQ25792_CHARGER_CONTROL_1_WATCHDOG_2S       (3<<0)
#define BQ25792_CHARGER_CONTROL_1_WATCHDOG_20S      (4<<0)
#define BQ25792_CHARGER_CONTROL_1_WATCHDOG_40S      (5<<0)
#define BQ25792_CHARGER_CONTROL_1_WATCHDOG_80S      (6<<0)
#define BQ25792_CHARGER_CONTROL_1_WATCHDOG_160S     (7<<0)

#define BQ25792_CHARGER_CONTROL_2_FORCE_INDET         (1<<7)
#define BQ25792_CHARGER_CONTROL_2_FORCE_INDET         (1<<7)
#define BQ25792_CHARGER_CONTROL_2_AUTO_INDET_EN       (1<<6)
#define BQ25792_CHARGER_CONTROL_2_EN_12V              (1<<5)
#define BQ25792_CHARGER_CONTROL_2_EN_9V               (1<<4)
#define BQ25792_CHARGER_CONTROL_2_HVDCP_EN            (1<<3)
#define BQ25792_CHARGER_CONTROL_2_SDRV_CTRL_MASK      (2<<1)
#define BQ25792_CHARGER_CONTROL_2_SDRV_CTRL_IDLE      (0<<1)
#define BQ25792_CHARGER_CONTROL_2_SDRV_CTRL_SHUTDOWN  (1<<1)
#define BQ25792_CHARGER_CONTROL_2_SDRV_CTRL_SHIP      (2<<1)
#define BQ25792_CHARGER_CONTROL_2_SDRV_CTRL_POWERDOWN (3<<1)
#define BQ25792_CHARGER_CONTROL_2_SDRV_DLY            (1<<0)

#define BQ25792_CHARGER_CONTROL_3_DIS_ACDRV           (1<<7)
#define BQ25792_CHARGER_CONTROL_3_EN_OTG              (1<<6)
#define BQ25792_CHARGER_CONTROL_3_PFM_OTG_DIS         (1<<5)
#define BQ25792_CHARGER_CONTROL_3_PFM_FWD_DIS         (1<<4)
#define BQ25792_CHARGER_CONTROL_3_WKUP_DLY            (1<<3)
#define BQ25792_CHARGER_CONTROL_3_DIS_LDO             (1<<2)
#define BQ25792_CHARGER_CONTROL_3_DIS_OTG_OOA         (1<<1)
#define BQ25792_CHARGER_CONTROL_3_DIS_FWD_OOA         (1<<0)

#define BQ25792_CHARGER_CONTROL_4_EN_ACDRV2           (1<<7)
#define BQ25792_CHARGER_CONTROL_4_EN_ACDRV1           (1<<6)
#define BQ25792_CHARGER_CONTROL_4_PWM_FREQ            (1<<5)
#define BQ25792_CHARGER_CONTROL_4_DIS_STAT            (1<<4)
#define BQ25792_CHARGER_CONTROL_4_DIS_VSYS_SHORT      (1<<3)
#define BQ25792_CHARGER_CONTROL_4_DIS_VOTG_UVP        (1<<2)
#define BQ25792_CHARGER_CONTROL_4_FORCE_VINDPM_DET    (1<<1)
#define BQ25792_CHARGER_CONTROL_4_EN_IBUS_OCP         (1<<0)

#define BQ25792_CHARGER_CONTROL_5_SFET_PRESENT        (1<<7)
#define BQ25792_CHARGER_CONTROL_5_EN_IBAT             (1<<5)
#define BQ25792_CHARGER_CONTROL_5_IBAT_REG_MASK       (3<<3)
#define BQ25792_CHARGER_CONTROL_5_IBAT_REG_3A         (0<<3)
#define BQ25792_CHARGER_CONTROL_5_IBAT_REG_4A         (1<<3)
#define BQ25792_CHARGER_CONTROL_5_IBAT_REG_5A         (2<<3)
#define BQ25792_CHARGER_CONTROL_5_IBAT_REG_DISABLE    (3<<3)
#define BQ25792_CHARGER_CONTROL_5_EN_IINDPM           (1<<2)
#define BQ25792_CHARGER_CONTROL_5_EN_EXTILIM          (1<<1)
#define BQ25792_CHARGER_CONTROL_5_EN_BATOC            (1<<0)

#define BQ25792_CHARGER_STATUS_0_IINDPM_STAT          (1<<7)
#define BQ25792_CHARGER_STATUS_0_VINDPM_STAT          (1<<6)
#define BQ25792_CHARGER_STATUS_0_WD_STAT              (1<<5)
#define BQ25792_CHARGER_STATUS_0_POORSRC_STAT         (1<<4)
#define BQ25792_CHARGER_STATUS_0_PG_STAT              (1<<3)
#define BQ25792_CHARGER_STATUS_0_AC2_PRESENT_STAT     (1<<2)
#define BQ25792_CHARGER_STATUS_0_AC1_PRESENT_STAT     (1<<1)
#define BQ25792_CHARGER_STATUS_0_VBUS_PRESENT_STAT    (1<<0)

#define BQ25792_CHARGER_STATUS_1_CHG_STAT             (7<<5)
#define BQ25792_CHARGER_STATUS_1_VBUS_STAT            (0xF<<1)
#define BQ25792_CHARGER_STATUS_1_BC12_DONE_STAT       (1<<0)

#define BQ25792_CHARGER_STATUS_2_ICO_STAT             (3<<6)
#define BQ25792_CHARGER_STATUS_2_TREG_STAT            (1<<2)
#define BQ25792_CHARGER_STATUS_2_DPDM_STAT            (1<<1)
#define BQ25792_CHARGER_STATUS_2_VBAT_PRESENT_STAT    (1<<0)

#define BQ25792_CHARGER_STATUS_3_ACRB2_STAT           (1<<7)
#define BQ25792_CHARGER_STATUS_3_ACRB1_STAT           (1<<6)
#define BQ25792_CHARGER_STATUS_3_ADC_DONE_STAT        (1<<5)
#define BQ25792_CHARGER_STATUS_3_VSYS_STAT            (1<<4)
#define BQ25792_CHARGER_STATUS_3_CHG_TMR_STAT         (1<<3)
#define BQ25792_CHARGER_STATUS_3_TRICHG_TMR_STAT      (1<<2)
#define BQ25792_CHARGER_STATUS_3_PRECHG_TMR_STAT      (1<<1)

#define BQ25792_CHARGER_STATUS_4_VBATOTG_LOW_STAT     (1<<4)
#define BQ25792_CHARGER_STATUS_4_TS_COLD_STAT         (1<<3)
#define BQ25792_CHARGER_STATUS_4_TS_COOL_STAT         (1<<2)
#define BQ25792_CHARGER_STATUS_4_TS_WARM_STAT         (1<<1)
#define BQ25792_CHARGER_STATUS_4_TS_HOT_STAT          (1<<0)

#define BQ25792_FAULT_STATUS_0_IBAT_REG_STAT          (1<<7)
#define BQ25792_FAULT_STATUS_0_VBUS_OVP_STAT          (1<<6)
#define BQ25792_FAULT_STATUS_0_VBAT_OVP_STAT          (1<<5)
#define BQ25792_FAULT_STATUS_0_IBUS_OCP_STAT          (1<<4)
#define BQ25792_FAULT_STATUS_0_IBAT_OCP_STAT          (1<<3)
#define BQ25792_FAULT_STATUS_0_CONV_OCP_STAT          (1<<2)
#define BQ25792_FAULT_STATUS_0_VAC2_OVP_STAT          (1<<1)
#define BQ25792_FAULT_STATUS_0_VAC1_OVP_STAT          (1<<0)

#define BQ25792_FAULT_STATUS_1_VSYS_SHORT_STAT        (1<<7)
#define BQ25792_FAULT_STATUS_1_VSYS_OVP_STAT          (1<<6)
#define BQ25792_FAULT_STATUS_1_OTG_OVP_STAT           (1<<5)
#define BQ25792_FAULT_STATUS_1_OTG_UVP_STAT           (1<<4)
#define BQ25792_FAULT_STATUS_1_TSHUT_STAT            (1<<2)

#define BQ25792_CHARGER_FLAGS_0_IINDPM_FLAG          (1<<7)
#define BQ25792_CHARGER_FLAGS_0_VINDPM_FLAG          (1<<6)
#define BQ25792_CHARGER_FLAGS_0_WD_FLAG              (1<<5)
#define BQ25792_CHARGER_FLAGS_0_POORSRC_FLAG         (1<<4)
#define BQ25792_CHARGER_FLAGS_0_PG_FLAG              (1<<3)
#define BQ25792_CHARGER_FLAGS_0_AC2_PRESENT_FLAG     (1<<2)
#define BQ25792_CHARGER_FLAGS_0_AC1_PRESENT_FLAG     (1<<1)
#define BQ25792_CHARGER_FLAGS_0_VBUS_PRESENT_FLAG    (1<<0)

#define BQ25792_CHARGER_FLAGS_1_CHG_FLAG             (1<<7)
#define BQ25792_CHARGER_FLAGS_1_ICO_FLAG             (1<<6)
#define BQ25792_CHARGER_FLAGS_1_VBUS_FLAG            (1<<4)
#define BQ25792_CHARGER_FLAGS_1_TREG_FLAG            (1<<2)
#define BQ25792_CHARGER_FLAGS_1_VBAT_PRESENT_FLAG    (1<<1)
#define BQ25792_CHARGER_FLAGS_1_BC12_DONE_FLAG       (1<<0)

#define BQ25792_CHARGER_FLAGS_2_DPDM_DONE_FLAG       (1<<6)
#define BQ25792_CHARGER_FLAGS_2_ADC_DONE_FLAG        (1<<5)
#define BQ25792_CHARGER_FLAGS_2_VSYS_FLAG            (1<<4)
#define BQ25792_CHARGER_FLAGS_2_CHG_TMR_FLAG         (1<<3)
#define BQ25792_CHARGER_FLAGS_2_TRICHG_TMR_FLAG      (1<<2)
#define BQ25792_CHARGER_FLAGS_2_PRECHG_TMR_FLAG      (1<<1)
#define BQ25792_CHARGER_FLAGS_2_TOPOFF_TMR_FLAG      (1<<0)

#define BQ25792_CHARGER_FLAGS_3_VBATOTG_LOW_FLAG     (1<<4)
#define BQ25792_CHARGER_FLAGS_3_TS_COLD_FLAG         (1<<3)
#define BQ25792_CHARGER_FLAGS_3_TS_COOL_FLAG         (1<<2)
#define BQ25792_CHARGER_FLAGS_3_TS_WARM_FLAG         (1<<1)
#define BQ25792_CHARGER_FLAGS_3_TS_HOT_FLAG          (1<<0)

#define BQ25792_FAULT_MASK_0_IBAT_MASK               (1<<7)
#define BQ25792_FAULT_MASK_0_VBUS_OVP_MASK           (1<<6)
#define BQ25792_FAULT_MASK_0_VBAT_OVP_MASK           (1<<5)
#define BQ25792_FAULT_MASK_0_IBUS_OCP_MASK           (1<<4)
#define BQ25792_FAULT_MASK_0_IBAT_OCP_MASK           (1<<3)
#define BQ25792_FAULT_MASK_0_CONV_OCP_MASK           (1<<2)
#define BQ25792_FAULT_MASK_0_VAC2_OVP_MASK           (1<<1)
#define BQ25792_FAULT_MASK_0_VAC1_OVP_MASK           (1<<0)

HAL_StatusTypeDef BQ25792_Read(uint8_t reg, uint8_t *pData, uint8_t len);
HAL_StatusTypeDef BQ25792_Write(uint8_t reg, uint8_t *pData, uint8_t len);
void BQ25792_Debug(void);
HAL_StatusTypeDef BQ25792_Init(void);
HAL_StatusTypeDef BQ25792_WD_Feed(void);

#endif /* INC_BQ25792_H_ */
