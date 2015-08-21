//https://www.interviewcake.com/question/bst-checker
//http://www.geeksforgeeks.org/amazon-interview-experience-196-on-campus/

#include <iostream>
#include <time.h>
#include <sstream>
#include <functional>
#include <vector>
#include <stack>
#include "HelperMethod.h"

using namespace std;

bool BinarySearchTreeRecursive(Node_BinaryTree* node, int value, std::function<bool(int, int)> func)
{
    if (node == NULL)
    {
        return true;
    }

    if (!func(value, node->value))
    {
        return false;
    }

    return BinarySearchTreeRecursive(node->leftNode, node->value, std::greater_equal<int>()) &&
        BinarySearchTreeRecursive(node->rightNode, node->value, std::less_equal<int>());
}

bool BinarySearchTree(Node_BinaryTree* node)
{
    return BinarySearchTreeRecursive(node, node->value + 1, std::greater_equal<int>());
}

Node_BinaryTree* MergeBst(Node_BinaryTree* bst1, Node_BinaryTree* bst2)
{
    vector<int> bst1Val, bst2Val;
    bst1->ToSortedArray(bst1Val);
    bst2->ToSortedArray(bst2Val);

    vector<int> allVals;
    int index1 = 0, index2 = 0;
    while (true)
    {
        if (index1 >= bst1Val.size() && index2 >= bst2Val.size())
        {
            break;
        }

        int val1 = INT_MAX;
        if (index1 < bst1Val.size())
        {
            val1 = bst1Val[index1];
        }

        int val2 = INT_MAX;
        if (index2 < bst2Val.size())
        {
            val2 = bst2Val[index2];
        }

        if (val1 >= val2)
        {
            allVals.emplace_back(val2);
            ++index2;
        }
        else
        {
            allVals.emplace_back(val1);
            ++index1;
        }
    }

    return HelperMethod::generateBinarySearchTree(allVals, true);
}

Node_BinaryTree* InorderSucc(Node_BinaryTree* bst, int val, Node_BinaryTree* mostRecentSucc)
{
    if (bst->value > val)
    {
        if (mostRecentSucc == NULL || bst->value < mostRecentSucc->value)
        {
            mostRecentSucc = bst;
        }

        return InorderSucc(bst->leftNode, val, mostRecentSucc);
    }
    else if (bst->value < val)
    {
        return InorderSucc(bst->rightNode, val, mostRecentSucc);
    }
    else
    {
        if (bst->rightNode != NULL)
        {
            return bst->rightNode->MinNode();
        }
        else
        {
            return mostRecentSucc;
        }
    }
}

// int main()
int BinarySearchTree_Checker()
{
    srand(time(NULL));
    Node_BinaryTree* bt = HelperMethod::generateBinaryTree(true, 4);
    bt->Print();
    cout << endl;
    cout << "BST result = " << BinarySearchTree(bt) << endl;
    cout << endl;
    cout << endl;

    Node_BinaryTree* bst = HelperMethod::generateBinarySearchTree(true, 7);
    bst->Print();
    cout << endl;
    cout << "BST result = " << BinarySearchTree(bst) << endl;
    cout << endl;
    cout << endl;

    Node_BinaryTree* bst2 = HelperMethod::generateBinarySearchTree(true, 3);
    bst2->Print();
    cout << endl;
    cout << "BST result = " << BinarySearchTree(bst2) << endl;

    Node_BinaryTree* mergedBst = MergeBst(bst, bst2);
    mergedBst->Print();
    cout << endl;
    cout << "BST result = " << BinarySearchTree(mergedBst) << endl;

    int test;
    cin >> test;

    return 0;
}

// int main()
int Test_InsertSearchDeletePrintBST()
{
    srand(time(NULL));
    Node_BinaryTree* bst = HelperMethod::generateBinarySearchTree(true, 7);
    bst->Print();
    cout << endl;

    bst->InsertBST(20);
    bst->Print();
    cout << endl;

    bst->InsertBST(10);
    bst->Print();
    cout << endl;

    bst->InsertBST(30);
    bst->Print();
    cout << endl;

    bst->InsertBST(-30);
    bst->Print();
    cout << endl;

    bst->InsertBST(-40);
    bst->Print();
    cout << endl;

    Node_BinaryTree* bst2 = bst->SearchBST(20);
    bst2->Print();
    cout << endl;

    bst->DeleteBST(20);
    bst->Print();
    cout << endl;

    bst->DeleteBST(-30);
    bst->Print();
    cout << endl;

    int test;
    cin >> test;

    return 0;
}

int main()
// int Inorder_Succ()
{
    Node_BinaryTree* bst = new Node_BinaryTree();
    bst->value = 50;
    bst->InsertBST(10);
    bst->InsertBST(30);
    bst->InsertBST(40);
    bst->InsertBST(20);
    bst->InsertBST(55);
    bst->InsertBST(17);
    bst->InsertBST(19);
    bst->InsertBST(23);

    cout << InorderSucc(bst, 20, NULL)->value << endl;
    cout << InorderSucc(bst, 30, NULL)->value << endl;
    cout << InorderSucc(bst, 19, NULL)->value << endl;
    cout << InorderSucc(bst, 50, NULL)->value << endl;
    if (InorderSucc(bst, 55, NULL) == NULL)
    {
        cout << "55 has no successor" << endl;
    }

    int test;
    cin >> test;

    return 0;
}