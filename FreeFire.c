#include <stdio.h>
#include <string.h> // Necessária para usar strcmp (comparar textos)

// Definindo a capacidade máxima da mochila
#define MAX_ITENS 10

// 1. ESTRUTURA DO ITEM (A "Ficha Cadastral")
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// VARIÁVEIS GLOBAIS
Item mochila[MAX_ITENS]; // Vetor que armazena os itens
int totalItens = 0;      // Contador que rastreia quantos itens temos agora

// 2. FUNÇÃO PARA ADICIONAR ITEM (LOOT)
void inserirItem() {
    // Verifica se ainda há espaço no vetor
    if (totalItens < MAX_ITENS) {
        printf("\n--- ADICIONAR NOVO ITEM ---\n");
        
        printf("Nome do Item: ");
        scanf("%s", mochila[totalItens].nome);
        
        printf("Tipo do Item (arma, cura, municao...): ");
        scanf("%s", mochila[totalItens].tipo);
        
        printf("Quantidade: ");
        scanf("%d", &mochila[totalItens].quantidade);

        // Após guardar, aumentamos o contador para a próxima posição
        totalItens++; 
        printf("Item adicionado com sucesso!\n");
    } else {
        // Se o contador chegou em 10, a mochila está cheia
        printf("\nMochila cheia! Voce precisa remover algo para ganhar espaço.\n");
    }
}

// 3. FUNÇÃO PARA REMOVER ITEM
void removerItem() {
    char nomeBusca[30];
    int encontrado = 0;

    if (totalItens == 0) {
        printf("\nA mochila ja esta vazia.\n");
        return;
    }

    printf("\nDigite o nome do item que deseja descartar: ");
    scanf("%s", nomeBusca);

    // Percorre a mochila slot por slot
    for (int i = 0; i < totalItens; i++) {
        // strcmp retorna 0 se os textos forem IGUAIS
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            
            // LOGICA DE REORDENAÇÃO:
            // Se eu removo o item da posição 'i', eu puxo todos os
            // itens da frente uma posição para trás para não deixar buracos.
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            
            totalItens--; // Diminui o total de itens guardados
            encontrado = 1;
            printf("Item '%s' removido com sucesso!\n", nomeBusca);
            break; 
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado na mochila.\n");
    }
}

// 4. FUNÇÃO PARA LISTAR OS ITENS
void listarItens() {
    printf("\n==========================================");
    printf("\n       ITENS NA MOCHILA (%d/%d)", totalItens, MAX_ITENS);
    printf("\n==========================================\n");
    printf("%-15s | %-10s | %s\n", "NOME", "TIPO", "QTD");
    printf("------------------------------------------\n");

    if (totalItens == 0) {
        printf("Mochila vazia. Va buscar loot!\n");
    } else {
        // Percorre o vetor até o limite do nosso contador
        for (int i = 0; i < totalItens; i++) {
            printf("%-15s | %-10s | %d\n", 
                   mochila[i].nome, 
                   mochila[i].tipo, 
                   mochila[i].quantidade);
        }
    }
    printf("==========================================\n");
}

// 5. MENU PRINCIPAL (LOOP DO JOGO)
int main() {
    int opcao;

    do {
        printf("\nMOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 0:
                printf("Saindo do sistema... Ate a proxima partida!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0); // O loop continua até o usuário digitar 0

    return 0;
}
