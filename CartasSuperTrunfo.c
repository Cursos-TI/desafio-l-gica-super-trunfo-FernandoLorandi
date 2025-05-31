#include <stdio.h>

// Uso de struct para criar uma "classe" de carta
typedef struct {
    char estado;
    char codigoCarta[50];
    char nomeCidade[50];
    double populacao;
    double area;
    double pib;
    int pontosTuristicos;
} CartaSuperTrunfo;

//Função de comparação normal
int compararCartas(double a, double b) {
    if (a > b) {
        return 1;
    } else if (b > a) {
        return 2;
    } else {
        return 0; // Empate
    }
}

//Função de comparação inversa
int compararCartasInverso(double a, double b) {
    if (a < b) {
        return 1;
    } else if (b < a) {
        return 2;
    } else {
        return 0; // Empate
    }
}


//Função para calcular a densidade populacional;
double densidadePopulacional(double populacao, double area) {
    double densidade = populacao / area;
    return densidade;
}

//Função para calcular o Pib per Capito;
double pibPerCapita(double pib, double populacao) {
    double perCapita = (pib * 1000000000) / populacao;
    return perCapita;
}

//Função para calcular o superpoder
double calculaSuperPoder(CartaSuperTrunfo carta) {
    double perCapita = pibPerCapita(carta.pib, carta.populacao);
    double inversoDensidade = carta.area / carta.populacao;

    double superPoder = ((carta.populacao / 1000000.0) +
                         (carta.area) +
                         (carta.pib) +
                         carta.pontosTuristicos +
                         (perCapita / 10.0) +
                         (inversoDensidade * 10000000.0)) / 10;

    return superPoder;
}

//Função de inserção de dados, recebe a referência da struct para de cartas e a posição dos dados no array;
void cadastroDeCartas(CartaSuperTrunfo cartas[], int i) {
    printf("\nCadastro de carta #0%d:\n", i);
    printf("Selecione um estado (A-H): ");
    scanf(" %c", &cartas[i].estado);
    printf("Selecione um código de caracteres (1-4): ");
    scanf("%49s", cartas[i].codigoCarta);
    printf("Digite o nome da cidade: ");
    fscanf(stdin, " %49[^\n]", cartas[i].nomeCidade);
    printf("Informe a população: ");
    scanf("%lf", &cartas[i].populacao);
    printf("Informe a área (em Km²): ");
    scanf("%lf", &cartas[i].area);
    printf("Informe o PIB (em bilhões): ");
    scanf("%lf", &cartas[i].pib);
    printf("Informe o número de pontos turísticos: ");
    scanf("%d", &cartas[i].pontosTuristicos);

    return;
}

//Função de impressão dos dados, recebe a referência da struct para de cartas e a posição dos dados no array;
void impressaoDeCartas(CartaSuperTrunfo cartas[], int i) {
    printf("\nResumo #%02d:\n", i);
    printf("Código: %c0%s\n", cartas[i].estado, cartas[i].codigoCarta);
    printf("Cidade: %s\n", cartas[i].nomeCidade);
    printf("População: %.2f habitantes\n", cartas[i].populacao);
    printf("Área: %.2f Km²\n", cartas[i].area);
    printf("PIB: %.2f bilhões de reais\n", cartas[i].pib);
    printf("Número de pontos turísticos: %d\n", cartas[i].pontosTuristicos);

    double densidade = densidadePopulacional(cartas[i].populacao, cartas[i].area);
    double perCapita = pibPerCapita(cartas[i].pib, cartas[i].populacao);
    double inversoDensidade = cartas[i].area / cartas[i].populacao;
    double superPoder = calculaSuperPoder(cartas[i]);

    printf("Densidade populacional: %.2f habitantes por Km²\n", densidade);
    printf("PIB per Capita: %.2f reais\n", perCapita);
    printf("Inverso da Densidade: %.6f Km² por habitante\n", inversoDensidade);
    printf("Super Poder da cidade: %.2f\n", superPoder);

    return;
}

// Função para escolher as cartas (versão corrigida)
void escolhaDeCarta(int *primeiroAtributo, int *segundoAtributo) {
    printf("\n--------------------- Escolha de atributos ------------------------------\n");
    printf("\nEscolha dois atributos que deseja comparar: \n");
    printf(
        "\n1 - População\n2 - Área\n3 - PIB\n4 - Pontos Turísticos\n5 - Densidade\n6 - PIB per Capita\n7 - Super Poder");

    // Primeiro atributo
    do {
        printf("\nPrimeiro atributo (1-7): ");
        scanf("%d", primeiroAtributo);
        if (*primeiroAtributo < 1 || *primeiroAtributo > 7) {
            printf("Opção inválida! Digite um número entre 1 e 7.\n");
        }
    } while (*primeiroAtributo < 1 || *primeiroAtributo > 7);

    // Segundo atributo
    do {
        printf("Segundo atributo (1-7): ");
        scanf("%d", segundoAtributo);
        if (*segundoAtributo < 1 || *segundoAtributo > 7) {
            printf("Opção inválida! Digite um número entre 1 e 7.\n");
        }
        if (*segundoAtributo == *primeiroAtributo) {
            printf("O segundo atributo deve ser diferente do primeiro!\n");
        }
    } while (*segundoAtributo < 1 || *segundoAtributo > 7 || *segundoAtributo == *primeiroAtributo);
}


int main() {
    //Chama a struck e passa 3 arrays.
    //Ignorei a posição 0 para não existir nenhuma carta com "ID" #00;
    CartaSuperTrunfo cartas[3];

    printf("\n----------------------- Cadastro de cartas ---------------------------\n");
    cadastroDeCartas(cartas, 1);
    cadastroDeCartas(cartas, 2);

    printf("\n---------------------- Impressão das cartas -----------------------\n");
    impressaoDeCartas(cartas, 1);
    impressaoDeCartas(cartas, 2);


    int attr1, attr2;
    escolhaDeCarta(&attr1, &attr2);
    printf("\nAtributos escolhidos: %d e %d\n", attr1, attr2);

    int atributosSelecionados[2] = {attr1, attr2};

    printf("\n-----------------------  Hora do duelo  ---------------------------\n");

    for (int i = 0; i < 2; i++) {
    int resultado = 0;
    switch (atributosSelecionados[i]) {
        case 1: {
            double val1 = cartas[1].populacao;
            double val2 = cartas[2].populacao;
            resultado = compararCartas(val1, val2);
            if (resultado == 0) {
                printf("Empate na População!\n");
            } else {
                double valorVencedor = (resultado == 1) ? val1 : val2;
                printf("Vencedor População: Carta (%d) - Valor: %.2f\n", resultado, valorVencedor);
            }
            break;
        }
        case 2: {
            double val1 = cartas[1].area;
            double val2 = cartas[2].area;
            resultado = compararCartas(val1, val2);
            if (resultado == 0) {
                printf("Empate na Área!\n");
            } else {
                double valorVencedor = (resultado == 1) ? val1 : val2;
                printf("Vencedor Área: Carta (%d) - Valor: %.2f\n", resultado, valorVencedor);
            }
            break;
        }
        case 3: {
            double val1 = cartas[1].pib;
            double val2 = cartas[2].pib;
            resultado = compararCartas(val1, val2);
            if (resultado == 0) {
                printf("Empate no PIB!\n");
            } else {
                double valorVencedor = (resultado == 1) ? val1 : val2;
                printf("Vencedor PIB: Carta (%d) - Valor: %.2f\n", resultado, valorVencedor);
            }
            break;
        }
        case 4: {
            int val1 = cartas[1].pontosTuristicos;
            int val2 = cartas[2].pontosTuristicos;
            resultado = compararCartas(val1, val2);
            if (resultado == 0) {
                printf("Empate nos Pontos Turísticos!\n");
            } else {
                int valorVencedor = (resultado == 1) ? val1 : val2;
                printf("Vencedor Pontos Turísticos: Carta (%d) - Valor: %d\n", resultado, valorVencedor);
            }
            break;
        }
        case 5: {
            double dens1 = cartas[1].populacao / cartas[1].area;
            double dens2 = cartas[2].populacao / cartas[2].area;
            resultado = compararCartasInverso(dens1, dens2);
            if (resultado == 0) {
                printf("Empate na Densidade!\n");
            } else {
                double valorVencedor = (resultado == 1) ? dens1 : dens2;
                printf("Vencedor Densidade: Carta (%d) - Valor: %.2f habitantes/Km²\n", resultado, valorVencedor);
            }
            break;
        }
        case 6: {
            double perCapita1 = pibPerCapita(cartas[1].pib, cartas[1].populacao);
            double perCapita2 = pibPerCapita(cartas[2].pib, cartas[2].populacao);
            resultado = compararCartas(perCapita1, perCapita2);
            if (resultado == 0) {
                printf("Empate no PIB per Capita!\n");
            } else {
                double valorVencedor = (resultado == 1) ? perCapita1 : perCapita2;
                printf("Vencedor PIB per Capita: Carta (%d) - Valor: %.2f\n", resultado, valorVencedor);
            }
            break;
        }
        case 7: {
            double sp1 = calculaSuperPoder(cartas[1]);
            double sp2 = calculaSuperPoder(cartas[2]);
            resultado = compararCartas(sp1, sp2);
            if (resultado == 0) {
                printf("Empate no Super Poder!\n");
            } else {
                double valorVencedor = (resultado == 1) ? sp1 : sp2;
                printf("Vencedor Super Poder: Carta (%d) - Valor: %.2f\n", resultado, valorVencedor);
            }
            break;
        }
        default:
            printf("Atributo inválido.\n");
            resultado = 0;
            break;
    }
}


    return 0;
}
