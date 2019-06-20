/*
 * Copyright (c) 2019 FTC team 4634 FROGbots
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdint.h>
#include "RollingIntegerAverage.h"

RollingIntegerAverage::RollingIntegerAverage(uint8_t capacity)
{
    buff = new int16_t[capacity];
    this->capacity = capacity;
    reset();
}

RollingIntegerAverage::~RollingIntegerAverage()
{
    delete[] buff;
}

void RollingIntegerAverage::add(int16_t val)
{
    if(!(index < capacity))
    {
        index = 0;
    }
    buff[index] = val;
    index++;
}

int16_t RollingIntegerAverage::avg()
{
    int32_t sum = 0;

    for(uint8_t i = 0; i < capacity; i++)
    {
        sum += buff[i];
    }

    return sum / capacity;
}

void RollingIntegerAverage::reset()
{
    for(uint8_t i = 0; i < capacity; i++)
    {
        buff[i] = 0;
    }
}
