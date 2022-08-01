#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
    printf("%d\n ", (1 && 25));
    Arv_b_no alunos = arv_b_cria();
    int op, mat;
    int pos_seek;

    FILE *arq;

    if (access("alunos.dat", F_OK) == 0)
        arq=fopen("alunos.dat","r+"); // arquivo existe
    else
        arq=fopen("alunos.dat","w+"); // arquivo nao existia
    
    do {
        op = menu();
        switch (op)
        {
        case 1:;
            int al_existe = 0;
            Aluno* a = criar_aluno();
            fseek(arq, 0, SEEK_END);
            pos_seek = ftell(arq);
            arv_b_pos_seek(alunos, recuperar_matricula(a), &al_existe);

            if (al_existe) {
                printf("Matricula ja cadastrada!\n");
                free(a);
            } else {
                printf("%d\n", tam_struct());
                fwrite(&a,tam_struct(),1,arq);

                arv_insere(alunos, recuperar_matricula(a), pos_seek);
            }

            break;
        case 2:;
            Aluno* al;
            int achou = 0;
            printf("Digite a matricula: ");
            scanf("%d", &mat);
            int pos = arv_b_pos_seek(alunos, mat, &achou);

            if(achou == 0) {
                printf("Aluno nao encontrado!\n");
            } else {
                fseek(arq, pos, SEEK_SET);
                fread(&al, tam_struct(), 1, arq);
                printf("Matricula: %d\n", recuperar_matricula(al));
                printf("Nome: %s\n", recuperar_nome(al));
                printf("Idade: %d\n", recuperar_idade(al));
                printf("Curso: %s\n", recuperar_curso(al));
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