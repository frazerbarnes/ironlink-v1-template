/*
 * lora.h
 *
 *  Created on: 30 Apr 2019
 *      Author: frazer
 */

#ifndef INC_LORA_H_
#define INC_LORA_H_

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "usbd_cdc_if.h"
#include "usart.h"

#define LORA_MAX_TRANSMIT_STRING 30

#define RN_JOIN_OTAA_MODE           "mac join otaa"
#define RN_JOIN_ABP_MODE            "mac join abp"

// SYS Commands
#define RN_SYS_SLEEP                "sys sleep"			//Sleep in ms. From 100 to 4294967296
#define RN_SYS_GET_VER              "sys get ver"			//Returns the information on hardware platform, firmware version, release date.
#define RN_SYS_FACTORY_RESET        "sys factoryRESET"		//Reset all configurations to factory default
#define RN_SYS_RESET                "sys reset"				//Reboot module

#define RN_SYS_GET_VDD              "sys get vdd"			//Get the mV of the module. From 0 - 3600
#define RN_SYS_GET_HWEUI            "sys get hweui"			//Get the HW eui address of the module
#define RN_SYS_SET_PIN              "sys set pindig"		//Set PIN. GPIO0 - GPIO14, UART_CTS, UART_RTS, TEST0, TEST1. to 0 or 1.

// MAC Commands
#define RN_MAC_GET_APP_EUI          "mac get appeui"		//Get current programmed APP eui
#define RN_MAC_GET_STATUS           "mac get status"		//
#define RN_MAC_RESET_CMD            "mac reset 868"			//Reset all configurations for band 868
#define RN_MAC_TX_CMD               "mac tx"				//Send data to Lora network. cnf (confirmed) or uncnf (unconfirmed), port number from 1 to 223, data
#define RN_MAC_JOIN_CMD             "mac join"				//Join Lora network. OTAA (over-the-air activation) or ABP (activation by personalization)
#define RN_MAC_SAVE_CMD             "mac save"				//Save the configuration (band, deveui, appeui, appkey, nwkskey, appskey, devaddr, ch).
#define RN_MAC_PAUSE_CMD            "mac pause"				//Pause LoraWan stack in ms (must be done if you want to change a config while you are already connected to Lora network). From 0 to 4294967295
#define RN_MAC_RESUME_CMD           "mac resume"			//Resume LoraWan stack

#define RN_MAC_SET_DEV_ADDR         "mac set devaddr"		//Set device address. from 00000000 to FFFFFFFF
#define RN_MAC_SET_DEV_EUI          "mac set deveui"		//Set device identifier. 8-byte HEX
#define RN_MAC_SET_APP_EUI          "mac set appeui"
#define RN_MAC_SET_NWK_SESS_KEY     "mac set nwkskey"
#define RN_MAC_SET_APP_SESS_KEY     "mac set appskey"
#define RN_MAC_SET_APP_KEY          "mac set appkey"
#define RN_MAC_GET_STATUS           "mac get status"
#define RN_MAC_SET_DATARATE         "mac set dr"
#define RN_MAC_SET_ADR_ON_CMD       "mac set adr"
#define RN_MAC_SET_AR_ON_CMD        "mac set ar"

#define RN_MAC_SET_PWRIDX			 "mac set pwridx"

// Radio command
#define RN_RADIO_GET_MODE           "radio get mod"
#define RN_RADIO_SET_MODE           "radio set mod"
#define RN_RADIO_MODE_LEN           18
#define RN_RADIO_SET_PWR            "radio set pwr"
#define RN_RADIO_GET_PWR            "radio get pwr"
#define RN_RADIO_SET_SYNC           "radio set sync"
#define RN_LORA_MODE                "lora"
#define RN_FSK_MODE                 "fsk"

#define LORA_RESPONSE_TIMEOUT	1
#define LORA_OK					2
#define LORA_INVALID_PARAM		3
#define LORA_UNKNOWN_ERROR		4

void lora_module_reboot();
void lora_module_set_gpio(char *gpio, uint8_t state);
void lora_module_send_command(char *command, char *value);
void lora_module_join_otaa();

#endif /* INC_LORA_H_ */
