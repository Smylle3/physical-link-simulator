#ifndef CAMADAFISICA_HPP
#define CAMADAFISICA_HPP

#include <string>

void CamadaDeAplicacaoTransmissora(std::string mensagem);
void CamadaFisicaTransmissora(int quadro[]);
void MeioDeComunicacao(int fluxoBrutoDeBits[]);
void CamadaFisicaReceptora(int quadro[]);
void CamadaDeAplicacaoReceptora(int quadro[]);
void AplicacaoReceptora(std::string mensagem);
int *CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[]);
int *CamadaFisicaTransmissoraCodificacaoManchester(int quadro[]);
int *CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[]);
int *CamadaFisicaReceptoraCodificacaoBinaria(int quadro[]);
int *CamadaFisicaReceptoraCodificacaoManchester(int quadro[]);
int *CamadaFisicaReceptoraCodificacaoBipolar(int quadro[]);

#endif // CAMADAFISICA_HPP