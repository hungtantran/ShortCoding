#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <sstream>
#include "HelperMethod.h"

using namespace std;

std::vector<int> preOrderTraversal(const Node_BinaryTree* root)
{
    std::vector<int> preOrderArr;
    std::stack<const Node_BinaryTree*> traversal;
    traversal.emplace(root);

    while (!traversal.empty())
    {
        const Node_BinaryTree* curNode = traversal.top();
        traversal.pop();

        preOrderArr.emplace_back(curNode->value);

        if (curNode->rightNode != NULL)
        {
            traversal.push(curNode->rightNode);
        }

        if (curNode->leftNode != NULL)
        {
            traversal.push(curNode->leftNode);
        }
    }

    return preOrderArr;
}

std::vector<int> inOrderTraversal(const Node_BinaryTree* root)
{
    std::vector<int> inOrderArr;
    std::stack<const Node_BinaryTree*> traversal;

    const Node_BinaryTree* cur = root;
    while (cur != NULL)
    {
        traversal.push(cur);
        cur = cur->leftNode;
    }

    while (!traversal.empty())
    {
        const Node_BinaryTree* curNode = traversal.top();
        traversal.pop();

        inOrderArr.emplace_back(curNode->value);

        cur = curNode->rightNode;
        while (cur != NULL)
        {
            traversal.push(cur);
            cur = cur->leftNode;
        }
    }

    return inOrderArr;
}

std::vector<int> postOrderTraversal(const Node_BinaryTree* root)
{
    std::vector<int> postOrderArr;

    return postOrderArr;
}

void print_all_paths_one_per_line(const Node_BinaryTree* root, std::vector<int>& path)
{
    path.emplace_back(root->value);

    if (root->leftNode != NULL)
    {
        print_all_paths_one_per_line(root->leftNode, path);
    }
    else
    {
        HelperMethod::printArray(path);
    }
    
    if (root->rightNode != NULL)
    {
        print_all_paths_one_per_line(root->rightNode, path);
    }
    else if (root->leftNode != NULL)
    {
        HelperMethod::printArray(path);
    }

    path.pop_back();
}

void print_all_paths_one_per_line(const Node_BinaryTree* root)
{
    std::vector<int> path;
    print_all_paths_one_per_line(root, path);
}

void level_order_traversal_in_spiral_form(const Node_BinaryTree* root)
{
    if (root == NULL)
    {
        return;
    }

    stack<const Node_BinaryTree*> leftToRightTraversal;
    stack<const Node_BinaryTree*> rightToLeftTraversal;
    rightToLeftTraversal.push(root);

    int leftToRight = false;

    while (true)
    {
        if (leftToRight)
        {
            if (leftToRightTraversal.empty())
            {
                break;
            }

            while (!leftToRightTraversal.empty())
            {
                const Node_BinaryTree* curNode = leftToRightTraversal.top();
                leftToRightTraversal.pop();
                cout << curNode->value << " ";

                if (curNode->leftNode != NULL)
                {
                    rightToLeftTraversal.push(curNode->leftNode);
                }

                if (curNode->rightNode != NULL)
                {
                    rightToLeftTraversal.push(curNode->rightNode);
                }
            }

            leftToRight = false;
        }
        else
        {
            if (rightToLeftTraversal.empty())
            {
                break;
            }

            while (!rightToLeftTraversal.empty())
            {
                const Node_BinaryTree* curNode = rightToLeftTraversal.top();
                rightToLeftTraversal.pop();
                cout << curNode->value << " ";

                if (curNode->rightNode != NULL)
                {
                    leftToRightTraversal.push(curNode->rightNode);
                }

                if (curNode->leftNode != NULL)
                {
                    leftToRightTraversal.push(curNode->leftNode);
                }
            }

            leftToRight = true;
        }
    }
}

int diameter_of_BT(const Node_BinaryTree* root, int& height)
{
    if (root == NULL)
    {
        height = 0;
        return 0;
    }

    int rootDiameter = 0;
    height = 0;

    int leftHeight = 0;
    int leftDiameter = diameter_of_BT(root->leftNode, leftHeight);
    if (leftHeight > height)
    {
        height = leftHeight;
    }
    if (leftDiameter > rootDiameter)
    {
        rootDiameter = leftDiameter;
    }

    int rightHeight = 0;
    int rightDiameter = diameter_of_BT(root->rightNode, rightHeight);
    if (rightHeight > height)
    {
        height = rightHeight;
    }
    if (rightDiameter > rootDiameter)
    {
        rootDiameter = rightDiameter;
    }

    height = height + 1;
    if (leftHeight + rightHeight + 1> rootDiameter)
    {
        rootDiameter = leftHeight + rightHeight + 1;
    }

    return rootDiameter;
}

int diameter_of_BT(const Node_BinaryTree* root)
{
    int height = 0;
    return diameter_of_BT(root, height);
}

bool exists_path_in_BT_with_sum_equals_given_number(const Node_BinaryTree* root, int sum)
{
    if (root == NULL)
    {
        if (sum == 0)
        {
            return true;
        }

        return false;
    }

    return exists_path_in_BT_with_sum_equals_given_number(root->leftNode, sum - root->value) ||
        exists_path_in_BT_with_sum_equals_given_number(root->rightNode, sum - root->value);
}

bool isMirror(const Node_BinaryTree* left, const Node_BinaryTree* right)
{
    if (left == NULL && right == NULL)
    {
        return true;
    }

    if (left == NULL && right != NULL)
    {
        return false;
    }

    if (left != NULL && right == NULL)
    {
        return false;
    }
    
    return isMirror(left->leftNode, right->rightNode) && isMirror(left->rightNode, right->leftNode);
}

bool foldable_BT(const Node_BinaryTree* root)
{
    if (root == NULL)
    {
        return true;
    }

    return isMirror(root->leftNode, root->rightNode);
}

void mirror_BT(Node_BinaryTree* root)
{
    if (root == NULL)
    {
        return;
    }

    Node_BinaryTree* left = root->leftNode;
    root->leftNode = root->rightNode;
    root->rightNode = left;

    mirror_BT(root->leftNode);
    mirror_BT(root->rightNode);
}

int print_level_of_given_node_BT(const Node_BinaryTree* root, int val, int level)
{
    if (root == NULL)
    {
        return -1;
    }

    if (root->value == val)
    {
        return level;
    }

    int foundLeft = print_level_of_given_node_BT(root->leftNode, val, level + 1);
    if (foundLeft != -1)
    {
        return foundLeft;
    }

    int foundRight = print_level_of_given_node_BT(root->rightNode, val, level + 1);
    return foundRight;
}

int print_level_of_given_node_BT(const Node_BinaryTree* root, int val)
{
    return print_level_of_given_node_BT(root, val, 1);
}

void print_all_ancestor(const Node_BinaryTree* root, int val, vector<int>& path)
{
    if (root == NULL)
    {
        return;
    }

    if (root->value == val)
    {
        HelperMethod::printArray(path);
    }

    path.emplace_back(root->value);
    print_all_ancestor(root->leftNode, val, path);
    print_all_ancestor(root->rightNode, val, path);
    path.pop_back();
}

void print_all_ancestor(const Node_BinaryTree* root, int val)
{
    vector<int> path;
    print_all_ancestor(root, val, path);
}

bool check_if_BT_is_sumtree(const Node_BinaryTree* root, int& sum)
{
    if (root == NULL)
    {
        sum = 0;
        return true;
    }
    
    if (root->leftNode == NULL && root->rightNode == NULL)
    {
        sum = root->value;
        return true;
    }

    int sumLeft = 0;
    bool leftSumTree = check_if_BT_is_sumtree(root->leftNode, sumLeft);
    if (!leftSumTree)
    {
        return false;
    }

    int sumRight = 0;
    bool rightSumTree = check_if_BT_is_sumtree(root->rightNode, sumRight);
    if (!rightSumTree)
    {
        return false;
    }

    sum = root->value + sumLeft + sumRight;
    return root->value == sumLeft + sumRight;
}

bool check_if_BT_is_sumtree(const Node_BinaryTree* root)
{
    int sum = 0;
    return check_if_BT_is_sumtree(root, sum);
}

void populate_inorder_successor_all_node(Node_BinaryTree* root, Node_BinaryTree*& curNode)
{
    if (root == NULL)
    {
        return;
    }

    populate_inorder_successor_all_node(root->leftNode, curNode);
    if (curNode != NULL)
    {
        curNode->nextNode = root;
    }
    curNode = root;
    populate_inorder_successor_all_node(root->rightNode, curNode);

    return;
}

void populate_inorder_successor_all_node(Node_BinaryTree* root)
{
    Node_BinaryTree* curNode = NULL;
    populate_inorder_successor_all_node(root, curNode);
}

// int main()
int iterative_traversal_BT()
{
    Node_BinaryTree* n1 = new Node_BinaryTree();
    Node_BinaryTree* n2 = new Node_BinaryTree();
    Node_BinaryTree* n3 = new Node_BinaryTree();
    Node_BinaryTree* n4 = new Node_BinaryTree();
    Node_BinaryTree* n5 = new Node_BinaryTree();
    Node_BinaryTree* n6 = new Node_BinaryTree();
    Node_BinaryTree* n7 = new Node_BinaryTree();

    n1->value = 50;
    n2->value = 30;
    n3->value = 70;
    n4->value = 20;
    n5->value = 40;
    n6->value = 60;
    n7->value = 80;

    n1->leftNode = n2;
    n1->rightNode = n3;

    n2->leftNode = n4;
    n2->rightNode = n5;

    n3->leftNode = n6;
    n3->rightNode = n7;

    n1->Print();
    cout << endl << endl;

    std::vector<int> preOrderTraversalArr = preOrderTraversal(n1);
    HelperMethod::printArray(preOrderTraversalArr);
    cout << endl << endl;

    std::vector<int> inOrderTraversalArr = inOrderTraversal(n1);
    HelperMethod::printArray(inOrderTraversalArr);
    cout << endl << endl;

    std::vector<int> postOrderTraversalArr = postOrderTraversal(n1);
    HelperMethod::printArray(postOrderTraversalArr);
    cout << endl << endl;

    int test;
    cin >> test;

    return 0;
}

// int main()
int print_all_paths_one_per_line()
{
    Node_BinaryTree* n1 = new Node_BinaryTree();
    Node_BinaryTree* n2 = new Node_BinaryTree();
    Node_BinaryTree* n3 = new Node_BinaryTree();
    Node_BinaryTree* n4 = new Node_BinaryTree();
    Node_BinaryTree* n5 = new Node_BinaryTree();
    Node_BinaryTree* n6 = new Node_BinaryTree();
    Node_BinaryTree* n7 = new Node_BinaryTree();

    n1->value = 50;
    n2->value = 30;
    n3->value = 70;
    n4->value = 20;
    n5->value = 40;
    n6->value = 60;
    n7->value = 80;

    n1->leftNode = n2;
    n1->rightNode = n3;

    n2->leftNode = n4;
    n2->rightNode = n5;

    n3->leftNode = n6;
    n3->rightNode = n7;

    n1->Print();
    cout << endl << endl;

    print_all_paths_one_per_line(n1);

    int test;
    cin >> test;

    return 0;
}

// int main()
int level_order_traversal_in_spiral_form()
{
    Node_BinaryTree* n1 = new Node_BinaryTree();
    Node_BinaryTree* n2 = new Node_BinaryTree();
    Node_BinaryTree* n3 = new Node_BinaryTree();
    Node_BinaryTree* n4 = new Node_BinaryTree();
    Node_BinaryTree* n5 = new Node_BinaryTree();
    Node_BinaryTree* n6 = new Node_BinaryTree();
    Node_BinaryTree* n7 = new Node_BinaryTree();

    n1->value = 1;
    n2->value = 2;
    n3->value = 3;
    n4->value = 7;
    n5->value = 6;
    n6->value = 5;
    n7->value = 4;

    n1->leftNode = n2;
    n1->rightNode = n3;

    n2->leftNode = n4;
    n2->rightNode = n5;

    n3->leftNode = n6;
    n3->rightNode = n7;

    n1->Print();
    cout << endl << endl;

    level_order_traversal_in_spiral_form(n1);

    int test;
    cin >> test;

    return 0;
}

// int main()
int diameter_of_BT()
{
    Node_BinaryTree* n1 = new Node_BinaryTree();
    Node_BinaryTree* n2 = new Node_BinaryTree();
    Node_BinaryTree* n3 = new Node_BinaryTree();
    Node_BinaryTree* n4 = new Node_BinaryTree();
    Node_BinaryTree* n5 = new Node_BinaryTree();

    n1->value = 1;
    n2->value = 2;
    n3->value = 3;
    n4->value = 4;
    n5->value = 5;

    n1->leftNode = n2;
    n1->rightNode = n3;

    n2->leftNode = n4;
    n2->rightNode = n5;

    n1->Print();
    cout << endl << endl;

    cout << diameter_of_BT(n1) << endl;

    int test;
    cin >> test;

    return 0;
}

// int main()
int exists_path_in_BT_with_sum_equals_given_number()
{
    Node_BinaryTree* n1 = new Node_BinaryTree();
    Node_BinaryTree* n2 = new Node_BinaryTree();
    Node_BinaryTree* n3 = new Node_BinaryTree();
    Node_BinaryTree* n4 = new Node_BinaryTree();
    Node_BinaryTree* n5 = new Node_BinaryTree();

    n1->value = 1;
    n2->value = 2;
    n3->value = 3;
    n4->value = 4;
    n5->value = 5;

    n1->leftNode = n2;
    n1->rightNode = n3;

    n2->leftNode = n4;
    n2->rightNode = n5;

    n1->Print();
    cout << endl << endl;

    cout << exists_path_in_BT_with_sum_equals_given_number(n1, 7) << endl;
    cout << exists_path_in_BT_with_sum_equals_given_number(n1, 8) << endl;
    cout << exists_path_in_BT_with_sum_equals_given_number(n1, 4) << endl;
    cout << exists_path_in_BT_with_sum_equals_given_number(n1, 3) << endl;
    cout << exists_path_in_BT_with_sum_equals_given_number(n1, 9) << endl;

    int test;
    cin >> test;

    return 0;
}

// int main()
int foldable_BT()
{
    Node_BinaryTree* n1 = new Node_BinaryTree();
    Node_BinaryTree* n2 = new Node_BinaryTree();
    Node_BinaryTree* n3 = new Node_BinaryTree();
    Node_BinaryTree* n4 = new Node_BinaryTree();
    Node_BinaryTree* n5 = new Node_BinaryTree();

    n1->value = 1;
    n2->value = 2;
    n3->value = 3;
    n4->value = 4;
    n5->value = 5;

    n1->leftNode = n2;
    n1->rightNode = n3;

    n2->rightNode = n4;

    n3->leftNode = n5;

    n1->Print();
    cout << endl << endl;

    cout << foldable_BT(n1) << endl;
    cout << endl;

    Node_BinaryTree* n6 = new Node_BinaryTree();
    Node_BinaryTree* n7 = new Node_BinaryTree();
    Node_BinaryTree* n8 = new Node_BinaryTree();
    Node_BinaryTree* n9 = new Node_BinaryTree();
    Node_BinaryTree* n10 = new Node_BinaryTree();

    n6->value = 1;
    n7->value = 2;
    n8->value = 3;
    n9->value = 4;
    n10->value = 5;

    n6->leftNode = n7;
    n6->rightNode = n8;

    n7->leftNode = n9;

    n8->leftNode = n10;

    n6->Print();
    cout << endl << endl;

    cout << foldable_BT(n6) << endl;

    int test;
    cin >> test;

    return 0;
}

// int main()
int mirror_BT()
{
    Node_BinaryTree* n1 = new Node_BinaryTree();
    Node_BinaryTree* n2 = new Node_BinaryTree();
    Node_BinaryTree* n3 = new Node_BinaryTree();
    Node_BinaryTree* n4 = new Node_BinaryTree();
    Node_BinaryTree* n5 = new Node_BinaryTree();
    Node_BinaryTree* n6 = new Node_BinaryTree();
    Node_BinaryTree* n7 = new Node_BinaryTree();

    n1->value = 50;
    n2->value = 30;
    n3->value = 70;
    n4->value = 20;
    n5->value = 40;
    n6->value = 60;
    n7->value = 80;

    n1->leftNode = n2;
    n1->rightNode = n3;

    n2->leftNode = n4;
    n2->rightNode = n5;

    n3->leftNode = n6;
    n3->rightNode = n7;

    n1->Print();
    cout << endl << endl;

    mirror_BT(n1);
    n1->Print();
    cout << endl << endl;

    int test;
    cin >> test;

    return 0;
}

// int main()
int print_level_of_given_node_BT()
{
    Node_BinaryTree* n1 = new Node_BinaryTree();
    Node_BinaryTree* n2 = new Node_BinaryTree();
    Node_BinaryTree* n3 = new Node_BinaryTree();
    Node_BinaryTree* n4 = new Node_BinaryTree();
    Node_BinaryTree* n5 = new Node_BinaryTree();
    Node_BinaryTree* n6 = new Node_BinaryTree();
    Node_BinaryTree* n7 = new Node_BinaryTree();

    n1->value = 50;
    n2->value = 30;
    n3->value = 70;
    n4->value = 20;
    n5->value = 40;
    n6->value = 60;
    n7->value = 80;

    n1->leftNode = n2;
    n1->rightNode = n3;

    n2->leftNode = n4;
    n2->rightNode = n5;

    n3->leftNode = n6;
    n3->rightNode = n7;

    n1->Print();
    cout << endl << endl;

    cout << print_level_of_given_node_BT(n1, 50) << endl;
    cout << print_level_of_given_node_BT(n1, 30) << endl;
    cout << print_level_of_given_node_BT(n1, 70) << endl;
    cout << print_level_of_given_node_BT(n1, 20) << endl;
    cout << print_level_of_given_node_BT(n1, 40) << endl;
    cout << print_level_of_given_node_BT(n1, 60) << endl;
    cout << print_level_of_given_node_BT(n1, 80) << endl;
    cout << print_level_of_given_node_BT(n1, 100) << endl;

    int test;
    cin >> test;

    return 0;
}

// int main()
int print_all_ancestor()
{
    Node_BinaryTree* n1 = new Node_BinaryTree();
    Node_BinaryTree* n2 = new Node_BinaryTree();
    Node_BinaryTree* n3 = new Node_BinaryTree();
    Node_BinaryTree* n4 = new Node_BinaryTree();
    Node_BinaryTree* n5 = new Node_BinaryTree();
    Node_BinaryTree* n6 = new Node_BinaryTree();
    Node_BinaryTree* n7 = new Node_BinaryTree();
    Node_BinaryTree* n8 = new Node_BinaryTree();

    n1->value = 50;
    n2->value = 30;
    n3->value = 70;
    n4->value = 20;
    n5->value = 40;
    n6->value = 60;
    n7->value = 80;
    n8->value = 30;

    n1->leftNode = n2;
    n1->rightNode = n3;

    n2->leftNode = n4;
    n2->rightNode = n5;

    n3->leftNode = n6;
    n3->rightNode = n7;

    n6->leftNode = n8;

    n1->Print();
    cout << endl << endl;

    print_all_ancestor(n1, 50);
    cout << endl;

    print_all_ancestor(n1, 30);
    cout << endl;

    print_all_ancestor(n1, 70);
    cout << endl;

    print_all_ancestor(n1, 20);
    cout << endl;

    print_all_ancestor(n1, 40);
    cout << endl;

    print_all_ancestor(n1, 60);
    cout << endl;

    print_all_ancestor(n1, 80);
    cout << endl;

    print_all_ancestor(n1, 100);
    cout << endl;

    int test;
    cin >> test;

    return 0;
}

// int main()
int check_if_BT_is_sumtree()
{
    Node_BinaryTree* n1 = new Node_BinaryTree();
    Node_BinaryTree* n2 = new Node_BinaryTree();
    Node_BinaryTree* n3 = new Node_BinaryTree();
    Node_BinaryTree* n4 = new Node_BinaryTree();
    Node_BinaryTree* n5 = new Node_BinaryTree();
    Node_BinaryTree* n6 = new Node_BinaryTree();

    n1->value = 26;
    n2->value = 10;
    n3->value = 3;
    n4->value = 4;
    n5->value = 6;
    n6->value = 3;

    n1->leftNode = n2;
    n1->rightNode = n3;

    n2->leftNode = n4;
    n2->rightNode = n5;

    n3->leftNode = n6;

    n1->Print();
    cout << endl << endl;

    // True
    cout << check_if_BT_is_sumtree(n1) << endl;
    cout << endl;

    // False
    Node_BinaryTree* n7 = new Node_BinaryTree();
    n7->value = 10;
    n3->rightNode = n7;

    cout << check_if_BT_is_sumtree(n1) << endl;
    cout << endl;

    // True
    n7->value = 0;
    cout << check_if_BT_is_sumtree(n1) << endl;
    cout << endl;

    int test;
    cin >> test;

    return 0;
}

// int main()
int populate_inorder_successor_all_node()
{
    Node_BinaryTree* n1 = new Node_BinaryTree();
    Node_BinaryTree* n2 = new Node_BinaryTree();
    Node_BinaryTree* n3 = new Node_BinaryTree();
    Node_BinaryTree* n4 = new Node_BinaryTree();
    Node_BinaryTree* n5 = new Node_BinaryTree();
    Node_BinaryTree* n6 = new Node_BinaryTree();
    Node_BinaryTree* n7 = new Node_BinaryTree();

    n1->value = 50;
    n2->value = 30;
    n3->value = 70;
    n4->value = 20;
    n5->value = 40;
    n6->value = 60;
    n7->value = 80;

    n1->leftNode = n2;
    n1->rightNode = n3;

    n2->leftNode = n4;
    n2->rightNode = n5;

    n3->leftNode = n6;
    n3->rightNode = n7;

    n1->Print();
    cout << endl << endl;

    populate_inorder_successor_all_node(n1);
    n1->Print();
    cout << endl << endl;

    int test;
    cin >> test;

    return 0;
}