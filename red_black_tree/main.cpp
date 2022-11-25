#include <iostream>
#include <Windows.h>
#include <cstdio>

using namespace std;

enum treeColor
{
    BLACK,
    RED
};

struct node
{
    size_t data;
    treeColor color;
    node* left;
    node* right;
    node* parent;

    node(size_t d, treeColor c, node* p, node* l, node* r) : data(d), color(c), parent(p), left(l), right(r) {};
};

class rbtree
{
private:
    node* root;

public:
    rbtree()
    {
        this->root = nullptr;
    }

    ~rbtree()
    {
        destroy(this->root);
    }

    void destroy(node*& leaf)
    {
        if (leaf != NULL)
        {
            destroy(leaf->left);
            destroy(leaf->right);
            delete leaf;
            leaf = nullptr;
        }
    }

    void leftRotate(node*& leaf, node* x)
    {
        node* y = x->right;
        x->right = y->left;

        if (y->left != NULL)
            y->left->parent = x;

        y->parent = x->parent;
        if (x->parent == NULL)
            leaf = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rightRotate(node*& leaf, node* y)
    {
        node* x = y->left;
        y->left = x->right;
        if (x->right != NULL)
            x->right->parent = y;

        x->parent = y->parent;
        if (y->parent == NULL)
            leaf = x;
        else if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;

        x->right = y;
        y->parent = x;
    }

    void insert(size_t data)
    {
        node* z = new node(data, RED, NULL, NULL, NULL);
        insert(this->root, z);
    }

    void insert(node*& root, node* leaf)
    {
        node* x = root;
        node* y = NULL;

        while (x != NULL)
        {
            y = x;
            if (leaf->data > x->data)
                x = x->right;
            else
                x = x->left;
        }

        leaf->parent = y;
        if (y != NULL)
        {
            if (leaf->data > y->data)
                y->right = leaf;
            else
                y->left = leaf;
        }
        else
            root = leaf;
        leaf->color = RED;
        insertFixUp(root, leaf);
    }

    void insertFixUp(node*& root, node* leaf)
    {
        node* parent;
        parent = leaf->parent;
        while (leaf != this->root && parent->color == RED)
        {
            node* gparent = parent->parent;

            if (gparent->left == parent)
            {
                node* uncle = gparent->right;
                if (uncle != NULL && uncle->color == RED)
                {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    gparent->color = RED;
                    leaf = gparent;
                    parent = leaf->parent;
                }
                else
                {
                    if (parent->right == leaf)
                    {
                        leftRotate(root, parent);
                        swap(leaf, parent);
                    }
                    rightRotate(root, gparent);
                    gparent->color = RED;
                    parent->color = BLACK;
                    break;
                }
            }
            else
            {
                node* uncle = gparent->left;

                if (uncle != NULL && uncle->color == RED)
                {
                    gparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;

                    leaf = gparent;
                    parent = leaf->parent;
                }
                else
                {
                    if (parent->left == leaf)
                    {
                        rightRotate(root, parent);
                        swap(parent, leaf);
                    }
                    leftRotate(root, gparent);
                    parent->color = BLACK;
                    gparent->color = RED;
                    break;
                }
            }
        }
        root->color = BLACK;
    }

    node* search(size_t data)
    {
        return search(data, this->root);
    }

    node* search(size_t data, node* leaf) const
    {
        if (leaf == NULL || leaf->data == data)
            return leaf;
        else if (data > leaf->data)
            return search(data, leaf->left);
        else
            return search(data, leaf->right);
    }

    void remove(size_t data)
    {
        node* leaf = search(data, this->root);
        if (leaf != NULL)
            remove(root, leaf);
    }

    void remove(node*& root, node* leaf)
    {
        node* child, * parent;
        treeColor color;
        // Левый и правый узлы удаленного узла не пусты (не конечные узлы)
        if (leaf->left != NULL && leaf->right != NULL)
        {
            node* replace = leaf;
            // Найти узел-преемник (самый нижний левый узел правого поддерева текущего узла)
            replace = leaf->right;
            while (replace->left != NULL)
            {
                replace = replace->left;
            }
            // Случай, когда удаленный узел не является корневым узлом
            if (leaf->parent != NULL)
            {
                if (leaf->parent->left == leaf)
                    leaf->parent->left = replace;
                else
                    leaf->parent->right = replace;
            }
            // Ситуация с корневым узлом
            else
                root = replace;
            // child - это правильный узел, который заменяет узел и является узлом, который требует последующей корректировки
            // Поскольку замена является преемником, он не может иметь левого дочернего узла
            // Аналогично, у узла-предшественника не может быть правого дочернего узла
            child = replace->right;
            parent = replace->parent;
            color = replace->color;

            // Удаленный узел является родительским узлом замещающего узла (repalce)
            if (parent == leaf)
                parent = replace;
            else
            {
                // Существование дочернего узла
                if (child != NULL)
                    child->parent = parent;
                parent->left = child;

                replace->right = leaf->right;
                leaf->right->parent = replace;
            }
            replace->parent = leaf->parent;
            replace->color = leaf->color;
            replace->left = leaf->left;
            leaf->left->parent = replace;
            if (color == BLACK)
                removeFixUp(root, child, parent);

            delete leaf;
            return;
        }
        // Когда в удаленном узле только левый (правый) узел пуст, найдите дочерний узел удаленного узла
        if (leaf->left != NULL)
            child = leaf->left;
        else
            child = leaf->right;

        parent = leaf->parent;
        color = leaf->color;
        if (child)
        {
            child->parent = parent;
        }
        // Удаленный узел не является корневым узлом
        if (parent)
        {
            if (leaf == parent->left)
                parent->left = child;
            else
                parent->right = child;
        }
        // Удаленный узел является корневым узлом
        else
            this->root = child;

        if (color == BLACK)
        {
            removeFixUp(root, child, parent);
        }
        delete leaf;
    }

    void removeFixUp(node*& root, node* leaf, node* parent)
    {
        node* othernode;
        while ((!leaf) || leaf->color == BLACK && leaf != this->root)
        {
            if (parent->left == leaf)
            {
                othernode = parent->right;
                if (othernode->color == RED)
                {
                    othernode->color = BLACK;
                    parent->color = RED;
                    leftRotate(root, parent);
                    othernode = parent->right;
                }
                else
                {
                    if (!(othernode->right) || othernode->right->color == BLACK)
                    {
                        othernode->left->color = BLACK;
                        othernode->color = RED;
                        rightRotate(root, othernode);
                        othernode = parent->right;
                    }
                    othernode->color = parent->color;
                    parent->color = BLACK;
                    othernode->right->color = BLACK;
                    leftRotate(root, parent);
                    leaf = root;
                    break;
                }
            }
            else
            {
                othernode = parent->left;
                if (othernode->color == RED)
                {
                    othernode->color = BLACK;
                    parent->color = RED;
                    rightRotate(root, parent);
                    othernode = parent->left;
                }
                if ((!othernode->left || othernode->left->color == BLACK) && (!othernode->right || othernode->right->color == BLACK))
                {
                    othernode->color = RED;
                    leaf = parent;
                    parent = leaf->parent;
                }
                else
                {
                    if (!(othernode->left) || othernode->left->color == BLACK)
                    {
                        othernode->right->color = BLACK;
                        othernode->color = RED;
                        leftRotate(root, othernode);
                        othernode = parent->left;
                    }
                    othernode->color = parent->color;
                    parent->color = BLACK;
                    othernode->left->color = BLACK;
                    rightRotate(root, parent);
                    leaf = root;
                    break;
                }
            }
        }
        if (leaf)
            leaf->color = BLACK;
    }

    void showPreOrder()
    {
        if (this->root == NULL)
            cout << "Empty tree";
        else
            showPreOrder(this->root);
    }

    void showPreOrder(node* leaf) const
    {
        if (leaf != NULL)
        {
            cout << leaf->data << " ";
            showPreOrder(leaf->left);
            showPreOrder(leaf->right);
        }
    }

    void showInOrder()
    {
        if (this->root == NULL)
            cout << "Empty tree";
        else
            showInOrder(this->root);
    }

    void showInOrder(node* leaf) const
    {
        if (leaf != NULL)
        {
            showInOrder(leaf->left);
            cout << leaf->data << " ";
            showInOrder(leaf->right);
        }
    }

    void showPostOrder()
    {
        if (this->root == NULL)
            cout << "Empty tree";
        else
            showPostOrder(this->root);
    }

    void showPostOrder(node* leaf) const
    {
        if (leaf != NULL)
        {
            showPostOrder(leaf->left);
            showPostOrder(leaf->right);
            cout << leaf->data << " ";
        }
    }
};

int main()
{
    SetConsoleOutputCP(1251);   // Устанавливаем кодировку для windows

    rbtree tree;
    for (size_t i = 1; i <= 10; i++)
    {
        tree.insert(i);
    }

    cout << "Прямой обход" << endl;
    tree.showInOrder();
    cout << endl << "Удаляем элемент со значением 1" << endl;
    tree.remove(1);
    cout << "Прямой обход" << endl;
    tree.showInOrder();
    cout << endl;

    return 0;
}