#include <stdio.h>
#include <stdlib.h>
#include "module.h"

#define DIGRAFO 1 
//Define se será digrafo.

int main() {
  //Variáveis para as Vertices e o grauGrafo.
  int Vertices=0, grauGrafo=0;
  int x=0;
  //Variável utilizada para operações 
  int op=-1,op2=0;

  //Variável para definir em qual vertice começará a busca
  int Vinicial=0;
  int origemVertice=0, destinoVertice=0, tV=0;

  //Variável utilizada para  buscas em profundidade e de largura
  int grafosVisitados[Vertices];  
  int ant[Vertices];
  float dist[Vertices];
  
    //Definição de quantas Vertices o grafo possuirá
    printf("Digite a quantidade de vértices o grafo possuirá: \n");
    x=scanf("%d", &Vertices);
  
    //Definição do grauGrafo 
    printf("Digite a quantidade de graus o grafo possuirá: \n");
    x=scanf("%d", &grauGrafo);
  
  //Alocando um grafo
  Grafo* grafo= criaG (Vertices, grauGrafo, 0 );

  //Insere aletóriamente um valor de vértices no grafo
  insere(grafo, grauGrafo);

  //While que chama as funções conforme a opção escolhida.
  while(op!=0){
    //Menu de para escolher uma operação 
  printf("Escolha uma opção abaixo: \n");
  printf("1. Imprimir gravo na tela.\n");
  printf("2. Adicionar uma nova aresta.\n");
  printf("3. Remover uma aresta.\n");
  printf("4. Buscar no grafo.\n");
  printf("5. Desalocar gravo.\n");
  printf("0. Sair.\n");
  printf("Digite a opção escolhida: \n");
  x=scanf("%d",&op);
    if(op==1){
      //chama função.
      imprimeG(grafo);
    }
    else if(op==2){
      printf("Determine sua origemVertice: ");
      x=scanf("%d", &origemVertice);
      printf("Determine seu destinoVertice: ");
      x=scanf("%d", &destinoVertice);
      insereA(grafo, origemVertice, destinoVertice, DIGRAFO, 0);
    }
    else if(op==3){
        printf("Determine sua origemVertice: ");
        x=scanf("%d", &origemVertice);
        printf("Determine seu destinoVertice: ");
        x=scanf("%d", &destinoVertice);
      //chama função.
        removeA(grafo, origemVertice, destinoVertice, DIGRAFO);  
    }
    else if (op==4){
      //Menu para escolher a forma de busca desejada
      printf("Busca dentro do grafo:\n\n");
      printf("1 - Procurar o menor caminho\n");
      printf("2 - Busca em profundidade\n");
      printf("3 - Busca em largura\n");
      printf("Digite a opção escolhida: \n");
      x=scanf("%d",&op2);
      if(op2==1){
        printf("Procura o menor caminho:\n");
        printf("\nDetermine o vertice inicial: ");
        x=scanf("%d", &Vinicial);
        mCaminho(grafo,Vinicial,ant,dist);   
        int i=0;
        for(i=0; i<grauGrafo; i++)
            if(ant[i] < 0)
            printf("%d: %d -> {%.2f}\n", i, ant[i], dist[i]);
            else
            printf("%d:  %d -> {%.2f}\n", i, ant[i], dist[i]);
      }
      else if(op2==2){
        printf("Busca em profundidade:\n");
        printf("\nDetermine o vertice inicial: ");
        x=scanf("%d", &Vinicial);
        //chama função.
        profundidadeG(grafo, Vinicial, grafosVisitados);
        
      }
      else if(op2==3){
        printf("Busca em profundidade:\n");
        printf("Determine o vertice inicial: \n");
        x=scanf("%d", &Vinicial);
        larguraG(grafo, Vinicial, grafosVisitados);
      }
      else{
        printf("Opção inválida!\n");
      }
    }
    else if(op==5){
      printf("Desalocando o grafo.\n");
      desalocaG(grafo);
    }
      else if(op==0){
        
      }
    else{
      printf("Opção inválida!\n");
    }
  }
  return 0;
}