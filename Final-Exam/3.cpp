#include <stdlib.h>

int *aggregator(int *a, int *b)
{
    int *res = (int *)malloc(2000 * sizeof(int));

    int *return_value = res;

    long long sum_a = 0;
    long long sum_b = 0;

    int a_finished = 0;
    int b_finished = 0;

    int state = 0;

    int a_count = 0;
    int b_count = 0;

    while ((a_finished && b_finished) != 1)
    {
        if (state == 0)
        {
            if (!a_finished)
            {
                *res = *a;
                if (*a == sum_a)
                    a_finished = 1;
                sum_a += *a;
                res++;
                a++;
                a_count++;
            }
        }
        else
        {
            if (!b_finished)
            {
                *res = *b;
                if (*b == sum_b)
                    b_finished = 1;
                sum_b += *b;
                res++;
                b++;
                b_count++;
            }
        }
        state ^= 1;
    }
    return return_value;
}
