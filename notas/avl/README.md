# Árvores Semi Balanceadas

Uma forma de resolver o problema da deterioração seria reestruturar nossa árvore a cada operação que potencialmente teria mexido na estrutura, entretanto essas operações de reestruturação são complexas e custosas, por isso partimos pra uma opção mais "leve", pensando no conceito de árvores semi-balanceadas.

Uma árvore balanceada responde aos seguintes critérios:

1. Máxima diferença de altura: 1
2. Máxima diferença de número de nodos: 1

Já uma árvore semi balanceada pode afrouxar esses critérios, segundo cada algoritmo ditar.

# Árvore AVL

O nome vem dos criadores Adelson-Velsky e Landis (_AVL_) e o algoritmo consiste em relaxar o segundo critério denotado antes, mantendo apenas o primeiro critério de que a diferença máxima de altura deve ser 1. Isso barateia consideravelmente os custos de reestruturação, já que precisamos de apenas dois tipos de operações: rotação simples (maioria dos casos) e rotação dupla (minoria dos casos).

## Estrutura de um nó ná árvore AVL

```c++
class Node {
    public:
        T data;
        Node* left;
        Node* right;
        int height;
}
``` 

O campo `height` é usado para denotar a altura da subárvore gerada pelo nó atual.

## Busca da altura

```c++
int height(Node* subtree) {
    if (subtree == nullptr) {
        return -1;
    } else {
        return subtree->height;
    }
}
```

## Inclusão com rotação AVL

Após executar a inserção:

1. Partimos do nodo inserido e subimos a árvore;
2. Atualizamos a informação do balanceamento em cada nodo;
3. Se chegarmos a raiz sem encontrar nada de errado, o algoritmo acaba aqui;
4. Caso seja encontrado um nodo desbalanceado, realizamos a rotação no primeiro nodo desbalanceado encontrado.

## Rotação simples a esquerda

```c++
Node* simple_left_rotation(Node* k2) {
    Node* k1;
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max(k2->left->height(), k2->right->height()) + 1;
    k1->height = max(k1->left->height(), k2->height) + 1;

    return k1;
} 
```

## Rotação simples a direita

```c++
Node* simple_right_rotation(Node* k2) {
    Node* k1;
    k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    k2->height = max(k2->left->height(), k2->right->height()) + 1;
    k1->height = max(k1->left->height(), k2->height) + 1;

    return k1;
} 
```

## Rotação dupla a esquerda

```c++
Node* double_left_rotation(Node* k3) {
    k3->left = simple_right_rotation(k3->left);
    return (simple_left_rotation(k3));
}
```

## Rotação dupla a direita

```c++
Node* double_left_rotation(Node* k3) {
    k3->left = simple_right_rotation(k3->left);
    return (simple_left_rotation(k3));
}
```

## Inserção na árvore AVL

```c++
Node* insert(T key, Node* tree, Node* father) {
    Node* rotated;

    if (tree == nullptr) {
        tree = new Node();
        tree->info = key;
        tree->height = 0;
        tree->left = nullptr;
        tree->right = nullptr;
    } else {
        if (key < tree->info) { // inserção na esquerda
            tree->left = insert(key, tree->left, tree);
            if (tree->left->height() - tree->right->height() > 1) { // desequilibrio
                if (key < tree->left->info) {
                    rotated = simple_left_rotation(tree);
                } else {
                    rotated = double_left_rotation(tree);
                }

                if (father->left == tree) {
                    father->left = rotated;
                } else {
                    father->right = rotated;
                }
            } else { // ta equilibrado
                tree->height = max(tree->left->height(), tree->right->height()) + 1;
            }
        } else if (key > tree->info) { // inserção na direita
            tree->right = insert(key, tree->right, tree);
            if (tree->right->height() - tree->left->height() > 1) { // desequilibrio
                if (key < tree->right->info) {
                    rotated = simple_right_rotation(tree);
                } else {
                    rotated = double_right_rotation(tree);
                }

                if (father->right == tree) {
                    father->right = rotated;
                } else {
                    father->left = rotated;
                }
            } else { // ta equilibrado
                tree->height = max(tree->left->height(), tree->right->height()) + 1;
            }
        } else {
            std::throwerr("Erro: chave ja está na árvore");
        }
    }

    return tree;
}
```

## Deleção em árvore AVL

```c++
Node* remove(T key, Node subtree) {
    Node* temp, child;
    if (subtree == nullptr) {
        return subtree;
    } else {
        if (key < subtree->key) {
            subtree->left = remove(key, subtree->left);
            subtree = zigzag(subtree);
            return subtree;
        } else if (key > subtree->key) {
            subtree->right = remove(key, subtree->right);
            subtree = zigzag(subtree);
            return subtree;
        } else {
            if (subtree->left == nullptr && subtree->right == nullptr) { // 2 filhos
                temp = min(subtree->right);
                subtree->key = temp->key;
                subtree->right = remove(subtree->key, subtree->right);
                return subtree;
            } else if (subtree->left != nullptr || subtree->right != nullptr) { // 1 filho
                temp = subtree;
                if (subtree->right != nullptr) { // filho a direita
                    child = subtree->right;
                    return child;
                } else { // filho a esquerda
                    child = subtree->left;
                    return child;
                }
            } else { // nó folha
                free(subtree);
                return null;
            }
        }
    }
}
```