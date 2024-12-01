/*
 */

#include "ConsoleUtils.h"
#include <memory>

using namespace std;

const string &ROOT_PREFIX = "";
const string &BRANCH_WITH_SIBLING = "├── ";
const string &BRANCH_LAST = "└── ";
const string &VERTICAL_LINE = "│   ";
const string &SPACE = "    ";

struct TreeNode {
    int value;
    unique_ptr<TreeNode> leftChild, centerChild, rightChild;

    TreeNode(int val)
        : value(val), leftChild(nullptr), centerChild(nullptr),
          rightChild(nullptr) {}
};

void printTree(const unique_ptr<TreeNode> &node, const string &prefix = "",
               bool hasSibling = false) {
    if (!node) {
        return;
    }

    const string &connector = (hasSibling) ? BRANCH_WITH_SIBLING : BRANCH_LAST;
    const string childPrefix = prefix + (hasSibling ? VERTICAL_LINE : SPACE);

    cout << prefix << connector << node->value << endl;

    bool hasMiddleChild = (node->centerChild != nullptr);
    bool hasRightChild = (node->rightChild != nullptr);

    printTree(node->leftChild, childPrefix, hasMiddleChild);
    printTree(node->centerChild, childPrefix, hasRightChild);
    printTree(node->rightChild, childPrefix, false);
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    unique_ptr<TreeNode> root = nullptr;

    if (root == nullptr) {
        cerr << "Failed to build tree" << endl;
        return 1;
    }

    clearConsole();
    cout << "Tree:" << endl;
    printTree(root, ROOT_PREFIX);

    return 0;
}
