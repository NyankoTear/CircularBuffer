#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define CIRCULAR_BUFFER_LENGTH 10
#define POINTER_BYTE_SIZE 8

typedef enum 
{
    BUFFER_OK = 0, 
    BUFFER_BUSY = 1
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
    myCirBufStr.pWriteBuf.pBlockStartAddr = myCirBufStr.cirBuf;
    myCirBufStr.pWriteBuf.pBlockEndAddr = myCirBufStr.cirBuf + 1;
    myCirBufStr.pReadBuf.pBlockStartAddr = myCirBufStr.cirBuf;
    myCirBufStr.pReadBuf.pBlockEndAddr = myCirBufStr.cirBuf + 1;
    myCirBufStr.pCirBufMinAddr = myCirBufStr.cirBuf;
    myCirBufStr.pCirBufMaxAddr = myCirBufStr.pCirBufMinAddr + myCirBufStr.cirBufLen;

    DebugPointerAddressCircularBufferStructure(&myCirBufStr);

    for (uint16_t i = 0; i < myCirBufStr.cirBufLen - 5; i++){
        GoToNextReadBuffer(&myCirBufStr);
    }

    DebugPointerAddressCircularBufferStructure(&myCirBufStr);

    // DebugPointerAddressCircularBufferStructure(&myCirBufStr);

    // for (uint16_t i = 0; i < myCirBufStr.cirBufLen + 10; i++)
    // {
    //     WriteCircularBuffer(&myCirBufStr, writeData);
    //     writeData++;
    // }

    // DebugDataCircularBufferStructure(&myCirBufStr);

    // for (uint16_t i = 0; i < myCirBufStr.cirBufLen + 10; i++)
    // {
    //     if (ReadCircularBuffer(&myCirBufStr, readData) == BUFFER_OK)
    //     {
    //         printf("Read data: %c\n", readData[0]);
    //     }
    // }

    // DebugPointerAddressCircularBufferStructure(&myCirBufStr);
    // DebugDataCircularBufferStructure(&myCirBufStr);

    // writeData = 'A';

    // for (uint16_t i = 0; i < myCirBufStr.cirBufLen - 5; i++)
    // {
    //     WriteCircularBuffer(&myCirBufStr, writeData);
    //     writeData++;
    // }

    // DebugDataCircularBufferStructure(&myCirBufStr);

    // for (uint16_t i = 0; i < myCirBufStr.cirBufLen; i++)
    // {
    //     if (ReadCircularBuffer(&myCirBufStr, readData) == BUFFER_OK)
    //     {
    //         printf("Read data: %c\n", readData[0]);
    //     }
    // }

    // DebugDataCircularBufferStructure(&myCirBufStr);

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

// CIRCULAR_BUFFER_STATUS WriteCircularBuffer(CirBufStr* pCirBuf, const char data)
// {
//     uint8_t* pNextBufAddr = (pCirBuf->pWriteBuf) + 1;
        
//     // Check if the after buffer reach the maximum address of the circular buffer.
//     // If it reaches, then the after buffer move the minimum address of the circular buffer which is the starting point of the circular buffer array.
//     if (!(pNextBufAddr < pCirBuf->pCirBufMaxAddr))
//     {
//         pNextBufAddr = pCirBuf->pCirBufMinAddr;
//     }

//     // DEBUG
//     printf("pNextBufAddr: %p\n", pNextBufAddr);

//     // Check if the circular buffer is full.
//     if (pNextBufAddr == pCirBuf->pReadBuf)
//     {
//         if (pCirBuf->pWriteBuf == pCirBuf->pPreviousWriteBufAddr)
//         {
//             printf("WARN: Buffer is full.\n");
//             return BUFFER_BUSY;
//         }
//         else
//         {
//             pCirBuf->pPreviousWriteBufAddr = pCirBuf->pWriteBuf;
//             *(pCirBuf->pWriteBuf) = data;
//         }
//     }
//     else
//     {
//         *(pCirBuf->pWriteBuf) = data;
//         GoToNextWriteBuffer(pCirBuf);
//         return BUFFER_OK;
//     }
// }

// CIRCULAR_BUFFER_STATUS ReadCircularBuffer(CirBufStr* pCirBuf, char* data)
// {
//     if (pCirBuf->pReadBuf == pCirBuf->pWriteBuf)
//     {
//         if (pCirBuf->pReadBuf == pCirBuf->pPreviousReadBufAddr)
//         {
//             printf("WARN: Buffer is empty.\n");
//             return BUFFER_BUSY;
//         }
//         else
//         {
//             pCirBuf->pPreviousReadBufAddr = pCirBuf->pReadBuf;
//             const char cirBufData = *(pCirBuf->pReadBuf);
//             *data = cirBufData;
//             return BUFFER_OK;
//         }
        
//     }
//     else
//     {
//         const char cirBufData = *(pCirBuf->pReadBuf);
//         *data = cirBufData;
//         GoToNextReadBuffer(pCirBuf);
//         return BUFFER_OK;
//     }
    



//     // if (pCirBuf->pReadBuf != pCirBuf->pWriteBuf)
//     // {
//     //     const char cirBufData = *(pCirBuf->pReadBuf);
//     //     *data = cirBufData;
//     //     GoToNextReadBuffer(pCirBuf);
//     //     return BUFFER_OK;
//     // }
//     // else
//     // {
//     //     return BUFFER_BUSY;
//     // }
// }

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