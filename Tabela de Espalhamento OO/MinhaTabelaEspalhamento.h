#ifndef MINHA_TABELA_ESPALHAMENTO_H
#define MINHA_TABELA_ESPALHAMENTO_H

#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada
#include "TabelaEspalhamentoAbstrata.h"
// TabelaEspalhamentoAbstrata
#include "excecoes.h"
// ExcecaoDadoInexistente

#include <iostream>
#include <string>
#include <cmath>



template<typename T, std::size_t _capacidade>
class MinhaTabelaEspalhamento final:
    public TabelaEspalhamentoAbstrata<T, _capacidade>
{
//implemente aqui
public:

    ~MinhaTabelaEspalhamento()
    {

    }

    
    virtual std::size_t capacidade() const
    {
    /**
     * @brief Obtém a capacidade da tabela.
     * 
     * @return Um inteiro maior do que 0.
     */

        return _capacidade;

    }

    virtual void inserir(T dado) 
    {
    /**
     * @brief Insere um dado na tabela. Se a tabela já contiver o dado, ele não
     * é inserido novamente.
     * 
     * @param dado O dado a ser inserido.
     */  
        std::size_t posicao = funcaoEspalhamento(dado);
        if(this->_tabela[posicao].contem(dado))
        {
            return;
        }
        else
        {
            this->_tabela[posicao].inserir(this->_tabela[posicao].tamanho(), dado);
        }
        
        
        
    }

    
    
    virtual void remover(T dado)
    {
    /**
     * @brief Remove um dado da tabela. Se a tabela não contiver o dado, uma
     * exceção ExcecaoDadoInexistente é lançada.
     * 
     * @param dado O dado a ser removido.
     */
        std::size_t posicao = funcaoEspalhamento(dado);
        if(this->_tabela[posicao].contem(dado))
        {
            this->_tabela[posicao].remover(dado);
        }
        else
        {
            throw ExcecaoDadoInexistente();
        }
    }

    
    virtual bool contem(T dado) const
    {
    /**
     * @brief Verifica se \p dado está contido na tabela.
     * 
     * @param dado O dado sendo buscado.
     * @return true se o dado está contido na tabela; false caso contrário.
     */
        std::size_t posicao = funcaoEspalhamento(dado);
        return this->_tabela[posicao].contem(dado);
    }

    virtual std::size_t quantidade() const 
    {
    /**
     * @brief Obtém a quantidade de dados contidos na árvore.
     * 
     * @return Um inteiro maior ou igual a 0.
     */
        size_t quantidade = 0;
        for(size_t i = 0; i < _capacidade; i++)
        {
            quantidade += this->_tabela[i].tamanho();
        }
        return quantidade;
    }

    
    
protected:
    
    virtual std::size_t funcaoEspalhamento(T dado) const
    {
    /**
     * @brief Obtém a posição correspondente na tabela para o dado.
     * 
     * @param dado O dado.
     * @return Um inteiro na faixa [0, capacidade).
     */
        return codigo(dado);

    }

    std::size_t codigo(int dado) const
    {   
        return dado % _capacidade;

    }

    std::size_t codigo(std::string dado) const
    {
        size_t tamanho = dado.length();
        int num = 0;

        for(size_t i = 0; i < tamanho; i++)
        {
            num += dado.at(i)* pow(31,tamanho - 1 - i);
        }
        return num % _capacidade;

    }



};

#endif
