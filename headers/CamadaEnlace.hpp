#ifndef CAMADAENLACE_HPP 
#define CAMADAENLACE_HPP
#include "../headers/CamadaFisica.hpp"

// Cabeçalho das funções da camada de enlace
  //Transmissão

void CamadaEnlaceDadosTransmissora(vector<int> quadro);
void CamadaEnlaceDadosTransmissoraEnquadramento(vector<int> quadro);
void CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro);

vector<int> CamadaDeEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro);
vector<int> CamadaDeEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(vector<int> quadro);

  //Recepção

void CamadaEnlaceDadosReceptora(vector<int> quadro);
void CamadaEnlaceDadosReceptoraEnquadramento(vector<int> quadro);
void CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro);

vector<int> CamadaDeEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro);
vector<int> CamadaDeEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(vector<int> quadro);

#endif // CAMADAENLACE_HPP