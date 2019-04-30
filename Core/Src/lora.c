/*
 * lora.c
 *
 *  Created on: 30 Apr 2019
 *      Author: frazer
 */

#include "lora.h"

void lora_module_reboot() {

	char buffer[50] = {'\0'};
	uint8_t len = 0;
	uint8_t i = 1;

	while(i) {

		len = sprintf(buffer, "%s\r\n", RN_SYS_RESET);
		HAL_UART_Transmit(&huart3, (uint8_t*)buffer, len, 100);
		memset(buffer, '\0', 50);
		if (HAL_UART_Receive(&huart3, (uint8_t*)buffer, 50, 5000) == HAL_TIMEOUT) {
			i = 0;
		}

		CDC_Transmit_FS((uint8_t*)buffer, 50);
	}
}

void lora_module_set_gpio(char *gpio, uint8_t state) {

	char buffer[30] = {'\0'};
	uint8_t len = 0;

	while(strstr(buffer, "ok") == NULL) {

		memset(buffer, '\0', 30);
		len = sprintf(buffer, "sys set pindig %s %u\r\n", gpio, state);
		HAL_UART_Transmit(&huart3, (uint8_t*)buffer, len, 100);

		memset(buffer, '\0', 30);
		HAL_UART_Receive(&huart3, (uint8_t*)buffer, 30, 200);

		//CDC_Transmit_FS((uint8_t*)buffer, 30);
	}
}

void lora_module_send_command(char *command, char *value) {

	char buffer[50] = {'\0'};
	uint8_t len = 0;
	uint8_t loop_count = 0;

	while(strstr(buffer, "ok") == NULL) {

		memset(buffer, '\0', 50);

		if(value != NULL) {
			len = sprintf(buffer, "%s %s\r\n", command, value);
			CDC_Transmit_FS((uint8_t*)buffer, 50);
		}
		else {
			len = sprintf(buffer, "%s\r\n", command);
			CDC_Transmit_FS((uint8_t*)buffer, 50);
		}

		HAL_UART_Transmit(&huart3, (uint8_t*)buffer, len, 100);

		memset(buffer, '\0', 50);
		HAL_UART_Receive(&huart3, (uint8_t*)buffer, 50, 200);

		CDC_Transmit_FS((uint8_t*)buffer, 50);

		if(loop_count >= 3) {
			break;
		}
		else {
			loop_count++;
		}

	}
}

void lora_module_join_otaa() {

	char buffer[50] = {'\0'};
	uint8_t len = 0;
	uint8_t i = 1;

	while(i) {

		len = sprintf(buffer, "%s\r\n", RN_JOIN_OTAA_MODE);
		HAL_UART_Transmit(&huart3, (uint8_t*)buffer, len, 100);
		memset(buffer, '\0', 50);
		if (HAL_UART_Receive(&huart3, (uint8_t*)buffer, 50, 1000) == HAL_TIMEOUT) {
			i = 0;
		}

		CDC_Transmit_FS((uint8_t*)buffer, 50);
	}

}
