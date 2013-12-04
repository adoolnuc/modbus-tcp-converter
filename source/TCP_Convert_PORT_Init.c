////TCP_Convert IO 设置///////////////////////////
#include<pic18.h>
#include<math.h>
#include"TCP_Convert_define_Init.h"
#include"TCP_Convert_W5200.h"



void port_init(void) 
{ 
	////IO输入 输出设置////////////////////////////////////////////////////////////
	Test_led0_SET = OUTPUT;   // MCU 输出口     	
	Test_led1_SET = OUTPUT;   // MCU 输出口    	
	Test_led2_SET = OUTPUT;   // MCU 输出口 		
	Test_led3_SET = OUTPUT;   // MCU 输出口 		
	LED_Run_SET   = OUTPUT;   // MCU 输出口   	
	                        
	ETH_SPI_INT_SET = INPUT;	// MCU 输入口	        
	ETH_OUT_SPI2_CLK2_SET = OUTPUT;   // MCU 输出口 	
	ETH_OUT_SPI2_MISO2_SET = INPUT;	// MCU 输入口	
	ETH_OUT_SPI2_MOSI2_SET = OUTPUT;   // MCU 输出口 	
	ETH_OUT_SPI2_CS2_SET = OUTPUT;   // MCU 输出口 	
	ETH_RST_SET = OUTPUT;   // MCU 输出口 		
	                        
	ETH_OUT_INT2_SET = INPUT;	// MCU 输入口	
	ETH_IN_INT1_SET = INPUT;	// MCU 输入口	        
	ETH_IN_SPI1_CS1_SET = OUTPUT;   // MCU 输出口 	
	ETH_IN_SPI1_CLK1_SET = OUTPUT;   // MCU 输出口 	
	ETH_IN_SPI1_MISO1_SET = INPUT;	// MCU 输入口	
	ETH_IN_SPI1_MOSI1_SET = OUTPUT;   // MCU 输出口 	
	MCU_TXD_SET = INPUT;   // MCU 输出口 		
	MCU_RXD_SET = INPUT;	// MCU 输入口	
	
	TRISA5 =0;	
	TRISA7 = 0;
	PORTAbits.RA5 =0;
	PORTAbits.RA7 =0;
	/////////////////////////////////////////////////////////////////////////////// 	
	OSCCON = 0xf0;//内部16M时钟，直接选择内部振荡器
	PLLEN = 1;//使能4XPLL
	////////////////////////////////////////////////////////////////////	
	PMD0 = 0xbf;//使能UART1，禁止UART2，禁止TMR1\2\3\4\5\6
	PMD1 = 0x1f;//使能SPI1、SPI2，禁止CCP1、2、3、4、5
	PMD2 = 0x0f;//禁止CTMU，禁止CMP1、2,禁止ADC
	
	TMR1MD = 0;
	//////////////////////////////////////////////////////////////////////	
 	WPUB = 0;	// PORTB禁止上拉电阻
 	IOCB = 0;  // 禁止电平变化中断	 
	////AD、数字IO设置//////////////////////////////////////////////////////////////	
	ANSELA = 0x00;//禁止模拟输入
	ANSELB = 0x00;
	ANSELC = 0x00;
	///////////////////////////////////////////////////////////////////////////////
	
	////URAT1设置////////////////////////////////////////////////////////////
	TXSTA1 = 0x24;//异步，使能发送
	RCSTA1 = 0x90;//使能串口，使能接收
	BAUDCON1 = 0x48;
	SPBRGH1 = 0x06;
	SPBRG1 = 0x82;//9600bps  FOSC=64M
	RC1IE =1;//使能接收中断
	//CREN1 =1;
	///////////////////////////////////////////////////////////////////////////////
	
	//////SPI设置///////////////////////////////////////////////////////////////////
	SSP1STAT = 0x40;//输出时间中间采样,上升沿采样，下降沿输出
	SSP1CON1 = 0x02;//CLK=FOSC/16=4M
	SSP1CON1bits.SSPEN =1;
	
	SSP2STAT = 0x40;//输出时间中间采样,上升沿采样，下降沿输出
	SSP2CON1 = 0x02;//CLK=FOSC/4=16M
	SSP2CON1bits.SSPEN=1;
	/////////////////////////////////////////////////////////////////////////////////
	TMR0H = 0x85;
	TMR0L = 0xee;//500ms定时器
	//TMR0H = 0xe7;
	//TMR0L = 0x95;//100ms定时器
	//TMR0H = 0xf3;
	//TMR0L = 0xca;//50ms定时器
	T0CON = 0x87;//使能TIMER0 ， 256分频
	////////////////////////////////////////////////////////////////////////////
	INTCON = 0x70;
	//INT0IE = 1;
	//TMR0IE =1;
	
	INTCON2 = 0xb5;//INT0 下降沿中断
	
	//timer 1
	TMR1H  = 0x15 ;
	TMR1L  = 0x9f ;//30ms 30msX3=90ms用于与PLC通讯
	T1CON  = 0x33 ;
	TMR1IF = 0;
	TMR1IE = 1;
	
	
}

void PORT_State_Init()
{
	ETH_RST = 0;
	Test_led0 = LED_OFF;
	Test_led1 = LED_OFF;			
	Test_led2 = LED_OFF;    			
	Test_led3 = LED_OFF;				
	
	LED_Run	=  LED_OFF;	
	RX1_Receive = RX1_REC_ERR;

	ETH_IN_MODE = TCP_SERVER;
	ETH_OUT_MODE = TCP_CLIENT;
	ETH_IN_Event_en = 0;
	ETH_OUT_Event_en = 0;
	ETH_OUT_PHY_Link_STA = nochange;
	ETH_IN_PHY_Link_STA = nochange;
	ETH_OUT_Link_Status = PHY_Link_ERR;
	ETH_IN_Link_Status = PHY_Link_ERR;
	
	TP_Timer=TIME_OFF;
	Work_stutas = normal_status;
	test_sync = ETH_OUT;
	Module_change_state = nochange;
	
	TIMER1_stutas = TIME_OFF;
	TIMER1_count = 0;
	
	ETH_OUT_function =0;
	list2_function1_add=25120;
}

void delay_1ms(uint time)//1ms delay
{
	uint i,k;
	for(k = 0; k< time; k++)
	{
		for(i = 0; i<1777; i++)
		{
			NOP();
		}
	}		
}