/*
 * lora.c
 *
 *  Created on: 30 Apr 2019
 *      Author: frazer
 */

#include "lora.h"

void lora_module_reboot() {

	char buffer[50] = {'\0'};
	uint8_t i = 0;

	while(i) {

		HAL_UART_Transmit(&huart3, (uint8_t*)RN_SYS_RESET, sizeof(RN_SYS_RESET), 100);
		if (HAL_UART_Receive(&huart3, (uint8_t*)buffer, 50, 5000) == HAL_TIMEOUT) {
			i = 1;
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

		CDC_Transmit_FS((uint8_t*)buffer, 30);
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

void lora_module_get_hweui(char* hweui) {

	char buffer[16] = {'0'};

	HAL_UART_Transmit(&huart3, (uint8_t*)RN_SYS_GET_HWEUI, sizeof(RN_SYS_GET_HWEUI), 100);
	HAL_UART_Receive(&huart3, (uint8_t*)buffer, 16, 500);
	CDC_Transmit_FS((uint8_t*)buffer, 16);

	strcpy(hweui, buffer);
}

uint8_t set_modem_config(char* setting, char* value) {

	char buffer[LORA_MAX_TRANSMIT_STRING] = {'\0'};
	uint8_t buffer_transmit_size = 0;

	buffer_transmit_size = sprintf(buffer, "%s %s \r\n", setting, value);

	if (HAL_UART_Transmit(&huart3, (uint8_t*)buffer, buffer_transmit_size, 100) ==  HAL_OK) {
		return 1;
	}
	else {
		return 0;
	}

}

uint8_t send_command(char *command) {

	char buffer[LORA_MAX_TRANSMIT_STRING] = {'\0'};
	uint8_t buffer_transmit_size = 0;

	// Transmit command to the modem
	HAL_UART_Transmit(&huart3, (uint8_t*)buffer, buffer_transmit_size, 1000);

	// Clear our buffer
	memset(buffer, '\0', LORA_MAX_TRANSMIT_STRING);

	HAL_UART_Receive(&huart3, (uint8_t*)buffer, LORA_MAX_TRANSMIT_STRING, 1000);

	CDC_Transmit_FS((uint8_t*)buffer, LORA_MAX_TRANSMIT_STRING);
	osDelay(10);

	if(strcmp(buffer, "ok")) {
		return LORA_OK;
	}
	else if(strcmp(buffer, "invalid_param")) {
		return LORA_INVALID_PARAM;
	}
	else {
		return LORA_UNKNOWN_ERROR;
	}

}
