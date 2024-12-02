/*
Lab de Datos 7: Introducción a Arboles

Se requiere realice un programa  que dada la definición
struct arbol{
int dato;
arbol *izq, *c1, *der;
}*rec,*raíz,*nuevo

1) Almacene una secuencia dada de números en el cual cada nodo contenga los
descendientes especificados en el registro,  si la secuencia de datos lo
permite.
2) Muestre el árbol resultante
3) Calcule la altura del árbol resultante
4) Muestre las hojas del árbol resultante

*Recuerden el uso estricto de  los apuntadores *raiz, *rec y *nuevo
 */

#include "ConsoleUtils.h"
#include <climits>
#include <map>
#include <memory>
#include <string>

using namespace std;

constexpr const char *ROOT_PREFIX = "";
constexpr const char *BRANCH_WITH_SIBLING = "├── ";
constexpr const char *BRANCH_LAST = "└── ";
constexpr const char *VERTICAL_LINE = "│   ";
constexpr const char *SPACE = "    ";
constexpr const char *EXIT_KEY = "q";
constexpr const char *LEAFS_SEPARATOR = " ";
constexpr const char *LEAFS_LEVELS = "    Nivel ";
constexpr const char *LEAFS_PREFIX = ": [";
constexpr const char *LEAFS_SUFIX = "]\n";
constexpr const char *TREE_LABEL = "Árbol:";
constexpr const char *EMPTY_TREE = "    [Árbol vacío]";
constexpr const char *NONE_LEAFS = "    [Ninguno]";

struct TreeNode {
    int value;
    unique_ptr<TreeNode> leftChild, centerChild, rightChild;

    TreeNode(int val)
        : value(val), leftChild(nullptr), centerChild(nullptr),
          rightChild(nullptr) {}
};

bool strIsValidInt(const string &str) {
    if (str.empty()) {
        return false;
    }

    for (char character : str) {
        if (!isdigit(character)) {
            return false;
        }
    }

    long long value = std::stoll(str);
    bool noOverflowed = value >= INT_MIN && value <= INT_MAX;
    return noOverflowed;
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
        cout << "- Valor de nodos sin hijos por nivel: " << endl;
        string leafNodes = getLeafNodes(root);
        if (leafNodes.empty()) {
            cout << NONE_LEAFS << endl;
        } else {
            cout << leafNodes;
        }

        cout << endl;
        if (root != nullptr) {
            cout << "- El árbol tiene una altura de: " << max_level << endl;
        } else {
            cout << "- El árbol no tiene altura. No está creado." << endl;
        }

        cout << endl << endl;
        cout << "Ingrese un entero para agregar al árbol ('" << EXIT_KEY
             << "' para salir): ";
        string user_input = promptValidInput<string>(
            "Entero Inválido. Ingrese nuevamente: ", [](const string &input) {
                return input == EXIT_KEY || strIsValidInt(input);
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
