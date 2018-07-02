#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct t_stopwords{ //struct para guardar as stopwords, quantidade de stopwords e stopword com maior tamanho 
  int qtd;
  int maior;
  char** list;
};

struct t_stopwords stopwords;
FILE* review;
FILE* f_stopwords;
char* nome_review;
char* nome_arq_stopwords;

int contaQtdPalavras(){
  int qtd = 0;
  review = fopen(nome_review, "r");
  if (review == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_review);
  }
  char aux[300];
  while(fgets(aux, 300, review)!=NULL){
    for(int i = 0; i < strlen(aux); i++){
      if(aux[i] == ' ' || aux[i] == '\n'){
        qtd++;
      }
    }
  } 
  return qtd;
  fclose(review);
}


void segmentaFrases(){ //segmenta frases em linhas diferentes
  review = fopen(nome_review, "r");
  FILE* arq_saida;
  char* nome_arq_saida;
  int j;
  nome_arq_saida = (char*)malloc(strlen(nome_review)+1);
  int achou_ponto = 0;
  int cont_t = 0;
  for(j=0; j<=strlen(nome_review); j++){
    if(achou_ponto){
      if(nome_review[j-1] == 't') cont_t++;
      if(cont_t == 2){
        nome_arq_saida[j] = nome_review[j-1];
        break;
      }
      nome_arq_saida[j] = nome_review[j-1];
    }else{
      if(nome_review[j] == '.'){
        achou_ponto = 1;
        nome_arq_saida[j] = 's';
        continue;
      }
      nome_arq_saida[j] = nome_review[j];
    }
  }
  nome_arq_saida[j+1] = '\0';
  arq_saida = fopen(nome_arq_saida, "w");
  if (review == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_review);
  }
  if (arq_saida == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_arq_saida);
  }
  char pontuacao[4];
  pontuacao[0] = '.';
  pontuacao[1] = '!';
  pontuacao[2] = '?';
  pontuacao[3] = ';';
  char aux[300];
  int pont = 0; //variável que indica se caracter é pontuação ou não
  int espaco = 0; //variável que indica se caracter é espaço ou não
  int abre_par = 0; //variável que indica se caracter é '(' ou não
  int fecha_par = 0; //variável que indica se caracter é ')' ou não
  int aspas = 0; //variável que indica se caracter é " ou não
  int primeiro_ponto;
  while (1){
    fgets(aux, 300, review);
    if(feof(review)){
      break;
    }
    for(int i = 0; i < strlen(aux); i++){
      if(!isupper(aux[i]) || !espaco){
        fprintf(arq_saida, "%c", aux[i]);
      }
      for(int j = 0; j < 4; j++){
        if(aux[i] == pontuacao[j]){
          primeiro_ponto = 1;
          pont = 1;
          break;
        }
      }
      if(primeiro_ponto){
        primeiro_ponto = 0;
        if(i == (strlen(aux) - 1)){ //testa se está no último caracter lido do arquivo de entrada nessa iteração
          break;
        }
        else{
          continue;
        }
      }
      if(pont && !abre_par){ //só queremos que seja tratado o caso da pontuacao quando não tiver dentro de um parentesis
        if(aux[i] == ' '){
          espaco = 1;
        }
        if(aux[i] == '\"'){
          aspas = 1;
        }
        pont = 0;
        if(i == (strlen(aux) - 1)){
          break;
        }
        else{
          continue;
        }
      }
      if(espaco){
        if(isupper(aux[i])){
          fputs("\n", arq_saida);
          fprintf(arq_saida, "%c", aux[i]);
        }
        if(aux[i] == '('){
          abre_par = 1;
        }
        espaco = 0;
        if(i == (strlen(aux) - 1)){
          break;
        }
        else{
          continue;
        }
      }
      if(abre_par){ //e se aparecer um ponto entre abre_par e fecha_par?
        if(aux[i] == ')'){
          fecha_par = 1;
        }
        abre_par = 0;
        if(i == (strlen(aux) - 1)){
          break;
        }
        else{
          continue;
        }
      }
      if(fecha_par){
        if(aux[i] == ' '){
          espaco = 1;
        }
        fecha_par = 0;
        if(i == (strlen(aux) - 1)){
          break;
        }
        else{
          continue;
        }
      }
    }
  }
  remove(nome_review);
  fclose(review);
  rename(nome_arq_saida, nome_review);
  free(nome_arq_saida);
  fclose(arq_saida);
}

void retiraEspacoFim(){ //deleta espaço no fim de cada frase após segmentação
  review = fopen(nome_review, "r");
  FILE* arq_saida;
  char* nome_arq_saida;
  int j;
  nome_arq_saida = (char*)malloc(strlen(nome_review)+1);
  int achou_ponto = 0;
  int cont_t = 0;
  for(j=0; j<=strlen(nome_review); j++){
    if(achou_ponto){
      if(nome_review[j-1] == 't') cont_t++;
      if(cont_t == 2){
        nome_arq_saida[j] = nome_review[j-1];
        break;
      }
      nome_arq_saida[j] = nome_review[j-1];
    }else{
      if(nome_review[j] == '.'){
        achou_ponto = 1;
        nome_arq_saida[j] = 's';
        continue;
      }
      nome_arq_saida[j] = nome_review[j];
    }
  }
  nome_arq_saida[j+1] = '\0';
  arq_saida = fopen(nome_arq_saida, "w");
  if (review == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_review);
  }
  if (arq_saida == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_arq_saida);
  }
  char aux[300];
  while(fgets(aux, 300, review)!=NULL){
    for(int i = 0; i < strlen(aux); i++){
      if(i != (strlen(aux) - 2)){
        fprintf(arq_saida, "%c", aux[i]);
      }else{
        if(aux[i] != ' '){
          fprintf(arq_saida, "%c", aux[i]);
        }
      }
    }
  }
  remove(nome_review);
  fclose(review);
  rename(nome_arq_saida, nome_review);
  free(nome_arq_saida);
  fclose(arq_saida);
}

void tokeniza(){ //quando tem uma ou mais pontuações sem espaço antes ou depois, por exemplo: "hello...you", não é possível cuidar desse caso, pois se não termos como "i.e." se tornariam "i e", emails também ficariam segmentados.
  review = fopen(nome_review, "r");
  FILE* arq_saida;
  char* nome_arq_saida;
  int j;
  nome_arq_saida = (char*)malloc(strlen(nome_review)+1);
  int achou_ponto = 0;
  int cont_t = 0;
  for(j=0; j<=strlen(nome_review); j++){
    if(achou_ponto){
      if(nome_review[j-1] == 't') cont_t++;
      if(cont_t == 2){
        nome_arq_saida[j] = nome_review[j-1];
        break;
      }
      nome_arq_saida[j] = nome_review[j-1];
    }else{
      if(nome_review[j] == '.'){
        achou_ponto = 1;
        nome_arq_saida[j] = 's';
        continue;
      }
      nome_arq_saida[j] = nome_review[j];
    }
  }
  nome_arq_saida[j+1] = '\0';
  arq_saida = fopen(nome_arq_saida, "w");
  if (review == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_review);
  }
  if (arq_saida == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_arq_saida);
  }
  char aux[300];
  int pont = 0;
  while(fgets(aux, 300, review)!=NULL){
    for(int i = 0; i < strlen(aux); i++){
      /*if(i != (strlen(aux) - 1)){
        if(!ispunct(aux[i]) && ispunct(aux[i+1]) && aux[i] != ' '){
          pont = 1;
          fprintf(arq_saida, "%c", aux[i]);
          continue;
        }
        if(pont && aux[i+1] != ' ' && !ispunct(aux[i+1])){
          pont = 0;
          fprintf(arq_saida, " ", aux[i]);
          continue;
        }
        if(pont && aux[i+1] == ' '){
          pont = 0;
        }
      }*/
      if(!ispunct(aux[i]) || aux[i] == '\''){
        fprintf(arq_saida, "%c", aux[i]);
      }
      if(i != (strlen(aux) - 1) && i > 0){
        if(aux[i] == '-' && aux[i+1] != ' '){ //cuida de hífens
          fprintf(arq_saida, " ", aux[i]);
        }
      }
    }
  }
  remove(nome_review);
  fclose(review);
  rename(nome_arq_saida, nome_review);
  free(nome_arq_saida);
  fclose(arq_saida);
}

void retiraEspacoAMais(){
  review = fopen(nome_review, "r");
  FILE* arq_saida;
  char* nome_arq_saida;
  int j;
  nome_arq_saida = (char*)malloc(strlen(nome_review)+1);
  int achou_ponto = 0;
  int cont_t = 0;
  for(j=0; j<=strlen(nome_review); j++){
    if(achou_ponto){
      if(nome_review[j-1] == 't') cont_t++;
      if(cont_t == 2){
        nome_arq_saida[j] = nome_review[j-1];
        break;
      }
      nome_arq_saida[j] = nome_review[j-1];
    }else{
      if(nome_review[j] == '.'){
        achou_ponto = 1;
        nome_arq_saida[j] = 's';
        continue;
      }
      nome_arq_saida[j] = nome_review[j];
    }
  }
  nome_arq_saida[j+1] = '\0';
  arq_saida = fopen(nome_arq_saida, "w");
  if (review == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_review);
  }
  if (arq_saida == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_arq_saida);
  }
  char aux[300];
  int espaco = 0;
  while(fgets(aux, 300, review)!=NULL){
    for(int i = 0; i < strlen(aux); i++){
      if(!ispunct(aux[i]) && aux[i] != ' ' || aux[i] == '\''){
        fprintf(arq_saida, "%c", aux[i]);
        espaco = 0;
      }
      if(aux[i] == ' ' && !espaco){
        espaco++;
        fprintf(arq_saida, "%c", aux[i]);
      }
    }
  }
  remove(nome_review);
  fclose(review);
  rename(nome_arq_saida, nome_review);
  free(nome_arq_saida);
  fclose(arq_saida);
}

void lowercase(){ 
  review = fopen(nome_review, "r");
  FILE* arq_saida;
  char* nome_arq_saida;
  int j;
  nome_arq_saida = (char*)malloc(strlen(nome_review)+1);
  int achou_ponto = 0;
  int cont_t = 0;
  for(j=0; j<=strlen(nome_review); j++){
    if(achou_ponto){
      if(nome_review[j-1] == 't') cont_t++;
      if(cont_t == 2){
        nome_arq_saida[j] = nome_review[j-1];
        break;
      }
      nome_arq_saida[j] = nome_review[j-1];
    }else{
      if(nome_review[j] == '.'){
        achou_ponto = 1;
        nome_arq_saida[j] = 's';
        continue;
      }
      nome_arq_saida[j] = nome_review[j];
    }
  }
  nome_arq_saida[j+1] = '\0';
  arq_saida = fopen(nome_arq_saida, "w");
  if (review == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_review);
  }
  if (arq_saida == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_arq_saida);
  }
  char aux[300];
  while(fgets(aux, 300, review)!=NULL){
    for(int i = 0; i < strlen(aux); i++){
      if(isupper(aux[i])!=0){
        aux[i] += 32; //lowercase é 32 a mais do que uppercase
      }
      fprintf(arq_saida, "%c", aux[i]);
    }
  }
  remove(nome_review);
  fclose(review);
  rename(nome_arq_saida, nome_review);
  free(nome_arq_saida);
  fclose(arq_saida);
}


void pegaStopwords(){ //função para pegar as stopwords, quantidade de stopwords e stopword com maior tamanho
  f_stopwords = fopen(nome_arq_stopwords, "r");
  if (f_stopwords == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_arq_stopwords);
  }
  stopwords.qtd = 0; //conta número de stopwords
  stopwords.maior = 0; //descobre stopword com mais caracteres
  char aux[20]; //string auxiliar para receber as stopwords
  while(fgets(aux, 20, f_stopwords)!=NULL){ //descobre tamanho da maior stopword e quantas stopwords existem
    if (strlen(aux) > stopwords.maior){
      stopwords.maior = strlen(aux);
    }
    stopwords.qtd ++;
  }
  stopwords.list = malloc(stopwords.qtd * sizeof(char*)); //aloca espaço para cada um dos stopwords
  for(int i = 0; i < stopwords.qtd; i++){
    stopwords.list[i] = malloc(stopwords.maior + 1);
  }
  rewind(f_stopwords);
  for(int i = 0; i < stopwords.qtd; i++){
    fscanf(f_stopwords, "%s", stopwords.list[i]);
  }
  fclose(f_stopwords);
}

void retiraStopwords(){
  review = fopen(nome_review, "r");
  FILE* arq_saida;
  char* nome_arq_saida;
  int j;
  nome_arq_saida = (char*)malloc(strlen(nome_review)+1);
  int achou_ponto = 0;
  int cont_t = 0;
  for(j=0; j<=strlen(nome_review); j++){
    if(achou_ponto){
      if(nome_review[j-1] == 't') cont_t++;
      if(cont_t == 2){
        nome_arq_saida[j] = nome_review[j-1];
        break;
      }
      nome_arq_saida[j] = nome_review[j-1];
    }else{
      if(nome_review[j] == '.'){
        achou_ponto = 1;
        nome_arq_saida[j] = 's';
        continue;
      }
      nome_arq_saida[j] = nome_review[j];
    }
  }
  nome_arq_saida[j+1] = '\0';
  arq_saida = fopen(nome_arq_saida, "w");
  if (review == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_review);
  }
  if (arq_saida == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_arq_saida);
  }
  int igual; //instancia flag para indicar se a palavra lida do arquivo de entrada é uma stopword ou não
  char aux[300];
  char* str;
  int inicio; //variável que guarda o inicio da substring de aux que será passada para str para comparar com cada stopword
  int tam; //variável que guarda o tamanho da substring de aux que será passada para str para comparar com cada stopword
  int i;
  int alocado = 0; //flag para indicar se str já teve espaço alocado ou não
  int primeiro;
  while(fgets(aux, 300, review)!=NULL){
    igual = 0;
    inicio = 0;
    primeiro = 1;
    for(i = 0; i < strlen(aux); i++){
      if(aux[i] == ' ' || aux[i] == '\n'){
        tam = i - inicio;
        str = (char*)malloc(tam + 1);
        alocado = 1;
        for(j = 0; j < tam; j++){
          str[j] = aux[inicio + j];
        }
        inicio = i + 1;
        str[j] = '\0';
        for(j = 0; j < stopwords.qtd; j++){
          if(strcmp(str, stopwords.list[j]) == 0){
            igual = 1;
            break;
          }
        }
        if(!igual){
          if(!primeiro){
            fputs(" ", arq_saida);
          }
          fputs(str, arq_saida);
        }
        if(aux[i] == '\n'){
          fputs("\n", arq_saida);
          break;
        }
        if(!igual && alocado){
          primeiro = 0;
        }
        if(alocado){
          free(str);
          alocado = 0;
        }
        igual = 0;
      }
    }
  }
  remove(nome_review);
  fclose(review);
  rename(nome_arq_saida, nome_review);
  free(nome_arq_saida);
  fclose(arq_saida);
}

void criaNGrama(int n){
  review = fopen(nome_review, "r");
  FILE* arq_saida;
  char* nome_arq_saida;
  int j;
  nome_arq_saida = (char*)malloc(strlen(nome_review)+1);
  int achou_ponto = 0;
  int cont_t = 0;
  for(j=0; j<=strlen(nome_review); j++){
    if(achou_ponto){
      if(nome_review[j-1] == 't') cont_t++;
      if(cont_t == 2){
        nome_arq_saida[j] = nome_review[j-1];
        break;
      }
      nome_arq_saida[j] = nome_review[j-1];
    }else{
      if(nome_review[j] == '.'){
        achou_ponto = 1;
        nome_arq_saida[j] = 's';
        continue;
      }
      nome_arq_saida[j] = nome_review[j];
    }
  }
  nome_arq_saida[j+1] = '\0';
  arq_saida = fopen(nome_arq_saida, "w");
  if (review == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_review);
  }
  if (arq_saida == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_arq_saida);
  }
  char aux[300];
  char* n_gram; //irá guardar N palavras
  int cont; //conta quantas palavras foram lidas
  int inicio[n+1];
  int tam;
  int i;
  int alocado = 0; //flag para indicar se n_gram já teve espaço alocado ou não
  while(fgets(aux, 300, review)!=NULL){
    cont = 0;
    for(i=0; i<n+1; i++){
      inicio[i] = 0;
    }
    for(i = 0; i < strlen(aux); i++){
      if(aux[i] == ' '){
        cont++;
        inicio[cont] = i + 1;
        if(cont == n){
          cont --;
          tam = i - inicio[0];
          n_gram = (char*)malloc(tam + 1);
          for(j = 0; j < tam; j++){
            n_gram[j] = aux[inicio[0] + j];
          }
          n_gram[j] = '\0';
          alocado = 1;
          fputs(n_gram, arq_saida);
          fputs("\n", arq_saida);
        }
      }
      if(aux[i] ==  '\n'){
        cont++;
        inicio[cont] = i + 1;
        if(cont == n){
          tam = i - inicio[0];
          n_gram = (char*)malloc(tam + 1);
          for(j = 0; j < tam; j++){
            n_gram[j] = aux[inicio[0] + j];
          }
          n_gram[j] = '\0';
          alocado = 1;
          fputs(n_gram, arq_saida);
          fputs("\n", arq_saida);
        }
      }
      if(alocado){
        alocado = 0;
        for(j=0; j<n; j++){
          inicio[j] = inicio[j+1];
        }
        inicio[j] = 0;
        free(n_gram);
      }
    }
  }
  remove(nome_review);
  fclose(review);
  rename(nome_arq_saida, nome_review);
  free(nome_arq_saida);
  fclose(arq_saida);
}

int main(int argc, char *argv[]){
  int n;
  int del_stopwords = atoi(argv[1]); //se 1 então deleta stopwords
  int do_n_gram = atoi(argv[2]); //se 1 então segmenta em n-gramas
  int inicio = 3;
  if(do_n_gram){
    n = atoi(argv[inicio]); //recebe n para passar como parâmetro para função que segmenta em n-gramas
    inicio++;
  }
  if(del_stopwords){
    nome_arq_stopwords = malloc(strlen(argv[inicio]));
    strcpy(nome_arq_stopwords, argv[inicio]);
    pegaStopwords();
    inicio++;
  } 
  int i;
  int qtd_palavras;
  for(i = inicio; i < argc; i++){
    nome_review = malloc(strlen(argv[i]));
    strcpy(nome_review, argv[i]);
    segmentaFrases();
    retiraEspacoFim();
    lowercase();
    tokeniza();
    retiraEspacoAMais();
    qtd_palavras = contaQtdPalavras();
    if(del_stopwords) retiraStopwords();
    if(do_n_gram) criaNGrama(n);
    free(nome_review);
  }
  return 0;
}
