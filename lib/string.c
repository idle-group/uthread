#include "global.h"
#include "string.h"
void memset(void *dst_, uint8_t value, uint32_t size)
{
    ASSERT(dst_ != NULL);
    uint8_t *dst = (uint8_t *)dst_;
    while (size > 0)
    {
        *dst = value;
        ++dst;
        --size;
    }
}