#include <iostream>

using namespace std;

struct node
{
    size_t data;
    node *left;
    node *right;
};

class btree
{
private:
    node *root;

    void cleanTree(node *leaf)
    {
        if (leaf != NULL)
        {
            cleanTree(leaf->left);
            cleanTree(leaf->right);
            delete leaf;
        }
    };

    void insert(size_t data, node *leaf)
    {
        if (data < leaf->data)
        {
            if (leaf->left != NULL)
                insert(data, leaf->left);
            else
            {
                leaf->left = new node;
                leaf->left->left = leaf->left->right = NULL;
                leaf->left->data = data;
            }
        }
        else if (data >= leaf->data)
        {
            if (leaf->right != NULL)
                insert(data, leaf->right);
            else
            {
                leaf->right = new node;
                leaf->right->left = leaf->right->right = NULL;
                leaf->right->data = data;
            }
        }
    }

    node *deleteLeaf(size_t data, node *leaf)
    {
        if (leaf == NULL)
        {
            return leaf;
        }

        if (leaf->data > data)
        {
            leaf->left = deleteLeaf(data, leaf->left);
            return leaf;
        }
        else if (leaf->data < data)
        {
            leaf->right = deleteLeaf(data, leaf->right);
            return leaf;
        }

        if (leaf->left == NULL)
        {
            node *tmp = leaf->right;
            delete leaf;
            return tmp;
        }
        else if (leaf->right == NULL)
        {
            node *tmp = leaf->left;
            delete leaf;
            return tmp;
        }
        else
        {
            node *succParent = leaf;
            node *succ = leaf->right;

            while (succ->left != NULL)
            {
                succParent = succ;
                succ = succ->left;
            }

            if (succParent != leaf)
                succParent->left = succ->right;
            else
                succParent->right = succ->right;

            leaf->data = succ->data;
            delete succ;
            return leaf;
        }
    }

public:
    btree()
    {
        this->root = NULL;
    };
    ~btree()
    {
        destroyTree();
    };

    bool isEmpty()
    {
        return (this->root == NULL);
    }

    void insert(size_t data)
    {
        if (this->root != NULL)
        {
            insert(data, this->root);
        }
        else
        {
            this->root = new node;
            this->root->left = this->root->right = NULL;
            this->root->data = data;
        }
    };

    node *search(size_t key)
    {
        return search(key, this->root);
    }

    node *search(size_t key, node *leaf)
    {
        if (leaf == NULL)
            return NULL;
        else
        {
            if (key == leaf->data)
                return leaf;
            if (key < leaf->data)
                return search(key, leaf->left);
            else
                return search(key, leaf->right);
        }
    }

    void showPreOrder()
    {
        showPreOrder(this->root);
    }

    //Прямой порядок обхода
    void showPreOrder(node *leaf)
    {
        if (leaf == NULL)
            return;

        cout << leaf->data << " ";
        showPreOrder(leaf->left);
        showPreOrder(leaf->right);
    }

    void showInOrder()
    {
        showInOrder(this->root);
    }

    //Симметричный обход
    void showInOrder(node *leaf)
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
        showPostOrder(this->root);
    }

    //Обратный обход
    void showPostOrder(node *leaf)
    {
        if (leaf != NULL)
        {
            showPostOrder(leaf->left);
            showPostOrder(leaf->right);
            cout << leaf->data << " ";
        }
    }

    size_t findMin()
    {
        return findMin(this->root);
    }

    // Return -1 if not found
    // Костыль
    size_t findMin(node *leaf)
    {
        if (leaf == NULL)
            return -1;
        else if (leaf->left == NULL)
            return leaf->data;
        else
            return findMin(leaf->left);
    }

    size_t findMax()
    {
        return findMax(this->root);
    }

    // Return -1 if not found
    // Костыль
    size_t findMax(node *leaf)
    {
        if (leaf == NULL)
            return -1;
        else if (leaf->right == NULL)
            return leaf->data;
        else
            return findMax(leaf->right);
    }

    void remove(size_t data)
    {
        deleteLeaf(data, this->root);
    }

    void destroyTree()
    {
        cleanTree(this->root);
    };
};

int main()
{
    btree *tree = new btree();

    for (size_t i = 1; i <= 10; i++)
        tree->insert(i);

    tree->showInOrder();
    tree->remove(4);
    cout << endl;
    tree->showInOrder();
    cout << endl;
    tree->showPostOrder();
    cout << endl;
    tree->showPreOrder();

    return 0;
}
