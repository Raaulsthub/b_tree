#include <stdio.h>
#include <stdlib.h>

#include "b_tree.h"
#include "aluno.h"

int menu()
{
    int op;
    printf("\n---------------------------------\n");
    printf("\tCADASTRO E BUSCA DE ALUNOS\n");
    printf("---------------------------------\n");
    printf("1 - CADASTRO\n");
    printf("2 - BUSCA\n");
    printf("3 - SAIR\n");
    scanf("%d", &op);
    return op;
}

int main(void)
{
    Arv_b_no alunos = arv_b_cria();
    int op, mat;
    do {
        op = menu();
        switch (op)
        {
        case 1:;
            Aluno* a = criar_aluno();
            arv_insere(alunos, recuperar_matricula(a));
            break;
        case 2:;
            printf("Digite a matricula: ");
            scanf("%d", &mat);
            int achou = arv_b_pos_seek(alunos, mat);
            if (achou == 0)
            {
                printf("Nao achou\n");
            }
            else
            {
                printf("Achou\n");
                printf("%d", achou);
            }
        default:
            break;
        }
    } while (op != 3);
    /*arv_insere(arv, 1);
    arv_insere(arv, 5);
    arv_insere(arv, 6);
    arv_insere(arv, 7);
    arv_insere(arv, 8);
    arv_insere(arv, 9);
    arv_insere(arv, 0);
    arv_insere(arv, 100);
    printf("SIM: %d", arv_b_pos_seek(arv, 1));
    printf("SIM: %d", arv_b_pos_seek(arv, 100));
    printf("SIM: %d", arv_b_pos_seek(arv, 8));
    printf("NAO: %d", arv_b_pos_seek(arv, 60));*/
}