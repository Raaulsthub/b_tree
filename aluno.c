#include "aluno.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno
{
    int matricula;
    char* nome;
    char* curso;
    int idade;
};


Aluno* criar_aluno()
{
    Aluno* a = (Aluno*) malloc (sizeof(Aluno));
    printf("\n\n Digite  o nome do aluno: ");
    char nome[30];
    scanf("%s[^\n]", nome);
    a->nome = (char*) malloc ((strlen(nome) + 1) * sizeof(char));
    strcpy(a->nome, nome);
    printf("\n Digite a matricula: ");
    scanf("%d", &a->matricula);
    printf("\n Digite a idade: ");
    scanf("%d", &a->idade);
    printf("\nDigite o curso: ");
    char curso[30];
    scanf("%s[^\n]", curso);
    a->curso = (char*) malloc ((strlen(curso) + 1) * sizeof(char));
    strcpy(a->curso, curso);
    return a;
}

int tam_struct() {
    return sizeof(struct aluno);
}


int recuperar_matricula(Aluno* a) {
    return a->matricula;
}
char* recuperar_nome(Aluno* a) {
    return a->nome;
}
int recuperar_idade(Aluno* a) {
    return a->idade;
}
char* recuperar_curso(Aluno* a) {
    return a->curso;
}