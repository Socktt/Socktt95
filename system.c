void * memset(void *dest, int c, int n)
{
    unsigned char *ptr = dest;
    while (n-- > 0)
        *ptr++ = c;
    return dest;
}