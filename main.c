#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void CircularBufferManager(uint8_t* pCirBuf, uint16_t length)
{
    uint8_t* pWriteBuf = NULL;
    uint8_t* pReadBuf = NULL;

    pWriteBuf = pCirBuf;
    pReadBuf = pCirBuf;

    printf("\nEntering Circular Buffer Manager...\n");
    printf("Argument pCirBuf pointer: %p\n", pCirBuf);
    printf("Argument pCirBuf length: %i\n", length);
}

int main (void)
{
    uint8_t circularBuf[10];

    for (uint16_t i = 0; i < sizeof(circularBuf) / sizeof(uint8_t); i++)
    {
        circularBuf[i] = i;
    }

    for (uint16_t i = 0; i < sizeof(circularBuf) / sizeof(uint8_t); i++)
    {
        printf("circularBuf[%i] element has %i\n", i, circularBuf[i]);
    }

    CircularBufferManager(circularBuf, 10);

    return 0;
}