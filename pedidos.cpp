#include "pedidos.h"
#include <fstream>
#include <iostream>
#include <cctype>
using namespace std;

void exibeMenuCliente(produto * produtos, int numProdutos, char ** carrinho, int tamanhoCarrinho) {
    cout << "RapiZinho" << endl;
    cout << "==========" << endl;

    // Exibir itens do carrinho
    for (int i = 0; i < tamanhoCarrinho; ++i) {
        cout << carrinho[i] << endl;
    }

    cout << "==========" << endl;

    // Exibindo os produtos relacionados a letra de forma crescente
    for (int i = 0; i < numProdutos; ++i) {
        char opcao = 'A' + i;
        cout << "(" << opcao << ") " << produtos[i].nome << endl;
    }

    cout << "(S) Sair" << endl;
    cout << "==========" << endl;
}

void fazerPedido(produto * produtos, int numProdutos) {
    char opcao, confirmacao,pagamento;
    int quantidade = 0, indice = 0, numPedido = 1, tamanhoCarrinho = 0;
    float total = 0;
    float subtotal;
    float preco;
    float taxaEntrega = 6.00;
    char ** carrinho = new char * [numProdutos];

    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.precision(2);

    do {
        exibeMenuCliente(produtos, numProdutos, carrinho, tamanhoCarrinho);
        cout << "Opção: ";
        cin >> opcao;
        opcao = toupper(opcao);

        if (opcao == 'S' || opcao == 's') {
            break;
        }


        int indice = opcao - 'A';
        if (indice < 0 || indice >= numProdutos) {
            cout << "Opção inválida!" << endl;
            continue;
        }

        cout << "Pedido" << endl;
        cout << "======" << endl;
        cout << produtos[indice].nome << endl;
        cout << "R$" << produtos[indice].preco << endl;
        cout << "======\nQuantidade: ";
        cin >> quantidade;

        if (quantidade > produtos[indice].quantidade) {
            cout << "Quantidade solicitada não disponível em estoque!" << endl;
            continue;
        }

        preco = produtos[indice].preco;
        subtotal = quantidade * preco;
        total += subtotal;
        
       // Criando e concatenando os char[]
       char * strQuantidade = intParaChar(quantidade);
       char * strPreco = floatParaChar(preco);
       char * strSubtotal = floatParaChar(subtotal);
       int tamanhoString = strlen(strQuantidade) + strlen(produtos[indice].nome) + strlen(strPreco) + strlen(strSubtotal) + 15;
       
       carrinho[tamanhoCarrinho] = new char[tamanhoString];
       sprintf_s(carrinho[tamanhoCarrinho], tamanhoString, "%s x %s de R$%s = R$%s", strQuantidade, produtos[indice].nome, strPreco, strSubtotal);
      
       delete[] strQuantidade;
       delete[] strPreco;
       delete[] strSubtotal;

       ++tamanhoCarrinho;

    } while (true);

    // Exibe novamente os itens do carrinho
    for (int i = 0; i < tamanhoCarrinho; ++i) {
        cout << carrinho[i] << endl;
    }
    cout << "Taxa de entrega = R$" << taxaEntrega << endl;
    cout << "===========\nTotal = R$" << (total + taxaEntrega) << endl;
    cout << "\n\n[P] Pix\n[C] Cartão\nPagamento: "; cin >> pagamento;
    cout << "Taxa de entrega = R$" << taxaEntrega << endl;
    cout << "===========\nTotal = R$" << total << endl;

    if (pagamento == 'P' || pagamento == 'p')
        cout << "Desconto de 10% = R$" << total * 0.10 << endl;
    if (pagamento == 'C' || pagamento == 'c')
        cout << "Desconto de 5% = R$" << total * 0.5 << endl;
    cout << "Confirma Pedido (S/N): ";
    cin >> confirmacao;

    if (confirmacao == 'S' || confirmacao == 's') {
        // Atualizar o estoque no vetor
        for (int i = 0; i < numProdutos; ++i) {
            if (produtos[i].nome == produtos[indice].nome) {
                produtos[i].quantidade -= quantidade; // Subtrair a quantidade vendida do estoque
                break;
            }
        }

        char ped[20] = "pedido_";
        char txt[] = ".txt";
        bool arquivoExiste = true;

        // Verificando se o arquivo já existe
        do {
            char numPedidoStr[5];
            strcpy_s(numPedidoStr, intParaChar(numPedido));
            strcpy_s(ped + 7, 5, numPedidoStr);  
            strcat_s(ped, txt);

            ifstream arquivo(ped);
            if (arquivo.good()) {
                arquivo.close();
                ++numPedido;
                arquivoExiste = true;
            }
            else {
                arquivoExiste = false;
            }
        } while (arquivoExiste);

        // Gravar o pedido em um arquivo texto
        ofstream fout(ped, ios::app);
        fout << "Pedido #" << numPedido << endl;
        fout << "--------------------------------------------------\n";
        for (int i = 0; i < tamanhoCarrinho; ++i) {
            fout << carrinho[i] << endl;
        }
        fout << "Taxa de entrega = R$" << taxaEntrega << endl;
        if (pagamento == 'P' || pagamento == 'p')
            fout << "Desconto de 10% = R$" << total * 0.10 << endl;
        if (pagamento == 'C' || pagamento == 'c')
            fout << "Desconto de 5% = R$" << total * 0.5 << endl;
        fout << "--------------------------------------------------\n";
        fout << "Total = R$" << total << endl;
        fout.close();
    }
    // Liberando a memória
    for (int i = 0; i < tamanhoCarrinho; ++i) {
        delete[] carrinho[i];
    }
    delete[] carrinho;
    
}

char * intParaChar(int n)
{
    int copia = n;
    int tamanho = 0;

    // Calculando o tamanho do novo vetor
    while (copia != 0) {
        copia /= 10;
        ++tamanho;
    }

    // Cria o vetor
    char * result = new char[tamanho + 1];  
    result[tamanho] = '\0';  

    // Preenche o vetor
    for (int i = tamanho - 1; i >= 0; --i) {
        result[i] = '0' + (n % 10);
        n /= 10;
    }

    return result;
}

char * floatParaChar(float f)
{
    int inteiro = int(f);
    float fracionario = f - inteiro;

    // Converter a parte inteira para char
    char * parteInteira = intParaChar(inteiro);

    // Calcular o tamanho necessário para a parte fracionária
    int tamanhoFracionario = 0;
    // 6 casas decimais
    int copiaFracionario = int(fracionario * 10);

    while (copiaFracionario != 0) {
        copiaFracionario /= 10;
        ++tamanhoFracionario;
    }

    // Calcular o tamanho total
    int tamanhoTotal = strlen(parteInteira) + 1 + tamanhoFracionario + 1; 
    char * result = new char[tamanhoTotal];
    int posicao = 0;

    // Copiar a parte inteira para o resultado
    for (int i = 0; parteInteira[i] != '\0'; ++i) {
        result[posicao++] = parteInteira[i];
    }
    delete[] parteInteira;

    // Adicionar o ponto 
    result[posicao++] = '.';

    // Converter a parte fracionária para char
    char * fracionariaStr = new char[tamanhoFracionario + 1]; // +1 para o '\0'
    fracionariaStr[tamanhoFracionario] = '\0';

    for (int i = tamanhoFracionario - 1; i >= 0; --i) {
        fracionariaStr[i] = '0' + (fracionario * 10);
        fracionario = (fracionario * 10) - int(fracionario * 10);
    }

    // Copiar a parte fracionária para o resultado
    for (int i = 0; fracionariaStr[i] != '\0'; ++i) {
        result[posicao++] = fracionariaStr[i];
    }
    delete[] fracionariaStr;

    // Adicionar o caractere nulo
    result[posicao] = '\0';

    return result;
}

