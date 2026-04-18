#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left;      
    struct Node *right;  
} Node;

Node *build_tree(int start, int end) {
    if (start > end) {
        return NULL;
    }

    int mid = start + (end - start) / 2;
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = mid;
    node->left = build_tree(start, mid - 1);
    node->right = build_tree(mid + 1, end);
    return node;
}
Node* build_structure(int n) {
    return build_tree(1, n);
}

// int main(){
//     int n; scanf("%d", &n);
//     Node* root = build_structure(n);
//     return 0;
// }