#include "../include/fifo.h"
#include <stdint.h>

Fifo::Fifo()
{
}
// ---- Fifo circular TESTING-----
int Fifo::circular_get()
{
    if (!circular_is_empty())
    {
        int32_t front = *head;
        head++;

        if (position > 0)
        {
            position--;
        }
        if (head == &buffer[0] + 5)
        {
            head = &buffer[0];
        }
        return front;
    }
return 0;
}

void Fifo::circular_put(int32_t item)
{
    *tail = item;
    if (head == tail && init != 0)
    {
        head++;
        if (head == &buffer[0] + 5)
        {
            head = &buffer[0];
        }
    }
    else
    {
        init = 1;
    }
    tail++;
    if (tail == &buffer[0] + 5)
    {
        tail = &buffer[0];
    }
    if (position < 5)
    {
        position++;
    }
}


bool Fifo::circular_is_empty()
{
    if (position < 0)
    {
        position = 0;
    }
    return position == 0;
}

bool Fifo::circular_is_full()
{
    return position == 5;
}

void Fifo::circular_reset()
{
    for (int i = 0; i < 5; i++)
    {
        buffer[i] = 0;
    }
    position = 0;
}