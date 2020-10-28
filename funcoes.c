#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include "funcoes.h" /*Novo*/

void valida_nivel(int *nivel) {

}

void gerador_senha(int *senha,int nivel) {/*De acordo com o nivel do jogo ele gera uma senha diferente*/
    int i,pos;
    int sorteados[6]={1,2,3,4,5,6};
    srand( (unsigned)time(NULL));
    if(nivel == 1) {/*Nivel 1 gera uma senha de 4 digitos de 1 a 6 sem repetição*/
      for (i=0; i < 4; i++){
        pos = rand() % 5;
        if(sorteados[pos] != 0){
            senha[i] = sorteados[pos];
            sorteados[pos] = 0;
        }
        else i--;
        }
    }
    else if(nivel == 2){/*Nivel 2 gera uma senha de 4 digitos de 1 a 6 com repetição */
    for (i=0; i < 4; i++){
        senha[i] = 1 + rand() % 6;
        }
    }
    else if(nivel == 3){/*Nivel 3 gera uma senha de 6 digitos com repetição*/
        senha = (int *) realloc(senha, 6 * sizeof(int));
        for (i=0; i < 6; i++){
            senha[i] = 1 + rand() % 7;
        }
    }
}

void limpar_ponteiros(int *tentativa,char *preto_branco) {
    *tentativa = 0;
    *preto_branco = 0;
}

void verifica_bola_pretas(int *tentativa, int *senha, char *preto, int tam) {
   int i;
   /*Esse for verifica se a tentativa esta na posicao certa e preenche o resto com traços*/
    for (i = 0; i < tam; i++){
        if(tentativa[i]==senha[i]) preto[i] = 'X';
    }
}

void verifica_bola_brancas(int *tentativa, int *senha, char *branco, int tam) {
    int i,j;
    int *aux;
    aux = (int *)malloc(tam * sizeof(int));
    /*Criei um auxiliar para remover os elementos que ja foram checados e nao gerar erro no codigo*/
    for (i = 0; i < tam; i++) {
        aux[i] = senha[i];
    }
    /*esse for verifica se o resto dos elementos do vetor que nao foram verificados aparecem em alguma posicao*/
    for (i = 0; i < tam; i++) {  
        for ( j = 0; j < tam; j++) {
         if(tentativa[i] == aux[j] && branco[i]!='X'&& branco[j]!='X') { 
             branco[i] = 'O';
             aux[j] = 0;
            }
        }
    }
    /*Se a posição do vetor não for 'x' ou 'o' vai receber um traço '-'*/
    for (i = 0; i < tam; i++) {
        if(branco[i]!='X' && branco[i]!='O') branco[i]='-';
    }
}

void limpa_nome(char nickname[]) {
    int tam = strlen(nickname);
    int i;
    
    for(i = 0; i < tam; i++) {
        
        if(nickname[i]=='\n') {
            nickname[i] = '\0';
        }

    }

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

int complexidade_jogo(void){
    char nivel[32];

    while(1){
        fgets(nivel, 32, stdin);
        limpa_nome(nivel);
        if (strlen(nivel) == 1){
            if (nivel[0] < 49 || nivel[0] > 51){
                printf("Complexidade de código inválida.\n");
            }
            else{
                break;
            }
        }
        else{
            printf("Complexidade de código inválida.\n");
        }
    }
    return nivel[0] - '0';
}

int validacao_acesso_regras(void) {
    char regras[32];
    while(1){
        fgets(regras, 32, stdin);
        limpa_nome(regras);
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