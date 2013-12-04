/////UART1\UART2发送 接收/////////////////////////
#include<pic18.h>
#include<math.h>
#include"TCP_Convert_define_Init.h"
#include"TCP_Convert_W5200.h"

uchar RX1_REG,RX1_Receive;

void Uart1_TX(uchar temp_tx)
{
	while(TRMT1==0);//等待发送完成
	TXREG1 = temp_tx;
	NOP();
	NOP();
	while(TRMT1==0);//等待发送完成
	//LED2=!LED2;
	//TMR1IF=0;	
}

void Uart1_RX()
{
	//Test_led2=!Test_led2;
	//LED_Run=!LED_Run;
	NOP();
	RX1_Receive = RX1_REC_ERR;
	Uart1_TX(RX1_REG);
	
}
