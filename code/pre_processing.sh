#!/bin/bash

#receber argumentos por linha de comando (ex: -n=3 (pro n-grama), -no_stemming, -keep_stopwords)
#receber argumento por linha de comando do path_dataset e path_code

path_dataset="/home/danielatk/Documents/Trabalho_RI/fake-detector/dataset/"
path_code="/home/danielatk/Documents/Trabalho_RI/fake-detector/code/"
path_texts="/home/danielatk/Documents/Trabalho_RI/fake-detector/texts/"

stopwords=$path_texts"stopwords.txt" #guarda a lista de stopwords que será usada para pré-processamento
vocabulario=$path_texts"vocabulario.txt" #guarda o vocabulário total de todas as avaliações
results=$path_texts"results.txt" #guarda resultados da análise dos tipos de palavra nas avaliações
f_words=$path_texts"function_words.txt" #guarda a lista de palavras funcionais que será usada para análise dos tipos de palavra nas avaliações
adjectives=$path_texts"adjectives.txt" #guarda a lista de adjetivos que será usada para análise dos tipos de palavra nas avaliações
adverbs=$path_texts"adverbs.txt" #guarda a lista de advérbios que será usada para análise dos tipos de palavra nas avaliações
verbs=$path_texts"verbs.txt" #guarda a lista de verbos que será usada para análise dos tipos de palavra nas avaliações
v_nouns=$path_texts"verb_and_noun.txt" #guarda a lista de palavras que são tanto verbos quanto substantivos que será usada para análise dos tipos de palavra nas avaliações

gcc -O2 -o $path_code"pre_processing" $path_code"pre_processing.c"
gcc -O2 -o $path_code"analise" $path_code"analise.c"
gcc -O3 -o $path_code"stem" $path_code"stem.c"

feature_extract=$path_code"./feature_extraction.py $vocabulario "
analise=$path_code"./analise $results $f_words $adjectives $adverbs $verbs $v_nouns "
pre_process=$path_code"./pre_processing $stopwords "
stem=$path_code"./stem "

for i in $(ls -d $path_dataset*/); do
	for j in $(ls -d $i*/); do
		for k in $(ls -d $j*/); do
			cd $k
			for l in $(ls $k); do
				pre_process="$pre_process$(readlink -f $l) "
				stem="$stem$(readlink -f $l) "
				analise="$analise$(readlink -f $l) "
				feature_extract="$feature_extract$(readlink -f $l) "
			done
		done
	done
done

$pre_process #resolver problema de saida.txt
#$stem
#$analise
#$feature_extract
