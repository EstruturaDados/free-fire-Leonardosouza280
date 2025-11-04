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
#include <stdio.h>
#include <string.h>
#include <stdbool.h> // Necessário para o tipo 'bool'

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
void buscarItemPorNome(); // NOVIDADE

// --- Função Principal (main) ---
int main() {
    int opcao;
    
    // Simulação de alguns itens para teste rápido
    strcpy(mochila[0].nome, "Poção de Vida");
    strcpy(mochila[0].tipo, "Consumível");
    mochila[0].quantidade = 5;
    totalItens++;

    strcpy(mochila[1].nome, "Espada Longa");
    strcpy(mochila[1].tipo, "Arma");
    mochila[1].quantidade = 1;
    totalItens++;


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
            case 4: // NOVO CASO
                buscarItemPorNome();
                break;
            case 5:
                printf("👋 Saindo do programa. Até mais!\n");
                break;
            default:
                printf("❌ Opção inválida. Por favor, escolha uma opção entre 1 e 5.\n");
                break;
        }

        printf("\n--- Pressione ENTER para continuar ---\n");
        // Limpa o buffer para pausar a execução até o ENTER
        while(getchar() != '\n');
        getchar(); 

    } while (opcao != 5);

    return 0;
}

// --- 3. Implementação das Funções ---

/**
 * Exibe o menu de opções no terminal. (Atualizado com a opção Buscar)
 */
void exibirMenu() {
    printf("\n==================================\n");
    printf("🛡️ MOCHILA COM BUSCA (Nível Aventureiro)\n");
    printf("==================================\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item por nome\n");
    printf("3. Listar itens\n");
    printf("4. Buscar item por nome (NOVO)\n");
    printf("5. Sair\n");
    printf("----------------------------------\n");
    printf("Escolha uma opção: ");
}

/**
 * Implementação da Busca Sequencial.
 * Procura um item pelo nome e exibe seus detalhes.
 */
void buscarItemPorNome() {
    if (totalItens == 0) {
        printf("⚠️ A mochila está vazia. Não há itens para buscar.\n");
        return;
    }

    char nomeParaBuscar[50];
    bool encontrado = false; // Flag de controle
    int i;
    
    printf("\n--- Buscar Item por Nome ---\n");
    printf("Digite o nome do item que deseja buscar: ");
    if (scanf(" %[^\n]", nomeParaBuscar) != 1) return;

    // 1. Busca Sequencial
    for (i = 0; i < totalItens; i++) {
        // Usa strcmp() para comparar o nome buscado com o nome do item atual
        // strcmp retorna 0 se as strings forem idênticas
        if (strcmp(mochila[i].nome, nomeParaBuscar) == 0) {
            encontrado = true;
            break; // Sai do loop assim que o item é encontrado
        }
    }

    // 2. Exibição do Resultado
    if (encontrado) {
        printf("\n✨ ITEM ENCONTRADO! ✨\n");
        printf("----------------------------------\n");
        printf("Nome:       %s\n", mochila[i].nome);
        printf("Tipo:       %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
        printf("----------------------------------\n");
    } else {
        printf("❌ Item '%s' não encontrado. Verifique a ortografia.\n", nomeParaBuscar);
    }
}

// --- Funções Reutilizadas do Nível Novato ---

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
#include <stdio.h>
#include <string.h>
#include <stdbool.h> // Para usar o tipo bool

// 1. Definição da Estrutura (struct) para o Item (com a Prioridade)
typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
    int prioridade; // Novo campo: 1 (mais alta) a 5 (mais baixa)
} Item;

// 2. Enumeração para Critérios de Ordenação
typedef enum {
    POR_NOME = 1,
    POR_TIPO,
    POR_PRIORIDADE
} CriterioOrdenacao;

// 3. Constantes e Variáveis Globais
#define MAX_ITENS 10
Item mochila[MAX_ITENS];
int totalItens = 0; 
// Flag de controle: indica se o vetor está ordenado estritamente por NOME
bool ordenadoPorNome = false; 

// --- Protótipos das Funções ---
void exibirMenu();
void exibirMenuOrdenacao();
void adicionarItem();
void listarItens();
void removerItem();
void insertionSort(CriterioOrdenacao criterio);
void buscaBinariaPorNome();

// --- Função Principal (main) ---
int main() {
    int opcao;
    
    // Simulação de alguns itens iniciais (com prioridade)
    strcpy(mochila[0].nome, "Poção de Vida");
    strcpy(mochila[0].tipo, "Consumível");
    mochila[0].quantidade = 5;
    mochila[0].prioridade = 3;
    totalItens++;

    strcpy(mochila[1].nome, "Adaga");
    strcpy(mochila[1].tipo, "Arma");
    mochila[1].quantidade = 1;
    mochila[1].prioridade = 2;
    totalItens++;

    strcpy(mochila[2].nome, "Mapa Antigo");
    strcpy(mochila[2].tipo, "Diversos");
    mochila[2].quantidade = 1;
    mochila[2].prioridade = 5;
    totalItens++;

    // Como adicionamos manualmente, a lista não está garantidamente ordenada
    ordenadoPorNome = false; 

    do {
        exibirMenu();
        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n');
            opcao = -1; 
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
                exibirMenuOrdenacao();
                break;
            case 5: // Busca Binária
                buscaBinariaPorNome();
                break;
            case 6:
                printf("👋 Saindo do programa. Até mais!\n");
                break;
            default:
                printf("❌ Opção inválida. Por favor, escolha uma opção entre 1 e 6.\n");
                break;
        }

        printf("\n--- Pressione ENTER para continuar ---\n");
        while(getchar() != '\n');
        getchar(); 

    } while (opcao != 6);

    return 0;
}

// --- 4. Implementação das Funções do Menu ---

void exibirMenu() {
    printf("\n==================================\n");
    printf("🧠 INVENTÁRIO MESTRE (Prioridade, Ordenação e Busca Binária)\n");
    printf("==================================\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item por nome\n");
    printf("3. Listar itens\n");
    printf("4. Ordenar mochila\n");
    printf("5. Buscar item (Busca Binária por nome)\n");
    printf("6. Sair\n");
    printf("----------------------------------\n");
    printf("Estado da ordenação por nome: %s\n", ordenadoPorNome ? "✅ Sim" : "❌ Não");
    printf("Escolha uma opção: ");
}

void exibirMenuOrdenacao() {
    int escolha;
    printf("\n--- Critério de Ordenação ---\n");
    printf("1. Por Nome\n");
    printf("2. Por Tipo\n");
    printf("3. Por Prioridade\n");
    printf("Escolha o critério (1-3): ");
    
    if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > 3) {
        printf("❌ Critério de ordenação inválido.\n");
        while(getchar() != '\n');
        return;
    }

    insertionSort((CriterioOrdenacao)escolha);
}

/**
 * Adiciona um novo item (com prioridade).
 */
void adicionarItem() {
    if (totalItens >= MAX_ITENS) {
        printf("⚠️ A mochila está cheia! (Capacidade máxima de %d itens).\n", MAX_ITENS);
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n");
    Item novoItem;

    printf("Nome do item: ");
    if (scanf(" %[^\n]", novoItem.nome) != 1) return; 

    printf("Tipo (ex: Arma, Consumível): ");
    if (scanf(" %[^\n]", novoItem.tipo) != 1) return;

    printf("Quantidade: ");
    if (scanf("%d", &novoItem.quantidade) != 1) {
        printf("❌ Entrada inválida para a quantidade.\n");
        while(getchar() != '\n'); 
        return;
    }
    
    // Leitura da Prioridade (NOVO)
    printf("Prioridade (1 a 5, sendo 1 mais alta): ");
    if (scanf("%d", &novoItem.prioridade) != 1 || novoItem.prioridade < 1 || novoItem.prioridade > 5) {
        printf("❌ Prioridade inválida. Item não adicionado.\n");
        while(getchar() != '\n');
        return;
    }

    mochila[totalItens] = novoItem;
    totalItens++;
    
    // Qualquer adição desfaz a ordenação por nome.
    ordenadoPorNome = false; 

    printf("✅ Item '%s' adicionado com sucesso! Total de itens: %d/%d.\n", 
           novoItem.nome, totalItens, MAX_ITENS);
}

/**
 * Lista todos os itens (agora incluindo Prioridade).
 */
void listarItens() {
    if (totalItens == 0) {
        printf("⚠️ A mochila está vazia. Nenhum item cadastrado.\n");
        return;
    }

    printf("\n--- 📜 ITENS NA MOCHILA (%d/%d) 📜 ---\n", totalItens, MAX_ITENS);
    printf("+-----------------------------------------------------------------------------+\n");
    printf("| %-20s | %-15s | %-10s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("+----------------------+-----------------+------------+------------+\n");

    for (int i = 0; i < totalItens; i++) {
        printf("| %-20s | %-15s | %-10d | %-10d |\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade,
               mochila[i].prioridade);
    }

    printf("+----------------------+-----------------+------------+------------+\n");
}

/**
 * Remove um item (similar ao Nível Aventureiro, mas a remoção desfaz a ordenação).
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

    // Busca Sequencial para encontrar o item (necessário para a remoção)
    for (i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeParaRemover) == 0) {
            indiceRemover = i;
            break;
        }
    }

    if (indiceRemover != -1) {
        printf("🗑️ Removendo '%s'...\n", mochila[indiceRemover].nome);
        
        for (i = indiceRemover; i < totalItens - 1; i++) {
            mochila[i] = mochila[i+1];
        }

        totalItens--;
        // Qualquer remoção desfaz a ordenação por nome
        ordenadoPorNome = false; 
        printf("✅ Item removido com sucesso. Total de itens: %d/%d.\n", totalItens, MAX_ITENS);
    } else {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeParaRemover);
    }
}


// --- 5. Funções de Ordenação e Busca ---

/**
 * Implementa o Insertion Sort para ordenar a mochila.
 * Inclui um contador de comparações.
 */
void insertionSort(CriterioOrdenacao criterio) {
    if (totalItens <= 1) {
        printf("⚠️ Não há itens suficientes para ordenar.\n");
        ordenadoPorNome = (criterio == POR_NOME);
        return;
    }

    int i, j;
    Item chave;
    long long comparacoes = 0; // Contador de comparações

    for (i = 1; i < totalItens; i++) {
        chave = mochila[i];
        j = i - 1;

        // Compara e move elementos da mochila[0..i-1] que são maiores
        // (ou menores, dependendo do critério) que a chave.
        while (j >= 0) {
            bool deveMover = false; // Flag para decidir se 'chave' é menor que 'mochila[j]'

            switch (criterio) {
                case POR_NOME:
                    // Se o nome da chave for alfabeticamente menor que o nome do item j
                    if (strcmp(chave.nome, mochila[j].nome) < 0) {
                        deveMover = true;
                    }
                    comparacoes++;
                    break;
                case POR_TIPO:
                    // Se o tipo da chave for alfabeticamente menor que o tipo do item j
                    if (strcmp(chave.tipo, mochila[j].tipo) < 0) {
                        deveMover = true;
                    }
                    comparacoes++;
                    break;
                case POR_PRIORIDADE:
                    // Se a prioridade da chave for MAIS ALTA (menor valor) que a prioridade do item j
                    if (chave.prioridade < mochila[j].prioridade) {
                        deveMover = true;
                    }
                    // Se as prioridades forem iguais, usa o nome como critério de desempate (opcional, mas bom)
                    else if (chave.prioridade == mochila[j].prioridade && strcmp(chave.nome, mochila[j].nome) < 0) {
                        deveMover = true;
                    }
                    comparacoes++;
                    break;
            }

            if (deveMover) {
                mochila[j + 1] = mochila[j];
                j = j - 1;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }

    // Atualiza o estado da ordenação:
    ordenadoPorNome = (criterio == POR_NOME);
    
    printf("✅ Mochila ordenada com sucesso por ");
    if (criterio == POR_NOME) printf("Nome");
    else if (criterio == POR_TIPO) printf("Tipo");
    else if (criterio == POR_PRIORIDADE) printf("Prioridade");
    
    printf(".\n");
    printf("📊 Análise de Desempenho: %lld comparações realizadas.\n", comparacoes);
}


/**
 * Implementa a Busca Binária (binary search) por nome, 
 * exigindo que a lista esteja ordenada por nome.
 */
void buscaBinariaPorNome() {
    if (totalItens == 0) {
        printf("⚠️ A mochila está vazia.\n");
        return;
    }

    if (!ordenadoPorNome) {
        printf("❌ ERRO: A busca binária exige que a mochila esteja ordenada por NOME.\n");
        printf("Por favor, ordene a mochila usando a opção 4 e escolhendo o critério 'Por Nome'.\n");
        return;
    }
    
    char nomeParaBuscar[50];
    printf("\n--- Busca Binária por Nome ---\n");
    printf("Digite o nome do item que deseja buscar: ");
    if (scanf(" %[^\n]", nomeParaBuscar) != 1) return;

    int esquerda = 0;
    int direita = totalItens - 1;
    int resultadoComparacao;
    bool encontrado = false;
    int indiceEncontrado = -1;
    int comparacoes = 0;
    
    // Busca Binária
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        comparacoes++; // Conta a comparação principal

        resultadoComparacao = strcmp(mochila[meio].nome, nomeParaBuscar);

        if (resultadoComparacao == 0) {
            // Item encontrado
            encontrado = true;
            indiceEncontrado = meio;
            break; 
        } else if (resultadoComparacao < 0) {
            // O item está na metade direita (nome buscado > nome no meio)
            esquerda = meio + 1;
        } else {
            // O item está na metade esquerda (nome buscado < nome no meio)
            direita = meio - 1;
        }
    }

    if (encontrado) {
        Item item = mochila[indiceEncontrado];
        printf("\n✨ ITEM ENCONTRADO! (Após %d iterações) ✨\n", comparacoes);
        printf("----------------------------------\n");
        printf("Nome:       %s\n", item.nome);
        printf("Tipo:       %s\n", item.tipo);
        printf("Quantidade: %d\n", item.quantidade);
        printf("Prioridade: %d\n", item.prioridade);
        printf("----------------------------------\n");
    } else {
        printf("❌ Item '%s' não encontrado na mochila. (Após %d iterações)\n", nomeParaBuscar, comparacoes);
    }
}