#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definições de constantes para o tamanho das estruturas
#define TAM_FILA 5
#define TAM_PILHA 3

// Struct Peca:
// Define os atributos básicos de uma peça no jogo.
typedef struct {
    char nome; // Representa o tipo: 'I', 'O', 'T', 'L'
    int id;    // Identificador único gerado sequencialmente
} Peca;

// Variáveis Globais para controle das estruturas
Peca fila[TAM_FILA];
Peca pilha[TAM_PILHA];

// Controle da Fila Circular
int inicioFila = 0;
int fimFila = 0;
int qtdeFila = 0;

// Controle da Pilha (topo = -1 indica pilha vazia)
int topoPilha = -1;

// Controle de IDs
int proximoId = 0;

// --- Protótipos das Funções ---
void inicializarFila();
void inicializarPilha();
Peca gerarPeca();
void adicionarPecaFila(Peca p); // Enqueue
Peca removerPecaFila();         // Dequeue
int pilhaCheia();
int pilhaVazia();
void pushPilha(Peca p);
Peca popPilha();
void exibirEstado();
void jogarPeca();
void reservarPeca();
void usarPecaReserva();
void trocarPecaTopoFrente();
void trocarBloco3();

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

int main() {
    // Inicialização da aleatoriedade
    srand(time(NULL));

    // Inicialização das estruturas
    inicializarFila(); // Já preenche a fila com 5 peças iniciais
    inicializarPilha();

    int opcao;

    do {
        exibirEstado();

        printf("\n--- MENU DE ACOES ---\n");
        printf("1 - Jogar peca da frente da fila\n");
        
        // 🧩 Nível Novato: Fila de Peças Futuras
        // (Funcionalidade básica de jogar implementada na opção 1)

        // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
        printf("2 - Enviar peca da fila para a reserva (pilha)\n");
        printf("3 - Usar peca da reserva (remover do topo)\n");

        // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
        printf("4 - Trocar peca da frente com topo da pilha\n");
        printf("5 - Trocar 3 primeiros da fila com os 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        printf("\n--------------------------------------------------\n");

        switch (opcao) {
            case 1:
                jogarPeca();
                break;
            case 2:
                reservarPeca();
                break;
            case 3:
                usarPecaReserva();
                break;
            case 4:
                // - Implemente interações avançadas entre as estruturas:
                // - Para a opção 4:
                // Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
                // Troque os elementos diretamente nos arrays.
                trocarPecaTopoFrente();
                break;
            case 5:
                // - Para a opção 5:
                // Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
                // Use a lógica de índice circular para acessar os primeiros da fila.
                trocarBloco3();
                break;
            case 0:
                printf("Encerrando o Tetris Stack. Ate logo!\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

// Função auxiliar para gerar peças aleatórias
Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.nome = tipos[rand() % 4];
    p.id = proximoId++;
    return p;
}

// 🧩 Nível Novato: Implementação da Fila

void inicializarFila() {
    inicioFila = 0;
    fimFila = 0;
    qtdeFila = 0;
    // Preenche a fila inicial
    for (int i = 0; i < TAM_FILA; i++) {
        adicionarPecaFila(gerarPeca());
    }
}

void adicionarPecaFila(Peca p) {
    if (qtdeFila < TAM_FILA) {
        fila[fimFila] = p;
        fimFila = (fimFila + 1) % TAM_FILA;
        qtdeFila++;
    }
}

Peca removerPecaFila() {
    Peca p = fila[inicioFila];
    inicioFila = (inicioFila + 1) % TAM_FILA;
    qtdeFila--;
    return p;
}

// Ação 1: Jogar (Remove da fila e repõe automaticamente)
void jogarPeca() {
    if (qtdeFila > 0) {
        Peca p = removerPecaFila();
        printf(">> Voce jogou a peca: [%c %d]\n", p.nome, p.id);
        
        // Reposição automática
        Peca nova = gerarPeca();
        adicionarPecaFila(nova);
        printf(">> Nova peca gerada e adicionada ao final da fila: [%c %d]\n", nova.nome, nova.id);
    }
}

// 🧠 Nível Aventureiro: Implementação da Pilha

void inicializarPilha() {
    topoPilha = -1;
}

int pilhaCheia() {
    return topoPilha == TAM_PILHA - 1;
}

int pilhaVazia() {
    return topoPilha == -1;
}

void pushPilha(Peca p) {
    if (!pilhaCheia()) {
        topoPilha++;
        pilha[topoPilha] = p;
    }
}

Peca popPilha() {
    Peca p = pilha[topoPilha];
    topoPilha--;
    return p;
}

// Ação 2: Reservar (Move da fila para a pilha)
void reservarPeca() {
    if (pilhaCheia()) {
        printf("ERRO: A Pilha de reserva esta cheia! Nao e possivel reservar.\n");
    } else {
        // Remove da fila
        Peca p = removerPecaFila();
        // Coloca na pilha
        pushPilha(p);
        printf(">> Peca [%c %d] movida para a reserva.\n", p.nome, p.id);
        
        // Reposição automática na fila
        Peca nova = gerarPeca();
        adicionarPecaFila(nova);
        printf(">> Fila reabastecida com: [%c %d]\n", nova.nome, nova.id);
    }
}

// Ação 3: Usar Reserva (Remove da pilha)
void usarPecaReserva() {
    if (pilhaVazia()) {
        printf("ERRO: A Pilha de reserva esta vazia!\n");
    } else {
        Peca p = popPilha();
        printf(">> Voce usou a peca da reserva: [%c %d]\n", p.nome, p.id);
    }
}

// 🔄 Nível Mestre: Integração e Trocas

// Ação 4: Troca Simples (Frente Fila <-> Topo Pilha)
void trocarPecaTopoFrente() {
    if (pilhaVazia()) {
        printf("ERRO: Pilha vazia. Impossivel trocar.\n");
        return;
    }
    // Como a fila é reiniciada automaticamente, ela nunca está vazia neste design, 
    // mas por segurança verifica-se:
    if (qtdeFila == 0) {
        printf("ERRO: Fila vazia.\n");
        return;
    }

    // Realiza a troca direta
    Peca temp = fila[inicioFila];
    fila[inicioFila] = pilha[topoPilha];
    pilha[topoPilha] = temp;

    printf(">> SUCESSO: Peca da frente da fila trocada com o topo da pilha.\n");
}

// Ação 5: Troca em Bloco (3 Primeiros Fila <-> 3 da Pilha)
void trocarBloco3() {
    // Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    if (qtdeFila < 3) {
        printf("ERRO: Fila nao possui pecas suficientes para troca tripla.\n");
        return;
    }
    if (topoPilha < 2) { // Índice 2 significa 3 elementos (0, 1, 2)
        printf("ERRO: Pilha precisa estar cheia (3 pecas) para troca tripla.\n");
        return;
    }

    printf(">> Realizando troca multipla (3 pecas)...\n");

    // Loop para trocar 3 elementos
    // A pilha é linear (acessamos 2, 1, 0)
    // A fila é circular (acessamos inicio, inicio+1, inicio+2 com módulo)
    for (int i = 0; i < 3; i++) {
        int indiceFila = (inicioFila + i) % TAM_FILA; // Lógica circular
        int indicePilha = topoPilha - i;              // Topo para baixo

        Peca temp = fila[indiceFila];
        fila[indiceFila] = pilha[indicePilha];
        pilha[indicePilha] = temp;
    }
    printf(">> SUCESSO: Troca de bloco realizada.\n");
}

// Função de Visualização
void exibirEstado() {
    printf("\n=== ESTADO ATUAL ===\n");
    
    // Exibir Fila
    printf("Fila de pecas:\t");
    if (qtdeFila == 0) {
        printf("[ VAZIA ]");
    } else {
        int i = inicioFila;
        for (int cont = 0; cont < qtdeFila; cont++) {
            printf("[%c %d] ", fila[i].nome, fila[i].id);
            i = (i + 1) % TAM_FILA;
        }
    }
    printf("\n");

    // Exibir Pilha
    printf("Pilha de reserva (Topo -> Base): ");
    if (pilhaVazia()) {
        printf("[ VAZIA ]");
    } else {
        for (int i = topoPilha; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
    }
    printf("\n");
}