#include "enchw.h"
#include "chip.h"

void enc_hw_setup(enchw_device_t *dev)
{
   Chip_SCU_PinMuxSet( 0xF, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC0)); // SSP1_SCK
   Chip_SCU_PinMuxSet( 0x1, 3, (SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC5)); // SSP1_MISO
   Chip_SCU_PinMuxSet( 0x1, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC5)); // SSP1_MOSI

   // Initialize SSP Peripheral
   Chip_SSP_Init(LPC_SSP1);

   Chip_SSP_Set_Mode(LPC_SSP1, SSP_MODE_MASTER);
   Chip_SSP_SetFormat(LPC_SSP1, SSP_BITS_8, SSP_FRAMEFORMAT_SPI, SSP_CLOCK_CPHA0_CPOL0);
   Chip_SSP_SetBitRate(LPC_SSP1, 10000000);

   Chip_SSP_Enable( LPC_SSP1 );

	gpioConfig(GPIO0, GPIO_OUTPUT);
	gpioWrite(GPIO0, ON);
}

void enc_hw_select(enchw_device_t *dev)
{
	gpioWrite(GPIO0, OFF);
}

void enc_hw_unselect(enchw_device_t *dev)
{
	gpioWrite(GPIO0, ON);
}

uint8_t enc_hw_exchangebyte(enchw_device_t *dev, uint8_t byte)
{
	uint8_t rx;

   Chip_SSP_DATA_SETUP_T xferConfig;

   xferConfig.tx_data = &byte;
   xferConfig.tx_cnt  = 0;
   xferConfig.rx_data = &rx;
   xferConfig.rx_cnt  = 0;
   xferConfig.length  = 1;

   Chip_SSP_RWFrames_Blocking( LPC_SSP1, &xferConfig );

	return rx;
}

