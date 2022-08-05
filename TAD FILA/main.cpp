#include <iostream>
#include "module.hpp"

int main(){

  //Criando a Fila
  Fila fila;

  //Menu de opções para a fila 
  int op=-1;
  while (op!=0){
    cout<<"Escolha uma opção para ser realizada:\n";
    cout<<"1. Inserir um elemento no inicio.\n";
    cout<<"2. Inserir um elemento no final.\n";
    cout<<"3. Remover um elemento do inicio.\n";
    cout<<"4. Remover um elemento do final.\n";
    cout<<"5. Imprimir a fila.\n";
    cout<<"6. Buscar um elemento na fila.\n";
    cout<<"7. Buscar um elemento em uma posição na fila.\n";
    cout<<"8. Mostrar o primeiro elemento da fila.\n";
    cout<<"9. Mostrar o último elemento da fila.\n";
    cout<<"10. Desalocar a fila.\n";  
    cout<<"0. Sair.\n";
    cout<<"Digite a opção escolhida: \n";
    cin>>op;

    //Chamando as funções conforme a opção escolhida
    if(op==1){
      int Dado=0;
      cout<<"Informe o dado que será inserido: \n";
      cin>>Dado;
      fila.insere1(Dado);
    }
      
    else if(op==2){
      int Dado=0;
      cout<<"Informe o dado que será inserido: \n";
      cin>>Dado;
      fila.insere2(Dado);
    }

    else if(op==3){
    if(fila.remove1())
    cout<<"Elemento removido do inicio!\n";
    else
    cout<<"Erro na remoção no inicio!\n";
    }

    else if (op==4){
    if(fila.remove2())
    cout<<"Elemento removido do final!\n";
    else
    cout<<"Erro na remoção no inicio!\n";
    }

    else if(op==5){
      cout<<"Impressão na tela: \n";
      fila.imprime();
      cout<<"Voltou!\n";
    }

    else if(op==6){
      int Dado=0;
      cout<<"Informe o dado que será buscado: \n";
      cin>>Dado;
      fila.busca1(Dado);
    }

    else if(op==7){
      int pos=-1;
      cout<<"Informe uma posição: \n";
      cin>>pos;
      fila.busca2(pos);
    }

    else if(op==8){
      cout<<"O primeiro elemento da fila é: "<<fila.primeiroNo()<<"\n";
    }

    else if(op==9){
      cout<<"O ultimo elemento da fila é: "<<fila.ultimoNo()<<"\n";     
    }

    else if(op==10){
      cout<<"Desalocando a fila!\n";
      fila.~Fila();
    }

    else{
      cout<<"Opção inválida!\n";
    }
    }
              
  return 0;
}