#include <iostream>

// Визначення структури вузла дерева
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Допоміжна функція для перевірки симетрії
bool isMirror(TreeNode* left, TreeNode* right) {
    // Якщо обидва вузли порожні, вони симетричні
    if (left == nullptr && right == nullptr) {
        return true;
    }
    
    // Якщо один з вузлів порожній, а інший - ні, вони не симетричні
    if (left == nullptr || right == nullptr) {
        return false;
    }
    
    // Порівнюємо значення вузлів і перевіряємо симетрію лівого і правого піддерев
    return (left->val == right->val) && 
           isMirror(left->left, right->right) && 
           isMirror(left->right, right->left);
}

// Головна функція для перевірки симетрії дерева
bool isSymmetric(TreeNode* root) {
    // Дерево симетричне, якщо ліве і праве піддерева дзеркально відображають одне одного
    return isMirror(root, root);
}

int main() {
    // Приклад 1
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(2);
    root1->left->left = new TreeNode(3);
    root1->left->right = new TreeNode(4);
    root1->right->left = new TreeNode(4);
    root1->right->right = new TreeNode(3);

    std::cout << std::boolalpha << isSymmetric(root1) << std::endl; // Output: true

    // Приклад 2
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(2);
    root2->right->left = new TreeNode(3);
    
    std::cout << std::boolalpha << isSymmetric(root2) << std::endl; // Output: false

    // Приклад 3 (тут потрібно створити дерева відповідно до прикладу)
    TreeNode* root3 = new TreeNode(1);
    root3->left = new TreeNode(2);
    root3->right = new TreeNode(1);

    std::cout << std::boolalpha << isSymmetric(root3) << std::endl; // Output: false

    // Очищення пам'яті
    delete root1->left->left;
    delete root1->left->right;
    delete root1->right->left;
    delete root1->right->right;
    delete root1->left;
    delete root1->right;
    delete root1;

    delete root2->left;
    delete root2->right->left;
    delete root2->right;
    delete root2;

    delete root3->left;
    delete root3->right;
    delete root3;

    return 0;
}
