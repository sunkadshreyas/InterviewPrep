#include<bits/stdc++.h>

using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};

int findMin(TreeNode* root) {
    while(root->left != NULL) {
        root = root->left;
    }
    return root->data;
}

TreeNode* DeleteNodeInBST(TreeNode* root, int deleteVal) {
    if(root == NULL) {
        return root;
    }
    if(deleteVal < root->data) {
        root->left = DeleteNodeInBST(root->left, deleteVal);
    } else if (deleteVal > root->data) {
        root->right = DeleteNodeInBST(root->right, deleteVal);
    } else {
        if(root->left == NULL && root->right == NULL) {
            // No child nodes
            delete root;
            root = NULL;
        } else if(root->left == NULL) {
            // only right child exists
            TreeNode* currNode = root;
            root = root->right;
            delete currNode;
        } else if(root->right == NULL) {
            // only left child exists
            TreeNode* currNode = root;
            root = root->left;
            delete currNode;
        } else {
            // both left and right child exist
            // find minVal in right sub tree
            int minVal = findMin(root->right);
            // replace the current value with the min value
            root->data = minVal;
            // delete the minValue node in the right subtree
            root->right = DeleteNodeInBST(root->right, deleteVal);
        }
    }
    return root;
}

void LevelOrderTraversal(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        int qSize = q.size();
        for(int i = 0; i < qSize; i++) {
            TreeNode* qNode = q.front();
            q.pop();
            cout << qNode->data << " ";
            if(qNode->left != NULL) {
                q.push(qNode->left);
            }
            if(qNode->right != NULL) {
                q.push(qNode->right);
            }
        }
    }
    cout << "\n";
}

TreeNode* createTreeNode(int data) {
    TreeNode* newTreeNode = new TreeNode();
    newTreeNode->data = data;
    newTreeNode->left = NULL;
    newTreeNode->right = NULL;
    return newTreeNode;
}

TreeNode* InsertNodeInBST(TreeNode* root, int data) {
    if(root == NULL) {
        TreeNode* newTreeNode = createTreeNode(data);
        root = newTreeNode;
        return root;
    }
    if(data <= root->data) {
        root->left = InsertNodeInBST(root->left, data);
    } else {
        root->right = InsertNodeInBST(root->right, data);
    }
    return root;
}

TreeNode* InOrderSuccessor(TreeNode* root, int reqVal) {
    TreeNode* searchNode = root;
    while(searchNode != NULL) {
        if(searchNode->data == reqVal) {
            // found the node, break
            break;
        } else if(searchNode->data > reqVal) {
            searchNode = searchNode->left;
        } else {
            searchNode = searchNode->right;
        }
    }
    if(searchNode->right != NULL) {
        // min value in the right subtree is the successor
        TreeNode* tempNode = searchNode->right;
        while (tempNode->left != NULL) {
            tempNode = tempNode->left;
        }
        return tempNode;
    }
    TreeNode* tempNode = root;
    TreeNode* ancestorNode = NULL;
    while(tempNode != NULL) {
        if(tempNode->data == reqVal) {
            break;
        } else if(tempNode->data > reqVal) {
            ancestorNode = tempNode;
            tempNode = tempNode->left;
        } else {
            tempNode = tempNode->right;
        }
    }
    return ancestorNode;
}

TreeNode* InOrderPredecssor(TreeNode* root, int reqVal) {
    TreeNode* searchNode = root;
    while(searchNode != NULL) {
        if(searchNode->data == reqVal) {
            // found the node, break
            break;
        } else if(searchNode->data > reqVal) {
            searchNode = searchNode->left;
        } else {
            searchNode = searchNode->right;
        }
    }
    if (searchNode->left != NULL) {
        TreeNode* tempNode = searchNode->left;
        while(tempNode->right != NULL) {
            tempNode = tempNode->right;
        }
        return tempNode;
    }
    TreeNode* tempNode = root;
    TreeNode* ancestorNode = NULL;
    while (tempNode != NULL) {
        if (tempNode->data == reqVal) {
            break;
        } else if (reqVal > tempNode->data) {
            ancestorNode = tempNode;
            tempNode = tempNode->right;
        } else {
            tempNode = tempNode->left;
        }
    }
    return ancestorNode;
}

int main() {
    TreeNode* rootNode = NULL;
    rootNode = InsertNodeInBST(rootNode, 15);
    rootNode = InsertNodeInBST(rootNode, 13);
    rootNode = InsertNodeInBST(rootNode, 18);
    rootNode = InsertNodeInBST(rootNode, 10);
    rootNode = InsertNodeInBST(rootNode, 20);
    rootNode = InsertNodeInBST(rootNode, 16);
    rootNode = InsertNodeInBST(rootNode, 17);
    rootNode = InsertNodeInBST(rootNode, 19);
    rootNode = InsertNodeInBST(rootNode, 22);
    LevelOrderTraversal(rootNode);
    // rootNode = DeleteNodeInBST(rootNode, 18);
    // LevelOrderTraversal(rootNode);
    TreeNode* inOrderSuccessorNode = NULL;
    inOrderSuccessorNode = InOrderSuccessor(rootNode, 10);
    cout << "InOrderSuccessor of 10 : " << inOrderSuccessorNode->data << "\n";
    inOrderSuccessorNode = InOrderSuccessor(rootNode, 18);
    cout << "InOrderSuccessor of 18 : " << inOrderSuccessorNode->data << "\n";
    inOrderSuccessorNode = InOrderSuccessor(rootNode, 17);
    cout << "InOrderSuccessor of 17 : " << inOrderSuccessorNode->data << "\n";
    TreeNode* InOrderPredecssorNode = NULL;
    InOrderPredecssorNode = InOrderPredecssor(rootNode, 16);
    cout << "InOrderPredecssor of 16 : " << InOrderPredecssorNode->data << "\n";
    InOrderPredecssorNode = InOrderPredecssor(rootNode, 19);
    cout << "InOrderPredecssor of 19 : " << InOrderPredecssorNode->data << "\n";
    InOrderPredecssorNode = InOrderPredecssor(rootNode, 17);
    cout << "InOrderPredecssor of 17 : " << InOrderPredecssorNode->data << "\n";
    InOrderPredecssorNode = InOrderPredecssor(rootNode, 18);
    cout << "InOrderPredecssor of 18 : " << InOrderPredecssorNode->data << "\n";
    return 0;
}
