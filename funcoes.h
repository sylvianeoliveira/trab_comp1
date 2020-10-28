#ifndef FUNCOES_H
#define FUNCOES_H /*Novo*/

void verifica_bola_pretas(int *tentativa, int *senha, char *preto, int tam);
void verifica_bola_brancas(int *tentativa, int *senha, char *branco, int tam);
void Verifica_Tentativa(int *senha);
void limpa_nome(char nickname[]); /*tira o enter*/
int validacao_acesso_regras(void);
int complexidade_jogo(void);
int valida_nome(char nickname[]); /*!!!!!! falar com o grupo se compensa fazer isso daqui so que usando funcao recursiva(diminuiria o codigo principal)  !!!!!!*/
void valida_nivel(int *nivel);
void gerador_senha(int *senha,int nivel);
void limpar_ponteiros(int *tentativa,char *preto_branco);

#endif
