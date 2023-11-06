#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "ArvoreBinariaDeBusca.h"


/**
 * @brief Representa uma árvore AVL.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public ArvoreBinariaDeBusca<T>
{
    //implemente aqui
    public: 

        MinhaArvoreAVL()
        {
            this->_raiz = nullptr;

        }

     ~MinhaArvoreAVL()
     {
            if(this->_raiz == nullptr)
            {
                return;
            }
            else
            {
                deletaRecursivo(this->_raiz);
            }
       
     }


    //**************** FUNÇOES DA ARVORE BINARIA DE BUSCA ****************
     bool vazia() const
     {
     /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */
        if( this->_raiz == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }

     }
    
    
     int quantidade() const
     {
     /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
        if(this->_raiz == nullptr)
        {
            return 0;
        }
        else
        {
            return 1 + NumeroNodo(this->_raiz->filhoEsquerda) + NumeroNodo(this->_raiz->filhoDireita);
        }
        
        
        
     }
    
    
     bool contem(T chave) const
    {
    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
        if(vazia())
        {
            return false;
        }
        else
        {
            Nodo<T>* nodo = this->_raiz;
            while(nodo != nullptr)
            {
                if(chave == nodo->chave)
                {
                    return true;
                }
                else if(chave < nodo->chave)
                {
                    nodo = nodo->filhoEsquerda;
                }
                else
                {
                    nodo = nodo->filhoDireita;
                }
            }
            return false;
        }

    }
    
     std::optional<int> altura(T chave) const
    {
     /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos. 
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */   
        if(vazia())
        {
            return std::nullopt;
        }
        else
        {
            Nodo<T>* nodo = this->_raiz;
            while(nodo != nullptr)
            {
                if(chave == nodo->chave)
                {
                    return nodo->altura;
                }
                else if(chave < nodo->chave)
                {
                    nodo = nodo->filhoEsquerda;
                }
                else
                {
                    nodo = nodo->filhoDireita;
                }
            }
            return std::nullopt;
        }
        
    }

    
     void inserir(T chave)
    {
    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */  
        if(vazia())
        {
            Nodo<T>* nodo = new Nodo<T>;
            nodo->chave = chave;
            nodo->altura = 0;
            nodo->filhoEsquerda = nullptr;
            nodo->filhoDireita = nullptr;
            this->_raiz = nodo;
        }
        else
        {
            Nodo<T>* nodo = this->_raiz;
            Nodo<T>* nodoPai = nullptr;
            while(nodo != nullptr)
            {
                nodoPai = nodo;
                if(chave < nodo->chave)
                {
                    nodo = nodo->filhoEsquerda;
                }
                else
                {
                    nodo = nodo->filhoDireita;
                }
            }
            nodo = new Nodo<T>;
            nodo->chave = chave;
            nodo->altura = 0;
            nodo->filhoEsquerda = nullptr;
            nodo->filhoDireita = nullptr;
            if(chave < nodoPai->chave)
            {
                nodoPai->filhoEsquerda = nodo;
            }
            else
            {
                nodoPai->filhoDireita = nodo;
            }
        }
        
        recalculaAltura(this->_raiz);
        balanceamento(this->_raiz);
    

    }
       
     void remover(T chave) 
    {
     /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     */  
        if(vazia())
        {
            return;
        }
        else 
        {
            if(!contem(chave))
            {
                return;
            }

            Nodo<T>* nodo = this->_raiz;
            Nodo<T>* nodoPai = nullptr;
            while(nodo->chave != chave)
            {
                nodoPai = nodo;
                if(chave < nodo->chave)
                {
                    nodo = nodo->filhoEsquerda;
                }
                else
                {
                    nodo = nodo->filhoDireita;
                }
            }
            if(nodo->filhoDireita == nullptr && nodo->filhoEsquerda == nullptr)
            {
                if(nodoPai == nullptr)
                {
                    this->_raiz = nullptr;
                }
                else if(nodoPai->filhoDireita == nodo)
                {
                    nodoPai->filhoDireita = nullptr;
                }
                else
                {
                    nodoPai->filhoEsquerda = nullptr;
                }
                delete nodo;
            }
            else if(nodo->filhoDireita == nullptr && nodo->filhoEsquerda != nullptr)
            {
                if(nodoPai->filhoDireita == nodo)
                {
                    nodoPai->filhoDireita = nodo->filhoEsquerda;
                }
                else
                {
                    nodoPai->filhoEsquerda = nodo->filhoEsquerda;
                }
                delete nodo;
            }
            else
            {
                Nodo<T>* nodoBusca = nodo->filhoDireita;
                Nodo<T>* nodoBuscaPai = nodo;
                while(nodoBusca->filhoEsquerda != nullptr)
                {
                    nodoBuscaPai = nodoBusca;
                    nodoBusca = nodoBusca->filhoEsquerda;
                }
                nodo->chave = nodoBusca->chave;
                if(nodoBuscaPai->filhoDireita == nodoBusca)
                {
                    nodoBuscaPai->filhoDireita = nodoBusca->filhoDireita;
                }
                else
                {
                    nodoBuscaPai->filhoEsquerda = nodoBusca->filhoDireita;
                }
                delete nodoBusca;
            }

            recalculaAltura(this->_raiz);
            balanceamento(this->_raiz);      
            return;
        }
        
    }

     std::optional<T> filhoEsquerdaDe(T chave) const
    {
     /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
       if(contem(chave))
       {
              Nodo<T>* nodo = this->_raiz;
              while(nodo->chave != chave)
              {
                if(chave < nodo->chave)
                {
                     nodo = nodo->filhoEsquerda;
                }
                else
                {
                     nodo = nodo->filhoDireita;
                }
              }
              if(nodo->filhoEsquerda != nullptr)
              {
                return nodo->filhoEsquerda->chave;
              }
              else
              {
                return std::nullopt;
              }

       }
       else 
        {
           return std::nullopt;
        }

    }

       
     std::optional<T> filhoDireitaDe(T chave) const 
    {
     /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */     
        if(contem(chave))
       {
              Nodo<T>* nodo = this->_raiz;
              while(nodo->chave != chave)
              {
                if(chave < nodo->chave)
                {
                     nodo = nodo->filhoEsquerda;
                }
                else
                {
                     nodo = nodo->filhoDireita;
                }
              }
              if(nodo->filhoDireita != nullptr)
              {
                return nodo->filhoDireita->chave;
              }
              else
              {
                return std::nullopt;
              }

       }
       else 
        {
           return std::nullopt;
        }
    }

    
     ListaEncadeadaAbstrata<T>* emOrdem() const 
    {
     /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem. 
     */

       ListaEncadeadaAbstrata<T>* lista = new MinhaListaEncadeada<T>;
        emOrdemRecursivo(lista, this->_raiz);
        return lista;
    }

    
     ListaEncadeadaAbstrata<T>* preOrdem() const 
    {
     /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem. 
     */

        ListaEncadeadaAbstrata<T>* lista = new MinhaListaEncadeada<T>;
        preOrdemRecursivo(lista, this->_raiz);
        return lista;
    }

    
     ListaEncadeadaAbstrata<T>* posOrdem() const 
    {
     /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem. 
     */
        ListaEncadeadaAbstrata<T>* lista = new MinhaListaEncadeada<T>;
        posOrdemRecursivo(lista, this->_raiz);
        return lista;
    }
    
    //******************* FUNÇOES AUGUSTO *******************************

    int NumeroNodo(Nodo<T>* nodo) const
     {
         if(nodo == nullptr)
         {
            return 0;
         }
         else
         {
            return 1 + NumeroNodo(nodo->filhoEsquerda) + NumeroNodo(nodo->filhoDireita);
         }
     }

    int recalculaAltura(Nodo<T>* nodo) const
    {
        if(nodo == nullptr)
        {
            return -1;
        }
        else
        {
            nodo->altura = 1 + std::max(recalculaAltura(nodo->filhoEsquerda), recalculaAltura(nodo->filhoDireita));
            return nodo->altura;
            
            
        }
    }

    void deletaRecursivo(Nodo<T>* nodo) const
    {
        if(nodo == nullptr)
        {
            return;
        }
        else
        {
            deletaRecursivo(nodo->filhoEsquerda);
            deletaRecursivo(nodo->filhoDireita);
            delete nodo;
        }
    }

    void emOrdemRecursivo(ListaEncadeadaAbstrata<T>* lista ,Nodo<T>* nodo) const
        {

            if(nodo == nullptr)
            {
                return;
            }
            else{
                emOrdemRecursivo(lista, nodo->filhoEsquerda);
                lista->inserirNoFim(nodo->chave);
                emOrdemRecursivo(lista, nodo->filhoDireita);
            }
        }

    void preOrdemRecursivo(ListaEncadeadaAbstrata<T>* lista ,Nodo<T>* nodo) const
        {
            if(nodo == nullptr)
            {
                return;
            }
            else
            {
                lista->inserirNoFim(nodo->chave);
                preOrdemRecursivo(lista, nodo->filhoEsquerda);
                preOrdemRecursivo(lista, nodo->filhoDireita);
              
            }
        }

    void posOrdemRecursivo(ListaEncadeadaAbstrata<T>* lista ,Nodo<T>* nodo) const
        {
            if(nodo == nullptr)
            {
                return;
            }
            else
            {
                
                posOrdemRecursivo(lista, nodo->filhoEsquerda);
                posOrdemRecursivo(lista, nodo->filhoDireita);
                lista->inserirNoFim(nodo->chave);
              
            }
        }

    void rotacaoEsquerda(Nodo<T>*& nodo) const
{
    Nodo<T>* nodoAux = nodo->filhoDireita;
    nodo->filhoDireita = nodoAux->filhoEsquerda;
    nodoAux->filhoEsquerda = nodo;
    nodo = nodoAux;
    
    
   
}

    void rotacaoDireita(Nodo<T>*& nodo) const
{
     Nodo<T>* nodoAux = nodo->filhoEsquerda;
    nodo->filhoEsquerda = nodoAux->filhoDireita;
    nodoAux->filhoDireita = nodo;
    nodo = nodoAux;
    
    

}

 void rotacaoDireitaEsquerda(Nodo<T>*& nodo) const
{
    Nodo<T>* nodoAux = nodo->filhoDireita;
    rotacaoDireita(nodoAux);
    nodo->filhoDireita = nodoAux;
    rotacaoEsquerda(nodo);
    
    
    
}

void rotacaoEsquerdaDireita(Nodo<T>*& nodo) const
{
    Nodo<T>* nodoAux = nodo->filhoEsquerda;
    rotacaoEsquerda(nodoAux);
    nodo->filhoEsquerda = nodoAux;
    rotacaoDireita(nodo);
}


    void balanceamento(Nodo<T>*& nodo) const
    {
        if(nodo == nullptr)
        {
            return;
        }
        else
        {
            balanceamento(nodo->filhoEsquerda);
            balanceamento(nodo->filhoDireita);

            if(nodo->filhoEsquerda == nullptr && nodo->filhoDireita == nullptr)
            {
                return;
            }
            else if(nodo->filhoEsquerda == nullptr && nodo->filhoDireita != nullptr)
            {
                if(nodo->filhoDireita->filhoDireita != nullptr && nodo->filhoDireita->filhoEsquerda != nullptr)
                {
                 if(nodo->filhoDireita->filhoEsquerda->altura > nodo->filhoDireita->filhoDireita->altura)
                 {
                     rotacaoDireitaEsquerda(nodo);
                 }
                 else
                 {
                    rotacaoEsquerda(nodo);
                 }
                }
                else if(nodo->filhoDireita->filhoDireita == nullptr && nodo->filhoDireita->filhoEsquerda != nullptr)
                {
                    rotacaoDireitaEsquerda(nodo);
                }
                else if(nodo->filhoDireita->filhoDireita != nullptr && nodo->filhoDireita->filhoEsquerda == nullptr)
                {
                    rotacaoEsquerda(nodo);
                }
            
                
            }
            else if(nodo->filhoEsquerda != nullptr && nodo->filhoDireita == nullptr)
            {
                if(nodo->filhoEsquerda->filhoDireita != nullptr && nodo->filhoEsquerda->filhoEsquerda != nullptr)
                {
                 if(nodo->filhoEsquerda->filhoDireita->altura > nodo->filhoEsquerda->filhoEsquerda->altura)
                 {
                     rotacaoEsquerdaDireita(nodo);
                 }
                 else
                 {
                     rotacaoDireita(nodo);
                 }
                }
                else if(nodo->filhoEsquerda->filhoDireita == nullptr && nodo->filhoEsquerda->filhoEsquerda != nullptr)
                {
                    rotacaoDireita(nodo);
                }
                else if(nodo->filhoEsquerda->filhoDireita != nullptr && nodo->filhoEsquerda->filhoEsquerda == nullptr)
                {
                    rotacaoEsquerdaDireita(nodo);
                }
                
            }
            else 
            {
                if(nodo->filhoEsquerda->altura - nodo->filhoDireita->altura > 1)
                {
                    rotacaoDireita(nodo);
                }
                else if(nodo->filhoDireita->altura - nodo->filhoEsquerda->altura > 1)
                {
                    rotacaoEsquerda(nodo);
                }

            }
           recalculaAltura(this->_raiz);

        }
    }

   

};



#endif