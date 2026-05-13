#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==========================================================
// 1. ESTRUTURAS DE DADOS
// ==========================================================

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó para a Lista Encadeada (Mochila Dinâmica)
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ==========================================================
// 2. VARIÁVEIS GLOBAIS
// ==========================================================
#define MAX_VETOR 10
Item mochilaVetor[MAX_VETOR]; 
int totalItensVetor = 0;      
No* cabecaLista = NULL;      

int compsSequencial = 0;
int compsBinaria = 0;

// ==========================================================
// 3. FUNÇÕES DO VETOR (SEQUENCIAL)
// ==========================================================

void inserirVetor() {
    if (totalItensVetor >= MAX_VETOR) {
        printf("\n[ALERTA] Mochila cheia!\n");
        return;
    }
    printf("\n-- NOVO ITEM (LOOT VETOR) --\n");
    printf("Nome do Item: "); scanf("%s", mochilaVetor[totalItensVetor].nome);
    printf("Tipo do Item: "); scanf("%s", mochilaVetor[totalItensVetor].tipo);
    printf("Quantidade: ");   scanf("%d", &mochilaVetor[totalItensVetor].quantidade);
    totalItensVetor++;
    printf("\nItem guardado no slot %d do vetor!\n", totalItensVetor);
}

/**
 * REMOVER NO VETOR: Busca o item e rearranja os slots seguintes.
 */
void removerVetor() {
    char nomeRemover[30];
    printf("\nNome do item para remover do VETOR: ");
    scanf("%s", nomeRemover);

    int pos = -1;
    // Primeiro, busca a posição do item
    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeRemover) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Item nao encontrado no vetor.\n");
    } else {
        // Desloca os itens para a esquerda para cobrir o buraco
        for (int j = pos; j < totalItensVetor - 1; j++) {
            mochilaVetor[j] = mochilaVetor[j+1];
        }
        totalItensVetor--;
        printf("Item '%s' removido e vetor reorganizado!\n", nomeRemover);
    }
}

void listarVetor() {
    printf("\n==========================================");
    printf("\n       ITENS NA MOCHILA (VETOR: %d/%d)", totalItensVetor, MAX_VETOR);
    printf("\n==========================================\n");
    printf("%-15s | %-10s | %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("------------------------------------------\n");
    for (int i = 0; i < totalItensVetor; i++) {
        printf("%-15s | %-10s | %d\n", 
               mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
    printf("==========================================\n");
}

void ordenarVetorPorNome() {
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j+1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = temp;
            }
        }
    }
}

void buscarVetor() {
    char nomeBusca[30];
    if (totalItensVetor == 0) { printf("Mochila vazia!\n"); return; }
    printf("\nItem para buscar e comparar: ");
    scanf("%s", nomeBusca);

    compsSequencial = 0;
    int achouSeq = -1;
    for (int i = 0; i < totalItensVetor; i++) {
        compsSequencial++;
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) { achouSeq = i; break; }
    }

    ordenarVetorPorNome();
    compsBinaria = 0;
    int achouBin = -1, inicio = 0, fim = totalItensVetor - 1;
    while (inicio <= fim) {
        compsBinaria++;
        int meio = (inicio + fim) / 2;
        int res = strcmp(mochilaVetor[meio].nome, nomeBusca);
        if (res == 0) { achouBin = meio; break; }
        if (res < 0) inicio = meio + 1; else fim = meio - 1;
    }

    printf("\n--- ANALISE DE BUSCA (VETOR) ---\n");
    if (achouSeq != -1) {
        printf("Item encontrado no slot: %d\n", achouSeq + 1);
        printf("Passos Busca Sequencial: %d\n", compsSequencial);
        printf("Passos Busca Binaria:    %d\n", compsBinaria);
    } else printf("Item inexistente.\n");
}

// ==========================================================
// 4. FUNÇÕES DA LISTA (DINÂMICA)
// ==========================================================

void inserirLista() {
    No* novo = (No*)malloc(sizeof(No));
    printf("\n-- NOVO ITEM (LOOT LISTA) --\n");
    printf("Nome: "); scanf("%s", novo->dados.nome);
    printf("Tipo: "); scanf("%s", novo->dados.tipo);
    printf("Qtd: ");  scanf("%d", &novo->dados.quantidade);
    novo->proximo = cabecaLista;
    cabecaLista = novo;
    printf("\nItem conectado à lista!\n");
}

void listarLista() {
    No* atual = cabecaLista;
    printf("\n==========================================");
    printf("\n       ITENS NA MOCHILA (LISTA DINAMICA)");
    printf("\n==========================================\n");
    printf("%-15s | %-10s | %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("------------------------------------------\n");
    while (atual != NULL) {
        printf("%-15s | %-10s | %d\n", 
               atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void removerLista() {
    char nome[30];
    printf("\nNome para remover da LISTA: ");
    scanf("%s", nome);
    No *atual = cabecaLista, *anterior = NULL;
    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual; atual = atual->proximo;
    }
    if (atual == NULL) { printf("Nao encontrado.\n"); return; }
    if (anterior == NULL) cabecaLista = atual->proximo;
    else anterior->proximo = atual->proximo;
    free(atual);
    printf("Removido e memoria liberada!\n");
}

// ==========================================================
// 5. MAIN
// ==========================================================

int main() {
    int opcao, modo;
    printf("1-VETOR | 2-LISTA: "); scanf("%d", &modo);

    do {
        printf("\n--- MOCHILA DE SOBREVIVENCIA (Modo: %s) ---", (modo == 1) ? "VETOR" : "LISTA");
        printf("\n1. Adicionar | 2. Remover | 3. Listar | 4. Analise | 0. Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: if(modo==1) inserirVetor(); else inserirLista(); break;
            case 2: if(modo==1) removerVetor(); else removerLista(); break;
            case 3: if(modo==1) listarVetor();  else listarLista();  break;
            case 4: if(modo==1) buscarVetor();  else printf("Analise apenas no Vetor.\n"); break;
        }
        if(opcao != 0) { printf("\nPressione Enter..."); setbuf(stdin, NULL); getchar(); getchar(); }
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    } while (opcao != 0);
    return 0;
}
