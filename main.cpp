#include <iostream>

// Визначення структури вузла дерева
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Функція для перевірки, чи два дерева однакові
bool isSameTree(TreeNode* p, TreeNode* q) {
    // Якщо обидва дерева порожні, вони однакові
    if (p == nullptr && q == nullptr) {
        return true;
    }
    
    // Якщо одне з дерев порожнє, а інше - ні, вони не однакові
    if (p == nullptr || q == nullptr) {
        return false;
    }
    
    // Якщо значення коренів не однакові, дерева не однакові
    if (p->val != q->val) {
        return false;
    }
    
    // Рекурсивно перевіряємо ліві та праві піддерева
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

int main() {
    // Приклад 1
    TreeNode* p1 = new TreeNode(1);
    p1->left = new TreeNode(2);
    p1->right = new TreeNode(3);
    
    TreeNode* q1 = new TreeNode(1);
    q1->left = new TreeNode(2);
    q1->right = new TreeNode(3);
    
    std::cout << std::boolalpha << isSameTree(p1, q1) << std::endl; // Output: true

    // Приклад 2
    TreeNode* p2 = new TreeNode(1);
    p2->left = new TreeNode(2);
    
    TreeNode* q2 = new TreeNode(1);
    q2->right = new TreeNode(2);
    
    std::cout << std::boolalpha << isSameTree(p2, q2) << std::endl; // Output: false

    // Приклад 3
    TreeNode* p3 = new TreeNode(1);
    p3->left = new TreeNode(2);
    p3->right = new TreeNode(1);
    
    TreeNode* q3 = new TreeNode(1);
    q3->left = new TreeNode(1);
    q3->right = new TreeNode(2);
    
    std::cout << std::boolalpha << isSameTree(p3, q3) << std::endl; // Output: false

    // Очищення пам'яті
    delete p1->left;
    delete p1->right;
    delete p1;
    delete q1->left;
    delete q1->right;
    delete q1;

    delete p2->left;
    delete p2;
    delete q2->right;
    delete q2;

    delete p3->left;
    delete p3->right;
    delete p3;
    delete q3->left;
    delete q3->right;
    delete q3;

    return 0;
}
