#include <stdio.h>
#include <string.h>

struct Territorio {
    
    char nome[30];
    char cor[10];
    int tropas;
};

int main(){
    struct Territorio territorios[5];
    
    for (int i = 0; i < 5; i++){
        printf("\nCadastro do territorio %d\n", i + 1);
        
        printf("Digite o nome do territorio: ");
        scanf("%s", territorios[i].nome);
        
        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);
        
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }
    
    printf("\n===TERRITORIOS CADASTRADOS===\n");
    
    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }
    return 0;
}
