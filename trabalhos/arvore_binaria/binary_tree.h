#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include <stdexcept>
#include "array_list.h"

namespace structures {

//! Classe que implementa uma árvore binária
template<typename T>
class BinaryTree {
public:
    //! Construtor padrão da árvore binária
    BinaryTree() = default;

    //! Destrutor padrão da árvore binária
    ~BinaryTree();

    //! Insere um elemento na árvore
    void insert(const T& data);

    //! Remove um elemento da árvore
    void remove(const T& data);

    //! Verifica se a árvore contém um dado específico
    bool contains(const T& data) const;

    //! Verifica se a árvore está vazia
    bool empty() const;

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
    struct Node {
        explicit Node(const T& data) : data{data},
        left{nullptr}, right{nullptr} {}

        T data;
        Node* left;
        Node* right;

        void insert(const T& data_) {
            if (data_ < this->data) {
                if (this->left == nullptr) {
                    Node* newNode = new Node(data_);
                    newNode->left = nullptr;
                    newNode->right = nullptr;
                    this->left = newNode;
                } else {
                    this->left->insert(data_);
                }
            } else {
                if (this->right == nullptr) {
                    Node* newNode = new Node(data_);
                    newNode->left = nullptr;
                    newNode->right = nullptr;
                    this->right = newNode;
                } else {
                    this->right->insert(data_);
                }
            }
        }

        bool remove(const T& data_) {
            bool temp = false;
            if (data_ == this->data) {
                Node* novo;
                if ((this->left != nullptr) && (this->right != nullptr)) {
                    novo = this->right;
                    while (novo->left != nullptr)
                        novo = novo->left;
                    this->data = novo->data;
                    temp = right -> remove(this->data);
                } else {
                    if (this->right != nullptr) {
                        this->data = right->data;
                        temp = right -> remove(this->data);
                    } else {
                        if (this->left != nullptr) {
                        this->data = left->data;
                        temp = left->remove(this->data);
                        } else {
                            delete this;
                            temp = true;
                        }
                    }
                }
            } else {
                if ((this->left != nullptr) && (data_ < this->data)) {
                    temp = left->remove(data_);
                }
                
                if ((this->right != nullptr) && (data_ > this->data)) {
                    temp = right->remove(data_);
                }
            }

            return temp;
        }

        bool contains(const T& data_) const {
            bool temp = false;

            if (data_ == this->data) {
                temp = true;
            } else {
                if ((this->left != nullptr) && (data_ < this->data)) {
                    temp = left->contains(data_);
                } else if ((this->right != nullptr) && (data_ > this->data)) {
                    temp = right->contains(data_);
                }
            }

            return temp;
        }

        void pre_order(structures::ArrayList<T>& v) const {
            v.push_back(this->data);

            if (this->left != nullptr) {
                left->pre_order(v);
            }

            if (this->right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(structures::ArrayList<T>& v) const {
            if (this->left != nullptr) {
                left->in_order(v);
            }

            v.push_back(this->data);

            if (this->right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(structures::ArrayList<T>& v) const {
            if (this->left != nullptr) {
                left->post_order(v);
            }

            if (this->right != nullptr) {
                right->post_order(v);
            }

            v.push_back(this->data);
        }
    };

    //! Raiz da árvore, privado
    Node* root;
    //! Tamanho da árvore, privado
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    delete root;
    size_ = 0;
}

template<typename T>
void structures::BinaryTree<T>::insert(const T &data) {
    if (empty()) {
        root = new Node(data);
    } else {
        root->insert(data);
    }

    size_++;
}

template<typename T>
void structures::BinaryTree<T>::remove(const T &data) {
    if (empty())
        throw std::out_of_range("Empty tree.");

    if (contains(data)) {
        size_--;
        root -> remove(data);
    }
}

template<typename T>
bool structures::BinaryTree<T>::contains(const T &data) const {
    bool temp = false;

    if (!empty())
        temp = root->contains(data);

    return temp;
}

template<typename T>
bool structures::BinaryTree<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    structures::ArrayList<T> v{};

    if (!empty()) {
        root->pre_order(v);
    }

    return v;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    structures::ArrayList<T> v{};

    if (!empty()) {
        root->in_order(v);
    }

    return v;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    structures::ArrayList<T> v{};

    if (!empty()) {
        root->post_order(v);
    }

    return v;
}

#endif
