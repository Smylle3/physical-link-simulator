#include <iostream>
#include "../headers/CamadaEnlace.hpp"
#include "../headers/CamadaFisica.hpp"

using namespace std;

int tipoDeEnquadramento = 0;  // Alterar de acordo com o teste
int tipoDeControleDeErro = 0; // Alterar de acordo com o teste

void CamadaEnlaceDadosTransmissora(vector<int> quadro)
{
	vector<int> quadro_enquadrado;

	quadro_enquadrado = CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
	quadro_enquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro_enquadrado);

	CamadaFisicaTransmissora(quadro_enquadrado);
} // Fim da CamadaEnlaceDadosTransmissora

vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(vector<int> quadro)
{
	cout << "Camada De Enlace de dados Transmissora | Enquadramento" << endl;

	cout << "==============================" << endl;
	cout << "  Selecione uma opcao de enquadramento:" << endl;
	cout << "==============================" << endl;
	cout << "  0 - Enquadramento por contagem de caracteres" << endl;
	cout << "  1 - Enquadramento por insercao de bytes" << endl;
	cout << "==============================" << endl;
	cout << "  Opcao: ";
	cin >> tipoDeEnquadramento; // Alterar de acordo com o teste
	cout << endl;

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

	return quadroEnquadrado;
}

//-----------------------------Transmissão de Dados----------------------------------------
vector<int> CamadaDeEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro)
{
	cout << "Enquadramento | Contagem de caracteres" << endl;

	// Calcula a quantidade de bytes necessários para representar o quadro
	uint8_t qtd_bytes = ceil(quadro.size() / 8);

	// Cria uma cópia do quadro original para adicionar o enquadramento
	vector<int> quadro_enquadrado_caracteres = quadro;

	// Converte a quantidade de bytes em uma representação binária de 8 bits
	bitset<8> bits(qtd_bytes);

	// Insere os bits da quantidade de bytes no início do quadro
	for (int i = 0; i < 8; i++)
	{
		if (int(bits[i]) == 1)
			quadro_enquadrado_caracteres.insert(quadro_enquadrado_caracteres.begin(), int(bits[i]));
		else
			quadro_enquadrado_caracteres.insert(quadro_enquadrado_caracteres.begin(), int(0));
	}

	cout << "Quadro enquadrado com contagem de caracteres: ";
	ImprimeBits(quadro_enquadrado_caracteres);
	return quadro_enquadrado_caracteres;
}

vector<int> CamadaDeEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro)
{
	cout << "Enquadramento | Insercao de bytes" << endl;

	// Definição dos padrões utilizados
	string flag = "00001111";
	string esc = "11110000";
	string flag_bit = "01111110";

	string byte_str = "", quadro_str = flag;

	vector<int> novo_quadro;
	int counter = 1;

	// Percorre cada bit do quadro original
	for (int i = 0; i < quadro.size(); i++)
	{
		byte_str += to_string(quadro[i]);

		// Verifica se é necessário inserir um byte completo
		if (counter == (BYTE))
		{
			// Verifica se o byte formado é igual a algum dos padrões (flag ou escape)
			if ((byte_str == flag) || (byte_str == esc))
				quadro_str += esc;

			// Insere o byte no quadro
			quadro_str += byte_str;
			counter = 0;
			byte_str = "";
		}
		counter++;
	}

	// Adiciona a flag no final do quadro
	quadro_str += flag;

	// Converte o quadro para um vetor de inteiros
	for (auto &i : quadro_str)
		novo_quadro.push_back(i - '0');

	cout << "Quadro enquadrado com insercao de bytes: ";
	ImprimeBits(novo_quadro);
	return novo_quadro;
}

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(vector<int> quadro)
{
	cout << "Camada De Enlace de dados Transmissora | Controle de erro | Paridade Par" << endl;

	vector<int> controle_paridade_par;
	bool paridade = true;

	for (int i = 0; i < quadro.size(); i++)
		controle_paridade_par.push_back(quadro.at(i));

	for (int i = 0; i < quadro.size(); i++)
		if (quadro.at(i) == 1)
			paridade = !paridade;

	controle_paridade_par.push_back(paridade);

	cout << "Controle por Paridade Par aplicado: ";
	ImprimeBits(controle_paridade_par);
	return controle_paridade_par;
} // Fim da CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(vector<int> quadro)
{
	cout << "Camada De Enlace de dados Transmissora | Controle de erro | CRC" << endl;

	vector<int> novo_quadro = quadro;
	string polinomio_crc_32 = "100110000010001110110110111";

	if (quadro.size() <= polinomio_crc_32.length())
	{
		cout << "Erro, o quadro possui menos bits que o polinômio" << endl;
		exit(1);
	}

	// Adiciona zeros ao final do quadro para acomodar o polinômio CRC
	for (int i = 0; i < polinomio_crc_32.length(); i++)
		novo_quadro.push_back(0);

	// Cálculo do CRC (Cyclic Redundancy Check)
	for (int i = 0; i < quadro.size(); i++)
	{
		if (novo_quadro[i] == 1)
		{
			// Realiza a operação XOR entre o elemento i+j do novo quadro e o polinômio CRC
			for (int j = 0; j < polinomio_crc_32.length(); j++)
				novo_quadro[i + j] ^= (polinomio_crc_32[j] - '0');
		}
	}

	// Restaura os bits originais do quadro
	for (int i = 0; i < quadro.size(); i++)
		novo_quadro[i] = quadro[i];

	cout << "Controle CRC aplicado: ";
	ImprimeBits(novo_quadro);
	return novo_quadro;
}

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(vector<int> quadro)
{
	cout << "Camada De Enlace de dados Transmissora | Controle de erro | Codigo de Hamming" << endl;

	int tamanho_quadro = quadro.size();
	int bit_redundancia = 0;

	// Calcula a quantidade de bits de paridade necessários
	while (tamanho_quadro + bit_redundancia + 1 > pow(2, bit_redundancia))
	{
		bit_redundancia++;
	}

	int tamanho_hamming = tamanho_quadro + bit_redundancia;
	vector<int> codigo_hamming(tamanho_hamming);

	int posicao_paridade = 0;
	int posicao_dado = 0;

	// Preenche o quadro Hamming com os bits de paridade nas posições corretas
	for (int i = 0; i < tamanho_hamming; i++)
	{
		if (i == pow(2, posicao_paridade) - 1)
		{
			posicao_paridade++;
		}
		else
		{
			codigo_hamming[i] = quadro[posicao_dado];
			posicao_dado++;
		}
	}

	// Calcula os bits de paridade
	for (int i = 0; i < bit_redundancia; i++)
	{
		int posicao_analise = pow(2, i) - 1;
		int xor_analise = 0;

		while (posicao_analise < tamanho_hamming)
		{
			for (int j = 0; j < pow(2, i); j++)
			{
				xor_analise ^= codigo_hamming[posicao_analise];
				posicao_analise++;
			}
			posicao_analise += pow(2, i);
		}

		codigo_hamming[pow(2, i) - 1] = xor_analise;
	}

	// Exibe o quadro codificado com os bits de paridade
	cout << "Quadro codificado por Codigo de Hamming: ";
	for (int bit : codigo_hamming)
	{
		cout << bit;
	}
	cout << endl;

	return codigo_hamming;
}

vector<int> CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro)
{
	cout << "Camada De Enlace de dados Transmissora | Controle de erro" << endl;
	cout << "==============================" << endl;
	cout << "  Selecione uma opcao para o controle de erro:" << endl;
	cout << "==============================" << endl;
	cout << "  0 - Controle de erro por bit paridade par" << endl;
	cout << "  1 - Controle de erro CRC" << endl;
	cout << "  2 - Controle de erro por codigo de Hamming" << endl;
	cout << "==============================" << endl;
	cout << "  Opcao: ";
	cin >> tipoDeControleDeErro; // Alterar de acordo com o teste
	cout << endl;

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
	return quadroControle;
} // Fim da CamadaEnlaceDadosTransmissoraControleDeErro

//-----------------------------Recepção de Dados----------------------------------------

vector<int> CamadaDeEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro)
{
	cout << "Camada De Enlace de dados Receptora | Enquadramento | Contagem de caracteres" << endl;
	vector<int> quadro_desenquadrado;
	for (int i = 8; i < quadro.size(); i++)
		quadro_desenquadrado.push_back(quadro[i]);

	cout << "Enquadramento por Contagem de caracteres: ";
	ImprimeBits(quadro_desenquadrado);
	return quadro_desenquadrado;
} // Fim da CamadaDeEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres

vector<int> CamadaDeEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro)
{
	cout << "Camada De Enlace de dados Receptora | Enquadramento | Insercao de Bytes:" << endl;
	string byte_str = "";        // Variável para armazenar os bits de cada byte do quadro
	string quadro_str = "";      // String para armazenar o quadro desenquadrado
	string flag = "00001111";     // Byte de flag utilizado na inserção de bytes
	string esc = "11110000";      // Byte de escape utilizado para escapar o byte de flag

	vector<int> novo_quadro;     // Vetor para armazenar o quadro desenquadrado como inteiros
	int counter = 1;             // Contador para acompanhar a formação de bytes
	bool ignore = false;         // Flag para indicar se o byte atual deve ser ignorado

	// Loop para percorrer os bits do quadro
	for (int i = 0; i < quadro.size(); i++)
	{
		byte_str += to_string(quadro[i]);   // Adiciona o bit atual à string do byte

		// Verifica se um byte foi formado
		if (counter == BYTE)
		{
			// Verifica se o byte é igual ao byte de flag ou de escape e não está sendo ignorado
			if (((byte_str == flag) || (byte_str == esc)) && !ignore)
				ignore = true;   // Byte é marcado para ser ignorado
			else
			{
				quadro_str += byte_str;   // Byte é adicionado ao quadro desenquadrado
				ignore = false;           // Reset da flag de ignorar
			}

			counter = 0;        // Reset do contador de bits do byte
			byte_str = "";     // Reset da string do byte
		}

		counter++;   // Incrementa o contador de bits
	}

	// Converte o quadro desenquadrado em um vetor de inteiros
	for (auto &i : quadro_str)
		novo_quadro.push_back(i - '0');

	cout << "Enquadramento por Insercao de bytes: ";
	ImprimeBits(novo_quadro);   // Imprime o quadro desenquadrado em forma de bits
	return novo_quadro;         // Retorna o quadro desenquadrado
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(vector<int> quadro)
{
	cout << "Camada De Enlace de dados Receptora | Controle de erro | Paridade Par" << endl;

	vector<int> recebimento_paridade_par;   // Vetor para armazenar o quadro desconsiderando o bit de paridade
	bool paridade = true;                    // Variável para armazenar o cálculo da paridade

	// Loop para percorrer os bits do quadro, desconsiderando o último bit de paridade
	for (int i = 0; i < quadro.size() - 1; i++)
		recebimento_paridade_par.push_back(quadro.at(i));

	// Verifica a paridade dos bits do quadro desconsiderando o último bit de paridade
	for (int i = 0; i < recebimento_paridade_par.size(); i++)
		if (recebimento_paridade_par.at(i) == 1)
			paridade = !paridade;

	// Verifica se o último bit do quadro (bit de paridade) é igual ao cálculo da paridade
	if (quadro.back() == paridade)
		cout << "Recebeu com sucesso" << endl;

	cout << "Controle por Paridade Par aplicado: ";
	ImprimeBits(recebimento_paridade_par);   // Imprime o quadro desconsiderando o bit de paridade
	return recebimento_paridade_par;
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(vector<int> quadro)
{
	cout << "Camada De Enlace de dados Receptora | Controle de erro | CRC" << endl;

	string polinomio_crc_32 = "100110000010001110110110111";  // Polinômio CRC-32
	vector<int> mensagem, novo_quadro;
	bool valido = true;

	if (quadro.size() <= polinomio_crc_32.length())
	{
		cout << "Erro, o quadro possui menos bits que o polinômio" << endl;
		exit(1);
	}

	novo_quadro = quadro;
	mensagem = quadro;
	mensagem.erase(mensagem.end() - 31, mensagem.end());   // Remove os 32 bits de verificação do CRC do quadro recebido

	// Realiza a verificação do CRC
	for (int i = 0; i < mensagem.size(); i++)
	{
		if (quadro[i] == 1)
		{
			for (int j = 0; j < polinomio_crc_32.length(); j++)
				novo_quadro[j + i] = novo_quadro[j + i] == polinomio_crc_32[j] ? 0 : 1;
			// Compara o item i+j do novo quadro com o polinômio CRC 32 bits e armazena, no mesmo elemento, 0 se forem iguais, e 1 caso sejam diferentes.
		}
	}

	// Verifica se o quadro é válido, ou seja, se não houve detecção de erro no CRC
	for (int i = 0; i < mensagem.size(); i++)
	{
		if (novo_quadro[i] != 0)
			valido = false;
	}

	// Se o quadro for válido, imprime a mensagem original (sem os bits de verificação do CRC) e retorna como resultado
	if (valido)
	{
		cout << "Controle por CRC aplicado: ";
		ImprimeBits(mensagem);
		return mensagem;
	}
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(vector<int> quadro)
{
	cout << "Camada De Enlace de dados Receptora | Controle de erro | Codigo de Hamming" << endl;

	vector<int> decodificacao_hamming;
	int posicao_paridade = 0;

	// Percorre o quadro recebido, pulando as posições que correspondem aos bits de paridade
	for (int i = 1; i <= quadro.size(); i++)
	{
		if (i == pow(2, posicao_paridade))
		{
			posicao_paridade++;
		}
		else
		{
			decodificacao_hamming.push_back(quadro.at(i - 1));
		}
	}

	// Exibe o quadro decodificado após a remoção dos bits de paridade
	cout << "Controle por Codigo de Hamming aplicado: ";
	ImprimeBits(decodificacao_hamming);
	return decodificacao_hamming;
}

void CamadaEnlaceDadosReceptora(vector<int> quadro)
{
	vector<int> quadro_desenquadrado;

	quadro_desenquadrado = CamadaEnlaceDadosReceptoraEnquadramento(quadro);
	quadro_desenquadrado = CamadaEnlaceDadosReceptoraControleDeErro(quadro_desenquadrado);

	CamadaDeAplicacaoReceptora(quadro_desenquadrado);
} // Fim da CamadaEnlaceDadosReceptora

vector<int> CamadaEnlaceDadosReceptoraEnquadramento(vector<int> quadro)
{
	cout << "Camada De Enlace de dados Receptora | Enquadramento" << endl;

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
		exit(1);
		break;
	}

	return quadroDesenquadrado;
} // Fim da CamadaEnlaceDadosReceptoraEnquadramento

vector<int> CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro)
{
	cout << "Camada De Enlace de dados Receptora | Controle de erro" << endl;
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

	ImprimeBits(quadroControle);
	return quadroControle;
} // Fim da CamadaEnlaceDadosReceptoraControleDeErro
