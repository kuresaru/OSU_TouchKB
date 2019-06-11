/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "common.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "km.h"

// __IO uint8_t PrevXferComplete = 1;
RCC_ClocksTypeDef RCC_ClockFreq;

u8 sendReset = 0;

//USB使能连接/断线
//enable:0,断开
//       1,允许连接	   
void USB_Port_Set(u8 enable)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //使能PORTA时钟		 
	if(enable)_SetCNTR(_GetCNTR()&(~(1<<1)));//退出断电模式
	else
	{	  
		_SetCNTR(_GetCNTR()|(1<<1));  // 断电模式
		GPIOA->CRH&=0XFFF00FFF;
		GPIOA->CRH|=0X00033000;
		GPIO_ResetBits(GPIOA, GPIO_Pin_12);
	}
}  

int main(void)
{

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//LED0
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//LED1
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_13;//KEY0 KEY1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIOA->BRR = GPIO_Pin_8;
  GPIOD->BRR = GPIO_Pin_2;
  Delay_ms(1000);
  GPIOA->BSRR = GPIO_Pin_8;
  GPIOD->BSRR = GPIO_Pin_2;

  USB_Port_Set(0); 	//USB先断开
	Delay_ms(700);
	USB_Port_Set(1);	//USB再次连接
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();
  
  while (1)
  {
    if (!(GPIOC->IDR & (1 << 1)))
    {
      if (!(GPIOC->IDR & (1 << 13)))
      {
        Keyboard_Send(0, KEY_Z, KEY_X, 0, 0, 0, 0);
        sendReset = 1;
      }
      else
      {
        Keyboard_Send(0, KEY_Z, 0, 0, 0, 0, 0);
        sendReset = 1;
      }
    } 
    else if (!(GPIOC->IDR & (1 << 13)))
    {
      Keyboard_Send(0, KEY_X, 0, 0, 0, 0, 0);
      sendReset = 1;
    }
    else if (sendReset)
    {
      Keyboard_SendReset();
      sendReset = 0;
    }
    Delay_ms(1);
  }
}

