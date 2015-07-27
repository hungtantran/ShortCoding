#include <time.h>
#include <queue>
#include <iostream>

#include "HelperMethod.h"

using namespace std;

void HelperMethod::printArray(const vector<int>& arr)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");
};

void HelperMethod::generateArray(vector<int>& arr, int size, int min, int max)
{
	for (int i = 0; i < size; ++i)
	{
		int val = rand() % (max - min + 1) + min;
		arr.emplace_back(val);
	}
};

Node_BinaryTree* HelperMethod::generateBinarySearchTree(bool balance, int depth)
{
    if (depth == 0)
    {
        return NULL;
    }

    Node_BinaryTree* root = new Node_BinaryTree();

    // TODO complete it

    return root;
};

Node_BinaryTree* HelperMethod::generateBinaryTree(bool balance, int depth)
{
    if (depth == 0)
    {
        return NULL;
    }

    Node_BinaryTree* root = new Node_BinaryTree();
    root->value = rand() % 100000;

    int randLeft = rand() % depth;
    if (balance)
    {
        randLeft = 1;
    }
    Node_BinaryTree* left = HelperMethod::generateBinaryTree(balance, depth - randLeft);

    int randRight = rand() % depth;
    if (balance)
    {
        randRight = 1;
    }
    Node_BinaryTree* right = HelperMethod::generateBinaryTree(balance, depth - randRight);

    root->leftNode = left;
    root->rightNode = right;

    return root;
};

void Node_BinaryTree::Print()
{
    this->level = 1;

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

        std::cout << cur->value << "(" << cur->level << ")" << "\t";

        Node_BinaryTree* left = cur->leftNode;
        if (left != NULL)
        {
            left->level = cur->level + 1;
            queue.push(left);
        }

        Node_BinaryTree* right = cur->rightNode;
        if (right != NULL)
        {
            right->level = cur->level + 1;
            queue.push(right);
        }
    }
};