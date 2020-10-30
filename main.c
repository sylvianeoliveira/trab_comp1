#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "funcoes.h"

int main(void){
    FILE *arquivo, *arquivo2;
    VETORES vetor;
    char c;
    int i, resposta, vidas, tamanho, intervalo, jogar_novamente, acesso_regras;
    char nickname[30];
    /*int acesso_regras = 42; falta arrumar a funcao daqui*/
    int teste_de_nome = 42;   /*para nao causar problemas com o retorno*/
    char nivel_do_jogo; 
    /*system("chcp 65001"); Para windows*/
    /*setlocale(LC_ALL, "Portuguese"); Para linux*/

    printf("Seja muito bem vindo ao Mastermind\n\n"); /*Mensagem de Boas-Vindas*/

    /***Solicita o nome do usuario***/
    while(1){
        printf("Informe seu nome (somente letras e números): \n");
        fgets(nickname,30,stdin);
        limpa_string(nickname);
        valida_nome(nickname);

        teste_de_nome = valida_nome(nickname);
        if (teste_de_nome == 1){
            printf("Nome aceito com sucesso.\n\n");
            break;
        }
        printf("Nome inválido\n");
    }

    printf("%s, chegou a hora de treinar suas habilidades em quebrar códigos.\n", nickname); /*Saudação para iniciar o jogo*/
    
    while(1){ /*O jogo em loop até o usuário desejar sair*/
        /***Alocação de memória para os vetores abaixo***/
        vetor.bolas_branca_e_preta = (char *) malloc(4 * sizeof(char));
        vetor.tentativa = (char *) malloc(4*sizeof(char));
        vetor.senha = (int *) malloc(4*sizeof(int));

        /***Decisão para ler ou não as regras***/
        printf("\nDeseja acessar o codigo de regras? (Digite 1 para sim, 0 para não)\n");
        acesso_regras = valida_acesso_regras();
        if (acesso_regras == 1){
            printf("\n");
            arquivo2 = fopen("regras.txt", "r"); /*Abre o arquivo de regras para leitura*/

            c = fgetc(arquivo2);
            while (!feof(arquivo2)){ /*While para imprimir o arquivo regra.txt*/
                putchar(c);
                c = fgetc(arquivo2);
            }

            fclose(arquivo2);
            printf("\nAgora que você já leu as regras, vamos ao jogo!\n");
        }
        else if (acesso_regras == 0){
            printf("\nNesse caso, vamos ao jogo.\n");
        }

        printf("\n");

        /***Escolha do nível do jogo***/
        printf("Escolha o nível em que deseja jogar: \n");
        printf("Digite 1 para nível fácil.\n");
        printf("Digite 2 para nível intermediário.\n");
        printf("Digite 3 para nível difícil.\n");

        nivel_do_jogo = valida_nivel(); /*Função que valida o nível escolhido pelo usuário e retorna o nível escolhido quando válido*/

        /***Avisos acerca da legenda utilizada no jogo***/
        printf("\n");
        printf("Aviso:\n");
        printf("Cada 'X' indica a quantidade números digitados por você que estão no codigo e estão na posição correta.\n");
        printf("Cada 'O' indica a quantidade números digitados por você que estão no codigo, mas na posição errada.\n");
        printf("\n");

        /***Switch para determinar as condições de cada nível***/
        switch (nivel_do_jogo){
        case 1:
            printf("Senha fácil gerada com sucesso.\n");
            tamanho = 4; /*Tamanho da senha*/
            vidas = 10; /*Quantidade de tentativas possíveis*/
            intervalo = 6; /*Opções de digitos: 1 a 6*/
            break;

        case 2:
            printf("Senha intermediária gerada com sucesso.\n");
            tamanho = 4; /*Tamanho da senha*/
            vidas = 15; /*Quantidade de tentativas possíveis*/
            intervalo = 6; /*Opções de digitos: 1 a 6*/
            break;

        case 3:
            printf("Senha difícil gerada com sucesso.\n");
            printf("Boa sorte %s, vai precisar.\n", nickname); /*Mensagem para usuários*/
            tamanho = 4; /*Tamanho da senha*/
            vidas = 20; /*Quantidade de tentativas possíveis*/
            intervalo = 8; /*Opções de digitos: 1 a 8*/

            /*vetor_bolas_branca_e_preta = (char *) realloc(vetor_bolas_branca_e_preta, 6 * sizeof(char));
            vetor_tentativa = (int *) realloc(vetor_tentativa, 6 * sizeof(int)); */
            break;
        default:
            break;
        }

        gerador_senha(vetor, nivel_do_jogo); /*Função que gera uma senha aleatória de acordo com o nível escolhido*/

        /*printf("%d %d %d %d\n", vetor.senha[0], vetor.senha[1], vetor.senha[2], vetor.senha[3]); Tirar no final*/

        arquivo = fopen("tela.txt", "w"); /*Limpa a tela antes de começar*/
        fclose(arquivo);

        /***Solicita ao usuário tentativas de acordo com sua quantidade de vidas***/
        for(i=0; i < vidas; i++){
            printf("\nTentativa: %d.\n", i+1);
            while(1){ /*While que verifica se a senha é válida*/
                printf("Digite uma senha sem espaço entre os digitos: "); /*Pede a tentativa*/
                fgets(vetor.tentativa, 32, stdin); /*Lê a tentativa*/
                limpa_string(vetor.tentativa); /*Limpa o \n do vetor tentativa*/
                resposta = valida_tentativa(vetor, intervalo, tamanho); /*Função que valida a senha e retorna 1 ou 0*/
                if (resposta == 1) break; /*Interrompe o while quando a tentativa é válida*/
            }
            
            calcula_acertos(vetor, tamanho); /*Função que retorna o vetor_bolas_branca_e_preta com a legenda de acertos*/

            arquivo = fopen("tela.txt", "a"); /*Escreve a nova linha*/
            if (arquivo == NULL) exit(1);

            /***Atribui a linha com os valores na tela do jogo***/
            fprintf(arquivo, "%c %c %c %c || %c %c %c %c\n", vetor.tentativa[0], vetor.tentativa[1], vetor.tentativa[2], vetor.tentativa[3],
            vetor.bolas_branca_e_preta[0], vetor.bolas_branca_e_preta[1], vetor.bolas_branca_e_preta[2], vetor.bolas_branca_e_preta[3]);

            fclose(arquivo);

            arquivo = fopen("tela.txt", "r+"); /*Imprime a tela do jogo para o usuário*/

            c = fgetc(arquivo);
            while (!feof(arquivo)){ /*While para imprimir o arquivo tela.txt*/
                putchar(c);
                c = fgetc(arquivo);
            }
            fclose(arquivo);

            if (compara_tentativa_senha(vetor, tamanho) == 1){ /*Imprime a mensagem de vitória e encerra a atribuição de tentativas*/
                printf("Parabéns! Você venceu o jogo!\n");
                break;
            }
            else if ((compara_tentativa_senha(vetor, tamanho) == 0) && (i ==  vidas - 1)){ /*Imprime a mensagem de derrota quando acabam as
                                                                                           tentativas e o usuário não acertou a senha*/
                printf("Derrota! Você perdeu o jogo!\n");
                /**Informa qual era a senha ao usuário que perdeu**/
                printf("A senha era: %d %d %d %d\n", vetor.senha[0], vetor.senha[1], vetor.senha[2], vetor.senha[3]);
            }
            limpa_ponteiros(vetor); /*Limpa os vetores tentativa e bolas a cada rodada*/
        }

        /***Limpa os vetores utilizados***/
        free(vetor.bolas_branca_e_preta);
        free(vetor.senha);
        free(vetor.tentativa);

        printf("\n%s, você deseja jogar novamente? (Digite 1 para sim, 0 para não)\n", nickname); /*Pergunta se o usuário deseja jogar novamente*/
        jogar_novamente = valida_acesso_regras();
        if (jogar_novamente == 0) exit(0); /*Se o usuário não desejar, o programa encerra*/
    }
    
    return 0;
}