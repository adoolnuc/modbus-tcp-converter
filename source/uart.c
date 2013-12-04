#include <pic18.h>
#include "uart.h"
#include"TCP_Convert_define_Init.h"

bank1 static UART_Obj g_uart;
UART_Obj *hUart;
//host_packet_obj host_cmd;//信息
unsigned char *cmd_str;
unsigned char bSync = 0;
bank3 unsigned char syn_head[2];

unsigned char init_uart()
{
	// 设置读缓冲
	g_uart.r_r   = &(g_uart.rbuf[0]);
	g_uart.r_w   = g_uart.r_r;
	g_uart.r_e   = g_uart.r_r + UART_BUF_LEN;
	g_uart.bSync = 0;
	g_uart.rlen  = 0;
	hUart = &g_uart;

	return 0;
}

unsigned char uart_get_char( )
{
	unsigned char c;
	if(g_uart.r_r != g_uart.r_w){
		c = *g_uart.r_r++;
		if(g_uart.r_r>=g_uart.r_e)	g_uart.r_r = &(g_uart.rbuf[0]);
		
		return c;
	}
	
	return 0;
}

int uart_read(unsigned char *buf, int max_len)     //指针数组，由256个指向char型数据的指针元素组成
{
	int len;
	int i ;

	hUart = &g_uart;
	if(max_len >= UART_BUF_LEN)  max_len = UART_BUF_LEN;  //限定最大max_len长度不大于UART_BUF_LEN
	len = hUart->r_w - hUart->r_r;
	if( len < 0 ) len += UART_BUF_LEN;

	if(len <max_len){                                                    
		return 0;   //无法读取足够的数据
	}

	if(hUart->r_w>hUart->r_r){
		for( i = 0; i < max_len; i++)
		{
			buf[i] = *(hUart->r_r++);
		}

	}else{
		/*分两次拷贝数据*/
		/*....w....r....*/
 		len = hUart->r_e - hUart->r_r;
		//memcpy(buf,hUart->r_r,len);
		if(len < max_len){
			//memcpy(buf+len,hUart->rbuf,max_len-len);	
			for( i = 0; i < len; i++)
			{
				//buf[i] = *(hUart->r_r + i);
				*buf++ = *(hUart->r_r + i);
			}	
 			for( i = 0; i < max_len-len; i++)
			{
				//buf[i+len] = *(hUart->rbuf + i);
				*buf++ = hUart->rbuf[i];
				//buf[i+2] = hUart->rbuf[i];
			}	 				
		}else{
			for( i = 0; i < max_len; i++)
			{
				buf[i] = *(hUart->r_r + i);
			}
		} 

		hUart->r_r += max_len;
		if(hUart->r_r>=hUart->r_e){
			hUart->r_r-= UART_BUF_LEN;
		}
	}

	return max_len;                    //返回max_len
}

/*
 * 判定是否有数据可以读取
 */
int uart_get_recv_count( )
{
	return hUart->rlen ;
}

/*
 * write uart
 */
void uart_write_uart(unsigned char *send_str, int send_str_len) 
{
	int i = 0;
	
	/*while(!TRMT1) 	// TRMT1 is set when TSR is empty
		continue ;
 
	for(i = 0 ; i < send_str_len; i++)
	{
		TXREG1 = send_str[i];
		while(!TRMT1) 	// TRMT1 is set when TSR is empty
			continue ;
	}*/
	for(i = 0 ; i < send_str_len; i++)
	{
		Uart1_TX(send_str[i]);
	}
	
}

unsigned char analysis_uart_info(unsigned char *str, int strlen )
{
	short i;
	int cmd_len;
	unsigned char cmd_id;
	unsigned char ss_adr;
	unsigned char ss_status;
	unsigned char curr_len;
	unsigned int  sum;
	
	cmd_len = uart_get_recv_count( );
	if(cmd_len < HOST_CMD_LEN)
	{
		return 0;
	}

	// 提取同步头
 	if(hUart->bSync == 0)
	{
		syn_head[0] = uart_get_char( );
		for( i = 0; i < cmd_len - 1; i++ )
		{
			if( syn_head[0] == UART_HOST_SYN1 )
			{
				syn_head[1] = uart_get_char( );
				if( syn_head[1] == UART_HOST_SYN2 )
				{
					hUart->bSync = 1;
					break;
				}else{
					syn_head[0] = syn_head[1];
				}
			}else{
				syn_head[0] = uart_get_char( );
			}
		}
	}  
	
	// 提取数据
	if(hUart->bSync){
		str[0] = UART_HOST_SYN1;
		str[1] = UART_HOST_SYN2;

		uart_read(str+2, strlen-2);		
		hUart->bSync = 0;//清同步标志
	}else{
		for(i = 0; i < strlen; i++) str[i] = 0x00;
		
		return 0;//数据帧长度不够
	} 
	
	// 和校验
 	sum = 0;
	for(i = 0; i < HOST_CMD_LEN-1; i++)
	{
		sum += str[i];
	}	
	if((sum&0xff) != str[HOST_CMD_LEN-1])
	{
		return 0;
	}
	/*else{
		for(i = 0; i < strlen; i++) str[i] = 0x00;
	}*/
	
	return str[2];
}
