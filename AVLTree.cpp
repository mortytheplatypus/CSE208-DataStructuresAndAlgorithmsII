#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    int height;
    Node* left;
    Node* right;
};

Node* CreateNode(int);
int getHeight(Node*);
int getBalanceFactor(Node*);

void Find(Node*, int);
Node* Insert(Node*&, int);
Node* Delete(Node*, int);
Node* Balance(Node*);
void PrintTree(Node*);

Node* LL_Rotate(Node*);
Node* RR_Rotate(Node*);
Node* LR_Rotate(Node*);
Node* RL_Rotate(Node*);


int main() {
    freopen("AVLtree.txt", "r", stdin);

    char COMMAND;
    int INPUT;
    Node* root = NULL;

    while (!cin.eof()) {
        cin >> COMMAND >> INPUT;

        if (COMMAND == 'F') {
            Find(root, INPUT);
        } else if (COMMAND == 'I') {
            root = Insert(root, INPUT);
            PrintTree(root);    
            cout << "\n";
        } else if (COMMAND == 'D') {
            // cout << "\n******Sending to Delete(): " << INPUT << "\n";
            root = Delete(root, INPUT);
            PrintTree(root);    
            cout << "\n";
        } else {
            break;
        }
    } 

    return 0;
}

//Done
int getHeight(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

//Done
int getBalanceFactor(Node* node) {
    if (node == NULL) {
        return 0;
    }

    return getHeight(node->left) - getHeight(node->right);
}

//Done
Node* CreateNode(int data) {
    Node* node = new Node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

//Done
void Find(Node* root, int data) {
    if (root == NULL) {
        cout << "False\n";
        return;
    } 

    if (data < root->data) {
        Find(root->left, data);
    } else if (data > root->data) {
        Find(root->right, data);
    } else {
        cout << "True\n";
    }
} 

//Done
Node* Insert(Node* &root, int data) {
    if (root == NULL) {
        return CreateNode(data);
    } else if (data < root->data) {
        root->left = Insert(root->left, data);
    } else if (data > root->data) {
        root->right = Insert(root->right, data);
    } else {
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    root = Balance(root);

    return root;
}

//Done
Node* Delete(Node* root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = Delete(root->left, data);
    } else if (data > root->data) {
        root->right = Delete(root->right, data);
    } else {
        if (root->left == NULL && root->right == NULL) {
            root = NULL;
        } else if (root->left == NULL) {
            *root = *(root->right);
        } else if (root->right == NULL) {
            *root = *(root->left);
        } else {
            Node* node = root->right;
            while(node->left != NULL) {
                node = node->left;
            }
            root->data = node->data;
            root->right = Delete(root->right, data);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    root = Balance(root);
    return root;
}

//Done
Node* Balance(Node* root) {
    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor < -1 || balanceFactor > 1) {
        cout << "Height invariant violated.\n";
        Node* node = root;
        if (balanceFactor == -2) {
            node = node->right;
            if (getHeight(node->right) > getHeight(node->left)) {
                root = RR_Rotate(root);
            } else {
                root = RL_Rotate(root);
            }
        } else if (balanceFactor == 2) {
            node = node->left;
            if (getHeight(node->left) > getHeight(node->right)) {
                root = LL_Rotate(root);
            } else {
                root = LR_Rotate(root);
            }
        }
        cout << "After rebalancing: ";
    }

    return root;
}

//Done
void PrintTree(Node* root) {
    if (root == NULL) {
        return;
    }
    cout << root->data;
    if (root->left == NULL && root->right == NULL) {
        return;
    }

    cout << "(";
    PrintTree(root->left);
    cout << ")(";
    PrintTree(root->right);
    cout << ")";
}

//Done
Node* LL_Rotate(Node* node) {
    Node* t;
    Node* t1;
    Node* t2;

    t = node;
    t1 = node->left;
    t2 = t1->right;

    t1->right = t;
    t->left = t2;

    t->height = 1+ max(getHeight(t2), getHeight(t->right));
    t1->height = 1 + max(getHeight(t), getHeight(t1->left));
    
    return t1;
}

//Done
Node* RR_Rotate(Node* node) {
    Node* t;
    Node* t1;
    Node* t2;

    t = node;
    t1 = node->right;
    t2 = t1->left;

    t1->left = t;
    t->right = t2;

    t->height = 1+ max(getHeight(t2), getHeight(t->left));
    t1->height = 1 + max(getHeight(t), getHeight(t1->right));
    
    return t1;
}

//Done
Node* LR_Rotate(Node* node) {
    Node* t;
    Node* t1;
    Node* t2;

    t = node;
    t1 = node->left;
    t2 = t1->right;

    t->left = t2;
    t1->right = t2->left;
    t2->left = t1;

    t1->height = 1 + max(getHeight(t1->left), getHeight(t1->right));
    t2->height = 1 + max(getHeight(t2->right), getHeight(t1));
    
    t = LL_Rotate(t);
    return t;
}

//Done
Node* RL_Rotate(Node* node) {
    Node* t;
    Node* t1;
    Node* t2;

    t = node;
    t1 = node->right;
    t2 = t1->left;

    t->right = t2;
    t1->left = t2->right;
    t2->right = t1;

    t1->height = 1 + max(getHeight(t1->left), getHeight(t1->right));
    t2->height = 1 + max(getHeight(t2->left), getHeight(t1));
    
    t = RR_Rotate(t);
    return t;
}

//