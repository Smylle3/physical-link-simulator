# Simulador de Camada Fisica

Trabalho 2 de TR1

## Objetivo
Esse projeto tem como objetivo simular o funcionamento da camada física por meio da implementação dos seguintes protocolos:(i)
Binário; (ii) Manchester; e (iii) Bipolar.

## Execução

O projeto faz uso da ferramente Makefile para automatizar compilação e execução segue os comandos necessários para assim rodar o projeto:

- Para compilar

  ```
  make compile
  ```
  
- Para executar

  ```
  make exec
  ```

- Para compilar e executar

  ```
  make run
  ```

- Para limpar o projeto (excluir executaveis e objetos gerados)

  ```
  make clean
  ```

- Caso não tenha o Makefile instalado, ainda é possivel compilar e rodar o programa, use o comando:

  ```
  g++ -std=c++11 -Wall src/Simulador.cpp  src/CamadaFisica.cpp -o obj/Simulador -I headers
  ```

  ```
  obj/simulador.exe
  ```

### Lembrando que o foi desenvolvido para a plataforma Windows, deve funcionar de forma diferente em Linux ou MacOS!!!

## Integrantes do grupo:
- David Herbert
- João Pedro Queiroz
- Mateus Lúcio
- Vanessa Costa
