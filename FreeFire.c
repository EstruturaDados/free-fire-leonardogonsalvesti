#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==========================================================
// 1. ESTRUTURAS DE DADOS (Conforme os requisitos do Mestre)
// ==========================================================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ==========================================================
// 2. VARIÁVEIS GLOBAIS
// ==========================================================
#define MAX 20
Item mochilaVetor[MAX];
int totalVetor = 0;
No* cabecaLista = NULL;
int comparacoes = 0;

// ==========================================================
// 3. FUNÇÕES DE SUPORTE (INTERFACE)
// ==========================================================

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    printf("\nPressione Enter para continuar...");
    setbuf(stdin, NULL);
    getchar();
    getchar();
}

// ==========================================================
// 4. ALGORITMOS DE ORDENAÇÃO E BUSCA (ESTILO VÍDEO)
// ==========================================================

void bubbleSortNome(Item v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Item temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

void selectionSortPrioridade(Item v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int max = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade > v[max].prioridade) max = j;
        }
        Item temp = v[max];
        v[max] = v[i];
        v[i] = temp;
    }
}

int buscaBinaria(Item v[], int n, char chave[]) {
    int inicio = 0, fim = n - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int res = strcmp(v[meio].nome, chave);
        if (res == 0) return meio;
        if (res < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// ==========================================================
// 5. TELAS DO SISTEMA (IGUAL AO VÍDEO)
// ==========================================================

void mostrarMochilaVetor() {
    printf("\n==========================================");
    printf("\n       ITENS NA MOCHILA (%d/%d)", totalVetor, MAX);
    printf("\n==========================================\n");
    printf("%-15s | %-12s | %-5s | %-5s\n", "NOME", "TIPO", "QTD", "PRIOR");
    printf("------------------------------------------\n");
    for (int i = 0; i < totalVetor; i++) {
        printf("%-15s | %-12s | %-5d | %-5d\n", 
               mochilaVetor[i].nome, mochilaVetor[i].tipo, 
               mochilaVetor[i].quantidade, mochilaVetor[i].prioridade);
    }
    printf("==========================================\n");
}

// ==========================================================
// 6. LOOP PRINCIPAL
// ==========================================================

int main() {
    int opcao, subOpcao;
    char buscaNome[30];

    do {
        limparTela();
        printf("--- CODIGO DA ILHA: DESAFIO MESTRE ---\n");
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Listar Mochila (Inventario)\n");
        printf("3. Estrategia de Ordenacao\n");
        printf("4. Ativar Torre (Busca Binaria)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (totalVetor < MAX) {
                    printf("\n-- NOVO ITEM --\n");
                    printf("Nome: "); scanf("%s", mochilaVetor[totalVetor].nome);
                    printf("Tipo: "); scanf("%s", mochilaVetor[totalVetor].tipo);
                    printf("Qtd: ");  scanf("%d", &mochilaVetor[totalVetor].quantidade);
                    printf("Prioridade (1-10): "); scanf("%d", &mochilaVetor[totalVetor].prioridade);
                    totalVetor++;
                    printf("\nItem adicionado com sucesso!\n");
                } else printf("\nMochila cheia!\n");
                pausar();
                break;

            case 2:
                mostrarMochilaVetor();
                pausar();
                break;

            case 3:
                printf("\n--- ESTRATEGIA DE ORDENACAO ---\n");
                printf("1. Bubble Sort (por Nome)\n2. Selection Sort (por Prioridade)\nEscolha: ");
                scanf("%d", &subOpcao);
                
                clock_t t = clock();
                if (subOpcao == 1) bubbleSortNome(mochilaVetor, totalVetor);
                else selectionSortPrioridade(mochilaVetor, totalVetor);
                t = clock() - t;

                printf("\nOrdenacao concluida!\nComparacoes realizadas: %d\n", comparacoes);
                printf("Tempo: %f seg\n", (double)t/CLOCKS_PER_SEC);
                mostrarMochilaVetor();
                pausar();
                break;

            case 4:
                bubbleSortNome(mochilaVetor, totalVetor); // Busca binária exige ordenação
                printf("\nDigite o componente-chave para ativar a torre: ");
                scanf("%s", buscaNome);
                int pos = buscaBinaria(mochilaVetor, totalVetor, buscaNome);
                if (pos != -1) {
                    printf("\n[SUCESSO] Componente '%s' encontrado! Torre ativada.\n", buscaNome);
                } else {
                    printf("\n[ERRO] Componente essencial nao localizado.\n");
                }
                pausar();
                break;
        }
    } while (opcao != 0);

    return 0;
}
