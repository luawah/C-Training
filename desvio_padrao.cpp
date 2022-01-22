#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>

int *le_vetor(unsigned n) {
    int *vetor = new int[n];
    for (unsigned i = 0; i < n; ++i) {
        std::cin >> vetor[i];
    }
    return vetor;
}

// Imprimir vetor de inteiros
void imprime_vetor(int vetor[], unsigned n) {
    std::cout << "[ ";
    for (unsigned i = 0; i < n; ++i) {
        std::cout << vetor[i];
        if (i < n - 1) {
            std::cout << ", ";
        }
    }
    std::cout << " ]";
    std::cout << '\n';
}
// Imprimir double
void imprime_vetor(double vetor[], unsigned n) {
    std::cout << "[ ";

    // Exibir apenas duas casas decimais apos a virgula
    std::cout << std::fixed << std::setprecision(2);

    for (unsigned i = 0; i < n; ++i) {
        std::cout << vetor[i];
        if (i < n - 1) {
            std::cout << ", ";
        }
    }
    std::cout << " ]";
    std::cout << '\n';
}

double calcula_media(int vetor[], int n) {
    double media = 0;
    for (int i = 0; i < n; ++i) {
        media += vetor[i];
    }
    media /= n;
    return media;
}
double calcula_variancia(int vetor[], int n) {
    double media = calcula_media(vetor, n);
    double variancia = 0;
    for (int i = 0; i < n; ++i) {
        variancia += pow((vetor[i] - media), 2);
    }
    variancia /= n - 1;
    return variancia;
}

double desvio_padrao(int vetor[], int n) {
    double variancia = calcula_variancia(vetor, n);
    double desvio_padrao = sqrt(variancia);
    return desvio_padrao;
}

void calcula_dp(int v1[], double v2[], unsigned n, unsigned k) {
    for (unsigned i = 0, j = 0; i < n; i += k, ++j) {
        // Calcular em um intervalo de v1[i] a v1[i+k]
        v2[j] = desvio_padrao(v1 + i, k);
    }
}

int main() {
    unsigned n = 0, k = 0;
    std::cin >> n >> k >> std::ws;

    // N deve ser divisivel por K
    if (n % k == 0) {
        int *v1 = le_vetor(n);
        double *v2 = new double[n / k];

        calcula_dp(v1, v2, n, k);

        // Imprime vetor de entrada
        std::cout << "v1 = ";
        imprime_vetor(v1, n);

        // Imprime vetor do desvio padrao
        std::cout << "v2 = ";
        imprime_vetor(v2, n / k);

        // Libera memoria
        delete[] v1;
        delete[] v2;
    }

    return 0;
}
