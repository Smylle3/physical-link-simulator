#include <iostream>
#include "../headers/CamadaFisica.hpp"

using namespace std;

int opcao = 0;

void ImprimeBits(vector<int> bits)
{
    for (int i = 0; i < bits.size(); i++)
    {
        cout << bits[i];
    }

    cout << endl
         << endl;
}

vector<int> ConversorParaBits(string mensagem)
{
    int i = 0, j = 0;
    vector<int> quadro;

    for (i = 0; i < mensagem.size(); i++)
    {
        bitset<8> set(mensagem[i]);
        if (mensagem[i] == ' ')
        {
            // um espaço vazio teve que virar um caso especial
            set.reset();   // todos são zero
            set.set(5, 1); // 32 == espaço
        }

        for (j = 7; j >= 0; j--)
        {
            if (set.test(j))
            {
                quadro.push_back(1);
            }
            else
            {
                quadro.push_back(0);
            }
        }
    }

    return quadro;
}

string ConversorParaString(vector<int> quadro)
{
    int i = 0, y = 0, j = 0;
    string mensagem;
    int letra = 0;
    // Pega grupo de 8 bits
    for (i = 0; i < quadro.size(); i += 8)
    {
        letra = 0;
        y = 0;
        // Ler os 8 bits e converte de binario para decimal utilizando base 2
        // e o expoente da potencia sendo o indice do bit
        for (j = i; j < (8 + i); j++)
        {
            if (quadro[j] == 1)
                letra = letra + pow(2, 7 - y);

            y++;
        }
        // Converte o valor inteiro em um caracter e concatena com a string que sera retornada
        mensagem.push_back((char)letra);
    }

    return mensagem;
}

void CamadaDeAplicacaoTransmissora(string mensagem)
{
    vector<int> quadro = ConversorParaBits(mensagem);

    cout << "Camada De Aplicacao Transmissora | Mensagem convertida para bits:" << endl;

    ImprimeBits(quadro);
    CamadaFisicaTransmissora(quadro);
}

void CamadaFisicaTransmissora(vector<int> quadro)
{
    cout << "Escolha uma opcao (0, 1 ou 2): ";
    cin >> opcao;
    cout << endl;

    int tipoDeCodificacao = opcao; // Mudar de acordo com o teste
    vector<int> fluxoBrutoDeBits;  // Trabalhar com BITS

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

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro)
{
    cout << "Camada Fisica Transmissora - Mensagem em codificacao Binaria: " << endl;
    // Implemente a codificação binária e retorne o fluxo bruto de bits como um ponteiro
    vector<int> fluxoBrutoDeBits = quadro;

    ImprimeBits(fluxoBrutoDeBits);
    return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro)
{
    cout << "Camada Fisica Transmissora - Mensagem em codificacao Manchester: " << endl;
    // Implemente a codificação Manchester e retorne o fluxo bruto de bits como um ponteiro
    vector<int> fluxoBrutoDeBits;

    for (int i = 0; i < quadro.size(); i++)
    {
        if (quadro[i] == 0)
        {
            // Bit 0: transição de alto para baixo no meio do intervalo
            fluxoBrutoDeBits.push_back(1);
            fluxoBrutoDeBits.push_back(0);
        }
        else if (quadro[i] == 1)
        {
            // Bit 1: transição de baixo para alto no meio do intervalo
            fluxoBrutoDeBits.push_back(0);
            fluxoBrutoDeBits.push_back(1);
        }
    }

    ImprimeBits(fluxoBrutoDeBits);
    return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro)
{
    cout << "Codificação Bipolar" << endl;
    // Implemente a codificação bipolar e retorne o fluxo bruto de bits como um ponteiro
    vector<int> fluxoBrutoDeBits; // Exemplo: inicialize o ponteiro como nulo
    // Faça as operações necessárias para codificar o quadro e atribuir o resultado a 'fluxoBrutoDeBits'
    return fluxoBrutoDeBits;
}

void MeioDeComunicacao(vector<int> fluxoBrutoDeBits) // Metodo que simula a transmissão de informações de um pontoA para um pontoB
{
    vector<int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    int tamanho = fluxoBrutoDeBitsPontoA.size();

    // fluxoBrutoDeBitsPontoB = new int[tamanho]; // Alocar memória para o array fluxoBrutoDeBitsPontoB

    for (int i = 0; i < tamanho; i++)
    {
        fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]); // Copia os elementos de fluxoBrutoDeBitsPontoA para fluxoBrutoDeBitsPontoB
    }

    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);

} // fim do metodo MeioDeComunicacao

void CamadaFisicaReceptora(vector<int> quadro)
{
    int tipoDeDecodificacao = opcao; // Alterar de acordo com o teste
    vector<int> fluxoBrutoDeBits;    // TRABALHAR COM BITS

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

    CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
} // CamadaFisicaReceptora

vector<int> CamadaFisicaReceptoraCodificacaoBinaria(vector<int> quadro)
{
    vector<int> fluxoBrutoDeBits = quadro;

    cout << "Camada Fisica Receptora - Mensagem em codificacao Binaria: " << endl;

    ImprimeBits(fluxoBrutoDeBits);

    return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaReceptoraCodificacaoManchester(vector<int> quadro)
{
    vector<int> fluxoBrutoDeBits;

    cout << "Camada Fisica Receptora - Mensagem em codificacao Manchester: " << endl;

    for (int i = 0; i < quadro.size(); i += 2)
    {
        if (quadro[i] == 1 && quadro[i + 1] == 0)
        {
            // Transição de alto para baixo: bit 0
            fluxoBrutoDeBits.push_back(0);
        }
        else if (quadro[i] == 0 && quadro[i + 1] == 1)
        {
            // Transição de baixo para alto: bit 1
            fluxoBrutoDeBits.push_back(1);
        }
        else
        {
            cout << "*ERRO NA DECODIFICACAO*" << endl;
        }
    }

    ImprimeBits(fluxoBrutoDeBits);

    return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaReceptoraCodificacaoBipolar(vector<int> quadro)
{
    cout << "Implementar Decodificação Bipolar" << endl;
    // Implemente a decodificação bipolar e retorne o fluxo bruto de bits como um ponteiro
    vector<int> fluxoBrutoDeBits; // Exemplo: inicialize o ponteiro como nulo
    // Faça as operações necessárias para decodificar o quadro e atribuir o resultado a 'fluxoBrutoDeBits'
    return fluxoBrutoDeBits;
}

void CamadaDeAplicacaoReceptora(vector<int> quadro)
{
    string mensagem = ConversorParaString(quadro);

    // Chama a próxima camada
    AplicacaoReceptora(mensagem);
} // fim do metodo CamadaDeAplicacaoReceptora

void AplicacaoReceptora(string mensagem)
{
    cout << "A mensagem recebida foi: " << mensagem << endl;
} // fim do método AplicacaoReceptora
