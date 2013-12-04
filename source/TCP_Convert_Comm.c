#include<pic18.h>
#include<math.h>
#include"TCP_Convert_define_Init.h"
#include "uart.h"

bank3 host_packet_obj  receive_val;
bank3 slave_packet_obj send_val;

void set_net_cfg(int cmd);
void respond_cfg_info(int cmd);

extern UART_Obj *hUart;
void receive_convert()
{
	unsigned char rval;
	
	rval = analysis_uart_info( (unsigned char*)&receive_val, HOST_CMD_LEN );
	//INT0IE = 1;
	
	switch(rval)
	{
		case SET_DOWN_CMD:
			{
				set_net_cfg(rval);
				Uart_clear_flag();
			}break;
		
		case GET_DOWN_CMD:
			{
				respond_cfg_info(rval);
				Uart_clear_flag();
			}break;
		
		case SET_UP_CMD:
			{
				set_net_cfg(rval);
				Uart_clear_flag();
			}break;
		
		case GET_UP_CMD:
			{
				respond_cfg_info(rval);
				Uart_clear_flag();
			}break;
		
		case SET_TEST_CMD:
			{
				Work_stutas = test_stutas;
				Uart1_TX(0x54);
				Module_change_state = change;
				Uart_clear_flag();
			}break;
		
		case CANCEL_TEST_CMD:
			{
				 Work_stutas = normal_status;
				 Uart1_TX(0x4e);
				 Module_change_state = change;
				 Uart_clear_flag();
			}break;
			
		case SEL_LIST1_CMD:
			{
				 Uart1_TX(0x4c);
				 Uart1_TX(0x31);
				 Write_EEPROM(EEPROM_sel_list,list1);
				 Uart_clear_flag();
				 RESET();
			}break;
			
		case SEL_LIST2_CMD:
			{
				 Uart1_TX(0x4c);
				 Uart1_TX(0x32);
				 Write_EEPROM(EEPROM_sel_list,list2);
				 Uart_clear_flag();
				 RESET();
			}break;
		
		default :Uart_clear_flag();break;		
	}	
}


void Uart_clear_flag()
{
	uchar i;
	hUart->rlen  = 0;
	/*for(i = 0; i < HOST_CMD_LEN; i++)
	{ 
		*(hUart->r_w++) = 0x00;
	}*/
}



void respond_cfg_info(int cmd)
{
	int i;
	unsigned int sum;
	unsigned char *ptr;
	
	switch(cmd)
	{
	case SET_DOWN_CMD:
	case GET_DOWN_CMD:
	{
		send_val.syn1 = UART_SYN1;	
		send_val.syn2 = UART_SYN2;
		if(cmd == SET_DOWN_CMD)
		{
			send_val.recmd  = SET_DOWN_CMD | 0x80;
		}else{
			send_val.recmd  = GET_DOWN_CMD | 0x80;
		}			
		send_val.rsv0 = 0x00;
					
		for(i=0;i<4;i++)
		{
			send_val.gateway[i]      = ETH_set_LIST[0].GATEWAY[i]; 
			send_val.netmask[i]      = ETH_set_LIST[0].SUBNET[i]; 
			send_val.far_ip[i]       = ETH_set_LIST[0].S0_DIP[i]; 
			send_val.local_ip[i]     = ETH_set_LIST[0].IP[i]; 
		}
		
		for(i=0;i<6;i++)
		{
			send_val.local_mac[i]    = ETH_set_LIST[0].MAC_ADDR[i];
		}
		
		for(i=0;i<2;i++)
		{
			send_val.local_port[i]   = ETH_set_LIST[0].S0_SPORT[i];
			send_val.far_port[i]     = ETH_set_LIST[0].S0_DPORT[i];
		}
		
		send_val.rsv1 = 0x00;
		
		sum = 0;
		ptr = (unsigned char*)(&send_val);
		for(i = 0; i < SLAVE_CMD_LEN - 1; i++)
		{
			sum += ptr[i];
		}
		
		send_val.sum = sum & 0xff;
		
		uart_write_uart((unsigned char *)&send_val, SLAVE_CMD_LEN);
	}break;
//uart_write_uart('a', 1);		
	case SET_UP_CMD:
	case GET_UP_CMD:
	{
		send_val.syn1 = UART_SYN1;	
		send_val.syn2 = UART_SYN2;
		if(cmd == SET_UP_CMD)
		{
			send_val.recmd  = SET_UP_CMD | 0x80;
		}else{
			send_val.recmd  = GET_UP_CMD | 0x80;
		}			
		send_val.rsv0 = 0x00;
					
		for(i=0;i<4;i++)
		{
			send_val.gateway[i]      = ETH_set_LIST[1].GATEWAY[i]; 
			send_val.netmask[i]      = ETH_set_LIST[1].SUBNET[i]; 
			send_val.far_ip[i]       = ETH_set_LIST[1].S0_DIP[i]; 
			send_val.local_ip[i]     = ETH_set_LIST[1].IP[i]; 
		}
		
		for(i=0;i<6;i++)
		{
			send_val.local_mac[i]    = ETH_set_LIST[1].MAC_ADDR[i];
		}
		
		for(i=0;i<2;i++)
		{
			send_val.local_port[i]   = ETH_set_LIST[1].S0_SPORT[i];
			send_val.far_port[i]     = ETH_set_LIST[1].S0_DPORT[i];
		}
		
		send_val.rsv1 = 0x00;
		
		sum = 0;
		ptr = (unsigned char*)(&send_val);
		for(i = 0; i < SLAVE_CMD_LEN - 1; i++)
		{
			sum += ptr[i];
		}
		
		send_val.sum = sum & 0xff;
		
		uart_write_uart(ptr, SLAVE_CMD_LEN);
		
	}break;
	
	default :break;		
	}
}

void set_net_cfg(int cmd)
{
	int i;
	
	switch(cmd)
	{
	case SET_DOWN_CMD:
	{
		for(i=0;i<4;i++)
		{
			ETH_set_LIST[0].GATEWAY[i]  = receive_val.gateway[i];
			ETH_set_LIST[0].SUBNET[i]   = receive_val.netmask[i];
			ETH_set_LIST[0].S0_DIP[i]   = receive_val.far_ip[i];
			ETH_set_LIST[0].IP[i]       = receive_val.local_ip[i];
		}
		
		for(i=0;i<6;i++)
		{
			ETH_set_LIST[0].MAC_ADDR[i] = receive_val.local_mac[i];
		}
		
		for(i=0;i<2;i++)
		{
			ETH_set_LIST[0].S0_SPORT[i] = receive_val.local_port[i];
			ETH_set_LIST[0].S0_DPORT[i] = receive_val.far_port[i];
		}
		
		EEPROM_update();
		delay_1ms(50);
		RESET();
	}break;
	case SET_UP_CMD:
	{
		for(i=0;i<4;i++)
		{
			ETH_set_LIST[1].GATEWAY[i]  = receive_val.gateway[i];
			ETH_set_LIST[1].SUBNET[i]   = receive_val.netmask[i];
			ETH_set_LIST[1].S0_DIP[i]   = receive_val.far_ip[i];
			ETH_set_LIST[1].IP[i]       = receive_val.local_ip[i];
		}                               
		
		for(i=0;i<6;i++)
		{
			ETH_set_LIST[1].MAC_ADDR[i] = receive_val.local_mac[i];
		}
		
		for(i=0;i<2;i++)
		{
			ETH_set_LIST[1].S0_SPORT[i] = receive_val.local_port[i];
			ETH_set_LIST[1].S0_DPORT[i] = receive_val.far_port[i];
		}
		
		EEPROM_update();
		delay_1ms(50);
		RESET();
	}break;
	default :break;		
	}
}
