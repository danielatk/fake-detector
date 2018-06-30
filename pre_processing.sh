#!/bin/bash

#receber argumentos por linha de comando (ex: -n=3 (pro n-grama), -no_stemming, -keep_stopwords)

path_dataset="/home/danielatk/Documents/Trabalho_RI/op_spam_v1.4/" #modifique isso para o caminho onde está o diretório /fake-detector/ (ex: "/home/user/Documents/fake-detector/"

path_code="/home/danielatk/Documents/Trabalho_RI/op_spam_v1.4/" #modifique isso para o caminho onde está o diretório que contém os arquivos a serem executadas (por default é o mesmo que path_dataset)

stopwords=$path_code"stopwords.txt" #guarda a lista de stopwords que será usada para pré-processamento
vocabulario=$path_code"vocabulario.txt" #guarda o vocabulário total de todas as avaliações
results=$path_code"results.txt" #guarda resultados da análise dos tipos de palavra nas avaliações
f_words=$path_code"function_words.txt" #guarda a lista de palavras funcionais que será usada para análise dos tipos de palavra nas avaliações
adjectives=$path_code"adjectives.txt" #guarda a lista de adjetivos que será usada para análise dos tipos de palavra nas avaliações
adverbs=$path_code"adverbs.txt" #guarda a lista de advérbios que será usada para análise dos tipos de palavra nas avaliações
verbs=$path_code"verbs.txt" #guarda a lista de verbos que será usada para análise dos tipos de palavra nas avaliações
v_nouns=$path_code"verb_and_noun.txt" #guarda a lista de palavras que são tanto verbos quanto substantivos que será usada para análise dos tipos de palavra nas avaliações

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

$pre_process #não funciona aqui pois quando renomea saida.txt não está copiando path inteiro do diretorio
#$stem
$analise
#$feature_extract
