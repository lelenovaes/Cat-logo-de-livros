# Cat-logo-de-livros
Projeto desenvolvido em C para obtenção de nota da disciplina Algoritmo e Estrutura de dados.
O objetivo é a criação de um catálogo de livros onde o usuário pode interagir de acordo com as opções apresentadas no menu.

![Captura de tela 2024-11-19 001720](https://github.com/user-attachments/assets/1a6d3abe-1155-451c-bfb3-085b2c51480a)

Funcionalidades:
1- Cadastrar Novo Livro: Com título, autor, ano de lançamento e gênero
2- Listar Livros: Exibe os livros cadastrados no arquivo csv ou e os adicionados no terminal.
3- Buscar Livro: Busca por título, autor, ano ou gênero.
4- Remover Livro: Remover do catálogo livros informando o título.
5- Salvar e Carregar de Arquivo: O catálogo é salvo no arquivo livros.csv e carrega os livros a partir desse arquivo.

1- CADASTRAR NOVO LIVRO

![Captura de tela 2024-11-19 002940](https://github.com/user-attachments/assets/b99af261-96c9-4962-bc84-d6fa0c14119f)

Para o cadastro de um novo livro ao catálogo através do termial, o usuário escolhe a opção de cadastro, informa o título, nome do autor, ano de publicação e gênero literário.
(Após isso, o livro foi cadastrado mas para ser salvo no arquivo csv é necessário que o usuário execute a opção 5(salvar e sair) no menu.).

2- LISTAR LIVROS

![Captura de tela 2024-11-19 003619](https://github.com/user-attachments/assets/1d17e082-2609-47c6-9db1-274e8dec1e3a)

Após cadastrar o novo livro no terminal e escolher a opção 2 no menu ele apenas exibe na tela as informações que foram fornecidas no momento do cadastro.
Ele também mostrou na lista os livros que foram adicionados diretamennte no arquivo CSV utilizando o Exel para ser executado:

![Captura de tela 2024-11-19 004156](https://github.com/user-attachments/assets/b5deb893-37bd-48f6-a737-5f85541de3e9)

3- BUSCAR LIVRO POR TÍTULO, AUTOR, ANO DE LANÇAMENTO OU GÊNERO

![Captura de tela 2024-11-19 004453](https://github.com/user-attachments/assets/5c47d5f7-ee74-46e8-97d1-dbf9335ac028)

A busca é feita e o programa apenas exibe o que foi encontrado com a informação que foi fornecida.

4- REMOVER LIVRO

![Captura de tela 2024-11-19 004755](https://github.com/user-attachments/assets/1c33f6f1-8e0a-47da-b296-f143f35c1cc2)

Ao escolher remover um título do catálogo o usuário o informa e ele só será realmente removido do arquivo CSV se após remover no terminal o usuário escolher no menu a opção de salvar e sair.

5- SALVAR E SAIR

![Captura de tela 2024-11-19 005106](https://github.com/user-attachments/assets/a31a56d4-bf05-4d0a-93c9-ef1d00f0224b)

Ao escolher a última opção do menu toda a interação feita antes será salva no arquivo CSV, se foi adicionado um livro no terminal ele aparecerá no arquivo, se removido algum título ao salvar e sair ele terá sido removido do arquivo... 

Estruturas de Dados Utilizadas
•	Estrutura Livro: Representa cada livro com os atributos:
o	titulo: O título do livro.
o	autor: O autor do livro.
o	ano: O ano de lançamento.
o	genero: O gênero do livro.
o	prox: Um ponteiro para o próximo livro na lista.

•	Estrutura tfila: Representa a fila de livros com:
o	inicio: Ponteiro para o início da fila.
o	fim: Ponteiro para o fim da fila.

