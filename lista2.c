#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXSIZE 10

typedef struct Aluno {
    char nome[20];
    int matricula;
    float nota;
} Aluno;

typedef struct ListaAlunos {
    Aluno alunos[MAXSIZE];
    int numElem;
} ListaAlunos;

void preencheAluno(Aluno* ptrAluno, int matricula, float nota, char* nome) {
    (*ptrAluno).matricula = matricula;
    (*ptrAluno).nota = nota;
    strcpy((*ptrAluno).nome, nome);
}

void inicializaLista(ListaAlunos* listaAlunos) {
    listaAlunos->numElem = 0;
}

void exibeLista(ListaAlunos* listaAlunos) {
    int index;
    printf("Exibindo lista...\n");
    for (index = 0; index < listaAlunos->numElem; index++) {
        printf("Aluno %d\n", index);
        printf("Nome: %s\n", listaAlunos->alunos[index].nome);
        printf("Matricula: %d\n", listaAlunos->alunos[index].matricula);
        printf("Nota: %.1f\n", listaAlunos->alunos[index].nota);
    }
}

// Função de comparação para a busca binária
int compareAluno(const void* a, const void* b) {
    return strcmp(((Aluno*)a)->nome, ((Aluno*)b)->nome);
}

// Inserção ordenada em ordem alfabética
bool insereAlunoEmOrdem(ListaAlunos* listaAlunos, Aluno aluno) {
    if (listaAlunos->numElem >= MAXSIZE) {
        printf("Insercao em posicao invalida!!!\n");
        return false;
    }

    int posicao = 0;
    while (posicao < listaAlunos->numElem && strcmp(aluno.nome, listaAlunos->alunos[posicao].nome) > 0) {
        posicao++;
    }

    for (int index = listaAlunos->numElem; index > posicao; index--) {
        listaAlunos->alunos[index] = listaAlunos->alunos[index - 1];
    }
    listaAlunos->alunos[posicao] = aluno;
    listaAlunos->numElem++;
    return true;
}

// Busca sequencial por nome de aluno com sentinela
int buscaAlunoPorNome(ListaAlunos* listaAlunos, char* nome) {
    strcpy(listaAlunos->alunos[listaAlunos->numElem].nome, nome); // Usando sentinela
    int i = 0;
    while (strcmp(listaAlunos->alunos[i].nome, nome) != 0) {
        i++;
    }
    if (i == listaAlunos->numElem) {
        return -1; // Nome não encontrado
    } else {
        return i;
    }
}

// Busca binária pelo nome dos alunos
int buscaBinariaPorNome(ListaAlunos* listaAlunos, char* nome) {
    Aluno alunoProcurado;
    strcpy(alunoProcurado.nome, nome);
    Aluno* result = bsearch(&alunoProcurado, listaAlunos->alunos, listaAlunos->numElem, sizeof(Aluno), compareAluno);
    if (result != NULL) {
        return result - listaAlunos->alunos;
    } else {
        return -1; // Nome não encontrado
    }
}

int main() {
    ListaAlunos listaAlunos;
    inicializaLista(&listaAlunos);

    Aluno aluno0, aluno1, aluno2;
    preencheAluno(&aluno0, 15424242, 9.5, "Joao");
    preencheAluno(&aluno1, 10101011, 10, "Ana");
    preencheAluno(&aluno2, 22222222, 7, "Bia");

    insereAlunoEmOrdem(&listaAlunos, aluno0);
    insereAlunoEmOrdem(&listaAlunos, aluno1);
    insereAlunoEmOrdem(&listaAlunos, aluno2);

    exibeLista(&listaAlunos);

    // Teste das novas funcionalidades
    int posicaoNome = buscaAlunoPorNome(&listaAlunos, "Ana");
    if (posicaoNome != -1) {
        printf("Aluno encontrado por nome:\n");
        printf("Nome: %s\n", listaAlunos.alunos[posicaoNome].nome);
        printf("Matricula: %d\n", listaAlunos.alunos[posicaoNome].matricula);
        printf("Nota: %.1f\n", listaAlunos.alunos[posicaoNome].nota);
    } else {
        printf("Aluno nao encontrado por nome.\n");
    }

    int posicaoNomeBinaria = buscaBinariaPorNome(&listaAlunos, "Bia");
    if (posicaoNomeBinaria != -1) {
        printf("Aluno encontrado por busca binaria por nome:\n");
        printf("Nome: %s\n", listaAlunos.alunos[posicaoNomeBinaria].nome);
        printf("Matricula: %d\n", listaAlunos.alunos[posicaoNomeBinaria].matricula);
        printf("Nota: %.1f\n", listaAlunos.alunos[posicaoNomeBinaria].nota);
    } else {
        printf("Aluno nao encontrado por busca binaria por nome.\n");
    }

    return 0;
}
