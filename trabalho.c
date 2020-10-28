#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include "funcoes.h" /*Novo*/

/*Estruturas*/
typedef struct{
    char nome[50];
} DADOS;
typedef struct {
    char *bolas_branca_e_preta;
    int *senha,*tentativa;
} VETORES;
/**/

int main(void) {
    VETORES vetor;
    int i,vidas=10,TAM;
     char nickname[11];
    int acesso_regras = 42; /*falta arrumar a funcao daqui*/
    int teste_de_nome = 42;   /*para nao causar problemas com o retorno*/
    char nivel_do_jogo; 
    vetor.bolas_branca_e_preta = (char *)malloc(4 * sizeof(char));
    vetor.tentativa= (int *)malloc(4*sizeof(int));
    vetor.senha = (int *)malloc(4*sizeof(int));
    printf("Seja muito bem vindo ao Mastermind\n");
    printf("\n");

    /*nome do usuario*/
    printf("informe seu nome, max de 10 caracteres, sendo eles números ou letras.\n");/**/
    fgets(nickname,11,stdin);
    limpa_nome(nickname);
    valida_nome(nickname);

    teste_de_nome = valida_nome(nickname);

    while(teste_de_nome == 0) {
        printf("Nome inválido.\n");
        printf("Informe seu nome, max de 10 caracteres, sendo eles números ou letras.\n");
        fgets(nickname,11,stdin);
        limpa_nome(nickname);
        teste_de_nome = valida_nome(nickname);
    }
    
    if(teste_de_nome == 1) {
        printf("Nome aceito com sucesso.\n");
    }

    printf("\n");
    /*saudações*/
    printf("%s, chegou a hora de treinar suas habilidades em quebrar códigos.\n", nickname);
    
    /*decisao de acessar ou nao as regras*/
    printf("Deseja acessar o codigo de regras? (digite 1 para sim, 0 para não)\n");
    acesso_regras = validacao_acesso_regras();

    /*if (acesso_regras == 1){     
        ponteiro_para_regras = fopen("regras.txt","r");

        if(ponteiro_para_regras == NULL) {
            !!!!!!!!!!!! remover esse print !!!!!!!!!!!!!!
            printf("o arquivo nao quer abrir, corrijam isso\n");
            exit(5);
        }

        printando as regras no console
        c = fgetc(ponteiro_para_regras);
        while(!feof(ponteiro_para_regras)) {
            putchar(c);
            c = fgetc(ponteiro_para_regras);  
        }
        fclose(ponteiro_para_regras);
    
    }*/
    if (acesso_regras == 0){
        printf("Nesse caso, vamos ao codigo.\n");
    }


    printf("\n");
    printf("Complexidade do código:\n"); /*sobrando tempo incluimos o desafio*/
    printf("Digite 1 para nível fácil.\n");
    printf("Digite 2 para nível intermediário.\n");
    printf("Digite 3 para nível difícil.\n");
    nivel_do_jogo = complexidade_jogo();

    printf("\n");
    printf("Dicas:\n");
    printf("Cada 'X' indica a quantidade números digitados por você que estão no codigo e estão na posição correta.\n");
    printf("Cada 'O' indica a quantidade números digitados por você que estão no codigo, mas na posição errada.\n");

        
    
    switch (nivel_do_jogo){

    case 1:
        printf("Código fácil gerado com sucesso.\n");
        TAM = 4;
        vidas = 10;
        break;

    case 2:
        printf("Código intermediário gerado com sucesso.\n");
        TAM = 4;
        vidas = 15;
        break;

    case 3:
        printf("Código difícil gerado com sucesso.\n Boa sorte %s, vai precisar.", nickname);
        TAM = 4;
        vidas = 20;
        vetor.bolas_branca_e_preta = (char *) realloc(vetor.bolas_branca_e_preta, 6 * sizeof(char));
        vetor.tentativa = (int *) realloc(vetor.tentativa, 6 * sizeof(int)); 
        break;
    default: /*!!!!!!!!! esse default aqui ta com problema?   !!!!!!!!!!*/
        puts("Error 404");
        break;
    }

    gerador_senha(vetor.senha,nivel_do_jogo);
    for (i = 0; i < TAM; i++)
    {
      printf("%d",vetor.senha[i]);
    }

    while(vidas!=0) {
    printf("\n");
    printf("Digite uma senha(com espaco entre os digitos e depois tecle enter): ");
    
    for (i = 0; i < TAM; i++) {
        scanf("%d",&vetor.tentativa[i]);
    
    }
    
    printf("\n");
    verifica_bola_pretas(vetor.tentativa, vetor.senha, vetor.bolas_branca_e_preta, TAM);
    verifica_bola_brancas(vetor.tentativa, vetor.senha, vetor.bolas_branca_e_preta, TAM);
    puts("Senha:* * * * ");
    puts("Tentativa:");
    for (i = 0; i < TAM; i++) {
      printf("%d",vetor.tentativa[i]);
    }
        printf(" || %s\n",vetor.bolas_branca_e_preta);
        vidas--;
        limpar_ponteiros(vetor.tentativa,vetor.bolas_branca_e_preta);
        printf("Digite uma senha: ");
     }
        free(vetor.bolas_branca_e_preta);
        free(vetor.senha);
        free(vetor.tentativa);
    
    return 0;
}