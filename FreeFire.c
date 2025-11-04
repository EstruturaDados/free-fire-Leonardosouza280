/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>*/

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

//int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

  //  return 0;
//}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
#include <stdio.h>
#include <string.h>

// 1. Definição da Estrutura (struct) para o Item
typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
} Item;

// 2. Constantes e Variáveis Globais
#define MAX_ITENS 10
Item mochila[MAX_ITENS];
int totalItens = 0; // Contador de itens atualmente na mochila

// --- Protótipos das Funções ---
void exibirMenu();
void adicionarItem();
void listarItens();
void removerItem();

// --- Função Principal (main) ---
int main() {
    int opcao;

    do {
        exibirMenu();
        // Leitura da opção
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer de entrada em caso de falha na leitura
            while(getchar() != '\n');
            opcao = -1; // Garante que a opção seja inválida
        }

        printf("\n");

        switch (opcao) {
            case 1:
                adicionarItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                printf("👋 Saindo do programa. Até mais!\n");
                break;
            default:
                printf("❌ Opção inválida. Por favor, escolha uma opção entre 1 e 4.\n");
                break;
        }

        printf("\n--- Pressione ENTER para continuar ---\n");
        // Limpa o buffer para pausar a execução até o ENTER
        while(getchar() != '\n');
        getchar(); 

    } while (opcao != 4);

    return 0;
}

// --- 3. Implementação das Funções ---

/**
 * Exibe o menu de opções no terminal.
 */
void exibirMenu() {
    printf("\n==================================\n");
    printf("🎒 INVENTÁRIO BÁSICO (Nível Novato)\n");
    printf("==================================\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item por nome\n");
    printf("3. Listar itens\n");
    printf("4. Sair\n");
    printf("----------------------------------\n");
    printf("Escolha uma opção: ");
}

/**
 * Adiciona um novo item à mochila, se houver espaço.
 */
void adicionarItem() {
    if (totalItens >= MAX_ITENS) {
        printf("⚠️ A mochila está cheia! (Capacidade máxima de %d itens).\n", MAX_ITENS);
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n");
    Item novoItem;

    // Leitura do Nome
    printf("Nome do item: ");
    // O espaco no scanf eh para ignorar qualquer espaco em branco pendente
    if (scanf(" %[^\n]", novoItem.nome) != 1) return; 

    // Leitura do Tipo
    printf("Tipo (ex: Arma, Consumível): ");
    if (scanf(" %[^\n]", novoItem.tipo) != 1) return;

    // Leitura da Quantidade
    printf("Quantidade: ");
    if (scanf("%d", &novoItem.quantidade) != 1) {
        printf("❌ Entrada inválida para a quantidade.\n");
        while(getchar() != '\n'); // Limpa o buffer
        return;
    }

    // Adiciona o item na próxima posição livre e incrementa o contador
    mochila[totalItens] = novoItem;
    totalItens++;

    printf("✅ Item '%s' adicionado com sucesso! Total de itens: %d/%d.\n", 
           novoItem.nome, totalItens, MAX_ITENS);
}

/**
 * Remove um item da mochila pelo seu nome.
 */
void removerItem() {
    if (totalItens == 0) {
        printf("⚠️ A mochila está vazia. Não há itens para remover.\n");
        return;
    }

    char nomeParaRemover[50];
    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item para remover: ");
    if (scanf(" %[^\n]", nomeParaRemover) != 1) return;
    
    int i, indiceRemover = -1;

    // 1. Busca Sequencial para encontrar o item
    for (i = 0; i < totalItens; i++) {
        // strcmp retorna 0 se as strings forem iguais
        if (strcmp(mochila[i].nome, nomeParaRemover) == 0) {
            indiceRemover = i;
            break;
        }
    }

    if (indiceRemover != -1) {
        // 2. Remoção: Move os itens subsequentes uma posição para trás
        printf("🗑️ Removendo '%s' (Quantidade: %d, Tipo: %s)...\n", 
               mochila[indiceRemover].nome, mochila[indiceRemover].quantidade, 
               mochila[indiceRemover].tipo);
        
        for (i = indiceRemover; i < totalItens - 1; i++) {
            mochila[i] = mochila[i+1];
        }

        // 3. Decrementa o contador de itens
        totalItens--;
        printf("✅ Item removido com sucesso. Total de itens: %d/%d.\n", totalItens, MAX_ITENS);
    } else {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeParaRemover);
    }
}

/**
 * Lista todos os itens atualmente na mochila em formato de tabela.
 */
void listarItens() {
    if (totalItens == 0) {
        printf("⚠️ A mochila está vazia. Nenhum item cadastrado.\n");
        return;
    }

    printf("\n--- 📜 ITENS NA MOCHILA (%d/%d) 📜 ---\n", totalItens, MAX_ITENS);
    printf("+---------------------------------------------------------------------+\n");
    printf("| %-25s | %-15s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("+---------------------------+-----------------+--------------+\n");

    for (int i = 0; i < totalItens; i++) {
        printf("| %-25s | %-15s | %-10d |\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }

    printf("+---------------------------+-----------------+--------------+\n");
}