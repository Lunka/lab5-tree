#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;

// Визначення структури вузла дерева
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Функція для вертикального обходу
vector<vector<int>> verticalTraversal(TreeNode* root) {
    // Словник для зберігання вузлів за стовпцями
    unordered_map<int, vector<pair<int, int>>> columnTable;
    // Черга для BFS
    queue<pair<TreeNode*, pair<int, int>>> bfsQueue;
    bfsQueue.push({root, {0, 0}}); // (вузол, (рядок, стовпець))

    while (!bfsQueue.empty()) {
        auto nodePair = bfsQueue.front();
        bfsQueue.pop();
        TreeNode* node = nodePair.first;
        int row = nodePair.second.first;
        int column = nodePair.second.second;

        if (node) {
            columnTable[column].emplace_back(row, node->val); // Зберігаємо рядок та значення

            bfsQueue.push({node->left, {row + 1, column - 1}});   // Лівий дочірній
            bfsQueue.push({node->right, {row + 1, column + 1}}); // Правий дочірній
        }
    }

    // Відсортовані результати
    vector<vector<int>> result;
    vector<int> columns;

    // Отримуємо всі стовпці
    for (const auto& column : columnTable) {
        columns.push_back(column.first);
    }

    // Сортуємо стовпці
    sort(columns.begin(), columns.end());

    // Вибірка значень по стовпцях
    for (int col : columns) {
        // Сортуємо вузли в даному стовпці за рядком, а потім за значенням
        sort(columnTable[col].begin(), columnTable[col].end());
        vector<int> columnValues;
        for (const auto& pair : columnTable[col]) {
            columnValues.push_back(pair.second);
        }
        result.push_back(columnValues);
    }

    return result;
}

// Функція для виведення дерева в масив (для тестування)
void printTree(TreeNode* root) {
    if (!root) {
        std::cout << "[]";
        return;
    }
    
    std::vector<int> result;
    std::vector<TreeNode*> queue;
    queue.push_back(root);
    
    while (!queue.empty()) {
        TreeNode* node = queue.front();
        queue.erase(queue.begin());
        if (node) {
            result.push_back(node->val);
            queue.push_back(node->left);
            queue.push_back(node->right);
        } else {
            result.push_back(NULL);
        }
    }

    // Видаляємо нульові елементи з кінця
    while (!result.empty() && result.back() == NULL) {
        result.pop_back();
    }

    // Виводимо результат
    std::cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        if (result[i] == NULL) {
            std::cout << "null";
        } else {
            std::cout << result[i];
        }
        if (i < result.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;
}

int main() {
    // Приклад 1
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);

    vector<vector<int>> result1 = verticalTraversal(root1);
    std::cout << "Example 1: ";
    for (const auto& column : result1) {
        std::cout << "[";
        for (size_t i = 0; i < column.size(); ++i) {
            std::cout << column[i];
            if (i < column.size() - 1) std::cout << ",";
        }
        std::cout << "] ";
    }
    std::cout << std::endl; // Output: [[9],[3,15],[20],[7]]

    // Приклад 2
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->left->left = new TreeNode(4);
    root2->left->right = new TreeNode(5);
    root2->right->left = new TreeNode(6);
    root2->right->right = new TreeNode(7);

    vector<vector<int>> result2 = verticalTraversal(root2);
    std::cout << "Example 2: ";
    for (const auto& column : result2) {
        std::cout << "[";
        for (size_t i = 0; i < column.size(); ++i) {
            std::cout << column[i];
            if (i < column.size() - 1) std::cout << ",";
        }
        std::cout << "] ";
    }
    std::cout << std::endl; // Output: [[4],[2],[1,5,6],[3],[7]]

    // Очищення пам'яті
    delete root1->right->right;
    delete root1->right->left;
    delete root1->right;
    delete root1->left;
    delete root1;

    delete root2->right->right;
    delete root2->right->left;
    delete root2->right;
    delete root2->left->right;
    delete root2->left->left;
    delete root2->left;
    delete root2;

    return 0;
}
