#include <iostream>
#include "../headers/CamadaEnlace.hpp"

using namespace std;

bool potenciaDeDois(int number)
{
	return (number & (number - 1)) == 0;
}

int calculaParidadeBit(const vector<int> &quadro, int posicao_paridade)
{
	int bit_paridade = 0;

	// Calcular o bit de paridade utilizando o esquema de paridade par
	for (int i = posicao_paridade; i < quadro.size(); i += (posicao_paridade + 1))
	{
		bit_paridade ^= quadro[i];
	}

	return bit_paridade;
}

void CamadaEnlaceDadosTransmissora(vector<int> quadro)
{
	vector<int> quadro_enquadrado;

	quadro_enquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
	quadro_enquadrado = CamadaEnlaceDadosTransmissoraControleDeErro(quadro_enquadrado);

	CamadaFisicaTransmissora(quadro);
} // Fim da CamadaEnlaceDadosTransmissora

vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(vector<int> quadro)
{
	int tipoDeEnquadramento = 0; // Alterar de acordo com o teste
	vector<int> quadroEnquadrado;

	switch (tipoDeEnquadramento)
	{
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

	cout << "Quadro Enquadrado: " << endl;
	ImprimeBits(quadroEnquadrado);
	return quadroEnquadrado;
}

//-----------------------------Transmissão de Dados----------------------------------------
vector<int> CamadaDeEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro)
{
	cout << "Enquadramento com contagem de caracteres\n\n";

	uint8_t qtd_bytes = ceil(quadro.size() / 8);
	vector<int> quadro_enquadrado_caracteres = quadro;
	vector<int> binario;
	bitset<8> bits(qtd_bytes);

	for (int i = 0; i < 8; i++)
	{
		if (int(bits[i]) == 1)
			quadro_enquadrado_caracteres.insert(quadro_enquadrado_caracteres.begin(), int(bits[i]));
		else
			quadro_enquadrado_caracteres.insert(quadro_enquadrado_caracteres.begin(), int(0));
	}

	cout << "Quadro enquadrado com contagem de caracteres:\n";
	ImprimeBits(quadro_enquadrado_caracteres);
	return quadro_enquadrado_caracteres;
} // Fim da CamadaDeEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres

vector<int> CamadaDeEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro)
{
	cout << "Enquadramento com insercao de bytes\n\n";

	string flag = "00001111";
	string esc = "11110000";
	string flag_bit = "01111110";
	string byte_str = "", quadro_str = flag;

	vector<int> novo_quadro;
	int counter = 1;

	for (int i = 0; i < quadro.size(); i++)
	{
		byte_str += to_string(quadro[i]);

		if (counter == (BYTE))
		{
			if ((byte_str == flag) || (byte_str == esc))
				quadro_str += esc;

			quadro_str += byte_str;
			counter = 0;
			byte_str = "";
		}
		counter++;
	}

	quadro_str += flag;

	for (auto &i : quadro_str)
		novo_quadro.push_back(i - '0');

	cout << "Quadro enquadrado com insercao de bytes:\n";
	ImprimeBits(novo_quadro);
	return novo_quadro;
} // fim da CamadaDeEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(vector<int> quadro)
{
	cout << "\n\nControle de Paridade Par..." << endl;

	vector<int> controle_paridade_par;
	bool paridade = true;

	for (int i = 0; i < quadro.size(); i++)
		controle_paridade_par.push_back(quadro.at(i));

	for (int i = 0; i < quadro.size(); i++)
		if (quadro.at(i) == 1)
			paridade = !paridade;

	controle_paridade_par.push_back(paridade);

	ImprimeBits(controle_paridade_par);
	return controle_paridade_par;
} // Fim da CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(vector<int> quadro)
{
	cout << "\n\nTransmissao com controle de erro CRC..." << endl;

	vector<int> novo_quadro = quadro;
	string polinomio_crc_32 = "100110000010001110110110111";

	if (quadro.size() <= polinomio_crc_32.length())
	{
		cout << "\n\nErro, o quadro possui menos bits que o polinomio" << endl
			 << endl;
		exit(1);
	}

	for (int i = 0; i < polinomio_crc_32.length(); i++)
		novo_quadro.push_back(0);

	for (int i = 0; i < quadro.size(); i++)
	{
		if (novo_quadro[i] == 1)
		{
			for (int j = 0; j < polinomio_crc_32.length(); j++)
				novo_quadro[i + j] ^= (polinomio_crc_32[j] - '0');
			// XOR entre o elemento i+j do novo quadro e o polinômio CRC 32bits; Armazena no próprio elemento i+j do novo quadro
		}
	}

	for (int i = 0; i < quadro.size(); i++)
		novo_quadro[i] = quadro[i];

	ImprimeBits(novo_quadro);
	return novo_quadro;
} // Fim da CamadaEnlaceDadosTransmissoraControleDeErroCRC

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(vector<int> quadro)
{
	cout << "\n\nControle de Erro com Código de Hamming..." << endl
		 << endl;

	int n = quadro.size(); // Tamanho do quadro
	int m = 0;			   // Número de bits de paridade adicionados
	int r = 0;			   // Número total de bits no quadro codificado

	// Determinar o número de bits de paridade a serem adicionados
	while (n + m + 1 > pow(2, m))
	{
		m++;
	}

	r = n + m; // Total de bits no quadro codificado

	// Criar o quadro codificado com os bits de paridade inicializados como 0
	vector<int> quadro_codificado(r, 0);

	int j = 0; // Índice para percorrer o quadro codificado
	int k = 0; // Índice para percorrer o quadro original
	// Preencher os bits de dados no quadro codificado, pulando os bits de paridade
	for (int i = 1; i <= r; i++)
	{
		if (potenciaDeDois(i))
		{
			// Pular bits de paridade
			continue;
		}
		else
		{
			// Preencher os bits de dados
			quadro_codificado[i - 1] = quadro[k];
			k++;
		}
	}
	// Calcular os bits de paridade usando a codificação de Hamming
	for (int i = 0; i < m; i++)
	{
		int bit_paridade = calculaParidadeBit(quadro_codificado, i);

		// Definir o bit de paridade no quadro codificado
		quadro_codificado[pow(2, i) - 1] = bit_paridade;
	}
	// Exibir o quadro codificado com os bits de paridade
	cout << "Quadro codificado com Código de Hamming:" << endl;
	ImprimeBits(quadro_codificado);
	return quadro_codificado;

} // Fim da CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming

vector<int> CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro)
{

	int tipoDeControleDeErro = 0; // Alterar de acordo o teste
	vector<int> quadroControle;

	switch (tipoDeControleDeErro)
	{
	case 0: // bit pariadade par
		quadroControle = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
		break;
	case 1: // CRC
		quadroControle = CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
		break;
	case 2: // Código de Hamming
		quadroControle = CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(quadro);
		break;
	default:
		cout << "ERROR" << endl;
		break;
	}
	cout << "Quadro após controle de erro realizado:" << endl;
	ImprimeBits(quadroControle);
	return quadroControle;
} // Fim da CamadaEnlaceDadosTransmissoraControleDeErro

//-----------------------------Recepção de Dados----------------------------------------

vector<int> CamadaDeEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro)
{
	vector<int> quadro_desenquadrado;
	for (int i = 8; i < quadro.size(); i++)
		quadro_desenquadrado.push_back(quadro[i]);

	return quadro_desenquadrado;
} // Fim da CamadaDeEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres

vector<int> CamadaDeEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro)
{
	string byte_str = "";
	string quadro_str = "";
	string flag = "00001111";
	string esc = "11110000";

	vector<int> novo_quadro;
	int counter = 1;
	bool ignore = false;

	for (int i = 0; i < quadro.size(); i++)
	{
		byte_str += to_string(quadro[i]);
		if (counter == BYTE)
		{
			if (((byte_str == flag) || (byte_str == esc)) && !ignore)
				ignore = true;
			else
			{
				quadro_str += byte_str;
				ignore = false;
			}
			counter = 0;
			byte_str = "";
		}
		counter++;
	}
	for (auto &i : quadro_str)
		novo_quadro.push_back(i - '0');

	ImprimeBits(novo_quadro);
	return novo_quadro;
} // Fim da CamadaDeEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes

vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(vector<int> quadro)
{
	vector<int> recebimento_paridade_par;
	bool paridade = true;

	for (int i = 0; i < quadro.size() - 1; i++)
		recebimento_paridade_par.push_back(quadro.at(i));

	for (int i = 0; i < recebimento_paridade_par.size(); i++)
		if (recebimento_paridade_par.at(i) == 1)
			paridade = !paridade;

	if (quadro.back() == paridade)
		cout << "Recebeu com sucesso " << endl;

	ImprimeBits(recebimento_paridade_par);
	return recebimento_paridade_par;
} // Fim da CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(vector<int> quadro)
{
	string polinomio_crc_32 = "100110000010001110110110111";
	vector<int> mensagem, novo_quadro;
	bool valido = true;

	if (quadro.size() <= polinomio_crc_32.length())
	{
		cout << "Erro, o quadro possui menos bits que o polinômio" << endl;
		exit(1);
	}

	novo_quadro = quadro;
	mensagem = quadro;
	mensagem.erase(mensagem.end() - 31, mensagem.end());

	for (int i = 0; i < mensagem.size(); i++)
	{
		if (quadro[i] == 1)
		{
			for (int j = 0; j < polinomio_crc_32.length(); j++)
				novo_quadro[j + i] = novo_quadro[j + i] == polinomio_crc_32[j] ? 0 : 1;
			/*  Compara o item i+j do novo quadro com o polinômio CRC 32 bits e armazena, no mesmo elemento,
					0 se forem iguais, e 1 caso sejam diferentes. */
		}
	}

	for (int i = 0; i < mensagem.size(); i++)
	{
		if (novo_quadro[i] != 0)
			valido = false;
	}

	if (valido)
	{
		ImprimeBits(mensagem);
		return mensagem;
	}
} // Fim da CamadaEnlaceDadosReceptoraControleDeErroCRC

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(vector<int> quadro)
{
	cout << "Decodificando do codigo de hamming..." << endl;

	vector<int> decodificacao_hamming;
	int posicao_paridade = 0;

	for (int i = 1; i <= quadro.size(); i++)
	{
		if (i == pow(2, posicao_paridade))
			posicao_paridade++;
		else
			decodificacao_hamming.push_back(quadro.at(i - 1));
	}

	ImprimeBits(decodificacao_hamming);
	return decodificacao_hamming;
} // Fim da CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming

void CamadaEnlaceDadosReceptora(vector<int> quadro)
{
	vector<int> quadro_desenquadrado;

	quadro_desenquadrado = CamadaEnlaceDadosReceptoraEnquadramento(quadro);
	quadro_desenquadrado = CamadaEnlaceDadosReceptoraControleDeErro(quadro_desenquadrado);

	ImprimeBits(quadro);
	CamadaDeAplicacaoReceptora(quadro);
} // Fim da CamadaEnlaceDadosReceptora

vector<int> CamadaEnlaceDadosReceptoraEnquadramento(vector<int> quadro)
{
	int tipoDeEnquadramento = 0; // Alterar de acordo o teste
	vector<int> quadroDesenquadrado;

	switch (tipoDeEnquadramento)
	{
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

vector<int> CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro)
{

	int tipoDeControleDeErro = 0; // Alterar de acordo o teste
	vector<int> quadroControle;

	switch (tipoDeControleDeErro)
	{
	case 0: // bit pariadade par
		quadroControle = CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
		break;
	case 1: // CRC
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
