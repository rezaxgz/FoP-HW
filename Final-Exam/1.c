#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int n = 0;

int bad_index(int i)
{
    if (i < n && i >= 0)
        return 0;
    return 1;
}

void load(char *line, double *registeries)
{
    int index;
    double num;
    sscanf(line, "load %d %lf", &index, &num);
    if (bad_index(index))
    {
        printf("INVALID REGISTER NUMBER\n");
        return;
    }
    registeries[index] = num;
};

void add(char *line, double *registeries)
{
    int i1, i2, i3;
    sscanf(line, "add %d %d %d", &i1, &i2, &i3);
    if (bad_index(i1) || bad_index(i2) || bad_index(i3))
    {
        printf("INVALID REGISTER NUMBER\n");
        return;
    }
    registeries[i3] = registeries[i1] + registeries[i2];
}

void sub(char *line, double *registeries)
{
    int i1, i2, i3;
    sscanf(line, "sub %d %d %d", &i1, &i2, &i3);
    if (bad_index(i1) || bad_index(i2) || bad_index(i3))
    {
        printf("INVALID REGISTER NUMBER\n");
        return;
    }
    registeries[i3] = registeries[i1] - registeries[i2];
}

void mul(char *line, double *registeries)
{
    int i1, i2, i3;
    sscanf(line, "mul %d %d %d", &i1, &i2, &i3);
    if (bad_index(i1) || bad_index(i2) || bad_index(i3))
    {
        printf("INVALID REGISTER NUMBER\n");
        return;
    }
    registeries[i3] = registeries[i1] * registeries[i2];
}

void divide(char *line, double *registeries)
{
    int i1, i2, i3;
    sscanf(line, "div %d %d %d", &i1, &i2, &i3);
    if (bad_index(i1) || bad_index(i2) || bad_index(i3))
    {
        printf("INVALID REGISTER NUMBER\n");
        return;
    }
    if (registeries[i2] != 0)
    {
        registeries[i3] = registeries[i1] / registeries[i2];
    }
}

long double calc_pow(double i, int n)
{
    double res = 1;
    while (n--)
    {
        res *= i;
    }
    return res;
}

long double sign(int n)
{
    if (n % 2 == 0)
        return 1.0;
    return -1.0;
}

long double fact(int n)
{
    if (n == 0)
        return 1.0;
    double res = 1.0;
    for (int i = 2; i <= n; i++)
        res *= i;
    return res;
}

void sin_cmd(char *line, double *registeries)
{
    int i1, i2, terms;
    sscanf(line, "sin %d %d %d", &i1, &i2, &terms);
    if (bad_index(i1) || bad_index(i2))
    {
        printf("INVALID REGISTER NUMBER\n");
        return;
    }
    long double res = 0.0;
    double x = registeries[i1];
    for (int i = 0; i < terms; i++)
    {
        res += sign(i) * calc_pow(x, 2 * i + 1) / fact(2 * i + 1);
    }
    registeries[i2] = res;
}

void cos_cmd(char *line, double *registeries)
{
    int i1, i2, terms;
    sscanf(line, "cos %d %d %d", &i1, &i2, &terms);
    if (bad_index(i1) || bad_index(i2))
    {
        printf("INVALID REGISTER NUMBER\n");
        return;
    }
    long double res = 0.0;
    double x = registeries[i1];
    for (int i = 0; i < terms; i++)
    {
        res += sign(i) * calc_pow(x, 2 * i) / fact(2 * i);
    }
    registeries[i2] = res;
}

void exp_cmd(char *line, double *registeries)
{
    int i1, i2, terms;
    sscanf(line, "exp %d %d %d", &i1, &i2, &terms);
    if (bad_index(i1) || bad_index(i2))
    {
        printf("INVALID REGISTER NUMBER\n");
        return;
    }
    long double res = 0.0;
    double x = registeries[i1];
    for (int i = 0; i < terms; i++)
    {
        res += calc_pow(x, i) / fact(i);
    }
    registeries[i2] = res;
}

void print(char *line, double *registeries)
{
    int i;
    sscanf(line, "print %d", &i);
    if (bad_index(i))
    {
        printf("INVALID REGISTER NUMBER\n");
        return;
    }
    double x = registeries[i];
    printf("%.4f\n", registeries[i]);
}

int main()
{
    char line[1000];
    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\n")] = '\0';

    sscanf(line, "%d", &n);

    double *registeries = malloc(n * sizeof(double));
    memset(registeries, 0, n * sizeof(double));

    while (fgets(line, sizeof(line), stdin))
    {
        line[strcspn(line, "\n")] = '\0';
        if (strncmp(line, "load", 4) == 0)
        {
            load(line, registeries);
        }
        else if (strncmp(line, "add", 3) == 0)
        {
            add(line, registeries);
        }
        else if (strncmp(line, "sub", 3) == 0)
        {
            sub(line, registeries);
        }
        else if (strncmp(line, "mul", 3) == 0)
        {
            mul(line, registeries);
        }
        else if (strncmp(line, "div", 3) == 0)
        {
            divide(line, registeries);
        }
        else if (strncmp(line, "sin", 3) == 0)
        {
            sin_cmd(line, registeries);
        }
        else if (strncmp(line, "cos", 3) == 0)
        {
            cos_cmd(line, registeries);
        }
        else if (strncmp(line, "exp", 3) == 0)
        {
            exp_cmd(line, registeries);
        }
        else if (strncmp(line, "print", 5) == 0)
        {
            print(line, registeries);
        }
        else if (strncmp(line, "end", 3) == 0)
        {
            break;
        }
    }

    free(registeries);
    return 0;
}