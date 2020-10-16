#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define CIRCULAR_BUFFER_LENGTH 10

typedef struct CirBufStr
{
    uint8_t cirBuf[CIRCULAR_BUFFER_LENGTH];
    uint16_t cirBufLen;
    uint8_t* pWriteBuf;
    uint8_t* pReadBuf;
    uint8_t* pCirBufMinAddr;
    uint8_t* pCirBufMaxAddr;
}CirBufStr;

void GoToNextWriteBuffer(CirBufStr* pCirBuf)
{
    // This function will skip when the buffer is full.
    if (pCirBuf->pWriteBuf != pCirBuf->pReadBuf)
    {
        // Check if the write buffer reach the maximum address of the circular buffer.
        // If it reaches, then the write buffer moves the minimum address of the circular buffer which is the starting point of the circular buffer array.
        if (pCirBuf->pWriteBuf < pCirBuf->pCirBufMaxAddr)
        {
            pCirBuf->pWriteBuf = pCirBuf->pCirBufMinAddr;
        }
        else
        {
            (pCirBuf->pWriteBuf)++;
        }

        // After moving to the next address, check if the buffer is full.
        if (pCirBuf->pWriteBuf == pCirBuf->pReadBuf)
        {
            printf("WARN: Buffer is full.");
        }
    }
    else
    {
        printf("WARN: Buffer is full.");
    }
    
}

void GoToNextReadBuffer(CirBufStr* pCirBuf)
{
    // This function will skip when the buffer is empty.
    if (pCirBuf->pReadBuf != pCirBuf->pWriteBuf)
    {
        // Check if the read buffer each the maximum address of the circular buffer.
        // If it reaches, then the read buffer move the minimum address of the circular buffer which is the starting point of the ciruclar buffer array.
        if (pCirBuf->pReadBuf < pCirBuf->pCirBufMaxAddr)
        {
            pCirBuf->pReadBuf = pCirBuf->pCirBufMinAddr;
        }
        else
        {
            (pCirBuf->pReadBuf)++;
        }

        // After moving to the next address, check if the buffer is empty.
        if (pCirBuf->pReadBuf == pCirBuf->pWriteBuf)
        {
            printf("WARN: Buffer is empty.");
        }
    }
    else
    {
        printf("WARN: Buffer is empty.");
    }
    
}

int main (void)
{
    CirBufStr myCirBufStr;

    // Initialize myCirBufStr
    myCirBufStr.cirBufLen = CIRCULAR_BUFFER_LENGTH;
    myCirBufStr.pWriteBuf = myCirBufStr.cirBuf;
    myCirBufStr.pReadBuf = myCirBufStr.cirBuf;
    myCirBufStr.pCirBufMinAddr = myCirBufStr.cirBuf;
    myCirBufStr.pCirBufMaxAddr = myCirBufStr.pCirBufMinAddr + myCirBufStr.cirBufLen;

    // Debugging for myCirBufStr.cirBuf
    for (uint16_t i = 0; i < myCirBufStr.cirBufLen; i++)
    {
        myCirBufStr.cirBuf[i] = i;
    }

    printf("myCirBufStr.cirBuf: %p\n", myCirBufStr.cirBuf);
    printf("myCirBufStr.pWriteBuf: %p\n", myCirBufStr.pWriteBuf);
    printf("myCirBufStr.pReadBuf: %p\n", myCirBufStr.pReadBuf);
    printf("myCirBufStr.pCifBufMinAddr: %p\n", myCirBufStr.pCirBufMinAddr);
    printf("myCirBufStr.pCifBufMaxAddr: %p\n", myCirBufStr.pCirBufMaxAddr);

    return 0;
}