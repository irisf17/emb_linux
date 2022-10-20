#ifndef FIFO_H
#define FIFO_H
#include <stdint.h>

const int FIFO_SIZE = 5;

class Fifo
{
public:
    Fifo();
    void test_normal_flow();
    void test_underflow();
    void test_overflow();
    void test_overwrite();

    int *head = buffer;
    int *tail = buffer;
    int init = 0;
    int circular_get();
    void circular_put(int32_t item);
    bool circular_is_empty();
    bool circular_is_full();
    void circular_reset();
    int position = 0;
    int buffer[FIFO_SIZE];

private:
    //int buffer[FIFO_SIZE];
    //int position = 0;
    // add variables pointing to the front and back of the buffer
};

#endif // FIFO_H