#!/bin/bash

path_dataset="" #modifique isso para o caminho onde está o diretório /op_spam_v1.4/ (ex: "/home/user/Documents/op_spam_v1.4/"

path_code="" #modifique isso para o caminho onde está o diretório que contém os arquivos pre_processing.c, stem.c, feature_extraction.py e stopwords.txt. O documento que guarda o vocabulário também será gerado nesse diretório

stopwords=$path_code"stopwords.txt"
vocabulario=$path_code"vocabulario.txt"

gcc -O2 -o $path_code"pre_processing" $path_code"pre_processing.c"
gcc -O3 -o $path_code"stem" $path_code"stem.c"

feature_extract=$path_code"./feature_extraction.py $vocabulario "

for i in $(ls -d $path_dataset*/); do
	for j in $(ls -d $i*/); do
		for k in $(ls -d $j*/); do
			pre_process=$path_code"./pre_processing $stopwords "
			stem=$path_code"./stem "
			cd $k
			for l in $(ls $k); do
				pre_process="$pre_process$(readlink -f $l) "
				stem="$stem$(readlink -f $l) "
				feature_extract="$feature_extract$(readlink -f $l) "
			done
			$pre_process
			$stem
		done
	done
done

$feature_extract
