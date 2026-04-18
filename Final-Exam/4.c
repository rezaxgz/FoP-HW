#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int idx = 0;

long long solve(int *is_null, char **preorder)
{
    char *token = preorder[idx];
    idx++;

    if (strcmp(token, "x") == 0)
    {
        *is_null = 1;
        return 0;
    }

    *is_null = 0;
    int val = atoi(token);

    int left_null = 0;
    int right_null = 0;

    long long left_val = solve(&left_null, preorder);
    long long right_val = solve(&right_null, preorder);

    if (left_null && right_null)
    {
        return val;
    }
    else if (!left_null && !right_null)
    {
        return val * (left_val + right_val);
    }
    else
    {
        long long child_val;
        if (!left_null)
        {
            child_val = left_val;
        }
        else
        {
            child_val = right_val;
        }
        return val + 2 * child_val;
    }
}

int main()
{
    char line[5000];
    if (!fgets(line, sizeof(line), stdin))
    {
        return 1;
    }

    char *preorder[1000];
    int count = 0;
    char *token = strtok(line, " \n");
    while (token != NULL)
    {
        preorder[count++] = token;
        token = strtok(NULL, " \n");
    }

    int root_null = 0;
    printf("%lld", solve(&root_null, preorder));

    return 0;
}