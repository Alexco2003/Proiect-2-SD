#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

struct Node
{

    int key; /// The value of the node
    int degree; /// The number of children of the node
    bool marked; /// Whether the node is marked
    Node* parent; /// The parent of the node
    Node* left; /// The left sibling of the node
    Node* right; /// The right sibling of the node
    Node* child; /// One of the node's children (if any)

    Node(int key);

};

Node::Node(int key)
{
    this->key = key;
    this->degree = 0;
    this->parent = nullptr;
    this->child = nullptr;
    this->left = this;
    this->right = this;
    this->marked = false;
}

class FibonacciHeap
{
private:

    /// Number of nodes in the heap
    int n;
    /// Pointer to the minimum node in the heap
    Node* minNode;
    /// Vector with all the nodes from the root list
    vector<Node*> nodes;

public:

    FibonacciHeap();

    int getN();
    Node* getMinNode();
    vector<Node*> getNodes();

    int findMin();
    void insert(int key);
    void merge(FibonacciHeap& FH);
    void decreaseKey(Node* x, int key);

    ~FibonacciHeap() {};

};

FibonacciHeap::FibonacciHeap()
{
    this->minNode = nullptr;
    this->n = 0;
}

int FibonacciHeap::getN()
{
    return this->n;
}
Node* FibonacciHeap::getMinNode()
{
    return this->minNode;
}
vector<Node*> FibonacciHeap::getNodes()
{
    return this->nodes;
}


int FibonacciHeap::findMin()
{
    if (this->minNode == nullptr)
    {
        cout << "The Fibonacci Heap is empty." << endl;
        return 0;
    }

    return this->minNode->key;
}

void FibonacciHeap::insert(int key)
{
    if(key<0)
    {
        return;
    }
    /// Create a new node with the given key
    Node* node = new Node(key);

    /// Add the new node to the root list
    if (this->minNode == nullptr)
    {
        this->minNode = node;
        this->minNode->left = this->minNode;
        this->minNode->right = this->minNode;
    }
    else
    {
        this->minNode->left->right = node;
        node->left = this->minNode->left;
        this->minNode->left = node;
        node->right = this->minNode;

        /// Update minimum node if necessary
        if (node->key < this->minNode->key)
        {
            this->minNode = node;
        }
    }

    this->n++;

    this->nodes.push_back(node);
}

void FibonacciHeap::merge(FibonacciHeap& FH)
{
    int i=0;

    /// If this Fibonacci heap is empty, set its minimum node to be the minimum node of FH
    if (this->minNode == nullptr)
    {
        this->minNode=FH.minNode;
        i++;
    }

    /// If FH is empty, do nothing
    if (FH.minNode == nullptr)
    {
        i++;
    }

    /// If both heaps are not empty, merge their root lists
    if(i==0)
    {
        /// Get the minimum nodes and their right nodes from both heaps
        Node* minNode1 = this->minNode;
        Node* minNode2 = FH.minNode;
        Node* minNode1Right = minNode1->right;
        Node* minNode2Right = minNode2->right;

        /// Link the two root lists together
        minNode1->right = minNode2Right;
        minNode2Right->left = minNode1;
        minNode2->right = minNode1Right;
        minNode1Right->left = minNode2;

        /// Update the minimum node if necessary
        if (FH.minNode->key<this->minNode->key)
            this->minNode=FH.minNode;
    }

    /// Update the size of this Fibonacci heap by adding the size of FH
    this->n += FH.n;

    /// Clear FH
    FH.minNode = nullptr;
    FH.n = 0;
}


void FibonacciHeap::decreaseKey(Node* x, int key)
{
    if (key >= x->key)
    {
        /// New key is greater than current key, error
        return;
    }

    x->key = key;
    Node* y = x->parent;

    if(y==nullptr) /// The case if x is already in the root list
    {
        if (x->key < this->minNode->key)
        {
            this->minNode = x;
        }

        return;
    }

    if(y->key<x->key) /// The case if the decrease key does not violate the min heap property
        return;



    if(x->right==x && x->left==x) /// If x is the only child of it's parent y, update the child pointer of y to nullptr
        y->child=nullptr;


    if (y->child==x) /// If y has more children (not just x)
    {


        y->child=x->right; /// If the pointer of child of y is to x (that we need to cut and add to the root list), update it to point to the next child (right sibling of x)
        x->left->right=x->right; /// Link the left and right of x (because we will cut x)
        x->right->left=x->left;
    }
    else
    {
        x->left->right=x->right; /// Link the left and right of x (because we will cut x)
        x->right->left=x->left;

    }

    /// Cut x from his parent and move it to the root list
    this->minNode->left->right = x;
    x->left = this->minNode->left;
    this->minNode->left = x;
    x->right = this->minNode;
    x->parent=nullptr;
    x->marked=false;
    this->nodes.push_back(x);

    /// Update minimum node if necessary
    if (x->key < this->minNode->key)
    {
        this->minNode = x;
    }

    y->degree--;





    if (y->marked==false) /// If parent of x is not marked, mark it
    {
        y->marked=true;
        if(y->parent==nullptr) /// If parent of x is a root, don't mark it because it is redundant
            y->marked=false;
        return;

    }
    else
        while (y->marked==true && y->parent!=nullptr)
        {
            /// We make x the new z, y the parent of y, and do the same thing as before
            Node* z=y;
            y=y->parent;

            if(z->right==z && z->left==z) /// If z is the only child of it's parent y, update the child pointer of y to nullptr
                y->child=nullptr;

            if (y->child==z)
            {
                y->child=z->right; /// If the pointer of child of y is to z (that we need to cut and add to the root list), update it to point to the next child (right sibling of z)
                z->left->right=z->right; /// Link the left and right of z (because we will cut z)
                z->right->left=z->left;
            }
            else
            {
                z->left->right=z->right; /// Link the left and right of z (because we will cut z)
                z->right->left=z->left;

            }
            /// Update z to the root list
            this->minNode->left->right = z;
            z->left = this->minNode->left;
            this->minNode->left = z;
            z->right = this->minNode;
            z->parent=nullptr;
            z->marked=false;
            this->nodes.push_back(z);

            /// Update minimum node if necessary
            if (z->key < this->minNode->key)
            {
                this->minNode = z;
            }

            y->degree--;



        }

    y->marked=true; ///If y is not a root, mark it

    if(y->parent==nullptr) ///If y is a root, don't mark it because it is redundant
        y->marked=false;



}


