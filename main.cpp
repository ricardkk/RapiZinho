#include <iostream>
#include <fstream>
#include "produto.h"
#include "controleEstoque.h"
#include "pedidos.h"
using namespace std;

int main(int argc, char * argv[]) {

    produto * produtos = nullptr;
    int num_produtos = 0; 

    // Le os itens do arquivo de estoque e copia para o vetor de produtos
    ifstream fin("estoque.bin", ios_base::binary);

    if (!fin) {
        cout << "Erro ao abrir o arquivo.";
        exit(EXIT_FAILURE);
    }

    // Verifica a quantidade de itens no arquivo
    fin.seekg(0, ios::end);
    num_produtos = fin.tellg() / sizeof(produto);
    fin.seekg(0, ios::beg);

    produtos = new produto[num_produtos];
    fin.read((char *)(produtos), num_produtos * sizeof(produto));
    fin.close();

    // Inicializar os produtos
    for (int i = 0; i < num_produtos; ++i) {
        if (strlen(produtos[i].nome) > 0) {
            // Garante que a string esteja terminada corretamente
            produtos[i].nome[strlen(produtos[i].nome)] = '\0'; 

        }
    }

    // Se iniciado com a opção -c, entrar no modo de controle de estoque
    if (argc > 1 && string(argv[1]) == "-c") {
        char opcao;
        do {
            exibeMenu();
            cin >> opcao;
            tratarOpcao(opcao, produtos, num_produtos);
        } while (opcao != 'S' && opcao != 's');
    }
    // Se não, fazer o pedido
    else {
        fazerPedido(produtos, num_produtos);

    }

    // Atualiza o estoque no arquivo binário
    ofstream fout("estoque.bin", ios::binary);

    if (!fout) {
        cout << "Erro ao abrir o arquivo.";
        exit(EXIT_FAILURE);
    }

    fout.write((char *)(produtos), num_produtos * sizeof(produto));
    fout.close();

    delete[] produtos;

}