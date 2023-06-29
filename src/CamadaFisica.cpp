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
    vector<int> quadro;

    for (char c : mensagem)
    {
        // Conversão direta de cada caractere para o valor binário correspondente
        bitset<8> bits(c);

        // Inserir os bits no quadro
        for (int i = 7; i >= 0; i--)
        {
            quadro.push_back(bits[i]);
        }
    }

    return quadro;
}

string ConversorParaString(vector<int> quadro)
{
    string mensagem;
    int valor = 0;

    for (size_t i = 0; i < quadro.size(); i += 8)
    {
        valor = 0;

        for (size_t j = 0; j < 8; j++)
        {
            valor = (valor << 1) + quadro[i + j];
        }

        mensagem.push_back(static_cast<char>(valor));
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
    cout << "==============================" << endl;
    cout << "  Selecione uma opcao de codificacao:" << endl;
    cout << "==============================" << endl;
    cout << "  0 - Codificacao Binaria" << endl;
    cout << "  1 - Codificacao Manchester" << endl;
    cout << "  2 - Codificacao Bipolar" << endl;
    cout << "==============================" << endl;
    cout << "  Opcao: ";
    cin >> opcao;
    cout << endl;

    int tipoDeCodificacao = opcao; // Mudar de acordo com o teste
    vector<int> fluxoBrutoDeBits;  // Trabalhar com BITS

    switch (tipoDeCodificacao)
    {
    case 0: // Codificação binária
        cout << "Codificacao BINARIA selecionada" << endl;
        fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
        break;
    case 1: // Codificação manchester
        cout << "Codificacao MANCHESTER selecionada" << endl;
        fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
        break;
    case 2: // Codificação bipolar
        cout << "Codificacao BIPOLAR selecionada" << endl;
        fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
        break;
    default:
        cout << "ERROR" << endl;
        break;
    }

    cout << "Camada Fisica Transmissora - Mensagem codificada:" << endl;
    ImprimeBits(fluxoBrutoDeBits);
    MeioDeComunicacao(fluxoBrutoDeBits);
} // fim do método CamadaFisicaTransmissora

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro)
{
    vector<int> fluxoBrutoDeBits = quadro;
    return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro)
{
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

    return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro)
{
    vector<int> fluxoBrutoDeBits;

    int polaridade = 1; // Polaridade inicial

    for (int i = 0; i < quadro.size(); i++)
    {
        if (quadro[i] == 0)
        {
            fluxoBrutoDeBits.push_back(0); // Bit 0 é representado por 0
        }
        else
        {
            fluxoBrutoDeBits.push_back(polaridade); // Bit 1 é representado pela polaridade atual
            polaridade *= -1;                       // Inverte a polaridade para o próximo bit
        }
    }

    return fluxoBrutoDeBits;
}

void MeioDeComunicacao(vector<int> fluxoBrutoDeBits) // Metodo que simula a transmissão de informações de um pontoA para um pontoB
{
    vector<int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    int tamanho = fluxoBrutoDeBitsPontoA.size();

    cout << "Enviando a mensagem, aguarde..." << endl;
    Sleep(3 * 1000);
    cout << endl;

    for (int i = 0; i < tamanho; i++)
    {
        fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]); // Copia os elementos de fluxoBrutoDeBitsPontoA para fluxoBrutoDeBitsPontoB
    }

    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);

} // fim do metodo MeioDeComunicacao

void CamadaFisicaReceptora(vector<int> quadro)
{
    cout << "Camada Fisica Receptora" << endl;
    int tipoDeDecodificacao = opcao; // Alterar de acordo com o teste
    vector<int> fluxoBrutoDeBits;    // TRABALHAR COM BITS

    switch (tipoDeDecodificacao)
    {
    case 0: // Decodificação binária
        cout << "Mensagem recebida com sucesso! Iniciando decodificacao BINARIA: " << endl;
        fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBinaria(quadro);
        break;
    case 1: // Decodificação Manchester
        cout << "Mensagem recebida com sucesso! Iniciando a decodificacao usando MANCHESTER: " << endl;
        fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoManchester(quadro);
        break;
    case 2: // Decodificação bipolar
        cout << "Mensagem recebida com sucesso! Iniciando decodificacao BIPOLAR: " << endl;
        fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBipolar(quadro);
        break;
    default:
        cout << "ERROR" << endl;
        break;
    }

    ImprimeBits(fluxoBrutoDeBits);
    CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
} // CamadaFisicaReceptora

vector<int> CamadaFisicaReceptoraCodificacaoBinaria(vector<int> quadro)
{
    vector<int> fluxoBrutoDeBits = quadro;
    return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaReceptoraCodificacaoManchester(vector<int> quadro)
{
    vector<int> fluxoBrutoDeBits;

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

    return fluxoBrutoDeBits;
}

vector<int> CamadaFisicaReceptoraCodificacaoBipolar(vector<int> quadro)
{
    vector<int> fluxoBrutoDeBits;

    int polaridade = 1; // Polaridade inicial

    for (int i = 0; i < quadro.size(); i++)
    {
        if (quadro[i] == 0)
        {
            fluxoBrutoDeBits.push_back(0); // Bit 0
        }
        else
        {
            fluxoBrutoDeBits.push_back(1); // Bit 1
            polaridade *= -1;              // Inverte a polaridade para o próximo bit
        }
    }

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
    int tamanho = mensagem.size();
    cout << "Mensagem decodificada" << endl;
    // Imprime a linha superior da caixa
    cout << "+";
    for (int i = 0; i < tamanho + 4; i++)
        cout << "-";
    cout << "+" << endl;

    // Imprime a mensagem dentro da caixa
    cout << "|  ";
    cout << mensagem;
    cout << "  |" << endl;

    // Imprime a linha inferior da caixa
    cout << "+";
    for (int i = 0; i < tamanho + 4; i++)
        cout << "-";
    cout << "+" << endl;
}