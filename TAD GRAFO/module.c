#include <stdio.h>
#include <stdlib.h>
#include "module.h"

//Define se será digrafo.
#define DIGRAFO 1 

//Definição da struct grafo
struct grafo{
    int pond; //Variável que define se ele será ponderado
    float** pesos; //Se ele for um grafo ponderado,então será uma matriz dinamica que guardará os valores
    int nVertices;  //Número de vertices que o grafo possuirá
    int MaxGrau; //Define quantos graus a vértice pode possuir
    int** arestas; //Guarda as conexões em uma matriz dinâmica
    int* grau; //Guarda o número de ligações já realizadas,sendo guardadas em um vetor 
};

/*Função para criar/alocar o grafo*/
Grafo* criaG(int nVertices,int MaxGrau,int pond){
    Grafo *grafo;
    grafo=(Grafo*) malloc(sizeof(struct grafo));
    
    //Verifica se o grafo foi criado
    if(grafo!=NULL){  
        grafo->nVertices=nVertices;
        grafo->MaxGrau=MaxGrau;
        //Define se o grafo é ponderado ou não
        if(pond!=0)
            grafo->pond=1; //É ponderado
        else
            grafo->pond=0; //Não é ponderado
        //Aloca o vetor de graus que serão as ligações ja feitas
        grafo->grau=(int*) calloc(nVertices,sizeof(int));

        //Criação da matriz dinâmica de arestas 
        grafo->arestas=(int**) malloc(nVertices * sizeof(int*)); //Aloca a primeira linha da matriz
        for(int i=0;i<nVertices;i++)
            grafo->arestas[i]=(int*) malloc(MaxGrau * sizeof(int));//Aloca as próximas linhas da "matriz"

        //Se o grafo for ponderado,então novamente será utilizado uma matriz dinâmica para guardar os pesos de cada aresta
        if(grafo->pond==1){
            grafo->pesos=(float**) malloc(nVertices * sizeof(float*)); //Aloca a primeira linha de vetores
            for(int i=0;i<nVertices;i++)
              grafo->pesos[i]=(float*) malloc(MaxGrau * sizeof(float));//Aloca todo o tamanho que poderá conter os pesos
        }
    }
    return grafo;
}

/*Função que desaloca o grafo*/
void desaloca(Grafo* grafo){
    //Testa se existe o grafo
    if(grafo!=NULL){
        //For para desalocar cada possição da matriz de arestas
        for(int i=0;i<grafo->nVertices;i++)
            free(grafo->arestas[i]);
        free(grafo->arestas);

        //For para desalocar a matriz de pesos
        if(grafo->pond){
            for(int i=0;i<grafo->nVertices;i++)
                free(grafo->pesos[i]);
            free(grafo->pesos);
          }
        free(grafo->grau);//Desaloca o vetor das ligações
        free(grafo);      //Desaloca de fato o grafo
    }
}
/*Função que insere aleatoriamente */
void insere(Grafo* grafo,int GRAU){
    for(int i=0;i<10 + rand() % 30;i++){
        insereA(grafo,rand() % GRAU,rand() % GRAU,DIGRAFO,0);
    }
}

/*Função que adiciona uma nova aresta no grafo alocado */
int insereA(Grafo* grafo,int origem,int destino,int digrafo,float peso){
    //Testa se existe o grafo
    if(grafo==NULL)
        return 0;
    //Verifica se os vertices existem
    if(origem<0||origem>=grafo->nVertices)
        return 0;

    //Verifica se existe o grafo 
    if(destino<0||destino>=grafo->nVertices)
        return 0;

    //Realiza a inserção ao final da matriz determinada pela sua origem
    grafo->arestas[origem][grafo->grau[origem]]=destino;

    //Teste se irá mesmo ser colocada na matriz de pesos
    if(grafo->pond)
        grafo->pesos[origem][grafo->grau[origem]]=peso;
    grafo->grau[origem]++;//Avança para a próxima poosição da matriz

    //Insere outra aresta se não for digrafo
    if(digrafo==0)
        insereA(grafo,destino,origem,1,peso);
    return 1;
}

/*Função de remoção de arestas*/
int removeA(Grafo* grafo,int origem,int destino,int digrafo){
    //Testa se o grafo existe 
    if(grafo==NULL)
        return 0;

    //Verifica se os vertices existem
    if(origem < 0 || origem>=grafo->nVertices)
        return 0;

    //Verifica se existe o grafo
    if(destino<0||destino>=grafo->nVertices)
        return 0;

    //While que busca a aresta que será removida
    int i=0;
    while(i<grafo->grau[origem] && grafo->arestas[origem][i]!=destino)
        i++;
    if(i==grafo->grau[origem])
        return 0;
    grafo->grau[origem]--;	
    grafo->arestas[origem][i]=grafo->arestas[origem][grafo->grau[origem]];

    if(grafo->pond)
        grafo->pesos[origem][i]=grafo->pesos[origem][grafo->grau[origem]];
    if(digrafo==0)
        removeA(grafo,destino,origem,1);
    return 1;
}

/*Função para imprimir o grafo*/
void imprimeG(Grafo *grafo){
    if(grafo==NULL)
        return;
    for(int i=0;i < grafo->nVertices;i++){
        printf("%d: ",i);
        for(int j=0;j < grafo->grau[i];j++){
            if(grafo->pond)
                printf(" %d(%.2f) ",grafo->arestas[i][j],grafo->pesos[i][j]);
            else
                printf(" %d ",grafo->arestas[i][j]);
        }
        printf("\n");
    }
}

/*Funções de busca*/
//Função principal
void profundidadeG(Grafo *grafo,int inicial,int *visitado){
    int cont=1;
    //Laço for que marca os vértices que já forma visitados
    for(int i=0;i<grafo->nVertices;i++)
        visitado[i]=0;
    profundidade(grafo,inicial,visitado,cont);
    printf("Busca em profundidade:\n\n");
    for(int i=0;i<grafo->nVertices;i++)
        printf("%d ->{%d}\n",i,visitado[i]);
}

//Função que define o cálculo determinado para a busca dentro do grafo
void profundidade(Grafo *grafo,int inicial,int *visitado,int cont){
    //Vertice recebera que a aresta já foi visitado,passando dentro do vetor
    visitado[inicial]=cont;
    
    //Parte para a verificação de todos os vizinhos desta vertice
    for(int i=0;i<grafo->grau[inicial];i++){
        //Verificação de se o vértice já foi ou não visitado
        if(!visitado[grafo->arestas[inicial][i]])
            profundidade(grafo,grafo->arestas[inicial][i],visitado,cont+1);
    }
}

/*Busca em largura a partir de um vertice inicial*/

void larguraG(Grafo *grafo,int inicial,int *visitado){
    int vert,n,cont=1;
    int *fila,aux1=0,aux=0;
    for(int i=0;i<grafo->nVertices;i++)
        visitado[i]=0;
    n=grafo->nVertices;
    fila=(int*) malloc(n * sizeof(int));//Fila alocada de forma estática com mesmo tamanho numero de vertices
    aux++;
    fila[aux]=inicial; //Coloca o vertice inicial no final da fila
    visitado[inicial]=cont; //Marca o vertice como visitado

    while(aux1 !=aux){     
        //Recupera o vertice que está no inicio da fila  
        aux1=(aux1 + 1) % n;    
        vert=fila[aux1];
        cont++;
        //Visita todos os vizinhos que ainda não foram visitados
        for(int i=0;i<grafo->grau[vert];i++){
            //Verifica se foram visitados 
            if(!visitado[grafo->arestas[vert][i]]){
                aux=(aux+1)%n;                   
                fila[aux]=grafo->arestas[vert][i];
                visitado[grafo->arestas[vert][i]]=cont; //Marca como visitado
            }
        }
    }
    free(fila); //Desaloca o vetor da fila auxiliar 
    //Mostra na tela o vetor visitado
    printf("Busca em largura:\n\n");
    int i=0;
    for(i=0;i<grafo->nVertices;i++)
        printf("%d ->{%d}\n",i,visitado[i]);
}

//Função que busca pelo menor caminho partir de um vértice inicial.
void mCaminho(Grafo *grafo,int inicial,int *anterior,float *dist){
    int cont,n,ind,*visitado,u;
    cont=n=grafo->nVertices;

    //Vetor auxiliar que armazena as distâncias e seus anteriores
    visitado=(int*) malloc(n * sizeof(int));
    for(int i=0;i<n;i++){
        anterior[i]=-1;
        dist[i]=-1;
        visitado[i]=0;
    }

    dist[inicial]=0;

    while(cont>0){
        u=menorDistancia(dist,visitado,n);
        if(u==-1)
            break;

        visitado[u]=1; //Marca como visitado
        cont--; 
      //Atualiza a distancia
        for(int i=0;i<grafo->grau[u];i++){
            ind=grafo->arestas[u][i];
            if(dist[ind]< 0){
               dist[ind]=dist[u]+1;
               anterior[ind]=u;
            } else{
                if(dist[ind]>dist[u]+1){
                    dist[ind]=dist[u]+1;
                    anterior[ind]=u;
                }
            }
        }
    }

    free(visitado);//Desaloca 
}

//Função que busca os vértices com a menor distancia
int menorDistancia(float *dist,int *visitado,int n){
    int menor=-1,primeiro=1;
    int i=0;
    for(i=0;i<n;i++){
            if(dist[i]>=0 && visitado[i]==0){
            if(primeiro){
                menor=i;
                primeiro=0;
            } else{
                if(dist[menor]>dist[i])
                    menor=i;
            }
        }
    }
    return menor;
}

void  desalocaG (Grafo* grafo){
    //Testa se o grafo existe
    if(grafo != NULL){
        //Desaloca a matriz de arestas
        for(int i=0; i<grafo->nVertices; i++)
            free(grafo->arestas[i]);
        free(grafo->arestas);

        //Desaloca a matriz de pesos
        if(grafo->pond){
            for(int i=0; i<grafo->nVertices; i++)
                free(grafo->pesos[i]);
            free(grafo->pesos);
        }

        free(grafo->grau); //Desaloca o vetor 
        free(grafo);       //Desaloca o grafo
    }
}