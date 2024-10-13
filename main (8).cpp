#include <iostream>
#include <string>
#include <stack>
#include <sstream>

using namespace std;

// Визначення структури вузла дерева
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Функція для відновлення дерева з рядка обходу
TreeNode* recoverFromPreorder(string traversal) {
    stack<TreeNode*> s; // Стек для зберігання вузлів
    int i = 0;          // Індикатор для обходу рядка

    while (i < traversal.length()) {
        int level = 0; // Глибина
        while (i < traversal.length() && traversal[i] == '-') {
            level++; // Рахуємо кількість тире
            i++;
        }

        // Отримуємо значення вузла
        int value = 0;
        while (i < traversal.length() && isdigit(traversal[i])) {
            value = value * 10 + (traversal[i] - '0'); // Формуємо число
            i++;
        }

        // Створюємо новий вузол
        TreeNode* node = new TreeNode(value);

        // Якщо стек не порожній, то потрібно додати вузол до батька
        if (level == 0) {
            // Корінь
            s.push(node);
        } else {
            // Додаємо до відповідного батьківського вузла
            while (s.size() > level) {
                s.pop(); // Повертаємось до батьківського вузла
            }
            TreeNode* parent = s.top();
            if (!parent->left) {
                parent->left = node; // Додаємо як лівого дочірнього
            } else {
                parent->right = node; // Додаємо як правого дочірнього
            }
            s.push(node); // Додаємо новий вузол до стеку
        }
    }

    // Повертаємо корінь дерева
    return s.empty() ? nullptr : s.top();
}

// Функція для виведення дерева у масив (для тестування)
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
    string traversal1 = "1-2--3--4-5--6--7";
    TreeNode* root1 = recoverFromPreorder(traversal1);
    cout << "Example 1: ";
    printTree(root1); // Output: [1,2,5,3,4,6,7]

    // Приклад 2
    string traversal2 = "1-2--3---4-5--6---7";
    TreeNode* root2 = recoverFromPreorder(traversal2);
    cout << "Example 2: ";
    printTree(root2); // Output: [1,2,5,3,null,6,null,4,null,7]

    // Приклад 3
    string traversal3 = "1-401--349---90--88";
    TreeNode* root3 = recoverFromPreorder(traversal3);
    cout << "Example 3: ";
    printTree(root3); // Output: [1,401,null,349,88,90]

    // Очищення пам'яті
    // (В цій реалізації немає деструктора для видалення вузлів, тому не забудьте додати його для справжньої програми)

    return 0;
}
