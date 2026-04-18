#include <stdio.h>
#include <string.h>

void join(char *a, char *b, char *res)
{
    for (int row = 0; row < 9; row++)
    {

        while (*a && *a != '\n')
        {
            *res++ = *a++;
        }
        if (*a == '\n')
            a++;

        *res++ = ' ';
        *res++ = ' ';
        *res++ = ' ';

        while (*b && *b != '\n')
        {
            *res++ = *b++;
        }
        if (*b == '\n')
            b++;

        *res++ = '\n';
    }
    *res = '\0';
}

void to_segment(int n, char *res)
{
    int t = 0, lu = 0, ru = 0, m = 0, ll = 0, rl = 0, b = 0;
    if (n == 0)
    {
        t = 1;
        b = 1;
        lu = 1;
        ll = 1;
        ru = 1;
        rl = 1;
    }
    else if (n == 1)
    {
        ru = 1;
        rl = 1;
    }
    else if (n == 2)
    {
        t = 1;
        ru = 1;
        m = 1;
        ll = 1;
        b = 1;
    }
    else if (n == 3)
    {
        t = 1;
        ru = 1;
        m = 1;
        rl = 1;
        b = 1;
    }
    else if (n == 4)
    {
        lu = 1;
        ru = 1;
        m = 1;
        rl = 1;
    }
    else if (n == 5)
    {
        t = 1;
        lu = 1;
        m = 1;
        rl = 1;
        b = 1;
    }
    else if (n == 6)
    {
        t = 1;
        lu = 1;
        m = 1;
        ll = 1;
        rl = 1;
        b = 1;
    }
    else if (n == 7)
    {
        t = 1;
        ru = 1;
        rl = 1;
    }
    else if (n == 8)
    {
        t = 1;
        m = 1;
        b = 1;
        lu = 1;
        ru = 1;
        ll = 1;
        rl = 1;
    }
    else if (n == 9)
    {
        t = 1;
        lu = 1;
        ru = 1;
        m = 1;
        rl = 1;
        b = 1;
    }
    char seg[73];
    memset(seg, ' ', 72);
    seg[72] = '\0';
    for (int i = 7; i < 73; i += 8)
        seg[i] = '\n';

    if (t)
    {
        for (int i = 1; i <= 5; i++)
            seg[i] = '*';
    }
    for (int row = 1; row <= 3; row++)
    {
        int idx = row * 8;
        if (lu)
            seg[idx] = '*';
        if (ru)
            seg[idx + 6] = '*';
    }

    if (m)
    {
        for (int i = 33; i <= 37; i++)
            seg[i] = '*';
    }

    for (int row = 5; row <= 7; row++)
    {
        int idx = row * 8;
        if (ll)
            seg[idx] = '*';
        if (rl)
            seg[idx + 6] = '*';
    }

    if (b)
    {
        for (int i = 65; i <= 69; i++)
            seg[i] = '*';
    }
    memcpy(res, seg, 73 * sizeof(char));
}

void create(int n, char *res)
{
    if (n < 10)
    {
        to_segment(n, res);
    }
    else
    {
        char left[100000];
        char right[100000];

        create(n / 10, left);
        to_segment(n % 10, right);

        join(left, right, res);
    }
}
int main()
{
    char n[1000];
    scanf("%s", n);

    char res[100000];
    char temp[100000];

    res[0] = '\0';

    for (int i = 0; n[i]; i++)
    {
        char digit_seg[100];
        to_segment(n[i] - '0', digit_seg);

        if (res[0] == '\0')
        {
            memcpy(res, digit_seg, 73);
        }
        else
        {
            join(res, digit_seg, temp);
            memcpy(res, temp, 100000);
        }
    }

    printf("%s", res);
}
