# fake-detector

Os diretórios "negative_polarity" e "positive_polarity" contém, cada um, 800 avaliações de um conjunto de hotéis em Chicago. Em cada um desses diretórios estão contidas 400 avaliações falsas e 400 verdadeiras, todas escritas por pessoas. Esses conjuntos de 400 avaliações estão distribuídos em um conjunto de 5 diretórios, com 80 avaliações cada, para facilitar na hora de fazer o k-fold cross-validation, com k = 5.

O projeto ainda está incompleto.

O que já foi feito:
-segmentação de frases (pre_processing.c, função escrita em c) <br />
-transformação de todos os caracteres para lowercase (pre_processing.c, função escrita em c) <br />
-tokenização (pre_processing.c, função escrita em c) <br />
-retirada de stopwords (pre_processing.c, função escrita em c) <br />
-criação de n-gramas (pre_processing.c, função, para qualquer valor de n, em c) <br />
-stemming (stem.c, código usado: https://tartarus.org/martin/PorterStemmer/c.txt) <br />
-definição do vocabulário em n-gramas (feature_extraction.py, função escrita em python usando a biblioteca sklearn) <br />
-script para executar os códigos, recebendo como entrada todas as avaliações <br />

O que falta fazer:
-contagem da quantidade de cada termo nos documentos <br />
-análise dos tipos de termo que mais aparecem nas avaliações falsas e verdadeiras (por isso a presença dos arquivos "adjectives.txt", "adverbs.txt", "function_words.txt", "verb_and_noun,txt" e "verbs.txt") <br />
-extração dos atributos tf-idf com uso da biblioteca sklearn <br />
-fazer 5-fold cross-validation <br />
-usar classificador SVM <br />
-analisar resultados
