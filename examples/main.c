#include "circular_buffer.h"

int main (void)
{
    CirBufStr myCirBufStr = {.cirBufLen = CIRCULAR_BUFFER_LENGTH, .cirBufStatus = BUFFER_EMPTY};
    char writeData = 'A';
    char readData[1];

    InitializeCircularBuffer(&myCirBufStr);

    for (uint16_t i = 0; i < myCirBufStr.cirBufLen - 5; i++)
    {
        WriteCircularBuffer(&myCirBufStr, writeData);
        writeData++;
    }

    for (uint16_t i = 0; i < myCirBufStr.cirBufLen - 5; i++)
    {
        if (ReadCircularBuffer(&myCirBufStr, readData) == 0)
        {
            printf("Data: %s\n", &readData[0]);
        }
    }

    for (uint16_t i = 0; i < myCirBufStr.cirBufLen + 1; i++)
    {
        WriteCircularBuffer(&myCirBufStr, writeData);
        writeData++;
    }

    DebugDataCircularBufferStructure(&myCirBufStr);

    return 0;
}