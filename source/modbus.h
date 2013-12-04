/*
 * modbus.h
 *
 *  Created on: 2013-12-2
 *      Author: Administrator
 */

#ifndef MODBUS_H_
#define MODBUS_H_

#define MODBUS_TID_LEN 2
#define MODBUS_PID_LEN 2
#define MODBUS_FRAME_LEN 2

typedef struct 
{
	char cTid[MODBUS_TID_LEN];
	char cPid[MODBUS_PID_LEN];
	char cFrameLen[MODBUS_FRAME_LEN];
	char cUid;
	char cCode;
} S_MODBUS_FRAME;

typedef struct 
{
	char cCount;
} S_MODBUS_READ_0X1_RES;

typedef struct 
{
	char cCount;
} S_MODBUS_READ_0X2_RES;

typedef struct 
{
	char cCount;
} S_MODBUS_READ_0X3_RES;

typedef struct 
{
	char cCount;
} S_MODBUS_READ_0X4_RES;

typedef struct 
{
	char cHighAddr;
	char cLowAddr;
	unsigned char cWrValHigh;
	unsigned char cWrValLow;
} S_MODBUS_READ_0X5_RES;

typedef struct 
{
	char cHighAddr;
	char cLowAddr;
	unsigned char cWrValHigh;
	unsigned char cWrValLow;
} S_MODBUS_READ_0X6_RES;

typedef struct 
{
	char cHighAddr;
	char cLowAddr;
	char cWrNumHigh;
	char cWrNumLow;
} S_MODBUS_READ_0XF_RES;

typedef struct 
{
	char cHighAddr;
	char cLowAddr;
	char cWrNumHigh;
	char cWrNumLow;
} S_MODBUS_READ_0X10_RES;

typedef struct 
{
	char cHighAddr;
	char cLowAddr;
	char cRdNumHigh;
	char cRdNumLow;
} S_MODBUS_READ_0X1_REQ;

typedef struct 
{
	char cHighAddr;
	char cLowAddr;
	char cRdNumHigh;
	char cRdNumLow;
} S_MODBUS_READ_0X2_REQ;

typedef struct 
{
	char cHighAddr;
	char cLowAddr;
	char cRdNumHigh;
	char cRdNumLow;
} S_MODBUS_READ_0X3_REQ;

typedef struct 
{
	char cHighAddr;
	char cLowAddr;
	char cRdNumHigh;
	char cRdNumLow;
} S_MODBUS_READ_0X4_REQ;

typedef struct 
{
	char cHighAddr;
	char cLowAddr;
	unsigned char cWrValHigh;
	unsigned char cWrValLow;
} S_MODBUS_READ_0X5_REQ;

typedef struct 
{
	char cHighAddr;
	char cLowAddr;
	unsigned char cWrValHigh;
	unsigned char cWrValLow;
} S_MODBUS_READ_0X6_REQ;

typedef struct 
{
	char cHighAddr;
	char cLowAddr;
	char cWrNumHigh;
	char cWrNumLow;
	char cCount;
} S_MODBUS_READ_0XF_REQ;

typedef struct 
{
	char cHighAddr;
	char cLowAddr;
	char cWrNumHigh;
	char cWrNumLow;
	char cCount;
} S_MODBUS_READ_0X10_REQ;

typedef struct
{
	char cCode;
	void (*pCodeCb)(char *pBuf);
} S_MODBUS_RES_PROC;

typedef struct
{
	char cCode;
	void (*pCodeCb)(unsigned int iInBufPtr, unsigned int iOutBufPtr, unsigned int pLen);
} S_MODBUS_REQ_PROC;

extern void ModBusParseRequest(char *pInBuf, char *pOutBuf, unsigned int *pLen);

#endif /* MODBUS_H_ */
