#include <stdio.h>
#include <stdlib.h>
#include "module.h"

#define DIGRAFO 1 
//Define se será digrafo.

int main(void) {
  //Variáveis para as vertices e o grau.
  int vertices, grau;
  
  //Variável utilizada para operações 
  int op=6,op2=0;

  //Variável para definir em qual vertice começará a busca
  int vertice_inicial;
  int origem, destino, test;

  //Variável utilizada para  buscas em profundidade e de largura
  int visitados[vertices];  
  int anterior[vertices];
  float distancia[vertices];
  
  //Definição de quantas vertices o grafo possuirá
  printf("Defina a quantidade de vértices o grafo possuirá: \n");
    scanf("%d", &vertices);
  
    //Definição do grau 
    printf("Defina a quantidade de graus o grafo possuirá: \n");
     scanf("%d", &grau);
  //Alocando um grafo
  Grafo* gr = cria_grafo (vertices, grau, 0 );

  //Insere aletóriamente um valor de vértices no grafo
  insere_aleatorio(gr, grau);

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
  scanf("%d",&op);
    if(op==1){
      //chama função.
      imprime_grafo(gr);
    }
    else if(op==2){
      printf("Determine sua origem: ");
      scanf("%d", &origem);
      printf("Determine seu destino: ");
      scanf("%d", &destino);
      //chama função.
      insere_aresta(gr, origem, destino, DIGRAFO, 0);
    }
    else if(op==3){
        printf("Determine sua origem: ");
        scanf("%d", &origem);
        printf("Determine seu destino: ");
        scanf("%d", &destino);
      //chama função.
        remove_aresta(gr, origem, destino, DIGRAFO);  
    }
    else if (op==4){
      //Menu para escolher a forma de busca desejada
      printf("Busca dentro do grafo:\n\n");
      printf("1 - Procurar o menor caminho\n");
      printf("2 - Busca em profundidade\n");
      printf("3 - Busca em largura\n");
      printf("Digite a opção escolhida: \n");
      scanf("%d",&op2);
      if(op2==1){
        printf("Procura o menor caminho:\n");
        printf("\nDetermine o vertice inicial: ");
        scanf("%d", &vertice_inicial);
        //chama função.
        menor_caminho_grafo(gr, vertice_inicial, anterior, distancia);    
        //If/else apenas para deixa indexado o código na hora do print
        for(int i=0; i<grau; i++)
            if(anterior[i] < 0)
            printf("%d: %d -> {%.2f}\n", i, anterior[i], distancia[i]);
            else
            printf("%d:  %d -> {%.2f}\n", i, anterior[i], distancia[i]);
      }
      else if(op2==2){
        printf("Busca em profundidade:\n");
        printf("\nDetermine o vertice inicial: ");
        scanf("%d", &vertice_inicial);
        //chama função.
        busca_profundidade_grafo(gr, vertice_inicial, visitados);
        
      }
      else if(op2==3){
        printf("Busca em profundidade:\n");
        printf("\nDetermine o vertice inicial: ");
        scanf("%d", &vertice_inicial);
        //chama função.
        busca_largura_grafo(gr, vertice_inicial, visitados);
      }
      else{
        printf("Opção inválida!\n");
      }
    }
    else if(op==5){
      printf("Desalocando o grafo.\n");
      libera_grafo(gr);
    }
    else{
      printf("Opção inválida!\n");
    }
  }
  return 0;
}