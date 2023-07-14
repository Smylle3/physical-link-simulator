#include <iostream>
#include <string>
#include "../headers/CamadaEnlace.hpp"

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
    cout << endl;

    CamadaDeAplicacaoTransmissora(mensagem);
}