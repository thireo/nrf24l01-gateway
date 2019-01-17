/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "LED.h"
#include "spi_master.h"
#include "nrf24l01.h"

char TX_ADDR[5] = {0x42,0x42,0x42,0x42,0};
char RX_ADDR[5] = {0x2A,0x2A,0x2A,0x2A,0};

uint8_t RX_Buffer[33];
struct bme280_data
{
	int32_t temperature;
	int32_t pressure;
	float humidity;
	float dew_point;
};

typedef union {
	struct {
		int32_t temperature;
		int32_t pressure;
		float humidity;
		float dew_point;
		}hestestruct;
		uint8_t bytes[16];
	}testheste;

void bme280_data_decompress(struct bme280_data *bme280_data_object, uint8_t *data_array);
void bme280_data_decompress(struct bme280_data *bme280_data_object, uint8_t *data_array)
{
	testheste testhest;

	for (int i=0;i<16;i++)
	{
		testhest.bytes[i] = data_array[i];
	}
	
	bme280_data_object->temperature = testhest.hestestruct.temperature;
	bme280_data_object->pressure = testhest.hestestruct.pressure;
	bme280_data_object->dew_point = testhest.hestestruct.dew_point;
	bme280_data_object->humidity = testhest.hestestruct.humidity;
	
	/*bme280_data_object->temperature = ((uint32_t)data_array[0] & 0xFF) + (((uint32_t)data_array[1] & 0xFF) << 8 ) + (((uint32_t)data_array[2] & 0xFF)<< 16) + (((uint32_t)data_array[3] & 0xFF) << 24);
	bme280_data_object->pressure = (data_array[4]) + ((data_array[5] << 8)) + ((data_array[6] << 16)) + ((data_array[7] << 24));
	bme280_data_object->dew_point = (data_array[8]) + ((data_array[9] << 8))+ ((data_array[10] << 16))+ ((data_array[11] << 24));
	bme280_data_object->humidity = (data_array[12]) + ((data_array[13] << 8))+ ((data_array[14] << 16))+ ((data_array[15] << 24));*/
}

struct bme280_data bme280_data_object;

int main (void)
{
	system_init();
	delay_init();
	LED_Init();
	spi_master_init();
	//nrf24l01_init();
	NRF_Enter_RX_Mode(RX_ADDR);
	
	uint32_t *p = 0x0080A00C;
	uint32_t words[4];
	
	words[0] = *(uint32_t*) 0x0080A00C;
	words[1] = *(uint32_t*) 0x0080A040;
	words[2] = *(uint32_t*) 0x0080A044;
	words[3] = *(uint32_t*) 0x0080A048;
	
	uint32_t Status = 0;
	uint32_t i = 0;
	LED_Set_Color(LED_BLUE);
	delay_ms(1000);
	while(1)
	{
		Status = NRF_Read_single(NRF_R_REGISTER(NRF_STATUS_REG));
		
		if ((Status & NRF_STATUS_RX_DR) && (Status != 0xFF))
		{
			
			i=NRF_Read_single(NRF_R_RX_PL_WID);
			if(i>31)
			{
				NRF_Write_1(NRF_FLUSH_RX);
			}
			i=NRF_Read_single(NRF_R_RX_PL_WID);
			NRF_Read(NRF_R_RX_PAYLOAD,i,&RX_Buffer);
			NRF_Write_2(NRF_W_REGISTER(NRF_STATUS_REG), NRF_STATUS_RX_DR);
			NRF_Write_1(NRF_FLUSH_RX);
			/*uint32_t tempLED = 0x000000;
			tempLED = tempLED + (RX_Buffer[3] << 16)*4;
			LED_Set_Color(tempLED);*/
			
			bme280_data_decompress(&bme280_data_object,&RX_Buffer[4]);
			
			/*if (bme280_data_object.temperature > 2100)
			{*/
				uint8_t lol = bme280_data_object.temperature/50;
				uint32_t tempcolour = (LED_OFF + (lol << 16)) & 0xFF0000;
				//LED_Set_Color(LED_GREEN);
				LED_Set_Color(tempcolour);
			/*}
			else
			{
				LED_Set_Color(LED_OFF);
			}*/
			
		}
		else
		{
			//LED_Set_Color(LED_OFF);
			/*delay_ms(500);
			LED_Set_Color(LED_YELLOW);
			delay_ms(500);*/
		}
	}
	/* Insert application code here, after the board has been initialized. */
}
