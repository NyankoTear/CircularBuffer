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


void CircularBufferManager(uint8_t* pCirBuf, uint16_t length)
{
    static uint8_t* pWriteBuf;
    static uint8_t* pReadBuf;

    static const uint8_t* pCirBufMinAddr;
    static const uint8_t* pCirBufMaxAddr;

    pWriteBuf = pCirBuf;
    pReadBuf = pCirBuf;

    pCirBufMinAddr = pCirBuf;
    pCirBufMaxAddr = pCirBufMinAddr + length;

    printf("\nEntering Circular Buffer Manager...\n");
    printf("Argument pCirBuf pointer: %p\n", pCirBuf);
    printf("Argument pCirBuf length: %i\n", length);
    printf("pCirBufMinAddr: %p\n", pCirBufMinAddr);
    printf("pCirBufMaxAddr: %p\n", pCirBufMaxAddr);

    // Next step checker
    if (pCirBuf < pCirBufMaxAddr)
    {
        pWriteBuf++;
        pReadBuf++;
    }
    else
    {
        pWriteBuf = pCirBufMinAddr;
        pReadBuf = pCirBufMinAddr;
    }
    
}

int main (void)
{
    uint8_t circularBuf[10];
    CirBufStr myCirBufStr;

    // Initialize myCirBufStr
    myCirBufStr.cirBufLen = CIRCULAR_BUFFER_LENGTH;
    myCirBufStr.pWriteBuf = myCirBufStr.cirBuf;
    myCirBufStr.pReadBuf = myCirBufStr.cirBuf;
    myCirBufStr.pCirBufMinAddr = myCirBufStr.cirBuf;
    myCirBufStr.pCirBufMaxAddr = myCirBufStr.pCirBufMinAddr + myCirBufStr.cirBufLen;

    // Debugging for circularBuf
    for (uint16_t i = 0; i < sizeof(circularBuf) / sizeof(uint8_t); i++)
    {
        circularBuf[i] = i;
    }

    for (uint16_t i = 0; i < sizeof(circularBuf) / sizeof(uint8_t); i++)
    {
        printf("circularBuf[%i]: %p\n", i, &circularBuf[i]);
    }

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

    CircularBufferManager(circularBuf, 10);

    return 0;
}