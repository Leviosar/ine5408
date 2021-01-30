# Introdução a árvores

As árvores são estruturas de dados que possuem uma organização hierárquia entre os seus elementos internos. Esse tipo de estrutura permite que se separe a estrutura em grupos menores, achando um caminho mais curto para procurar por um certo dado.

Formalmente, uma árvore é um conjunto finitio de um ou mais nós/vértices, tais que:

- Existe um nó chamado `raiz da árvore`
- Os demais nós formam n conjuntos disjuntos, sendo que cada um desses conjuntos também é uma árvore (denominada subárvore).

## Representações de árvores

Podemos representar uma árvore de diversas maneiras para facilitar a visualização e entendimento.

1. Representação por diagrama hierárquico
2. Representação por diagrama de Euler-Venn (teoria dos conjuntos)
3. Representação por expressão parentetizada (utilizando parênteses aninhados)
4. Representação por expressão não parentetizada

As expressões 1 e 2 ajudam na visualização humana, entretando as duas últimas expressões são muito mais fáceis de persistir em um banco de dados ou em memória para reconstrui-la depois.

## Definições

1. Aresta
    - Uma aresta é uma linha que liga dois nós da árvore
2. Caminho
    - Existe um **caminho** entre dois nós A e B da árvore, se a partir do nó A eu conseguir seguir arestas que me levem até o nó B.
    - Existe um caminho entre a raiz e QUALQUER nó da árvore (do contrário não seria uma árvore).
3. Nó ancestral
    - Se houver um caminho entre A e B e esse caminho começa por A, dizemos que A é um nó ancestral de B.
    - Se esse mesmo caminho só tiver uma aresta, dizemos que A é o nó pai de B.
    - Exceto pela raiz, todo nó possui um pai.
4. Nó descendente
    - Se houver um caminho entre A e B e esse caminho começa por B, dizemos que A é um nó descendente de B.
    - Se esse mesmo caminho só tiver uma aresta, dizemos que A é um nó filho de B
5. Nós irmãos
    - Dois nós que são filhos do mesmo pai, são chamados de irmão.
6. Nó folha
    - Se um nó não possui filhos, chamamos ele de nó folha ou nó terminal.
7. Grau do nó
    - O grau de um nó é igual ao número de filhos que ele possui
8. Nível do nó
    - A raiz tem nível 0, seus filhos nível 1, são netos nívl 2 e assim sucessivamente.
9. Grau da árvore
    - É igual ao maior grau entre os nós dentro da árvore
10. Nível da árvore
    - É igual ao maior nível entre os nós dentro da árvore.

# Árvore binária

Incluir limitações de forma nos gera tipos específicos de árvores, um deles é a árvore binária, onde o grau máximo de cada nó é 2. Dessa for, um nó pode ter 0, 1 ou 2 filhos. 

A partir dessa definição, podemos dizer que se um nó possui dois filhos, ele irá ter o filho da esquerda, que gera a subárvore da esquerda e o filho da direita que gera a subárvore da direita

> Árvore binária completa: um nó ou tem 2 filhos ou 0.

### Transformação: árvore n-ária para binária

É possível transformar uma árvore n-ária em binária com o seguinte algoritmo:

1. A raiz da árvore será a raiz da nova subárvore binária.

2. O nó filho mais a esquerda da raiza da árvore será o nó filho à esquerda da raiz da árvore binária.

3. Cada nó irmão de A, da esquerda para a direita será o nó filho à direita do nó irmão da esquerda, até que todos os nós filhos da raiza da árvore já tinham sido incluídos na árvore binária em construção.

Esse algoritmo é aplicado na árvore de forma recursiva.

### Modelagem de uma árvore binária em C++

Cada nó vai precisar guardar as seguintes informações:

- Um ponteiro para o filho localizado à esquerda
- Um ponteiro para o filho localizado à direita
- Um ponteiro para a informação que queremos armazenar

Uma assinatura possível para a nossa classe é algo como:

```c++
template typename<T>
class Node<T> {
    public:
        Node<T>* left;
        Node<T>* right;
        T* data;
}
```

> Caso left e right sejam um nullptr, sabemos que chegamos a um nó folha

### Construção de uma árvore binária

Só faz sentido construir uma árvore a partir de informações que sejam possíveis de ser ordenados de forma hierárquia, como por exemplo uma classe que possua um identificador númerico inteiro. De prefência a árvore criada deve possuir a menor altura possível, facilitando os caminhos de busca dentro dela, então devemos preencher cada nível o máximo antes de ir ao próximo.

1. Use um nó para a raiz
2. Gere a subárvore esquerda com nósAEsquerda = númeroDeNós / 2
3. Gere a subárvore direita com nósADireita = númeroDeNós - nósAEsquerda -1 

```c++
Node* buildTree(int n) {
    int left, right;
    T* info;
    Node* newNode;

    if (n = 0) {
        return NULL;
    }

    left = n / 2;
    right = n - left - 1;

    newNode->info = info;
    newNode->left = buildTree(left);
    newNode->right = buildTree(right);

    return newNode;
}
```

### Percurso em árvores binárias

O percurso em árvores binárias corresponde ao caminho execuado em listas:
    - Partimos de um nó inicial (raiz) e visitamos todos os demais nós em uma ordem previamente especificada

Para exemplificar, pense numa árvore binária utilizada para representar uma expressão, com as seguintes restrições:
    - Cada operador representa uma bifurcação
    - Seus dois operandos correspondentes são representados por suas subárvores

Existem 3 ordens para se percorrer uma árvore na sua estrutura natural:

1. Preorder(r, e, d)
    - Primeiro percorremos a raiz, depois a esquerda e por último a direita
2. Inorder(e, r, d)
    - Primeiro percorremos a esquerda, depois a raiz e por último a direita
3. Postorder(e, d, r)
    - Primeiro percorremos a esquerda, depois a direita e por último a raiz

Essas 3 ordens vão gerar expressões diferentes, porém todas válidas, de acordo com 3 notações. Preorder, inorder e postorder vão gerar respectivamente expressões de notação prefixada, infixada e posfixada/sufixada.

Implementações em pseudocódigo dos 3 algoritmos seguem abaixo.

**Preorder:**

```c++
void preorder(Node* root) {
    if (root != null) {
        print(root->info);
        preorder(root->left);
        preorder(root->right);
    }
}
```

**Inorder:**

```c++
void inorder(Node* root) {
    if (root != null) {
        inorder(root->left);
        print(root->info);
        inorder(root->right);
    }
}
```

**Postorder:**

```c++
void postorder(Node* root) {
    if (root != null) {
        postorder(root->left);
        postorder(root->right);
        print(root->info);
    }
}
```

### Busca em árvore binária 

> Uma árvore que se encontra organizada de tal forma que, para cada nodo Ti, todas as chaves da subárvore à esquerda de Ti são menores que (ou iguais a) Ti e a direita são maiores que Ti. (Niklaus Wirth)

> Em uma árvore balanceada a busca de um dado específico possui complexidade O(logn)

```c++
Node* search(T key, Node* pointer) {
    while(pointer != null && pointer->info != key) {
        if (pointer->info < key) {
            pointer = pointer->right;
        } else {
            pointer = pointer->left;
        }
    }

    return pointer;
}
```

### Inserção em árvore binária

```c++
Node* insert(Node root, T key) {
    Node* newNode;

    if(key < root->key) {
        if(raiz->left == nullptr) {
            newNode = new Node();
            newNode->key = key;
            newNode->left = nullptr;
            newNode->right = nullptr;
            root->left = newNode;
        } else {
            root = insert(root->left, key);
        }
    } else {
        if (root->right = nullptr) {
            newNode = new Node();
            newNode->key = key;
            newNode->left = nullptr;
            newNode->right = nullptr;
            root->right = newNode;
        } else {
            root = insert(root->right, key);
        }
    }
}
```

### Deleção em árvore binária

Na deleção pode dar merda, porque as características organizacionais da árvore não devem ser quebradas.

1. Se o nó a ser deletado possui somente uma subárvore filha
    - Podemos simplesmente mover esta subárvore toda para cima
    - Se o nodo a ser excluído é filho esquerdo de seu pai, o seu filho esquerdo será o novo filho esquerdo desse pai, e vice-versa.

2. Se o nó a ser deletado possui duas subárvores filhas.
    - Catapimbas não entendi nada do que o professor explicou e só vou implementar o pseudocódigo aqui embaixo

```c++
Node* remove(T key, Node subtree) {
    Node* temp, child;
    if (subtree == nullptr) {
        return subtree;
    } else {
        if (key < subtree->key) {
            subtree->left = remove(key, subtree->left);
            return subtree;
        } else if (key > subtree->key) {
            subtree->right = remove(key, subtree->right);
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

### Desvantagens de uma árvore binária de busca

1. Deterioração:

Quando inserimos um elemento em uma árvore de buscar utilizando uma inserção simples, ao longo do tempo estaremos deteriorando nossa árvore, desbalanceando a quantidade de elementos em cada lado.