/*
 */

#include "ConsoleUtils.h"
#include <climits>
#include <map>
#include <memory>
#include <string>

using namespace std;

const string &ROOT_PREFIX = "";
const string &BRANCH_WITH_SIBLING = "├── ";
const string &BRANCH_LAST = "└── ";
const string &VERTICAL_LINE = "│   ";
const string &SPACE = "    ";
const string &EXIT_KEY = "q";
const string &LEAFS_SEPARATOR = " ";
const string &LEAFS_LEVELS = "    Nivel ";
const string &LEAFS_PREFIX = ": [";
const string &LEAFS_SUFIX = "]\n";
const string &TREE_LABEL = "Árbol:";
const string &EMPTY_TREE = "    [Árbol vacío]";
const string &NONE_LEAFS = "    [Ninguno]";

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

void collectLeafNodesWithLevel(const unique_ptr<TreeNode> &node,
                               map<int, string> &levelMap, int level = 0) {
    if (node == nullptr) {
        return;
    }

    if (isLeaf(node)) {
        levelMap[level] += to_string(node->value) + LEAFS_SEPARATOR;
        return;
    }

    collectLeafNodesWithLevel(node->leftChild, levelMap, level + 1);
    collectLeafNodesWithLevel(node->centerChild, levelMap, level + 1);
    collectLeafNodesWithLevel(node->rightChild, levelMap, level + 1);
}

string getLeafNodes(const unique_ptr<TreeNode> &node) {
    if (node == nullptr) {
        return "";
    }

    map<int, string> levelMap;
    collectLeafNodesWithLevel(node, levelMap);

    string result;
    for (const auto &[level, nodes] : levelMap) {
        string nodesStr = nodes;
        if (!nodesStr.empty() && nodesStr.back() == ' ') {
            nodesStr.pop_back();
        }

        result += LEAFS_LEVELS + to_string(level) + LEAFS_PREFIX + nodesStr +
                  LEAFS_SUFIX;
    }
    return result;
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
    if (node == nullptr) {
        if (currentLevel == levelToFill) {
            node = make_unique<TreeNode>(nodeValue);
            return true;
        }

        return false;
    }

    if (insertNode(node->leftChild, nodeValue, levelToFill, currentLevel + 1)) {
        return true;
    }

    if (insertNode(node->centerChild, nodeValue, levelToFill,
                   currentLevel + 1)) {
        return true;
    }

    return insertNode(node->rightChild, nodeValue, levelToFill,
                      currentLevel + 1);
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    enableUTF8Output();

    bool isRunning = true;
    unique_ptr<TreeNode> root = nullptr;
    int max_level = getTreeMaxLevel(root);
    int next_fill_level = getTreeNextFillLevel(root);

    while (isRunning) {
        clearConsole();

        cout << TREE_LABEL << endl;
        if (root != nullptr) {
            printTree(root, ROOT_PREFIX);
        } else {
            cout << EMPTY_TREE << endl;
        }

        cout << endl;
        cout << "Información:" << endl;
        cout << "Valor de nodos sin hijos por nivel: " << endl;
        string leafNodes = getLeafNodes(root);
        if (leafNodes.empty()) {
            cout << NONE_LEAFS << endl;
        } else {
            cout << leafNodes;
        }

        if (root != nullptr) {
            cout << "El árbol tiene una altura de: " << max_level << endl;
        } else {
            cout << "El árbol no tiene altura. No está creado." << endl;
        }

        cout << endl << endl;
        cout << "Ingrese un valor para agregar al árbol ('" << EXIT_KEY
             << "' para salir): ";
        string user_input = promptValidInput<string>(
            "Valor Inválido. Ingrese nuevamente: ", [](const string &input) {
                return input == EXIT_KEY || strIsNumber(input);
            });

        if (user_input == EXIT_KEY) {
            isRunning = false;
        } else {
            insertNode(root, stoi(user_input), next_fill_level);
            max_level = getTreeMaxLevel(root);
            next_fill_level = getTreeNextFillLevel(root);
        }
    }

    return 0;
}
