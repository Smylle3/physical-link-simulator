#ifndef CAMADAFISICA_HPP
#define CAMADAFISICA_HPP

#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <bits/stdc++.h>
#include <bitset>

using namespace std;

void CamadaDeAplicacaoTransmissora(string mensagem);
void CamadaFisicaTransmissora(vector<int> quadro);
void MeioDeComunicacao(vector<int> fluxoBrutoDeBits);
void CamadaFisicaReceptora(vector<int> quadro);
void CamadaDeAplicacaoReceptora(vector<int> quadro);
void AplicacaoReceptora(string mensagem);

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro);
vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro);
vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro);
vector<int> CamadaFisicaReceptoraCodificacaoBinaria(vector<int> quadro);
vector<int> CamadaFisicaReceptoraCodificacaoManchester(vector<int> quadro);
vector<int> CamadaFisicaReceptoraCodificacaoBipolar(vector<int> quadro);

vector<int> ConversorParaBits(string mensagem);
string ConversorParaString(vector<int> quadro);

#endif // CAMADAFISICA_HPP