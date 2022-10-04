#include <iostream>
#include <cstdio>
#include <new>
using namespace std;
#define infinito 10000000

struct node{
    int data;
    float weight;
    node *next;

    void dataInput(int d, float w){
        data = d;
        weight = w;
        next = NULL;
    }
};

struct grafo{
    node **list;
    
    grafo(int n){
        node **aux = new(nothrow) node*[n];
        list = aux;
    }
    void inicializares(int n){
        for(int i = 0; i < n; i++){
            list[i] = NULL;
        }
    }
    void add(int v1, int v2, float w){
        node *noh = new(nothrow) node;
        noh->dataInput(v2, w);
        noh->next = list[v1];
        list[v1] = noh;
    }
    void printall(int n){
        for(int i = 0; i < n; i++){
            node *aux = list[i];
            while(aux != NULL){
                aux = aux->next;
            }
        }
    }
};
int remover(float *vetor,int *pai, int n){
    int menor = 0;
    for(int i = 0; i<n; i++){
        if(vetor[i]<vetor[menor] and pai[i] != -1){
            menor = i;
        }
    }
    return menor;
}
int main(){
    int edges; // N° de vértices
    scanf("dl\nformat=edgelist1\nn=%d\ndata:\n", &edges); //entrada padrão
    grafo *g = new grafo(edges); // criar grafo que vai armazenar tudo
    g->inicializares(edges);
    int edge1, edge2; //vértices que vamos receber
    float weight; //peso da aresta
    while(scanf("\n%d %d %f", &edge1, &edge2, &weight ) == 3){
        g->add(edge1 - 1, edge2 - 1, weight); //adicionando vértices a lista de adjacencia
        g->add(edge2 - 1, edge1 - 1, weight); //adicionando vértices a lista de adjacencia
    }

    float *vetor = new float[edges];
    int *pai = new int[edges];
    for(int i = 0; i < edges; i++){
        vetor[i] = infinito;
        pai[i] = -2;
    }
    int m = 0;
    pai[0] = 0;
    while(m < edges){
        int vertice = remover(vetor, pai, edges);
        
        pai[vertice] = -1;
        node *aux = g->list[vertice];
        while(aux!=NULL){
            if(pai[aux->data] != -1 and aux->weight < vetor[aux->data]){
                pai[aux->data] = vertice;
                vetor[aux->data] = aux->weight;
            }
            aux = aux->next;
        }
        m++;
    }
    float soma = 0;
    for (int i = 1; i < edges; i ++ ){
        soma+=vetor[i];
    }
    printf("%.3f", soma);
}

//NAO ESTA ADICIONANDO TUDO QUE DEVIA (TODAS AS ARESTAS)