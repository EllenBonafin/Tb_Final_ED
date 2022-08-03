#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "module.h"

#define DIGRAFO 1 
//Define se será digrafo.

//Definição do tipo Grafo
struct grafo{
    int ponderado;  //Variável que define se ele será ponderado
    float** pesos;  //Se ele for um grafico ponderado, então será uma matriz dinamica que guardará os valores
    int num_vertices;   //Número de vertices que o grafo possuirá
    int grau_max;  //Define quantos graus a vértice pode possuir
    int** arestas;  //Guarda as conexões em uma matriz dinâmica
    int* grau;  //Guarda o número de ligações já realizadas, sendo guardadas em um vetor 
};

/*Função para criar/alocar o grafo*/
Grafo* cria_grafo(int num_vertices, int grau_max, int ponderado){
    Grafo *gr;
    gr= (Grafo*) malloc(sizeof(struct grafo)); //Aloca a estrutura Grafo
    
    //Verifica foi criada a estrutura
    if(gr!= NULL){  
        gr->num_vertices= num_vertices;
        gr->grau_max= grau_max;
        //Define se o grafo é ponderado ou não
        if(ponderado!= 0)
            gr->ponderado= 1;  //É ponderado
        else
            gr->ponderado= 0;  //Não é ponderado
        //Aloca o vetor de graus que serão as ligações ja feitas
        gr->grau= (int*) calloc(num_vertices,sizeof(int)); 

        //Criação da matriz dinâmica de arestas 
        gr->arestas= (int**) malloc(num_vertices * sizeof(int*));  //Aloca a primeira linha de vetores
        for(int i=0; i<num_vertices; i++)
            gr->arestas[i]= (int*) malloc(grau_max * sizeof(int)); //Aloca as próximas linhas dos vetores com o grau_max passado acima

        //Caso o grafo seja ponderado, teremos novamente a matriz dinâmica para guardarmos os pesos de cada aresta
        if(gr->ponderado== 1){
            gr->pesos= (float**) malloc(num_vertices * sizeof(float*));  //Aloca a primeira linha de vetores
            for(int i=0; i<num_vertices; i++)
              gr->pesos[i]= (float*) malloc(grau_max * sizeof(float)); //Aloca todo o tamanho que poderá conter os pesos
        }
    }
    return gr;
}

/*Função que desaloca o grafo*/
void libera_grafo(Grafo* gr){
    //Testa se o grafo existe mesmo
    if(gr != NULL){
        //For para desalocar cada possição da matriz de arestas
        for(int i=0; i<gr->num_vertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);

        //For para desalocar a matriz de pesos
        if(gr->ponderado){
            for(int i=0; i<gr->num_vertices; i++)
                free(gr->pesos[i]);
            free(gr->pesos);
          }
        free(gr->grau); //Desaloca o vetor das ligações
        free(gr);       //Desaloca de fato o grafo
    }
}
/*Função que insere aleatoriamente */
void insere_aleatorio(Grafo* gr, int GRAU){
    srand(time(NULL));

    for(int i=0; i<10 + rand() % 30; i++){
        insere_aresta(gr, rand() % GRAU, rand() % GRAU, DIGRAFO, 0);
    }
}

/*Função que adiciona uma nova aresta no grafo alocado */
int insere_aresta(Grafo* gr, int origem, int destino, int digrafo, float peso){
    //Testa se o grafo existe mesmo
    if(gr == NULL)
        return 0;
    //Verifica se os vertices existem, sendo que ele não pode ser 0 e nem maior que meu número de vertices
    if(origem < 0 || origem >= gr->num_vertices)
        return 0;

    //Verifica se existe o grafo 
    if(destino < 0 || destino >= gr->num_vertices)
        return 0;

    //Realiza a inserção ao final da matriz determinada pela sua origem
    gr->arestas[origem][gr->grau[origem]] = destino;

    //Teste se irá mesmo ser colocada na matriz de pesos
    if(gr->ponderado)
        gr->pesos[origem][gr->grau[origem]] = peso;
    gr->grau[origem]++; //Avança para a próxima poosição da matriz

    /*Insere outra aresta se não for digrafo, passando de ordem inversa, do destino e da origem*/
    if(digrafo == 0)
        insere_aresta(gr, destino, origem, 1, peso);
    return 1;
}

/*Função de remoção de arestas*/
int remove_aresta(Grafo* gr, int origem, int destino, int digrafo){
    //Testa se o grafo existe mesmo
    if(gr == NULL)
        return 0;

    //Verifica se os vertices existem
    if(origem < 0 || origem >= gr->num_vertices)
        return 0;

    //Verifica se existe o grafo
    if(destino < 0 || destino >= gr->num_vertices)
        return 0;

    //While que busca a aresta que será removida
    int i = 0;
    while(i<gr->grau[origem] && gr->arestas[origem][i]!= destino)
        i++;
    //Caso a condição saia do laço então a aresta não existe.
    if(i == gr->grau[origem])
        return 0;

    //Remove uma aresta e desloca o ultimo valor para frente
    gr->grau[origem]--; 	
    gr->arestas[origem][i]= gr->arestas[origem][gr->grau[origem]];
    
    //Irá fazer a mesma coisa caso seja ponderado o grafo
    if(gr->ponderado)
        gr->pesos[origem][i] = gr->pesos[origem][gr->grau[origem]];

    //Remove outra aresta se não for digrafo
    if(digrafo == 0)
        remove_aresta(gr, destino, origem, 1);
    return 1;
}

/*Função para imprimir o grafo*/
void imprime_grafo(Grafo *gr){
    //Testa se o grafo existe mesmo
    if(gr == NULL)
        return;

    //Laço for que percorre todo o grafo, suas vértices 
    for(int i=0; i < gr->num_vertices; i++){
        printf("%d: ", i);
        for(int j=0; j < gr->grau[i]; j++){
            if(gr->ponderado)
                printf("{%d(%.2f)} ", gr->arestas[i][j], gr->pesos[i][j]);
            else
                printf("{%d} ", gr->arestas[i][j]);
        }
        printf("\n");
    }
}

//Funções de busca
//Função principal
void busca_profundidade_grafo(Grafo *gr, int inicial, int *visitado){
    int cont = 1;

    //Laço for que marca os vértices que já forma visitados
    for(int i=0; i<gr->num_vertices; i++)
        visitado[i] = 0;

    //Chama a função de busca
    busca_profundidade(gr, inicial, visitado, cont);

    //Mostra na tela a busca realizada
    printf("Busca em profundidade:\n\n");
    for(int i=0; i<gr->num_vertices; i++)
        printf("%d -> {%d}\n",i ,visitado[i]);
}

//Função que define o cálculo determinado para a busca dentro do grafo
void busca_profundidade(Grafo *gr, int inicial, int *visitado, int cont){
    //Vertice recebera que a aresta já foi visitado, passando dentro do vetor
    visitado[inicial] = cont;
    
    //Parte para a verificação de todos os vizinhos desta vertice
    for(int i=0; i<gr->grau[inicial]; i++){
        //Verificação de se o vértice já foi ou não visitado
        if(!visitado[gr->arestas[inicial][i]])
            busca_profundidade(gr,gr->arestas[inicial][i],visitado,cont+1);
    }
}

/*Busca em largura parti de um vértice inicial, explorando todos os vértice vizinhos, em seguida para todos
  os vértices vizinhos repetira o processo, assim olhando todos que estão inexplorado
  - Usado para achar componentes conectados, achar todos os vertices conectado, achar o menor caminho
    testar bipartição em grafo*/

void busca_largura_grafo(Grafo *gr, int inicial, int *visitado){
    int vert, NV, cont= 1;
    int *fila, IF= 0, FF= 0;  //IF: inicio da fila, FF: final da fila

    //Marca todos os vértices como não visitados
    for(int i=0; i<gr->num_vertices; i++)
        visitado[i] = 0;

    //Cria uma fila para armazenar a ordem em que os vértices foram visitados
    NV = gr->num_vertices;
    fila = (int*) malloc(NV * sizeof(int)); //Fila alocada de forma estática com mesmo tamanho numero de vertices
    FF++;
    fila[FF] = inicial;  //Coloca o vertice inicial no final da fila
    visitado[inicial] = cont;  //Marca o vertice como visitado

    while(IF != FF){     
        //Recupera o vertice que está no inicio da fila  
        IF = (IF + 1) % NV;     
        vert = fila[IF];
        cont++;

        //Visita todos os vizinhos que ainda não foram visitados e coloca na fila alocada
        for(int i=0; i<gr->grau[vert]; i++){
            //Verifica se foram visitados ou não
            if(!visitado[gr->arestas[vert][i]]){
                FF = (FF + 1) % NV;                     //Adiciona ele na fila
                fila[FF] = gr->arestas[vert][i];
                visitado[gr->arestas[vert][i]] = cont;  //Marca como visitado no vetor
            }
        }
    }
    free(fila);  //Desaloca o vetor da fila auxiliar 

    //Mostra na tela o vetor visitado
    printf("Busca em largura:\n\n");
    for(int i=0; i < gr->num_vertices; i++)
        printf("%d -> {%d}\n", i, visitado[i]);
}

//Função que busca pelo menor caminho partir de um vértice inicial e calcula a menor distância deste vértice a todos os demais, desde que exista um caminho entre eles.
void menor_caminho_grafo(Grafo *gr, int inicial, int *anterior, float *distancia){
    int cont, NV, ind, *visitado, u;
    cont= NV= gr->num_vertices;

    //Vetor auxiliar para armazenar as distâncias e seus anteriores
    visitado = (int*) malloc(NV * sizeof(int));
    for(int i=0; i < NV; i++){
        anterior[i] = -1;
        distancia[i] = -1;
        visitado[i] = 0;
    }

    distancia[inicial] = 0;

    while(cont > 0){
        u = procura_menor_distancia(distancia, visitado, NV);
        if(u == -1)
            break;

        visitado[u] = 1;  //Marca como visitado
        cont--;  //Visitado mais um vertice por isso decrementa

        //Atualiza a nova distancia dos vizinhos
        for(int i=0; i<gr->grau[u]; i++){
            ind= gr->arestas[u][i];
            if(distancia[ind]< 0){
               distancia[ind]= distancia[u]+1;
               anterior[ind]= u;
            } else{
                if(distancia[ind]>distancia[u]+1){
                    distancia[ind]= distancia[u]+1;
                    anterior[ind]= u;
                }
            }
        }
    }

    free(visitado); //Desaloca o vetor auxiliar
}

//Função que busca os vértices com a menor distancia e que ainda não tenham sido visitados.
int procura_menor_distancia(float *distancia, int *visitado, int NV){
    int menor=-1, primeiro=1;
    
    for(int i=0; i<NV; i++){
            if(distancia[i]>=0 && visitado[i]==0){
            if(primeiro){
                menor= i;
                primeiro= 0;
            } else{
                if(distancia[menor]>distancia[i])
                    menor= i;
            }
        }
    }
    return menor;
}
