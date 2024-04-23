#pragma once
#include "produto.h"


char * intParaChar(int n);

char * floatParaChar(float f);

void exibeMenuCliente(produto * produtos, int numProdutos, char ** carrinho, int tamanhoCarrinho);

void fazerPedido(produto * produtos, int numProdutos);