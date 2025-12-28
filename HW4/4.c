#include <stdio.h>
void dfs(int v, int arr[], int visited[], int n){
    visited[v] = 1;
    for (int i = 0; i < n; i++){
        if(i == v)continue;
        if(visited[i])continue;
        if(arr[i * n + v])dfs(i, arr, visited, n);
    }
}
int main(){
    int n; scanf("%d", &n);
    int arr[n * n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &arr[i * n + j]);
        }
    }
    int visited[n];
    for(int i = 0; i < n; i++)visited[i] = 0;

    int components = 0;
    for(int v = 0; v < n; v++){
        if(visited[v] == 0){
            components++;
            dfs(v, arr, visited, n);
        }
    }
    printf("%d",components);
    return 0;
}