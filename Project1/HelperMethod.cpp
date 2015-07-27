#include <time.h>
#include <queue>
#include <iostream>
#include <math.h>
#include <stack>

#include "HelperMethod.h"

using namespace std;

void HelperMethod::printArray(const vector<int>& arr)
{
    for (int i = 0; i < arr.size(); ++i)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

void HelperMethod::generateArray(vector<int>& arr, int size, int min, int max)
{
	for (int i = 0; i < size; ++i)
	{
		int val = rand() % (max - min + 1) + min;
		arr.emplace_back(val);
	}
}

Node_BinaryTree* HelperMethod::generateBinarySearchTree(std::vector<int> vals, bool balance)
{
    return generateBinarySearchTree(balance, vals, 0, vals.size() - 1);
}

Node_BinaryTree* HelperMethod::generateBinarySearchTree(bool balance, const vector<int>& val, int start, int end)
{
    if (start > end)
    {
        return NULL;
    }

    int index = (start + end) / 2;
    if (!balance)
    {
        if (end > start)
        {
            index = rand() % (end - start + 1) + start;
        }
        else
        {
            index = start;
        }
    }

    Node_BinaryTree* root = new Node_BinaryTree();
    root->value = val[index];

    Node_BinaryTree* leftNode = generateBinarySearchTree(balance, val, start, index-1);
    Node_BinaryTree* rightNode = generateBinarySearchTree(balance, val, index + 1, end);
    root->leftNode = leftNode;
    root->rightNode = rightNode;

    return root;
}

Node_BinaryTree* HelperMethod::generateBinarySearchTree(bool balance, int numVal)
{
    vector<int> val;

    int lastVal = -50;
    for (int i = 0; i < numVal; ++i)
    {
        int newVal = lastVal + (rand() % 20 + 1);
        val.emplace_back(newVal);
        lastVal = newVal;
    }

    return generateBinarySearchTree(balance, val, 0, numVal - 1);
}

Node_BinaryTree* HelperMethod::generateBinaryTree(bool balance, int maxdepth)
{
    if (maxdepth == 0)
    {
        return NULL;
    }

    Node_BinaryTree* root = new Node_BinaryTree();
    root->value = rand() % 100;

    int randLeft = rand() % maxdepth + 1;
    if (balance)
    {
        randLeft = 1;
    }
    Node_BinaryTree* left = HelperMethod::generateBinaryTree(balance, maxdepth - randLeft);

    int randRight = rand() % maxdepth + 1;
    if (balance)
    {
        randRight = 1;
    }
    Node_BinaryTree* right = HelperMethod::generateBinaryTree(balance, maxdepth - randRight);

    root->leftNode = left;
    root->rightNode = right;

    return root;
}

void Node_BinaryTree::Print()
{
    this->level = 1;
    this->parentVal = 0;

    std::queue<Node_BinaryTree*> queue;
    queue.emplace(this);

    int lastLevel = 0;
    while (!queue.empty())
    {
        Node_BinaryTree* cur = queue.front();
        queue.pop();

        if (cur->level > lastLevel)
        {
            std::cout << std::endl;
            lastLevel = cur->level;
        }

        std::cout << cur->value << "(" << cur->level << ", " << cur->parentVal << ")" << "  ";

        Node_BinaryTree* left = cur->leftNode;
        if (left != NULL)
        {
            left->level = cur->level + 1;
            left->parentVal = cur->value;
            queue.push(left);
        }

        Node_BinaryTree* right = cur->rightNode;
        if (right != NULL)
        {
            right->level = cur->level + 1;
            right->parentVal = cur->value;
            queue.push(right);
        }
    }
}

void Node_BinaryTree::ToSortedArray(vector<int>& result)
{
    if (this == NULL)
    {
        return;
    }

    this->leftNode->ToSortedArray(result);
    result.emplace_back(this->value);
    this->rightNode->ToSortedArray(result);
}