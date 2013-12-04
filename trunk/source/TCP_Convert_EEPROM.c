////TCP_Convert EEPROM///////////////////////////
#include<pic18.h>
#include<math.h>
#include"TCP_Convert_define_Init.h"
#include"TCP_Convert_W5200.h"



/////////////写EEPROM////////////////////
void Write_EEPROM(uchar temp_add,uchar temp_data)
{
	 
	WRERR = 0;
	EEADR = temp_add;
	EEDATA = temp_data;
	EEPGD = 0;//访问EEPROM
	CFGS = 0;
	WREN = 1;
	GIE = 0; 
	
	EECON2 = 0x55;
	EECON2 = 0xaa;
	WR = 1;
	while(WR==1);	
	WREN = 0;	
	GIE = 1; 
}

uchar Read_EEPROM(uchar temp_add)
{
	EEADR = temp_add;
	EEPGD = 0;//访问EEPROM
	CFGS = 0;
	RD=1;
	NOP();
	NOP();
	return(EEDATA);	
}
	
void EEPROM_Init()
{
	uchar i;
	if(Read_EEPROM(EEPROM_set_flag_add)!=0x5a)
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
		ETH_set_LIST[0].S0_DIP[3] = 201;

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
		
		list_sel = list2;//地址表选择
		
		for(i=0;i<4;i++)
		{
			Write_EEPROM(EEPROM_ETHIN_GAR_add0 +i,ETH_set_LIST[0].GATEWAY[i]);//写入 ETH IN 网关
			Write_EEPROM(EEPROM_ETHOUT_GAR_add0 +i,ETH_set_LIST[1].GATEWAY[i]);//写入 ETH OUT 网关
		}
		
		for(i=0;i<4;i++)
		{
			Write_EEPROM(EEPROM_ETHIN_SUBR_add0 +i,ETH_set_LIST[0].SUBNET[i]);//写入 ETH IN 子网掩码
			Write_EEPROM(EEPROM_ETHOUT_SUBR_add0 +i,ETH_set_LIST[1].SUBNET[i]);//写入 ETH OUT 子网掩码
		}
		
		for(i=0;i<6;i++)
		{
			Write_EEPROM(EEPROM_ETHIN_MAC_add0 +i,ETH_set_LIST[0].MAC_ADDR[i]);//写入 ETH IN 本机MAC地址
			Write_EEPROM(EEPROM_ETHOUT_MAC_add0 +i,ETH_set_LIST[1].MAC_ADDR[i]);//写入 ETH OUT 本机MAC地址
		}
		
		for(i=0;i<4;i++)
		{
			Write_EEPROM(EEPROM_ETHIN_IP_add0 +i,ETH_set_LIST[0].IP[i]);//写入 ETH IN 本机IP地址
			Write_EEPROM(EEPROM_ETHOUT_IP_add0 +i,ETH_set_LIST[1].IP[i]);//写入 ETH OUT 本机IP地址
		}
		
		for(i=0;i<2;i++)
		{
			Write_EEPROM(EEPROM_ETHIN_S0_SPORT_add0 +i,ETH_set_LIST[0].S0_SPORT[i]);//写入 ETH IN SOCKET 端口号
			Write_EEPROM(EEPROM_ETHOUT_S0_SPORT_add0 +i,ETH_set_LIST[1].S0_SPORT[i]);//写入 ETH OUT SOCKET 端口号
		}
		
		for(i=0;i<4;i++)
		{
			Write_EEPROM(EEPROM_ETHIN_S0_DIP_add0 +i,ETH_set_LIST[0].S0_DIP[i]);//写入 ETH IN 目的地IP地址
			Write_EEPROM(EEPROM_ETHOUT_S0_DIP_add0 +i,ETH_set_LIST[1].S0_DIP[i]);//写入 ETH OUT 目的地IP地址
		}
		
		for(i=0;i<2;i++)
		{
			Write_EEPROM(EEPROM_ETHIN_S0_DPORT_add0 +i,ETH_set_LIST[0].S0_DPORT[i]);//写入 ETH IN 目的地 端口号
			Write_EEPROM(EEPROM_ETHOUT_S0_DPORT_add0 +i,ETH_set_LIST[1].S0_DPORT[i]);//写入 ETH OUT 目的地 端口号
		}
	
		Write_EEPROM(EEPROM_sel_list,list_sel);
		////////////////////////////////////////////////////////////////////////////
		Write_EEPROM(EEPROM_set_flag_add,0x5a);
		//RESET();
		//Test_led3 = 0;
	}
	else
	{		
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
		
		list_sel =  Read_EEPROM(EEPROM_sel_list);
		//Test_led3 = 0;
	}
}

void EEPROM_update()
{
	int i;
	
	for(i=0;i<4;i++)
	{
		Write_EEPROM(EEPROM_ETHIN_GAR_add0 +i,ETH_set_LIST[0].GATEWAY[i]);//写入 ETH IN 网关
		Write_EEPROM(EEPROM_ETHOUT_GAR_add0 +i,ETH_set_LIST[1].GATEWAY[i]);//写入 ETH OUT 网关
	}
	
	for(i=0;i<4;i++)
	{
		Write_EEPROM(EEPROM_ETHIN_SUBR_add0 +i,ETH_set_LIST[0].SUBNET[i]);//写入 ETH IN 子网掩码
		Write_EEPROM(EEPROM_ETHOUT_SUBR_add0 +i,ETH_set_LIST[1].SUBNET[i]);//写入 ETH OUT 子网掩码
	}
	
	for(i=0;i<6;i++)
	{
		Write_EEPROM(EEPROM_ETHIN_MAC_add0 +i,ETH_set_LIST[0].MAC_ADDR[i]);//写入 ETH IN 本机MAC地址
		Write_EEPROM(EEPROM_ETHOUT_MAC_add0 +i,ETH_set_LIST[1].MAC_ADDR[i]);//写入 ETH OUT 本机MAC地址
	}
	
	for(i=0;i<4;i++)
	{
		Write_EEPROM(EEPROM_ETHIN_IP_add0 +i,ETH_set_LIST[0].IP[i]);//写入 ETH IN 本机IP地址
		Write_EEPROM(EEPROM_ETHOUT_IP_add0 +i,ETH_set_LIST[1].IP[i]);//写入 ETH OUT 本机IP地址
	}
	
	for(i=0;i<2;i++)
	{
		Write_EEPROM(EEPROM_ETHIN_S0_SPORT_add0 +i,ETH_set_LIST[0].S0_SPORT[i]);//写入 ETH IN SOCKET 端口号
		Write_EEPROM(EEPROM_ETHOUT_S0_SPORT_add0 +i,ETH_set_LIST[1].S0_SPORT[i]);//写入 ETH OUT SOCKET 端口号
	}
	
	for(i=0;i<4;i++)
	{
		Write_EEPROM(EEPROM_ETHIN_S0_DIP_add0 +i,ETH_set_LIST[0].S0_DIP[i]);//写入 ETH IN 目的地IP地址
		Write_EEPROM(EEPROM_ETHOUT_S0_DIP_add0 +i,ETH_set_LIST[1].S0_DIP[i]);//写入 ETH OUT 目的地IP地址
	}
	
	for(i=0;i<2;i++)
	{
		Write_EEPROM(EEPROM_ETHIN_S0_DPORT_add0 +i,ETH_set_LIST[0].S0_DPORT[i]);//写入 ETH IN 目的地 端口号
		Write_EEPROM(EEPROM_ETHOUT_S0_DPORT_add0 +i,ETH_set_LIST[1].S0_DPORT[i]);//写入 ETH OUT 目的地 端口号
	}
}

