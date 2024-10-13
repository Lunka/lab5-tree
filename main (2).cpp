#include <iostream>
#include <vector>
#include <queue>

// Визначення структури вузла дерева
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Функція для інвертування дерева
TreeNode* invertTree(TreeNode* root) {
    // Якщо дерево порожнє, повертаємо NULL
    if (root == nullptr) {
        return nullptr;
    }
    
    // Інвертуємо ліве та праве піддерева
    TreeNode* left = invertTree(root->left);
    TreeNode* right = invertTree(root->right);
    
    // Обмінюємо ліве та праве піддерева
    root->left = right;
    root->right = left;

    return root; // Повертаємо корінь дерева
}

// Функція для виведення дерева в масив
void printTree(TreeNode* root) {
    if (!root) {
        std::cout << "[]";
        return;
    }
    
    std::queue<TreeNode*> q;
    std::vector<int> result;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        if (node) {
            result.push_back(node->val);
            q.push(node->left);
            q.push(node->right);
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
    TreeNode* root1 = new TreeNode(4);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(7);
    root1->left->left = new TreeNode(1);
    root1->left->right = new TreeNode(3);
    root1->right->left = new TreeNode(6);
    root1->right->right = new TreeNode(9);

    TreeNode* invertedRoot1 = invertTree(root1);
    printTree(invertedRoot1); // Output: [4,7,2,9,6,3,1]

    // Приклад 2
    TreeNode* root2 = new TreeNode(2);
    root2->left = new TreeNode(1);
    root2->right = new TreeNode(3);

    TreeNode* invertedRoot2 = invertTree(root2);
    printTree(invertedRoot2); // Output: [2,3,1]

    // Приклад 3
    TreeNode* root3 = nullptr;

    TreeNode* invertedRoot3 = invertTree(root3);
    printTree(invertedRoot3); // Output: []

    // Очищення пам'яті
    delete invertedRoot1->left->left;
    delete invertedRoot1->left->right;
    delete invertedRoot1->right->left;
    delete invertedRoot1->right->right;
    delete invertedRoot1->left;
    delete invertedRoot1->right;
    delete invertedRoot1;

    delete root2->left;
    delete root2->right;
    delete root2;

    return 0;
}
