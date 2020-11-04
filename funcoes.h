#ifndef FUNCOES_H
#define FUNCOES_H
#include <locale.h>
#include "estruturas.h"

void acesso_caractere_especial(void); /*Permite imprimir caracteres especiais na tela*/
void limpa_buffer(void); /*Limpa o buffer em diferentes sistemas operacionais*/

void limpa_string(char string[]); /*Retira o \n da string*/
void limpa_ponteiros(VETORES vetor); /*Zera os ponteiros*/

int valida_nome(char nickname[]); /*Valida o nome inserido pelo usuário*/
int valida_acesso_regras(void); /*Valida o acesso a regras*/
int valida_nivel(void); /*Valida o nivel de jogo*/
int valida_tentativa (VETORES vetor, int intervalo); /*Valida cada tentativa feita pelo usuário no jogo*/

void easteregg(char nickname[]); /*Trata e verifica o caso de easteregg*/
void gerador_senha(VETORES vetor,int nivel); /*Gera uma senha de acordo com o nível escolhido*/
void calcula_acertos(VETORES vetor); /*Retorna o vetor com a legenda de acertos*/
int compara_tentativa_senha(VETORES vetor); /*Verifica se a tentativa é igual a senha*/

#endif