#ifndef MINHALISTAENCADEADA_H
#define MINHALISTAENCADEADA_H

#include "ListaEncadeadaAbstrata.h"

template <typename T>
class MinhaListaEncadeada :  public ListaEncadeadaAbstrata<T>
{
    //implemente aqui
    public:

    
     ~MinhaListaEncadeada() 
    {
        /**
         * @brief Destrutor da classe.
         */
        
        while ( this->_tamanho > 0 )
        {
            this->removerDoInicio();
        }

    };

     MinhaListaEncadeada()
    {
        /**
         * @brief Construtor da classe.
         */
        this->_tamanho = 0;
        this->_primeiro = nullptr;

    };


     std::size_t tamanho() const 
    {
        /**
         * @brief Obtém a quantidade de itens na lista.
         *
         * @return Um inteiro maior ou igual a 0.
         */
        return this->_tamanho;
    };

     bool vazia() const
    {
        /**
         * @brief Indica se há algum item na lista ou não.
         *
         * @return false se houver algum item na lista; true caso contrário.
         */
        if(tamanho() == 0)
            return true;
        else
            return false;
    };

     std::size_t posicao(T dado) const 
    {
        /**
         * @brief Obtém a posição de um item na lista. Lança
         * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
         * ExcecaoDadoInexistente caso o item não esteja contido na lista.
         *
         * @param dado O item cuja posição deseja-se obter.
         * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
         * item na lista, a posição da primeira ocorrência.
         */
        if(tamanho() == 0)
            throw ExcecaoListaEncadeadaVazia();
        
        Elemento<T>* elementoAtual = this->_primeiro;
        size_t indiceAtual = 0;
        
        while (elementoAtual != nullptr)
        {
            if (elementoAtual->dado == dado)
            {
                return indiceAtual;
            }

            elementoAtual = elementoAtual->proximo;
            ++indiceAtual;
        }

        
        throw ExcecaoDadoInexistente();

    };

     bool contem(T dado) const 
    {
        /**
         * @brief Indica se um dado item está contido na lista ou não.
         *
         * @param dado O item sendo buscado.
         * @return true se o item está contido na lista; false caso contrário.
         */
        /* 
        tentativa que da erro 
        if(posicao(dado)>= 0 && posicao(dado) < tamanho())
            return true;
        else
            return false;
         */
        Elemento<T>* elementoAtual = this->_primeiro;
        size_t indiceAtual = 0;
        
        while (elementoAtual != nullptr)
        {
            if (elementoAtual->dado == dado)
            {
                
                return true;
            }

            elementoAtual = elementoAtual->proximo;
            ++indiceAtual;
        }

        return false;


    };

     void inserirNoInicio(T dado) 
    {
        /**
         * @brief Insere um item no início da lista.
         *
         * @param dado O item sendo inserido.
         */
        Elemento<T>* novoElemento = new Elemento<T>(dado, this->_primeiro);

        this->_primeiro = novoElemento;
        ++this->_tamanho;
    };

     void inserir(std::size_t posicao, T dado) 
    {
        /**
         * @brief Insere um item em uma posição específica da lista. Lança
         * ExcecaoPosicaoInvalida caso a posição não esteja na faixa
         * [0, tamanho].
         *
         * @param posicao Um inteiro dentro da faixa [0, tamanho]. Ao se inserir em
         * uma posição já ocupada, a posição do item que já estava naquela posição
         * será posicao + 1; inserir-se na posicao tamanho significa inserir-se no
         * fim da lista.
         * @param dado O item sendo inserido.
         */
        if (posicao > this->_tamanho) 
        {
            throw ExcecaoPosicaoInvalida();
        }

        if (posicao == 0) 
        {
            this->inserirNoInicio(dado);
            return;
        }

        Elemento<T>* elementoAtual = this->_primeiro;

        for (size_t i = 0; i < posicao - 1; i++) 
        {
            elementoAtual = elementoAtual->proximo;
        }

        Elemento<T>* novoElemento = new Elemento<T>(dado, elementoAtual->proximo);
        elementoAtual->proximo = novoElemento;
        ++this->_tamanho;
     
   
    };

     void inserirNoFim(T dado) 
    {
        /**
         * @brief Insere um item no fim da lista.
         *
         * @param dado O item sendo inserido.
         */
        this->inserir(this->_tamanho, dado);
    };

    
     T removerDoInicio() 
    {
        /**
        * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
        * caso não haja nenhum item na lista.
        *
        * @return O item removido.
        */   
        if (vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        Elemento<T>* elementoRemovido = this->_primeiro;

        T dado = elementoRemovido->dado;

        this->_primeiro = elementoRemovido->proximo;
        
        delete elementoRemovido;

       --this->_tamanho;
       return dado;
        
    };

     T removerDe(std::size_t posicao) 
    {
        /**
        * @brief Remove um item de uma posição específica da lista. Lança
        * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
        *
        * @param posicao Um inteiro dentro da faixa [0, tamanho).
        * @return O item removido.
        */
        
        if (posicao >= this->_tamanho  ) 
        {
            throw ExcecaoPosicaoInvalida();
        }

        if (posicao == 0) 
        {
            return this->removerDoInicio();
        }

        Elemento<T>* elementoAtual = this->_primeiro;

        for( size_t i = 0; i < posicao - 1; i++)
        {
            elementoAtual = elementoAtual->proximo;
        }

        Elemento<T>* elementoRemovido = elementoAtual->proximo;

        T dado = elementoRemovido->dado;

        elementoAtual->proximo = elementoRemovido->proximo;

        delete elementoRemovido;
        --this->_tamanho;
        return dado;

    };

     T removerDoFim() 
    {
        /**
        * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
        * caso não haja nenhum item na lista.
        *
        * @return O item removido.
        */
        if (vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        return this->removerDe(this->_tamanho - 1);
    };
    
     void remover(T dado) 
    {
    /**
     * @brief Remove um item específico da lista. Lança
     * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     *
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorrência.
     */

        if(vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        if(!contem(dado))
        {
            throw ExcecaoDadoInexistente();
        }
        this->removerDe(posicao(dado));
        
    };

};

#endif