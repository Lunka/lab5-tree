#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Визначення структури вузла дерева
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Серіалізація дерева
std::string serialize(TreeNode* root) {
    if (!root) return "null"; // Використовуємо "null" для позначення порожніх вузлів
    
    // Записуємо значення вузлів у форматі "val,leftSubtree,rightSubtree"
    return std::to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
}

// Десеріалізація дерева
TreeNode* deserialize(std::string data) {
    std::istringstream s(data);
    std::string val;
    return deserializeHelper(s);
}

TreeNode* deserializeHelper(std::istringstream& s) {
    std::string val;
    std::getline(s, val, ','); // Отримуємо наступне значення з рядка

    if (val == "null") return nullptr; // Повертаємо nullptr для порожніх вузлів
    
    TreeNode* node = new TreeNode(std::stoi(val)); // Створюємо новий вузол
    node->left = deserializeHelper(s); // Десеріалізуємо ліве піддерево
    node->right = deserializeHelper(s); // Десеріалізуємо праве піддерево

    return node; // Повертаємо створений вузол
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
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->right->left = new TreeNode(4);
    root1->right->right = new TreeNode(5);

    std::string serialized1 = serialize(root1);
    std::cout << "Serialized Example 1: " << serialized1 << std::endl; // Output: "1,2,null,null,3,4,null,null,5,null,null"

    TreeNode* deserialized1 = deserialize(serialized1);
    std::cout << "Deserialized Example 1: ";
    printTree(deserialized1); // Output: [1,2,3,null,null,4,5]

    // Приклад 2
    TreeNode* root2 = nullptr;

    std::string serialized2 = serialize(root2);
    std::cout << "Serialized Example 2: " << serialized2 << std::endl; // Output: "null"

    TreeNode* deserialized2 = deserialize(serialized2);
    std::cout << "Deserialized Example 2: ";
    printTree(deserialized2); // Output: []

    // Очищення пам'яті
    delete root1->left; // Вивільняємо пам'ять для всіх вузлів
    delete root1->right->left;
    delete root1->right->right;
    delete root1->right;
    delete root1;

    return 0;
}
