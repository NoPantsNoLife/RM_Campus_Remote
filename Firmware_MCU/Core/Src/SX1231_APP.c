#include "SX1231_APP.h"
#include "delay.h"

SX1231_Typedef SX1231_Primary;

#define SX1231_WAIT_TH 10000


void SX1231_Primary_TransmitPacket(uint8_t bfr[SX1231_PayloadLength])
{
	static uint32_t wait;
	bfr[SX1231_PayloadLength - 1] = Checksum(bfr, SX1231_PayloadLength);
	while(SX1231_IsActiveFlag_FifoNotEmpty(&SX1231_Primary))
		wait++;
	SX1231_WriteFifo(&SX1231_Primary, bfr, SX1231_PayloadLength);
	while(! SX1231_IsActiveFlag_PacketSent(&SX1231_Primary))
		wait++;
	
	if(wait > SX1231_WAIT_TH)
	{
		wait = 0;
		SX1231_Init_Primary();
	}
}


uint8_t Checksum(uint8_t bfr[], uint32_t length)
{
	uint32_t i;
	uint8_t s = 0;
	for(i=0; i<length-1; i++)
		s += bfr[i];
	return s;
}

void SX1231_Init_Primary()
{
	SX1231_Typedef_Init(&SX1231_Primary);

	SX1231_Primary.SPI_Port = SPI1;
	SX1231_Primary.NSS_GPIO_Pin = SPI_NE_Pin;
	SX1231_Primary.NSS_GPIO_Port = SPI_NE_GPIO_Port;
	SX1231_Primary.DMA_Enable = 0;

	SX1231_Primary.Common.Mode = SX1231_MODE_TX;
	SX1231_Primary.Common.BitRate = 19200;
	SX1231_Primary.Common.Fdev = 40000;
	SX1231_Primary.Common.Frf = 913456789;

	//SX1231_Primary.IRQ_PinMapping.ClkOut = 5;
	SX1231_Primary.IRQ_PinMapping.DioMapping[0] = 0;
	SX1231_Primary.IRQ_PinMapping.DioMapping[1] = 3;
	SX1231_Primary.IRQ_PinMapping.DioMapping[2] = 0;
	SX1231_Primary.IRQ_PinMapping.DioMapping[3] = 0;
	SX1231_Primary.IRQ_PinMapping.DioMapping[4] = 1;
	SX1231_Primary.IRQ_PinMapping.DioMapping[5] = 3;

	SX1231_Primary.Transmitter.OutputPower = 10 + 18;
	SX1231_Primary.Transmitter.PaOn = SX1231_PA0_ON | SX1231_PA1_ON | SX1231_PA2_ON;
	SX1231_Primary.Transmitter.OcpOn = SX1231_OCP_DISABLE;

	SX1231_Primary.Receiver.LnaZin = SX1231_LNA_ZIN_200_OHMS;

	SX1231_Primary.PacketEngine.PreambleSize = 4;
	SX1231_Primary.PacketEngine.SyncSize = 2;
	SX1231_Primary.PacketEngine.SyncValue[0] = 0x66;
	SX1231_Primary.PacketEngine.SyncValue[1] = 0xcc;
	SX1231_Primary.PacketEngine.SyncValue[2] = 0xff;
	SX1231_Primary.PacketEngine.PacketFormat = SX1231_PACKET_FORMAT_FIXED_LENGTH;
	SX1231_Primary.PacketEngine.AddressFiltering = SX1231_ADDRESS_FILTERING_MATCH_NODE_ADDRESS;
	SX1231_Primary.PacketEngine.PayloadLength = SX1231_PayloadLength;
	SX1231_Primary.PacketEngine.NodeAddress = 0x23;
	SX1231_Primary.PacketEngine.DcFree = SX1231_DC_FREE_MANCHESTER;

	SX1231_Primary_Reset();
	SX1231_Init(&SX1231_Primary);
}

void SX1231_Primary_Reset()
{
	LL_GPIO_SetOutputPin(RF_RST_GPIO_Port, RF_RST_Pin);
	delayms(2);
	LL_GPIO_ResetOutputPin(RF_RST_GPIO_Port, RF_RST_Pin);
	delayms(10);
}
