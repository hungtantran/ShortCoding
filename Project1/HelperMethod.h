#include <vector>

struct Node_BinaryTree
{
    int value;
    Node_BinaryTree* leftNode;
    Node_BinaryTree* rightNode;
    int level;
    int parentVal;

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

    void ToSortedArray(std::vector<int>& result);
};

class HelperMethod
{
public:
	static void printArray(const std::vector<int>& arr);

	static void generateArray(std::vector<int>& arr, int size, int min, int max);

    static Node_BinaryTree* generateBinaryTree(bool balance = false, int maxdepth = 10);

    static Node_BinaryTree* generateBinarySearchTree(std::vector<int> vals, bool balance = true);

    static Node_BinaryTree* generateBinarySearchTree(bool balance = true, int numVal = 31);

    static Node_BinaryTree* generateBinarySearchTree(bool balance, const std::vector<int>& val, int start, int end);
};