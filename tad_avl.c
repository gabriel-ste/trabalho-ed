#include <stdio.h>
#include <stdlib.h>

struct tNodoA
{
    int info;
    struct tNodoA *esq;
    struct tNodoA *dir;
};
typedef struct tNodoA pNodoA;

pNodoA* rotacao_esquerda(pNodoA *pt)
{
	pNodoA *ptu;
	test
	ptu = pt->dir;
	pt->dir = ptu->esq;
	ptu->esq = pt;
	pt = ptu;
return pt;
} 