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