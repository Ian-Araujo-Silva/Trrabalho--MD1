#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *tabelaA[] = {
    "0001101", "0011001", "0010011", "0111101", "0100011",
    "0110001", "0101111", "0111011", "0110111", "0001011"
};

char *tabelaB[] = {
    "0100111", "0110011", "0011011", "0100001", "0011101",
    "0111001", "0000101", "0010001", "0001001", "0010111"
};

char *tabelaC[] = {
    "1110010", "1100110", "1101100", "1000010", "1011100",
    "1001110", "1010000", "1000100", "1001000", "1110100"
};

char *padraoInicial[] = {
    "AAAAAA", "AABABB", "AABBAB", "AABBBA", "ABAABB",
    "ABBAAB", "ABBBAA", "ABABAB", "ABABBA", "ABBABA"
};

int calcularDigitoVerificador(char codigo[]) {
    int soma = 0;

    for (int i = 0; i < 12; i++) {
        int digito = codigo[i] - '0';

        if (i % 2 == 0)
            soma += digito * 1;
        else
            soma += digito * 3;
    }

    int resto = soma % 10;

    if (resto == 0)
        return 0;
    else
        return 10 - resto;
}

int codigoValido(char codigo[]) {
    if (strlen(codigo) != 12)
        return 0;

    for (int i = 0; i < 12; i++) {
        if (!isdigit(codigo[i]))
            return 0;
    }

    return 1;
}

void gerarEAN13(char codigo[]) {
    char bits[200] = "";
    int primeiroDigito = codigo[0] - '0';

    strcat(bits, "101");

    for (int i = 1; i <= 6; i++) {
        int digito = codigo[i] - '0';

        if (padraoInicial[primeiroDigito][i - 1] == 'A')
            strcat(bits, tabelaA[digito]);
        else
            strcat(bits, tabelaB[digito]);
    }

    strcat(bits, "01010");

    for (int i = 7; i <= 12; i++) {
        int digito = codigo[i] - '0';
        strcat(bits, tabelaC[digito]);
    }

    strcat(bits, "101");

    printf("\nRepresentacao em bits do EAN-13:\n");
    printf("%s\n", bits);
}

int main() {
    char codigo[14];

    printf("Digite os 12 primeiros digitos do EAN-13: ");
    scanf("%13s", codigo);

    if (!codigoValido(codigo)) {
        printf("\nErro: digite exatamente 12 numeros.\n");
        return 1;
    }

    int digitoVerificador = calcularDigitoVerificador(codigo);

    codigo[12] = digitoVerificador + '0';
    codigo[13] = '\0';

    printf("\nDigito verificador calculado: %d\n", digitoVerificador);
    printf("Codigo EAN-13 completo: %s\n", codigo);

    gerarEAN13(codigo);

    return 0;

    /* Professor acredito que esqueci de falar sobre a estrutura dele em bits.
    No padrão EAN-13 existem sequências fixas chamadas guardas. O código sempre começa com 101, que indica o inicio da leitura.
    No centro existe a sequência 01010, que separa a parte esquerda da parte direita do código. Por fim, o código termina com 101, 
    indicando ao leitor onde a leitura deve ser encerrada.
    Essas sequências não representam números do produto, mas servem para orientar o scanner durante a leitura.*/
}
