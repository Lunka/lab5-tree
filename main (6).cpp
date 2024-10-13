#include <iostream>

// Визначення структури вузла дерева
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Глобальна змінна для зберігання кількості камер
int cameraCount = 0;

// Функція для обходу дерева та визначення розміщення камер
int minCameraCover(TreeNode* root) {
    if (!root) return 2; // Порожній вузол вважається покритим

    int left = minCameraCover(root->left);   // Стан лівого піддерева
    int right = minCameraCover(root->right); // Стан правого піддерева

    // Якщо один з дочірніх вузлів не покритий, потрібно встановити камеру на цьому вузлі
    if (left == 0 || right == 0) {
        cameraCount++;
        return 1; // Вузол має камеру
    }

    // Якщо один з дочірніх вузлів має камеру, цей вузол покритий
    if (left == 1 || right == 1) {
        return 2; // Вузол покритий, але не має камери
    }

    // Якщо обидва дочірніх вузли покриті, але без камер
    return 0; // Вузол не покритий
}

// Основна функція для отримання мінімальної кількості камер
int minCameraCover(TreeNode* root) {
    if (minCameraCover(root) == 0) { // Якщо корінь не покритий, встановлюємо камеру
        cameraCount++;
    }
    return cameraCount;
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
    TreeNode* root1 = new TreeNode(0);
    root1->left = new TreeNode(0);
    root1->left->left = new TreeNode(0);
    root1->left->right = new TreeNode(0);

    std::cout << "Example 1: " << minCameraCover(root1) << std::endl; // Output: 1

    // Приклад 2
    TreeNode* root2 = new TreeNode(0);
    root2->left = new TreeNode(0);
    root2->left->left = new TreeNode(0);
    root2->right = new TreeNode(0);
    root2->right->right = new TreeNode(0);
    root2->right->right->left = new TreeNode(0);

    std::cout << "Example 2: " << minCameraCover(root2) << std::endl; // Output: 2

    // Очищення пам'яті
    delete root1->left->left;
    delete root1->left->right;
    delete root1->left;
    delete root1;

    delete root2->left->left;
    delete root2->left;
    delete root2->right->right->left;
    delete root2->right->right;
    delete root2->right;
    delete root2;

    return 0;
}
