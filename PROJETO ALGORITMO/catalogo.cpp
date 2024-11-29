// fila com lista encadeada

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Estrutura do livro
typedef struct Livro {
    char titulo[100];   
    char autor[50];     
    int ano;            
    char genero[30];    
    struct Livro* prox; // Ponteiro para o próximo livro
} Livro;

// --------------------------------------------------------------------------------------------

// Estrutura da fila de livros
typedef struct { 
    Livro* inicio; 
    Livro* fim;    
} Fila;

// --------------------------------------------------------------------------------------------

void inicializarFila(Fila* fila) { // ponteiro para a variável que representa a Fila de livros
    fila->inicio = NULL;
    fila->fim = NULL;
    
    printf("Bem-vindo ao Catálogo de Livros!\n");
    printf("No seu catálogo você pode listar livros que ele possue, adicionar novos livros,"
           "\nremover livros e buscar por título, autor ou gênero.\n");
}

// --------------------------------------------------------------------------------------------

// verifica se a fila está vazia
int filaVazia(Fila fila) { 
    return fila.inicio == NULL; 
}

// --------------------------------------------------------------------------------------------

void inserirLivro(Fila* fila, char* titulo, char* autor, int ano, char* genero) {
    Livro* novoLivro = (Livro*)malloc(sizeof(Livro)); // Aloca memória para um novo livro
    if (!novoLivro) { // Verifica se a alocação falhou (se for NULL)
        printf("Erro ao alocar memória para o livro.\n");
        return;
    }
    // Preenche os dados do novo livro
    strcpy(novoLivro->titulo, titulo);
    strcpy(novoLivro->autor, autor);
    novoLivro->ano = ano;
    strcpy(novoLivro->genero, genero);
    novoLivro->prox = NULL; 

    // Insere o novo livro na fila (como uma lista encadeada)
    if (filaVazia(*fila)) {
        fila->inicio = novoLivro; 
    } else {
        fila->fim->prox = novoLivro; 
    }
    fila->fim = novoLivro; 
}

// --------------------------------------------------------------------------------------------

void exibirLivros(Fila fila) {

     Livro* atual = fila.inicio; // aponta para o primeiro livro da fila
     
     // enquanto houver um livro na fila, o loop continuará
    while (atual) { 
        printf("Título: %s | Autor: %s | Ano: %d | Gênero: %s\n",
               atual->titulo, atual->autor, atual->ano, atual->genero);
        atual = atual->prox; // Avança para o próximo livro na lista
    }

    if (filaVazia(fila)) { // Verifica se a fila está vazia
        printf("Nenhum livro no catálogo.\n");
        return;
    }    
}

// --------------------------------------------------------------------------------------------

void buscarLivro(Fila fila, const char* termo) {
    
    Livro* atual = fila.inicio;
    int encontrado = 1; 


// Verifica se o termo de busca está no título, autor ou gênero do livro    
    while (atual) {
        if (strstr(atual->titulo, termo) || strstr(atual->autor, termo) || strstr(atual->genero, termo)) {
            printf("Título: %s | Autor: %s | Ano: %d | Gênero: %s\n", atual->titulo, atual->autor, atual->ano, atual->genero);
            encontrado = 1; 
        }
        atual = atual->prox; 
    }
    // se a saída for diferente de enconntrado = 1 exibe a mensagem
    if (!encontrado) { 
        printf("Nenhum livro encontrado com o termo: %s\n", termo);
    }
    
     if (filaVazia(fila)) { // Verifica se a fila está vazia
        printf("Nenhum livro no catálogo.\n");
        return;
    }
}

// --------------------------------------------------------------------------------------------

void removerLivro(Fila* fila, const char* titulo) {
    if (filaVazia(*fila)) { 
        printf("Nenhum livro no catálogo para remover.\n");
        return;
    }
//  "atual" é o livro a ser removiido da lista
    Livro* atual = fila->inicio;
    Livro* anterior = NULL; // Ponteiro para o livro anterior


// se for null então passa para o próximo livro da lista
    while (atual && strcmp(atual->titulo, titulo) != 0) { 
        anterior = atual; // o ponteiro anterior é movido para o livro atual e o ponteiro atual avança para o próximo livro
        atual = atual->prox; 
    }

    if (!atual) {   
	   printf("Livro não encontrado: %s\n", titulo);
        return;
    }

    if (anterior) { // se anterior não for NULL, o livro a ser removido não é o primeiro livro da lista
        anterior->prox = atual->prox; // vai apontar para o próximo livro após o removido
    } else {
        fila->inicio = atual->prox; // Se for o primeiro, o início aponta para o próximo
    }

    if (atual == fila->fim) { 
        fila->fim = anterior; // O último livro passa a ser o anterior
    }

    free(atual); // Libera a memória do livro removido
    printf("Livro \"%s\" removido com sucesso.\n", titulo);
}

// --------------------------------------------------------------------------------------------


void lerLivrosDeArquivo(Fila* fila, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r"); // tenta abrir o arquivo para leitura
    if (!arquivo) { 
        printf("Arquivo %s não encontrado. Um novo catálogo será criado.\n", nomeArquivo);
        return;
    }

    char titulo[100], autor[50], genero[30];
    int ano;

    // Lê cada linha do arquivo (até encontrar ; ou \n) e insere os dados na fila

    while (fscanf(arquivo, "%99[^;];%49[^;];%d;%29[^\n]\n", titulo, autor, &ano, genero) != EOF) {
        inserirLivro(fila, titulo, autor, ano, genero);
    }
    fclose(arquivo); // Fecha o arquivo após a leitura
}

// --------------------------------------------------------------------------------------------

void salvarLivrosEmArquivo(Fila fila, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w"); // Abre o arquivo para escrita
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s para salvar.\n", nomeArquivo);
        return;
    }

    Livro* atual = fila.inicio;

    while (atual) {
        fprintf(arquivo, "%s;%s;%d;%s\n", atual->titulo, atual->autor, atual->ano, atual->genero);
        atual = atual->prox; 
    }
    fclose(arquivo); 
    printf("Catálogo salvo no arquivo %s.\n", nomeArquivo);
}


// --------------------------------------------------------------------------------------------

int main() {
	
    setlocale(LC_ALL, "Portuguese");
    Fila catalogo; // Declara a fila de livros em "catalogo' 
    inicializarFila(&catalogo); // Inicializa a fila de livros
    const char* nomeArquivo = "livros.csv"; 
    
    lerLivrosDeArquivo(&catalogo, nomeArquivo); // Lê os livros do arquivo, se houver

    int opcao;
    char titulo[100], autor[50], genero[30];
    int ano;

    do {
        printf("\n--- Menu do Catálogo ---\n");
        printf("1. Cadastrar novo Livro\n");
        printf("2. Mostrar todos os livros do catálogo\n");
        printf("3. Buscar Livro por título, autor ou gênero\n");
        printf("4. Remover Livro\n");
        printf("5. Salvar e sair\n");

        printf("\nEscolha a opção que deseja executar: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer de entrada

// --------------------------------------------------------------------------------------------

        switch (opcao) {
            case 1:
                // Cadastro do livro
                printf("Título: ");
                fgets(titulo, sizeof(titulo), stdin); // garantir que não ocorra transbordamento de memória
                titulo[strcspn(titulo, "\n")] = '\0'; // Remove o caractere de nova linha (\n) adicionado ao final da string quando fgets é usado

                printf("Autor: ");
                fgets(autor, sizeof(autor), stdin); // garantir que não ocorra transbordamento de memória
                autor[strcspn(autor, "\n")] = '\0';

                printf("Ano: ");
                scanf("%d", &ano);
                getchar(); // Limpa o buffer de entrada

                printf("Gênero: ");
                fgets(genero, sizeof(genero), stdin);// garantir que não ocorra transbordamento de memória
                genero[strcspn(genero, "\n")] = '\0';

                inserirLivro(&catalogo, titulo, autor, ano, genero); // Insere o novo livro na fila
                printf("\nLivro cadastrado com sucesso!\n");
                break;

// --------------------------------------------------------------------------------------------

            case 2:
                exibirLivros(catalogo);
                break;

// --------------------------------------------------------------------------------------------

            case 3:
                // Busca livros por título, autor ou gênero
                printf("Digite o título, autor, ou gênero para buscar no catálogo: ");
                fgets(titulo, sizeof(titulo), stdin); // garantir que não ocorra transbordamento de memória
                titulo[strcspn(titulo, "\n")] = '\0';
                buscarLivro(catalogo, titulo);
                break;

// --------------------------------------------------------------------------------------------

            case 4:
                // Remove um livro pelo título
                printf("Digite o título do livro a ser removido: ");
                fgets(titulo, sizeof(titulo), stdin); // garantir que não ocorra transbordamento de memória
                titulo[strcspn(titulo, "\n")] = '\0';
                removerLivro(&catalogo, titulo);
                break;

// --------------------------------------------------------------------------------------------

            case 5:
                // Salva os livros no arquivo e sai
                salvarLivrosEmArquivo(catalogo, nomeArquivo);
                printf("Saindo...\n");
                break;
                
// --------------------------------------------------------------------------------------------

            default:
                // Se a opção for inválida
                printf("Opção inválida! Tente novamente.\n");
                
        }
    } while (opcao != 5);
    return 0; // Finaliza o programa
}
