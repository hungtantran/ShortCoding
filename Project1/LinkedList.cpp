#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int value;
    Node* nextNode;

    Node(int value, Node* nextNode) :
        value(value), nextNode(nextNode)
    {
    }

    void Print()
    {
        printf("%d ", value);

        if (nextNode != NULL)
        {
            nextNode->Print();
        }
    }
};

void ReverseLinkedList(Node* node)
{
    if (node == NULL)
    {
        return;
    }

    Node* prev = NULL;
    Node* cur = node;
    Node* next = cur->nextNode;

    while (cur != NULL)
    {
        cur->nextNode = prev;
        prev = cur;
        cur = next;

        if (cur != NULL)
        {
            next = cur->nextNode;
        }
    }
}

Node* MergeLinkedList(Node* a, Node* b)
{
    Node* start = NULL;
    
    Node* last = NULL;
    while (true)
    {
        if (a == NULL)
        {
            if (last != NULL)
            {
                last->nextNode = b;
            }
            else
            {
                start = b;
            }

            break;
        }

        if (b == NULL)
        {
            if (last != NULL)
            {
                last->nextNode = a;
            }
            else
            {
                start = a;
            }

            break;
        }

        if (a->value > b->value)
        {
            if (last != NULL)
            {
                last->nextNode = a;
                last = a;
                a = a->nextNode;
            }
            else
            {
                last = a;
                start = a;
                a = a->nextNode;
            }
        }
        else
        {
            if (last != NULL)
            {
                last->nextNode = b;
                last = b;
                b = b->nextNode;
            }
            else
            {
                last = b;
                start = b;
                b = b->nextNode;
            }
        }
    }

    return start;
}

int main()
// int LinkedList
{

    Node a(10, NULL);
    Node b(8, &a);
    Node c(6, &b);
    Node d(4, &c);
    d.Print();
    cout << endl;

    ReverseLinkedList(&d);
    a.Print();
    cout << endl;

    Node e(9, NULL);
    Node f(7, &e);
    Node g(5, &f);
    Node h(3, &g);
    h.Print();
    cout << endl;

    ReverseLinkedList(&h);
    e.Print();
    cout << endl;

    Node* merged = MergeLinkedList(&a, &e);
    merged->Print();
    cout << endl;

    int test;
    cin >> test;

    return 0;
}