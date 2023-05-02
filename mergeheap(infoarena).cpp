#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>

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
    bool seen; /// For extract-min, to know when to exit the while(true)

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
    this->seen=false;
}

class FibonacciHeap
{
private:

    /// Number of nodes in the heap
    int n;
    /// Pointer to the minimum node in the heap
    Node* minNode;

public:

    FibonacciHeap();

    /// Important Methods (The operations of the Fibonacci Heap)
    Node* insert(int key); /// This was adjusted to be "Node*" instead of "void" for testing purposes / for the interactive menu
    void merge(FibonacciHeap& FH);
    Node* extractMax(); /// This was adjusted to be "Node*" instead of "int" for testing purposes / for the interactive menu


    ~FibonacciHeap() {};



};

FibonacciHeap::FibonacciHeap()
{
    this->minNode = nullptr;
    this->n = 0;

}


Node* FibonacciHeap::insert(int key)
{
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
        if (node->key > this->minNode->key)
        {
            this->minNode = node;
        }
    }

    this->n++;
    return node;

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
        if (FH.minNode->key>this->minNode->key)
            this->minNode=FH.minNode;
    }

    /// Update the size of this Fibonacci heap by adding the size of FH
    this->n += FH.n;

    /// Clear FH
    FH.minNode = nullptr;
    FH.n = 0;
}


Node* FibonacciHeap::extractMax()
{
    if (this->minNode == nullptr)
    {
        cout << "The Fibonacci Heap is empty." << endl;
        return this->minNode;
    }
    this->minNode->degree=0;
    Node* oldMinNode=this->minNode; /// Keep the current minNode, because we will return it later
    int maxDegree = ceil(log2(this->n))+1;/// The maximum possible degree from the Fibonacci Heap
    vector<Node*> degreeNodes(maxDegree, nullptr); /// The vector with the length of maxDegree for later

    if (this->minNode->child!=nullptr) /// If this->minNode has children
    {
        Node* current = this->minNode->child; /// Make every child's parent pointer to nullptr
        do
        {
            current->parent=nullptr;
            current = current->right;
        }
        while (current != this->minNode->child);

        this->minNode->right->left = current->left; /// Add all children of this->minNode to the root list
        current->left->right = this->minNode->right;
        this->minNode->right = current;
        current->left = this->minNode;

        this->minNode->child=nullptr; /// We don't need this anymore since we are going to cut this->minNode
    }

    Node* newMinNode=this->minNode->right; /// Set a temporary minNode to be able to continue

    if(this->minNode == newMinNode) /// If this->minNode is the only node in the root list, stop here
    {
        this->minNode=nullptr;
        this->n--;
        return oldMinNode;
    }

    this->minNode->left->right=this->minNode->right; /// Link the left and right of this->minNode (because we will cut this->minNode)
    this->minNode->right->left=this->minNode->left;

    this->minNode->left=nullptr; /// Make the left and right of the this->minNode nullptr because we have already linked its siblings and will soon need to remove it
    this->minNode->right=nullptr;

    this->minNode=newMinNode; /// Update this->minNode


    Node* current=this->minNode; /// We are getting to the combining of the trees with the same degree part. We start from this->minNode

    bool foundSeen = false; /// To know when to exit the main while

    while (foundSeen!=true)
    {
        current->seen = true; /// Update the seen attribute of "current", to know that we have visited the current node
        Node* next = current->right; /// To be able to keep in mind where we need to go next
        if(next->seen == true) /// If where we need to go next is already a previously visited node, it means we have completed our job here
            foundSeen = true;

        int degree = current->degree; /// Get current node degree

        while(degreeNodes[degree] != nullptr) /// While (degreeNodes[degree] != nullptr), we ensure that the current node is combined with every other node of the same degree
        {
            Node* other = degreeNodes[degree]; /// Take the element from the vector
            degreeNodes[degree] = nullptr; /// Reset the degreeNodes[degree]

            if (current->key < other->key) /// To make every time "other" a child of "current"
            {
                swap(current, other);
            }
            other->seen = false; /// This will be important for next extractMin operations

            /// Link "other" as a child of "current"

            other->left->right=other->right; /// Link the left and right of "other" (because we will cut "other")
            other->right->left=other->left;

            other->parent=current; /// Update its parent to "current"

            degree++; /// Update degree of "current", "other" is now a child of "current" so +1
            current->degree++;

            if (current->child == nullptr) /// If "current" has no previous children just set its child pointer to "other"
            {
                current->child = other;
                other->right = other->left = other; /// Set the left and right of "other" to himself
            }
            else
            {
                /// If "current" has children, merge "other" to "current's" children
                current->child->left->right = other;
                other->left = current->child->left;
                other->right = current->child;
                current->child->left = other;
            }
        }

        degreeNodes[degree] = current; /// Update degreeNodes[degree]

        if (current->key >= this->minNode->key) /// Update the minimum if necessary
        {
            this->minNode = current;
        }

        current = next; /// Go to the next node that we need to visit
    }

    Node* current2 = this->minNode; /// Set the "seen" attribute to false for every root to prepare for the next extractMin operation
    do
    {
        current2->seen=false;
        current2 = current2->right;
    }
    while (current2 != this->minNode);

    this->n--;

    return oldMinNode;
}


int main()
{
    ifstream f1("mergeheap.in");
    ofstream f2("mergeheap.out");
    int N;
    int Q;
    f1>>N;
    f1>>Q;
    vector<FibonacciHeap> lista (N);

    while(Q!=0)
    {
        int y;
        f1>>y;
        if(y==1)
        {
            int nr;
            int x;
            f1>>nr;
            f1>>x;
            lista[nr-1].insert(x);
        }
        if (y==2)
        {
            int nr;
            f1>>nr;
            Node* nod=lista[nr-1].extractMax();
            f2<<nod->key<<endl;
            delete nod;
        }
        if(y==3)
        {
            int a;
            int b;
            f1>>a;
            f1>>b;
            lista[a-1].merge(lista[b-1]);

        }

        Q--;
    }

    f1.close();
    f2.close();
    return 0;

}
