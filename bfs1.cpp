#include<iostream> 
#include<stdlib.h> 
#include<queue> 
using namespace std;

class node {
public:
    node *left, *right;
    int data;
};

class Breadthfs {
public:
    node *insert(node *, int);
    void bfs(node *);
};

// function to insert a node in the tree
node* Breadthfs::insert(node *root, int data) {
    if (!root) {
        root = new node;
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        return root;
    }

    queue<node*> q;
    q.push(root);

    while (!q.empty()) {
        node *temp = q.front();
        q.pop();

        if (temp->left == NULL) {
            temp->left = new node;
            temp->left->left = NULL;
            temp->left->right = NULL;
            temp->left->data = data;
            return root;
        }
        else {
            q.push(temp->left);
        }

        if (temp->right == NULL) {
            temp->right = new node;
            temp->right->left = NULL;
            temp->right->right = NULL;
            temp->right->data = data;
            return root;
        }
        else {
            q.push(temp->right);
        }
    }
}

// function to perform BFS
void Breadthfs::bfs(node *head) {
    queue<node*> q;
    q.push(head);
    int qSize;

    while (!q.empty()) {
        qSize = q.size();

        // parallelize the loop for processing nodes at the current level
        #pragma omp parallel for
        for (int i = 0; i < qSize; i++) {
            node* currNode;

            // get the current node from the queue in a critical section
            #pragma omp critical
            {
                currNode = q.front();
                q.pop();
                cout << "\t" << currNode->data;
            }

            // add the adjacent nodes to the queue in a critical section
            #pragma omp critical
            {
                if (currNode->left)
                    q.push(currNode->left);
                if (currNode->right)
                    q.push(currNode->right);
            }
        }
    }
}

int main() {
    node *root = NULL;
    int data;
    char ans;

    // build the tree
    do {
        cout << "\nEnter data => ";
        cin >> data;
        root = Breadthfs().insert(root, data);
        cout << "Do you want to insert one more node? ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    // perform BFS
    Breadthfs().bfs(root);

    return 0;
}
