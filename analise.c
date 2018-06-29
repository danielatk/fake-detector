#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct t_listas{ //struct para guardar as listas de palavras funcionais, advérbios, etc
  char** f_words_list;
  char** adjectives_list;
  char** adverbs_list;
  char** verbs_list;
  char** v_nouns_list;

  int f_words_maior;
  int adjectives_maior;
  int adverbs_maior;
  int verbs_maior;
  int v_nouns_maior;

  int f_words_qtd;
  int adjectives_qtd;
  int adverbs_qtd;
  int verbs_qtd;
  int v_nouns_qtd;
};

struct t_listas palavras;

FILE *review, *f_words, *adjectives, *adverbs, *verbs, *v_nouns, *results;
char *nome_review, *nome_f_words, *nome_adjectives, *nome_adverbs, *nome_verbs, *nome_v_nouns, *nome_results;

int qtd_palavras_doc = 0;
int qtd_palavras_d_total = 0; //quantity of words in all the deceptive reviews
int qtd_palavras_t_total = 0; //quantity of words in all the truthful reviews
int media_palavras_d; //mean of the words per deceptive review
int media_palavras_t; //meand of the words per truthful review

int cont_t_f_words = 0; //function words counter for truthful reviews
int cont_t_adjectives = 0;
int cont_t_adverbs = 0;
int cont_t_verbs = 0;
int cont_t_v_nouns = 0;

int cont_d_f_words = 0; //function words counter for deceptive reviews
int cont_d_adjectives = 0;
int cont_d_adverbs = 0;
int cont_d_verbs = 0;
int cont_d_v_nouns = 0;

void pegaListasPalavras(){
  f_words = fopen(nome_f_words, "r");
  if (f_words == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_f_words);
  }
  adjectives = fopen(nome_adjectives, "r");
  if (adjectives == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_adjectives);
  }
  adverbs = fopen(nome_adverbs, "r");
  if (adverbs == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_adverbs);
  }
  verbs = fopen(nome_verbs, "r");
  if (verbs == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_verbs);
  }
  v_nouns = fopen(nome_v_nouns, "r");
  if (v_nouns == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_v_nouns);
  }

  palavras.f_words_maior = 0;
  palavras.f_words_qtd = 0;
  palavras.adjectives_maior = 0;
  palavras.adjectives_qtd = 0;
  palavras.adverbs_maior = 0;
  palavras.adverbs_qtd = 0;
  palavras.verbs_maior = 0;
  palavras.verbs_qtd = 0;
  palavras.v_nouns_maior = 0;
  palavras.v_nouns_qtd = 0;

  char aux[30];

  while(fgets(aux, 30, f_words)!=NULL){
    if (strlen(aux) > palavras.f_words_maior){
      palavras.f_words_maior = strlen(aux);
    }
    palavras.f_words_qtd ++;
  }
  palavras.f_words_list = malloc(palavras.f_words_qtd * sizeof(char*));
  for(int i = 0; i < palavras.f_words_qtd; i++){
    palavras.f_words_list[i] = malloc(palavras.f_words_maior + 1);
  }
  rewind(f_words);
  for(int i = 0; i < palavras.f_words_qtd; i++){
    fscanf(f_words, "%s", palavras.f_words_list[i]);
  }
  fclose(f_words);

  while(fgets(aux, 30, adjectives)!=NULL){
    if (strlen(aux) > palavras.adjectives_maior){
      palavras.adjectives_maior = strlen(aux);
    }
    palavras.adjectives_qtd ++;
  }
  palavras.adjectives_list = malloc(palavras.adjectives_qtd * sizeof(char*));
  for(int i = 0; i < palavras.adjectives_qtd; i++){
    palavras.adjectives_list[i] = malloc(palavras.adjectives_maior + 1);
  }
  rewind(adjectives);
  for(int i = 0; i < palavras.adjectives_qtd; i++){
    fscanf(adjectives, "%s", palavras.adjectives_list[i]);
  }
  fclose(adjectives);

  while(fgets(aux, 30, adverbs)!=NULL){
    if (strlen(aux) > palavras.adverbs_maior){
      palavras.adverbs_maior = strlen(aux);
    }
    palavras.adverbs_qtd ++;
  }
  palavras.adverbs_list = malloc(palavras.adverbs_qtd * sizeof(char*));
  for(int i = 0; i < palavras.adverbs_qtd; i++){
    palavras.adverbs_list[i] = malloc(palavras.adverbs_maior + 1);
  }
  rewind(adverbs);
  for(int i = 0; i < palavras.adverbs_qtd; i++){
    fscanf(adverbs, "%s", palavras.adverbs_list[i]);
  }
  fclose(adverbs);

  while(fgets(aux, 30, verbs)!=NULL){
    if (strlen(aux) > palavras.verbs_maior){
      palavras.verbs_maior = strlen(aux);
    }
    palavras.verbs_qtd ++;
  }
  palavras.verbs_list = malloc(palavras.verbs_qtd * sizeof(char*));
  for(int i = 0; i < palavras.verbs_qtd; i++){
    palavras.verbs_list[i] = malloc(palavras.verbs_maior + 1);
  }
  rewind(verbs);
  for(int i = 0; i < palavras.verbs_qtd; i++){
    fscanf(verbs, "%s", palavras.verbs_list[i]);
  }
  fclose(verbs);

  while(fgets(aux, 30, v_nouns)!=NULL){
    if (strlen(aux) > palavras.v_nouns_maior){
      palavras.v_nouns_maior = strlen(aux);
    }
    palavras.v_nouns_qtd ++;
  }
  palavras.v_nouns_list = malloc(palavras.v_nouns_qtd * sizeof(char*));
  for(int i = 0; i < palavras.v_nouns_qtd; i++){
    palavras.v_nouns_list[i] = malloc(palavras.v_nouns_maior + 1);
  }
  rewind(v_nouns);
  for(int i = 0; i < palavras.v_nouns_qtd; i++){
    fscanf(v_nouns, "%s", palavras.v_nouns_list[i]);
  }
  fclose(v_nouns);
}

void contaQtdPalavras(int d){
  review = fopen(nome_review, "r");
  if (review == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_review);
  }
  char aux[30];
  while(fgets(aux, 30, review)!=NULL){
    for(int i = 0; i < strlen(aux); i++){
      if(aux[i] == '\n'){
        qtd_palavras_doc++;
      }
    }
  }
  if(d){
    qtd_palavras_d_total += qtd_palavras_doc;
  }else{
    qtd_palavras_t_total += qtd_palavras_doc;
  }
  qtd_palavras_doc = 0;
  fclose(review);
}

void escreveResults(){
  results = fopen(nome_results, "w");
  if (results == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_results);
  }
  fprintf(results, "Quantidade de palavras funcionais nas avaliações falsas: %d\n", cont_d_f_words);
  fprintf(results, "Quantidade de advérbios nas avaliações falsas: %d\n", cont_d_adverbs);
  fprintf(results, "Quantidade de adjetivos nas avaliações falsas: %d\n", cont_d_adjectives);
  fprintf(results, "Quantidade de verbos nas avaliações falsas: %d\n", cont_d_verbs);
  fprintf(results, "Quantidade de palavras que podem ser verbos ou substantivos nas avaliações falsas: %d\n", cont_d_v_nouns);

  fprintf(results, "Quantidade de palavras funcionais nas avaliações verdadeiras: %d\n", cont_t_f_words);
  fprintf(results, "Quantidade de advérbios nas avaliações verdadeiras: %d\n", cont_t_adverbs);
  fprintf(results, "Quantidade de adjetivos nas avaliações verdadeiras: %d\n", cont_t_adjectives);
  fprintf(results, "Quantidade de verbos nas avaliações verdadeiras: %d\n", cont_t_verbs);
  fprintf(results, "Quantidade de verbos que são substantivos nas avaliações verdadeiras: %d\n", cont_t_v_nouns);

  fclose(results);
}

void contaTiposPalavras(int d){
  review = fopen(nome_review, "r");
  if (review == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_review);
  }
  f_words = fopen(nome_f_words, "r");
  if (f_words == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_f_words);
  }
  adjectives = fopen(nome_adjectives, "r");
  if (adjectives == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_adjectives);
  }
  adverbs = fopen(nome_adverbs, "r");
  if (adverbs == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_adverbs);
  }
  verbs = fopen(nome_verbs, "r");
  if (verbs == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_verbs);
  }
  v_nouns = fopen(nome_v_nouns, "r");
  if (v_nouns == NULL){
    printf("Erro na abertura do arquivo %s\n", nome_v_nouns);
  }
  char aux[30];
  int i, j;
  while(1){
    fscanf(review, "%s", aux);
    if(feof(review)){
      break;
    }
    for(j = 0; j < palavras.f_words_qtd; j++){
      if(strcmp(aux, palavras.f_words_list[j]) == 0){
        if(d){
          cont_d_f_words++;
        }else{
          cont_t_f_words++;
        }
        break;
      }
    }
    for(j = 0; j < palavras.adjectives_qtd; j++){
      if(strcmp(aux, palavras.adjectives_list[j]) == 0){
        if(d){
          cont_d_adjectives++;
        }else{
          cont_t_adjectives++;
        }
        break;
      }
    }
    for(j = 0; j < palavras.adverbs_qtd; j++){
      if(strcmp(aux, palavras.adverbs_list[j]) == 0){
        if(d){
          cont_d_adverbs++;
        }else{
          cont_t_adverbs++;
        }
        break;
      }
    }
    for(j = 0; j < palavras.verbs_qtd; j++){
      if(strcmp(aux, palavras.verbs_list[j]) == 0){
        if(d){
          cont_d_verbs++;
        }else{
          cont_t_verbs++;
        }
        break;
      }
    }
    for(j = 0; j < palavras.v_nouns_qtd; j++){
      if(strcmp(aux, palavras.v_nouns_list[j]) == 0){
        if(d){
          cont_d_v_nouns++;
        }else{
          cont_t_v_nouns++;
        }
        break;
      }
    }
  }
  fclose(review);
  fclose(f_words);
  fclose(adjectives);
  fclose(adverbs);
  fclose(verbs);
  fclose(v_nouns);
}

int main(int argc, char *argv[]){

  nome_results = malloc(strlen(argv[1]));
  nome_results = argv[1];
  nome_f_words = malloc(strlen(argv[2]));
  nome_f_words = argv[2];
  nome_adjectives = malloc(strlen(argv[3]));
  nome_adjectives = argv[3];
  nome_adverbs = malloc(strlen(argv[4]));
  nome_adverbs = argv[4];
  nome_verbs = malloc(strlen(argv[5]));
  nome_verbs = argv[5];
  nome_v_nouns = malloc(strlen(argv[6]));
  nome_v_nouns = argv[6];

  pegaListasPalavras();

  int i;
  int j;

  int d; //if d == 1 review is deceptive, if d == 0 review is truthful

  for(i = 7; i < argc; i++){
    nome_review = malloc(strlen(argv[i]));
    nome_review = argv[i];
    int cont_underline = 0; //variável auxiliar para descobrir se avaliação é falsa ou verdadeira
    int letra_decisiva = 0; //outra variável auxiliar para descobrir se avaliação é falsa ou verdadeira
    for(j=strlen(argv[i]); j>=0; j--){
      if(letra_decisiva){
        if(nome_review[j] == 'd'){
          d = 1;
        }else if(nome_review[j] == 't'){
          d = 0;
        }else{
          exit(0);
        }
        break;
      }
      if(nome_review[j] == '_'){
        cont_underline ++;
      }
      if(cont_underline == 2){
        letra_decisiva = 1;
      }
    }
    contaQtdPalavras(d);
    contaTiposPalavras(d);
  }
  escreveResults();
  return 0;
}
