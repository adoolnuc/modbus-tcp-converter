#ifndef _UART_H_
#define _UART_H_

#define UART_BUF_LEN			64

// ָ���
#define HOST_CMD_LEN			32
#define SLAVE_CMD_LEN			32

#define UART_SYN1				0xEB
#define UART_SYN2				0x90

#define UART_HOST_SYN1          0xAA
#define UART_HOST_SYN2          0x55


// ָ����
#define SET_DOWN_CMD			0x01
#define GET_DOWN_CMD			0x02
#define SET_UP_CMD				0x03  
#define GET_UP_CMD				0x04  
#define SET_TEST_CMD			0x12
#define CANCEL_TEST_CMD			0x15
#define SEL_LIST1_CMD			0x41
#define SEL_LIST2_CMD			0x42

#define RSV						0x00

typedef struct{
	/*���ܻ��湲UART_BUF_LEN���ֽ�*/
	unsigned char rbuf[UART_BUF_LEN];
	
	/*���ջ���дλ��*/
	unsigned char *r_w;
	
	/*���ջ����λ��*/
	unsigned char *r_r;
	
	/*���ջ������λ��*/
	unsigned char *r_e;
	
	/*�����ݳ���*/
	int rlen;
	
	/*����λ��*/
	unsigned int ridx;
	
	/*ͬ����־*/
	unsigned char bSync;
}UART_Obj;

// Э�� ////////////////////////////////////////////////////////
//�ظ����ݰ���ʽ
typedef struct recv_data_pack{
	unsigned char syn1;					//0 SYN1(0xEB)
	unsigned char syn2;					//1 SYN2(0x90)
	unsigned char recmd;				//2 �����ֶ�
	unsigned char rsv0;					//3 ����
	unsigned char gateway[4];			//4-7	�ӻ�ID
	unsigned char netmask[4];			//8-11	����
	unsigned char local_ip[4];		    //12-15 �ӻ�״̬
	unsigned char local_port[2];		//16-17 �ӻ���ǰ����ֵ��λ
	unsigned char far_ip[4];			//18-21 �ӻ���ǰ����ֵ��λ
	unsigned char far_port[2];		    //22-23  ��ǰ����Ԥ����ֵ��λ
	unsigned char local_mac[6];		    //24-29 ��ǰ����Ԥ����ֵ��λ
	unsigned char rsv1;   				//30 У���
	unsigned char sum;   				//31 У���
}slave_packet_obj, *slave_packet_handle;

//�������ʽ
typedef struct setting_packet{
	unsigned char syn1;					//0 SYN1(0xAA)
	unsigned char syn2;					//1 SYN2(0x55)
	unsigned char cmd;				    //2 �����ֶ�
	unsigned char rsv0;					//3 ����
	unsigned char gateway[4];			//4-7	�ӻ�ID
	unsigned char netmask[4];			//8-11	����
	unsigned char local_ip[4];		    //12-15 �ӻ�״̬
	unsigned char local_port[2];		//16-17 �ӻ���ǰ����ֵ��λ
	unsigned char far_ip[4];			//18-21 �ӻ���ǰ����ֵ��λ
	unsigned char far_port[2];		    //22-23  ��ǰ����Ԥ����ֵ��λ
	unsigned char local_mac[6];		    //24-29 ��ǰ����Ԥ����ֵ��λ
	unsigned char rsv1;   				//30 У���
	unsigned char sum;   				//31 У���
}host_packet_obj, *host_packet_handle;

extern unsigned char init_uart();
int uart_get_recv_count( );
unsigned char uart_get_char( );
int uart_read(unsigned char *buf, int max_len) ;
int uart_get_recv_count( );
unsigned char analysis_uart_info(unsigned char *str, int strlen );
extern void uart_write_uart(unsigned char *send_str, int send_str_len) ;
#endif //_UART_H_


