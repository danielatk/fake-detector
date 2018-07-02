# fake-detector

Para executar o script vá até o diretório <path>/fake-detector/code e execute ./pre_processing.sh. Os seguintes argumentos podem ser passados por linha de comando:
* no_stemming (não executar o stemming)
* no_n_gram (não executar segmentação em n-gramas)
* n=<int> (passa int como parâmetro pra função que segmenta em n-gramas)
* keep_stopwords (não retira stopwords)
* no_analysis (não executa análise dos tipos de palavras nas avaliações)
* no_feature_extract (não extrai os atributos das avaliações)
* no_pre_proc (não executa o pré-processamento das avaliações)

Se quiser executar somente pre_processing.c o primeiro argumento é 1 se quiser deletar stopwords e 0 se não quiser, o segundo argumento é 1 se quiser realizar segmentação em n-gramas e 0 se não quiser, o terceiro argumento é o valor de n para segmentação em n-gramas (se o segunto argumento for 0 então omita esse argumento), o quarto argumento é o caminho completo do arquivo onde está stopwords.txt (se o primeiro argumento for 0 então omita esse argumento). Os argumentos seguintes são os caminhos completos das avaliações a serem pré-processadas.

Se quiser executar somente stemming.c os argumentos são os caminhos completos das avaliações a serem stemizadas.

Se quiser executar somente analise.c o primeiro argumento é o caminho completo do arquivo .txt onde deseja guardar os resultados da análise, o segundo argumento é o caminho completo do arquivo function_words.txt, o terceiro argumento é o caminho completo do arquivo adjectives.txt, o quarto argumento é o caminho completo do arquivo adverbs.txt, o quinto argumento é o caminho completo do arquivo verbs.txt, o sexto argumento é o caminho completo do arquivo verb_and_noun.txt. Os argumentos seguintes são os caminhos completos das avaliações a serem analisadas.

Se quiser executar somente feature_extraction.py o primeiro argumento é o caminho completo do arquivo .txt onde deseja guardar o vocabulário das avaliações lidas. Os argumentos seguintes são os caminhos completos das avaliações a terem seus atributos extraídos.

Os diretórios "negative_polarity" e "positive_polarity" contém, cada um, 800 avaliações de um conjunto de hotéis em Chicago. Em cada um desses diretórios estão contidas 400 avaliações falsas e 400 verdadeiras, todas escritas por pessoas. Esses conjuntos de 400 avaliações estão distribuídos em um conjunto de 5 diretórios, com 80 avaliações cada, para facilitar na hora de fazer o k-fold cross-validation, com k = 5.

O projeto ainda está incompleto.

O que já foi feito:
* segmentação de frases (pre_processing.c, função escrita em c)
* transformação de todos os caracteres para lowercase (pre_processing.c, função escrita em c)
* tokenização (pre_processing.c, função escrita em c)
* retirada de stopwords (pre_processing.c, função escrita em c)
* criação de n-gramas (pre_processing.c, função, para qualquer valor de n, em c)
* stemming (stem.c, código usado: https://tartarus.org/martin/PorterStemmer/c.txt)
* definição do vocabulário em n-gramas (feature_extraction.py, função escrita em python usando a biblioteca sklearn)
* script para executar os códigos, recebendo como entrada todas as avaliações

O que falta fazer:
* contagem da quantidade de cada termo nos documentos
* análise dos tipos de termo que mais aparecem nas avaliações falsas e verdadeiras (por isso a presença dos arquivos "adjectives.txt", "adverbs.txt", "function_words.txt", "verb_and_noun,txt" e "verbs.txt")
* extração dos atributos tf-idf com uso da biblioteca sklearn
* fazer 5-fold cross-validation
* usar classificador LSVM
* analisar resultados
