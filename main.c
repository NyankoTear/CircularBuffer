#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define CIRCULAR_BUFFER_LENGTH 10

typedef enum 
{
    BUFFER_OK = 0, 
    BUFFER_BUSY = 1
} CIRCULAR_BUFFER_STATUS;

typedef struct CirBufStr
{
    char cirBuf[CIRCULAR_BUFFER_LENGTH];
    const uint16_t cirBufLen;
    uint8_t* pWriteBuf;
    uint8_t* pReadBuf;
    uint8_t* pCirBufMinAddr;
    uint8_t* pCirBufMaxAddr;
} CirBufStr;

void GoToNextWriteBuffer(CirBufStr* pCirBuf);
void GoToNextReadBuffer(CirBufStr* pCirBuf);
CIRCULAR_BUFFER_STATUS WriteCircularBuffer(CirBufStr* pCirBuf, const char data);
CIRCULAR_BUFFER_STATUS ReadCircularBuffer(CirBufStr* pCirBuf, char* data);
void DebugPointerAddressCircularBufferStructure(const CirBufStr* pCirBuf);
void DebugDataCircularBufferStructure(const CirBufStr* pCirBuf);

int main (void)
{
    CirBufStr myCirBufStr = {.cirBufLen = CIRCULAR_BUFFER_LENGTH};
    char writeData = 'A';
    char readData[1];

    // Initialize myCirBufStr
    myCirBufStr.pWriteBuf = myCirBufStr.cirBuf;
    myCirBufStr.pReadBuf = myCirBufStr.cirBuf;
    myCirBufStr.pCirBufMinAddr = myCirBufStr.cirBuf;
    myCirBufStr.pCirBufMaxAddr = myCirBufStr.pCirBufMinAddr + myCirBufStr.cirBufLen;

    // Debugging for myCirBufStr.cirBuf
    for (uint16_t i = 0; i < myCirBufStr.cirBufLen; i++)
    {
        myCirBufStr.cirBuf[i] = i;
    }

    DebugPointerAddressCircularBufferStructure(&myCirBufStr);

    for (uint16_t i = 0; i < myCirBufStr.cirBufLen; i++)
    {
        WriteCircularBuffer(&myCirBufStr, writeData);
        writeData++;
    }

    DebugDataCircularBufferStructure(&myCirBufStr);

    for (uint16_t i = 0; i < myCirBufStr.cirBufLen; i++)
    {
        if (ReadCircularBuffer(&myCirBufStr, readData) == BUFFER_OK)
        {
            printf("Read data: %c\n", readData[0]);
        }
    }

    DebugDataCircularBufferStructure(&myCirBufStr);

    writeData = 'A';

    for (uint16_t i = 0; i < myCirBufStr.cirBufLen; i++)
    {
        WriteCircularBuffer(&myCirBufStr, writeData);
        // writeData++;
    }

    DebugDataCircularBufferStructure(&myCirBufStr);

    for (uint16_t i = 0; i < myCirBufStr.cirBufLen; i++)
    {
        if (ReadCircularBuffer(&myCirBufStr, readData) == BUFFER_OK)
        {
            printf("Read data: %c\n", readData[0]);
        }
    }

    DebugDataCircularBufferStructure(&myCirBufStr);

    return 0;
}

void GoToNextWriteBuffer(CirBufStr* pCirBuf)
{
    ++(pCirBuf->pWriteBuf);

    // Check if the write buffer reach the maximum address of the circular buffer.
    // If it reaches, then the write buffer moves the minimum address of the circular buffer which is the starting point of the circular buffer array.
    if (!(pCirBuf->pWriteBuf < pCirBuf->pCirBufMaxAddr))
    {
        pCirBuf->pWriteBuf = pCirBuf->pCirBufMinAddr;
    }
}

void GoToNextReadBuffer(CirBufStr* pCirBuf)
{
    ++(pCirBuf->pReadBuf);

    // Check if the read buffer reach the maximum address of the circular buffer.
    // If it reaches, then the read buffer move the minimum address of the circular buffer which is the starting point of the ciruclar buffer array.
    if (!(pCirBuf->pReadBuf < pCirBuf->pCirBufMaxAddr))
    {
        pCirBuf->pReadBuf = pCirBuf->pCirBufMinAddr;
    }
}

CIRCULAR_BUFFER_STATUS WriteCircularBuffer(CirBufStr* pCirBuf, const char data)
{
    uint8_t* pNextBufAddr = (pCirBuf->pWriteBuf) + 1;

    // Check if the after buffer reach the maximum address of the circular buffer.
    // If it reaches, then the after buffer move the minimum address of the circular buffer which is the starting point of the circular buffer array.
    if (!(pNextBufAddr < pCirBuf->pCirBufMaxAddr))
    {
        pNextBufAddr = pCirBuf->pCirBufMinAddr;
    }

    // DEBUG
    printf("pNextBufAddr: %p\n", pNextBufAddr);

    // Check if the circular buffer is full.
    if (pNextBufAddr == pCirBuf->pReadBuf){
        printf("WARN: Buffer is full.\n");
        return BUFFER_BUSY;
    }
    else
    {
        *(pCirBuf->pWriteBuf) = data;
        GoToNextWriteBuffer(pCirBuf);
        return BUFFER_OK;
    }
}

CIRCULAR_BUFFER_STATUS ReadCircularBuffer(CirBufStr* pCirBuf, char* data)
{
    if (pCirBuf->pReadBuf != pCirBuf->pWriteBuf)
    {
        const char cirBufData = *(pCirBuf->pReadBuf);
        *data = cirBufData;
        GoToNextReadBuffer(pCirBuf);
        return BUFFER_OK;
    }
    else
    {
        return BUFFER_BUSY;
    }
}

void DebugPointerAddressCircularBufferStructure(const CirBufStr* pCirBuf)
{
    printf("\npCirBuf->cirBuf: %p\n", pCirBuf->cirBuf);
    printf("pCirBuf->pWriteBuf: %p\n", pCirBuf->pWriteBuf);
    printf("pCirBuf->pReadBuf: %p\n", pCirBuf->pReadBuf);
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