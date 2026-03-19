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

// Cadastro dos territórios
void cadastrar(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nCadastro do territorio %d\n", i + 1);

        getchar();

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do exercito: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Exibir territórios
void exibir(Territorio *mapa, int n) {
    printf("\n=== TERRITORIOS ===\n");
    for (int i = 0; i < n; i++) {
        printf("\n[%d] %s", i, mapa[i].nome);
        printf("\nCor: %s", mapa[i].cor);
        printf("\nTropas: %d\n", mapa[i].tropas);
    }
}

// Função de ataque
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\nAtaque: %d | Defesa: %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        printf(">>> Atacante venceu!\n");

        // muda dono
        strcpy(defensor->cor, atacante->cor);

        // transfere metade das tropas
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

    } else {
        printf(">>> Defensor venceu!\n");
        atacante->tropas -= 1;

        if (atacante->tropas < 0)
            atacante->tropas = 0;
    }
}

// Liberação de memória
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

int main() {
    int n;

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &n);

    // Alocação dinâmica
    Territorio *mapa = (Territorio *) calloc(n, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    cadastrar(mapa, n);

    int opcao;
    do {
        exibir(mapa, n);

        int a, d;

        printf("\nEscolha o territorio atacante: ");
        scanf("%d", &a);

        printf("Escolha o territorio defensor: ");
        scanf("%d", &d);

        // validação
        if (a < 0 || a >= n || d < 0 || d >= n) {
            printf("Escolha invalida!\n");
            continue;
        }

        if (strcmp(mapa[a].cor, mapa[d].cor) == 0) {
            printf("Nao pode atacar territorio da mesma cor!\n");
            continue;
        }

        atacar(&mapa[a], &mapa[d]);

        printf("\nDeseja continuar? (1 = sim / 0 = nao): ");
        scanf("%d", &opcao);

    } while (opcao == 1);

    liberarMemoria(mapa);

    return 0;
}