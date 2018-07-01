#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
from sklearn.feature_extraction.text import *

'''---------------funções---------------'''

def defineVocabulario():
  n_gramas = review.readlines()
  for i in range(len(n_gramas)):
    if not any(n_gramas[i] in s for s in vocab):
      vocab.write(n_gramas[i])
      vocabulario.append(n_gramas[i])

def contaNGramas():
  n_gramas = review.readlines()
  contador = vetorizador.fit_transform(n_gramas).toarray()

'''---------------execução---------------'''

vocab = open(sys.argv[1], 'a+') #documento que guardará o vocabulário (em n-gramas de palavras) de todos os documentos
#contagem = open(sys.argv[2], 'a+') #documento que guardará a quantidade de cada n_grama em cada documento
vocabulario = [] #lista que guardará o vocabulário (em n-gramas de palavras) de todos os documentos

for i in range(2, len(sys.argv)):
  review = open(sys.argv[i], 'r')
  defineVocabulario()
  review.close()

for i in range(len(vocabulario)):
  vocabulario[i] = vocabulario[i].replace("\n", "") #retira caracter newline no final de cada linha
vetorizador = CountVectorizer(vocabulary = list(set(vocabulario)))
contador = []

for i in range(2, len(sys.argv)):
  review = open(sys.argv[i], 'r')
  contaNGramas()
  review.close()

#print vetorizador.vocabulary_

vocab.close()
#contagem.close()
