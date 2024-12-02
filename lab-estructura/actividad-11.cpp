/*
 */

#include "ConsoleUtils.h"
#include <climits>
#include <memory>
#include <string>

using namespace std;

const string &ROOT_PREFIX = "";
const string &BRANCH_WITH_SIBLING = "├── ";
const string &BRANCH_LAST = "└── ";
const string &VERTICAL_LINE = "│   ";
const string &SPACE = "    ";
const string &EXIT_KEY = "q";
int MAX_LEVEL = 0;
int NEXT_FILL_LEVEL = 0;

struct TreeNode {
    int value;
    unique_ptr<TreeNode> leftChild, centerChild, rightChild;

    TreeNode(int val)
        : value(val), leftChild(nullptr), centerChild(nullptr),
          rightChild(nullptr) {}
};

bool strIsNumber(const string &str) {
    if (str.empty() || str.find_first_not_of("0123456789") != string::npos) {
        return false;
    }
    try {
        long long num = stoll(str);
        return num <= INT_MAX;
    } catch (...) {
        return false;
    }
}

void printTree(const unique_ptr<TreeNode> &node, const string &prefix = "",
               bool hasSibling = false) {
    if (node == nullptr) {
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

bool isLeaf(const unique_ptr<TreeNode> &node) {
    return node->leftChild == nullptr && node->centerChild == nullptr &&
           node->rightChild == nullptr;
}

string getLeafNodes(const unique_ptr<TreeNode> &node) {
    if (node == nullptr) {
        return "";
    }

    if (isLeaf(node)) {
        return to_string(node->value) + " ";
    }

    return getLeafNodes(node->leftChild) + getLeafNodes(node->centerChild) +
           getLeafNodes(node->rightChild);
}

int getTreeMaxLevel(const unique_ptr<TreeNode> &node) {
    if (node == nullptr) {
        return -1;
    }

    return 1 + getTreeMaxLevel(node->leftChild);
}

bool isLevelFilled(const unique_ptr<TreeNode> &node, int levelToCheck,
                   int currentLevel = 0) {
    if (currentLevel == levelToCheck) {
        return node != nullptr;
    }

    if (node == nullptr) {
        return true;
    }

    return isLevelFilled(node->leftChild, levelToCheck, currentLevel + 1) &&
           isLevelFilled(node->centerChild, levelToCheck, currentLevel + 1) &&
           isLevelFilled(node->rightChild, levelToCheck, currentLevel + 1);
}

int getTreeNextFillLevel(const unique_ptr<TreeNode> &node) {
    int treeMaxLevel = getTreeMaxLevel(node);
    int nextFillLevel =
        isLevelFilled(node, treeMaxLevel) ? treeMaxLevel + 1 : treeMaxLevel;

    return nextFillLevel;
}

bool insertNode(unique_ptr<TreeNode> &node, const int &nodeValue,
                const int &levelToFill, int currentLevel = 0) {
    if (currentLevel == levelToFill) {
        if (node == nullptr) {
            node = make_unique<TreeNode>(nodeValue);
            return true;
        }
        return false;
    }

    if (node == nullptr) {
        return false;
    }

    if (currentLevel + 1 == levelToFill) {
        if (node->leftChild == nullptr) {
            node->leftChild = make_unique<TreeNode>(nodeValue);
            return true;
        }
        if (node->centerChild == nullptr) {
            node->centerChild = make_unique<TreeNode>(nodeValue);
            return true;
        }
        if (node->rightChild == nullptr) {
            node->rightChild = make_unique<TreeNode>(nodeValue);
            return true;
        }
        return false;
    }

    return insertNode(node->leftChild, nodeValue, levelToFill,
                      currentLevel + 1) ||
           insertNode(node->centerChild, nodeValue, levelToFill,
                      currentLevel + 1) ||
           insertNode(node->rightChild, nodeValue, levelToFill,
                      currentLevel + 1);
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    bool isRunning = true;
    unique_ptr<TreeNode> root = nullptr;

    while (isRunning) {
        clearConsole();

        cout << "Árbol:" << endl;
        if (root != nullptr) {
            printTree(root, ROOT_PREFIX);
        } else {
            cout << "    [Árbol vacío]" << endl;
        }

        cout << endl;
        cout << "Información:" << endl;
        cout << "Valor de nodos sin hijos: " << endl;
        string leafNodes = getLeafNodes(root);
        if (leafNodes.empty()) {
            cout << "    [Ninguno]";
        } else {
            cout << ("    [" + leafNodes + "]") << endl;
        }

        cout << endl;
        if (nullptr != root) {
            cout << "El árbol tiene una altura de: " << MAX_LEVEL << endl;
        } else {
            cout << "El árbol no tiene altura. No está creado." << endl;
        }
        cout << "Rellenar en: " << NEXT_FILL_LEVEL << endl;

        cout << endl;
        cout << "Ingrese un valor para agregar al árbol ('" << EXIT_KEY
             << "' para salir): ";
        string user_input = promptValidInput<string>(
            "Valor Inválido. Ingrese nuevamente: ", [](const string &input) {
                return input == EXIT_KEY || strIsNumber(input);
            });

        if (user_input == EXIT_KEY) {
            isRunning = false;
        } else {
            insertNode(root, stoi(user_input), NEXT_FILL_LEVEL);
            MAX_LEVEL = getTreeMaxLevel(root);
            NEXT_FILL_LEVEL = getTreeNextFillLevel(root);
        }
    }

    return 0;
}
