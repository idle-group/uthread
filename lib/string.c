#include "global.h"
#include "string.h"
#include <assert.h>
void memset(void *dst_, uint8_t value, uint32_t size)
{
    assert(dst_ != NULL);
    uint8_t *dst = (uint8_t *)dst_;
    while (size > 0)
    {
        *dst = value;
        ++dst;
        --size;
    }
}

char *strcpy(char *dst_, const char *src_)
{
    assert(dst_ != NULL && src_ != NULL);
    char *r = dst_;
    while ((*dst_++ = *src_++))
        ;
    return r;
}