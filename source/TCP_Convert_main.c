// MCU : Microchip high performance 8 bit MCU :PIC18F65K80
//FOSC =64M
#include<pic18.h>
#include<math.h>
#include"TCP_Convert_define_Init.h"
#include"TCP_Convert_W5200.h"
#include "uart.h"

 //__CONFIG1H(IESO_OFF&FCMEN_OFF&PRICLKEN_ON&PLLCFG_OFF&FOSC_INTIO7&BORV_190&BOREN_OFF&PWRTEN_ON&WDTPS_32768&WDTEN_SWON&);//芯片配置字

/////////////////////////////////////////////////////////////

uchar Work_stutas,test_sync,Module_change_state;
uchar TP_Timer;
uchar ETH_IN_Event_en;
uchar ETH_OUT_Event_en;
uchar ETH_IN_PHY_Link_STA,ETH_OUT_PHY_Link_STA;
bank3 uchar net_switch = OPEN;
extern UART_Obj *hUart;
void init_test_val();

uchar TIMER1_count,TIMER1_stutas;

void interrupt ISR_Event(void)
{
	if(RC1IE&&RC1IF)
	{
		RC1IF = 0;
		Test_led3 = !Test_led3;
		//INT0IE = 0;
		net_switch = CLOSED;		
		
		/*缓存数据*/
		*(hUart->r_w++) = RCREG1; /*读数据*/
		
		/*判断写指针是否到达接收缓冲末尾*/
		if(hUart->r_w >= hUart->r_e) hUart->r_w = hUart->rbuf;

		/*判断缓冲是否满*/
		if(hUart->r_w == hUart->r_r)
		{
			//丢弃最早的一个字节
			hUart->r_r++;
			if(hUart->r_r >= hUart->r_e)
			{
				hUart->r_r = hUart->rbuf;
			}
		}
		
		/*数据长度*/
		hUart->rlen = (hUart->r_w - hUart->r_r);
		if(hUart->rlen < 0){
			hUart->rlen += UART_BUF_LEN;
		}
		
		//TXREG1 = (unsigned )hUart->rlen & 0xff;
		//INT0IE = 1;
	}
	
	if(INT0IE&&INT0IF)
	{		
		INT0IF = 0;
		//LED_Run != LED_Run;

		if(ETH_IN_INT1==0)
		{
			INT0IE = 0;
			ETH_IN_Event_en=1;
		}
		else if(ETH_OUT_INT2==0)
		{
			INT0IE = 0;
			ETH_OUT_Event_en =1;
		}	
	}
	
	if(TMR0IE&&TMR0IF)
	{
		TMR0IF = 0;	
		TMR0IE = 0;
		Test_led0 = !Test_led0;
		TP_Timer=TIME_OUT;		
	}	
	
	if(TMR1IE&&TMR1IF)//50ms
	{
		TMR1IF =0;
		TMR1ON = 0 ;
		//CLRWDT();
		if(TIMER1_count<3)//90ms
		{
			TIMER1_count = TIMER1_count + 1;
			TMR1H  = 0x15 ;
			TMR1L  = 0x9f ;//30ms 30msX3=90ms用于与PLC通讯
			T1CON  = 0x33 ;	
		}
		else
		{
			TIMER1_stutas = TIME_OUT;
			TIMER1_count = 0;
		}	
	}	
}	

void main()
{ 	
	uchar i;
	port_init();  	// IO 口初始化
	PORT_State_Init();
	init_uart();
	///////////////////////////////////////////
	net_switch = OPEN;
	NOP();
	NOP();
	for(i=0;i<32;i++)//延迟3us
	{
		NOP();
	}
	ETH_RST = 1;
	NOP();
	NOP();
	///////////////////////////////////////////
	EEPROM_Init();	
	delay_1ms(300);
	ETH_Init();
	
	GIE = 1;   // enable interrupt
	while(1)
	{	
		CLRWDT();
        NOP();
       // delay_1ms(100);
       // Test_led3 = !Test_led3;
		Socket_LINK_OFF_DET();
		NOP();
		////////////////////////////////////////////////////
		receive_convert();
		NOP();
	    ////////////////////////////////////////////////////
	    if(TP_Timer==TIME_OUT)
	    {
	    	//Uart1_TX(1);
			//Uart1_TX(Read_Byte_W5200(ETH_IN, Sn_SR(0)));
			if((Read_Byte_W5200(ETH_IN,PHY)&0x20)==0x20)//网线连接
			{
				Test_led1 = 0;
				if(ETH_IN_Link_Status == PHY_Link_OK)
				{
					ETH_IN_PHY_Link_STA = nochange;		
				}
				else
				{
					//Test_led3 = !Test_led3;
					
					TMR0IE = 0;
					TMR0ON = 0;
					ETH_IN_PHY_Link_STA = change;
					ETH_IN_Link_Status = PHY_Link_OK;	
					W5200_Config(ETH_IN);
					Socket_Listen_init(ETH_IN,0);	
					//Test_led3 = !Test_led3;	
				}
				if(Read_Byte_W5200(ETH_IN, Sn_SR(0))==SOCK_CLOSED)
				{
					W5200_Config(ETH_IN);
					Socket_Listen_init(ETH_IN,0);
				}
			}
			else
			{
				Test_led1 = 1;
				if(ETH_IN_Link_Status == PHY_Link_ERR)
				{
					ETH_IN_PHY_Link_STA = nochange;
					
				}
				else
				{
					TMR0IE = 0;
					TMR0ON = 0;
					ETH_IN_PHY_Link_STA = change;
					ETH_IN_Link_Status = PHY_Link_ERR;	
			
					Write_Byte_W5200(ETH_IN,Sn_CR(0),Sn_CR_CLOSE);		/* Close socket */		
				}
			}		
			///////////////////////////////////////////////////////////
			//Uart1_TX(2);
			//Uart1_TX(Read_Byte_W5200(ETH_OUT, Sn_SR(0)));
			if((Read_Byte_W5200(ETH_OUT,PHY)&0x20)==0x20)//网线连接
			{
				Test_led2 = 0;
				if(ETH_OUT_Link_Status == PHY_Link_OK)
				{
					ETH_OUT_PHY_Link_STA = nochange;
				}
				else
				{
					//Test_led3 = !Test_led3;
					TMR0IE = 0;
					TMR0ON = 0;
					ETH_OUT_PHY_Link_STA = change;
					ETH_OUT_Link_Status = PHY_Link_OK;
					W5200_Config(ETH_OUT);
					Socket_connect_init(ETH_OUT,0);		
					//Test_led3 = !Test_led3;
				}
				
				if(Read_Byte_W5200(ETH_OUT, Sn_SR(0))==SOCK_CLOSED)
				{
					W5200_Config(ETH_OUT);
					Socket_connect_init(ETH_OUT,0);	
				}	
			}
			else
			{
				Test_led2 = 1;
				if(ETH_OUT_Link_Status == PHY_Link_ERR)
				{
					ETH_OUT_PHY_Link_STA = nochange;				
				}
				else
				{
					TMR0IE = 0;
					TMR0ON = 0;
					ETH_OUT_PHY_Link_STA = change;
					ETH_OUT_Link_Status = PHY_Link_ERR;
					
					Write_Byte_W5200(ETH_OUT,Sn_CR(0),Sn_CR_CLOSE);		/* Close socket */	
				}
			}
			////////////////////////////////////////
			//Uart1_TX(Work_stutas);
			if(Work_stutas == test_stutas)
			{
				Test_NET_Transmission_detection();
			}
			//Uart1_TX(Read_Byte_W5200(ETH_IN, Sn_SR(0)));
			//Uart1_TX(Read_Byte_W5200(ETH_OUT, Sn_SR(0)));
			
			TMR0H = 0x85;
			TMR0L = 0xee;//500ms定时器
			//TMR0H = 0xe7;
			//TMR0L = 0x95;//100ms定时器
			TMR0ON = 1;
			TMR0IE = 1;
			TP_Timer=TIME_OFF;
	    }
	    ////////////////////////////////////////////////////
		if(ETH_IN_Event_en==1)
		{ 
			GIE = 0;/* Disable all intterupt */
			ETH_IN_Event();
			ETH_IN_Event_en = 0;
			INT0IE = 1;
			GIE = 1;
		}
		else if(ETH_OUT_Event_en == 1)
		{
			ETH_OUT_Event();
			ETH_OUT_Event_en = 0;
			INT0IE = 1;
		}
		
		//////////////////////////////////////////////////////
		if(TIMER1_stutas == TIME_OUT )// ETH_OUT 与PLC通讯
		{
			ETH_OUT_Communication_PLC();
				
			TIMER1_stutas = TIME_OFF;
			TMR1H  = 0x15 ;
			TMR1L  = 0x9f ;//30ms 30msX3=90ms用于与PLC通讯
			T1CON  = 0x33 ;			
		}
		///////////////////////////////////////////////////////
		if(Module_change_state == change)
		{
			Module_change_state = nochange;
			if(Work_stutas == test_stutas)
			{
				Test_work_init();
			}
			else if(Work_stutas == normal_status)
			{
				normal_work_init();
			}
		}
	}	
}





  

