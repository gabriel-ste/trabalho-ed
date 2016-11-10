#include <stdio.h>
#include <stdlib.h>

typedef int TipoInfo;

struct TNodoA
{
    TipoInfo info;
    int FB;
    struct TNodoA *esq;
    struct TNodoA *dir;
};
typedef struct TNodoA pNodoA;

/*
    This function is going to be used to initialize the tree
*/
pNodoA* inicializa(void)
{
    return NULL;
}


/*
    Code that applies a simple rotation left to the node
    *function based in the classes presentations
*/

pNodoA* rotacao_esquerda(pNodoA *pt)
{
    pNodoA *ptu;
    ptu = pt->dir;
    pt->dir = ptu->esq;
    ptu->esq = pt;
    pt->FB = 0;
    pt = ptu;
    return pt;
}

/*
    Code that applies a simple right rotation to the node
    *function based in the classes presentations
*/
pNodoA* rotacao_direita(pNodoA* pt)
{
    pNodoA *ptu;
    ptu = pt->esq;
    pt->esq = ptu->dir;
    ptu->dir = pt;
    pt->FB = 0;
    pt = ptu;
    return pt;
}

/*
    Code that applies a double right rotation to the node
    *function based in the classes presentations
*/
pNodoA* rotacao_dupla_direita (pNodoA* pt)
{
    pNodoA *ptu, *ptv;
    ptu = pt->esq;
    ptv = ptu->dir;
    ptu->dir = ptv->esq;
    ptv->esq = ptu;
    pt->esq = ptv->dir;
    ptv->dir = pt;
    if (ptv->FB == 1) pt->FB = -1;
    else pt->FB = 0;
    if (ptv->FB == -1) ptu->FB = 1;
    else ptu->FB = 0;
    pt = ptv;
    return pt;
}

/*
    Code that applies a double left rotation to the node
    *function based in the classes presentations
*/
pNodoA* rotacao_dupla_esquerda (pNodoA *pt)
{
    pNodoA *ptu, *ptv;
    ptu = pt->dir;
    ptv = ptu->esq;
    ptu->esq = ptv->dir;
    ptv->dir = ptu;
    pt->dir = ptv->esq;
    ptv->esq = pt;
    if (ptv->FB == -1) pt->FB = 1;
    else pt->FB = 0;
    if (ptv->FB == 1) ptu->FB = -1;
    else ptu->FB = 0;
    pt = ptv;
    return pt;
}

pNodoA* Caso1 (pNodoA *a, int *ok)
{
    pNodoA *ptu;
    ptu = a->esq;
    if (ptu->FB == 1)
    {
       // printf("fazendo rotacao direita em %d\n",a->info);
        a = rotacao_direita(a);
    }
    else
    {
      //  printf("fazendo rotacao dupla direita em %d\n",a->info);
        a = rotacao_dupla_direita(a);
    }
    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA* Caso2 (pNodoA *a, int *ok)
{
    pNodoA *ptu;
    ptu = a->dir;
    if (ptu->FB == -1)
    {
        //printf("fazendo rotacao esquerda em %d\n",a->info);
        a=rotacao_esquerda(a);
    }
    else
    {
        //printf("fazendo rotacao dupla esquerda em %d\n",a->info);
        a=rotacao_dupla_esquerda(a);
    }
    a->FB = 0;
    *ok = 0;
    return a;
}

/*
    This function is used to insert nodes in to a AVL tree. It ensures that the tree will be with the right factor.
    *function based in the classes presentations
*/

pNodoA* InsereAVL (pNodoA *a, TipoInfo x, int *ok)
{
    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
    x, a chave a ser inserida e h a altura da árvore */
    if (a == NULL)
    {
        a = (pNodoA*) malloc(sizeof(pNodoA));
        a->info = x;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else if (x < a->info)
    {
        a->esq = InsereAVL(a->esq,x,ok);
        if (*ok)
        {
            switch (a->FB)  // testa o valor do fator da raiz da subárvore onde o nodo foi inserido a esquerda
            {
            case -1:            // faz as devidas correções dos fatores
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = 1;
                break;
            case 1:         // se era 1 e foi inserido na esquerda, virou +2. Logo, vamos precisar de rotação:
                a = (pNodoA*) Caso1(a,ok);
                break;
            }
        }
    }
    else
    {
        a->dir = InsereAVL(a->dir,x,ok);
        if (*ok)
        {
            switch (a->FB) // testa o valor do fator da raiz da subárvore onde o nodo foi inserido a direita
            {
            case 1:              // cases fazem as devidas correções dos fatores
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = -1;
                break;
            case -1:    // se era -1 e foi inserido na direita, virou -2. Logo, vamos precisar de rotação;
                a = (pNodoA *) Caso2(a,ok);
                break;
            }
        }
    }
    return a;
}

/*
    The following functions are the in the pattern to print nodes of binary trees.
    *all these functions are based in the classes presentations.
*/
void caminhamento_central_esq(pNodoA *a)
{
    if (a!= NULL)
    {
        caminhamento_central_esq(a->esq);
        printf("%d ",a->info);
        caminhamento_central_esq(a->dir);
    }
}

void caminhamento_central_dir(pNodoA *a)
{
    if (a!= NULL)
    {
        caminhamento_central_dir(a->dir);
        printf("%d ",a->info);
        caminhamento_central_dir(a->esq);
    }
}

void caminhamento_preFixado_esq(pNodoA *a)
{
    if (a!= NULL)
    {
        printf("%d ",a->info);
        caminhamento_preFixado_esq(a->esq);
        caminhamento_preFixado_esq(a->dir);
    }
}

void caminhamento_posFixado_esq(pNodoA *a)
{
    if (a!= NULL)
    {
        caminhamento_posFixado_esq(a->esq);
        caminhamento_posFixado_esq(a->dir);
        printf("%d ",a->info);
    }
}
/*
    This function will print a tree using equals to define the nodes levels.
            developed in laboratory's class.
*/

void caminhamento_preFixado_esq_barras(pNodoA *a, int nivel)
{
    int i;
    if (a!= NULL)
    {
        for(i=0; i<=nivel; i++)
            printf("=");
        printf("%d\n",a->info);
        nivel ++;
        caminhamento_preFixado_esq_barras(a->esq,nivel);
        caminhamento_preFixado_esq_barras(a->dir,nivel);
    }
}


// end of plot functions


// main for testing:
int main()
{
    int *flag;

    pNodoA *a;
    a = inicializa();
    a = InsereAVL(a,10,flag);
    a = InsereAVL(a,2,flag);
    a = InsereAVL(a,3,flag);
    a = InsereAVL(a,11,flag);
    a = InsereAVL(a,20,flag);
    a = InsereAVL(a,31,flag);
    a = InsereAVL(a,58,flag);
    a = InsereAVL(a,37,flag);
    a = InsereAVL(a,34,flag);
    a = InsereAVL(a,25,flag);
    a = InsereAVL(a,0,flag);

    caminhamento_preFixado_esq_barras(a,0);

}
