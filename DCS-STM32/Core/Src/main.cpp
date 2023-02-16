/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.cpp
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "DcsBios.h"
#include "LCD_HD44780.h"
#include <string.h>
#include <time.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern "C" {
int __io_putchar(int ch) {
	if (ch == '\n') {
		__io_putchar('\r');
	}

	HAL_UART_Transmit(&huart3, (uint8_t*) &ch, 1, HAL_MAX_DELAY);

	return 1;
}
int _write(int file, char *ptr, int len) {
	return __io_putchar(*ptr);
}
}
void onIcpCom1BtnChange(unsigned int newValue) {
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}
void onClockCurrtimeHChange(unsigned int newValue) {

	//TODO: poprawna konwersja czasu z sekund na HH:MM:SS
	/*time_t currentTime = newValue;
	struct tm ts;

	//22513 = 12:07:33
	// Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
	ts = *localtime(&currentTime);
	//strftime(buf, sizeof(buf), "%a %Y-%m-%d", &ts);
	LCD_Cls();
	//LCD_Locate(0, 0);
	//LCD_String(buf);
	//strftime(buf, sizeof(buf), "%H:%M:%S", &ts);
	 */
	char buf[5] = {0};
	itoa(newValue,buf,10);
	LCD_Locate(0, 0);
	LCD_String(buf);

}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();
	MX_TIM5_Init();
	MX_TIM3_Init();
	/* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);

	// Inicjalizacja buttonow DCS
	DcsBios::Switch2Pos icpCom1Btn("ICP_COM1_BTN", ICP_COM1_BTN_GPIO_Port,
	ICP_COM1_BTN_Pin);
	DcsBios::Switch2Pos icpCom2Btn("ICP_COM2_BTN", ICP_COM2_BTN_GPIO_Port,
	ICP_COM2_BTN_Pin);
	DcsBios::Switch2Pos icpEntrBtn("ICP_ENTR_BTN", ICP_ENTR_BTN_GPIO_Port,
	ICP_ENTR_BTN_Pin);
	DcsBios::Switch2Pos icpIffBtn("ICP_IFF_BTN", ICP_IFF_BTN_GPIO_Port,
	ICP_IFF_BTN_Pin);
	DcsBios::Switch2Pos icpWxBtn("ICP_WX_BTN", ICP_WX_BTN_GPIO_Port,
	ICP_WX_BTN_Pin);
	DcsBios::Switch2Pos icpListBtn("ICP_LIST_BTN", ICP_LIST_BTN_GPIO_Port,
	ICP_LIST_BTN_Pin);
	DcsBios::Switch2Pos icpAaModeBtn("ICP_AA_MODE_BTN",
	ICP_AA_MODE_BTN_GPIO_Port, ICP_AA_MODE_BTN_Pin);
	DcsBios::Switch2Pos icpAgModeBtn("ICP_AG_MODE_BTN",
	ICP_AG_MODE_BTN_GPIO_Port, ICP_AG_MODE_BTN_Pin);

	// Enkoder
	DcsBios::RotaryEncoder icpRasterBrtKnb("ICP_RASTER_BRT_KNB", "-3200", "+3200", &htim5);

	// LED
	DcsBios::LED icpCom1BtnLed(0x4426, 0x0020, LD2_GPIO_Port, LD2_Pin);

	// Callback na zmiane czasu - przychodzi z DCS
	DcsBios::IntegerBuffer clockCurrtimeHBuffer(0x44f8, 0xffff, 0, onClockCurrtimeHChange);

	//Debugowe rzeczy
	const char *usartTest = "HAL_UART_Transmit: Hello. USART2 TEST...\r\n";
	const char *usartTest2 = "printf: Hello. USART3 TEST...\r\n";
	HAL_UART_Transmit(&huart2, (uint8_t*) usartTest, strlen(usartTest),	HAL_MAX_DELAY);
	printf(usartTest2);

	// Inicjalizacja LCD oraz DCSBiosu
	LCD_Init();
	DcsBios::setup(&huart2, &huart3); //UART2 to Serial po kablu, UART3 to serial na pinach PC4 i PC11
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	// Test ekranu
	LCD_Cls();
	LCD_Locate(0, 0);
	LCD_String("DCS-BIOS");
	HAL_Delay(1000);
	LCD_Locate(0, 1);
	LCD_String("GordonPeak mode");

	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		DcsBios::loop();
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1)
			!= HAL_OK) {
		Error_Handler();
	}

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSICalibrationValue = 0;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 40;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
