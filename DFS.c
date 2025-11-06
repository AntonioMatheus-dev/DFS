#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef int bool;
typedef int TIPOPESO;

#define BRANCO 0
#define AMARELO 1
#define VERMELHO 2

typedef struct adjacencia
{
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
}ADJACENCIA;

typedef struct vertices
{
    /* Outros dados vão aqui*/
    ADJACENCIA *cab;
} VERTICE;


typedef struct grafo
{
    int vertices;
    int arestas;
    VERTICE *adj;
}GRAFO;


void visitaP(GRAFO *g, int u, int *cor);

void profundidade(GRAFO *g)
{
    int cor [g->vertices];
    int u;
    for (u = 0; u<g->vertices;u++){
        cor[u] = BRANCO;
    }

    for (u=0; u<g->vertices;u++){
        if (cor[u] == BRANCO){
            visitaP(g, u, cor);
        }
    }
}

void visitaP(GRAFO *g, int u, int *cor){
    //Ao visitar um nó, o marcamos com amarelo
     cor[u] = AMARELO;
     //então visitamos suas adjacencias (arestas (u, v))recursivamente
     ADJACENCIA *v = g->adj[u].cab;
     while (v){
            if (cor[v->vertice] == BRANCO){
                visitaP(g, v->vertice, cor);
            }
            v = v->prox;
     }
     //Após visitar todas as adjacencias, marcamos o nó como vermelho     
     cor[u] = VERMELHO;
     printf("Visitando vertice %d\n", u);
}

GRAFO *criaGrafo(int v){
    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE *)malloc(v * sizeof(VERTICE));
    int i;
    for(i=0; i < v; i++){
        g->adj[i].cab = NULL;
    }
    return g;
}

void criaAresta(GRAFO *g, int origem, int destino, TIPOPESO peso){
    ADJACENCIA *novo = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    novo->vertice = destino;
    novo->peso = peso;
    novo->prox = g->adj[origem].cab;
    g->adj[origem].cab = novo;
    g->arestas++;
}

int main() {
    // Criar um grafo de exemplo com 5 vértices
    GRAFO *g = criaGrafo(5);
    
    // Adicionar algumas arestas
    criaAresta(g, 0, 1, 1);
    criaAresta(g, 0, 2, 1);
    criaAresta(g, 1, 3, 1);
    criaAresta(g, 2, 4, 1);
    
    printf("Iniciando busca em profundidade:\n");
    profundidade(g);
    
    return 0;
}