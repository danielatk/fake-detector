#!/bin/bash

#-----------declaração das variáveis-----------

cd ../dataset
path_dataset="$(pwd)/"
cd ../code
path_code="$(pwd)/"
cd ../texts
path_texts="$(pwd)/"

del_stopwords=1	#define se stopwords serão deletadas ou não
do_n_gram=1
n=2	#define o n dos n-gramas
do_stemming=1	#define se será feito stemming ou não
do_analysis=1	#define se será feita análise dos tipos de palavras nas avaliações
do_feat_extract=1	#define se será feita extração dos atributos das avaliações
do_pre_proc=1	#define se será feito pré-processamento das avaliações

#-----------leitura dos argumentos alimentados por linha de comando-----------

#ver casos de botar ou não no_n_gram e n=* (vai dar problema do jeito que tá agora)

for arg in "$@"; do
	if [ "$arg" = "no_stemming" ]; then
		do_stemming=0
	elif [ "$arg" = "keep_stopwords" ]; then
		del_stopwords=0
	elif [ "$arg" = "no_n_gram" ]; then
		do_n_gram=0
	elif [[ "$arg" == n=* ]]; then
		tam_arg=${#arg}
		n=${arg:$tam_arg - 1:$tam_arg}
	elif [ "$arg" = "no_analysis" ]; then
		do_analysis=0
	elif [ "$arg" = "no_feat_extract" ]; then
		do_feat_extract=0
	elif [ "$arg" = "no_pre_proc" ]; then
		do_pre_proc=0
	else
		exit
	fi
done

#-----------definindo path de arquivos auxiliares-----------

if (($del_stopwords == 1)); then
	stopwords=$path_texts"stopwords.txt"	#guarda a lista de stopwords que será usada para pré-processamento
fi
if (($do_feat_extract == 1)); then
	vocabulario=$path_texts"vocabulario.txt"	#guarda o vocabulário total de todas as avaliações
fi
if (($do_analysis == 1)); then
	results=$path_texts"results.txt"	#guarda resultados da análise dos tipos de palavra nas avaliações
	f_words=$path_texts"function_words.txt"	#guarda a lista de palavras funcionais que será usada para análise dos tipos de palavra nas avaliações
	adjectives=$path_texts"adjectives.txt"	#guarda a lista de adjetivos que será usada para análise dos tipos de palavra nas avaliações
	adverbs=$path_texts"adverbs.txt"	#guarda a lista de advérbios que será usada para análise dos tipos de palavra nas avaliações
	verbs=$path_texts"verbs.txt"	#guarda a lista de verbos que será usada para análise dos tipos de palavra nas avaliações
	v_nouns=$path_texts"verb_and_noun.txt"	#guarda a lista de palavras que são tanto verbos quanto substantivos que será usada para análise dos tipos de palavra nas avaliações
fi

#-----------compilação-----------

if (($do_pre_proc == 1)); then
	gcc -O2 -o $path_code"pre_processing" $path_code"pre_processing.c"
fi
if (($do_analysis == 1)); then
	gcc -O2 -o $path_code"analise" $path_code"analise.c"
fi
if (($do_stemming == 1)); then
	gcc -O3 -o $path_code"stem" $path_code"stem.c"
fi

#-----------definindo path para execução (argumentos auxiliares)-----------

if (($do_feat_extract == 1)); then
	feature_extract=$path_code"./feature_extraction.py $vocabulario "
fi
if (($do_analysis == 1)); then
	analise=$path_code"./analise $results $f_words $adjectives $adverbs $verbs $v_nouns "
fi
if (($do_pre_proc == 1)); then
	pre_process=$path_code"./pre_processing $del_stopwords $do_n_gram "
	if (($do_n_gram == 1)); then
		pre_process="$pre_process$n "
	fi
	if (($del_stopwords == 1)); then
		pre_process="$pre_process$stopwords "
	fi
fi
if (($do_stemming == 1)); then
	stem=$path_code"./stem "
fi

#-----------definindo path para execução (path das avaliações)-----------

for i in $(ls -d $path_dataset*/); do
	for j in $(ls -d $i*/); do
		for k in $(ls -d $j*/); do
			cd $k
			for l in $(ls $k); do
				if (($do_pre_proc == 1)); then
					pre_process="$pre_process$(readlink -f $l) "
				fi
				if (($do_stemming == 1)); then
					stem="$stem$(readlink -f $l) "
				fi
				if (($do_analysis == 1)); then
					analise="$analise$(readlink -f $l) "
				fi
				if (($do_feat_extract == 1)); then
					feature_extract="$feature_extract$(readlink -f $l) "
				fi
			done
		done
	done
done

#-----------execução-----------

if (($do_pre_proc == 1)); then
	$pre_process	#resolver problema de saida.txt
fi
if (($do_stemming == 1)); then
	$stem	#resolver problema de saida.txt
fi
if (($do_analysis == 1)); then
	$analise
fi
if (($do_feat_extract == 1)); then
	$feature_extract
fi
