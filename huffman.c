
#include <stdio.h>
#include <stdlib.h>

struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
};

struct Node* createNode(char ch, int freq) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->ch = ch;
    node->freq = freq;
    node->left = node->right = NULL;

    return node;
}

// Find the node with minimum frequency
int findMin(struct Node* nodes[], int n) {
    int min = 0;

    for (int i = 1; i < n; i++) {
        if (nodes[i]->freq < nodes[min]->freq)
            min = i;
    }

    return min;
}

// Generate Huffman codes
void printCodes(struct Node* root, int code[], int top,
                int *totalBits) {
    if (root->left == NULL && root->right == NULL) {
        printf("%c\t%d\t", root->ch, root->freq);

        for (int i = 0; i < top; i++)
            printf("%d", code[i]);

        printf("\n");

        *totalBits += root->freq * top;
        return;
    }

    if (root->left != NULL) {
        code[top] = 0;
        printCodes(root->left, code, top + 1, totalBits);
    }

    if (root->right != NULL) {
        code[top] = 1;
        printCodes(root->right, code, top + 1, totalBits);
    }
}

int main() {
    char ch[] = {'a', 'c', 'd', 'e', 'o',
                 'm', 's', 't', 'u'};

    int freq[] = {20, 11, 2, 10, 15, 8, 10, 22, 2};

    int n = 9;
    struct Node* nodes[20];

    for (int i = 0; i < n; i++)
        nodes[i] = createNode(ch[i], freq[i]);

    int size = n;

    // Build Huffman tree
    while (size > 1) {
        int i = findMin(nodes, size);
        struct Node* left = nodes[i];

        nodes[i] = nodes[size - 1];
        size--;

        int j = findMin(nodes, size);
        struct Node* right = nodes[j];

        struct Node* parent =
            createNode('$', left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        nodes[j] = parent;
    }

    int code[100];
    int totalBits = 0;

    printf("Character\tFrequency\tHuffman Code\n");

    printCodes(nodes[0], code, 0, &totalBits);

    printf("\nTotal encoded bits (frequency units): %d\n",
           totalBits);

    printf("Total memory required: %d bits\n", totalBits * 100);
    printf("Total memory required: %d bytes\n",
           (totalBits * 100) / 8);

    return 0;
}