#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "b_tree.h"

#define ORDEM (4)

struct index{
    int chave;
    int pos_em_arquivo;
};

struct arv_b_no
{
    int folha;   /* esse no eh folha? usado para controle */
    int num_chaves; /* quantas chaves contem */
    Index chaves[ORDEM];
    struct arv_b_no *filhos[ORDEM + 1]; /* filhos tem indices menores q esse no */
};

Arv_b_no arv_b_cria(void)
{
    Arv_b_no b;

    b = malloc(sizeof(*b));
    assert(b);

    b->folha = 1;
    b->num_chaves = 0;

    return b;
}

void arv_b_free(Arv_b_no b)
{
    int i;

    if (!b->folha)
    {
        for (i = 0; i < b->num_chaves + 1; i++)
        {
            arv_b_free(b->filhos[i]);
        }
    }

    free(b);
}

// Essa função retorna o menor index i em um array, onde a chave em [i] eh maior que a chave no argumento
static int
procura_posicao(int n, const Index *a, int chave)
{
    int lo;
    int hi;
    int mid;

    lo = -1;
    hi = n;

    while (lo + 1 < hi)
    {
        mid = (lo + hi) / 2;
        if (a[mid].chave == chave)
        {
            return mid;
        }
        else if (a[mid].chave < chave)
        {
            lo = mid;
        }
        else
        {
            hi = mid;
        }
    }

    return hi;
}

int arv_b_pos_seek(Arv_b_no b, int chave)
{
    int pos;

    if (b->num_chaves == 0)
    {
        return 0;
    }

    // procura chave ou chave maior, para assim procurar em seus filhos
    pos = procura_posicao(b->num_chaves, b->chaves, chave);

    if (pos < b->num_chaves && b->chaves[pos].chave == chave)
    {
        return 1;
    }
    else
    {
        return (!b->folha && arv_b_pos_seek(b->filhos[pos], chave));
    }
}

// Inserir chave em arvore
// retorna no quando pagina splita
// coloca o no do meio em *median
// retorna 0 se nao splita

static Arv_b_no
arv_insere_aux(Arv_b_no b, int chave, int *median)
{
    int pos;
    int mid;
    Arv_b_no b2;

    pos = procura_posicao(b->num_chaves, b->chaves, chave);

    if (pos < b->num_chaves && b->chaves[pos].chave == chave)
    {
        // registro ja na arvore
        return 0;
    }

    if (b->folha)
    {

        // no pai libera indice 0
        memmove(&b->chaves[pos + 1], &b->chaves[pos], sizeof(*(b->chaves)) * (b->num_chaves - pos));
        b->chaves[pos].chave = chave;
        b->num_chaves++;
    }
    else
    {

        // inserir no filho
        b2 = arv_insere_aux(b->filhos[pos], chave, &mid);

        if (b2)
        {

            // no pai libera indice zero movendo todos os indices para i + 1
            memmove(&b->chaves[pos + 1], &b->chaves[pos], sizeof(*(b->chaves)) * (b->num_chaves - pos));
            // no filho vai para a pos 1
            memmove(&b->filhos[pos + 2], &b->filhos[pos + 1], sizeof(*(b->chaves)) * (b->num_chaves - pos));

            b->chaves[pos].chave = mid;
            b->filhos[pos + 1] = b2;
            b->num_chaves++;
        }
    }

    // splitando
    if (b->num_chaves >= ORDEM)
    {
        mid = b->num_chaves / 2;

        *median = b->chaves[mid].chave;

        /* fazer novo no para quando chave eh maior que o numero no meio
        /* se comporta assim:
         *
         *      3 5 7
         *      A B C D
         *
         * vira:
         *          (5)
         *      3        7
         *      A B      C D
         */

        b2 = malloc(sizeof(*b2));

        b2->num_chaves = b->num_chaves - mid - 1;
        b2->folha = b->folha;

        memmove(b2->chaves, &b->chaves[mid + 1], sizeof(*(b->chaves)) * b2->num_chaves);
        if (!b->folha)
        {
            memmove(b2->filhos, &b->filhos[mid + 1], sizeof(*(b->filhos)) * (b2->num_chaves + 1));
        }

        b->num_chaves = mid;

        return b2;
    }
    else
    {
        return 0;
    }
}

void arv_insere(Arv_b_no b, int chave)
{
    Arv_b_no b1; // filho da esquerda
    Arv_b_no b2; // filho da direita
    int median;

    b2 = arv_insere_aux(b, chave, &median);

    if (b2)
    {
        // estamos no no raiz, se for necessario split, precisamos de uma nova raiz
        b1 = malloc(sizeof(*b1));
        assert(b1);

        // copiar raiz para b1
        memmove(b1, b, sizeof(*b));

        // raiz estara apontando pra b1 e b2
        b->num_chaves = 1;
        b->folha = 0;
        b->chaves[0].chave = median;
        b->filhos[0] = b1;
        b->filhos[1] = b2;
    }
}
