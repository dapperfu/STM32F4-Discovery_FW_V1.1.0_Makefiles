/********************************************************************************/
/*!
	@file			uart_support.c
	@author         Nemui Trinomius (http://nemuisan.blog.bai.ne.jp)
    @version        2.00
    @date           2011.09.14
	@brief          Based on ST Microelectronics's Sample Thanks!

    @section HISTORY
		2011.06.12	V1.00	Start Here.
		2011.09.14	V2.00	Expand fifo buffer uint8_t to uint16_t
		
    @section LICENSE
		BSD License. See Copyright.txt
*/
/********************************************************************************/

/*
 UART2TX : PA2
 UART2RX : PA3
 UART3TX : PD8
 UART3RX : PD9
 UART4TX : PA0
 UART4RX : PA1

 UART3 は GPS用
*/

/* Includes ------------------------------------------------------------------*/
#include "uart_support.h"

/* Defines -------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
// static USART_TypeDef* UART;
// static USART_Buffer_t* pUSART_Buf;
USART_Buffer_t USART1_Buf;
USART_Buffer_t USART2_Buf;
USART_Buffer_t USART3_Buf;
USART_Buffer_t UART4_Buf;

/* Constants -----------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

/**************************************************************************/
/*! 
    Initialize UART.
*/
/**************************************************************************/
/* Initialize serial console */
void conio_init(uint32_t port, uint32_t baudrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure; // 2012.05.23 ちょっと心配
  
	/* Turn on USART*/
	switch (port)
	{
		case 1 :
//			UART = (USART_TypeDef *) USART1_BASE;

			/* Enable GPIO clock */
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
			/* Enable UART clock */
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
			/* Connect PXx to USARTx_Tx*/
			GPIO_PinAFConfig(GPIOA,  GPIO_PinSource9, GPIO_AF_USART1);
			/* Connect PXx to USARTx_Rx*/
			GPIO_PinAFConfig(GPIOA,  GPIO_PinSource10, GPIO_AF_USART1);

			/* Configure USART Tx as alternate function  */
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);

			/* Configure USART Rx as alternate function  */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
			GPIO_Init(GPIOA, &GPIO_InitStructure);

		
			/* Configure one bit for preemption priority */
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

			/* Enable the USART1 Interrupt */
			NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);

			USART_StructInit(&USART_InitStructure);
			USART_InitStructure.USART_BaudRate = baudrate;
			USART_Init((USART_TypeDef *)USART1_BASE, &USART_InitStructure);

			/* Init Ring Buffer */
//			pUSART_Buf = &USART1_Buf;
			USART1_Buf.RX_Tail = 0;
			USART1_Buf.RX_Head = 0;
			USART1_Buf.TX_Tail = 0;
			USART1_Buf.TX_Head = 0;

			/* Enable USART1 Receive interrupts */
			USART_ITConfig((USART_TypeDef *)USART1_BASE, USART_IT_RXNE, ENABLE);
			USART_Cmd((USART_TypeDef *)USART1_BASE, ENABLE);
	
		break;
 
		case 2 :
// 			UART = (USART_TypeDef *) USART2_BASE;

			/* Enable GPIO clock */
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
			/* Enable UART clock */
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
			/* Connect PXx to USARTx_Tx*/
			GPIO_PinAFConfig(GPIOA,  GPIO_PinSource2, GPIO_AF_USART2);
			/* Connect PXx to USARTx_Rx*/
			GPIO_PinAFConfig(GPIOA,  GPIO_PinSource3, GPIO_AF_USART2);

			/* Configure USART Tx as alternate function  */
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);

			/* Configure USART Rx as alternate function  */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			GPIO_Init(GPIOA, &GPIO_InitStructure);

		
			/* Configure one bit for preemption priority */
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

			/* Enable the USART1 Interrupt */
			NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);

			USART_StructInit(&USART_InitStructure);
			USART_InitStructure.USART_BaudRate = baudrate;
			USART_Init((USART_TypeDef *)USART2_BASE, &USART_InitStructure);

			/* Init Ring Buffer */
//			pUSART_Buf = &USART2_Buf;
			USART2_Buf.RX_Tail = 0;
			USART2_Buf.RX_Head = 0;
			USART2_Buf.TX_Tail = 0;
			USART2_Buf.TX_Head = 0;

			/* Enable USART Receive interrupts */
			USART_ITConfig((USART_TypeDef *)USART2_BASE, USART_IT_RXNE, ENABLE);
			USART_Cmd((USART_TypeDef *)USART2_BASE, ENABLE);
			
		break;
	
		case 3 :
// 			UART = (USART_TypeDef *) USART3_BASE;

			/* Enable GPIO clock */
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
			/* Enable UART clock */
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
			/* Connect PXx to USARTx_Tx*/
			GPIO_PinAFConfig(GPIOD,  GPIO_PinSource8, GPIO_AF_USART3);
			/* Connect PXx to USARTx_Rx*/
			GPIO_PinAFConfig(GPIOD,  GPIO_PinSource9, GPIO_AF_USART3);

			/* Configure USART Tx as alternate function  */
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOD, &GPIO_InitStructure);

			/* Configure USART Rx as alternate function  */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
			GPIO_Init(GPIOD, &GPIO_InitStructure);

		
			/* Configure one bit for preemption priority */
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

			/* Enable the USART1 Interrupt */
			NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);

			USART_StructInit(&USART_InitStructure);
			USART_InitStructure.USART_BaudRate = baudrate;
			USART_Init((USART_TypeDef *)USART3_BASE, &USART_InitStructure);

 			/* Init Ring Buffer */
//			pUSART_Buf = &USART3_Buf;
			USART3_Buf.RX_Tail = 0;
			USART3_Buf.RX_Head = 0;
			USART3_Buf.TX_Tail = 0;
			USART3_Buf.TX_Head = 0;

			/* Enable USART Receive interrupts */
			USART_ITConfig((USART_TypeDef *)USART3_BASE, USART_IT_RXNE, ENABLE);
			USART_Cmd((USART_TypeDef *)USART3_BASE, ENABLE);
			
		break;

		case 4 :
// 			UART = (USART_TypeDef *) UART4_BASE;

			/* Enable GPIO clock */
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
			/* Enable UART clock */
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	
			/* Connect PXx to USARTx_Tx*/
			GPIO_PinAFConfig(GPIOA,  GPIO_PinSource0, GPIO_AF_UART4);
			/* Connect PXx to USARTx_Rx*/
			GPIO_PinAFConfig(GPIOA,  GPIO_PinSource1, GPIO_AF_UART4);

			/* Configure USART Tx as alternate function  */
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);

			/* Configure USART Rx as alternate function  */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
			GPIO_Init(GPIOA, &GPIO_InitStructure);

		
			/* Configure one bit for preemption priority */
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

			/* Enable the USART1 Interrupt */
			NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);

			USART_StructInit(&USART_InitStructure);
			USART_InitStructure.USART_BaudRate = baudrate;
			USART_Init((USART_TypeDef *)UART4_BASE, &USART_InitStructure);

			/* Init Ring Buffer */
//			pUSART_Buf = &UART4_Buf;
			UART4_Buf.RX_Tail = 0;
			UART4_Buf.RX_Head = 0;
			UART4_Buf.TX_Tail = 0;
			UART4_Buf.TX_Head = 0;

			/* Enable USART Receive interrupts */
			USART_ITConfig((USART_TypeDef *)UART4_BASE, USART_IT_RXNE, ENABLE);
			USART_Cmd((USART_TypeDef *)UART4_BASE, ENABLE);
		break;

	}

}

/**************************************************************************/
/*! 
    Check UART TX Buffer Empty.
*/
/**************************************************************************/
bool USART_TXBuffer_FreeSpace(USART_Buffer_t* USART_buf)
{
	/* Make copies to make sure that volatile access is specified. */
	uint16_t tempHead = (USART_buf->TX_Head + 1) & (UART_BUFSIZE-1);
	uint16_t tempTail = USART_buf->TX_Tail;

	/* There are data left in the buffer unless Head and Tail are equal. */
	return (tempHead != tempTail);
}

/**************************************************************************/
/*! 
    Put Bytedata with Buffering.
*/
/**************************************************************************/
bool USART_TXBuffer_PutByte(uint32_t port,USART_Buffer_t* USART_buf, uint8_t data)
{

	uint16_t tempTX_Head;
	bool TXBuffer_FreeSpace;
	switch(port) {
	  case 1:
		TXBuffer_FreeSpace = USART_TXBuffer_FreeSpace(USART_buf);
		if(TXBuffer_FreeSpace) {
		  	tempTX_Head = USART_buf->TX_Head;
			__disable_irq();
		  	USART_buf->TX[tempTX_Head]= data;
			/* Advance buffer head. */
			USART_buf->TX_Head = (tempTX_Head + 1) & (UART_BUFSIZE-1);
			__enable_irq();
			/* Enable TXE interrupt. */
			USART_ITConfig((USART_TypeDef *) USART1_BASE, USART_IT_TXE, ENABLE);
		}
		return TXBuffer_FreeSpace;
		break;
	  case 2:
		TXBuffer_FreeSpace = USART_TXBuffer_FreeSpace(USART_buf);
		if(TXBuffer_FreeSpace) {
		  	tempTX_Head = USART_buf->TX_Head;
			__disable_irq();
		  	USART_buf->TX[tempTX_Head]= data;
			/* Advance buffer head. */
			USART_buf->TX_Head = (tempTX_Head + 1) & (UART_BUFSIZE-1);
			__enable_irq();
			/* Enable TXE interrupt. */
			USART_ITConfig((USART_TypeDef *) USART2_BASE, USART_IT_TXE, ENABLE);
		}
		return TXBuffer_FreeSpace;
		break;
	  case 3:
		TXBuffer_FreeSpace = USART_TXBuffer_FreeSpace(USART_buf);
		if(TXBuffer_FreeSpace) {
		  	tempTX_Head = USART_buf->TX_Head;
			__disable_irq();
		  	USART_buf->TX[tempTX_Head]= data;
			/* Advance buffer head. */
			USART_buf->TX_Head = (tempTX_Head + 1) & (UART_BUFSIZE-1);
			__enable_irq();
			/* Enable TXE interrupt. */
			USART_ITConfig((USART_TypeDef *) USART3_BASE, USART_IT_TXE, ENABLE);
		}
		return TXBuffer_FreeSpace;
		break;
	  case 4:
		TXBuffer_FreeSpace = USART_TXBuffer_FreeSpace(USART_buf);
		if(TXBuffer_FreeSpace) {
		  	tempTX_Head = USART_buf->TX_Head;
			__disable_irq();
		  	USART_buf->TX[tempTX_Head]= data;
			/* Advance buffer head. */
			USART_buf->TX_Head = (tempTX_Head + 1) & (UART_BUFSIZE-1);
			__enable_irq();
			/* Enable TXE interrupt. */
			USART_ITConfig((USART_TypeDef *) UART4_BASE, USART_IT_TXE, ENABLE);
		}
		return TXBuffer_FreeSpace;
		break;
	}

	return false; // ?
}

/**************************************************************************/
/*! 
    Check UART RX Buffer Empty.
*/
/**************************************************************************/
bool USART_RXBufferData_Available(USART_Buffer_t* USART_buf)
{
	/* Make copies to make sure that volatile access is specified. */
	uint16_t tempHead = USART_buf->RX_Head;
	uint16_t tempTail = USART_buf->RX_Tail;

	/* There are data left in the buffer unless Head and Tail are equal. */
	return (tempHead != tempTail);
}

/**************************************************************************/
/*! 
    Get Bytedata with Buffering.
*/
/**************************************************************************/
uint8_t USART_RXBuffer_GetByte(USART_Buffer_t* USART_buf)
{
	uint8_t ans;

	__disable_irq();
	ans = (USART_buf->RX[USART_buf->RX_Tail]);

	/* Advance buffer tail. */
	USART_buf->RX_Tail = (USART_buf->RX_Tail + 1) & (UART_BUFSIZE-1);
	
	__enable_irq();

	return ans;
}

/**************************************************************************/
/*! 
    High Level function.
*/
/**************************************************************************/
/* Send 1 character */
inline void putch_p(uint32_t port,uint8_t data)
{
#if 0
	/* Polling version */
	while (!(UART->SR & USART_FLAG_TXE));
	UART->DR = c;
#endif
	/* Interrupt Version */

	switch (port) {
	  case 1 :
		while(!USART_TXBuffer_FreeSpace(&USART1_Buf));
		USART_TXBuffer_PutByte(port,&USART1_Buf,data);
		break;
	  case 2 :
		while(!USART_TXBuffer_FreeSpace(&USART2_Buf));
		USART_TXBuffer_PutByte(port,&USART2_Buf,data);
		break;
	  case 3 :
		while(!USART_TXBuffer_FreeSpace(&USART3_Buf));
		USART_TXBuffer_PutByte(port,&USART3_Buf,data);
		break;
	  case 4 :
		while(!USART_TXBuffer_FreeSpace(&UART4_Buf));
		USART_TXBuffer_PutByte(port,&UART4_Buf,data);
		break;
	}
}

void putch(uint8_t data)
{
	putch_p(UART_DEFAULT_NUM,data);
}

/**************************************************************************/
/*! 
    High Level function.
*/
/**************************************************************************/
/* Receive 1 character */
uint8_t getch_p(uint32_t port)
{
	switch (port) {
	  case 1 :
		if (USART_RXBufferData_Available(&USART1_Buf))
			return USART_RXBuffer_GetByte(&USART1_Buf);
		else
			return false;
		break;
	  case 2 :
		if (USART_RXBufferData_Available(&USART2_Buf))
			return USART_RXBuffer_GetByte(&USART2_Buf);
		else
			return false;
		break;
	  case 3 :
		if (USART_RXBufferData_Available(&USART3_Buf))
			return USART_RXBuffer_GetByte(&USART3_Buf);
		else
			return false;
		break;
	  case 4 :
		if (USART_RXBufferData_Available(&UART4_Buf))
			return USART_RXBuffer_GetByte(&UART4_Buf);
		else
			return false;
		break;
	}
	return 0; // ?
}

uint8_t getch(void)
{
	return getch_p(UART_DEFAULT_NUM);
}

/**************************************************************************/
/*! 
    High Level function.
*/
/**************************************************************************/
/* Return 1 if key pressed */
uint8_t keypressed(uint32_t port)
{
	switch (port) {
	  case 1 :
		return (USART_RXBufferData_Available(&USART1_Buf));
	  case 2 :
		return (USART_RXBufferData_Available(&USART2_Buf));
	  case 3 :
		return (USART_RXBufferData_Available(&USART3_Buf));
	  case 4 :
		return (USART_RXBufferData_Available(&UART4_Buf));
	}
	return 0; // ?
  /*return (UART->SR & USART_FLAG_RXNE);*/
}

/**************************************************************************/
/*! 
    High Level function.
*/
/**************************************************************************/
/* Send a string */
void cputs(char *s)
{
  while (*s)
    putch(*s++);
}

/**************************************************************************/
/*! 
    High Level function.
*/
/**************************************************************************/
/* Receive a string, with rudimentary line editing */
void cgets(uint32_t port,char *s, int bufsize)
{
  char *p;
  int c;

  memset(s, 0, bufsize);

  p = s;

  for (p = s; p < s + bufsize-1;)
  {
    /* 20090521Nemui */
	do{		
		c = getch_p(port);
	}while(c == false);
	/* 20090521Nemui */
    switch (c)
    {
      case '\r' :
      case '\n' :
        putch_p(port,'\r');
        putch_p(port,'\n');
        *p = '\n';
        return;

      case '\b' :
        if (p > s)
        {
          *p-- = 0;
          putch_p(port,'\b');
          putch_p(port,' ');
          putch_p(port,'\b');
        }
        break;

      default :
        putch_p(port,c);
        *p++ = c;
        break;
    }
  }

  return;
}

/* End Of File ---------------------------------------------------------------*/
