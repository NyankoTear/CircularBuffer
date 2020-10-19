/**
 ******************************************************************************
 * @file    circular_buffer.c
 * @author  Donghyun Ko    
 * @brief   This file provides functions to manage a circular (or ring) buffer.
 * 
 @verbatim
 ====================================================================================================
                                    #### How to use this file ####
 ====================================================================================================
 (#) To make a circle buffer first define the buffer length in the header file (circular_buffer.h):
     #define CIRCULAR_BUFFER_LENGTH <buffer length>

 (#) Declare CirBufStr with specific length and BUFFER_EMPTY status:
     CirBufStr <variable name> = {.cirBufLen = CIRCULAR_BUFFER_LENGTH, .cirBufStatus = BUFFER_EMPTY};

 (#) Write data into the buffer using the following function:
     WriteCircularBuffer()
     
 (#) Read the buffer using the following function:
     ReadCircularBuffer()
 ====================================================================================================
 (#) Optionally, debug the pointer address of the CirBufStr:

    (+) Define debug macro:
        #define __DEBUG_CIRCULE_BUFFER__

    (+) Debug pointer address using the following function:
        DebugPointerAddressCircularBufferStructure()

 (#) Optionally, debug the all data in the circular buffer:

    (+) Define debug macro:
        #define __DEBUG_CIRCULE_BUFFER__

    (+) Debug the all data in the circular buffer using the following function:
        DebugDataCircularBufferStructure()
 ====================================================================================================
 @endverbatim
 *******************************************************************
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
 *******************************************************************
 */

#include "circular_buffer.h"

/**
 * @brief Initialize the circular buffer structure.
 * @param pCirBuf pointer to a CirBufStr structure that contains the setup parameter for the circular buffer structure. 
 * @return none
 */
void InitializeCircularBuffer(CirBufStr* pCirBuf)
{
    pCirBuf->pWriteBuf.pBlockStartAddr = pCirBuf->cirBuf;
    pCirBuf->pWriteBuf.pBlockEndAddr = pCirBuf->cirBuf + 1;
    pCirBuf->pReadBuf.pBlockStartAddr = pCirBuf->cirBuf;
    pCirBuf->pReadBuf.pBlockEndAddr = pCirBuf->cirBuf + 1;
    pCirBuf->pCirBufMinAddr = pCirBuf->cirBuf;
    pCirBuf->pCirBufMaxAddr = pCirBuf->pCirBufMinAddr + pCirBuf->cirBufLen;
}

/**
 * @brief Go to he next write buffer of the circular buffer.
 * @param pCirBuf pointer to a CirBufStr structure that contains the current address of the write buffer.
 * @return none
 */
void GoToNextWriteBuffer(CirBufStr* pCirBuf)
{
    ++(pCirBuf->pWriteBuf.pBlockStartAddr);
    ++(pCirBuf->pWriteBuf.pBlockEndAddr);

    // Check if the write buffer reach the maximum address of the circular buffer.
    // If it reaches, then the write buffer moves the minimum address of the circular buffer which is the starting point of the circular buffer array.
    if (!(pCirBuf->pWriteBuf.pBlockStartAddr < pCirBuf->pCirBufMaxAddr))
    {
        pCirBuf->pWriteBuf.pBlockStartAddr = pCirBuf->pCirBufMinAddr;
    }

    if (!(pCirBuf->pWriteBuf.pBlockEndAddr < pCirBuf->pCirBufMaxAddr))
    {
        pCirBuf->pWriteBuf.pBlockEndAddr = pCirBuf->pCirBufMinAddr;
    }
}

/**
 * @brief Go to he next read buffer of the circular buffer.
 * @param pCirBuf pointer to a CirBufStr structure that contains the current address of the read buffer.
 * @return none
 */
void GoToNextReadBuffer(CirBufStr* pCirBuf)
{
    ++(pCirBuf->pReadBuf.pBlockStartAddr);
    ++(pCirBuf->pReadBuf.pBlockEndAddr);

    // Check if the read buffer reach the maximum address of the circular buffer.
    // If it reaches, then the read buffer move the minimum address of the circular buffer which is the starting point of the ciruclar buffer array.
    if (!(pCirBuf->pReadBuf.pBlockStartAddr < pCirBuf->pCirBufMaxAddr))
    {
        pCirBuf->pReadBuf.pBlockStartAddr = pCirBuf->pCirBufMinAddr;
    }
    
    if (!(pCirBuf->pReadBuf.pBlockEndAddr < pCirBuf->pCirBufMaxAddr))
    {
        pCirBuf->pReadBuf.pBlockEndAddr = pCirBuf->pCirBufMinAddr;
    }
}

/**
 * @brief Write 1-byte into the circular buffer.
 * @param pCirBuf pointer to a CirBufStr structure that contains an address where to write.
 * @param data 1-byte char data
 * @return Write status
 *          0: Successfully write the data.
 *         -1: Fail to write the data because the buffer is full.
 */
uint8_t WriteCircularBuffer(CirBufStr* pCirBuf, const char data)
{
    // Check if the circular buffer is full.
    if (pCirBuf->cirBufStatus != BUFFER_FULL)
    {
        *(pCirBuf->pWriteBuf.pBlockStartAddr) = data;
        GoToNextWriteBuffer(pCirBuf);

        if (pCirBuf->pWriteBuf.pBlockStartAddr != pCirBuf->pReadBuf.pBlockStartAddr)
        {
            pCirBuf->cirBufStatus = BUFFER_OK;
        }
        else
        {
            pCirBuf->cirBufStatus = BUFFER_FULL;
        }
        
        return 0;
    }
    else
    {
        printf("WARN: Buffer is full.\n");
        return -1;
    }
}

/**
 * @brief Read 1-byte from the circular buffer.
 * @param pCirBuf pointer to a CirBufStr structure that contains an address where to read.
 * @param data pointer to a char that contains a read value.
 * @return Read status
 *          0: Successfully read the data.
 *         -1: Fail to read the data because the buffer is empty.
 */
uint8_t ReadCircularBuffer(CirBufStr* pCirBuf, char* data)
{
    // Check if the circular buffer is empty.
    if (pCirBuf->cirBufStatus != BUFFER_EMPTY)
    {
        data[0] = (char)*(pCirBuf->pReadBuf.pBlockStartAddr);
        GoToNextReadBuffer(pCirBuf);
        
        if (pCirBuf->pReadBuf.pBlockStartAddr != pCirBuf->pWriteBuf.pBlockStartAddr)
        {
            pCirBuf->cirBufStatus = BUFFER_OK;
        }
        else
        {
            pCirBuf->cirBufStatus = BUFFER_EMPTY;
        }
        
        return 0;
    }
    else
    {
        printf("WARN: Buffer is empty.\n");
        return -1;
    }
}

#ifdef __DEBUG_CIRCULE_BUFFER__

/**
 * @brief Print all necessary pointer address of the CirBufStr structure.
 * @note This function is able to use if __DEBUG_CIRCULE_BUFFER__ is defined.
 * @param pCifBuf pointer to a CirBufStr structure that contains all pointer address of the circular buffer structure.
 * @return none
 */
void DebugPointerAddressCircularBufferStructure(const CirBufStr* pCirBuf)
{
    printf("\npCirBuf->cirBuf: %p\n", pCirBuf->cirBuf);
    printf("pCirBuf->pWriteBuf.pBlockStartAddr: %p\n", pCirBuf->pWriteBuf.pBlockStartAddr);
    printf("pCirBuf->pWriteBuf.pBlockEndAddr: %p\n", pCirBuf->pWriteBuf.pBlockEndAddr);
    printf("pCirBuf->pReadBuf.pBlockStartAddr: %p\n", pCirBuf->pReadBuf.pBlockStartAddr);    
    printf("pCirBuf->pReadBuf.pBlockEndAddr: %p\n", pCirBuf->pReadBuf.pBlockEndAddr);
    printf("pCirBuf->pCifBufMinAddr: %p\n", pCirBuf->pCirBufMinAddr);
    printf("pCirBuf->pCifBufMaxAddr: %p\n", pCirBuf->pCirBufMaxAddr);
}

/**
 * @brief Print all circular buffer data.
 * @note This function is able to use if __DEBUG_CIRCULE_BUFFER__ is defined. 
 * @param pCirBuf pointer to a CirBufStr structure that contains the circular buffer data.
 * @return none
 */
void DebugDataCircularBufferStructure(const CirBufStr* pCirBuf)
{
    printf("\n");
    for (uint16_t i = 0; i < pCirBuf->cirBufLen; i++)
    {
        printf("pCirBuf->cirBuf[%i]: %c\n", i, pCirBuf->cirBuf[i]);
    }
}

#endif /* __DEBUG_CIRCULE_BUFFER__ */
