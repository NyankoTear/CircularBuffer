/**
 ******************************************************************************
 * @file    circular_buffer.h
 * @author  Donghyun Ko    
 * @brief   Header file of circular (or ring) buffer.
 * 
 ******************************************************************************
 * @attention
 * Copyright (c) 2020 Donghyun Ko
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 ******************************************************************************
 */

#ifndef __CIRCULAR_BUFFER__
#define __CIRCULAR_BUFFER__

#include <stdio.h>
#include <stdint.h>

#define CIRCULAR_BUFFER_LENGTH 10   /*!< Defines the length of the circular buffer. */
#define __DEBUG_CIRCULE_BUFFER__

typedef enum 
{
    BUFFER_OK = 0,      /*!< Buffer is idle, writing successfully, or reading successfully */
    BUFFER_FULL = 1,    /*!< Buffer is full */
    BUFFER_EMPTY = 2    /*!< Buffer is empty */
} CIRCULAR_BUFFER_STATUS;

typedef struct BlockBufStr
{
    uint8_t* pBlockStartAddr;   /*!< 1-byte block buffer start address */
    uint8_t* pBlockEndAddr;     /*!< 1-byte block buffer end address */
}BlockBufStr;

typedef struct CirBufStr
{
    char cirBuf[CIRCULAR_BUFFER_LENGTH];    /*!< Character circular buffer array */
    const uint16_t cirBufLen;               /*!< Specifies the length of the circular buffer. */
    BlockBufStr pWriteBuf;                  /*!< 1-byte write buffer block structure */
    BlockBufStr pReadBuf;                   /*!< 1-byte read buffer block structure */
    uint8_t* pCirBufMinAddr;                /*!< Specifies the minimum address of the circular buffer. */
    uint8_t* pCirBufMaxAddr;                /*!< Specifies the (maximum address + 1) of the circular buffer. */
    CIRCULAR_BUFFER_STATUS cirBufStatus;    /*!< Specifies the current status of the circular buffer. */
} CirBufStr;

void InitializeCircularBuffer(CirBufStr* pCirBuf);
uint8_t WriteCircularBuffer(CirBufStr* pCirBuf, const char data);
uint8_t ReadCircularBuffer(CirBufStr* pCirBuf, char* data);

#ifdef __DEBUG_CIRCULE_BUFFER__

void DebugPointerAddressCircularBufferStructure(const CirBufStr* pCirBuf);
void DebugDataCircularBufferStructure(const CirBufStr* pCirBuf);

#endif /* __DEBUG_CIRCULE_BUFFER__ */

#endif /* __CIRCULAR_BUFFER__ */