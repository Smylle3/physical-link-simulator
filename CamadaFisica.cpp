#include <iostream>
#include "CamadaFisica.hpp"

using namespace std;

void CamadaDeAplicacaoTransmissora(string mensagem)
{
    int quadro[mensagem.length()];
    for (int i = 0; i < mensagem.length(); i++)
    {
        quadro[i] = mensagem[i];
    }
    CamadaFisicaTransmissora(quadro);
}

void CamadaFisicaTransmissora(int quadro[])
{
    int tipoDeCodificacao = 0; // Mudar de acordo com o teste
    int *fluxoBrutoDeBits;     // Trabalhar com BITS

    switch (tipoDeCodificacao)
    {
    case 0: // Codificação binária
        fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
        break;
    case 1: // Codificação manchester
        fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
        break;
    case 2: // Codificação bipolar
        fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
        break;
    default:
        cout << "ERROR" << endl;
        break;
    }

    MeioDeComunicacao(fluxoBrutoDeBits);
} // fim do método CamadaFisicaTransmissora

int *CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[])
{
    cout << "Codificação Binária" << endl;
    // Implemente a codificação binária e retorne o fluxo bruto de bits como um ponteiro
    int *fluxoBrutoDeBits = nullptr; // Exemplo: inicialize o ponteiro como nulo
    // Faça as operações necessárias para codificar o quadro e atribuir o resultado a 'fluxoBrutoDeBits'
    return fluxoBrutoDeBits;
}

int *CamadaFisicaTransmissoraCodificacaoManchester(int quadro[])
{
    cout << "Codificação Manchester" << endl;
    // Implemente a codificação Manchester e retorne o fluxo bruto de bits como um ponteiro
    int *fluxoBrutoDeBits = nullptr; // Exemplo: inicialize o ponteiro como nulo
    // Faça as operações necessárias para codificar o quadro e atribuir o resultado a 'fluxoBrutoDeBits'
    return fluxoBrutoDeBits;
}

int *CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[])
{
    cout << "Codificação Bipolar" << endl;
    // Implemente a codificação bipolar e retorne o fluxo bruto de bits como um ponteiro
    int *fluxoBrutoDeBits = nullptr; // Exemplo: inicialize o ponteiro como nulo
    // Faça as operações necessárias para codificar o quadro e atribuir o resultado a 'fluxoBrutoDeBits'
    return fluxoBrutoDeBits;
}

void MeioDeComunicacao(int fluxoBrutoDeBits[]) // Metodo que simula a transmissão de informações de um pontoA para um pontoB
{
    int *fluxoBrutoDeBitsPontoA, *fluxoBrutoDeBitsPontoB;

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    int tamanho = sizeof(fluxoBrutoDeBits) / sizeof(fluxoBrutoDeBits[0]); // Obter o tamanho do array

    fluxoBrutoDeBitsPontoB = new int[tamanho]; // Alocar memória para o array fluxoBrutoDeBitsPontoB

    for (int i = 0; i < tamanho; i++)
    {
        fluxoBrutoDeBitsPontoB[i] = fluxoBrutoDeBitsPontoA[i]; // Copiar os elementos de fluxoBrutoDeBitsPontoA para fluxoBrutoDeBitsPontoB
    }

    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);

    delete[] fluxoBrutoDeBitsPontoB; // Liberar a memória alocada para o array fluxoBrutoDeBitsPontoB
} // fim do metodo MeioDeComunicacao

void CamadaFisicaReceptora(int quadro[])
{
    int tipoDeDecodificacao = 0; // Alterar de acordo com o teste
    int *fluxoBrutoDeBits;       // TRABALHAR COM BITS

    switch (tipoDeDecodificacao)
    {
    case 0: // Decodificação binária
        fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBinaria(quadro);
        break;
    case 1: // Decodificação Manchester
        fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoManchester(quadro);
        break;
    case 2: // Decodificação bipolar
        fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBipolar(quadro);
        break;
    default:
        cout << "ERROR" << endl;
        break;
    }

    MeioDeComunicacao(fluxoBrutoDeBits);
} // CamadaFisicaReceptora

int *CamadaFisicaReceptoraCodificacaoBinaria(int quadro[])
{
    cout << "Implementar Decodificação Binária" << endl;
    // Implemente a decodificação binária e retorne o fluxo bruto de bits como um ponteiro
    int *fluxoBrutoDeBits = nullptr; // Exemplo: inicialize o ponteiro como nulo
    // Faça as operações necessárias para decodificar o quadro e atribuir o resultado a 'fluxoBrutoDeBits'
    return fluxoBrutoDeBits;
}

int *CamadaFisicaReceptoraCodificacaoManchester(int quadro[])
{
    cout << "Implementar Decodificação Manchester" << endl;
    // Implemente a decodificação Manchester e retorne o fluxo bruto de bits como um ponteiro
    int *fluxoBrutoDeBits = nullptr; // Exemplo: inicialize o ponteiro como nulo
    // Faça as operações necessárias para decodificar o quadro e atribuir o resultado a 'fluxoBrutoDeBits'
    return fluxoBrutoDeBits;
}

int *CamadaFisicaReceptoraCodificacaoBipolar(int quadro[])
{
    cout << "Implementar Decodificação Bipolar" << endl;
    // Implemente a decodificação bipolar e retorne o fluxo bruto de bits como um ponteiro
    int *fluxoBrutoDeBits = nullptr; // Exemplo: inicialize o ponteiro como nulo
    // Faça as operações necessárias para decodificar o quadro e atribuir o resultado a 'fluxoBrutoDeBits'
    return fluxoBrutoDeBits;
}

void CamadaDeAplicacaoReceptora(int quadro[])
{
    string mensagem;
    for (int i = 0; i < sizeof(quadro); i++)
    {
        mensagem += static_cast<char>(quadro[i]);
    }

    // Chama a próxima camada
    AplicacaoReceptora(mensagem);
} // fim do metodo CamadaDeAplicacaoReceptora

void AplicacaoReceptora(string mensagem)
{
    cout << "A mensagem recebida foi: " << mensagem << endl;
} // fim do método AplicacaoReceptora
