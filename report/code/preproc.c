#define USE_FOO

#ifdef USE_FOO
static int foo(void)
{
    return 1;
}
#endif /*USE_FOO*/