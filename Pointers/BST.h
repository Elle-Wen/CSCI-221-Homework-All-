struct Node;
struct Node* makeEmpty(struct Node* root);
struct Node* insert(struct Node* root, int x);
void inorder(struct Node* root);
struct Node* del(struct Node* root, int x);
struct Node* buildTree(struct Node* root, int* array, int start, int end);


