#include <cmath>
#include <ctime>
#include <iostream>

struct Data {
    unsigned dia, mes, ano;
};
struct DadosEntrada {
    Data data_nascimento;
    double valor_patrimonio;
    double valor_emprestimo;
    unsigned qtde_meses_pagamento;
};

DadosEntrada le_dados() {
    DadosEntrada dados = {};
    std::cin >> dados.data_nascimento.dia;
    std::cin >> dados.data_nascimento.mes;
    std::cin >> dados.data_nascimento.ano;
    std::cin >> dados.valor_patrimonio;
    std::cin >> dados.valor_emprestimo;
    std::cin >> dados.qtde_meses_pagamento;
    return dados;
}

Data obter_data_atual() {
    Data data = {};
    time_t t = time(NULL);
    struct tm lt = *localtime(&t);
    data.ano = (unsigned)lt.tm_year + 1900;
    data.mes = (unsigned)lt.tm_mon + 1;
    data.dia = (unsigned)lt.tm_mday;
    return data;
}
unsigned calcula_idade(Data data_nascimento) {
    Data data_atual = obter_data_atual();

    if (data_nascimento.dia > data_atual.dia) {
        data_atual.mes -= 1;
        data_atual.dia += 30;
    }
    if (data_nascimento.mes > data_atual.mes) {
        data_atual.ano -= 1;
        data_atual.mes += 12;
    }

    Data data_diferenca = {data_atual.dia - data_nascimento.dia,
                           data_atual.mes - data_nascimento.mes,
                           data_atual.ano - data_nascimento.ano};

    unsigned idade_dias = data_diferenca.dia + data_diferenca.mes * 30 + data_diferenca.ano * 365;
    return idade_dias / 365; // Idade em anos
}

unsigned fator_de_risco(unsigned idade, double valor_patrimonio) {
    unsigned fator = 0;
    if (idade > 18) {
        if (idade < 30) {
            fator = 3;
        } else if (idade < 50) {
            fator = 6;
        } else if (idade < 60) {
            fator = 9;
        } else {
            fator = 12;
        }
    }

    if (valor_patrimonio < 50000.0) {
        fator += 2;
    } else if (valor_patrimonio < 200000.0) {
        fator += 1;
    } else if (valor_patrimonio < 100000000.0) {
        fator -= 1;
    } else {
        fator -= 2;
    }

    return fator;
}

double calcula_juros(unsigned fator_risco) {
    return 1.8 + (fator_risco * 0.2);
}
double calcula_mensalidade(double valor_emprestimo, double juros_mensais, double qtde_meses) {
    double qtde_anos = qtde_meses / 12;
    double mensalidade = (valor_emprestimo * pow(1 + juros_mensais, qtde_anos)) / qtde_meses;
    return mensalidade;
}

double calcula_juros_mensalidade(DadosEntrada dados, double *juros_resultado) {
    unsigned idade = calcula_idade(dados.data_nascimento);
    unsigned fator_risco = fator_de_risco(idade, dados.valor_patrimonio);
    *juros_resultado = calcula_juros(fator_risco);
    return calcula_mensalidade(dados.valor_emprestimo, *juros_resultado, dados.qtde_meses_pagamento);
}

bool validar_data(Data data) {
    bool valida = false;
    if (data.mes >= 1 && data.mes <= 12) {
        if ((data.dia >= 1 && data.dia <= 31) && (data.mes == 1 || data.mes == 3 || data.mes == 5 || data.mes == 7 || data.mes == 8 || data.mes == 10 || data.mes == 12)) {
            valida = true;
        } else if ((data.dia >= 1 && data.dia <= 30) && (data.mes == 4 || data.mes == 6 || data.mes == 9 || data.mes == 11)) {
            valida = true;
        } else if ((data.dia >= 1 && data.dia <= 28) && data.mes == 2) {
            valida = true;
        } else if (data.dia == 29 && data.mes == 2 && (data.ano % 400 == 0 || (data.ano % 4 == 0 && data.ano % 100 != 0))) {
            valida = true;
        } else {
            valida = false;
        }
    }
    return valida;
}

int main() {
    DadosEntrada dados = le_dados();

    if (validar_data(dados.data_nascimento)) {
        unsigned idade = calcula_idade(dados.data_nascimento);
        unsigned fator_risco = fator_de_risco(idade, dados.valor_patrimonio);
        double juros_mes = 0;
        double mensalidade = calcula_juros_mensalidade(dados, &juros_mes);

        std::cout << "Fator de risco: " << fator_risco << '\n';
        std::cout << "Juros ao mes: " << juros_mes << "%\n";
        std::cout << "Mensalidade: R$" << mensalidade << '\n';
    }
}