#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

typedef struct Territorio Territorio;

// ================= MISSÕES =================

// Sorteia missão
void atribuirMissao(char *destino, char *missoes[], int total) {
    int sorteio = rand() % total;
    strcpy(destino, missoes[sorteio]);
}

// Exibe missão (por valor)
void exibirMissao(char *missao) {
    printf("\n=== SUA MISSAO ===\n%s\n\n", missao);
}

// Verifica missão
int verificarMissao(char *missao, Territorio *mapa, int n, char corJogador) {
    int territorios = 0;
    int tropasTotal = 0;
    int territoriosFortes = 0;

    for (int i = 0; i < n; i++) {
        if (strcmp(mapa[i].cor, &corJogador) == 0) {
            territorios++;
            tropasTotal += mapa[i].tropas;

            if (mapa[i].tropas >= 5)
                territoriosFortes++;
        }
    }

    // Missões simples baseadas em texto
    if (strstr(missao, "3 territorios") && territorios >= 3)
        return 1;

    if (strstr(missao, "10 tropas") && tropasTotal >= 10)
        return 1;

    if (strstr(missao, "todos territorios") && territorios == n)
        return 1;

    if (strstr(missao, "2 territorios fortes") && territoriosFortes >= 2)
        return 1;

    if (strstr(missao, "eliminar vermelho")) {
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0)
                return 0;
        }
        return 1;
    }

    return 0;
}

// ================= JOGO =================

void cadastrar(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nCadastro do territorio %d\n", i + 1);

        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf(" %[^\n]", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

void exibir(Territorio *mapa, int n) {
    printf("\n=== TERRITORIOS ===\n");
    for (int i = 0; i < n; i++) {
        printf("\n[%d] %s\n", i, mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\nAtaque: %d | Defesa: %d\n", dadoA, dadoD);

    if (dadoA > dadoD) {
        printf(">>> Atacante venceu!\n");

        strcpy(defensor->cor, atacante->cor);

        int metade = atacante->tropas / 2;
        defensor->tropas = metade;
        atacante->tropas -= metade;

    } else {
        printf(">>> Defensor venceu!\n");
        atacante->tropas--;

        if (atacante->tropas < 0)
            atacante->tropas = 0;
    }
}

void liberarMemoria(Territorio *mapa, char *missao) {
    free(mapa);
    free(missao);
}

// ================= MAIN =================

int main() {
    srand(time(NULL));

    int n;
    printf("Quantos territorios? ");
    scanf("%d", &n);

    Territorio *mapa = calloc(n, sizeof(Territorio));

    // Missões disponíveis
    char *missoes[] = {
        "Conquistar 3 territorios",
        "Ter 10 tropas",
        "Dominar todos territorios",
        "Conquistar 2 territorios fortes",
        "Eliminar vermelho"
    };

    // Alocar missão dinamicamente
    char *missaoJogador = malloc(100 * sizeof(char));

    // Sorteio da missão
    atribuirMissao(missaoJogador, missoes, 5);

    cadastrar(mapa, n);

    // Mostrar missão uma vez
    exibirMissao(missaoJogador);

    int opcao;
    do {
        exibir(mapa, n);

        int a, d;

        printf("\nAtacante: ");
        scanf("%d", &a);

        printf("Defensor: ");
        scanf("%d", &d);

        if (a < 0 || a >= n || d < 0 || d >= n) {
            printf("Escolha invalida!\n");
            continue;
        }

        if (strcmp(mapa[a].cor, mapa[d].cor) == 0) {
            printf("Mesmo exercito!\n");
            continue;
        }

        if (mapa[a].tropas <= 1) {
            printf("Tropas insuficientes!\n");
            continue;
        }

        atacar(&mapa[a], &mapa[d]);

        // Verifica missão
        if (verificarMissao(missaoJogador, mapa, n, mapa[a].cor[0])) {
            printf("\n🏆 MISSAO CUMPRIDA! VOCE VENCEU!\n");
            break;
        }

        printf("\nContinuar? (1/0): ");
        scanf("%d", &opcao);

    } while (opcao == 1);

    liberarMemoria(mapa, missaoJogador);

    return 0;
}