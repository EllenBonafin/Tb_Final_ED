#ifndef MODULO_HPP
#define MODULO_HPP

using namespace std;

//Tipo de dado que será armazenado no nó
typedef int Dado;

//Struct no 
typedef struct No {
	Dado info; // Dado 
	struct No *prox;	// Ponteiro para o próximo nó 
} No;

// Definição da classe e lista encadeada
class lista{
private:
    No *primeiro;
    No *ultimo;
    int tamL;
public:
    //Inicializando a lista
    lista();

    //Destrói a lista 
    ~lista();

    //Função que retorna o tamanho da lista 
    int tamanho();

    //Função que verifica se a lista está vazia 
    bool vazio();

    //Função que imprime a lista na tela
    void imprime();

    /*Funções de Inserção*/
    //Função que insere no inicio
    bool insereinicio(Dado Dado);
    //Função que insere no final
    bool inserefinal(Dado Dado);

    /*Funções de Remoção*/
    //Função que remove um elemnto do inicio da lista
    bool removeinicio();
    //Função que remove um elemento do final da lista
    bool removefinal();

    /*Funções de busca*/
    //Função que busca um elemento na lista 
    bool buscaelemento(Dado Dado);
    //Função que retorna um elemento conforme  a posição passada por parâmetro 
    Dado buscaposicao(int pos);
};

// Definição da classe e da Fila com herança da lista encadeada
class Fila : protected lista{
public:
    // Inicializando a lista
    Fila();

    //Destrói a lista 
    ~Fila();

    //Operação que retorna o tamanho da fila
    int tamanho();

    /*Função de Inserção*/
    bool insere1(Dado Dado);
    bool insere2(Dado Dado);

    /*Função de Remoção*/
    bool remove1();
    bool remove2();

    //Função que verifica se a fila está vazia 
    bool tam();


    //Função que imprime a fila na tela
    void imprime();

    /*Função de Busca*/
    bool busca1(Dado Dado); //Busca um elemento na fila
    Dado busca2(int pos); //Retorna o elemento da posição informada


    /*Funções para pegar o primeiro e o ultimo nó da fila*/
    //Função que retorna o primeiro elemento da fila
    Dado primeiroNo();

    //Função que retorna o ultimo elemento da fila
    Dado ultimoNo();
};

#endif