///////宏定义///////////////

///////////////////////////////////////////////////////////////
#define uchar	unsigned char
#define uint	unsigned int

#define INPUT		1
#define OUTPUT		0

#define LED_ON		0
#define LED_OFF		1

#define TIME_OFF	0
#define TIME_OUT	1

#define normal_status	0
#define test_stutas		1

#define SYS_ID  0x01

#define EEPROM_set_flag_add  	 0x00

#define EEPROM_sel_list  	 	 0x05

#define EEPROM_ETHIN_GAR_add0	 0x10
#define EEPROM_ETHIN_GAR_add1	 0x11
#define EEPROM_ETHIN_GAR_add2	 0x12
#define EEPROM_ETHIN_GAR_add3	 0x13

#define EEPROM_ETHIN_SUBR_add0	 0x14
#define EEPROM_ETHIN_SUBR_add1	 0x15
#define EEPROM_ETHIN_SUBR_add2	 0x16
#define EEPROM_ETHIN_SUBR_add3	 0x17

#define EEPROM_ETHIN_MAC_add0	 0x18
#define EEPROM_ETHIN_MAC_add1	 0x19
#define EEPROM_ETHIN_MAC_add2	 0x1a
#define EEPROM_ETHIN_MAC_add3	 0x1b
#define EEPROM_ETHIN_MAC_add4	 0x1c
#define EEPROM_ETHIN_MAC_add5	 0x1d

#define EEPROM_ETHIN_IP_add0	  0x1e
#define EEPROM_ETHIN_IP_add1	  0x1f
#define EEPROM_ETHIN_IP_add2	  0x20
#define EEPROM_ETHIN_IP_add3	  0x21

#define EEPROM_ETHIN_S0_SPORT_add0	  0x22
#define EEPROM_ETHIN_S0_SPORT_add1	  0x23

#define EEPROM_ETHIN_S0_DIP_add0	  0x24
#define EEPROM_ETHIN_S0_DIP_add1	  0x25
#define EEPROM_ETHIN_S0_DIP_add2	  0x26
#define EEPROM_ETHIN_S0_DIP_add3	  0x27

#define EEPROM_ETHIN_S0_DPORT_add0	  0x28
#define EEPROM_ETHIN_S0_DPORT_add1	  0x29

#define EEPROM_ETHOUT_GAR_add0	 0x30
#define EEPROM_ETHOUT_GAR_add1	 0x31
#define EEPROM_ETHOUT_GAR_add2	 0x32
#define EEPROM_ETHOUT_GAR_add3	 0x33

#define EEPROM_ETHOUT_SUBR_add0	 0x34
#define EEPROM_ETHOUT_SUBR_add1	 0x35
#define EEPROM_ETHOUT_SUBR_add2	 0x36
#define EEPROM_ETHOUT_SUBR_add3	 0x37

#define EEPROM_ETHOUT_MAC_add0	 0x38
#define EEPROM_ETHOUT_MAC_add1	 0x39
#define EEPROM_ETHOUT_MAC_add2	 0x3a
#define EEPROM_ETHOUT_MAC_add3	 0x3b
#define EEPROM_ETHOUT_MAC_add4	 0x3c
#define EEPROM_ETHOUT_MAC_add5	 0x3d

#define EEPROM_ETHOUT_IP_add0	 0x3e
#define EEPROM_ETHOUT_IP_add1	 0x3f
#define EEPROM_ETHOUT_IP_add2	 0x40
#define EEPROM_ETHOUT_IP_add3	 0x41

#define EEPROM_ETHOUT_S0_SPORT_add0	  0x42
#define EEPROM_ETHOUT_S0_SPORT_add1	  0x43

#define EEPROM_ETHOUT_S0_DIP_add0	  0x44
#define EEPROM_ETHOUT_S0_DIP_add1	  0x45
#define EEPROM_ETHOUT_S0_DIP_add2	  0x46
#define EEPROM_ETHOUT_S0_DIP_add3	  0x47

#define EEPROM_ETHOUT_S0_DPORT_add0	  0x48
#define EEPROM_ETHOUT_S0_DPORT_add1	  0x49



#define RX1_REC_OK	1
#define RX1_REC_ERR	0

// 原来值
#define ETH_IN		0//设为服务器
#define ETH_OUT		1//设为客户端

#define CMD_VALID       0
#define CMD_INVALID     -1
#define CDM_PACKAGE_H   6//六个起始字节：事务处理标示符（2byte），协议标示符（2byte），长度（2byte）

#define TCP_SERVER		0
#define TCP_CLIENT		1

#define SOCKET_OPEN_ERR 1
#define SOCKET_OPEN_OK	2
#define	SOCKET_CONNECT_ERR	3
#define	SOCKET_CONNECT_OK	4

#define	PHY_Link_ERR	1
#define	PHY_Link_OK		2

#define	nochange		0
#define	change			1

#define OPEN            1
#define CLOSED          0

#define list1			1
#define list2			2

/////////////////////////////////////////////////////////////
struct 
{
	unsigned char GATEWAY[4];//网关地址
	unsigned char SUBNET[4];//子网掩码
	unsigned char MAC_ADDR[6];//本机MAC地址
	unsigned char IP[4];//本机IP地址

	unsigned char S0_SPORT[2];// SOCKET 端口号
	unsigned char S0_DIP[4];//目的地IP地址
	unsigned char S0_DPORT[2];//目的地 端口号
}ETH_set_LIST[2];
/////////////////////////////////////////////////////////////
extern uchar RX1_REG,RX1_Receive;

extern uchar Work_stutas,test_sync,Module_change_state;
extern uchar TP_Timer;
extern uchar ETH_IN_Event_en;
extern uchar ETH_OUT_Event_en;
extern uchar ETH_IN_PHY_Link_STA,ETH_OUT_PHY_Link_STA;

extern uchar S_DIP[],S_DPORT[];
extern uchar ETH_IN_MODE,ETH_OUT_MODE;
extern bank1 uchar ETH_IN_Rx_Buffer[],ETH_OUT_Rx_Buffer[];
extern bank2 uchar ETH_IN_Tx_Buffer[],ETH_OUT_Tx_Buffer[];
extern uchar ETH_IN_SOCKET_Status,ETH_OUT_SOCKET_Status;
extern uchar ETH_IN_Link_Status,ETH_OUT_Link_Status;
extern bank3 uchar net_switch;
extern uint ETH_IN_RX_size,ETH_OUT_RX_size,Modbus_pc_cmd;
extern uchar list_sel;
extern uchar low4bit_temp,high4bit_temp,b_H_add0,b_L_add7;
extern uchar b_add0,b_add2;
extern uint change_add;
extern uchar temp_buf9,temp_buf10,ycqd_write_vaule;
//extern Para ETH_set_LIST[];//ETH_IN=ETH_LIST[0],ETH_OUT=ETH_LIST[1];

extern uchar TIMER1_count,TIMER1_stutas;
extern uchar ETH_OUT_function;
extern uint list2_function1_add;
extern uchar list1_function1_buf,list1_function2_buf,list1_function4_buf2340L,list1_function4_buf2340H,list1_function4_buf2342L,list1_function4_buf2342H;
extern uchar list2_function1_buf24960,list2_function1_buf25120,list2_function2_bufL,list2_function2_bufH,list2_function4_buf2340L,list2_function4_buf2340H,list2_function4_buf2342L,list2_function4_buf2342H,list2_function1_buf;

//////////////////////////////////////////////////////////////
extern void port_init(void);
extern void PORT_State_Init();
extern void delay_1ms(uint time);//1ms delay

extern void Write_EEPROM(uchar temp_add,uchar temp_data);
extern uchar Read_EEPROM(uchar temp_add);
extern void EEPROM_Init();
extern void EEPROM_update();

extern void Uart1_TX(uchar temp_tx);
extern void Uart1_RX();

extern void Test_work_init();
extern void normal_work_init();
extern void Test_NET_Transmission_detection();
extern void Socket_LINK_OFF_DET();
extern void ETH_IN_Event();
extern void ETH_OUT_Event();
extern unsigned char Detect_Gateway(uchar channal);
extern void ETH_Init();
extern uchar Read_Byte_W5200(uchar channal,uint addr);
extern unsigned char Read_IR(uchar channal,uchar s);
extern unsigned int Read_RSR(uchar channal,uchar s);
extern unsigned char Read_SR(uchar channal,uchar s);
extern void Read_W5200(uchar channal,uint Reg_Addr,uchar *Data_ptr,uint Data_Size);
extern unsigned int S_rx_process(uchar channal,uchar s);
extern unsigned char S_tx_process(uchar channal,uchar s, unsigned int tx_size);
extern void Socket_Config(uchar channal,uchar s);
extern void Socket_connect_init(uchar channal,uchar s);
extern void Socket_Listen_init(uchar channal,uchar s);
extern void W5200_Config(uchar channal);
extern void Write_Byte_W5200(uchar channal,uint addr, uchar dat);
extern void Write_W5200(uchar channal,uint Reg_Addr,uchar *Data_ptr, uint Data_Size);
extern void download_protocol_add_analyze();
extern void updata_protocol_data_analyze();

extern void ETH_OUT_Communication_PLC();
extern void ETH_OUT_rec_PLC_data();
extern void ETH_IN_rec_PC_data();
//extern void ETH_PHY_Check();

//extern void protocol_convert(void);
extern void receive_convert();
extern void Uart_clear_flag();

extern int request_convert( unsigned char cnts, unsigned char *cmd_flag );
extern int respond_convert( unsigned char cnts, unsigned char *cmd_flag );
/*

extern ;
extern ;
extern ;
extern ;
extern ;
extern ;
extern ;
extern ;
extern ;
extern ;
extern ;
extern ;
extern ;
extern ;
extern ;
extern ;
extern ;
extern ;
extern ;
extern ;
extern ;*/
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
#define  Test_led0     		PORTAbits.RA0		// MCU 输出口
#define  Test_led1   		PORTAbits.RA1		// MCU 输出口
#define  Test_led2			PORTAbits.RA2		// MCU 输出口
#define  Test_led3			PORTAbits.RA3		// MCU 输出口
#define  LED_Run     		PORTAbits.RA4		// MCU 输出口

#define  ETH_SPI_INT		PORTBbits.RB0		// MCU 输入口
#define  ETH_OUT_SPI2_CLK2	PORTBbits.RB1		// MCU 输出口
#define  ETH_OUT_SPI2_MISO2	PORTBbits.RB2		// MCU 输入口
#define  ETH_OUT_SPI2_MOSI2	PORTBbits.RB3     	// MCU 输出口	
#define  ETH_OUT_SPI2_CS2	PORTBbits.RB4     	// MCU 输出口
#define  ETH_RST			PORTBbits.RB5		// MCU 输出口

#define  ETH_OUT_INT2		PORTCbits.RC0		// MCU 输入口
#define  ETH_IN_INT1		PORTCbits.RC1		// MCU 输入口
#define  ETH_IN_SPI1_CS1	PORTCbits.RC2		// MCU 输出口
#define  ETH_IN_SPI1_CLK1	PORTCbits.RC3     	// MCU 输出口	
#define  ETH_IN_SPI1_MISO1	PORTCbits.RC4    		// MCU 输入口
#define  ETH_IN_SPI1_MOSI1	PORTCbits.RC5		// MCU 输出口
#define  MCU_TXD			PORTCbits.RC6     	// MCU 输出口
#define  MCU_RXD			PORTCbits.RC7		// MCU 输入口

///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
#define  Test_led0_SET     			TRISA0		// MCU 输出口
#define  Test_led1_SET   			TRISA1		// MCU 输出口
#define  Test_led2_SET				TRISA2		// MCU 输出口
#define  Test_led3_SET				TRISA3		// MCU 输出口  
#define  LED_Run_SET     			TRISA4		// MCU 输出口  
                                                           
#define  ETH_SPI_INT_SET			TRISB0		// MCU 输入口  
#define  ETH_OUT_SPI2_CLK2_SET		TRISB1		// MCU 输出口  
#define  ETH_OUT_SPI2_MISO2_SET		TRISB2		// MCU 输入口  
#define  ETH_OUT_SPI2_MOSI2_SET		TRISB3     	// MCU 输出口	
#define  ETH_OUT_SPI2_CS2_SET		TRISB4     	// MCU 输出口  
#define  ETH_RST_SET				TRISB5		// MCU 输出口  
                                                           
#define  ETH_OUT_INT2_SET			TRISC0		// MCU 输入口  
#define  ETH_IN_INT1_SET			TRISC1		// MCU 输入口  
#define  ETH_IN_SPI1_CS1_SET		TRISC2		// MCU 输出口  
#define  ETH_IN_SPI1_CLK1_SET		TRISC3    	// MCU 输出口	
#define  ETH_IN_SPI1_MISO1_SET		TRISC4    	// MCU 输入口  
#define  ETH_IN_SPI1_MOSI1_SET		TRISC5		// MCU 输出口  
#define  MCU_TXD_SET				TRISC6     	// MCU 输出口  
#define  MCU_RXD_SET				TRISC7		// MCU 输入口  
 
///////////////////////////////////////////////////////////////