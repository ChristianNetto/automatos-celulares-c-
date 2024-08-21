#include <iostream>
#include <bitset>
using namespace std;

int regra30(int esquerda, int centro, int direita) {
    // Aplica a regra utilizando XOR e OR
    int proximo_estado = (esquerda ^ (direita | centro));/* & 1: Para garantir que o resultado final 
    seja apenas um bit (0 ou 1), aplica-se uma operação AND com 1. Isso é útil para garantir 
    que proximo_estado seja sempre 0 ou 1, como exigido em autômatos celulares*/

    return proximo_estado;
}

int regra90(int esquerda, int direita) {
    return esquerda ^ direita; //usando o ^(ou excluisivo) para saber os estados das celulas vizinhas à direita e à esquerda.
}

int regra110(int esquerda, int centro, int direita) {
    int padrao = (esquerda << 2) | (centro << 1) | direita;
    // regra dos 110 em binario: 01101110
    switch(padrao) {
        case 0b111: return 0;
        case 0b110: return 1;
        case 0b101: return 1;
        case 0b100: return 0;
        case 0b011: return 1;
        case 0b010: return 1;
        case 0b001: return 1;
        case 0b000: return 0;
    }
    return 0;
}

int regraCustom(int esquerda, int centro, int direita, int numero) {
    // transforma o número fornecido em binário
    bitset<8> bits(numero);
    // concatena os bits e converte para decimal
    int padrao = (esquerda << 2) | (centro << 1) | direita;
    // retorna o bit correspondente ao padrão na regra personalizada
    return bits.test(padrao) ? 1 : 0; //siminilar a condicional, operador ternário
}

void imprimirLinha(const int linha[], int tamanho) {
    for (int i = 0; i < tamanho; ++i) { //itera sobre cada celula da linha
        cout << (linha[i] ? '#' : ' '); //retorna # se a celula é 1, caso nao seja, retorna "(vazio)"
    }
    cout << endl;
}

void puxaDados(int& escolha_regra){
    cout << "Escolha a regra (30, 90, 110 ou um numero(0 a 255) para a regra customizada): ";
    cin >> escolha_regra;
}

int main() {
    const int tamanho = 35; //Tamanho da linha do autômato
    const int geracoes = 15; // Número de gerações a serem geradas
    int escolha_regra; // escolhendo a regra

    puxaDados(escolha_regra);

    // faz a verificação da regra, pra ver se ela é personalizada
    if (escolha_regra < 0 || (escolha_regra > 110 && escolha_regra < 0) || escolha_regra > 255) {
        cout << "Regra customizada escolhida: " << escolha_regra << endl;
    }

    int linha[tamanho] = {0}; //faz com que a linha inicie com o valor 0
    linha[tamanho / 2] = 1; //faz com que a celula central mude para o valor 1

    imprimirLinha(linha, tamanho); //exibe uma geração

    for (int g = 0; g < geracoes; ++g) {
        int novaLinha[tamanho] = {0}; // inicializa nova linha com zeros

        for (int i = 0; i < tamanho; ++i) {
            int esquerda = (i == 0) ? 0 : linha[i - 1];/*faz uma analise se esquerda i for = 0, isso significa que nao há
            celula à esquerda, então, esquerda é definida como 0 ou morta */ 
            int centro = linha[i];/*Esta linha obtém o estado da célula atual (linha[i]), 
            que é a própria célula que estamos considerando.*/
            int direita = (i == tamanho - 1) ? 0 : linha[i + 1];//mesma coisa do que acontece com o esquerda/
            
            int resultado;
            switch(escolha_regra) { // utiliza switch para pegar o que o usuario inseriu e voltar o resultado
                case 30:
                    resultado = regra30(esquerda, centro, direita);
                    break;
                case 90:
                    resultado = regra90(esquerda, direita);
                    break;
                case 110:
                    resultado = regra110(esquerda, centro, direita);
                    break;
                default:
                    resultado = regraCustom(esquerda, centro, direita, escolha_regra);
            }
            novaLinha[i] = resultado;
        }

        for (int i = 0; i < tamanho; ++i) {
            linha[i] = novaLinha[i]; //muda a linha antiga por uma linha nova
        }
        imprimirLinha(linha, tamanho);
    }
}