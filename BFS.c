#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef int bool;
typedef int TIPOPESO;

typedef struct adjacencia
{
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertices{
    /* Outros dados vão aqui*/
    ADJACENCIA *cab;
} VERTICE;

typedef struct grafo
{
    int vertices;
    int arestas;
    VERTICE *adj;
} GRAFO;

typedef struct registro {
    int chave;
} REGISTRO;

typedef struct filaNo {
    REGISTRO reg;
    struct filaNo *prox;
} FILANO;

typedef struct fila {
    FILANO *inicio;
    FILANO *fim;
} FILA;

void inicializarFila(FILA *f){
    f->inicio = f->fim = NULL;
}

void inserirNaFila(FILA *f, REGISTRO r){
    FILANO *n = (FILANO *) malloc(sizeof(FILANO));
    if (!n) return; 
    n->reg = r;
    n->prox = NULL;
    if (!f->fim) {
        f->inicio = n;
    } else {
        f->fim->prox = n;
    }
    f->fim = n;
}

void excluirDaFila(FILA *f, REGISTRO *r){
    if (!f->inicio) return; // fila vazia
    FILANO *t = f->inicio;
    *r = t->reg;
    f->inicio = t->prox;
    if (!f->inicio) f->fim = NULL;
    free(t);
}

/* Protótipo para evitar declaração implícita em largura() */
void visitaL(GRAFO *g, int s, bool *expl);

void largura(GRAFO *g)
{
    // definimos um arranjo que diz se o nó foi ou não explorado
    bool expl[g->vertices];

    int u;
    for (u=0; u<g->vertices; u++)
        expl[u] = false;

    for (u=0; u<g->vertices; u++){
        if (!expl[u]){
            visitaL(g, u, expl);
        }
    }
}

void visitaL(GRAFO *g, int s, bool *expl){

    FILA f;
    inicializarFila(&f);
    expl[s] = true;
    REGISTRO r;
    r.chave = s;
    inserirNaFila(&f, r);

    while (f.inicio)
    {
        excluirDaFila(&f, &r);
        int u = r.chave;
        // aqui marcamos/mostramos o vértice visitado
        printf("Visitando vertice %d\n", u);
        ADJACENCIA *v = g->adj[u].cab;
        while (v){
            if (!expl[v->vertice]){
                expl[v->vertice] = true;
                REGISTRO novo;
                novo.chave = v->vertice;
                inserirNaFila(&f, novo);
            }
            v = v->prox;
        }
    }
}

/*Funções auxiliares para criar grafo e arestas para teste */
GRAFO *criaGrafo(int v){
    GRAFO *g = (GRAFO *) malloc(sizeof(GRAFO));
    if (!g) return NULL;
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE *) malloc(v * sizeof(VERTICE));
    int i;
    for (i = 0; i < v; i++){
        g->adj[i].cab = NULL;
    }
    return g;
}

void criaAresta(GRAFO *g, int origem, int destino, TIPOPESO peso){
    if (!g) return;
    ADJACENCIA *novo = (ADJACENCIA *) malloc(sizeof(ADJACENCIA));
    if (!novo) return;
    novo->vertice = destino;
    novo->peso = peso;
    novo->prox = g->adj[origem].cab;
    g->adj[origem].cab = novo;
    g->arestas++;
}

int main(){
    GRAFO *g = criaGrafo(6);
    criaAresta(g, 0, 1, 1);
    criaAresta(g, 0, 2, 1);
    criaAresta(g, 1, 3, 1);
    criaAresta(g, 1, 4, 1);
    criaAresta(g, 2, 5, 1);

    printf("Iniciando busca em largura:\n");
    largura(g);

    return 0;
}


