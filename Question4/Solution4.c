#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for Red-Black Tree
typedef struct Node {
   int data;
   char color; // 'R' for Red, 'B' for Black
   struct Node *left, *right, *parent;
} Node;

// Root of the Red-Black Tree
typedef struct {
   Node* root;
} RedBlackTree;

// Function to create a new node
Node* createNode(int data) {
   Node* newNode = (Node*)malloc(sizeof(Node));
   newNode->data = data;
   newNode->color = 'R'; // New node must be Red
   newNode->left = newNode->right = newNode->parent = NULL;
   return newNode;
}

// Function to rotate left
void rotateLeft(RedBlackTree* tree, Node* x) {
   Node* y = x->right;
   x->right = y->left;
   if (y->left != NULL)
       y->left->parent = x;
   y->parent = x->parent;
   if (x->parent == NULL)
       tree->root = y;
   else if (x == x->parent->left)
       x->parent->left = y;
   else
       x->parent->right = y;
   y->left = x;
   x->parent = y;
}

// Function to rotate right
void rotateRight(RedBlackTree* tree, Node* x) {
   Node* y = x->left;
   x->left = y->right;
   if (y->right != NULL)
       y->right->parent = x;
   y->parent = x->parent;
   if (x->parent == NULL)
       tree->root = y;
   else if (x == x->parent->right)
       x->parent->right = y;
   else
       x->parent->left = y;
   y->right = x;
   x->parent = y;
}

// Fix violations after insertion
void fixInsertion(RedBlackTree* tree, Node* z) {
   while (z->parent && z->parent->color == 'R') {
       Node* grandparent = z->parent->parent;
       if (z->parent == grandparent->left) {
           Node* uncle = grandparent->right;
           if (uncle && uncle->color == 'R') {
               z->parent->color = 'B';
               uncle->color = 'B';
               grandparent->color = 'R';
               z = grandparent;
           } else {
               if (z == z->parent->right) {
                   z = z->parent;
                   rotateLeft(tree, z);
               }
               z->parent->color = 'B';
               grandparent->color = 'R';
               rotateRight(tree, grandparent);
           }
       } else {
           Node* uncle = grandparent->left;
           if (uncle && uncle->color == 'R') {
               z->parent->color = 'B';
               uncle->color = 'B';
               grandparent->color = 'R';
               z = grandparent;
           } else {
               if (z == z->parent->left) {
                   z = z->parent;
                   rotateRight(tree, z);
               }
               z->parent->color = 'B';
               grandparent->color = 'R';
               rotateLeft(tree, grandparent);
           }
       }
   }
   tree->root->color = 'B';
}

// Function to insert a node into the Red-Black Tree
void insert(RedBlackTree* tree, int data) {
   Node* newNode = createNode(data);
   if (!tree->root) {
       tree->root = newNode;
       tree->root->color = 'B';
       return;
   }
   Node* parent = NULL;
   Node* current = tree->root;
   while (current) {
       parent = current;
       if (data < current->data)
           current = current->left;
       else
           current = current->right;
   }
   newNode->parent = parent;
   if (data < parent->data)
       parent->left = newNode;
   else
       parent->right = newNode;
   fixInsertion(tree, newNode);
}

// Function to search for a value in the tree
int search(Node* root, int data) {
   while (root) {
       if (data == root->data)
           return 1;
       else if (data < root->data)
           root = root->left;
       else
           root = root->right;
   }
   return 0;
}

// In-order traversal helper function
void inorderTraversal(Node* root, Node** arr, int* index) {
   if (root) {
       inorderTraversal(root->left, arr, index);
       arr[(*index)++] = root;
       inorderTraversal(root->right, arr, index);
   }
}

// Function to store nodes in an array for display
Node** displayTree(RedBlackTree* tree, int* size) {
   *size = 0;
   Node* current = tree->root;
   Node** arr = (Node**)malloc(100 * sizeof(Node*));
   inorderTraversal(current, arr, size);
   return arr;
}

int main() {
   int n;
   scanf("%d", &n);
   RedBlackTree tree;
   tree.root = NULL;
   for (int i = 0; i < n; i++) {
       char command[10];
       int value;
       scanf("%s", command);
       if (strcmp(command, "insert") == 0) {
           scanf("%d", &value);
           insert(&tree, value);
       } else if (strcmp(command, "search") == 0) {
           scanf("%d", &value);
           printf("%s\n", search(tree.root, value) ? "YES" : "NO");
       } else if (strcmp(command, "display") == 0) {
           int size;
           Node** arr = displayTree(&tree, &size);
           for (int j = 0; j < size; j++) {
               printf("%d(%c) ", arr[j]->data, arr[j]->color);
           }
           printf("\n");
           free(arr);
       }
   }
   return 0;
}
