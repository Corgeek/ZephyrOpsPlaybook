/*
 * Copyright (c) 2024 Takayuki Goto <tkg.develop@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include "drivers/i2c/drv_i2c_common.h"

#ifdef  __cplusplus
extern "C" {
#endif

// VSS                                                          // -
#define GPIOG_PIN09                 GPIO_PORT_PIN(gpiog,  9)    // QSPI_BK2_IO2
#define GPIOD_PIN05                 GPIO_PORT_PIN(gpiod,  5)    // PMOD#2- USART2_TX
#define GPIOD_PIN04                 GPIO_PORT_PIN(gpiod,  4)    // PMOD#4- USART2_RTS
#define GPIOC_PIN10                 GPIO_PORT_PIN(gpioc, 10)    // SDIO1_D2
#define GPIOA_PIN15                 GPIO_PORT_PIN(gpioa, 15)    // JTDI
#define GPIOI_PIN01                 GPIO_PORT_PIN(gpioi,  1)    // FCM_D25
#define GPIOI_PIN00                 GPIO_PORT_PIN(gpioi,  0)    // FMC_D24
// VSS                                                          // -
#define GPIOI_PIN06                 GPIO_PORT_PIN(gpioi,  6)    // FMC_D28
#define GPIOI_PIN05                 GPIO_PORT_PIN(gpioi,  5)    // FMC_NBL3
#define GPIOI_PIN04                 GPIO_PORT_PIN(gpioi,  4)    // FMC_NBL2
#define GPIOB_PIN05                 GPIO_PORT_PIN(gpiob,  5)    // ULPI_D7
// VDDKDO                                                       // -
// VCAP                                                         // -
#define GPIOK_PIN05                 GPIO_PORT_PIN(gpiok,  5)    // JOY_RIGHT
#define GPIOG_PIN10                 GPIO_PORT_PIN(gpiog, 10)    // DCMI_D2
// VBAT                                                         // -
#define GPIOJ_PIN15                 GPIO_PORT_PIN(gpioj, 15)    // Audio_INT
#define GPIOD_PIN06                 GPIO_PORT_PIN(gpiod,  6)    // PMOD#4- USART2_RX
#define GPIOD_PIN03                 GPIO_PORT_PIN(gpiod,  3)    // PMOD#18_DFSDM_CKOUT/DCMI_D5
#define GPIOC_PIN11                 GPIO_PORT_PIN(gpioc, 11)    // SDIO1_D3 || DCMI_D4
#define GPIOA_PIN14                 GPIO_PORT_PIN(gpioa, 14)    // JTCK_SWCLK
#define GPIOI_PIN02                 GPIO_PORT_PIN(gpioi,  2)    // FMC_D26
#define GPIOH_PIN15                 GPIO_PORT_PIN(gpioh, 15)    // FMC_D23
#define GPIOH_PIN14                 GPIO_PORT_PIN(gpioh, 14)    // FMC_D22
// VSS                                                          // -
#define GPIOI_PIN07                 GPIO_PORT_PIN(gpioi,  7)    // FMC_D29
#define GPIOE_PIN01                 GPIO_PORT_PIN(gpioe,  1)    // FMC_NBL1
#define GPIOB_PIN06                 GPIO_PORT_PIN(gpiob,  6)    // HDMI_CEC
// VSS                                                          // -
#define GPIOB_PIN04                 GPIO_PORT_PIN(gpiob,  4)    // NJTRST

#define GPIOK_PIN04                 GPIO_PORT_PIN(gpiok,  4)    // JOY_LEFT
#define GPIOG_PIN11                 GPIO_PORT_PIN(gpiog, 11)    // ETH_/TX_EN/TX_EN
// PC15-OSC32_OUT                                               // OSC32_OUT
// VSS                                                          // -
#define GPIOD_PIN07                 GPIO_PORT_PIN(gpiod,  7)    // SPDIF_RX0
#define GPIOC_PIN12                 GPIO_PORT_PIN(gpioc, 12)    // SDIO1_CK
// VSS                                                          // -
#define GPIOI_PIN03                 GPIO_PORT_PIN(gpioi,  3)    // FMC_D27
#define GPIOA_PIN13                 GPIO_PORT_PIN(gpioa, 13)    // JTMS-SWDIO
// VSS                                                          // -
// VDDLDO                                                       // -
// PC14-OSC32_IN                                                // OSC32_IN
#define GPIOE_PIN02                 GPIO_PORT_PIN(gpioe,  2)    // ETH_nINT || SAI4_CK1
#define GPIOE_PIN00                 GPIO_PORT_PIN(gpioe,  0)    // FMC_NBL0
#define GPIOB_PIN07                 GPIO_PORT_PIN(gpiob,  7)    // DCMI_VSYNC
#define GPIOB_PIN03                 GPIO_PORT_PIN(gpiob,  3)    // JTDO/TRACESWO
#define GPIOK_PIN06                 GPIO_PORT_PIN(gpiok,  6)    // JOY_UP
#define GPIOK_PIN03                 GPIO_PORT_PIN(gpiok,  3)    // JOY_DOWN
#define GPIOG_PIN12                 GPIO_PORT_PIN(gpiog, 12)    // ETH_/TXD1/TXD1
#define GPIOE_PIN05                 GPIO_PORT_PIN(gpioe,  5)    // SAI1_SCK_A
#define GPIOJ_PIN14                 GPIO_PORT_PIN(gpioj, 14)    // DCMI_PWR_EN
#define GPIOJ_PIN12                 GPIO_PORT_PIN(gpioj, 12)    // BL_CTRL
#define GPIOD_PIN02                 GPIO_PORT_PIN(gpiod,  2)    // SDIO1_CMD
#define GPIOD_PIN00                 GPIO_PORT_PIN(gpiod,  0)    // FMC_D2
#define GPIOA_PIN10                 GPIO_PORT_PIN(gpioa, 10)    // VCP-USART1_RX
#define GPIOA_PIN09                 GPIO_PORT_PIN(gpioa,  9)    // VCP-USART1_TX
#define GPIOH_PIN13                 GPIO_PORT_PIN(gpioh, 13)    // FMC_D21
// VCAP                                                         // -
#define GPIOE_PIN04                 GPIO_PORT_PIN(gpioe,  4)    // SAI1_FS_A
#define GPIOE_PIN03                 GPIO_PORT_PIN(gpioe,  3)    // SAI1_SD_B
#define GPIOB_PIN09                 GPIO_PORT_PIN(gpiob,  9)    // PMOD#19_DFSDM-DATA7 || DCMI_D7
#define GPIOB_PIN08                 GPIO_PORT_PIN(gpiob,  8)    // PMOD#20_DFSDM-CK7 || DCMI_D6
#define GPIOG_PIN14                 GPIO_PORT_PIN(gpiog, 14)    // FMC_SDNCAS
#define GPIOK_PIN07                 GPIO_PORT_PIN(gpiok,  7)    // TOUCH_INT
#define GPIOG_PIN15                 GPIO_PORT_PIN(gpiog, 15)    // QSPI_BK2_IO3
 
#define GPIOG_PIN13                 GPIO_PORT_PIN(gpiog, 13)    // ETH_/TXD0/TXD0
// VLXSMPS                                                      // -
#define GPIOJ_PIN13                 GPIO_PORT_PIN(gpioj, 13)    // PMOD#12_GPIO
// VDD                                                          // -
#define GPIOD_PIN01                 GPIO_PORT_PIN(gpiod,  1)    // FMC_D3
#define GPIOC_PIN08                 GPIO_PORT_PIN(gpioc,  8)    // SDIO1_D0
#define GPIOC_PIN09                 GPIO_PORT_PIN(gpioc,  9)    // SDIO1_D1 || DCMI_D3
#define GPIOA_PIN08                 GPIO_PORT_PIN(gpioa,  8)    // CEC_CK || MCO1
#define GPIOA_PIN12                 GPIO_PORT_PIN(gpioa, 12)    // PMOD#4-SPI2_SCK/2_CK
#define GPIOA_PIN11                 GPIO_PORT_PIN(gpioa, 11)    // PMOD#1-SPI2_NSS/2_WS
#define GPIOI_PIN09                 GPIO_PORT_PIN(gpioi,  9)    // FMC_D30
#define GPIOC_PIN13                 GPIO_PORT_PIN(gpioc, 13)    // TAMP_1/WKUP2
#define GPIOI_PIN08                 GPIO_PORT_PIN(gpioi,  8)    // uSD_Detect
#define GPIOE_PIN06                 GPIO_PORT_PIN(gpioe,  6)    // SAI1_SD_A
// VDD                                                          // -
// PDR_ON                                                       // -
// BOOT0                                                        // -
// VDD                                                          // -
// VDDSMPS                                                      // -
#define GPIOC_PIN07                 GPIO_PORT_PIN(gpioc,  7)    // PMOD#17_DFSDM_DATA3/DCMI_D1
#define GPIOC_PIN06                 GPIO_PORT_PIN(gpioc,  6)    // PMOD#11_INT/DCMI_D0
#define GPIOG_PIN08                 GPIO_PORT_PIN(gpiog,  8)    // FMC_SDCLK
#define GPIOG_PIN07                 GPIO_PORT_PIN(gpiog,  7)    // SAI1_MCLK_A
// VDD33USB                                                     // -
// VSSSMPS                                                      // -
#define GPIOI_PIN10                 GPIO_PORT_PIN(gpioi, 10)    // FMC_D31
#define GPIOI_PIN11                 GPIO_PORT_PIN(gpioi, 11)    // ULPI_DIR
// VDD                                                          // -
#define GPIOF_PIN02                 GPIO_PORT_PIN(gpiof,  2)    FMC_A2
// VSS                                                          // -
// VSS                                                          // -
// VDD                                                          // -
#define GPIOG_PIN05                 GPIO_PORT_PIN(gpiog,  5)    // FMC_BA1
#define GPIOG_PIN06                 GPIO_PORT_PIN(gpiog,  6)    // QSPI_BK1_NCS
// VSS                                                          // -

// VDD50USB                                                     // -
// VFBSMPS                                                      // -
#define GPIOF_PIN01                 GPIO_PORT_PIN(gpiof,  1)    // FMC_A1
#define GPIOF_PIN00                 GPIO_PORT_PIN(gpiof,  0)    // FMC_A0
// VDD                                                          // -
// VSS                                                          // -
// VSS                                                          // -
// VSS                                                          // -
#define GPIOI_PIN12                 GPIO_PORT_PIN(gpioi, 12)    // LED1
// VSS                                                          // -
// VSS                                                          // -
// VDD                                                          // -
#define GPIOG_PIN04                 GPIO_PORT_PIN(gpiog,  4)    // FMC_BA0
#define GPIOG_PIN03                 GPIO_PORT_PIN(gpiog,  3)    // DSI_Reset
#define GPIOG_PIN02                 GPIO_PORT_PIN(gpiog,  2)    // FMC_A12
#define GPIOK_PIN02                 GPIO_PORT_PIN(gpiok,  2)    // JOY_SEL
#define GPIOI_PIN13                 GPIO_PORT_PIN(gpioi, 13)    // LED2
#define GPIOI_PIN14                 GPIO_PORT_PIN(gpioi, 14)    // LED3
#define GPIOF_PIN03                 GPIO_PORT_PIN(gpiof,  3)    // FMC_A3
// VDD                                                          // -
// VSS                                                          // -
// VSS                                                          // -
// VSS                                                          // -
// PH1-OSC_OUT                                                  // OSC_OUT
// VSS                                                          // -
// VSS                                                          // -
// VDD                                                          // -
#define GPIOK_PIN00                 GPIO_PORT_PIN(gpiok,  0)    // ARD_D13-SPI5_SCK
#define GPIOK_PIN01                 GPIO_PORT_PIN(gpiok,  1)    // ARD_D10-SPI5_NSS || TIM1_CH1
// VSS                                                          // -
// VSS                                                          // -
// PH0-OSC_IN                                                   // OSC_IN
// VSS                                                          // -
#define GPIOF_PIN05                 GPIO_PORT_PIN(gpiof,  5)    // FMC_A5
#define GPIOF_PIN04                 GPIO_PORT_PIN(gpiof,  4)    // FMC_A4

// VSS                                                          // -
// VSS                                                          // -
// VSS                                                          // -
// NRST                                                         // NRST
// VSS                                                          // -
// VSS                                                          // -
// VDD                                                          // -
#define GPIOJ_PIN11                 GPIO_PORT_PIN(gpioj, 11)    // ARD_D12-SPI5_MISO
// VSSDSI                                                       // -
// DSI_D1P                                                      // -
// DSI_D1N                                                      // -
#define GPIOF_PIN06                 GPIO_PORT_PIN(gpiof,  6)    // QSPI_BK1_IO3
#define GPIOF_PIN07                 GPIO_PORT_PIN(gpiof,  7)    // QSPI_BK1_IO2
#define GPIOF_PIN08                 GPIO_PORT_PIN(gpiof,  8)    // PMOD#14_PWM || ARD_D3-TIM13_CH1
// VDD                                                          // -
// VSS                                                          // -
// VSS                                                          // -
// VSS                                                          // -
// VDDA                                                         // -
// VSS                                                          // -
// VSS                                                          // -
// VDD                                                          // -
#define GPIOJ_PIN10                 GPIO_PORT_PIN(gpioj, 10)    // ARD_D11-SPI5_MOSI || TIM1_CH2N
// VSSDSI                                                       // -
// DSI_CKP                                                      // -
// DSI_CKN                                                      // -
#define GPIOC_PIN00                 GPIO_PORT_PIN(gpioc,  0)    // ULPI_STP
#define GPIOF_PIN10                 GPIO_PORT_PIN(gpiof, 10)    // ARD_A1
#define GPIOF_PIN09                 GPIO_PORT_PIN(gpiof,  9)    // QSPI_BK1_IO1
// VDD                                                          // -
// VSS                                                          // -
// VSS                                                          // -
// VSS                                                          // -
// VREF+                                                        // -
// VDD                                                          // -

#define GPIOJ_PIN09                 GPIO_PORT_PIN(gpioj,  9)    // ARD_D0-UART8_RX
// VSSDSI                                                       // -
// DSI_D0P                                                      // -
// DSI_D0N                                                      // -
#define GPIOC_PIN01                 GPIO_PORT_PIN(gpioc,  1)    // ETH_MDC || SAI4_D1
#define GPIOC_PIN02                 GPIO_PORT_PIN(gpioc,  2)    // PMOD#3-SPI2_MISO/2_SDI
#define GPIOC_PIN03                 GPIO_PORT_PIN(gpioc,  3)    // PMOD#2-SPI2_MOSI/2_SDO
// VDD                                                          // -
// VREF-                                                        // -
// VDD                                                          // -
// VDD                                                          // -
// VDD                                                          // -
#define GPIOJ_PIN08                 GPIO_PORT_PIN(gpioj,  8)    // ARD_D1-UART8_TX
#define GPIOJ_PIN07                 GPIO_PORT_PIN(gpioj,  7)    // ARD_D6-TIM8_CH2N
#define GPIOJ_PIN06                 GPIO_PORT_PIN(gpioj,  6)    // ARD_D9-TIM8_CH2
// VSS                                                          // -
// VCAPDSI                                                      // -
#define GPIOH_PIN02                 GPIO_PORT_PIN(gpioh,  2)    // QSPI_BK2_IO0
#define GPIOA_PIN02                 GPIO_PORT_PIN(gpioa,  2)    // ETH_MDIO
#define GPIOA_PIN01                 GPIO_PORT_PIN(gpioa,  1)    // ETH_/RX_CLK/REF_CLK/CLK
#define GPIOA_PIN00                 GPIO_PORT_PIN(gpioa,  0)    // PMOD#1- USART2_CTS_NSS
#define GPIOJ_PIN00                 GPIO_PORT_PIN(gpioj,  0)    // ARD_D7
// VDD                                                          // -
// VDD                                                          // -
#define GPIOE_PIN10                 GPIO_PORT_PIN(gpioe, 10)    // FMC_D7
// VSSA                                                         // -
#define GPIOE_PIN11                 GPIO_PORT_PIN(gpioe, 11)    // FMC_D8
#define GPIOB_PIN10                 GPIO_PORT_PIN(gpiob, 10)    // ULPI_D3
#define GPIOB_PIN11                 GPIO_PORT_PIN(gpiob, 11)    // ULPI_D4
#define GPIOH_PIN10                 GPIO_PORT_PIN(gpioh, 10)    // FMC_D18
#define GPIOH_PIN11                 GPIO_PORT_PIN(gpioh, 11)    // FMC_D19
#define GPIOD_PIN15                 GPIO_PORT_PIN(gpiod, 15)    // FMC_D1
#define GPIOD_PIN14                 GPIO_PORT_PIN(gpiod, 14)    // FMC_D0
// VDDDSI                                                       // -
#define GPIOH_PIN03                 GPIO_PORT_PIN(gpioh,  3)    // QSPI_BK2_IO1

#define GPIOH_PIN04                 GPIO_PORT_PIN(gpioh,  4)    // ULPI_NXT
#define GPIOH_PIN05                 GPIO_PORT_PIN(gpioh,  5)    // FMC_SDNWE
#define GPIOI_PIN15                 GPIO_PORT_PIN(gpioi, 15)    // LED4
#define GPIOJ_PIN01                 GPIO_PORT_PIN(gpioj,  1)    // OTG_HS_OverCurrent
#define GPIOF_PIN13                 GPIO_PORT_PIN(gpiof, 13)    // FMC_A7
#define GPIOF_PIN14                 GPIO_PORT_PIN(gpiof, 14)    // FMC_A8
#define GPIOE_PIN09                 GPIO_PORT_PIN(gpioe,  9)    // FMC_D6
// PC2_C                                                        // ARD_A4
#define GPIOE_PIN12                 GPIO_PORT_PIN(gpioe, 12)    // FMC_D9
#define GPIOE_PIN15                 GPIO_PORT_PIN(gpioe, 15)    // FMC_D12
#define GPIOJ_PIN05                 GPIO_PORT_PIN(gpioj,  5)    // ARD_D8
#define GPIOH_PIN09                 GPIO_PORT_PIN(gpioh,  9)    // FMC_D17
#define GPIOH_PIN12                 GPIO_PORT_PIN(gpioh, 12)    // FMC_D20
#define GPIOD_PIN11                 GPIO_PORT_PIN(gpiod, 11)    // QSPI_BK1_IO0
#define GPIOD_PIN12                 GPIO_PORT_PIN(gpiod, 12)    // PMOD#7/ARD_D15-I2C4_SCL
#define GPIOD_PIN13                 GPIO_PORT_PIN(gpiod, 13)    // PMOD#10/ARD_D14-I2C4_SDA
// PC3_C                                                        // ARD_A5
#define GPIOA_PIN06                 GPIO_PORT_PIN(gpioa,  6)    // ARD_D5-TIM3_CH1 || DCMI_PIXCLK
// VSS                                                          // -
#define GPIOA_PIN07                 GPIO_PORT_PIN(gpioa,  7)    // ETH_/RX_DV/CRS_DV/SYNC
#define GPIOB_PIN02                 GPIO_PORT_PIN(gpiob,  2)    // QSPI_CLK
#define GPIOF_PIN12                 GPIO_PORT_PIN(gpiof, 12)    // FMC_A6
// VSS                                                          // -
#define GPIOF_PIN15                 GPIO_PORT_PIN(gpiof, 15)    // FMC_A9
// PA0_C                                                        // ARD_A2
#define GPIOE_PIN13                 GPIO_PORT_PIN(gpioe, 13)    // FMC_D10
#define GPIOH_PIN06                 GPIO_PORT_PIN(gpioh,  6)    // FMC_SDNE1
// VSS                                                          // -
#define GPIOH_PIN08                 GPIO_PORT_PIN(gpioh,  8)    // FMC_D16
#define GPIOB_PIN12                 GPIO_PORT_PIN(gpiob, 12)    // ULPI_D5
#define GPIOB_PIN15                 GPIO_PORT_PIN(gpiob, 15)    // PMOD#8-SPI2_MOSI/2_SDO
#define GPIOD_PIN10                 GPIO_PORT_PIN(gpiod, 10)    // FMC_D15
#define GPIOD_PIN09                 GPIO_PORT_PIN(gpiod,  9)    // FMC_D14
// PA1_C                                                        // ARD_A3
#define GPIOA_PIN05                 GPIO_PORT_PIN(gpioa,  5)    // ULPI_CK
 
#define GPIOC_PIN04                 GPIO_PORT_PIN(gpioc,  4)    // ETH_/RXD0/RXD0/RXD
#define GPIOB_PIN01                 GPIO_PORT_PIN(gpiob,  1)    // ULPI_D2
#define GPIOJ_PIN02                 GPIO_PORT_PIN(gpioj,  2)    // DSI_TE
#define GPIOF_PIN11                 GPIO_PORT_PIN(gpiof, 11)    // FMC_SDNRAS
#define GPIOG_PIN00                 GPIO_PORT_PIN(gpiog,  0)    // FMC_A10
#define GPIOE_PIN08                 GPIO_PORT_PIN(gpioe,  8)    // FMC_D5
// VSS                                                          // -
#define GPIOE_PIN14                 GPIO_PORT_PIN(gpioe, 14)    // FMC_D11
// VCAP1                                                        // -
// VDDLDO                                                       // -
#define GPIOH_PIN07                 GPIO_PORT_PIN(gpioh,  7)    // FMC_SDCKE1
#define GPIOB_PIN13                 GPIO_PORT_PIN(gpiob, 13)    // ULPI_D6
#define GPIOB_PIN14                 GPIO_PORT_PIN(gpiob, 14)    // PMOD#9-SPI2_MISO/2_SDI
#define GPIOD_PIN08                 GPIO_PORT_PIN(gpiod,  8)    // FMC_D13
// VSS                                                          // -
#define GPIOA_PIN03                 GPIO_PORT_PIN(gpioa,  3)    // ULPI_D0
#define GPIOA_PIN04                 GPIO_PORT_PIN(gpioa,  4)    // PMOD#13_ADC || ARD_A0 || DCMI_HSYNC
#define GPIOC_PIN05                 GPIO_PORT_PIN(gpioc,  5)    // ETH_/RXD1/RXD1
#define GPIOB_PIN00                 GPIO_PORT_PIN(gpiob,  0)    // ULPI_D1
#define GPIOJ_PIN03                 GPIO_PORT_PIN(gpioj,  3)    // ARD_D2
#define GPIOJ_PIN04                 GPIO_PORT_PIN(gpioj,  4)    // ARD_D4
#define GPIOG_PIN01                 GPIO_PORT_PIN(gpiog,  1)    // FMC_A11
#define GPIOE_PIN07                 GPIO_PORT_PIN(gpioe,  7)    // FMC_D4


#define I2C_100KHZ_BUS              DEVICE_DT_GET(DT_NODELABEL(i2c4))
#define UART_115200_BUS             DEVICE_DT_GET(DT_NODELABEL(usart1))
#define USER_BUTTON                 GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios)
#define GREEN_LED                   GPIOI_PIN12
#define ORANGE_LED                  GPIOI_PIN13
#define RED_LED                     GPIOI_PIN14
#define BLUE_LED                    GPIOI_PIN15

#define JOY_RIGHT                   GPIOK_PIN05
#define JOY_LEFT                    GPIOK_PIN04
#define JOY_UP                      GPIOK_PIN06
#define JOY_DOWN                    GPIOK_PIN03
#define JOY_SELECT                  GPIOK_PIN02

#ifdef  __cplusplus
}
#endif
