#include <iostream>
#include <algorithm>

// Визначення структури вузла дерева
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Глобальна змінна для збереження максимального значення
int maxPathSum(TreeNode* root, int& max_sum) {
    if (!root) return 0; // Якщо вузол порожній, повертаємо 0

    // Рекурсивно обчислюємо максимальні суми лівого та правого піддерев
    int left = std::max(maxPathSum(root->left, max_sum), 0); // Додаємо 0, якщо значення від'ємне
    int right = std::max(maxPathSum(root->right, max_sum), 0); // Аналогічно для правого піддерева

    // Обчислюємо максимальну суму шляху через цей вузол
    int current_sum = root->val + left + right;

    // Оновлюємо глобальну максимальну суму
    max_sum = std::max(max_sum, current_sum);

    // Повертаємо максимальну суму шляху, яка може бути використана батьківським вузлом
    return root->val + std::max(left, right);
}

// Основна функція для знаходження максимальної суми шляху
int maxPathSum(TreeNode* root) {
    int max_sum = INT_MIN; // Початкове значення
    maxPathSum(root, max_sum);
    return max_sum;
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

    std::cout << "Example 1: " << maxPathSum(root1) << std::endl; // Output: 6

    // Приклад 2
    TreeNode* root2 = new TreeNode(-10);
    root2->left = new TreeNode(9);
    root2->right = new TreeNode(20);
    root2->right->left = new TreeNode(15);
    root2->right->right = new TreeNode(7);

    std::cout << "Example 2: " << maxPathSum(root2) << std::endl; // Output: 42

    // Очищення пам'яті
    delete root1->left;
    delete root1->right;
    delete root1;

    delete root2->left;
    delete root2->right->left;
    delete root2->right->right;
    delete root2->right;
    delete root2;

    return 0;
}
