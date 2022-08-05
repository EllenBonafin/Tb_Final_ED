#include <iostream>
#include "module.hpp"

//Inicializa a lista 
lista::lista(){
  //Utilizamos o nullptr para evitar ambguidades que o null pode causar
    this->primeiro = nullptr;
    this->ultimo = nullptr;
    this->tamL = 0;
}

//Remove a lista
lista::~lista(){
    if(vazio()) //retorna true caso a pilha estiver vazia
        return;
    No *aux= this->primeiro, *p; //Armazena em aux a primeira posição da fila
    while (aux != nullptr){ //Percorre toda a fila
        p= aux; 
        aux= aux->prox; //Aux pega o próximo nó
        delete[] p; //Free em p
    }
}

//Função que retorna o tamanho da lista 
int lista::tamanho(){
    return this->tamL;
}

//Função que verifica se a lista está vazia, retorna true caso a fila estiver vazia
bool lista::vazio(){
    return this->tamL==0;
}

//Função que imprime a lista na tela
void lista::imprime(){
  cout<<"Entrou!\n";
    if(this->vazio()){
        return ;
  }
    else{
    No *aux = primeiro;
    for (int i = 0; i < tamanho(); i++)
        cout<<"Entrou no for!\n";
        cout << aux->info << " \n ";
        aux = aux->prox;
}
  }

//Função que insere no inicio
bool lista::insereinicio(Dado Dado){
    No *novoNo = new No;
    if(novoNo==nullptr)
        return false;
    novoNo->info = Dado;
    novoNo->prox = nullptr;

    if(vazio()){
        this->primeiro = novoNo;
        this->ultimo = novoNo;
    }
    else{
        novoNo->prox = this->primeiro;
        this->primeiro = novoNo;
    }
    this->tamL++;
    return true;
}

//Função que insere no final
bool lista::inserefinal(Dado Dado){
    No *novoNo = new No;
    if(novoNo==nullptr)
        return false;
    novoNo->info= Dado;
    novoNo->prox= nullptr; //Utilizando o nullprt pois o null pode causar ambiguidade.

    if(vazio()){
        this->primeiro= novoNo;
        this->ultimo= novoNo;
    }
    else{
        this->ultimo->prox = novoNo;
        this->ultimo= novoNo;
    }
    this->tamL++;
    return true;
}


//Função que remove um elemento do inicio 
bool lista::removeinicio(){
    if(vazio())   //Verifica se está vazio
        return false;
    No *aux= this->primeiro; //Aux recebe a primeira posição da fila
    this->primeiro= aux->prox; //Aux pega a próxima posição da fila
    this->tamL--;
    delete[] aux; //Desaloca a variável aux
    return true;
}

//Função que remove um elemento do final
bool lista::removefinal(){
    if(vazio())
        return false;
    No *aux = this->primeiro;
    for(int i = 0 ; i < this->tamanho() - 1 ; i++)
        aux = aux->prox;
    this->ultimo = aux;
    this->ultimo->prox = nullptr;
    this->tamL--;
    delete[] aux->prox;
    return true;
}

//Função que busca um elemento
bool lista::buscaelemento(Dado Dado){
    if(vazio())
        return false;
    No*aux= this->primeiro;
    for(int i;i<this->tamanho();i++){
        if(aux->info==Dado)
          cout<<"Elemento Encontrado!\n"<<"Na posição: "<<i<<"\n";
            return true;
        aux= aux->prox;
    }
    return false;
}

//Função que retorna um elemento conforme  a posição passada por parâmetro
Dado lista::buscaposicao(int pos){
    if((this->vazio()) || (pos>=this->tamanho())){
        cerr<< "Posição inválida!\n" << endl;
        return -1;
    }
    No *aux = this->primeiro;
    for (int i = 0; i < pos; i++)
        aux = aux->prox;
    return aux->info;
}

// Inicializando a lista
Fila::Fila(){}
//Destrói a lista 
Fila::~Fila(){}

//Retorna o tamanho da fila
int Fila::tamanho(){
    return this->tamanho();
}

//Insere no final da fila
bool Fila::insere1(Dado Dado){
    return this->insereinicio(Dado);
}
//Insere no final da fila
bool Fila::insere2(Dado Dado){
    return this->inserefinal(Dado);
}

/*Função de remoção*/

//Remove um elemento do inicio da fila
bool Fila::remove1(){
    return this->removeinicio();
}

//Remove um elemento do final da fila
bool Fila::remove2(){
    return this->removefinal();
}

/*Função que retorna o tamaho da fila*/
//Retorna true se a fila estiver vazia 
bool Fila::tam(){
    return this->vazio();
}


/*Função de imprimir na tela*/
//Imprime na tela a fila 
void Fila::imprime(){
   this->imprime();
}

/*Funções de busca*/
//Função que busca um elemento na fila
bool Fila::busca1(Dado Dado){
  return this->buscaelemento(Dado);
  }

//Função que busca um elemento em uma posição na fila
Dado Fila::busca2(int pos){
  return this->buscaposicao(pos);
}

/*Funções para pegar o primeiro e o ultimo elemento da fila*/
//Pega o primeiro elemento da fila 
Dado Fila::primeiroNo(){
    return this->buscaposicao(0);
}
//Pega o ultimo elemento da fila 
Dado Fila::ultimoNo(){
    return this->buscaposicao(this->tamanho()-1);
}