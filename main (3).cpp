#include <iostream>
#include <stack>

// Визначення структури вузла дерева
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Функція для знаходження k-го найменшого елемента у BST
int kthSmallest(TreeNode* root, int k) {
    std::stack<TreeNode*> stack;
    TreeNode* current = root;
    
    // Виконуємо обхід у порядку зростання
    while (true) {
        // Додаємо всі ліві вузли в стек
        while (current) {
            stack.push(current);
            current = current->left;
        }
        
        // Якщо стек порожній, закінчуємо
        if (stack.empty()) {
            break;
        }
        
        // Отримуємо верхній елемент зі стека
        current = stack.top();
        stack.pop();
        
        // Зменшуємо k на 1
        k--;
        
        // Якщо k досяг нуля, повертаємо значення
        if (k == 0) {
            return current->val;
        }
        
        // Переходимо до правого піддерева
        current = current->right;
    }
    
    return -1; // Це значення буде повернуто, якщо k перевищує кількість елементів у дереві
}

// Функція для виведення дерева в масив (для тестування)
void printTree(TreeNode* root) {
    if (!root) {
        std::cout << "[]";
        return;
    }
    
    std::stack<TreeNode*> stack;
    stack.push(root);
    
    std::cout << "[";
    while (!stack.empty()) {
        TreeNode* node = stack.top();
        stack.pop();
        if (node) {
            std::cout << node->val << ",";
            stack.push(node->right);
            stack.push(node->left);
        } else {
            std::cout << "null,";
        }
    }
    std::cout << "]" << std::endl;
}

int main() {
    // Приклад 1
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(1);
    root1->right = new TreeNode(4);
    root1->left->right = new TreeNode(2);

    std::cout << "Example 1: " << kthSmallest(root1, 1) << std::endl; // Output: 1

    // Приклад 2
    TreeNode* root2 = new TreeNode(5);
    root2->left = new TreeNode(3);
    root2->right = new TreeNode(6);
    root2->left->left = new TreeNode(2);
    root2->left->right = new TreeNode(4);
    root2->left->left->left = new TreeNode(1);

    std::cout << "Example 2: " << kthSmallest(root2, 3) << std::endl; // Output: 3

    // Очищення пам'яті
    delete root1->left->right;
    delete root1->left;
    delete root1->right;
    delete root1;

    delete root2->left->left->left;
    delete root2->left->left;
    delete root2->left->right;
    delete root2->left;
    delete root2->right;
    delete root2;

    return 0;
}
