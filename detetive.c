#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50

// -------------------
// Estrutura da sala
// -------------------
typedef struct Sala {
    char nome[MAX_NOME];      // Nome do cômodo
    struct Sala *esquerda;    // Caminho à esquerda
    struct Sala *direita;     // Caminho à direita
} Sala;


// --------------------------------------
// Função: cria uma sala
// --------------------------------------
Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));

    if (nova == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;

    return nova;
}


// --------------------------------------------------------
// Função: permite ao jogador explorar as salas da mansão
// --------------------------------------------------------
void explorarSalas(Sala *atual) {
    char escolha;

    while (atual != NULL) {
        printf("\nVocê está em: **%s**\n", atual->nome);

        // Verifica se é uma folha (sem caminhos)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Não há mais caminhos!\n");
            printf("Exploração encerrada.\n");
            return;
        }

        printf("Escolha um caminho:\n");
        if (atual->esquerda != NULL)  printf("  (e) Esquerda → %s\n", atual->esquerda->nome);
        if (atual->direita != NULL)   printf("  (d) Direita  → %s\n", atual->direita->nome);
        printf("  (s) Sair da exploração\n");
        printf("→ ");

        scanf(" %c", &escolha);

        if (escolha == 'e' || escolha == 'E') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Caminho inexistente! Tente novamente.\n");
            }

        } else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Caminho inexistente! Tente novamente.\n");
            }

        } else if (escolha == 's' || escolha == 'S') {
            printf("Você decidiu sair. Até mais!\n");
            return;
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}


// -------------------
// Função principal
// -------------------
int main() {
    // Montagem da mansão
    // Hall
    Sala *hall = criarSala("Hall de Entrada");

    // Segundo nível
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Cozinha");

    // Terceiro nível
    hall->esquerda->esquerda = criarSala("Biblioteca");
    hall->esquerda->direita = criarSala("Quarto");

    hall->direita->esquerda = criarSala("Jardim");
    hall->direita->direita = criarSala("Escritório");

    printf("\nBem-vindo(a) ao Detective Quest!\n");
    printf("Explore a mansão para encontrar o culpado...\n");

    explorarSalas(hall);

    printf("\nJogo encerrado.\n");
    return 0;
}
