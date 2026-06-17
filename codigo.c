#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char caractere;
    char *codigo;
} Code39;

Code39 tabela[] = {
    {'0', "101001101101"}, {'1', "110100101011"},
    {'2', "101100101011"}, {'3', "110110010101"},
    {'4', "101001101011"}, {'5', "110100110101"},
    {'6', "101100110101"}, {'7', "101001011011"},
    {'8', "110100101101"}, {'9', "101100101101"},
    {'A', "110101001011"}, {'B', "101101001011"},
    {'C', "110110100101"}, {'D', "101011001011"},
    {'E', "110101100101"}, {'F', "101101100101"},
    {'G', "101010011011"}, {'H', "110101001101"},
    {'I', "101101001101"}, {'J', "101011001101"},
    {'*', "100101101101"}
};

char* buscarCodigo(char c) {
    int tamanho = sizeof(tabela) / sizeof(tabela[0]);

    for (int i = 0; i < tamanho; i++) {
        if (tabela[i].caractere == c) {
            return tabela[i].codigo;
        }
    }

    return NULL;
}

void gerarCodigoBarras(char texto[]) {
    printf("\nCodigo de barras gerado:\n\n");

    
    printf("%s ", buscarCodigo('*'));

    for (int i = 0; i < strlen(texto); i++) {
        char c = toupper(texto[i]);
        char *codigo = buscarCodigo(c);

        if (codigo != NULL) {
            printf("%s ", codigo);
        } else {
            printf("\nCaractere invalido: %c\n", c);
        }
    }

    printf("%s\n", buscarCodigo('*'));
}

int main() {
    char texto[50];

    printf("Digite uma sequencia com letras A-J ou numeros 0-9: ");
    scanf("%49s", texto);

    gerarCodigoBarras(texto);

    return 0;
}