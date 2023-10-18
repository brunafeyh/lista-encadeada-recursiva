#include <stdio.h>
#include <stdlib.h>

typedef int TipoItem;

typedef struct No {
    TipoItem info;
    struct No *prox;
} Lista;

int vazia(Lista *l) {
    return (l == NULL);
}

void limpar_lista(Lista *l) {
    if (l != NULL) {
        Lista *aux = l->prox;
        free(l);
        limpar_lista(aux);
    }
}

Lista *inserir(Lista *l, TipoItem info) {
    if (vazia(l)) {
        l = (Lista *)malloc(sizeof(Lista));
        l->info = info;
        l->prox = NULL;
        return l;
    }
    l->prox = inserir(l->prox, info);
    return l;
}

Lista *remover(Lista *l, TipoItem info) {
    if (!vazia(l)) {
        if (l->info == info) {
            Lista *temp = l;
            l = l->prox;
            free(temp);
        } else {
            l->prox = remover(l->prox, info);
        }
    } else {
        printf("Elemento não encontrado!\n");
    }

    return l;
}

void imprimir(Lista *l) {
    if (l != NULL) {
        printf("%d ", l->info);
        imprimir(l->prox);
    }
}

Lista *inverter(Lista *l) {
    Lista *aux;

    if (vazia(l)) {
        aux = NULL;
    } else {
        aux = inverter(l->prox);
        aux = inserir(aux, l->info);
    }

    return aux;
}

Lista *concatenar(Lista *l1, Lista *l2) {
    Lista *aux = NULL;

    if (!vazia(l1)) {
        aux = inserir(aux, l1->info);
        aux->prox = concatenar(l1->prox, l2);
    }
    if (vazia(l1) && !vazia(l2)) {
        aux = inserir(aux, l2->info);
        aux->prox = concatenar(l1, l2->prox);
    }

    return aux;
}

Lista *intercalar(Lista *l1, Lista *l2) {
    Lista *aux = NULL;

    if (!vazia(l1) && !vazia(l2)) {
        aux = inserir(aux, l1->info);
        aux = inserir(aux, l2->info);
        aux->prox->prox = intercalar(l1->prox, l2->prox);
    } else {

        if (vazia(l1)) {
            aux = concatenar(aux, l2);
        } else if (vazia(l2)) {
            aux = concatenar(aux, l1);
        }

    }

    return aux;
}

int main() {
    Lista *l1 = NULL;
    Lista *l2 = NULL;
    Lista *l3 = NULL;
    Lista *l4 = NULL;
    Lista *l5 = NULL;

    l1 = inserir(l1, 1);
    l1 = inserir(l1, 2);
    l1 = inserir(l1, 3);
    l1 = inserir(l1, 4);
    l1 = inserir(l1, 5);

    printf("Lista: ");
    imprimir(l1);
    printf("\n");

    l1 = remover(l1, 3);
    l1 = remover(l1, 5);

    printf("Lista após remoção: ");
    imprimir(l1);
    printf("\n");

    l2 = inserir(l2, 0);
    l2 = inserir(l2, 2);
    l2 = inserir(l2, 4);
    l2 = inserir(l2, 6);
    l2 = inserir(l2, 8);

    l3 = inverter(l2);

    printf("Lista original: ");
    imprimir(l2);
    printf("\n");

    printf("Lista após inversão: ");
    imprimir(l3);
    printf("\n");

    l4 = concatenar(l1, l3);
    printf("Lista após concatenar: ");
    imprimir(l4);
    printf("\n");

    l5 = intercalar(l1, l3);
    printf("Lista após intercalar: ");
    imprimir(l5);
    printf("\n");

    limpar_lista(l1);
    limpar_lista(l2);
    limpar_lista(l3);
    limpar_lista(l4);
    limpar_lista(l5);
    l1 = NULL;
    l2 = NULL;
    l3 = NULL;
    l4 = NULL;
    l5 = NULL;

    return 0;
}
