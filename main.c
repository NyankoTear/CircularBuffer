#include "circular_buffer.h"

int main (void)
{
    CirBufStr myCirBufStr = {.cirBufLen = CIRCULAR_BUFFER_LENGTH, .cirBufStatus = BUFFER_EMPTY};
    char writeData = 'A';
    char readData[1];

    InitializeCircularBuffer(&myCirBufStr);

    return 0;
}