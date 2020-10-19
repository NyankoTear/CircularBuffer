#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define CIRCULAR_BUFFER_LENGTH 10
#define POINTER_BYTE_SIZE 8

typedef enum 
{
    BUFFER_OK = 0, 
    BUFFER_FULL = 1,
    BUFFER_EMPTY = 2
} CIRCULAR_BUFFER_STATUS;

typedef struct BlockBufStr
{
    uint8_t* pBlockStartAddr;
    uint8_t* pBlockEndAddr;
}BlockBufStr;

typedef struct CirBufStr
{
    char cirBuf[CIRCULAR_BUFFER_LENGTH];
    const uint16_t cirBufLen;
    BlockBufStr pWriteBuf;
    BlockBufStr pReadBuf;
    uint8_t* pCirBufMinAddr;
    uint8_t* pCirBufMaxAddr;
    CIRCULAR_BUFFER_STATUS cirBufStatus;
} CirBufStr;

void GoToNextWriteBuffer(CirBufStr* pCirBuf);
void GoToNextReadBuffer(CirBufStr* pCirBuf);
uint8_t WriteCircularBuffer(CirBufStr* pCirBuf, const char data);
uint8_t ReadCircularBuffer(CirBufStr* pCirBuf, char* data);
void DebugPointerAddressCircularBufferStructure(const CirBufStr* pCirBuf);
void DebugDataCircularBufferStructure(const CirBufStr* pCirBuf);

int main (void)
{
    CirBufStr myCirBufStr = {.cirBufLen = CIRCULAR_BUFFER_LENGTH, .cirBufStatus = BUFFER_EMPTY};
    char writeData = 'A';
    char readData[1];

    // Initialize myCirBufStr
    myCirBufStr.pWriteBuf.pBlockStartAddr = myCirBufStr.cirBuf;
    myCirBufStr.pWriteBuf.pBlockEndAddr = myCirBufStr.cirBuf + 1;
    myCirBufStr.pReadBuf.pBlockStartAddr = myCirBufStr.cirBuf;
    myCirBufStr.pReadBuf.pBlockEndAddr = myCirBufStr.cirBuf + 1;
    myCirBufStr.pCirBufMinAddr = myCirBufStr.cirBuf;
    myCirBufStr.pCirBufMaxAddr = myCirBufStr.pCirBufMinAddr + myCirBufStr.cirBufLen;

    return 0;
}

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

void DebugDataCircularBufferStructure(const CirBufStr* pCirBuf)
{
    printf("\n");
    for (uint16_t i = 0; i < pCirBuf->cirBufLen; i++)
    {
        printf("pCirBuf->cirBuf[%i]: %c\n", i, pCirBuf->cirBuf[i]);
    }
}