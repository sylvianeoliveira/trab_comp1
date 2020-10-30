#ifndef FUNCOES_H
#define FUNCOES_H 
#include "estruturas.h"
void limpa_string(char string[]); /*Retira o \n da string*/
void limpa_ponteiros(VETORES vetor);

int valida_nome(char nickname[]); /*!!!!!! falar com o grupo se compensa fazer isso daqui so que usando funcao recursiva(diminuiria o codigo principal)  !!!!!!*/
int valida_acesso_regras(void); /*Valida o acesso a regras*/
int valida_nivel(void); /*Valida o nivel de jogo*/
int valida_tentativa (VETORES vetor, int intervalo, int tamanho);

void gerador_senha(VETORES vetor,int nivel); /*Gera uma senha de acordo com o nível escolhido*/
void calcula_acertos(VETORES vetor, int tamanho); /*Retorna o vetor com a legenda de acertos*/
int compara_tentativa_senha(VETORES vetor, int tamanho); /*Verifica se a tentativa é igual a senha*/

#endif