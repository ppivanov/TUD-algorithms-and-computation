﻿#include "BinaryTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using std::vector;
using std::cout;
using std::endl;
using std::queue;

BinaryTree::BinaryTree() = default;
BinaryTree::~BinaryTree() {
	destruct_tree(root);
}

void BinaryTree::destruct_tree(TreeNode* node) {
	if (node != nullptr) {
		destruct_tree(node->left);
		destruct_tree(node->right);
		delete node;
		node = nullptr;
	}
}


bool BinaryTree::path_is_correct(vector<int> path) {
	int start = path[0];
	int path_size = path.size();
	if (path_size > 2 && root->left && path[1] == root->left->data) {								// left branch.. all elements at 1 .... n-1 should be LESS than the root
		for (size_t i = 1; i < path_size; i++)
			if (path[i] > start) return false;
	}
	if (path_size > 2 && root->right && path[1] == root->right->data) {								// right branch.. all elements at 1 .... n-1 should be GREATER than the root
		for (size_t i = 1; i < path.size(); i++)
			if (path[i] < start) return false;
	}
	return true;
}

bool BinaryTree::is_BST() {
	vector<int> paths;
	return is_BST(root, paths);
}
int BinaryTree::is_BST(TreeNode* node, vector<int> path) {
	if (node == nullptr)
		return 1;

	path.push_back(node->data);

	if (node->left == nullptr && node->right == nullptr)
	{
		return path_is_correct(path);
	}
	else
	{
		bool left_is_ok = is_BST(node->left, path);
		bool right_is_ok = is_BST(node->right, path);

		return (left_is_ok && right_is_ok);
	}
}

bool BinaryTree::is_BST_Recur() {
	int min = INT_MAX;
	int max = INT_MIN;
	bool result = is_BST_Recur(root, min, max);
	return result;
}
int BinaryTree::is_BST_Recur(TreeNode* node, int& min, int& max) {
	if (node == nullptr) return 1;
	
	int min_left_branch = min_value_unordered(node->right, min);
	int max_left_branch = max_value_unordered(node->left, max);

	if (min_left_branch > node->data && node->data > max_left_branch) return 1;
	else return 0;
}

int BinaryTree::min_value(TreeNode* node)
{
	if (node == nullptr) return INT_MAX;
	if (node->left == nullptr) return node->data;

	return min_value(node->left);
}

int BinaryTree::min_value_unordered(TreeNode* node, int& min)
{
	if (node == nullptr) return INT_MAX;

	min_value_unordered(node->left, min);
	min_value_unordered(node->right, min);

	if (node->data < min) min = node->data;
	return min;
}

int BinaryTree::max_value_unordered(TreeNode* node, int& max)
{
	if (node == nullptr) return INT_MIN;

	max_value_unordered(node->left, max);
	max_value_unordered(node->right, max);

	if (node->data > max) max = node->data;
	return max;
}

// ****************** This adds the nodes as if the tree was a BST ****************** //
// ************* Comment out the add on line 113 to switch between them ************* //
void BinaryTree::add(int toadd)
{
	if (root == nullptr) {
		root = new TreeNode(toadd);
		return;
	}
	add(toadd, root);
}
void BinaryTree::add(int toadd, TreeNode* node)
{
	if (node->data == toadd) return;

	if (toadd < node->data) {
		if (node->left == nullptr) {
			node->left = new TreeNode(toadd);
			return;
		}

		add(toadd, node->left);
	}
	else if (toadd > node->data) {
		if (node->right == nullptr) {
			node->right = new TreeNode(toadd);
			return;
		}
		add(toadd, node->right);
	}
	else return;
}

// ****************** This fn will add the nodes by keeping the tree balanced but not in order ****************** //
//void BinaryTree::add(int toadd)
//{
//	if (root == nullptr) {
//		root = new TreeNode(toadd);
//		return;
//	}
//
//	queue<TreeNode*> q;
//	q.push(root);
//
//	add(toadd, q);
//}
void BinaryTree::add(int toadd, queue<TreeNode*> queue)
{
	TreeNode* node = queue.front();
	queue.pop();
	if (node->left == nullptr) {
		node->left = new TreeNode(toadd);
		return;
	}
	else if (node->right == nullptr) {
		node->right = new TreeNode(toadd);
		return;
	}
	else {
		queue.push(node->left);
		queue.push(node->right);
		add(toadd, queue);
	}
}

// Print fn source: https://stackoverflow.com/a/51730733
void BinaryTree::pretty_print() {
	pretty_print(root);
}
void BinaryTree::pretty_print(const TreeNode* node)
{
	pretty_print("", node, false);
}
void BinaryTree::pretty_print(std::string prefix, const TreeNode* node, bool isLeft)
{
	if (node != nullptr)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "|--" : "|__");

		// print the value of the node
		std::cout << node->data << std::endl;

		// enter the next tree level - left and right branch
		pretty_print(prefix + (isLeft ? "|   " : "    "), node->left, true);
		pretty_print(prefix + (isLeft ? "|   " : "    "), node->right, false);
	}
}
