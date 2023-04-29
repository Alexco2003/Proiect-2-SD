#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <windows.h>
#include <chrono>
#include <thread>

using namespace std;

void pause(int seconds)
{
    this_thread::sleep_for(chrono::seconds(seconds));
}

void clearScreen()
{
    system("CLS");
}

void Menu1()
{
    clearScreen();
    cout << "\n1-Test the Fibonacci Heap A";
    cout << "\n2-Create your own Fibonacci Heap";
    cout << "\n3-Stop";
    cout << endl;

}

void Menu2()
{
    clearScreen();
    cout << "\n1-Test the Fibonacci Heap A";
    cout << "\n2-Back to your own Fibonacci Heap";
    cout << "\n3-Stop";
    cout << endl;

}

void Menu3()
{
    clearScreen();
    cout << "\n1-Insertion";
    cout << "\n2-Find Minimum";
    cout << "\n3-Merge";
    cout << "\n4-Decrease Key";
    cout << "\n5-Delete";
    cout << "\n6-Extract Minimum";
    cout << "\n7-Display Fibonacci Heap 1 (The Root List)";
    cout << "\n8-Display Fibonacci Heap 2 (All The Nodes)";
    cout << "\n9-Back";

    cout << endl;

}

struct Node
{

    int key; /// The value of the node
    int degree; /// The number of children of the node
    bool marked; /// Whether the node is marked
    Node* parent; /// The parent of the node
    Node* left; /// The left sibling of the node
    Node* right; /// The right sibling of the node
    Node* child; /// One of the node's children (if any)

    Node();
    Node(int key);

};

Node::Node()
{
    this->key = 0;
    this->degree = 0;
    this->parent = nullptr;
    this->child = nullptr;
    this->left = this;
    this->right = this;
    this->marked = false;
}

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
    /// Vector with all the nodes from the Fibonacci Heap (This was added for testing / for the interactive menu
    vector<Node*> nodes;

public:

    FibonacciHeap();

    /// Methods for testing / for the interactive menu
    int getN();
    Node* getMinNode();
    vector<Node*> getNodes();
    void setNodes(vector<Node*> newNodes);
    void setMinNode(Node* x);
    void setN(int n);
    void displayFibonacciHeap();
    void displayAllNodes();

    /// Important Methods (The operations)
    int findMin();
    Node* insert(int key); /// This was adjusted to be "Node*" instead of "void" for testing purposes / for the interactive menu
    void merge(FibonacciHeap& FH);
    void decreaseKey(Node* x, int key);
    Node* extractMin(); /// This was adjusted to be "Node*" instead of "int" for testing purposes / for the interactive menu
    void deleteNode(Node* x);


    ~FibonacciHeap() {};

};

FibonacciHeap::FibonacciHeap()
{
    this->minNode = nullptr;
    this->n = 0;
    this->nodes=vector<Node*> ();
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

Node* FibonacciHeap::insert(int key)
{
    if(key<0)
    {
        Node* node = new Node();
        return node;
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
    if (key > x->key)
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

    if(y->key<=x->key) /// The case if the decrease key does not violate the min heap property
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

            /// Cut z from his parent and move it to the root list
            this->minNode->left->right = z;
            z->left = this->minNode->left;
            this->minNode->left = z;
            z->right = this->minNode;
            z->parent=nullptr;
            z->marked=false;

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

///Currently in work
Node* FibonacciHeap::extractMin()
{
    Node* Y=this->minNode; ///keep the minNode, might be useful later
    Node* newMinNode=this->minNode->right; ///make this because this->minNode=newMinNode later
    int key=this->minNode->key;///keep the key of minNode (of the minNode we want to cut)
    int maxDegree = ceil(log2(this->n));///max possible degree
    vector<Node*>degreeNodes(maxDegree); /// The vector with max degree for later

    this->minNode->left->right=this->minNode->right; /// Link the left and right of this->minNode (because we will cut this->minNode)
    this->minNode->right->left=this->minNode->left;
    this->minNode->left=nullptr;///Make the left and right of the minNode nullptr because we already linked its siblings and we will need to remove it soon
    this->minNode->right=nullptr;

    Node* current = this->minNode->child; ///Make every child's parent pointer to nullptr

    do
    {
        current->parent=nullptr;
        current = current->right;
    }
    while (current != this->minNode->child);


    /// Get the new minimum node (right sibling of previous minNode) and the previous minNode pointer to its child and their right nodes
    Node* minNode1 = newMinNode;
    Node* minNode2 = this->minNode->child;
    Node* minNode1Right = minNode1->right;
    Node* minNode2Right = minNode2->right;

    /// Link the two root lists together (link the child's lists which contains all of previous minNode childs to the right sibling of previous minNode)
    minNode1->right = minNode2Right;
    minNode2Right->left = minNode1;
    minNode2->right = minNode1Right;
    minNode1Right->left = minNode2;

    this->minNode->child=nullptr;///we dont need this anymore since we are going to cut this->minNode
    this->minNode=newMinNode; ///update the minNode to be the previous minNode right sibling




    /// To be continued




    ///At the final, traverse the root list and find the new minimum
    current = this->minNode->right;
    while (current != this->minNode)
    {
        if (current->key < this->minNode->key)
        {
            this->minNode = current;
        }
        current = current->right;
    }

    return Y;
}

void FibonacciHeap::deleteNode(Node* x)
{
    /// Decrease the key of the node to be deleted to a very small negative value
    decreaseKey(x,-2003);
    /// Extract the minimum node (which will be the node with the decreased key)
    extractMin();
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
void FibonacciHeap::setNodes(vector<Node*> newNodes)
{
    this->nodes = newNodes;
}
void FibonacciHeap::setMinNode(Node* x)
{
    this->minNode=x;
}
void FibonacciHeap::setN(int n)
{
    this->n=n;
}

void FibonacciHeap::displayFibonacciHeap()
{
    if (this->minNode == nullptr)
    {
        cout << "The Fibonacci Heap is empty." << endl;
        return;
    }
    cout<<"The root nodes of the Fibonacci Heap are : ";
    Node* current = this->minNode;

    do
    {
        if(current->right==this->minNode)
            cout << current->key;
        else
            cout << current->key << " --> ";
        current = current->right;
    }
    while (current != this->minNode);
    cout<<endl;
    cout<<"The Fibonacci Heap has " << this->n << " nodes.";
    cout<<endl;
}

void FibonacciHeap::displayAllNodes()
{
    if(this->minNode==nullptr || this->nodes.size()==0)
    {
        cout<<"The Fibonacci Heap is empty."<<endl<<endl;
        return;
    }
    for(int i=0; i<this->nodes.size(); i++)
        cout<<i<<". "<<this->nodes[i]->key<<endl;
    cout<<endl;
}


int main()
{


/// Fibonacci Heap A

    FibonacciHeap A;

    vector <Node*> Nodes3;
    Nodes3=A.getNodes();
    Nodes3.push_back(A.insert(3));
    Nodes3.push_back(A.insert(17));
    Nodes3.push_back(A.insert(24));
    Nodes3.push_back(A.insert(23));
    Nodes3.push_back(A.insert(7));
    A.setNodes(Nodes3);

    Node* a=new Node(18);
    Node* b=new Node(52);
    Node* c=new Node(38);

    a->left->right = b;
    b->left = a->left;
    a->left = b;
    b->right = a;

    a->left->right = c;
    c->left = a->left;
    a->left = c;
    c->right = a;

    a->parent=A.getNodes()[0];
    b->parent=A.getNodes()[0];
    c->parent=A.getNodes()[0];
    a->marked=true;

    A.getNodes()[0]->child=b;
    A.getNodes()[0]->degree=3;

    Node* d=new Node(39);
    a->child=d;
    d->marked=true;
    d->parent=a;
    a->degree=1;

    Node* e=new Node(41);
    c->child=e;
    e->parent=c;
    c->degree=1;

    Node* f=new Node(30);
    f->parent=A.getNodes()[1];
    A.getNodes()[1]->child=f;
    A.getNodes()[1]->degree=1;

    Node* h=new Node(26);
    h->marked=true;
    h->parent=A.getNodes()[2];
    A.getNodes()[2]->child=h;
    A.getNodes()[2]->degree=2;
    Node* g=new Node(46);
    g->parent=A.getNodes()[2];

    h->left->right = g;
    g->left = h->left;
    h->left = g;
    g->right = h;

    Node* i=new Node(35);
    i->marked=true;

    i->parent=h;
    h->child=i;
    h->degree=1;

    vector <Node*> Nodes1;
    Nodes1=A.getNodes();
    Nodes1.push_back(a);
    Nodes1.push_back(b);
    Nodes1.push_back(c);
    Nodes1.push_back(d);
    Nodes1.push_back(e);
    Nodes1.push_back(f);
    Nodes1.push_back(h);
    Nodes1.push_back(g);
    Nodes1.push_back(i);
    A.setNodes(Nodes1);
    A.setN(14);


/// Fibonacci Heap B

    FibonacciHeap B;

    vector <Node*> Nodes4;
    Nodes4=B.getNodes();
    Nodes4.push_back(B.insert(2));
    Nodes4.push_back(B.insert(20));
    Nodes4.push_back(B.insert(5));
    Nodes4.push_back(B.insert(13));
    B.setNodes(Nodes4);

    Node* j=new Node(36);
    Node* k=new Node(50);
    j->left->right = k;
    k->left = j->left;
    j->left = k;
    k->right = j;

    j->parent=B.getNodes()[1];
    k->parent=B.getNodes()[1];
    B.getNodes()[1]->child=j;
    B.getNodes()[1]->degree=2;

    Node* l = new Node(80);
    l->parent=j;
    j->degree=1;
    j->child=l;

    vector <Node*> Nodes2;
    Nodes2=B.getNodes();
    Nodes2.push_back(j);
    Nodes2.push_back(k);
    Nodes2.push_back(l);
    B.setNodes(Nodes2);
    B.setN(7);


///Fibonacci Heap C (Another Fibonacci Heap B)

    FibonacciHeap C;

    vector <Node*> Nodes5;
    Nodes5=C.getNodes();
    Nodes5.push_back(C.insert(2));
    Nodes5.push_back(C.insert(20));
    Nodes5.push_back(C.insert(5));
    Nodes5.push_back(C.insert(13));
    C.setNodes(Nodes5);

    Node* m=new Node(36);
    Node* n=new Node(50);
    m->left->right = n;
    n->left = m->left;
    m->left = n;
    n->right = m;

    m->parent=C.getNodes()[1];
    n->parent=C.getNodes()[1];
    C.getNodes()[1]->child=m;
    C.getNodes()[1]->degree=2;

    Node* p = new Node(80);
    p->parent=m;
    m->degree=1;
    m->child=p;

    vector <Node*> Nodes6;
    Nodes6=C.getNodes();
    Nodes6.push_back(m);
    Nodes6.push_back(n);
    Nodes6.push_back(p);
    C.setNodes(Nodes6);
    C.setN(7);


/// Fibonacci Heap D (Your own Fibonacci Heap)
    FibonacciHeap D;

    int cnt1=0,cnt2=0,cnt3=0;

    while (true)
    {
        if(cnt2==0)
        {
            Menu1();
        }
        else
        {
            Menu2();
        }
        int number;
        cin >> number;

        switch (number)
        {
        case 1:
        {
            clearScreen();
            while (true)
            {
                int number2;
                Menu3();
                cin >> number2;

                switch(number2)
                {
                case 1:
                {
                    clearScreen();
                    cout<<"The key (value) of the node to be inserted : ";
                    int key;
                    cin>>key;
                    if(key>=0)
                    {
                        vector <Node*> nodes;
                        nodes=A.getNodes();
                        nodes.push_back(A.insert(key));
                        A.setNodes(nodes);
                        clearScreen();
                        cout<<"The insertion was successful!"<<endl;
                        pause(3);
                    }
                    clearScreen();
                    break;
                }
                case 2:
                {
                    clearScreen();
                    if(A.getMinNode()==nullptr)
                        A.findMin();

                    else
                    {
                        cout<<"The minimum key (value) of the Fibonacci Heap is : ";
                        cout<<A.findMin()<<endl;
                    }
                    cout<<endl;
                    cout<<"Press 'enter' to return to the menu."<<endl;
                    cin.ignore();
                    while(cin.get() != '\n');
                    clearScreen();
                    clearScreen();
                    break;
                }
                case 3:
                {
                    if(cnt1==0)
                    {
                        clearScreen();
                        cnt1++;
                        A.merge(B);

                        vector <Node*> nodes1;
                        vector <Node*> nodes2;
                        nodes1=A.getNodes();
                        nodes2=B.getNodes();
                        nodes1.insert(nodes1.end(), nodes2.begin(), nodes2.end());
                        A.setNodes(nodes1);
                        nodes2.clear();
                        B.setNodes(nodes2);

                        cout<<"Merging Fibonacci Heap A with Fibonacci Heap B was successful!"<<endl;
                        pause(5);
                        clearScreen();
                        break;
                    }
                    else
                    {
                        clearScreen();
                        break;
                    }

                }
                case 4:
                {
                    clearScreen();


                    if(A.getMinNode()==nullptr || A.getNodes().size()==0)
                    {
                        clearScreen();
                        break;
                    }
                    for(int i=0; i<A.getNodes().size(); i++)
                        cout<<i<<". "<<A.getNodes()[i]->key<<endl;
                    cout<<endl;
                    cout<<"Pick the index of the wanted node : ";
                    int nr;
                    cin>>nr;
                    cout<<endl;
                    cout<<"Pick the new key (value) of the node : ";
                    int nr2;
                    cin>>nr2;
                    A.decreaseKey(A.getNodes()[nr],nr2);
                    cout<<endl;
                    if(A.getNodes()[nr]->key==nr2)
                    {
                        cout<<"DecreaseKey was successful!"<<endl;
                        pause(3);
                    }



                    clearScreen();
                    break;
                }
                case 5:
                {
                    clearScreen();
                    if(A.getMinNode()==nullptr || A.getNodes().size()==0)
                    {
                        clearScreen();
                        break;
                    }

                    clearScreen();
                    break;
                }
                case 6:
                {
                    clearScreen();
                    if(A.getMinNode()==nullptr || A.getNodes().size()==0)
                    {
                        clearScreen();
                        break;
                    }

                    clearScreen();
                    break;
                }
                case 7:
                {
                    clearScreen();
                    A.displayFibonacciHeap();
                    cout<<endl;
                    cout<<"Press 'enter' to return to the menu."<<endl;
                    cin.ignore();
                    while(cin.get() != '\n');
                    clearScreen();
                    break;
                }
                case 8:
                {
                    clearScreen();

                    A.displayAllNodes();
                    cout<<"Press 'enter' to return to the menu."<<endl;
                    cin.ignore();
                    while(cin.get() != '\n');


                    clearScreen();
                    break;
                }
                case 9:
                {
                    clearScreen();
                    break;
                }

                default:
                {
                    clearScreen();
                    break;
                }

                }

                if(number2==9)
                {
                    clearScreen();
                    break;
                }

            }
            clearScreen();
            break;

        }

        case 2:
        {
            clearScreen();
            cnt2++;
            while (true)
            {

                int number3;
                Menu3();
                cin >> number3;

                switch(number3)
                {
                case 1:
                {
                    clearScreen();
                    cout<<"The key (value) of the node to be inserted : ";
                    int key;
                    cin>>key;
                    if(key>=0)
                    {
                        vector <Node*> nodes;
                        nodes=D.getNodes();
                        nodes.push_back(D.insert(key));
                        D.setNodes(nodes);
                        clearScreen();
                        cout<<"The insertion was successful!"<<endl;
                        pause(3);
                    }
                    clearScreen();
                    break;
                }
                case 2:
                {
                    clearScreen();
                    if(D.getMinNode()==nullptr)
                        D.findMin();

                    else
                    {
                        cout<<"The minimum key (value) of the Fibonacci Heap is : ";
                        cout<<D.findMin()<<endl;
                    }
                    cout<<endl;
                    cout<<"Press 'enter' to return to the menu."<<endl;
                    cin.ignore();
                    while(cin.get() != '\n');
                    clearScreen();
                    clearScreen();
                    break;
                }
                case 3:
                {
                    if(cnt3==0)
                    {
                        clearScreen();
                        cnt3++;
                        D.merge(C);

                        vector <Node*> nodes1;
                        vector <Node*> nodes2;
                        nodes1=D.getNodes();
                        nodes2=C.getNodes();
                        nodes1.insert(nodes1.end(), nodes2.begin(), nodes2.end());
                        D.setNodes(nodes1);
                        nodes2.clear();
                        C.setNodes(nodes2);

                        cout<<"Merging your Fibonacci Heap with Fibonacci Heap B was successful!"<<endl;
                        pause(5);
                        clearScreen();
                        break;
                    }
                    else
                    {
                        clearScreen();
                        break;
                    }

                }
                case 4:
                {
                    clearScreen();


                    if(D.getMinNode()==nullptr || D.getNodes().size()==0)
                    {
                        clearScreen();
                        break;
                    }
                    for(int i=0; i<D.getNodes().size(); i++)
                        cout<<i<<". "<<D.getNodes()[i]->key<<endl;
                    cout<<endl;
                    cout<<"Pick the index of the wanted node : ";
                    int nr;
                    cin>>nr;
                    cout<<endl;
                    cout<<"Pick the new key (value) of the node : ";
                    int nr2;
                    cin>>nr2;
                    D.decreaseKey(D.getNodes()[nr],nr2);
                    cout<<endl;
                    if(D.getNodes()[nr]->key==nr2)
                    {
                        cout<<"DecreaseKey was successful!"<<endl;
                        pause(3);
                    }



                    clearScreen();
                    break;
                }
                case 5:
                {
                    clearScreen();
                    if(D.getMinNode()==nullptr || D.getNodes().size()==0)
                    {
                        clearScreen();
                        break;
                    }

                    clearScreen();
                    break;
                }
                case 6:
                {
                    clearScreen();
                    if(D.getMinNode()==nullptr || D.getNodes().size()==0)
                    {
                        clearScreen();
                        break;
                    }

                    clearScreen();
                    break;
                }
                case 7:
                {
                    clearScreen();
                    D.displayFibonacciHeap();
                    cout<<endl;
                    cout<<"Press 'enter' to return to the menu."<<endl;
                    cin.ignore();
                    while(cin.get() != '\n');
                    clearScreen();
                    break;
                }
                case 8:
                {
                    clearScreen();

                    D.displayAllNodes();

                    cout<<"Press 'enter' to return to the menu."<<endl;
                    cin.ignore();
                    while(cin.get() != '\n');


                    clearScreen();
                    break;
                }
                case 9:
                {
                    clearScreen();
                    break;
                }

                default:
                {
                    clearScreen();
                    break;
                }

                }

                if(number3==9)
                {
                    clearScreen();
                    break;
                }

            }
            clearScreen();
            break;

        }

        case 3:
        {
            clearScreen();
            break;
        }

        default:
        {
            clearScreen();
            break;
        }

        }
        if(number==3)
        {
            clearScreen();
            break;

        }
    }


    return 0;


}
