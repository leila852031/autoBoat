/**
  ******************************************************************************
  * @file    Template/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-September-2013
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_conf.h"
/** @addtogroup Template
  * @{
  */ 

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void Boat( void* pvParameters );

int main( void )
{	
	
	RCC_Configuration();
//	TIM_Configuration();
	GPIO_Configuration();
	xTaskCreate( Boat, (signed char*)"Boat", 128, NULL, tskIDLE_PRIORITY+1, NULL );
	vTaskStartScheduler();
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
   // RCC Configuration
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
}

/**
  * @brief  configure the PD12~15 to Timers
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
    // GPIO Configuration
	// LED3 (Green): GPIO_Pin_13, LED4 (Red): GPIO_Pin_14
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
}

void Boat( void* pvParameters )
{
	GPIO_ToggleBits(GPIOG, GPIO_Pin_14);
	while(1)
	{
		GPIO_ToggleBits(GPIOG, GPIO_Pin_13);
		GPIO_ToggleBits(GPIOG, GPIO_Pin_14);

		vTaskDelay(1000);
	}
}
