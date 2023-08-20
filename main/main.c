#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "driver/adc.h"
#include "driver/gpio.h"
#include "esp_adc_cal.h"

//#define ROUTE_VREF_TO_GPIO

const uint32_t V_Ref = 1098;
const adc1_channel_t ADC_GPIO_NUM = ADC_CHANNEL_0;


void app_main(void)
{
#ifdef ROUTE_VREF_TO_GPIO
	esp_err_t status;
	status = adc2_vref_to_gpio(GPIO_NUM_25);
	if(status == ESP_OK)
	{
		printf("ADC2 Vref routed to GPIO25\n");
	}
	else
	{
		printf("Failed to route ADC2 Vref\n");
	}
#else
	esp_adc_cal_characteristics_t characteristics;
	adc1_config_width(ADC_WIDTH_BIT_12);
	adc1_config_channel_atten(ADC_GPIO_NUM, ADC_ATTEN_DB_11);
	esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, V_Ref, &characteristics);
	uint32_t voltage;
#endif

    while (true) {
    	voltage =   esp_adc_cal_raw_to_voltage(adc1_get_raw(ADC_GPIO_NUM), &characteristics);
    	printf("%d mV\n",voltage);
        usleep(100000);
    }
}
