#include <time.h>
#include <queue>
#include <iostream>
#include <math.h>
#include <stack>

#include "HelperMethod.h"

using namespace std;

int HelperMethod::LeftHeap(int index) {
    return index * 2 + 1;
}

int HelperMethod::RightHeap(int index) {
    return index * 2 + 2;
}

int HelperMethod::ParentHeap(int index) {
    return (index - 1) / 2;
}

void HelperMethod::Heapify(std::vector<int>& arr) {
    Heapify(arr, 0, arr.size());
}

void HelperMethod::Heapify(std::vector<int>& arr, int index, int heapSize) {
    int left = LeftHeap(index);
    int right = RightHeap(index);

    int largest = index;
    if (left < heapSize && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < heapSize && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest == index) {
        return;
    }

    int tmp = arr[index];
    arr[index] = arr[largest];
    arr[largest] = tmp;

    Heapify(arr, largest, heapSize);
}

void HelperMethod::BuildMaxHeap(std::vector<int>& arr) {
    for (int i = arr.size() / 2; i >= 0; --i) {
        Heapify(arr, i, arr.size());
    }
}

void HelperMethod::HeapSort(std::vector<int>& arr) {
    BuildMaxHeap(arr);

    int heapSize = arr.size();
    for (int i = arr.size() - 1; i > 0; --i) {
        int tmp = arr[0];
        arr[0] = arr[heapSize - 1];
        arr[heapSize - 1] = tmp;

        --heapSize;
        Heapify(arr, 0, heapSize);
    }
}

void HelperMethod::InsertHeap(std::vector<int>& arr, int val) {
    arr.emplace_back(INT_MIN);
    IncreaseKey(arr, arr.size() - 1, val);
}

void HelperMethod::IncreaseKey(std::vector<int>& arr, int index, int newVal) {
    arr[index] = newVal;

    int parent = ParentHeap(index);
    int curIndex = index;
    while (parent >= 0) {
        if (arr[curIndex] > arr[parent]) {
            int tmp = arr[parent];
            arr[parent] = arr[curIndex];
            arr[curIndex] = arr[parent];

            curIndex = parent;
            parent = ParentHeap(curIndex);
        } else {
            break;
        }
    }
}

int HelperMethod::RemoveLargestHeap(std::vector<int>& arr) {
    int tmp = arr[0];
    arr[0] = arr[arr.size() - 1];
    arr.pop_back();

    Heapify(arr);

    return tmp;
}

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
    srand(time(NULL));

	for (int i = 0; i < size; ++i)
	{
		int val = rand() % (max - min + 1) + min;
		arr.emplace_back(val);
	}
}

void Node_BinaryTree::InsertBST(int val)
{
    if (val < this->value)
    {
        if (this->leftNode == NULL)
        {
            Node_BinaryTree* newNode = new Node_BinaryTree();
            newNode->value = val;
            this->leftNode = newNode;
        }
        else
        {
            this->leftNode->InsertBST(val);
        }
    }
    else
    {
        if (this->rightNode == NULL)
        {
            Node_BinaryTree* newNode = new Node_BinaryTree();
            newNode->value = val;
            this->rightNode = newNode;
        }
        else
        {
            this->rightNode->InsertBST(val);
        }
    }
}

Node_BinaryTree* Node_BinaryTree::MaxNode()
{
    if (this->rightNode == NULL)
    {
        return this;
    }

    return this->rightNode->MaxNode();
}

Node_BinaryTree* Node_BinaryTree::MinNode()
{
    if (this->leftNode == NULL)
    {
        return this;
    }

    return this->leftNode->MinNode();
}

Node_BinaryTree* Node_BinaryTree::DeleteBST(int val)
{
    if (val < this->value)
    {
        if (this->leftNode != NULL)
        {
            this->leftNode = this->leftNode->DeleteBST(val);
        }
    }
    else if (val > this->value)
    {
        if (this->rightNode != NULL)
        {
            this->rightNode = this->rightNode->DeleteBST(val);
        }
    }
    else
    {
        if (this->leftNode == NULL)
        {
            return this->rightNode;
        }
        else if (this->rightNode == NULL)
        {
            return this->leftNode;
        }
        else
        {
            Node_BinaryTree* nextSuccessor = this->rightNode->MaxNode();
            this->value = nextSuccessor->value;
            this->rightNode = this->rightNode->DeleteBST(this->value);
        }
    }

    return this;
}

Node_BinaryTree* Node_BinaryTree::SearchBST(int val)
{
    if (val < this->value)
    {
        return this->leftNode->SearchBST(val);
    }
    else if (val > this->value)
    {
        return this->rightNode->SearchBST(val);
    }
    else
    {
        return this;
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
};