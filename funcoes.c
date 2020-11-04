#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "estruturas.h"
#include "funcoes.h"

#define TAMANHO_SENHA 4


void acesso_caractere_especial(void){
    #if defined(linux) || defined(unix) || defined(APPLE)
        setlocale(LC_ALL, "Portuguese");
    #endif
 
    #if defined(_WIN32) || defined(_WIN64)
        system("chcp 65001");
    #endif
}

void limpa_buffer(void){
    #if defined(linux) || defined(unix) || defined(APPLE)
       __fpurge(stdin);
    #endif
 
    #if defined(_WIN32) || defined(_WIN64)
       fflush(stdin);
    #endif
}


void limpa_string(char string[]) {
    int tam = strlen(string);
    int i;
    
    for(i = 0; i < tam; i++) { 
        if(string[i]=='\n') { /*Se for \n, substitui por \0*/
            string[i] = '\0';
        }
    }
}

void limpa_ponteiros(VETORES vetor) {
    vetor.tentativa[0] = '\0';
    vetor.bolas_branca_e_preta = '\0';
}


int valida_nome(char nickname[]) {
    int i,tam;
    
    tam = strlen(nickname);

    if(tam > 30)  return 0;

    /*aplicação das restrições do nome*/
    for(i = 0; i < tam; i++) {
        if( !( (nickname[i] >= 'A' && nickname[i] <= 'Z') || (nickname[i] >= 'a' && nickname[i] <= 'z') || (nickname[i] >= '0' && nickname[i] <= '9') || nickname[i]==' ') ) {
    
            return 0;
        }
    }

    return 1;
}

int valida_acesso_regras(void) {
    char regras[32];
    while(1){
        fgets(regras, 32, stdin);
        limpa_buffer();
        limpa_string(regras);
        if (strlen(regras) == 1){
            if (regras[0] != '0' && regras[0] != '1'){ /*Imprime comando invválido nas tentativas inválidas*/
                printf("Comando inválido.\n");
            }
            else{
                break;
            }
        }
        else{ /*Imprime comando invválido nas tentativas inválidas*/
            printf("Comando inválido.\n");
        }
    }
    return regras[0] - '0';
}

int valida_nivel(void){
    char nivel[32];

    while(1){
        fgets(nivel, 32, stdin);
        limpa_buffer();
        limpa_string(nivel);
        if ((strlen(nivel) == 1) && (nivel[0] >= 49 && nivel[0] <= 51)) break; /*Para para retornar o nível 1, 2 ou 3*/

        else if((strlen(nivel) == 2) && (nivel[0] == '4' && nivel[1] == '2')) return 42; /*Retorna o nível do easteregg*/

        else printf("Nível inválido\n");
    }
    return nivel[0] - '0';
}

int valida_tentativa (VETORES vetor, int intervalo){
    int i;
    char intervalo_char = intervalo + '0';
    if (strlen(vetor.tentativa) == TAMANHO_SENHA){
        for(i=0; i < TAMANHO_SENHA; i++){
            if (vetor.tentativa[i] >= 49 && vetor.tentativa[i] <= intervalo_char){ /*Continua se a tentativa estiver válida até o momento*/
                continue;
            }
            else{ /*Retorna 0 quando a tentativa não é valida*/
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

void easteregg(char nickname[]){
    char world[5] = "world"; /*Vetor de comparação*/
    char andre[11] = "andre brito"; /*Vetor de comparação*/
    char valeria[14] = "valeria bastos"; /*Vetor de comparação*/
    int i, tamanho, validador = 0;
    tamanho = strlen(nickname);

    for (i=0; i < tamanho; i++){ /*Compara se a string é igual a world*/
        if ((tamanho == 5) && (nickname[i] == world[i] || nickname[i] == world[i] - 32)) validador = 1;
        else{
            validador = 0;
            break;
        }
    }
    if (validador == 1) printf("Hello ");

    for (i=0; i < tamanho; i++){ /*Compara se a string é igual a 'andre' ou 'andre brito'*/
        if ((tamanho == 5 || tamanho == 11) && (nickname[i] == andre[i] || nickname[i] == andre[i] - 32)) validador = 1;
        else{
            validador = 0;
            break;
        }
    }
    if (validador == 1) printf("Professor??? :o \n\n");

    for (i=0; i < tamanho; i++){ /*Compara se a strig é igual a 'valeria' ou 'valeria bastos'*/
        if ((tamanho == 7 || tamanho == 14) && (nickname[i] == valeria[i] || nickname[i] == valeria[i] - 32)) validador = 1;
        else{
            validador = 0;
            break;
        }
    }
    if (validador == 1) printf("Professora??? :o\n\n");  
}

void gerador_senha(VETORES vetor,int nivel) {
    int i,pos;
    int sorteados[6]={1,2,3,4,5,6};
    srand( (unsigned)time(NULL));
    
    if(nivel == 1) {/*Nivel 1 gera uma senha de 4 digitos de 1 a 6 sem repetição*/
      for (i=0; i < TAMANHO_SENHA; i++){
            pos = rand() % 5;

        if(sorteados[pos] != 0){
            vetor.senha[i] = sorteados[pos];
            sorteados[pos] = 0;
        }
        else i--;
        }
    }

    else if(nivel == 2) {/*Nivel 2 gera uma senha de 4 digitos de 1 a 6 com repetição */
        for (i=0; i < TAMANHO_SENHA; i++){
            vetor.senha[i] = 1 + rand() % 5;
        }
    }

    else if(nivel == 3) {/*Nivel 3 gera uma senha de 4 digitos de 1 a 8 com repetição*/
        for (i=0; i < TAMANHO_SENHA; i++){
            vetor.senha[i] = 1 + rand() % 7;
        }
    }

    else if(nivel == 42){ /*Modo desafio gera uma senha de 4 dígitos de 1 a 9 com repetição*/
        for (i=0; i < TAMANHO_SENHA; i++){
            vetor.senha[i] = 1 + rand() % 8;
        }
    }
}

void calcula_acertos(VETORES vetor){
    int i, j, contador = 0;
    int *vetor_tentativa_int, *aux;

    vetor_tentativa_int = (int *)malloc(TAMANHO_SENHA * sizeof(int)); /*Aloca memória para o vetor inteiro de tentativa*/
    aux = (int *)malloc(TAMANHO_SENHA * sizeof(int)); /*Aloca memória para o vetor auxliar*/

    /***Inicia o vetor de bolas com traços '-'***/
    for (i = 0; i < TAMANHO_SENHA; i++){
        vetor.bolas_branca_e_preta[i] = '-';
    }

    /***Copia a senha para um vetor auxiliar***/
    for (i = 0; i < TAMANHO_SENHA; i++) {
        aux[i] = vetor.senha[i];
    }

   /***Verifica quais números da tentativa estão corretos e na posicao certa 'X'***/
    for (i = 0; i < TAMANHO_SENHA; i++){
        vetor_tentativa_int[i] = vetor.tentativa[i] - '0'; /*Converte de char para inteiro*/

        if(vetor_tentativa_int[i] == vetor.senha[i]) {
            vetor.bolas_branca_e_preta[contador] = 'X';
            aux[i] = 0; /*Substitui o valor analisado para um 0*/
            vetor_tentativa_int[i] = 0;
            contador++; /*Altera o contador para a legenda não sobrescrever uma posição já preenchida*/
        }
    }
    /***Verifica quais números da tentativa restante estão corretos mas na posição errada***/
    for (i = 0; i < TAMANHO_SENHA; i++){  
        for ( j = 0; j < TAMANHO_SENHA; j++){
            if(vetor_tentativa_int[i] == aux[j] && vetor_tentativa_int[i] != 0){ /*Verifica se o algarismo da tentativa está em algum lugar da senha*/
                vetor.bolas_branca_e_preta[contador] = 'O'; /*Se estiver, acrescenta um 'O'*/
                contador++; /*Altera o contador para a legenda não sobrescrever uma posição já preenchida*/
                aux[j] = 0; /*Substitui o valor analisado da senha para um 0*/
                break; /*Para de procurar em senha porque já achou*/
            }
        }
    }
    free(vetor_tentativa_int);
    free(aux);
}

int compara_tentativa_senha(VETORES vetor){
    int i, *vetor_tentativa_int;

    vetor_tentativa_int = (int *) malloc(TAMANHO_SENHA * sizeof(int)); /*Aloca memória para o vetor inteiro de tentativa*/

    for(i=0; i < TAMANHO_SENHA; i++){
        vetor_tentativa_int[i] = vetor.tentativa[i] - '0'; /*Converte de char para inteiro*/
        if (vetor_tentativa_int[i] == vetor.senha[i]) continue;
        else{
            return 0;
        }
    }
    return 1; /*Retorna 1, pois a senha e a tentativa são iguais*/
}