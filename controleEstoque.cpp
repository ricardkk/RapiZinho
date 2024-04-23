#include "controleEstoque.h"
#include "produto.h"
#include <iostream>
using namespace std;



void exibeMenu()
{
    cout << "\nPainel de Controle" << endl;
    cout << "===================" << endl;
    cout << "(A)dicionar" << endl;
    cout << "(E)xcluir" << endl;
    cout << "(L)istar" << endl;
    cout << "(S)air" << endl;
    cout << "===================" << endl;
    cout << "Opcao: ";
}

void adicionarProdutos(produto *& produtos, int & num_produtos)
{
    char nome[24];
    float preco;
    unsigned int quantidade;
    cout << "\nAdicionar" << endl;
    cout << "--------" << endl;
    cout << "Produto: "; cin.ignore(); cin.getline(nome,24);
    cout << "Preço: "; cin >> preco;
    cout << "Quantidade: "; cin >> quantidade;

    // Verifica se o produto já existe no vetor
    for (int i = 0; i < num_produtos; ++i) {
        if (strcmp(produtos[i].nome, nome) == 0) {
            produtos[i].preco = preco;
            produtos[i].quantidade += quantidade;
            return; 
        }
    }

    // Se não existir, expandir vetor
    produtos = expandirVetor(produtos, num_produtos, ++num_produtos);

    // Adiciona o novo produto ao final do vetor
    strcpy_s(produtos[num_produtos - 1].nome, nome);
    produtos[num_produtos - 1].preco = preco;
    produtos[num_produtos - 1].quantidade = quantidade;
}

void excluirProdutos(produto *& produtos, int & num_produtos)
{
    cout << "\nExcluir" << endl;
    cout << "-------" << endl;

    // Exibir a lista numerada dos produtos
    for (int i = 0; i < num_produtos; ++i) {
        cout << i + 1 << ") " << produtos[i].nome << endl;
    }

    int escolha;
    cout << "Produto: ";
    cin >> escolha;

    if (escolha < 1 || escolha > num_produtos) {
        cout << "Escolha inválida!" << endl;
        return;
    }

    // Confirmar a exclusão com o usuário
    char confirmacao;
    cout << "Deseja excluir \"" << produtos[escolha - 1].nome << "\" (S/N)? ";
    cin >> confirmacao;

    if (confirmacao == 'S' || confirmacao == 's') {
        // Remover o produto do vetor de produtos
        for (int i = escolha - 1; i < num_produtos - 1; ++i) {
            produtos[i] = produtos[i + 1];
        }
        num_produtos--;  // Atualizar o número de produtos
        cout << "Produto excluído com sucesso!" << endl;
    }
    else {
        cout << "Operação de exclusão cancelada." << endl;
    }
}

void listarProdutos(produto * produtos, int num_produtos)
{
   cout << "\nListagem" << endl;
   cout << "--------" << endl;
    for (int i = 0; i < num_produtos; ++i) {
        cout << produtos[i].nome << " - R$" << produtos[i].preco << " - " << produtos[i].quantidade << " und." << std::endl;
    }
}

void tratarOpcao(char opcao, produto *& produtos, int & num_produtos) {
    switch (toupper(opcao)) {
    case 'A':
        adicionarProdutos(produtos, num_produtos);
        break;
    case 'E':
        excluirProdutos(produtos, num_produtos);
        break;
    case 'L':
        listarProdutos(produtos, num_produtos);
        break;
    case 'S':
        cout << "Saindo do modo de controle de estoque." << endl;
        break;
    default:
        cout << "Opção inválida. Tente novamente." << endl;
    }
}

produto * expandirVetor(produto *& produtos, int & num_produtos, int & novoTamanho) {
    // Cria um vetor com o novo tamanho e copia todos os elementos do antigo para o novo
    produto * novoVetor = new produto[novoTamanho];

    for (int i = 0; i < num_produtos; ++i) {
        novoVetor[i] = produtos[i];
    }

    delete[] produtos;
    return novoVetor;
}