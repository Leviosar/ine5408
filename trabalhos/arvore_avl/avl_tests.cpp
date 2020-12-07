// Copyright 2016 João Paulo Taylor Ienczak Zanette
// Jean Everson Martina
// Alexandre G. Silva (percursos corrigidos em nov2018, 
//                     alturas verificadas  em out2020)

#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "avl_tree.h"

namespace {


/**
 * Classe com propósito de oferecer maior robustez aos testes.
 */
class Dummy {
public:
    Dummy() = default;
    explicit Dummy(double value):
        value_{value}
    {}

    /**
     * Valor encapsulado
     */
    double value() const {
        return value_;
    }

    bool operator<(const Dummy& other) const {
        return value() < other.value();
    }

    bool operator<=(const Dummy& other) const {
        return value() <= other.value();
    }

    bool operator>(const Dummy& other) const {
        return value() > other.value();
    }

    bool operator>=(const Dummy& other) const {
        return value() >= other.value();
    }

    bool operator==(const Dummy& other) const {
        return value() == other.value();
    }

    bool operator!=(const Dummy& other) const {
        return value() != other.value();
    }

private:
    /**
     * Valor encapsulado
     */
    double value_{0.};
};

/**
 * Sobrescrita do operador std::ostream<<(Dummy) para possibilitar printar um
 * Dummy através do std::cout.
 */
std::ostream& operator<<(std::ostream& os, const Dummy& dummy) {
    os << dummy.value();
    return os;
}


/**
 * Valores a serem inseridos na árvore de inteiros.
 */
const auto int_values = std::vector<int>{
    10, 5, 8, 20, 25, 15, -5, -10, 30, -15
};

/**
 * Valores a serem inseridos na árvore de strings.
 */
const auto string_values = std::vector<std::string>{
    "AAA", "BBB", "123", "Hello, World!", "Goodbye, World!"
};

/**
 * Valores a serem inseridos na árvore de dummies.
 */
const auto dummy_values = std::vector<Dummy>{
    Dummy{0.},
    Dummy{-5.},
    Dummy{10.},
    Dummy{7.5},
    Dummy{-5.5},
    Dummy{3.1415},
    Dummy{4.2},
    Dummy{-10.},
};


/**
 * Teste unitário para árvore binária
 */
class AVLTreeTest: public testing::Test {
protected:
    /**
     * Lista para teste com inteiros.
     */
    structures::AVLTree<int> int_list{};
    /**
     * Lista para teste com strings.
     */
    structures::AVLTree<std::string> string_list{};
    /**
     * Lista para teste com dummies.
     */
    structures::AVLTree<Dummy> dummy_list{};

    /**
     * Testa uma inserção simples em uma lista.
     */
    template <typename T, typename U>
    void simple_insertion(T& list, U& values) {
        ASSERT_TRUE(list.empty());
        list.insert(values[0]);
        ASSERT_FALSE(list.empty());
        ASSERT_EQ(1, list.size());
    }

    /**
     * Testa a inserção de múltiplos valores em uma lista.
     */
    template <typename T, typename U>
    void multiple_insertion(T& list, const U& values) {
        ASSERT_TRUE(list.empty());
        for (auto& value : values) {
            list.insert(value);
        }
        ASSERT_FALSE(list.empty());
        ASSERT_EQ(values.size(), list.size());
    }

    /**
     * Testa se todos os valores inseridos estão na lista.
     */
    template <typename T, typename U>
    void contains_all(const T& list, const U& values) {
        for (auto& value : values) {
            ASSERT_TRUE(list.contains(value));
        }
    }
};

}  // namespace

/**
 * Testa se a árvore informa corretamente quando está vazia.
 */
TEST_F(AVLTreeTest, Empty) {
    ASSERT_TRUE(int_list.empty());
    ASSERT_TRUE(string_list.empty());
    ASSERT_TRUE(dummy_list.empty());
}

/**
 * Testa se a árvore de inteiros permite corretamente a inserção de um elemento.
 */
TEST_F(AVLTreeTest, SingleIntegerInsertion) {
    simple_insertion(int_list, int_values);
}

/**
 * Testa se a árvore de strings permite corretamente a inserção de um elemento.
 */
TEST_F(AVLTreeTest, SingleStringInsertion) {
    simple_insertion(string_list, string_values);
}


/**
 * Testa se a árvore de um tipo qualquer permite corretamente a inserção de um
 * elemento.
 */
TEST_F(AVLTreeTest, SingleDummyInsertion) {
    simple_insertion(dummy_list, dummy_values);
}

/**
 * Testa se a árvore de inteiros permite corretamente a inserção de vários
 * elementos.
 */
TEST_F(AVLTreeTest, MultipleIntegerInsertion) {
    multiple_insertion(int_list, int_values);
    ASSERT_EQ(3, int_list.height());
}

/**
 * Testa se a árvore de strings permite corretamente a inserção de vários
 * elementos.
 */
TEST_F(AVLTreeTest, MultipleStringInsertion) {
    multiple_insertion(string_list, string_values);
    ASSERT_EQ(2, string_list.height());
}

/**
 * Testa se a árvore de um tipo qualquer permite corretamente a inserção de
 * vários elementos.
 */
TEST_F(AVLTreeTest, MultipleDummyInsertion) {
    multiple_insertion(dummy_list, dummy_values);
    ASSERT_EQ(3, dummy_list.height());
}

/**
 * Testa se a árvore checa corretamente a presença de um elemento.
 */
TEST_F(AVLTreeTest, Contains) {
    multiple_insertion(int_list, int_values);
    multiple_insertion(string_list, string_values);
    multiple_insertion(dummy_list, dummy_values);

    contains_all(int_list, int_values);
    contains_all(string_list, string_values);
    contains_all(dummy_list, dummy_values);
}

/**
 * Testa se a árvore checa corretamente a ausência de um elemento.
 */
TEST_F(AVLTreeTest, NotContains) {
    multiple_insertion(int_list, int_values);
    multiple_insertion(string_list, string_values);
    multiple_insertion(dummy_list, dummy_values);

    ASSERT_FALSE(int_list.contains(3));
    ASSERT_FALSE(string_list.contains("Hallo, World!"));
    ASSERT_FALSE(dummy_list.contains(Dummy{4.3}));
}

/**
 * Testa se a remoção de um elemento na árvore funciona como previsto.
 */
TEST_F(AVLTreeTest, Remove) {
    {
        multiple_insertion(int_list, int_values);
        auto size = int_list.size();
        ASSERT_TRUE(int_list.contains(-15));
        int_list.remove(-15);
        ASSERT_FALSE(int_list.contains(-15));
        ASSERT_EQ(size-1, int_list.size());
        ASSERT_EQ(3, int_list.height());
    }

    {
        multiple_insertion(string_list, string_values);
        auto size = string_list.size();
        ASSERT_TRUE(string_list.contains("Hello, World!"));
        string_list.remove("Hello, World!");
        ASSERT_FALSE(string_list.contains("Hello, World!"));
        ASSERT_EQ(size-1, string_list.size());
        ASSERT_EQ(2, string_list.height());
    }

    {
        multiple_insertion(dummy_list, dummy_values);

        auto size = dummy_list.size();
        auto dummy = Dummy{4.2};
        ASSERT_TRUE(dummy_list.contains(dummy));

        dummy_list.remove(dummy);

        ASSERT_FALSE(dummy_list.contains(dummy));
        ASSERT_EQ(size-1, dummy_list.size());
        ASSERT_EQ(2, dummy_list.height());
    }
}

/**
 * Testa se a árvore gera corretamente uma lista por pré-ordem.
 */
TEST_F(AVLTreeTest, PreOrder) {
    {
        multiple_insertion(int_list, int_values);

        auto preordered = int_list.pre_order();
        auto expected = {10, 5, -10, -15, -5, 8, 20, 15, 25, 30};
        auto i = 0u;
        for (auto& value : expected) {
            ASSERT_EQ(value, preordered[i]);
            ++i;
        }
    }

    {
        multiple_insertion(string_list, string_values);

        auto preordered = string_list.pre_order();
        auto expected = {
            "AAA", "123", "Goodbye, World!", "BBB", "Hello, World!"
        };
        auto i = 0u;
        for (auto& value : expected) {
            ASSERT_EQ(value, preordered[i]);
            ++i;
        }
    }

    {
        multiple_insertion(dummy_list, dummy_values);
        auto preordered = dummy_list.pre_order();

        auto expected = {0., -5.5, -10., -5., 7.5, 3.1415, 4.2, 10.};
        auto i = 0u;
        for (auto& value : expected) {
            ASSERT_EQ(Dummy{value}, preordered[i]);
            ++i;
        }
    }
}

/**
 * Testa se a árvore gera corretamente uma lista por em-ordem.
 */
TEST_F(AVLTreeTest, InOrder) {
    {
        multiple_insertion(int_list, int_values);

        auto inordered = int_list.in_order();
        auto expected = {-15, -10, -5, 5, 8, 10, 15, 20, 25, 30};
        auto i = 0u;
        for (auto& value : expected) {
            ASSERT_EQ(value, inordered[i]);
            ++i;
        }
    }

    {
        multiple_insertion(string_list, string_values);

        auto inordered = string_list.in_order();
        auto expected = {
            "123", "AAA", "BBB", "Goodbye, World!", "Hello, World!"
        };
        auto i = 0u;
        for (auto& value : expected) {
            ASSERT_EQ(value, inordered[i]);
            ++i;
        }
    }

    {
        multiple_insertion(dummy_list, dummy_values);
        auto inordered = dummy_list.in_order();

        auto expected = {-10., -5.5, -5., 0., 3.1415, 4.2, 7.5, 10.};
        auto i = 0u;
        for (auto& value : expected) {
            ASSERT_EQ(Dummy{value}, inordered[i]);
            ++i;
        }
    }
}

/**
 * Testa se a árvore gera corretamente uma lista por pós-ordem.
 */
TEST_F(AVLTreeTest, PostOrder) {
    {
        multiple_insertion(int_list, int_values);

        auto postordered = int_list.post_order();
        auto expected = {-15, -5, -10, 8, 5, 15, 30, 25, 20, 10};
        auto i = 0u;
        for (auto& value : expected) {
            ASSERT_EQ(value, postordered[i]);
            ++i;
        }
    }

    {
        multiple_insertion(string_list, string_values);

        auto postordered = string_list.post_order();
        auto expected = {
            "123", "BBB", "Hello, World!", "Goodbye, World!", "AAA"
        };
        auto i = 0u;
        for (auto& value : expected) {
            ASSERT_EQ(value, postordered[i]);
            ++i;
        }
    }

    {
        multiple_insertion(dummy_list, dummy_values);
        auto postordered = dummy_list.post_order();

        auto expected = {-10., -5., -5.5, 4.2, 3.1415, 10., 7.5, 0.};
        auto i = 0u;
        for (auto& value : expected) {
            ASSERT_EQ(Dummy{value}, postordered[i]);
            ++i;
        }
    }
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
