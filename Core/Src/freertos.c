/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "lora.h"

//RN settings OTAA connection
//static char *appEui = "0000000000000000";
//static char *appKey = "00000000000000000000000000000000";
//RN settings ABP connection
//static char *devAddr = "12A00000";
//static char *nwkSKey = "00000000000000000000000000000000";
//static char *appSKey = "00000000000000000000000000000000";

char *appEui = "70B3D57ED001B6D2";
char *appKey = "4836F6175167F6BAB5C1F51038DF0132";
char *hweui  = "00F55AE7491DFB47";

osThreadId defaultTaskHandle;
osThreadId serviceTaskHandle;

void StartDefaultTask(void const * argument);
void StartServiceTask(void const * argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of serviceTask */
  osThreadDef(serviceTask, StartServiceTask, osPriorityIdle, 0, 128);
  serviceTaskHandle = osThreadCreate(osThread(serviceTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();

  osDelay(3000);
  lora_module_reboot();
  osDelay(3000);

  lora_module_set_gpio("GPIO3", 1);
  lora_module_set_gpio("GPIO4", 1);
  lora_module_set_gpio("GPIO5", 1);

  osDelay(50);

  // Set the device address
  //CDC_Transmit_FS((uint8_t*)"RN_MAC_SET_DEV_EUI\r\n", sizeof("\r\n"));;
  lora_module_send_command(RN_MAC_RESET_CMD, NULL);
  osDelay(50);

  // Set the device address
  //CDC_Transmit_FS((uint8_t*)"RN_MAC_SET_DEV_EUI\r\n", sizeof("\r\n"));;
  lora_module_send_command(RN_MAC_SET_DEV_EUI, hweui);
  osDelay(50);

  // Set the network key
  //CDC_Transmit_FS((uint8_t*)"RN_MAC_SET_APP_KEY\r\n", sizeof("RN_MAC_SET_APP_KEY\r\n"));;
  lora_module_send_command(RN_MAC_SET_APP_KEY, appKey);
  osDelay(50);

  // Set the EUI
  //CDC_Transmit_FS((uint8_t*)"RN_MAC_SET_APP_EUI\r\n", sizeof("RN_MAC_SET_APP_EUI\r\n"));;
  lora_module_send_command(RN_MAC_SET_APP_EUI, appEui);
  osDelay(50);

  //CDC_Transmit_FS((uint8_t*)"RN_MAC_SET_PWRIDX\r\n", sizeof("RN_MAC_SET_PWRIDX\r\n"));;
  lora_module_send_command(RN_MAC_SET_PWRIDX, "1");
  osDelay(50);

  // Disable adaptive data rate
  //CDC_Transmit_FS((uint8_t*)"RN_MAC_SET_ADR_ON_CMD\r\n", sizeof("RN_MAC_SET_ADR_ON_CMD\r\n"));;
  lora_module_send_command(RN_MAC_SET_ADR_ON_CMD, "off");
  osDelay(50);

  // Disable automatic replies
  //CDC_Transmit_FS((uint8_t*)"RN_MAC_SET_AR_ON_CMD\r\n", sizeof("RN_MAC_SET_AR_ON_CMD\r\n"));;
  lora_module_send_command(RN_MAC_SET_AR_ON_CMD, "off");
  osDelay(50);

  // Save the mac details
  //CDC_Transmit_FS((uint8_t*)"RN_MAC_SAVE_CMD\r\n", sizeof("RN_MAC_SAVE_CMD\r\n"));;
  lora_module_send_command(RN_MAC_SAVE_CMD, NULL);
  osDelay(50);

  // Save the mac details
  //CDC_Transmit_FS((uint8_t*)"RN_JOIN_OTAA_MODE\r\n", sizeof("RN_JOIN_OTAA_MODE\r\n"));;
  //lora_module_send_command(RN_JOIN_OTAA_MODE, NULL);

  for(;;)
  {
	  lora_module_join_otaa();
	  osDelay(9000);

	  // Say hello world to the gateway
	  //osDelay(9000);
	  //lora_module_send_command(RN_MAC_TX_CMD, "cnf 1 48656c6c6f20576f726c6421");
  }
}

/* USER CODE BEGIN Header_StartServiceTask */
/**
* @brief Function implementing the serviceTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartServiceTask */
void StartServiceTask(void const * argument)
{
  /* USER CODE BEGIN StartServiceTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartServiceTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
