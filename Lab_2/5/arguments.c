#include <stdio.h>
#include <stdlib.h>

#define MAXINT 2147483647


int arg_to_int(char *arg)
{
    char *ptr = arg;

    int num = 0;
    int factor = 1;
    
    if (*ptr == '-')
    {
        factor = -1;
        ++ptr;
    }

    while (*ptr)
    {
        if ('0' - 1 < *ptr && *ptr < '9' + 1)
        {
            num = num * 10 + (*ptr - '0');
        }
        ++ptr;
    }
    num *= factor;

    return num;
}

int is_number(char *arg)
{
    char *ptr = arg;
    int dot = 0;

    if (*ptr == '-')
    {
        ++ptr;
    }

    while (*ptr)
    {
        if (*ptr == '.')
        {
            if (dot > 0)
            {
                return 0;
            }
            ++dot;
            
        }
        else if ('0' > *ptr || *ptr > '9')
        {
            return 0;
        }
        ++ptr;
    }

    return 1;
}

int is_integer(char *arg)
{
    char *ptr = arg;
    
    if (*arg == '-')
    {
        ++ptr;
    }

    while (*ptr)
    {
        if ('0' > *ptr || *ptr > '9')
        {
            return 0;
        }
        ++ptr;
    }
    return 1;
}

int is_flag(char const* arg)
{
    return arg[0] == '-' || arg[0] == '/';
}

int get_rand_int(int a, int b)
{
    if (a == b)
    {
        return a;
    }
    return random() % (b - a + 1) + a;
}

int swap_elements(int *item_0, int *item_1)
{
    // printf("%p %p\n", item_0, item_1);
    int buffer = *item_0;
    *item_0 = *item_1;
    *item_1 = buffer;

    return 0;
}

int swap_max_min(int a[])
{
    int max = -MAXINT;
    int min = MAXINT;
    int i_max = 0;
    int i_min = 0;
    
    int i;
    for (i = 0; i < 10; ++i)
    {
        if (a[i] > max)
        {
            max = a[i];
            i_max = i;
        }
        if (a[i] < min)
        {
            min = a[i];
            i_min = i;
        }
    }

    swap_elements(a + i_min, a + i_max);

    return 0;
}

int make_set(int *a, int *set)
{
    int length = 0;
    int i, j, item;
    int in_set;
    for (i = 0; i < 10; ++i)
    {
        item = a[i];
        in_set = 0;

        for (j = 0; j < length; ++j)
        {
            if (item == set[j])
            {
                in_set = 1;
                break;
            }
        }   
        if (!in_set)
        {
            set[length++] = item;
        }
    }

    return length;
}