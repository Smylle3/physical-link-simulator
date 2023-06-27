#include <iostream>
#include <string>
#include "CamadaFisica.hpp"

using namespace std;

void AplicacaoTransmissora();

int main()
{
    AplicacaoTransmissora();
    return 0;
}

void AplicacaoTransmissora()
{
    string mensagem;
    cout << "Digite uma Mensagem: " << endl;
    cin >> mensagem;

    CamadaDeAplicacaoTransmissora(mensagem);
}