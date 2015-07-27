#include <vector>

struct Node_BinaryTree
{
    int value;
    Node_BinaryTree* leftNode;
    Node_BinaryTree* rightNode;
    int level;

    Node_BinaryTree() :
        value(INT_MIN),
        leftNode(NULL),
        rightNode(NULL)
    {
    }

    Node_BinaryTree(int value, Node_BinaryTree* left, Node_BinaryTree* right) :
        value(value), leftNode(left), rightNode(right)
    {
    }

    void Print();
};

class HelperMethod
{
public:
	static void printArray(const std::vector<int>& arr);

	static void generateArray(std::vector<int>& arr, int size, int min, int max);

    static Node_BinaryTree* generateBinarySearchTree(bool balance = false, int depth = 10);

    static Node_BinaryTree* generateBinaryTree(bool balance = false, int depth = 10);
};