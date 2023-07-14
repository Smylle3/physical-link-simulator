#include <iostream>
#include "../headers/CamadaEnlace.hpp"


using namespace std;

void CamadaEnlaceDadosTransmissora(vector<int> quadro){

  CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

  CamadaEnlaceDadosTransmissoraControleDeErro(quadro);

  CamadaFisicaTransmissora(quadro);
} // Fim da CamadaEnlaceDadosTransmissora

vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(vector<int> quadro) {
    
    // escolhe o tipo de enquadramento
	// 0 = Contagem de Caracters
	// 1 = inserção de bytes
	int enquadramento = 1;
	vector<int> quadro_enquadrado;
	// enquadra o fluxo de bits passado
	switch (enquadramento){
		case 0:

			quadro_enquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);

			break;

		case 1:

			quadro_enquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);

			break;
	}

	attron(COLOR_PAIR(2));
	printw("Quadro Enquadrado: \n\n");
	attroff(COLOR_PAIR(2));
	for (int i : quadro)
		printw("%d", i);
	printw("\n\n");
	
	return quadro_enquadrado;
    
  int tipoDeEnquadramento = 0; // Alterar de acordo o teste
  vector<int> quadroEnquadrado;

  switch (tipoDeEnquadramento){

    case 0: // Contagem de caracteres
      quadroEnquadrado = CamadaDeEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);
      break;
    
    case 1: // Inserção de bytes
      quadroEnquadrado = CamadaDeEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);
      break;

    default:
      cout << "ERROR" << endl;
      break;
  }
} // Fim da CamadaEnlaceDadosTransmissoraEnquadramento

//-----------------------------Transmissão de Dados----------------------------------------
vector<int> CamadaDeEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro){
  //cod aqui

} // Fim da CamadaDeEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres

vector<int> CamadaDeEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro){
  //cod aqui

} // fim da CamadaDeEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(vector<int> quadro){

} // Fim da CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(vector<int> quadro){

} // Fim da CamadaEnlaceDadosTransmissoraControleDeErroCRC

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(vector<int> quadro){

} // Fim da CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming




vector<int> CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro){

  int tipoDeControleDeErro = 0; // Alterar de acordo o teste
  vector<int> quadroControle;

  switch (tipoDeControleDeErro){

    case 0: //bit pariadade par
      quadroControle = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
      break;

    case 1: //CRC
      quadroControle = CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
      break;

    case 2: // Código de Hamming
      quadroControle = CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(quadro);
      break;
    
    default:
      cout << "ERROR" << endl;
      break;
  }

} // Fim da CamadaEnlaceDadosTransmissoraControleDeErro


//-----------------------------Recepção de Dados----------------------------------------

vector<int> CamadaDeEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro){

} // Fim da CamadaDeEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres

vector<int> CamadaDeEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro){
  // cod aqui
} // Fim da CamadaDeEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes

vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(vector<int> quadro){

} // Fim da CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(vector<int> quadro){

} // Fim da CamadaEnlaceDadosReceptoraControleDeErroCRC

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(vector<int> quadro){

} // Fim da CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming


void CamadaEnlaceDadosReceptora(vector<int> quadro){

  CamadaEnlaceDadosReceptoraEnquadramento(quadro);

  CamadaEnlaceDadosReceptoraControleDeErro(quadro);

  CamadaDeAplicacaoReceptora(quadro);
} // Fim da CamadaEnlaceDadosReceptora

void CamadaEnlaceDadosReceptoraEnquadramento(vector<int> quadro){
  int tipoDeEnquadramento = 0; // Alterar de acordo o teste
  vector<int> quadroDesenquadrado;

  switch (tipoDeEnquadramento){

    case 0: // Contagem de caracteres
      quadroDesenquadrado = CamadaDeEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadro);
      break;
    
    case 1: // Inserção de bytes
      quadroDesenquadrado = CamadaDeEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadro);
      break;

    default:
      cout << "ERROR" << endl;
      break;
  }
} // Fim da CamadaEnlaceDadosReceptoraEnquadramento

void CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro){
  
  int tipoDeControleDeErro = 0; // Alterar de acordo o teste
  vector<int> quadroControle;

  switch (tipoDeControleDeErro){

    case 0: //bit pariadade par
      quadroControle = CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
      break;

    case 1: //CRC
      quadroControle = CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
      break;
    
    case 2: // Código de Hamming
      quadroControle = CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(quadro);
      break;    
    
    default:
      cout << "ERROR" << endl;
      break;
  }


} // Fim da CamadaEnlaceDadosReceptoraControleDeErro

