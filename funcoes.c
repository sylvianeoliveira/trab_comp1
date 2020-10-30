#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estruturas.h"
#include "funcoes.h"

void limpa_string(char string[]) {
    int tam = strlen(string);
    int i;
    
    for(i = 0; i < tam; i++) { 
        if(string[i]=='\n') {
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
        limpa_string(regras);
        if (strlen(regras) == 1){
            if (regras[0] != '0' && regras[0] != '1'){
                printf("Comando inválido.\n");
            }
            else{
                break;
            }
        }
        else{
            printf("Comando inválido.\n");
        }
    }
    return regras[0] - '0';
}

int valida_nivel(void){
    char nivel[32];

    while(1){
        fgets(nivel, 32, stdin);
        limpa_string(nivel);
        if (strlen(nivel) == 1){
            if (nivel[0] < 49 || nivel[0] > 51){
                printf("Nível de jogo inválido.\n");
            }
            else{
                break;
            }
        }
        else{
            printf("Nível de jogo inválido.\n");
        }
    }
    return nivel[0] - '0';
}

int valida_tentativa (VETORES vetor, int intervalo, int tamanho){
    int i;
    char intervalo_char = intervalo + '0';
    if (strlen(vetor.tentativa) == tamanho){
        for(i=0; i < tamanho; i++){
            if (vetor.tentativa[i] >= 49 && vetor.tentativa[i] <= intervalo_char){
                continue;
            }
            else{
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

void gerador_senha(VETORES vetor,int nivel) {/*De acordo com o nivel do jogo ele gera uma senha diferente*/
    int i,pos;
    int sorteados[6]={1,2,3,4,5,6};
    srand( (unsigned)time(NULL));
    
    if(nivel == 1) {/*Nivel 1 gera uma senha de 4 digitos de 1 a 6 sem repetição*/
      for (i=0; i < 4; i++) {
            pos = rand() % 5;

        if(sorteados[pos] != 0) {
            vetor.senha[i] = sorteados[pos];
            sorteados[pos] = 0;
        }

        else i--;
        }
    }

    else if(nivel == 2) {/*Nivel 2 gera uma senha de 4 digitos de 1 a 6 com repetição */
        for (i=0; i < 4; i++){
            vetor.senha[i] = 1 + rand() % 6;
        }
    }
    else if(nivel == 3) {/*Nivel 3 gera uma senha de 6 digitos com repetição*/
        vetor.senha = (int *) realloc(vetor.senha, 6 * sizeof(int));
        for (i=0; i < 6; i++){
            vetor.senha[i] = 1 + rand() % 7;
        }
    }
}

void calcula_acertos(VETORES vetor, int tamanho){
    int i, j, contador = 0;
    int *vetor_tentativa_int, *aux;

    vetor_tentativa_int = (int *)malloc(tamanho * sizeof(int)); /*Aloca memória para o vetor inteiro de tentativa*/
    aux = (int *)malloc(tamanho * sizeof(int)); /*Aloca memória para o vetor auxliar*/

    /***Inicia o vetor de bolas com traços '-'***/
    for (i = 0; i < tamanho; i++){
        vetor.bolas_branca_e_preta[i] = '-';
    }

    /***Copia a senha para um vetor auxiliar***/
    for (i = 0; i < tamanho; i++) {
        aux[i] = vetor.senha[i];
    }

   /***Verifica quais números da tentativa estão corretos e na posicao certa 'X'***/
    for (i = 0; i < tamanho; i++){
        vetor_tentativa_int[i] = vetor.tentativa[i] - '0'; /*Converte de char para inteiro*/

        if(vetor_tentativa_int[i] == vetor.senha[i]) {
            vetor.bolas_branca_e_preta[contador] = 'X';
            aux[i] = 0; /*Substitui o valor analisado para um 0*/
            contador++; /*Altera o contador para a legenda não sobrescrever uma posição já preenchida*/
        }
    }

    /***Verifica quais números da tentativa restante estão corretos mas na posição errada***/
    for (i = 0; i < tamanho; i++) {  
            for ( j = 0; j < tamanho; j++) {
                if((vetor.bolas_branca_e_preta[i]!='X' && vetor.bolas_branca_e_preta[j]!='X') && vetor_tentativa_int[i] == aux[j]) { 
                    vetor.bolas_branca_e_preta[contador] = 'O'; 
                    contador++; /*Altera o contador para a legenda não sobrescrever uma posição já preenchida*/
                    aux[j] = 0; /*Substitui o valor analisado para um 0*/
                }
            }
    }
}

int compara_tentativa_senha(VETORES vetor, int tamanho){
    int i, *vetor_tentativa_int;

    vetor_tentativa_int = (int *) malloc(tamanho * sizeof(int)); /*Aloca memória para o vetor inteiro de tentativa*/

    for(i=0; i < tamanho; i++){
        vetor_tentativa_int[i] = vetor.tentativa[i] - '0'; /*Converte de char para inteiro*/
        if (vetor_tentativa_int[i] == vetor.senha[i]) continue;
        else{
            return 0;
        }
    }
    return 1; /*Retorna 1, pois a senha e a tentativa são iguais*/
}




