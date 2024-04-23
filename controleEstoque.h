#pragma once
#include "produto.h"
void exibeMenu();

produto * expandirVetor(produto *& produtos, int & num_produtos, int & capacidade);

void adicionarProdutos(produto *& produtos, int & num_produtos);

void excluirProdutos(produto *& produtos, int & num_produtos);

void listarProdutos(produto * produtos, int num_produtos);

void tratarOpcao(char opcao, produto *& produtos, int & num_produtos);

