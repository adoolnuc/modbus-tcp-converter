/////W5200 SPI //////////
#include<pic18.h>
#include<math.h>
#include<stdio.h>
#include"TCP_Convert_define_Init.h"
#include"TCP_Convert_W5200.h"
#include"modbus.h"

uchar S_DIP[4],S_DPORT[2];
uchar ETH_IN_MODE,ETH_OUT_MODE;
bank1 uchar ETH_IN_Rx_Buffer[RX_BUFFER_SIZE],ETH_OUT_Rx_Buffer[RX_BUFFER_SIZE];
bank2 uchar ETH_IN_Tx_Buffer[TX_BUFFER_SIZE],ETH_OUT_Tx_Buffer[TX_BUFFER_SIZE];

uchar ETH_IN_SOCKET_Status,ETH_OUT_SOCKET_Status;
uchar ETH_IN_Link_Status,ETH_OUT_Link_Status;
uint ETH_IN_RX_size,ETH_OUT_RX_size,Modbus_pc_cmd;
uchar list_sel;

uchar low4bit_temp,high4bit_temp,b_H_add0,b_L_add7;
uchar b_add0,b_add2;
uint change_add;
uchar temp_buf9,temp_buf10,ycqd_write_vaule;

uchar ETH_OUT_function;
uint list2_function1_add;
uchar list1_function1_buf,list1_function2_buf,list1_function4_buf2340L,list1_function4_buf2340H,list1_function4_buf2342L,list1_function4_buf2342H;
uchar list2_function1_buf24960,list2_function1_buf25120,list2_function2_bufL,list2_function2_bufH,list2_function4_buf2340L,list2_function4_buf2340H,list2_function4_buf2342L,list2_function4_buf2342H,list2_function1_buf;
//Para ETH_set_LIST[2];//ETH_IN=ETH_LIST[0],ETH_OUT=ETH_LIST[1];

/*
	ETH_IN GATEWAY[4]={192.168.1.171};//网关地址
	ETH_IN SUBNET[4]={};;//子网掩码
	ETH_IN MAC_ADDR[6]={};;//本机MAC地址
	ETH_IN IP[4]={};;//本机IP地址

	ETH_IN S0_SPORT[2]={};;// SOCKET 端口号
	ETH_IN S0_DIP[4]={192.168.1.181};;//目的地IP地址
	ETH_IN S0_DPORT[2]={};;//目的地 端口号
	///////////////////////////////////////////////////////
	ETH_OUT GATEWAY[4]={};//网关地址
	ETH_OUT SUBNET[4]={};;//子网掩码
	ETH_OUT MAC_ADDR[6]={};;//本机MAC地址
	ETH_OUT IP[4]={};;//本机IP地址

	ETH_OUT S0_SPORT[2]={};;// SOCKET 端口号
	ETH_OUT S0_DIP[4]={};;//目的地IP地址
	ETH_OUT S0_DPORT[2]={};;//目的地 端口号
*/

void Test_work_init()
{
	ETH_set_LIST[0].GATEWAY[0] = 192;
	ETH_set_LIST[0].GATEWAY[1] = 168;
	ETH_set_LIST[0].GATEWAY[2] = 1;
	ETH_set_LIST[0].GATEWAY[3] = 1;
	
	ETH_set_LIST[0].SUBNET[0] = 255;
	ETH_set_LIST[0].SUBNET[1] = 255;
	ETH_set_LIST[0].SUBNET[2] = 255;
	ETH_set_LIST[0].SUBNET[3] = 0;
	
	ETH_set_LIST[0].MAC_ADDR[0] = 0;
	ETH_set_LIST[0].MAC_ADDR[1] = 0xa0;
	ETH_set_LIST[0].MAC_ADDR[2] = 0xc9;
	ETH_set_LIST[0].MAC_ADDR[3] = 0x78;
	ETH_set_LIST[0].MAC_ADDR[4] = 0x32;
	ETH_set_LIST[0].MAC_ADDR[5] = 0;
	
	ETH_set_LIST[0].IP[0] = 192;
	ETH_set_LIST[0].IP[1] = 168;
	ETH_set_LIST[0].IP[2] = 1;
	ETH_set_LIST[0].IP[3] = 181;
	
	ETH_set_LIST[0].S0_SPORT[0]= 0x01;			/* default SOCKET0 port number=502 */
	ETH_set_LIST[0].S0_SPORT[1]= 0xF6;

	ETH_set_LIST[0].S0_DIP[0] = 192;			/* Default Socket0 destination IP is: 192.168.0.30 */
	ETH_set_LIST[0].S0_DIP[1] = 168;
	ETH_set_LIST[0].S0_DIP[2] = 1;
	ETH_set_LIST[0].S0_DIP[3] = 100;

	ETH_set_LIST[0].S0_DPORT[0] = 0x01;			/* Default Socket0 destination port number is 502 */
	ETH_set_LIST[0].S0_DPORT[1] = 0xF6;
	/////////////////////////////////////////////////////////////////////////////////////////
	ETH_set_LIST[1].GATEWAY[0] = 192;
	ETH_set_LIST[1].GATEWAY[1] = 168;
	ETH_set_LIST[1].GATEWAY[2] = 1;
	ETH_set_LIST[1].GATEWAY[3] = 1;
	
	ETH_set_LIST[1].SUBNET[0] = 255;
	ETH_set_LIST[1].SUBNET[1] = 255;
	ETH_set_LIST[1].SUBNET[2] = 255;
	ETH_set_LIST[1].SUBNET[3] = 0;
	
	ETH_set_LIST[1].MAC_ADDR[0] = 0;
	ETH_set_LIST[1].MAC_ADDR[1] = 0xa1;
	ETH_set_LIST[1].MAC_ADDR[2] = 0xc9;
	ETH_set_LIST[1].MAC_ADDR[3] = 0x78;
	ETH_set_LIST[1].MAC_ADDR[4] = 0x32;
	ETH_set_LIST[1].MAC_ADDR[5] = 0;
	
	ETH_set_LIST[1].IP[0] = 192;
	ETH_set_LIST[1].IP[1] = 168;
	ETH_set_LIST[1].IP[2] = 1;
	ETH_set_LIST[1].IP[3] = 171;
	
	ETH_set_LIST[1].S0_SPORT[0]= 0x01;			/* default SOCKET0 port number = 502 */
	ETH_set_LIST[1].S0_SPORT[1]= 0xF6;

	ETH_set_LIST[1].S0_DIP[0] = 192;			/* Default Socket0 destination IP is: 192.168.0.30 */
	ETH_set_LIST[1].S0_DIP[1] = 168;
	ETH_set_LIST[1].S0_DIP[2] = 1;
	ETH_set_LIST[1].S0_DIP[3] = 181;

	ETH_set_LIST[1].S0_DPORT[0] = 0x01;			/* Default Socket0 destination port number is 502 */
	ETH_set_LIST[1].S0_DPORT[1] = 0xF6;
	
	ETH_Init();
}

void normal_work_init()
{
	uchar i;
	for(i=0;i<4;i++)
	{
		ETH_set_LIST[0].GATEWAY[i] = Read_EEPROM(EEPROM_ETHIN_GAR_add0 +i);
		ETH_set_LIST[1].GATEWAY[i] = Read_EEPROM(EEPROM_ETHOUT_GAR_add0 +i);
	}
	
	for(i=0;i<4;i++)
	{
		ETH_set_LIST[0].SUBNET[i] = Read_EEPROM(EEPROM_ETHIN_SUBR_add0 +i);
		ETH_set_LIST[1].SUBNET[i] = Read_EEPROM(EEPROM_ETHOUT_SUBR_add0 +i);
	}
	
	for(i=0;i<6;i++)
	{
		ETH_set_LIST[0].MAC_ADDR[i] = Read_EEPROM(EEPROM_ETHIN_MAC_add0 +i);
		ETH_set_LIST[1].MAC_ADDR[i] = Read_EEPROM(EEPROM_ETHOUT_MAC_add0 +i);
	}
	
	for(i=0;i<4;i++)
	{
		ETH_set_LIST[0].IP[i] = Read_EEPROM(EEPROM_ETHIN_IP_add0 +i);
		ETH_set_LIST[1].IP[i] = Read_EEPROM(EEPROM_ETHOUT_IP_add0 +i);
	}
	
	for(i=0;i<2;i++)
	{
		ETH_set_LIST[0].S0_SPORT[i] = Read_EEPROM(EEPROM_ETHIN_S0_SPORT_add0 +i);
		ETH_set_LIST[1].S0_SPORT[i] = Read_EEPROM(EEPROM_ETHOUT_S0_SPORT_add0 +i);
	}
	
	for(i=0;i<4;i++)
	{
		ETH_set_LIST[0].S0_DIP[i] = Read_EEPROM(EEPROM_ETHIN_S0_DIP_add0 +i);
		ETH_set_LIST[1].S0_DIP[i] = Read_EEPROM(EEPROM_ETHOUT_S0_DIP_add0 +i);
	}
	
	for(i=0;i<2;i++)
	{
		ETH_set_LIST[0].S0_DPORT[i] = Read_EEPROM(EEPROM_ETHIN_S0_DPORT_add0 +i);
		ETH_set_LIST[1].S0_DPORT[i] = Read_EEPROM(EEPROM_ETHOUT_S0_DPORT_add0 +i);
	}
	
	ETH_Init();
}


void Test_NET_Transmission_detection()
{
	if(test_sync==ETH_OUT)
	{
		ETH_OUT_Tx_Buffer[0]=0x49;
		ETH_OUT_Tx_Buffer[1]=0x3e;
		ETH_OUT_Tx_Buffer[2]=0x4f;
		ETH_OUT_Tx_Buffer[3]=0x3d;
		ETH_OUT_Tx_Buffer[4]=0x4c;
		ETH_OUT_Tx_Buffer[5]=0x50;
		ETH_OUT_Tx_Buffer[6]=list_sel+0x30;
		ETH_OUT_Tx_Buffer[7]=0x20;
		
		if(Read_Byte_W5200(ETH_OUT, Sn_SR(0)) == SOCK_ESTABLISHED)
		{
			S_tx_process(ETH_OUT, 0, 8);
		}
		test_sync = ETH_IN;
	}
	else if(test_sync==ETH_IN)
	{
		ETH_IN_Tx_Buffer[0]=0x4f;
		ETH_IN_Tx_Buffer[1]=0x3e;
		ETH_IN_Tx_Buffer[2]=0x49;					
		ETH_IN_Tx_Buffer[3]=0x3d;
		ETH_IN_Tx_Buffer[4]=0x4c;
		ETH_IN_Tx_Buffer[5]=0x50;
		ETH_IN_Tx_Buffer[6]=list_sel+0x30;
		ETH_IN_Tx_Buffer[7]=0x20;;
		
		if(Read_Byte_W5200(ETH_IN, Sn_SR(0)) == SOCK_ESTABLISHED)
		{
			S_tx_process(ETH_IN, 0, 8);
		}
		test_sync = ETH_OUT;
	}
}

void Socket_LINK_OFF_DET()
{
	if(ETH_IN_Link_Status == PHY_Link_OK)//网线连接
	{
		if(Read_Byte_W5200(ETH_IN, Sn_SR(0))==SOCK_CLOSE_WAIT)
		{
			Write_Byte_W5200(ETH_IN,Sn_CR(0),Sn_CR_DISCON);		
		}
	}
	
	if(ETH_OUT_Link_Status == PHY_Link_OK)//网线连接
	{
		if(Read_Byte_W5200(ETH_OUT, Sn_SR(0))==SOCK_CLOSE_WAIT)
		{
			Write_Byte_W5200(ETH_OUT,Sn_CR(0),Sn_CR_DISCON);
		}
	}
}


/* Write a byte to W5200 through SPI  ETH IN*/
void Write_Byte_W5200(uchar channal,uint addr, uchar dat)
{
	uchar add_H,add_L;
	GIE = 0;/* Disable all intterupt */
	add_H = (uchar)(addr/256);
	add_L = (uchar)(addr&0x00ff);
	
	if(channal == ETH_IN)
	{
		SSP1IF=0;							
		ETH_IN_SPI1_CS1=0;
		NOP();	
		NOP();
		
		SSP1BUF =add_H;						/* Write Register address */
		while(SSP1IF==0);
		SSP1IF=0;
		SSP1BUF=add_L;
		while(SSP1IF==0);
		SSP1IF=0;
	
		SSP1BUF=0x80;							/* Send Write command, Write 1 byte*/
		while(SSP1IF==0);
		SSP1IF=0;
		SSP1BUF=0x01;
		while(SSP1IF==0);
		SSP1IF=0;
	
		SSP1BUF=dat;
		while(SSP1IF==0);
		SSP1IF=0;
	
		NOP();	
		NOP();
		ETH_IN_SPI1_CS1=1;
	}
	else if(channal == ETH_OUT)
	{
		SSP2IF=0;							
		ETH_OUT_SPI2_CS2=0;
		NOP();	
		NOP();
		
		SSP2BUF =add_H;						/* Write Register address */
		while(SSP2IF==0);
		SSP2IF=0;
		SSP2BUF=add_L;
		while(SSP2IF==0);
		SSP2IF=0;
	
		SSP2BUF=0x80;							/* Send Write command, Write 1 byte*/
		while(SSP2IF==0);
		SSP2IF=0;
		SSP2BUF=0x01;
		while(SSP2IF==0);
		SSP2IF=0;
	
		SSP2BUF=dat;
		while(SSP2IF==0);
		SSP2IF=0;
	
		NOP();	
		NOP();
		ETH_OUT_SPI2_CS2=1;
	}
	GIE = 1;							/* Enable all interrupt */
}

/* Read a byte from W5200 through SPI */
uchar Read_Byte_W5200(uchar channal,uint addr)
{
	uchar i;
	uchar add_H,add_L;
	
	GIE = 0;/* Disable all intterupt */
	add_H = (uchar)(addr/256);
	add_L = (uchar)(addr&0x00ff);
	
	if(channal == ETH_IN)
	{
		/*if(SSP1CON1bits.WCOL==1)
		{
			SSP1CON1bits.WCOL =0;
		}
		if(SSP1STATbits.BF==1)
		{
			i=SSP1BUF;
		}*/
		SSP1IF=0;							
		ETH_IN_SPI1_CS1=0;
		NOP();	
		NOP();

		SSP1BUF=add_H;						/* Write Register address */
		while(SSP1IF==0);
		SSP1IF=0;
		SSP1BUF=add_L;
		while(SSP1IF==0);
		SSP1IF=0;
	
		SSP1BUF=0x00;							/* Send read command, Read 1 byte*/
		while(SSP1IF==0);
		SSP1IF=0;
		SSP1BUF=0x01;
		while(SSP1IF==0);
		SSP1IF=0;
	
		SSP1BUF=0;
		while(SSP1IF==0);
		SSP1IF=0;
		i=SSP1BUF;
	
		NOP();	
		NOP();
		ETH_IN_SPI1_CS1=1;
	}
	else if(channal == ETH_OUT)
	{
		SSP2IF=0;							
		ETH_OUT_SPI2_CS2=0;
		NOP();	
		NOP();

		SSP2BUF=add_H;						/* Write Register address */
		while(SSP2IF==0);
		SSP2IF=0;
		SSP2BUF=add_L;
		while(SSP2IF==0);
		SSP2IF=0;
	
		SSP2BUF=0x00;							/* Send read command, Read 1 byte*/
		while(SSP2IF==0);
		SSP2IF=0;
		SSP2BUF=0x01;
		while(SSP2IF==0);
		SSP2IF=0;
	
		SSP2BUF=0;
		while(SSP2IF==0);
		SSP2IF=0;
		i=SSP2BUF;
	
		NOP();	
		NOP();
		ETH_OUT_SPI2_CS2=1;
		
	}	
	GIE = 1;							/* Enable all interrupt */
	
	//Uart1_TX(i);
	return i;
}

/* Write data to W5200 through SPI */
void Write_W5200(uchar channal,uint Reg_Addr,uchar *Data_ptr, uint Data_Size)
{
	uint i;
	uchar add_H,add_L;
	
	GIE = 0;/* Disable all intterupt */
	add_H = (uchar)(Reg_Addr/256);
	add_L = (uchar)(Reg_Addr&0x00ff);
	
	if(channal == ETH_IN)
	{
		SSP1IF=0;							
		ETH_IN_SPI1_CS1=0;
		NOP();	
		NOP();

		SSP1BUF=add_H;					/* Send Register Address */
		while(SSP1IF==0);
		SSP1IF=0;
		SSP1BUF=add_L;
		while(SSP1IF==0);
		SSP1IF=0;
	
		i=Data_Size|0x8000;					/* Send Write Command, send write data size */
		SSP1BUF=(uchar)(i/256);
		while(SSP1IF==0);
		SSP1IF=0;
		SSP1BUF=(uchar)(i);
		while(SSP1IF==0);
		SSP1IF=0;
	
		for(i=0;i<Data_Size;i++)
		{
			SSP1BUF=*Data_ptr;
			while(SSP1IF==0);
			SSP1IF=0;
			Data_ptr++;
		}
	
		NOP();	
		NOP();
		ETH_IN_SPI1_CS1=1;
	}
	else if(channal == ETH_OUT)
	{
		SSP2IF=0;							
		ETH_OUT_SPI2_CS2=0;
		NOP();	
		NOP();

		SSP2BUF=add_H;					/* Send Register Address */
		while(SSP2IF==0);
		SSP2IF=0;
		SSP2BUF=add_L;
		while(SSP2IF==0);
		SSP2IF=0;
	
		i=Data_Size|0x8000;					/* Send Write Command, send write data size */
		SSP2BUF=(uchar)(i/256);
		while(SSP2IF==0);
		SSP2IF=0;
		SSP2BUF=(uchar)(i);
		while(SSP2IF==0);
		SSP2IF=0;
	
		for(i=0;i<Data_Size;i++)
		{
			SSP2BUF=*Data_ptr;
			while(SSP2IF==0);
			SSP2IF=0;
			Data_ptr++;
		}
	
		NOP();	
		NOP();
		ETH_OUT_SPI2_CS2=1;
	}
	GIE=1;							/* Enable all interrupt */
}

/* Read data from W5200 through SPI */
void Read_W5200(uchar channal,uint Reg_Addr,uchar *Data_ptr,uint Data_Size)
{
	uint i;
	uchar j;
	uchar add_H,add_L;
	
	GIE = 0;/* Disable all intterupt */
	add_H = (uchar)(Reg_Addr/256);
	add_L = (uchar)(Reg_Addr&0x00ff);
	
	if(channal == ETH_IN)
	{
		SSP1IF=0;							
		ETH_IN_SPI1_CS1=0;
		NOP();	
		NOP();

		SSP1BUF=add_H;					/* Send Register Address */
		while(SSP1IF==0);
		SSP1IF=0;
		SSP1BUF=add_L;
		while(SSP1IF==0);
		SSP1IF=0;
	
		i=Data_Size&0x7fff;				/* Send READ Command, send write data size */
		SSP1BUF=(uchar)(i/256);
		while(SSP1IF==0);
		SSP1IF=0;
		SSP1BUF=(uchar)(i);
		while(SSP1IF==0);
		SSP1IF=0;
	
		for(i=0;i<Data_Size;i++)
		{
			SSP1BUF=0;
			while(SSP1IF==0);
			SSP1IF=0;
			j=SSP1BUF;
			*Data_ptr=j;
			Data_ptr++;
		}	
		NOP();	
		NOP();
		ETH_IN_SPI1_CS1=1;
	}
	else if(channal == ETH_OUT)
	{
		SSP2IF=0;							
		ETH_OUT_SPI2_CS2=0;
		NOP();	
		NOP();

		SSP2BUF=add_H;					/* Send Register Address */
		while(SSP2IF==0);
		SSP2IF=0;
		SSP2BUF=add_L;
		while(SSP2IF==0);
		SSP2IF=0;
	
		i=Data_Size&0x7fff;				/* Send READ Command, send write data size */
		SSP2BUF=(uchar)(i/256);
		while(SSP2IF==0);
		SSP2IF=0;
		SSP2BUF=(uchar)(i);
		while(SSP2IF==0);
		SSP2IF=0;
	
		for(i=0;i<Data_Size;i++)
		{
			SSP2BUF=0;
			while(SSP2IF==0);
			SSP2IF=0;
			j=SSP2BUF;
			*Data_ptr=j;
			Data_ptr++;
		}	
		NOP();	
		NOP();
		ETH_OUT_SPI2_CS2=1;
	}	
	GIE=1;							/* Enable all interrupt */
}

/* Close Socket */
void Close_Socket(uchar channal,uchar s)
{
	if(Read_Byte_W5200(channal,Sn_SR(s))&SOCK_ESTABLISHED)
	{
		Write_Byte_W5200(channal,Sn_CR(s),Sn_CR_DISCON);
	}

	Write_Byte_W5200(channal,Sn_CR(s),Sn_CR_CLOSE);		/* Close socket */
}


/* Read W5200 Socket state */
unsigned char Read_SR(uchar channal,uchar s)
{
	unsigned char i;

	i=Read_Byte_W5200(channal,Sn_SR(s));

	return i;	
}

/* Read W5200 Socket Interrupt state */
unsigned char Read_IR(uchar channal,uchar s)
{
	unsigned char i;

	i=Read_Byte_W5200(channal,Sn_IR(s));

	if(i==0)
		return 0;
	else
		Write_Byte_W5200(channal,Sn_IR(s),i);		/* Clear IR */

	return i;	
}

/* Read Socket Received dada size */
unsigned int Read_RSR(uchar channal,uchar s)
{
	unsigned int i;

	i=Read_Byte_W5200(channal,Sn_RX_RSR0(s));
	i*=256;
	i+=Read_Byte_W5200(channal,Sn_RX_RSR0(s)+1);

	return i;
}

/*********************************************************************
                         W5100 Initialization
*********************************************************************/
void W5200_Config(uchar channal)
{
	//Para *param=(Para *)Parameters;
	
	Write_Byte_W5200(channal,MR,0x80);		/* Software reset W5200 */
	delay_1ms(10);

	Write_W5200(channal,SHAR0,ETH_set_LIST[channal].MAC_ADDR,6);//配置MAC,
	Write_W5200(channal,SUBR0,ETH_set_LIST[channal].SUBNET,4);//配置子网掩码
	Write_W5200(channal,GAR0,ETH_set_LIST[channal].GATEWAY,4);//配置网关，
	Write_W5200(channal,SIPR0,ETH_set_LIST[channal].IP,4);//配置IP,

	Write_Byte_W5200(channal,IMR2,0x01);				/* Enable scocket 0 interrupt */

	Write_Byte_W5200(channal,INTLEVEL1,0x02);		/* Interrupt low level interval time */	
}

/***************************************************************************************
Detect Gateway and get Gateway MAC address
Find Gateway then return TRUE, otherwise return FALSE
***************************************************************************************/
unsigned char Detect_Gateway(uchar channal)
{
	unsigned char i;

	//Para *param=(Para *)Parameters;
	Write_Byte_W5200(channal,Sn_MR(0),Sn_MR_TCP);		/* Open Socket in TCP mode */	
	Write_Byte_W5200(channal,Sn_CR(0),Sn_CR_OPEN);//打开端口

	delay_1ms(50);
	if(Read_Byte_W5200(channal,Sn_SR(0))!=SOCK_INIT)
	{
		Write_Byte_W5200(channal,Sn_CR(0),Sn_CR_CLOSE);		/* Failed to open socket in TCP mode */
		return(SOCKET_OPEN_ERR);
	}
	return(SOCKET_OPEN_OK);
}

/*****************************************************************************
			                          Socket n
*****************************************************************************/
/*---------------------------------------------------------
Socket n initialization
No return value
---------------------------------------------------------*/
void Socket_Config(uchar channal,uchar s)
{
	//Para *param=(Para *)Parameters;

	Write_W5200(channal,Sn_PORT0(s),ETH_set_LIST[channal].S0_SPORT,2);		/* SOCKET PORT Number */
	Write_W5200(channal,Sn_DPORT0(s),ETH_set_LIST[channal].S0_DPORT,2);		/* SOCKET Destination PORT Number */
	Write_W5200(channal,Sn_DIPR0(s),ETH_set_LIST[channal].S0_DIP,4);			/* SOCKET Destination IP */

	//Write_Byte_W5200(channal,Sn_IMR(s),0x0f);//,TIMEROUT,RECV,DISCON,CON 使能
	                                         //，ARP、TCP超时中断，接收数据中断，断开连接中断，产生连接中断
	Write_Byte_W5200(channal,Sn_IMR(s),0x0e);
	/* Maximum Segment size */
	Write_Byte_W5200(channal,Sn_MSSR0(s),0x05);//最大分片大小 MTU=1460
	Write_Byte_W5200(channal,Sn_MSSR0(s)+1,0xb4);
}




/*-----------------------------------------------------------------------------
Read SOCKET n RX Memory, Put received DATA in Rx_Buffer
Input: None
Return: Received data size
-----------------------------------------------------------------------------*/
unsigned int S_rx_process(uchar channal,uchar s)
{
	unsigned int size;
	unsigned int rx_offset,rx1_offset;
	unsigned int i;
	
	size=Read_Byte_W5200(channal,Sn_RX_RSR0(s));
	size*=256;
	size+=Read_Byte_W5200(channal,Sn_RX_RSR0(s)+1);

	rx_offset=Read_Byte_W5200(channal,Sn_RX_RD0(s));
	rx_offset*=256;
	rx_offset+=Read_Byte_W5200(channal,Sn_RX_RD0(s)+1);
	rx1_offset=rx_offset;

	rx_offset=rx_offset&(RX_MEM_SIZE-1);
	
	if(channal==ETH_IN)
	{
		if((size+rx_offset)<=RX_MEM_SIZE)
		Read_W5200(channal,(RX_MEM+s*RX_MEM_SIZE+rx_offset),ETH_IN_Rx_Buffer,size);
		else
		{
			i=RX_MEM_SIZE-rx_offset;
			Read_W5200(channal,(RX_MEM+s*RX_MEM_SIZE+rx_offset),ETH_IN_Rx_Buffer,i);
			Read_W5200(channal,(RX_MEM+s*RX_MEM_SIZE),ETH_IN_Rx_Buffer+i,(size-i));
		}
	}
	else if(channal==ETH_OUT)
	{
		if((size+rx_offset)<=RX_MEM_SIZE)
		Read_W5200(channal,(RX_MEM+s*RX_MEM_SIZE+rx_offset),ETH_OUT_Rx_Buffer,size);
		else
		{
			i=RX_MEM_SIZE-rx_offset;
			Read_W5200(channal,(RX_MEM+s*RX_MEM_SIZE+rx_offset),ETH_OUT_Rx_Buffer,i);
			Read_W5200(channal,(RX_MEM+s*RX_MEM_SIZE),ETH_OUT_Rx_Buffer+i,(size-i));
		}		
	}

	rx1_offset+=size;
	Write_Byte_W5200(channal,Sn_RX_RD0(s),rx1_offset/256);
	Write_Byte_W5200(channal,Sn_RX_RD0(s)+1,rx1_offset);

	Write_Byte_W5200(channal,Sn_CR(s),Sn_CR_RECV);
		
	return size;
}

/*-----------------------------------------------------------------------------
Data in Tx_Buffer to be transfered through SOCKET n
Input: Data size in Tx_Buffer to be transfered
-----------------------------------------------------------------------------*/
unsigned char S_tx_process(uchar channal,uchar s, unsigned int tx_size)
{
	unsigned int tx_offset, tx1_offset;
	unsigned int i;
	unsigned char j;
		
	tx_offset=Read_Byte_W5200(channal,Sn_TX_WR0(s));
	tx_offset*=256;
	tx_offset+=Read_Byte_W5200(channal,Sn_TX_WR0(s)+1);
	tx1_offset=tx_offset;

	tx_offset=tx_offset&(TX_MEM_SIZE-1);
	
	if(channal==ETH_IN)
	{
		if((tx_offset+tx_size)<=TX_MEM_SIZE)
		Write_W5200(channal,(TX_MEM+s*TX_MEM_SIZE+tx_offset),ETH_IN_Tx_Buffer,tx_size);
		else
		{
			i=TX_MEM_SIZE-tx_offset;
			Write_W5200(channal,(TX_MEM+s*TX_MEM_SIZE+tx_offset),ETH_IN_Tx_Buffer,i);
			Write_W5200(channal,(TX_MEM+s*TX_MEM_SIZE),ETH_IN_Tx_Buffer+i,(tx_size-i));
		}
	}
	else if(channal==ETH_OUT)
	{
		if((tx_offset+tx_size)<=TX_MEM_SIZE)
		Write_W5200(channal,(TX_MEM+s*TX_MEM_SIZE+tx_offset),ETH_OUT_Tx_Buffer,tx_size);
		else
		{
			i=TX_MEM_SIZE-tx_offset;
			Write_W5200(channal,(TX_MEM+s*TX_MEM_SIZE+tx_offset),ETH_OUT_Tx_Buffer,i);
			Write_W5200(channal,(TX_MEM+s*TX_MEM_SIZE),ETH_OUT_Tx_Buffer+i,(tx_size-i));
		}
	}
	
	tx1_offset+=tx_size;
	Write_Byte_W5200(channal,Sn_TX_WR0(s),tx1_offset/256);
	Write_Byte_W5200(channal,Sn_TX_WR0(s)+1,tx1_offset);

	Write_Byte_W5200(channal,Sn_CR(s),Sn_CR_SEND);
	
	do
	{
		j=Read_IR(channal,s);
		if(j&Sn_IR_SEND_OK)
		{
			Write_Byte_W5200(channal,Sn_IR(s),Sn_IR_SEND_OK);		//清中断
			return true;
		}
			
		else if(j&Sn_IR_TIMEOUT)
		{
			Write_Byte_W5200(channal,Sn_IR(s),Sn_IR_TIMEOUT);		//清中断
			return false;
		}
	}while(1);	
	return true;
}


void ETH_Init()
{
	//1、初始化W5200芯片
	W5200_Config(ETH_IN);
	W5200_Config(ETH_OUT);
	
	//2、初始化SOCKET端口,设置工作模式
	// Socket_Listen_init(ETH_OUT,0);
	// Socket_connect_init(ETH_IN,0);	
	Socket_Listen_init(ETH_IN,0);
	Socket_connect_init(ETH_OUT,0);	
}

void ETH_IN_Event()//收到PC端发来数据（机房）
{
	uchar i,j;
	uchar cmd_flag;//
	
	int ret_val;
	i = Read_IR(ETH_IN,0); 
	
	//if(i&Sn_IR_SEND_OK)
	//{
	//	Write_Byte_W5200(ETH_IN,Sn_IR(0),Sn_IR_SEND_OK);		//清中断
	//}
	if(i&Sn_IR_TIMEOUT)
	{
		//Socket_Listen_init(ETH_IN,0);
		Write_Byte_W5200(ETH_IN,Sn_IR(0),Sn_IR_TIMEOUT);		//清中断
		Write_Byte_W5200(ETH_IN,Sn_CR(0),Sn_CR_CLOSE);		/* Close socket */
		
	}
	else if(i&Sn_IR_RECV)
	{
		LED_Run = !LED_Run;
		ETH_IN_RX_size =S_rx_process(ETH_IN,0);      /* Read W5200 Data to Rx_Buffer ,ETH_IN_RX_size=size*/

		if(Work_stutas == normal_status)
		{
			// 协议转化
			ETH_IN_rec_PC_data();
			//download_protocol_add_analyze();
				
			///////////////////////////////////////////////
			LED_Run = !LED_Run;
			//Uart1_TX(0x90);
			///////////////////////////////////////////////////////
			/*if(Read_Byte_W5200(ETH_OUT, Sn_SR(0)) == SOCK_ESTABLISHED)
			{
				S_tx_process(ETH_OUT, 0, ETH_IN_RX_size);
			}*/
			//}
		}
		else if(Work_stutas == test_stutas)
		{
			for(j=0;j<ETH_IN_RX_size;j++)
			{
				LED_Run = !LED_Run;
				Uart1_TX(ETH_IN_Rx_Buffer[j]);
				LED_Run = !LED_Run;
			}		
		}	
				
		Write_Byte_W5200(ETH_IN,Sn_IR(0),Sn_IR_RECV);		//清中断
	}
	else if(i&Sn_IR_DISCON)
	{
		Uart1_TX(Sn_IR_DISCON|0x10);
		Write_Byte_W5200(ETH_IN,Sn_IR(0),Sn_IR_DISCON);		//清中断
		Write_Byte_W5200(ETH_IN,Sn_CR(0),Sn_CR_CLOSE);		// Close socket 			
	}
	else if(i&Sn_IR_CON)
	{
		Write_Byte_W5200(ETH_IN,Sn_IR(0),Sn_IR_CON);		//清中断
	}
}

void ETH_OUT_Event()//发送接收 PLC数据
{
	uchar i,k,j;
	uchar cmd_flag;
	i = Read_IR(ETH_OUT,0);
	int ret_val;
	
	//if(i&Sn_IR_SEND_OK)
	//{
	//	Write_Byte_W5200(ETH_IN,Sn_IR(0),Sn_IR_SEND_OK);		//清中断
	//}
	if(i&Sn_IR_TIMEOUT)
	{
		Write_Byte_W5200(ETH_OUT,Sn_IR(0),Sn_IR_TIMEOUT);		//清中断
		Write_Byte_W5200(ETH_OUT,Sn_CR(0),Sn_CR_CLOSE);		/* Close socket */
	}
	else if(i&Sn_IR_RECV)
	{
		ETH_OUT_RX_size=S_rx_process(ETH_OUT,0);      /* Read W5200 Data to Rx_Buffer ,k=size*/

		if(Work_stutas == normal_status)
		{
			// 协议转化
			
			ETH_OUT_rec_PLC_data();
			//updata_protocol_data_analyze();
	 			
				/*for(j=0;j<ETH_OUT_RX_size;j++)		
				{
					
					ETH_IN_Tx_Buffer[j]=ETH_OUT_Rx_Buffer[j];
				}*/
			
			
			/*if(Read_Byte_W5200(ETH_IN, Sn_SR(0)) == SOCK_ESTABLISHED)
			{
				S_tx_process(ETH_IN, 0, ETH_OUT_RX_size);
			}*/			
		}
		else if(Work_stutas == test_stutas)
		{
			for(j=0;j<ETH_OUT_RX_size;j++)
			{
				LED_Run = !LED_Run;
				Uart1_TX(ETH_OUT_Rx_Buffer[j]);
				LED_Run = !LED_Run;
			}		
		}

		Write_Byte_W5200(ETH_OUT,Sn_IR(0),Sn_IR_RECV);		//清中断		
	}
	else if(i&Sn_IR_DISCON)
	{
		Write_Byte_W5200(ETH_OUT,Sn_IR(0),Sn_IR_DISCON);		//清中断
		Write_Byte_W5200(ETH_OUT,Sn_CR(0),Sn_CR_CLOSE);
	}
	else if(i&Sn_IR_CON)
	{
		Write_Byte_W5200(ETH_OUT,Sn_IR(0),Sn_IR_CON);		//清中断
	}
}

void Socket_connect_init(uchar channal,uchar s)
{
	if(channal == ETH_IN)
	{
		if((Read_Byte_W5200(ETH_IN,PHY)&0x20)==0x20)//网线连接
		{
			ETH_IN_Link_Status=PHY_Link_OK;//物理连接成功
			
			Write_Byte_W5200(ETH_IN,Sn_CR(s),Sn_CR_CLOSE);			/* Close Socket */
			delay_1ms(100);
		
			Socket_Config(ETH_IN,s);//初始化SOCKET0
			//ETH_set_LIST[channal].S0_SPORT[1]++;	
	
	
			Write_Byte_W5200(ETH_IN,Sn_MR(s),Sn_MR_TCP);		/* Open Socket in TCP mode */	
			Write_Byte_W5200(ETH_IN,Sn_CR(s),Sn_CR_OPEN);//打开端口
			
			delay_1ms(50);
			if(Read_Byte_W5200(ETH_IN,Sn_SR(s))!=SOCK_INIT)
			{
				ETH_IN_SOCKET_Status = SOCKET_OPEN_ERR;
				Write_Byte_W5200(ETH_IN,Sn_CR(s),Sn_CR_CLOSE);		/* Failed to open socket in TCP mode */
			}
			
			Write_Byte_W5200(ETH_IN,Sn_CR(s),Sn_CR_CONNECT);//TCP客户端		/* Set Socket s in TCP Client mode */
			ETH_IN_SOCKET_Status = SOCKET_OPEN_OK;	
					
		}
		else
		{
			Write_Byte_W5200(ETH_IN,Sn_CR(s),Sn_CR_CLOSE);
			ETH_IN_Link_Status=PHY_Link_ERR;
			ETH_IN_SOCKET_Status = SOCKET_OPEN_ERR;
		}
	}
	else if(channal == ETH_OUT)
	{
		if((Read_Byte_W5200(ETH_OUT,PHY)&0x20)==0x20)//网线连接
		{
			ETH_OUT_Link_Status=PHY_Link_OK;//物理连接成功
			
			Write_Byte_W5200(ETH_OUT,Sn_CR(s),Sn_CR_CLOSE);			/* Close Socket */
			delay_1ms(100);
		
			Socket_Config(ETH_OUT,s);//初始化SOCKET0
			//ETH_set_LIST[channal].S0_SPORT[1]++;	
	
	
			Write_Byte_W5200(ETH_OUT,Sn_MR(s),Sn_MR_TCP);		/* Open Socket in TCP mode */	
			Write_Byte_W5200(ETH_OUT,Sn_CR(s),Sn_CR_OPEN);//打开端口
			
			delay_1ms(50);
			if(Read_Byte_W5200(ETH_OUT,Sn_SR(s))!=SOCK_INIT)
			{
				ETH_OUT_SOCKET_Status = SOCKET_OPEN_ERR;
				Write_Byte_W5200(ETH_OUT,Sn_CR(s),Sn_CR_CLOSE);		/* Failed to open socket in TCP mode */
			}
			
			Write_Byte_W5200(ETH_OUT,Sn_CR(s),Sn_CR_CONNECT);//TCP客户端			/* Set Socket s in TCP Client mode */			
			ETH_OUT_SOCKET_Status = SOCKET_OPEN_OK;		
			//LED_Run = 0;	
		}
		else
		{
			Write_Byte_W5200(ETH_OUT,Sn_CR(s),Sn_CR_CLOSE);
			ETH_OUT_Link_Status==PHY_Link_ERR;
			ETH_OUT_SOCKET_Status = SOCKET_OPEN_ERR;
		}	
	}
}

void Socket_Listen_init(uchar channal,uchar s)
{
	if(channal == ETH_IN)
	{
		if((Read_Byte_W5200(ETH_IN,PHY)&0x20)==0x20)//网线连接
		{
			ETH_IN_Link_Status=PHY_Link_OK;//物理连接成功
			
			Write_Byte_W5200(ETH_IN,Sn_CR(s),Sn_CR_CLOSE);			/* Close Socket */
			delay_1ms(100);
		
			Socket_Config(ETH_IN,s);//初始化SOCKET0
			//ETH_set_LIST[channal].S0_SPORT[1]++;	
	
			Write_Byte_W5200(ETH_IN,Sn_MR(s),Sn_MR_TCP);		/* Open Socket in TCP mode */	
			Write_Byte_W5200(ETH_IN,Sn_CR(s),Sn_CR_OPEN);//打开端口
			
			delay_1ms(50);
			if(Read_Byte_W5200(ETH_IN,Sn_SR(s))!=SOCK_INIT)
			{
				ETH_IN_SOCKET_Status = SOCKET_OPEN_ERR;
				Write_Byte_W5200(ETH_IN,Sn_CR(s),Sn_CR_CLOSE);		/* Failed to open socket in TCP mode */
			}
			
			Write_Byte_W5200(ETH_IN,Sn_CR(s),Sn_CR_LISTEN);//TCP服务器		/* Set Socket s in TCP Server mode */
			delay_1ms(20);

			if(Read_Byte_W5200(ETH_IN,Sn_SR(s))!=SOCK_LISTEN)
			{
				ETH_IN_SOCKET_Status = SOCKET_OPEN_ERR;
				Write_Byte_W5200(ETH_IN,Sn_CR(s),Sn_CR_CLOSE);		/* Failed to open socket in TCP mode */
			}
			ETH_IN_SOCKET_Status = SOCKET_OPEN_OK;			
		}
		else
		{
			Write_Byte_W5200(ETH_IN,Sn_CR(s),Sn_CR_CLOSE);
			ETH_IN_Link_Status=PHY_Link_ERR;
			ETH_IN_SOCKET_Status = SOCKET_OPEN_ERR;
		}
	}
	else if(channal == ETH_OUT)
	{
		if((Read_Byte_W5200(ETH_OUT,PHY)&0x20)==0x20)//网线连接
		{
			ETH_OUT_Link_Status=PHY_Link_OK;//物理连接成功
			
			Write_Byte_W5200(ETH_OUT,Sn_CR(s),Sn_CR_CLOSE);			/* Close Socket */
			delay_1ms(100);
		
			Socket_Config(ETH_OUT,s);//初始化SOCKET0
			//ETH_set_LIST[channal].S0_SPORT[1]++;	
	
			Write_Byte_W5200(ETH_OUT,Sn_MR(s),Sn_MR_TCP);		/* Open Socket in TCP mode */	
			Write_Byte_W5200(ETH_OUT,Sn_CR(s),Sn_CR_OPEN);//打开端口
			
			delay_1ms(50);
			if(Read_Byte_W5200(ETH_OUT,Sn_SR(s))!=SOCK_INIT)
			{
				ETH_OUT_SOCKET_Status = SOCKET_OPEN_ERR;
				Write_Byte_W5200(ETH_OUT,Sn_CR(s),Sn_CR_CLOSE);		/* Failed to open socket in TCP mode */
			}
			
			Write_Byte_W5200(ETH_OUT,Sn_CR(s),Sn_CR_LISTEN);//TCP服务器		/* Set Socket s in TCP Server mode */
			delay_1ms(20);

			if(Read_Byte_W5200(ETH_OUT,Sn_SR(s))!=SOCK_LISTEN)
			{
				ETH_OUT_SOCKET_Status = SOCKET_OPEN_ERR;
				Write_Byte_W5200(ETH_OUT,Sn_CR(s),Sn_CR_CLOSE);		/* Failed to open socket in TCP mode */
			}
			ETH_OUT_SOCKET_Status = SOCKET_OPEN_OK;			
		}
		else
		{
			Write_Byte_W5200(ETH_OUT,Sn_CR(s),Sn_CR_CLOSE);
			ETH_OUT_Link_Status==PHY_Link_ERR;
			ETH_OUT_SOCKET_Status = SOCKET_OPEN_ERR;
		}	
	}
}
/*
void download_protocol_add_analyze()
{
	uchar j;
	uint cmd_add;
	
	if(list_sel==list1)//地址码表1
	{
		for(j=0;j<7;j++)		
		{
			ETH_OUT_Tx_Buffer[j]=ETH_IN_Rx_Buffer[j];
		}
		
		ETH_OUT_Tx_Buffer[7]=ETH_IN_Rx_Buffer[7];
		Modbus_pc_cmd = ETH_IN_Rx_Buffer[7];//备份命令码，返回数据时恢复
		////////////////////////////////////////////////////
		cmd_add =((ETH_IN_Rx_Buffer[8]*256)+ETH_IN_Rx_Buffer[9]);
		
		switch(ETH_IN_Rx_Buffer[7])
		{
			case 1:
			{
				switch(cmd_add)
				{
					case 1://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x62;//addr = 25120
						ETH_OUT_Tx_Buffer[9] = 0x20;
						change_add = 25120;
						for(j=10;j<=ETH_IN_RX_size;j++)		
						{
							ETH_OUT_Tx_Buffer[j]=ETH_IN_Rx_Buffer[j];
						}
					}break;
					default :break;	
				}				
			}break;
			case 2://命令码
			{
				switch(cmd_add)
				{
					case 0://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x62;//addr = 25104
						ETH_OUT_Tx_Buffer[9] = 0x10;
						change_add = 25104;
					}break;
					default :break;	
				}
				for(j=10;j<=ETH_IN_RX_size;j++)		
				{
					ETH_OUT_Tx_Buffer[j]=ETH_IN_Rx_Buffer[j];
				}
			}break;
			case 4:
			{
				switch(cmd_add)
				{
					case 1://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x09;//addr = 2340
						ETH_OUT_Tx_Buffer[9] = 0x24;
						change_add = 2340;
					}break;				
					default :break;	
				}
				ETH_OUT_Tx_Buffer[10] = ETH_IN_Rx_Buffer[10];
				ETH_OUT_Tx_Buffer[11] = ETH_IN_Rx_Buffer[11]+1;//2340,2341,2342	
			}break;
			
			case 5:
			{
				switch(cmd_add)
				{
					case 1://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x62;//addr = 25120
						ETH_OUT_Tx_Buffer[9] = 0x20;
						change_add = 25120;
						for(j=10;j<=ETH_IN_RX_size;j++)		
						{
							ETH_OUT_Tx_Buffer[j]=ETH_IN_Rx_Buffer[j];
						}
					}break;
					default :break;	
				}
			}break;
			default :break;
		}
		
	}
	else if(list_sel==list2)//地址码表2
	{
		for(j=0;j<7;j++)		
		{
			ETH_OUT_Tx_Buffer[j]=ETH_IN_Rx_Buffer[j];
		}
		
		ETH_OUT_Tx_Buffer[7]=ETH_IN_Rx_Buffer[7];
		Modbus_pc_cmd = ETH_IN_Rx_Buffer[7];//备份命令码，返回数据时恢复

		cmd_add =((ETH_IN_Rx_Buffer[8]*256)+ETH_IN_Rx_Buffer[9]);
		
		switch(ETH_IN_Rx_Buffer[7])
		{
			case 2://命令码
			{
				switch(cmd_add)
				{
					case 0://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x62;//addr = 25104
						ETH_OUT_Tx_Buffer[9] = 0x10;
						change_add = 25104;
					}break;
					case 1://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x62;//addr = 25105
						ETH_OUT_Tx_Buffer[9] = 0x11;
					}break;
					case 2://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x62;//addr = 25106
						ETH_OUT_Tx_Buffer[9] = 0x12;
					}break;
					case 3://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x62;//addr = 25107
						ETH_OUT_Tx_Buffer[9] = 0x13;
					}break;
					case 4://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x62;//addr = 25112
						ETH_OUT_Tx_Buffer[9] = 0x18;
					}break;
					case 5://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x62;//addr = 25108
					ETH_OUT_Tx_Buffer[9] = 0x14;
					}break;
					case 6://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x62;//addr = 25109
					ETH_OUT_Tx_Buffer[9] = 0x15;
					}break;
					case 7://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x62;//addr = 25110
					ETH_OUT_Tx_Buffer[9] = 0x16;
					}break;
					case 8://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x62;//addr = 25111
					ETH_OUT_Tx_Buffer[9] = 0x17;
					}break;
					case 9://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x62;//addr = 25113
					ETH_OUT_Tx_Buffer[9] = 0x19;
					}break;
					default :break;	
				}
				for(j=10;j<=ETH_IN_RX_size;j++)		
				{
					ETH_OUT_Tx_Buffer[j]=ETH_IN_Rx_Buffer[j];
				}
			}break;
			case 4:
			{
				switch(cmd_add)
				{
					case 1://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x09;//addr = 2340
						ETH_OUT_Tx_Buffer[9] = 0x24;
						change_add = 2340;
					}break;				
					default :break;	
				}
				ETH_OUT_Tx_Buffer[10] = ETH_IN_Rx_Buffer[10];
				ETH_OUT_Tx_Buffer[11] = ETH_IN_Rx_Buffer[11]+1;//2340,2341,2342	
			}break;
			case 1:
			{
				switch(cmd_add)
				{
					case 0://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x61;//addr = 24960
						ETH_OUT_Tx_Buffer[9] = 0x80;
						change_add = 24960;
						
						for(j=10;j<=ETH_IN_RX_size;j++)		
						{
							ETH_OUT_Tx_Buffer[j]=ETH_IN_Rx_Buffer[j];
						}
					}break;
					case 1://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x62;//addr = 25120
						ETH_OUT_Tx_Buffer[9] = 0x20;
						change_add = 25120;
						for(j=10;j<=ETH_IN_RX_size;j++)		
						{
							ETH_OUT_Tx_Buffer[j]=ETH_IN_Rx_Buffer[j];
						}
					}break;
					default :break;	
				}				
			}break;
			case 5:
			{
				switch(cmd_add)
				{
					case 0://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x61;//addr = 24960
						ETH_OUT_Tx_Buffer[9] = 0x80;
						change_add = 24960;
						
						for(j=10;j<=ETH_IN_RX_size;j++)		
						{
							ETH_OUT_Tx_Buffer[j]=ETH_IN_Rx_Buffer[j];
						}				
					}break;
					case 1://地址码	
					{
						ETH_OUT_Tx_Buffer[8] = 0x62;//addr = 25120
						ETH_OUT_Tx_Buffer[9] = 0x20;
						change_add = 25120;
						for(j=10;j<=ETH_IN_RX_size;j++)		
						{
							ETH_OUT_Tx_Buffer[j]=ETH_IN_Rx_Buffer[j];
						}
						if(ETH_IN_Rx_Buffer[10]==0xff)
						{
							ycqd_write_vaule = 0x02;//远程启动写1
						}
						else if(ETH_IN_Rx_Buffer[10]==0)
						{
							ycqd_write_vaule = 0x00;//远程启动写0
						}
					}break;
					default :break;	
				}
			}break;
			default :break;
		}		
	}
}*/

/*
void updata_protocol_data_analyze()
{
	uchar j;
	uint cmd_add;
	
	if(list_sel==list1)//地址码表1
	{
		for(j=0;j<7;j++)		
		{
			ETH_IN_Tx_Buffer[j]=ETH_OUT_Rx_Buffer[j];
		}		
		//ETH_IN_Tx_Buffer[7] = Modbus_pc_cmd;//恢复PC机发下来的命令码
		ETH_IN_Tx_Buffer[7] = ETH_OUT_Rx_Buffer[7];//恢复PC机发下来的命令码
		ETH_IN_Tx_Buffer[8]=ETH_OUT_Rx_Buffer[8];//返回字节数
		
		if((change_add==25104)&&(Modbus_pc_cmd==0x02))
		{
			if(ETH_OUT_Rx_Buffer[8]==0)//返回字节数
			{
				for(j=9;j<=ETH_OUT_RX_size;j++)		
				{
					ETH_IN_Tx_Buffer[j]=ETH_OUT_Rx_Buffer[j];
				}
			}
			else if(ETH_OUT_Rx_Buffer[8]==1)//接收字节数为1，bit位顺序处理
			{				
				for(j=9;j<=ETH_OUT_RX_size;j++)		
				{
					ETH_IN_Tx_Buffer[j]=ETH_OUT_Rx_Buffer[j];
				}				
			}
		}
		else if((change_add==2340)&&(Modbus_pc_cmd==0x04))//每个地址双字节回复数据
		{
			ETH_IN_Tx_Buffer[8]=ETH_OUT_Rx_Buffer[8]-2;//返回字节数
			
			ETH_IN_Tx_Buffer[9]=ETH_OUT_Rx_Buffer[9];
			ETH_IN_Tx_Buffer[10]=ETH_OUT_Rx_Buffer[10];
			
			ETH_IN_Tx_Buffer[11]=ETH_OUT_Rx_Buffer[13];
			ETH_IN_Tx_Buffer[12]=ETH_OUT_Rx_Buffer[14];
			
			ETH_OUT_RX_size = ETH_OUT_RX_size -2;	
		}
		else if((change_add==25120)&&((Modbus_pc_cmd==0x05)||(Modbus_pc_cmd==0x01)))
		{
			for(j=9;j<=ETH_OUT_RX_size;j++)		
			{
				ETH_IN_Tx_Buffer[j]=ETH_OUT_Rx_Buffer[j];
			}			
		}
	}
	else if(list_sel==list2)//地址码表2
	{
		for(j=0;j<7;j++)		
		{
			ETH_IN_Tx_Buffer[j]=ETH_OUT_Rx_Buffer[j];
		}		
		//ETH_IN_Tx_Buffer[7] = Modbus_pc_cmd;//恢复PC机发下来的命令码
		ETH_IN_Tx_Buffer[7] = ETH_OUT_Rx_Buffer[7];//恢复PC机发下来的命令码
		ETH_IN_Tx_Buffer[8]=ETH_OUT_Rx_Buffer[8];//返回字节数
		
		if((change_add==25104)&&(Modbus_pc_cmd==0x02))
		{
			if(ETH_OUT_Rx_Buffer[8]==0)//返回字节数
			{
				for(j=9;j<=ETH_OUT_RX_size;j++)		
				{
					ETH_IN_Tx_Buffer[j]=ETH_OUT_Rx_Buffer[j];
				}
			}
			else if(ETH_OUT_Rx_Buffer[8]==1)//接收字节数为1，bit位顺序处理
			{
				low4bit_temp = ETH_OUT_Rx_Buffer[9]&0x0f;//取低4位
				high4bit_temp = (ETH_OUT_Rx_Buffer[9]<<1)&0xe0;//取移位后的高3位
				ETH_IN_Tx_Buffer[9] = low4bit_temp|high4bit_temp;
				
			}
			else if(ETH_OUT_Rx_Buffer[8]==2)//接收字节数为2，bit位顺序处理
			{
				temp_buf9 = ETH_OUT_Rx_Buffer[9];
				temp_buf10 = ETH_OUT_Rx_Buffer[10];
				
				b_H_add0 = temp_buf10&0x01;//备份高字节最低位
				b_L_add7 = temp_buf9&0x80;//备份低字节最高位
				ETH_IN_Tx_Buffer[10] = (temp_buf10&0x02)|(b_L_add7>>7);
				
				low4bit_temp = temp_buf9&0x0f;//取低4位
				high4bit_temp = (temp_buf9<<1)&0xe0;//取移位后的高3位
				ETH_IN_Tx_Buffer[9] = low4bit_temp|high4bit_temp|(b_H_add0<<4);				
			}
		}
		else if((change_add==2340)&&(Modbus_pc_cmd==0x04))
		{
			ETH_IN_Tx_Buffer[8]=ETH_OUT_Rx_Buffer[8]-2;//返回字节数
			
			ETH_IN_Tx_Buffer[9]=ETH_OUT_Rx_Buffer[9];
			ETH_IN_Tx_Buffer[10]=ETH_OUT_Rx_Buffer[10];
			
			ETH_IN_Tx_Buffer[11]=ETH_OUT_Rx_Buffer[13];
			ETH_IN_Tx_Buffer[12]=ETH_OUT_Rx_Buffer[14];
			
			ETH_OUT_RX_size = ETH_OUT_RX_size -2;	
		}
		else if((change_add==24960)&&(Modbus_pc_cmd==0x01))
		{
			ETH_IN_Tx_Buffer[9]=ETH_OUT_Rx_Buffer[9]|ycqd_write_vaule;//远程启动状态保持
		}
		else if((change_add==24960)&&(Modbus_pc_cmd==0x05))
		{
			for(j=9;j<=ETH_OUT_RX_size;j++)		
			{
				ETH_IN_Tx_Buffer[j]=ETH_OUT_Rx_Buffer[j];
			}
		}
		else if((change_add==25120)&&(Modbus_pc_cmd==0x05))
		{
			for(j=9;j<=ETH_OUT_RX_size;j++)		
			{
				ETH_IN_Tx_Buffer[j]=ETH_OUT_Rx_Buffer[j];
			}			
		}
	}
}*/
/*
uchar low4bit_temp,high4bit_temp,b_H_add0,b_L_add7;
uchar b_add0,b_add2;
uint change_add;
uchar temp_buf9,temp_buf10,ycqd_write_vaule;
*/

void ETH_OUT_Communication_PLC()//定时采集PLC数据
{
	uchar i;
	if(list_sel==list1)//地址码表1 25104-25111
	{
		for(i=0;i<5;i++)
		{
			ETH_OUT_Tx_Buffer[i]=0;
		}
		ETH_OUT_Tx_Buffer[5]=6;//legth
		ETH_OUT_Tx_Buffer[6]=1;//unit identifier
		
		if((ETH_OUT_function!=1)&&(ETH_OUT_function!=2))
		{
			ETH_OUT_function =1;
			ETH_OUT_Tx_Buffer[7]=1;//function
			
			ETH_OUT_Tx_Buffer[8]=0x62;
			ETH_OUT_Tx_Buffer[9]=0x20;//reference number 25120
			
			ETH_OUT_Tx_Buffer[10]=0;
			ETH_OUT_Tx_Buffer[11]=0x01;//bit count
		}
		else if(ETH_OUT_function!=2)
		{
			ETH_OUT_function =2;
			ETH_OUT_Tx_Buffer[7]=2;//function
			
			ETH_OUT_Tx_Buffer[8]=0x62;
			ETH_OUT_Tx_Buffer[9]=0x10;//reference number 25104
			
			ETH_OUT_Tx_Buffer[10]=0;
			ETH_OUT_Tx_Buffer[11]=0x08;//bit count
		}
		else if(ETH_OUT_function!=4)
		{
			ETH_OUT_function =4;
			ETH_OUT_Tx_Buffer[7]=4;//function
			
			ETH_OUT_Tx_Buffer[8]=0x09;
			ETH_OUT_Tx_Buffer[9]=0x24;//reference number 2340
			
			ETH_OUT_Tx_Buffer[10]=0;
			ETH_OUT_Tx_Buffer[11]=0x03;//word count
		}
		
		if(Read_Byte_W5200(ETH_OUT, Sn_SR(0)) == SOCK_ESTABLISHED)
		{
			S_tx_process(ETH_OUT, 0, 12);
		}
	}
	else if(list_sel==list2)//地址码表2 25104-25113
	{
		for(i=0;i<5;i++)
		{
			ETH_OUT_Tx_Buffer[i]=0;
		}
		ETH_OUT_Tx_Buffer[5]=6;//legth
		ETH_OUT_Tx_Buffer[6]=1;//unit identifier
		
		if((ETH_OUT_function!=1)&&(ETH_OUT_function!=2))
		{
			ETH_OUT_function =1;
			ETH_OUT_Tx_Buffer[7]=1;//function
			
			if(list2_function1_add==25120)
			{
				list2_function1_add=24960;
				ETH_OUT_Tx_Buffer[8]=0x61;
				ETH_OUT_Tx_Buffer[9]=0x80;//reference number 24960
			}
			else if(list2_function1_add==24960)
			{
				list2_function1_add=25120;
				ETH_OUT_Tx_Buffer[8]=0x62;
				ETH_OUT_Tx_Buffer[9]=0x20;//reference number 25120
			}
			
			ETH_OUT_Tx_Buffer[10]=0;
			ETH_OUT_Tx_Buffer[11]=0x01;//bit count
		}
		else if(ETH_OUT_function!=2)
		{
			ETH_OUT_function =2;
			ETH_OUT_Tx_Buffer[7]=2;//function
			
			ETH_OUT_Tx_Buffer[8]=0x62;
			ETH_OUT_Tx_Buffer[9]=0x10;//reference number 25104
			
			ETH_OUT_Tx_Buffer[10]=0;
			ETH_OUT_Tx_Buffer[11]=0x0a;//bit count
		}
		else if(ETH_OUT_function!=4)
		{
			ETH_OUT_function =4;
			ETH_OUT_Tx_Buffer[7]=4;//function
			
			ETH_OUT_Tx_Buffer[8]=0x09;
			ETH_OUT_Tx_Buffer[9]=0x24;//reference number 2340
			
			ETH_OUT_Tx_Buffer[10]=0;
			ETH_OUT_Tx_Buffer[11]=0x03;//word count
		}
		
		if(Read_Byte_W5200(ETH_OUT, Sn_SR(0)) == SOCK_ESTABLISHED)
		{
			S_tx_process(ETH_OUT, 0, 12);
		}
	}
}

void ETH_OUT_rec_PLC_data()
{
	if(list_sel==list1)//地址码表1 25104-25111
	{
		switch(ETH_OUT_Rx_Buffer[7])
		{
			case 1:
			{
				list1_function1_buf = ETH_OUT_Rx_Buffer[9];
			}break;
			case 2:
			{
				list1_function2_buf = ETH_OUT_Rx_Buffer[9];
			}break;
			case 4:
			{
				list1_function4_buf2340L = ETH_OUT_Rx_Buffer[9];
				list1_function4_buf2340H = ETH_OUT_Rx_Buffer[10];
				
				list1_function4_buf2342L = ETH_OUT_Rx_Buffer[13];
				list1_function4_buf2342H = ETH_OUT_Rx_Buffer[14];
			}break;
			default:break;
		}
		
		/*Uart1_TX(0x11);
		Uart1_TX(list1_function1_buf);
		Uart1_TX(0x12);
		Uart1_TX(list1_function2_buf);
		Uart1_TX(0x14);
		Uart1_TX(list1_function4_buf2340L);
		Uart1_TX(list1_function4_buf2340H);
		Uart1_TX(list1_function4_buf2342L);
		Uart1_TX(list1_function4_buf2342H);*/
	}
	else if(list_sel==list2)//地址码表2 25104-25113
	{
		switch(ETH_OUT_Rx_Buffer[7])
		{
			case 1:
			{
				if(list2_function1_add==24960)
				{
					list2_function1_buf24960 = ETH_OUT_Rx_Buffer[9];
				}
				else if(list2_function1_add==25120)
				{
					list2_function1_buf25120 = ETH_OUT_Rx_Buffer[9];
				}
				//list2_function1_buf = list2_function1_buf24960 |((list2_function1_buf25120<1)&0x02);
				list2_function1_buf = list2_function1_buf25120 |((list2_function1_buf24960<1)&0x02);
			}break;
			case 2:
			{
				temp_buf9 = ETH_OUT_Rx_Buffer[9];
				temp_buf10 = ETH_OUT_Rx_Buffer[10];
				
				b_H_add0 = temp_buf10&0x01;//备份高字节最低位
				b_L_add7 = temp_buf9&0x80;//备份低字节最高位
				list2_function2_bufH = (temp_buf10&0x02)|(b_L_add7>>7);
				
				low4bit_temp = temp_buf9&0x0f;//取低4位
				high4bit_temp = (temp_buf9<<1)&0xe0;//取移位后的高3位
				list2_function2_bufL = low4bit_temp|high4bit_temp|(b_H_add0<<4);	
			}break;
			case 4:
			{
				list2_function4_buf2340L = ETH_OUT_Rx_Buffer[9];
				list2_function4_buf2340H = ETH_OUT_Rx_Buffer[10];
				
				list2_function4_buf2342L = ETH_OUT_Rx_Buffer[13];
				list2_function4_buf2342H = ETH_OUT_Rx_Buffer[14];
			}break;
			default:break;
		}	
		/*Uart1_TX(0x21);
		Uart1_TX(list2_function1_buf24960);
		Uart1_TX(0x21);
		Uart1_TX(list2_function1_buf25120);
		Uart1_TX(0x22);
		Uart1_TX(list2_function2_bufL);
		Uart1_TX(list2_function2_bufH);
		Uart1_TX(0x24);
		Uart1_TX(list2_function4_buf2340L);
		Uart1_TX(list2_function4_buf2340H);
		Uart1_TX(list2_function4_buf2342L);
		Uart1_TX(list2_function4_buf2342H);	*/
	}
}

void ETH_IN_rec_PC_data()
{
	unsigned int iLen;
	uchar i,j;
	uint cmd_add;
	if(list_sel==list1)//地址码表1 25104-25111
	{
		for(i=0;i<5;i++)		
		{
			ETH_IN_Tx_Buffer[j]=0;
		}
				
		switch(ETH_IN_Rx_Buffer[7])
		{
			case 1:
			{
				ETH_IN_Tx_Buffer[5]=4;	//length
				ETH_IN_Tx_Buffer[6]=1;	//uint
				ETH_IN_Tx_Buffer[7]=ETH_IN_Rx_Buffer[7];//function
				ETH_IN_Tx_Buffer[8]=1;//byte count
				ETH_IN_Tx_Buffer[9]=list1_function1_buf;//data		
				
				if(Read_Byte_W5200(ETH_IN, Sn_SR(0)) == SOCK_ESTABLISHED)
				{
					S_tx_process(ETH_IN, 0, 10);
				}	
			}break;
			case 2://命令码
			{
				ETH_IN_Tx_Buffer[5]=4;	//length
				ETH_IN_Tx_Buffer[6]=1;	//uint
				ETH_IN_Tx_Buffer[7]=ETH_IN_Rx_Buffer[7];//function
				ETH_IN_Tx_Buffer[8]=1;//byte count
				ETH_IN_Tx_Buffer[9]=list1_function2_buf;//data
				
				if(Read_Byte_W5200(ETH_IN, Sn_SR(0)) == SOCK_ESTABLISHED)
				{
					S_tx_process(ETH_IN, 0, 10);
				}	
			}break;
			case 4:
			{
				if(ETH_IN_Rx_Buffer[11]==1)
				{
					ETH_IN_Tx_Buffer[5]=5;	//length
					ETH_IN_Tx_Buffer[6]=1;	//uint
					ETH_IN_Tx_Buffer[7]=ETH_IN_Rx_Buffer[7];//function
					ETH_IN_Tx_Buffer[8]=2;//byte count
					ETH_IN_Tx_Buffer[9]=list1_function4_buf2340L;//data	
					ETH_IN_Tx_Buffer[10]=list1_function4_buf2340H;//data	
					
					if(Read_Byte_W5200(ETH_IN, Sn_SR(0)) == SOCK_ESTABLISHED)
					{
						S_tx_process(ETH_IN, 0, 11);
					}
				}
				else if(ETH_IN_Rx_Buffer[11]==2)
				{
					ETH_IN_Tx_Buffer[5]=7;	//length
					ETH_IN_Tx_Buffer[6]=1;	//uint
					ETH_IN_Tx_Buffer[7]=ETH_IN_Rx_Buffer[7];//function
					ETH_IN_Tx_Buffer[8]=4;//byte count
					ETH_IN_Tx_Buffer[9]=list1_function4_buf2340L;//data	
					ETH_IN_Tx_Buffer[10]=list1_function4_buf2340H;//data
					ETH_IN_Tx_Buffer[11]=list1_function4_buf2342L;//data	
					ETH_IN_Tx_Buffer[12]=list1_function4_buf2342H;//data
					
					if(Read_Byte_W5200(ETH_IN, Sn_SR(0)) == SOCK_ESTABLISHED)
					{
						S_tx_process(ETH_IN, 0, 13);
					}
				}
			}break;
			
			case 5:
			{
				cmd_add =((ETH_IN_Rx_Buffer[8]*256)+ETH_IN_Rx_Buffer[9]);
				if(cmd_add==1)//地址码	
				{
					////回复PC/////
					for(j=0;j<ETH_IN_RX_size;j++)
					{
						ETH_IN_Tx_Buffer[j] = ETH_IN_Rx_Buffer[j];
					}
					if(Read_Byte_W5200(ETH_IN, Sn_SR(0)) == SOCK_ESTABLISHED)
					{
						S_tx_process(ETH_IN, 0, ETH_IN_RX_size);
					}
					
					/////下发PLC/////////
					for(j=0;j<7;j++)		
					{
						ETH_OUT_Tx_Buffer[j]=ETH_IN_Rx_Buffer[j];
					}
					
					ETH_OUT_Tx_Buffer[7]=ETH_IN_Rx_Buffer[7];
					
					ETH_OUT_Tx_Buffer[8] = 0x62;//addr = 25120
					ETH_OUT_Tx_Buffer[9] = 0x20;
					
					for(j=10;j<=ETH_IN_RX_size;j++)		
					{
						ETH_OUT_Tx_Buffer[j]=ETH_IN_Rx_Buffer[j];
					}
					
					if(Read_Byte_W5200(ETH_OUT, Sn_SR(0)) == SOCK_ESTABLISHED)
					{
						S_tx_process(ETH_OUT, 0, ETH_IN_RX_size);
					}			
				}			
			}break;
			default :break;
		}		
	}
	else if(list_sel==list2)//地址码表2 25104-25113
	{
		ModBusParseRequest(ETH_IN_Rx_Buffer, ETH_IN_Tx_Buffer, &iLen);
#if 1
		if(Read_Byte_W5200(ETH_IN, Sn_SR(0)) == SOCK_ESTABLISHED)
		{
			S_tx_process(ETH_IN, 0, iLen);
		}
#endif
	}
}




