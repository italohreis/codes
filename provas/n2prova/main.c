#include <stdio.h>
#include <stdbool.h>
#include "func.h"

#define red_text "\x1b[31m"
#define green_text "\x1b[32m"
#define reset_color "\x1b[0m"


/* Uma concessionária de veículos mantêm o cadastro de seus veículos desta forma:
    código do veículo (número inteiro),
    código da cor (número inteiro, 1 para branco, 2 para preto, 3 para vermelho e 4 para cinza),
    quantidade.

    A capacidade máxima de armazenagem nas suas garagens é de 150 veículos. Não permita que
    sejam cadastrados mais veículos do que a capacidade.

    Faça um programa que inicialmente leia os dados dos vários veículos que estão atualmente na
    concessionária. Serão cadastrados, no máximo 25 tipos de veículos. Não permita código do veículo
    com mesma cor em linhas diferentes.

    Após esta leitura inicial, ofereça ao vendedor, sempre que desejar, a possibilidade de consultar um
    destes relatórios: Relatório geral (mostre todos os veículos e seus dados, a quantidade total de
    veículos e a percentagem de ocupação das garagens), relatório por cor (dada a cor, mostre a
    quantidade total e todos os veículos desta cor), relatório por código (dado o código, mostre a
    quantidade total e todos os veículos com o código e seus dados), busca por veículo (Dados o
    código do veículo e sua cor, mostre a quantidade. Se o veículo for encontrado, a busca deve ser
    interrompida). Pode ocorrer a necessidade de cadastrar um veículo que tenha sido adquirido
    esporadicamente, então o programa deve ser capaz de inserir um veículo (apenas 1) a qualquer
    momento.  */



typedef struct {
    int codigo;
    int cor;
    int quantidadeCarro;
} carro;


int main(void){
    carro carros[25];
    
    for (int i = 0; i < 25; i++){
        carros[i].codigo = 0;
    }

    int QuantidadeTotal = 0;
    int numCor, numCodigo;
    int code, color;
    bool opcao = false;
    int resp, cCarros = 0;     //cCarros -> conta a quantidade de tipos de carros inseridos

    do{
        printf("\n---------------------------------------------------------------------------------\n");
        printf("\nCarro %d\n", cCarros);
        printf("\nDigite o codigo do carro --> ");
        scanf("%d", &code);

        color = 0;
        while(color < 1 || color > 4){          //estrutura de repeticao para verificar a resposta do usuario
            printf("\nDigite a cor do carro (1 - branco / 2 - preto / 3 - vermelho / 4 - cinza) --> ");
            scanf("%d", &color);

            if(color < 1 || color > 4){
                printf(red_text "\nCor invalida, tente novamente.\n" reset_color);
            }
        }

        QuantidadeCarros(code, color, &QuantidadeTotal, &cCarros);  //Função para inserir a quantidade de carros.

        resp = -1;
        while(resp != 0 && resp != 1){
            printf("\nDeseja inserir mais carros ? (1 - sim / 0 - nao) --> ");
            scanf("%d", &resp);

            if(resp != 0 && resp != 1){
                printf(red_text "\nResposta invalida, tente novamente.\n" reset_color);
            }
        }                                                 

        if (resp == 0){
            break;
        }
        printf("carros -> %d\n", cCarros);
        if(cCarros == 25){
            printf(red_text "\nLimite de carros atingido.\n" reset_color);
            break;
        }

    } while (resp == 1);


    int op;
    while (1){

        printf("\n\nO que deseja fazer ?\n\n");
        printf(" 1 - relatorio geral.\n 2 - relatorio por cor.\n 3 - relatorio por codigo.\n 4 - busca por veiculo.\n" 
        " 5 - inserir um veiculo.\n 6 - finalizar.\n");
        scanf("%d", &op);

        switch (op){
            case 1:
                RelatorioGeral(QuantidadeTotal);
                break;

            case 2:
                printf("\nQual cor deseja consultar ? --> ");
                scanf("%d", &numCor);
                
                RelatorioCor(numCor);

                break;

            case 3:
                printf("\nQual codigo do veiculo que deseja consultar ? --> ");
                scanf("%d", &numCodigo);
                
                RelatorioCodigo(numCodigo);

                break;

            case 4:
                printf("\nQual o codigo do veiculo ? --> ");
                scanf("%d", &numCodigo);
                printf("\nQual cor do veiculo ? --> ");
                scanf("%d", &numCor);
                
                BuscaVeiculo(numCodigo, numCor, cCarros);

                break;

            case 5:
                if(opcao == true){
                    printf(red_text "\nVeiculo ja adicionado.\n" reset_color);
                    break;
                }

                printf("\nQual o codigo do veiculo ? --> ");
                scanf("%d", &numCodigo);

                printf("\nQual cor do veiculo ? --> ");
                scanf("%d", &numCor);

                for(int i = 0; i < 25; i++){
                    if(carros[i].codigo == numCodigo && carros[i].cor == numCor){
                        carros[i].quantidadeCarro += 1;
                        QuantidadeTotal += 1;
                        break;
                    }

                    if(carros[i].codigo == 0){
                        carros[i].codigo = numCodigo;
                        carros[i].cor = numCor;
                        carros[i].quantidadeCarro = 1;
                        QuantidadeTotal += 1;

                        printf(green_text "\nVeiculo inserido com sucesso.\n" reset_color);
                        break;
                    }

                }

                opcao = true;
                
                break;
            case 6:
                printf("\nfim.\n");
                return 0;

            default:
                printf(red_text "\nResposta inválida, tente novamente.\n" reset_color);
        }
    }

    return 0;
}


