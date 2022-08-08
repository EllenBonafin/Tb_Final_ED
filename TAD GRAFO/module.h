/*Função usada pra criar o grafo*/
typedef struct grafo Grafo;

/*Função que inicializa o grafo*/
Grafo* criaG(int nVertices, int MaxGrau, int pond);

/*Função que desaloca o grafo*/
void desalocaG(Grafo* grafo);

/*Função que realiza a inserção aleatóriamente*/
int insereA(Grafo* grafo, int origem, int destino, int digrafo, float peso);

/*Função de remoção*/
int removeA(Grafo* grafo, int origem, int destino, int digrafo);

/*Função de impressão*/
void imprimeG(Grafo *grafo);

/*Funções de busca do grafo*/
void profundidade(Grafo *grafo, int inicial, int *visitado, int cont);
void profundidadeG(Grafo *grafo, int inicial, int *visitado);
void larguraG(Grafo *grafo, int inicial, int *visitado);
int menorDistancia(float *distancia, int *visitado, int n);
void mCaminho(Grafo *grafo, int inicial, int *anterior, float *distancia);

//Insere valores aleatórios
void insere(Grafo* grafo, int GRAU);