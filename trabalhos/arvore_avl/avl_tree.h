#ifndef STRUCTURES_AVL_TREE_H
#define STRUCTURES_AVL_TREE_H

#include <stdexcept>
#include "array_list.h"

namespace structures
{

    //! Classe que implementa uma árvore binária
    template <typename T>
    class AVLTree
    {
    public:
        //! Construtor padrão da árvore binária
        AVLTree() = default;

        //! Destrutor padrão da árvore binária
        ~AVLTree();

        //! Insere um elemento na árvore
        void insert(const T &data);

        //! Remove um elemento da árvore
        void remove(const T &data);

        //! Verifica se a árvore contém um dado específico
        bool contains(const T &data) const;

        //! Verifica se a árvore está vazia
        bool empty() const;

        //! Retorna a áltura da árvore
        int height() const;

        //! Retorna o tamanho da árvore
        std::size_t size() const;

        //! Transforma a árvore em uma lista utilizando o pre_order
        ArrayList<T> pre_order() const;

        //! Transforma a árvore em uma lista utilizando o in_order
        ArrayList<T> in_order() const;

        //! Transforma a árvore em uma lista utilizando o post_order
        ArrayList<T> post_order() const;

    private:
        //! Struct privada Node
        struct Node
        {
            explicit Node(const T &data) : data{data}, left{nullptr}, right{nullptr}, height_{0} {}

            T data;
            int height_;
            Node *left;
            Node *right;

            void insert(const T &data_) {
                Node *newNode;
                Node *rotate;

                if (data_ < this->data) {
                    if (this->left == nullptr) {
                        newNode = new Node(data_);
                        this->left = newNode;
                        if (height_node(this->left) - height_node(this->right) > 1) {
                            if (data < this->left->data) {
                                rotate = simple_left_rotation(this);
                            } else {
                                rotate = double_left_rotation(this);
                            }

                            if (this->left == this) {
                                this->left = rotate;
                            } else {
                                this->right = rotate;
                            }
                        } else {
                            this->update_height(max_height(this->left, this->right) + 1);
                        }
                    } else {
                        this->left->insert(data_);
                    }
                } else {
                    if (this->right == nullptr) {
                        newNode = new Node(data_);
                        this->right = newNode;
                        if ((height_node(this->right) - height_node(this->left)) > 1) {
                            if (data < this->right->data) {
                                rotate = simple_right_rotation(this);
                            } else {
                                rotate = double_right_rotation(this);
                            }

                            if (this->right == this) {
                                this->right = rotate;
                            } else {
                                this->left = rotate;
                            }
                        } else {
                            this->update_height(max_height(this->left, this->right) + 1);
                        }
                    } else {
                        this->right->insert(data_);
                    }
                }
            }

            bool remove(const T &data_) {
                Node *temp;

                if (this == nullptr) {
                    return false;
                } else {
                    if (data_ < this->data) {
                        return this->left->remove(data_);
                    } else if (data_ > this->data) {
                        return this->right->remove(data_);
                    } else {
                        if (this->right != nullptr && this->left != nullptr) { // 2 filhos
                            temp = this->right;
                            while (temp->left != nullptr)
                                temp = temp->left;

                            this->data = temp->data;
                            return this->right->remove(this->data);
                        } else {
                            temp = this;
                            if (this->right != nullptr) {
                                temp = this->right;
                                this->data = temp->data;
                                return this->right->remove(temp->data);
                            } else {
                                if (this->left != nullptr) {
                                    temp = this->left;
                                    this->data = temp->data;
                                    return this->left->remove(temp->data);
                                }
                                else {
                                    delete this;
                                    return true;
                                }
                            }
                        }
                    }
                }
            }

            bool contains(const T &data_) const
            {
                bool temp = false;

                if (data_ == this->data)
                {
                    temp = true;
                }
                else
                {
                    if ((this->left != nullptr) && (data_ < this->data))
                    {
                        temp = left->contains(data_);
                    }
                    else if ((this->right != nullptr) && (data_ > this->data))
                    {
                        temp = right->contains(data_);
                    }
                }

                return temp;
            }

            void update_height(std::size_t height_)
            {
                this->height_ = height_;
            }

            Node *simple_left_rotation(Node *node)
            {
                Node *root_new;
                root_new = node->left;
                node->left = root_new->left;
                root_new->right = node;
                node->update_height(max_height(node->left, node->right) + 1);
                root_new->update_height(max_height(root_new->left, node->right) + 1);
                return root_new;
            }

            Node *simple_right_rotation(Node *node)
            {
                Node *root_new;
                root_new = node->left;
                node->left = root_new->right;
                root_new->left = node;
                node->update_height(max_height(node->right, node->left) + 1);
                root_new->update_height(max_height(root_new->right, node) + 1);
                return root_new;
            }

            Node *double_left_rotation(Node *node_rotate)
            {
                node_rotate->left = simple_right_rotation(node_rotate->left);
                return simple_left_rotation(node_rotate);
            }

            Node *double_right_rotation(Node *node_rotate)
            {
                node_rotate->right = simple_right_rotation(node_rotate->right);
                return simple_right_rotation(node_rotate);
            }

            int height_node(Node *sub_tree) {
                if (sub_tree == nullptr) {
                    return -1;
                } else {
                    return sub_tree->height();
                }
            }

            int max_height(Node *sub_tree_a, Node *sub_tree_b)
            {
                int height_sub_a;
                int height_sub_b;

                if (sub_tree_a == nullptr)
                {
                    height_sub_a = -1;
                }
                else
                {
                    height_sub_a = sub_tree_a->height();
                }

                if (sub_tree_b == nullptr)
                {
                    height_sub_b = -1;
                }
                else
                {
                    height_sub_b = sub_tree_b->height();
                }

                if (height_sub_a > height_sub_b)
                {
                    return height_sub_a;
                }
                return height_sub_b;
            }

            void pre_order(structures::ArrayList<T> &v) const
            {
                v.push_back(this->data);

                if (this->left != nullptr)
                {
                    left->pre_order(v);
                }

                if (this->right != nullptr)
                {
                    right->pre_order(v);
                }
            }

            void in_order(structures::ArrayList<T> &v) const
            {
                if (this->left != nullptr)
                {
                    left->in_order(v);
                }

                v.push_back(this->data);

                if (this->right != nullptr)
                {
                    right->in_order(v);
                }
            }

            void post_order(structures::ArrayList<T> &v) const
            {
                if (this->left != nullptr)
                {
                    left->post_order(v);
                }

                if (this->right != nullptr)
                {
                    right->post_order(v);
                }

                v.push_back(this->data);
            }

            int height()
            {
                return this->height_;
            }
        };

        //! Raiz da árvore, privado
        Node *root;
        //! Tamanho da árvore, privado
        std::size_t size_;
    };

} // namespace structures

template <typename T>
structures::AVLTree<T>::~AVLTree()
{
    delete root;
    size_ = 0;
}

template <typename T>
void structures::AVLTree<T>::insert(const T &data)
{
    if (empty())
    {
        root = new Node(data);
    }
    else
    {
        root->insert(data);
    }

    size_++;
}

template <typename T>
void structures::AVLTree<T>::remove(const T &data)
{
    if (empty())
        throw std::out_of_range("Empty tree.");

    if (contains(data))
    {
        size_--;
        root->remove(data);
    }
}

template <typename T>
bool structures::AVLTree<T>::contains(const T &data) const
{
    bool temp = false;

    if (!empty())
        temp = root->contains(data);

    return temp;
}

template <typename T>
bool structures::AVLTree<T>::empty() const
{
    return (size_ == 0);
}

template <typename T>
int structures::AVLTree<T>::height() const
{
    return root->height();
}

template <typename T>
std::size_t structures::AVLTree<T>::size() const
{
    return size_;
}

template <typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const
{
    structures::ArrayList<T> v{};

    if (!empty())
    {
        root->pre_order(v);
    }

    return v;
}

template <typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const
{
    structures::ArrayList<T> v{};

    if (!empty())
    {
        root->in_order(v);
    }

    return v;
}

template <typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const
{
    structures::ArrayList<T> v{};

    if (!empty())
    {
        root->post_order(v);
    }

    return v;
}

#endif
