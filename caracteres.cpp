#include <cctype>
#include <iostream>

char *le_caracteres(unsigned int n) {
    char *vetor = new char[n];
    for (unsigned int i = 0; i < n; ++i) {
        std::cin >> vetor[i];
    }
    return vetor;
}

unsigned int converte_caracteres(char *vetor, unsigned int n) {
    unsigned int n_conversoes = 0;
    for (unsigned int i = 0; i < n; ++i) {
        // Se for minusculo converte em maiusculo e vice-versa
        if (islower(vetor[i])) {
            vetor[i] = toupper(vetor[i]);
            ++n_conversoes;
        } else if (isupper(vetor[i])) {
            vetor[i] = tolower(vetor[i]);
            ++n_conversoes;
        }
    }
}

void imprime_caracteres(char *vetor, unsigned int n) {
    for (unsigned int i = 0; i < n; ++i) {
        std::cout << vetor[i];
    }
    std::cout << '\n';
}

int main() {
    unsigned int n = 0;
    std::cin >> n >> std::ws;

    char *vetor = le_caracteres(n);
    unsigned n_conversoes = converte_caracteres(vetor, n);
    imprime_caracteres(vetor, n);

    std::cout << "Quantidade de conversoes: " << n_conversoes << '\n';

    delete[] vetor;
}