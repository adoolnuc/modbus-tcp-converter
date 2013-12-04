////TCP_Convert IO ����///////////////////////////
#include<pic18.h>
#include<math.h>
#include"TCP_Convert_define_Init.h"
#include"TCP_Convert_W5200.h"



void port_init(void) 
{ 
	////IO���� �������////////////////////////////////////////////////////////////
	Test_led0_SET = OUTPUT;   // MCU �����     	
	Test_led1_SET = OUTPUT;   // MCU �����    	
	Test_led2_SET = OUTPUT;   // MCU ����� 		
	Test_led3_SET = OUTPUT;   // MCU ����� 		
	LED_Run_SET   = OUTPUT;   // MCU �����   	
	                        
	ETH_SPI_INT_SET = INPUT;	// MCU �����	        
	ETH_OUT_SPI2_CLK2_SET = OUTPUT;   // MCU ����� 	
	ETH_OUT_SPI2_MISO2_SET = INPUT;	// MCU �����	
	ETH_OUT_SPI2_MOSI2_SET = OUTPUT;   // MCU ����� 	
	ETH_OUT_SPI2_CS2_SET = OUTPUT;   // MCU ����� 	
	ETH_RST_SET = OUTPUT;   // MCU ����� 		
	                        
	ETH_OUT_INT2_SET = INPUT;	// MCU �����	
	ETH_IN_INT1_SET = INPUT;	// MCU �����	        
	ETH_IN_SPI1_CS1_SET = OUTPUT;   // MCU ����� 	
	ETH_IN_SPI1_CLK1_SET = OUTPUT;   // MCU ����� 	
	ETH_IN_SPI1_MISO1_SET = INPUT;	// MCU �����	
	ETH_IN_SPI1_MOSI1_SET = OUTPUT;   // MCU ����� 	
	MCU_TXD_SET = INPUT;   // MCU ����� 		
	MCU_RXD_SET = INPUT;	// MCU �����	
	
	TRISA5 =0;	
	TRISA7 = 0;
	PORTAbits.RA5 =0;
	PORTAbits.RA7 =0;
	/////////////////////////////////////////////////////////////////////////////// 	
	OSCCON = 0xf0;//�ڲ�16Mʱ�ӣ�ֱ��ѡ���ڲ�����
	PLLEN = 1;//ʹ��4XPLL
	////////////////////////////////////////////////////////////////////	
	PMD0 = 0xbf;//ʹ��UART1����ֹUART2����ֹTMR1\2\3\4\5\6
	PMD1 = 0x1f;//ʹ��SPI1��SPI2����ֹCCP1��2��3��4��5
	PMD2 = 0x0f;//��ֹCTMU����ֹCMP1��2,��ֹADC
	
	TMR1MD = 0;
	//////////////////////////////////////////////////////////////////////	
 	WPUB = 0;	// PORTB��ֹ��������
 	IOCB = 0;  // ��ֹ��ƽ�仯�ж�	 
	////AD������IO����//////////////////////////////////////////////////////////////	
	ANSELA = 0x00;//��ֹģ������
	ANSELB = 0x00;
	ANSELC = 0x00;
	///////////////////////////////////////////////////////////////////////////////
	
	////URAT1����////////////////////////////////////////////////////////////
	TXSTA1 = 0x24;//�첽��ʹ�ܷ���
	RCSTA1 = 0x90;//ʹ�ܴ��ڣ�ʹ�ܽ���
	BAUDCON1 = 0x48;
	SPBRGH1 = 0x06;
	SPBRG1 = 0x82;//9600bps  FOSC=64M
	RC1IE =1;//ʹ�ܽ����ж�
	//CREN1 =1;
	///////////////////////////////////////////////////////////////////////////////
	
	//////SPI����///////////////////////////////////////////////////////////////////
	SSP1STAT = 0x40;//���ʱ���м����,�����ز������½������
	SSP1CON1 = 0x02;//CLK=FOSC/16=4M
	SSP1CON1bits.SSPEN =1;
	
	SSP2STAT = 0x40;//���ʱ���м����,�����ز������½������
	SSP2CON1 = 0x02;//CLK=FOSC/4=16M
	SSP2CON1bits.SSPEN=1;
	/////////////////////////////////////////////////////////////////////////////////
	TMR0H = 0x85;
	TMR0L = 0xee;//500ms��ʱ��
	//TMR0H = 0xe7;
	//TMR0L = 0x95;//100ms��ʱ��
	//TMR0H = 0xf3;
	//TMR0L = 0xca;//50ms��ʱ��
	T0CON = 0x87;//ʹ��TIMER0 �� 256��Ƶ
	////////////////////////////////////////////////////////////////////////////
	INTCON = 0x70;
	//INT0IE = 1;
	//TMR0IE =1;
	
	INTCON2 = 0xb5;//INT0 �½����ж�
	
	//timer 1
	TMR1H  = 0x15 ;
	TMR1L  = 0x9f ;//30ms 30msX3=90ms������PLCͨѶ
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