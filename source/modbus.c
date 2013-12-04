/*
 * modbus.c
 *
 *  Created on: 2013-12-2
 *      Author: Administrator
 */

#include <string.h>
#include <stdio.h>

#include "modbus.h"

void ModBus0x1ReqProc(unsigned int iInBufPtr, unsigned int iOutBufPtr, unsigned int pLen)
{
	int iFrameLen;
	char *pInBuf = (char *)iInBufPtr, *pOutBuf = (char *)iOutBufPtr;
	int iRdNumBytes, iRdNumBits;
	S_MODBUS_FRAME *pMBOutBuf = (S_MODBUS_FRAME *)pOutBuf;
	S_MODBUS_READ_0X1_RES *pMBResBuf = (S_MODBUS_READ_0X1_RES *)(pOutBuf +
	  sizeof(S_MODBUS_FRAME));
	S_MODBUS_READ_0X1_REQ *pModBus = (S_MODBUS_READ_0X1_REQ *)(pInBuf + sizeof(S_MODBUS_FRAME));
	char *pData = pOutBuf + sizeof(S_MODBUS_FRAME) + sizeof(S_MODBUS_READ_0X1_RES);

	iRdNumBits = (pModBus->cRdNumHigh << 8) | pModBus->cRdNumLow;
	iRdNumBytes = iRdNumBits / 8 + ((iRdNumBits % 8) ? 1 : 0);

	iFrameLen = sizeof(pMBOutBuf->cUid) + sizeof(pMBOutBuf->cCode) + sizeof(S_MODBUS_READ_0X1_RES)
	  + iRdNumBytes;
	memcpy(pOutBuf, pInBuf, sizeof(S_MODBUS_FRAME));
	pMBOutBuf->cFrameLen[1] = iFrameLen & 0xff;
	pMBOutBuf->cFrameLen[0] = (iFrameLen >> 8) & 0xff;
	pMBResBuf->cCount = iRdNumBytes;

	memset(pData, 0x1, iRdNumBytes);

	*((unsigned int *)pLen) = sizeof(S_MODBUS_FRAME) + sizeof(S_MODBUS_READ_0X1_RES)
	  + iRdNumBytes;
}

void ModBus0x2ReqProc(unsigned int iInBufPtr, unsigned int iOutBufPtr, unsigned int pLen)
{
	int iFrameLen;
	char *pInBuf = (char *)iInBufPtr, *pOutBuf = (char *)iOutBufPtr;
	int iRdNumBytes, iRdNumBits;
	S_MODBUS_FRAME *pMBOutBuf = (S_MODBUS_FRAME *)pOutBuf;
	S_MODBUS_READ_0X2_RES *pMBResBuf = (S_MODBUS_READ_0X2_RES *)(pOutBuf +
      sizeof(S_MODBUS_FRAME));
	S_MODBUS_READ_0X2_REQ *pModBus = (S_MODBUS_READ_0X2_REQ *)(pInBuf + sizeof(S_MODBUS_FRAME));
	char *pData = pOutBuf + sizeof(S_MODBUS_FRAME) + sizeof(S_MODBUS_READ_0X2_RES);

	iRdNumBits = (pModBus->cRdNumHigh << 8) | pModBus->cRdNumLow;
	iRdNumBytes = iRdNumBits / 8 + ((iRdNumBits % 8) ? 1 : 0);

	iFrameLen = sizeof(pMBOutBuf->cUid) + sizeof(pMBOutBuf->cCode) + sizeof(S_MODBUS_READ_0X2_RES)
	  + iRdNumBytes;

	memcpy(pOutBuf, pInBuf, sizeof(S_MODBUS_FRAME));
	pMBOutBuf->cFrameLen[1] = iFrameLen & 0xff;
	pMBOutBuf->cFrameLen[0] = (iFrameLen >> 8) & 0xff;
	pMBResBuf->cCount = iRdNumBytes;
	
	memset(pData, 0x1, iRdNumBytes);

	*((unsigned int *)pLen) = sizeof(S_MODBUS_FRAME) + sizeof(S_MODBUS_READ_0X2_RES)
	  + iRdNumBytes;
}

void ModBus0x3ReqProc(unsigned int iInBufPtr, unsigned int iOutBufPtr, unsigned int pLen)
{
	int iFrameLen;
	char *pInBuf = (char *)iInBufPtr, *pOutBuf = (char *)iOutBufPtr;
	int iRdNumBytes, iRdNumWords;
	S_MODBUS_FRAME *pMBOutBuf = (S_MODBUS_FRAME *)pOutBuf;
	S_MODBUS_READ_0X3_RES *pMBResBuf = (S_MODBUS_READ_0X3_RES *)(pOutBuf +
	  sizeof(S_MODBUS_FRAME));
	S_MODBUS_READ_0X3_REQ *pModBus = (S_MODBUS_READ_0X3_REQ *)(pInBuf +
	  sizeof(S_MODBUS_FRAME));
	char *pData = pOutBuf + sizeof(S_MODBUS_FRAME) + sizeof(S_MODBUS_READ_0X3_RES);

	iRdNumWords = (pModBus->cRdNumHigh << 8) | pModBus->cRdNumLow;
	iRdNumBytes = iRdNumWords * 2;

	iFrameLen = sizeof(pMBOutBuf->cUid) + sizeof(pMBOutBuf->cCode) + sizeof(S_MODBUS_READ_0X3_RES)
	  + iRdNumBytes;
	memcpy(pOutBuf, pInBuf, sizeof(S_MODBUS_FRAME));
	pMBOutBuf->cFrameLen[1] = iFrameLen & 0xff;
	pMBOutBuf->cFrameLen[0] = (iFrameLen >> 8) & 0xff;
	pMBResBuf->cCount = iRdNumBytes;

	memset(pData, 0x3, iRdNumBytes);

	*((unsigned int *)pLen) = sizeof(S_MODBUS_FRAME) + sizeof(S_MODBUS_READ_0X3_RES)
	  + iRdNumBytes;
}

void ModBus0x4ReqProc(unsigned int iInBufPtr, unsigned int iOutBufPtr, unsigned int pLen)
{
	int iFrameLen;
	char *pInBuf = (char *)iInBufPtr, *pOutBuf = (char *)iOutBufPtr;
	int iRdNumBytes, iRdNumWords;
	S_MODBUS_FRAME *pMBOutBuf = (S_MODBUS_FRAME *)pOutBuf;
	S_MODBUS_READ_0X4_RES *pMBResBuf = (S_MODBUS_READ_0X4_RES *)(pOutBuf +
		sizeof(S_MODBUS_FRAME));
	S_MODBUS_READ_0X4_REQ *pModBus = (S_MODBUS_READ_0X4_REQ *)(pInBuf + sizeof(S_MODBUS_FRAME));
	char *pData = pOutBuf + sizeof(S_MODBUS_FRAME) + sizeof(S_MODBUS_READ_0X4_RES);

	iRdNumWords = (pModBus->cRdNumHigh << 8) | pModBus->cRdNumLow;
	iRdNumBytes = iRdNumWords * 2;

	iFrameLen = sizeof(pMBOutBuf->cUid) + sizeof(pMBOutBuf->cCode) + sizeof(S_MODBUS_READ_0X4_RES)
	  + iRdNumBytes;

	memcpy(pOutBuf, pInBuf, sizeof(S_MODBUS_FRAME));
	pMBOutBuf->cFrameLen[1] = iFrameLen & 0xff;
	pMBOutBuf->cFrameLen[0] = (iFrameLen >> 8) & 0xff;
	pMBResBuf->cCount = iRdNumBytes;

	memset(pData, 0xee, iRdNumBytes);

	*((unsigned int *)pLen) = sizeof(S_MODBUS_FRAME) + sizeof(S_MODBUS_READ_0X4_RES)
	  + iRdNumBytes;
}

void ModBus0x5ReqProc(unsigned int iInBufPtr, unsigned int iOutBufPtr, unsigned int pLen)
{
	char *pInBuf = (char *)iInBufPtr, *pOutBuf = (char *)iOutBufPtr;
	int iFrameLen;
	S_MODBUS_FRAME *pMBOutBuf = (S_MODBUS_FRAME *)pOutBuf;
	S_MODBUS_READ_0X5_RES *pMBResBuf = (S_MODBUS_READ_0X5_RES *)(pOutBuf +
		sizeof(S_MODBUS_FRAME));
	S_MODBUS_READ_0X5_REQ *pModBus = (S_MODBUS_READ_0X5_REQ *)(pInBuf + sizeof(S_MODBUS_FRAME));

	iFrameLen = sizeof(pMBOutBuf->cUid) + sizeof(pMBOutBuf->cCode) +
      sizeof(S_MODBUS_READ_0X5_RES);

	memcpy(pOutBuf, pInBuf, sizeof(S_MODBUS_FRAME));
	pMBOutBuf->cFrameLen[1] = iFrameLen & 0xff;
	pMBOutBuf->cFrameLen[0] = (iFrameLen >> 8) & 0xff;
	pMBResBuf->cHighAddr = pModBus->cHighAddr;
	pMBResBuf->cLowAddr = pModBus->cLowAddr;
	pMBResBuf->cWrValHigh = pModBus->cWrValHigh;
	pMBResBuf->cWrValLow = pModBus->cWrValLow;

	*((unsigned int *)pLen) = sizeof(S_MODBUS_FRAME) + sizeof(S_MODBUS_READ_0X5_RES);
}

void ModBus0x6ReqProc(unsigned int iInBufPtr, unsigned int iOutBufPtr, unsigned int pLen)
{
	char *pInBuf = (char *)iInBufPtr, *pOutBuf = (char *)iOutBufPtr;
	int iFrameLen;
	S_MODBUS_FRAME *pMBOutBuf = (S_MODBUS_FRAME *)pOutBuf;
	S_MODBUS_READ_0X6_RES *pMBResBuf = (S_MODBUS_READ_0X6_RES *)(pOutBuf +
		sizeof(S_MODBUS_FRAME));
	S_MODBUS_READ_0X6_REQ *pModBus = (S_MODBUS_READ_0X6_REQ *)(pInBuf + sizeof(S_MODBUS_FRAME));

	iFrameLen = sizeof(pMBOutBuf->cUid) + sizeof(pMBOutBuf->cCode) +
	  sizeof(S_MODBUS_READ_0X6_RES);

	memcpy(pOutBuf, pInBuf, sizeof(S_MODBUS_FRAME));
	pMBOutBuf->cFrameLen[1] = iFrameLen & 0xff;
	pMBOutBuf->cFrameLen[0] = (iFrameLen >> 8) & 0xff;
	pMBResBuf->cHighAddr = pModBus->cHighAddr;
	pMBResBuf->cLowAddr = pModBus->cLowAddr;
	pMBResBuf->cWrValHigh = pModBus->cWrValHigh;
	pMBResBuf->cWrValLow = pModBus->cWrValLow;

	*((unsigned int *)pLen) = sizeof(S_MODBUS_FRAME) + sizeof(S_MODBUS_READ_0X6_RES);
}

void ModBus0xFReqProc(unsigned int iInBufPtr, unsigned int iOutBufPtr, unsigned int pLen)
{
	char *pInBuf = (char *)iInBufPtr, *pOutBuf = (char *)iOutBufPtr;
	int i, iFrameLen;
	S_MODBUS_FRAME *pMBOutBuf = (S_MODBUS_FRAME *)pOutBuf;
	S_MODBUS_READ_0XF_RES *pMBResBuf = (S_MODBUS_READ_0XF_RES *)(pOutBuf +
		sizeof(S_MODBUS_FRAME));
	S_MODBUS_READ_0XF_REQ *pModBus = (S_MODBUS_READ_0XF_REQ *)(pInBuf + sizeof(S_MODBUS_FRAME));
	unsigned char *pData = (unsigned char *)(pInBuf + sizeof(S_MODBUS_FRAME) +
	  sizeof(S_MODBUS_READ_0XF_REQ));

	iFrameLen = sizeof(pMBOutBuf->cUid) + sizeof(pMBOutBuf->cCode) + sizeof(S_MODBUS_READ_0XF_RES);

	memcpy(pOutBuf, pInBuf, sizeof(S_MODBUS_FRAME) + sizeof(S_MODBUS_READ_0XF_RES));
	pMBOutBuf->cFrameLen[1] = iFrameLen & 0xff;
	pMBOutBuf->cFrameLen[0] = (iFrameLen >> 8) & 0xff;
	pMBResBuf->cHighAddr = pModBus->cHighAddr;
	pMBResBuf->cLowAddr = pModBus->cLowAddr;
	pMBResBuf->cWrNumHigh = pModBus->cWrNumHigh;
	pMBResBuf->cWrNumLow = pModBus->cWrNumLow;

	*((unsigned int *)pLen) = sizeof(S_MODBUS_FRAME) + sizeof(S_MODBUS_READ_0XF_RES);
}

void ModBus0x10ReqProc(unsigned int iInBufPtr, unsigned int iOutBufPtr, unsigned int pLen)
{
	char *pInBuf = (char *)iInBufPtr, *pOutBuf = (char *)iOutBufPtr;
	int i, iFrameLen;
	S_MODBUS_FRAME *pMBOutBuf = (S_MODBUS_FRAME *)pOutBuf;
	S_MODBUS_READ_0X10_RES *pMBResBuf = (S_MODBUS_READ_0X10_RES *)(pOutBuf +
		sizeof(S_MODBUS_FRAME));
	S_MODBUS_READ_0X10_REQ *pModBus = (S_MODBUS_READ_0X10_REQ *)(pInBuf + sizeof(S_MODBUS_FRAME));
	unsigned char *pData = (unsigned char *)(pInBuf + sizeof(S_MODBUS_FRAME) +
		sizeof(S_MODBUS_READ_0X10_REQ));

	iFrameLen = sizeof(pMBOutBuf->cUid) + sizeof(pMBOutBuf->cCode) + sizeof(S_MODBUS_READ_0X10_RES);

	memcpy(pOutBuf, pInBuf, sizeof(S_MODBUS_FRAME) + sizeof(S_MODBUS_READ_0X10_RES));
	pMBOutBuf->cFrameLen[1] = iFrameLen & 0xff;
	pMBOutBuf->cFrameLen[0] = (iFrameLen >> 8) & 0xff;
	pMBResBuf->cHighAddr = pModBus->cHighAddr;
	pMBResBuf->cLowAddr = pModBus->cLowAddr;
	pMBResBuf->cWrNumHigh = pModBus->cWrNumHigh;
	pMBResBuf->cWrNumLow = pModBus->cWrNumLow;

	*((unsigned int *)pLen) = sizeof(S_MODBUS_FRAME) + sizeof(S_MODBUS_READ_0X10_RES);
}

S_MODBUS_REQ_PROC m_sMBReqProc[] =
{
	{0x01, ModBus0x1ReqProc},
	{0x02, ModBus0x2ReqProc},
	{0x03, ModBus0x3ReqProc},
	{0x04, ModBus0x4ReqProc},
	{0x05, ModBus0x5ReqProc},
	{0x06, ModBus0x6ReqProc},
	{0x0F, ModBus0xFReqProc},
	{0x10, ModBus0x10ReqProc},
};

void ModBusParseRequest(char *pInBuf, char *pOutBuf, unsigned int *pLen)
{
	int i;
	S_MODBUS_FRAME *pModBus = (S_MODBUS_FRAME *)pInBuf;

	for (i = 0; i < sizeof(m_sMBReqProc) / sizeof(*m_sMBReqProc); i++)
	{
		if (pModBus->cCode == m_sMBReqProc[i].cCode)
		{
			m_sMBReqProc[i].pCodeCb((unsigned int)pInBuf, (unsigned int)pOutBuf, (unsigned int)pLen);
			return;
		}
	}
}
