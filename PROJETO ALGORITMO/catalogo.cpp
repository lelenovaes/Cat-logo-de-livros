#include <stdio.h>     
#include <stdlib.h>    // Biblioteca para fun��es de aloca��o de mem�ria
#include <locale.h>    // Biblioteca para definir configura��es regionais
#include <string.h>    // Biblioteca para manipula��o de strings
#include <ctype.h>     // Biblioteca para fun��es de manipula��o de caracteres

// Estrutura do livro
typedef struct Livro {
    char titulo[100];  // array de caracteres que armazena o t�tulo do livro (at� 99 caracteres)
    char autor[50];    // Autor do livro
    int ano;           // Ano de lan�amento
    char genero[30];   // G�nero do livro
    struct Livro* prox; // Ponteiro para o pr�ximo livro na lista
} Livro;

// Estrutura que representa a fila de livros
typedef struct {
    Livro* inicio; // Ponteiro para o in�cio da fila
    Livro* fim;    // Ponteiro para o fim da fila
} tfila; // ponteiro para a estrutura da fila

// Fun��o para inicializar a fila
void CriarFila(tfila* Fila) {
    Fila->inicio = Fila->fim = NULL; // A fila come�a vazia
    printf("Bem-vindo ao seu cat�logo!\n");
    printf("No seu cat�logo voc� pode listar livros, adicionar novos livros,"
           "\nremover livros e buscar por t�tulo, autor, ano de lan�amento ou g�nero.\n");
}

// Verifica se a fila est� vazia
int FilaVazia(tfila Fila) {
    return (Fila.inicio == NULL); // Retorna 1 se a fila est� vazia, 0 caso contr�rio
}

// Fun��o para inserir um novo livro na fila
int Inserir(tfila* Fila, char* titulo, char* autor, int ano, char* genero) {
    Livro* novo = (Livro*)malloc(sizeof(Livro)); // Aloca mem�ria para um novo livro
    if (novo == NULL) return 0; // Se falhar a aloca��o, retorna 0

    // Copia os dados do novo livro
    strcpy(novo->titulo, titulo);
    strcpy(novo->autor, autor);
    novo->ano = ano;
    strcpy(novo->genero, genero);
    novo->prox = NULL; // O novo livro ser� o �ltimo, ent�o pr�ximo � NULL

    // Se a fila est� vazia, o novo livro � o primeiro
    if (FilaVazia(*Fila)) {
        Fila->inicio = novo;
    } else {
        // Caso contr�rio, adiciona o novo livro ao fim da fila
        Fila->fim->prox = novo;
    }
    
    Fila->fim = novo; // Atualiza o fim da fila
    return 1; // Retorna 1 para indicar sucesso
}

// Fun��o para exibir todos os livros da fila
void ExibirFila(tfila Fila) {
    if (FilaVazia(Fila)) {
        printf("\nCat�logo vazio.\n\n"); // Mensagem se a fila est� vazia
        return;
    }
    Livro* atual = Fila.inicio; // Come�a do in�cio da fila
    while (atual != NULL) {
        // Exibe os dados de cada livro
        printf("T�tulo: %s, Autor: %s, Ano de lan�amento: %d, G�nero: %s\n", 
               atual->titulo, atual->autor, atual->ano, atual->genero);
        atual = atual->prox; // Avan�a para o pr�ximo livro
    }
}

// Fun��o para ler livros de um arquivo e inserir na fila
void LerDeArquivo(tfila* Fila, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r"); // Abre o arquivo para leitura
    if (arquivo == NULL) {
        printf("\nERRO NO ARQUIVO!\n"); // Mensagem de erro se o arquivo n�o abrir
        return;
    }

    char titulo[100], autor[50], genero[30];
    int ano;
    // L� os dados dos livros do arquivo
    while (fscanf(arquivo, "%99[^;];%49[^;];%d;%29[^\n]\n", titulo, autor, &ano, genero) != EOF) {
// especifica como os dados est�o organizados no arquivo
// %99[^;]: l� at� 99 caracteres at� encontrar um ponto e v�rgula, armazenando-os em titulo.
// %49[^;]: l� at� 49 caracteres at� encontrar um ponto e v�rgula, armazenando-os em autor.
// %d: l� um inteiro e armazena em ano.
// %29[^\n]: l� at� 29 caracteres at� encontrar uma nova linha (\n), armazenando-os em genero.
        Inserir(Fila, titulo, autor, ano, genero); // Insere cada livro na fila
    }
    fclose(arquivo); // Fecha o arquivo ap�s leitura
}

// Fun��o para salvar a fila de livros em um arquivo
void SalvarEmArquivo(tfila Fila, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w"); // Abre o arquivo para escrita
    if (arquivo == NULL) {
        printf("\nERRO ao abrir o arquivo para escrita!\n");
        return; // Mensagem de erro se o arquivo n�o abrir
    }

    Livro* atual = Fila.inicio; // Come�a do in�cio da fila
    // Escreve os dados de cada livro no arquivo
    while (atual != NULL) {
        fprintf(arquivo, "%s;%s;%d;%s\n", atual->titulo, atual->autor, atual->ano, atual->genero);
        atual = atual->prox; // Avan�a para o pr�ximo livro
    }
    fclose(arquivo); // Fecha o arquivo
    printf("\nCat�logo salvo no arquivo %s.\n", nomeArquivo); // Mensagem de sucesso
}

// Fun��o para remover acentua��o de uma string
void removerAcento(char* str) {
    char* acentuados = "�����������������������"; // Caracteres acentuados
    char* semAcento = "aaaaaeeeiioooouuuuc"; // Correspondente sem acentua��o
    for (int i = 0; str[i]; i++) {
        for (int j = 0; acentuados[j]; j++) {
            if (str[i] == acentuados[j]) {
                str[i] = semAcento[j]; // Substitui acentuado por sem acento
                break;
            }
        }
        str[i] = tolower(str[i]); // Converte para min�sculas
    }
}

// Fun��o para comparar duas strings sem considerar acentua��o
int compararSemAcento(const char* str1, const char* str2) {
    char copia1[100], copia2[100];
    strcpy(copia1, str1); // Copia a primeira string
    strcpy(copia2, str2); // Copia a segunda string
    
    removerAcento(copia1); // Remove acentua��o da primeira string
    removerAcento(copia2); // Remove acentua��o da segunda string
    
    return strcmp(copia1, copia2) == 0; // Compara as strings normalizadas
}

// Fun��o para buscar um livro pelo t�tulo, autor, ano ou g�nero
void BuscarLivro(tfila Fila, const char* termo) {
    if (FilaVazia(Fila)) {
        printf("\nCat�logo vazio.\n"); // Mensagem se a fila est� vazia
        return;
    }

    Livro* atual = Fila.inicio; // Come�a do in�cio da fila
    int encontrou = 0; // Indicador de se encontrou um livro

    char termoNormalizado[100];
    strcpy(termoNormalizado, termo); // Copia o termo de busca
    removerAcento(termoNormalizado); // Remove acentua��o do termo

    // Percorre a lista de livros
    while (atual != NULL) {
        char tituloAtual[100];
        strcpy(tituloAtual, atual->titulo); // Copia o t�tulo do livro atual
        removerAcento(tituloAtual); // Remove acentua��o do t�tulo

        // Verifica se o termo corresponde ao t�tulo, autor ou g�nero
        if (compararSemAcento(tituloAtual, termoNormalizado) || 
            compararSemAcento(atual->autor, termoNormalizado) || 
            compararSemAcento(atual->genero, termoNormalizado)) {
            // Se encontrado, exibe os dados do livro
            printf("T�tulo: %s, Autor: %s, Ano de lan�amento: %d, G�nero: %s\n", 
                   atual->titulo, atual->autor, atual->ano, atual->genero);
            encontrou = 1; // Atualiza indicador
        }
        atual = atual->prox; // Avan�a para o pr�ximo livro
    }

    if (!encontrou) {
        printf("Nenhum livro foi encontrado: %s\n", termo); // Mensagem se n�o encontrar
    }
}

// Fun��o para buscar livros por ano
void BuscarPorAno(tfila Fila, int ano) {
    if (FilaVazia(Fila)) {
        printf("\nCat�logo vazio, n�o � poss�vel buscar livros.\n"); // Mensagem se a fila est� vazia
        return;
    }
    
    Livro* atual = Fila.inicio; // Come�a do in�cio da fila
    int encontrou = 0; // Indicador de se encontrou um livro

    // Percorre a lista de livros
    while (atual != NULL) {
        if (atual->ano == ano) { // Verifica se o ano do livro atual corresponde ao ano buscado
            // Se encontrado, exibe os dados do livro
            printf("\nT�tulo: %s, Autor: %s, Ano de lan�amento: %d, G�nero: %s\n\n", 
                   atual->titulo, atual->autor, atual->ano, atual->genero);
            encontrou = 1; // Atualiza indicador
        }
        atual = atual->prox; // Avan�a para o pr�ximo livro
    }

    if (!encontrou) {
        printf("Nenhum livro encontrado com esse ano de lan�amento: %d\n", ano); // Mensagem se n�o encontrar
    }
}

// Fun��o para remover um livro da fila pelo t�tulo
int RemoverLivro(tfila* Fila, const char* titulo) {
    if (FilaVazia(*Fila)) {
        printf("Cat�logo vazio, n�o � poss�vel remover livros.\n"); // Mensagem se a fila est� vazia
        return 0; // Retorna 0 para indicar falha
    }

    Livro* atual = Fila->inicio; // Come�a do in�cio da fila
    Livro* anterior = NULL; // Ponteiro para o livro anterior

    char tituloNormalizado[100];
    strcpy(tituloNormalizado, titulo); // Copia o t�tulo a ser removido
    removerAcento(tituloNormalizado); // Remove acentua��o do t�tulo

    // Percorre a lista de livros
    while (atual != NULL) {
        char tituloAtual[100];
        strcpy(tituloAtual, atual->titulo); // Copia o t�tulo do livro atual
        removerAcento(tituloAtual); // Remove acentua��o do t�tulo

        if (strcmp(tituloAtual, tituloNormalizado) == 0) { // Verifica se os t�tulos correspondem
            // Livro encontrado
            if (anterior == NULL) {
                Fila->inicio = atual->prox; // Remove o primeiro livro
                if (Fila->inicio == NULL) {
                    Fila->fim = NULL; // Fila ficou vazia
                }
            } else {
                anterior->prox = atual->prox; // Remove o livro do meio ou fim
                if (atual->prox == NULL) {
                    Fila->fim = anterior; // Atualiza o fim se for o �ltimo livro
                }
            }
            free(atual); // Libera a mem�ria do livro removido
            printf("Livro \"%s\" removido com sucesso!\n", titulo); // Mensagem de sucesso
            return 1; // Retorna 1 para indicar sucesso
        }
        anterior = atual; // Atualiza o livro anterior
        atual = atual->prox; // Avan�a para o pr�ximo livro
    }
    
    printf("Livro \"%s\" n�o encontrado no cat�logo.\n", titulo); // Mensagem se n�o encontrar
    return 0; // Livro n�o encontrado
}

// Fun��o principal do programa
int main() {
    setlocale(LC_ALL, "Portuguese"); // Define a localidade para portugu�s
    tfila Fila; // Declara a fila de livros
    int opcao; // Vari�vel para armazenar a op��o do menu
    char titulo[100], autor[50], genero[30], termo[100]; // Vari�veis para entrada de dados
    CriarFila(&Fila); // Inicializa a fila

    LerDeArquivo(&Fila, "livros.csv"); // L� livros de um arquivo

    // Loop do menu
    do {
        printf("\n--- Menu do Cat�logo ---\n");
        printf("1. Cadastrar novo Livro\n");
        printf("2. Mostrar todos os livros do cat�logo\n");
        printf("3. Buscar Livro por t�tulo, autor, ano de lan�amento ou g�nero\n");
        printf("4. Remover Livro\n");
        printf("5. Salvar e sair\n");
        printf("\nEscolha a op��o que deseja executar: ");

        // L� a op��o do usu�rio
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inv�lida! Tente novamente.\n"); // Mensagem de erro para entrada inv�lida
            while (getchar() != '\n'); // Limpa o buffer
            continue;
        }

        switch (opcao) {
            case 1: // Op��o para cadastrar um novo livro
                printf("Digite o t�tulo do livro: ");
                while (getchar() != '\n'); // Limpa o buffer
                fgets(titulo, sizeof(titulo), stdin); // L� o t�tulo
                titulo[strcspn(titulo, "\n")] = '\0'; // Remove nova linha
                printf("Digite o nome do autor do livro: ");
                fgets(autor, sizeof(autor), stdin); // L� o autor
                autor[strcspn(autor, "\n")] = '\0'; // Remove nova linha
                printf("Digite o ano de publica��o: ");
                int ano;
                if (scanf("%d", &ano) != 1) { // L� o ano
                    printf("Ano inv�lido!\n"); // Mensagem de erro se o ano for inv�lido
                    while (getchar() != '\n'); // Limpa o buffer
                    continue;
                }
                printf("Digite o g�nero do livro: ");
                while (getchar() != '\n'); // Limpa o buffer
                fgets(genero, sizeof(genero), stdin); // L� o g�nero
                genero[strcspn(genero, "\n")] = '\0'; // Remove nova linha
                Inserir(&Fila, titulo, autor, ano, genero); // Insere o novo livro na fila
                printf("\nLivro cadastrado com sucesso!\n"); // Mensagem de sucesso
                break;
            case 2: // Op��o para exibir todos os livros
                printf("\n--- Lista de Livros ---\n\n");
                ExibirFila(Fila); // Chama a fun��o para exibir livros
                break;
            case 3: // Op��o para buscar um livro
                printf("Digite o t�tulo, autor, ano de lan�amento ou g�nero para buscar: ");
                while (getchar() != '\n'); // Limpa o buffer
                fgets(termo, sizeof(termo), stdin); // L� o termo de busca
                termo[strcspn(termo, "\n")] = '\0'; // Remove nova linha
                
                int anoBuscado;
                // Verifica se o termo lido � um ano
                if (sscanf(termo, "%d", &anoBuscado) == 1) {
                    BuscarPorAno(Fila, anoBuscado); // Busca por ano
                } else {
                    BuscarLivro(Fila, termo); // Busca por t�tulo, autor ou g�nero
                }
                break;
            case 4: // Op��o para remover um livro
                printf("Digite o t�tulo do livro a ser removido: ");
                while (getchar() != '\n'); // Limpa o buffer
                fgets(titulo, sizeof(titulo), stdin); // L� o t�tulo
                titulo[strcspn(titulo, "\n")] = '\0'; // Remove nova linha
                RemoverLivro(&Fila, titulo); // Remove o livro da fila
                break;
            case 5: // Op��o para salvar e sair
                SalvarEmArquivo(Fila, "livros.csv"); // Salva a fila em um arquivo
                printf("Saindo...\n"); // Mensagem de sa�da
                break;
            default: // Caso de op��o inv�lida
                printf("Op��o inv�lida!\n");
        }
    } while (opcao != 5); // Continua at� a op��o de sair ser escolhida

    return 0; // Finaliza o programa
}
