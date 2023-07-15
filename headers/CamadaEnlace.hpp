#ifndef CAMADAENLACE_HPP 
#define CAMADAENLACE_HPP
#include "../headers/CamadaFisica.hpp"

// Cabeçalho das funções da camada de enlace
//Transmissão

void CamadaEnlaceDadosTransmissora(vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro);

vector<int> CamadaDeEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro);
vector<int> CamadaDeEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(vector<int> quadro);
vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(vector<int> quadro);

//Recepção

void CamadaEnlaceDadosReceptora(vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraEnquadramento(vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro);

vector<int> CamadaDeEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro);
vector<int> CamadaDeEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(vector<int> quadro);
vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(vector<int> quadro);

#endif // CAMADAENLACE_HPP