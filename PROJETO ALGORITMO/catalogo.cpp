#include <stdio.h>     
#include <stdlib.h>    // Biblioteca para funções de alocação de memória
#include <locale.h>    // Biblioteca para definir configurações regionais
#include <string.h>    // Biblioteca para manipulação de strings
#include <ctype.h>     // Biblioteca para funções de manipulação de caracteres

// Estrutura do livro
typedef struct Livro {
    char titulo[100];  // array de caracteres que armazena o título do livro (até 99 caracteres)
    char autor[50];    // Autor do livro
    int ano;           // Ano de lançamento
    char genero[30];   // Gênero do livro
    struct Livro* prox; // Ponteiro para o próximo livro na lista
} Livro;

// Estrutura que representa a fila de livros
typedef struct {
    Livro* inicio; // Ponteiro para o início da fila
    Livro* fim;    // Ponteiro para o fim da fila
} tfila; // ponteiro para a estrutura da fila

// Função para inicializar a fila
void CriarFila(tfila* Fila) {
    Fila->inicio = Fila->fim = NULL; // A fila começa vazia
    printf("Bem-vindo ao seu catálogo!\n");
    printf("No seu catálogo você pode listar livros, adicionar novos livros,"
           "\nremover livros e buscar por título, autor, ano de lançamento ou gênero.\n");
}

// Verifica se a fila está vazia
int FilaVazia(tfila Fila) {
    return (Fila.inicio == NULL); // Retorna 1 se a fila está vazia, 0 caso contrário
}

// Função para inserir um novo livro na fila
int Inserir(tfila* Fila, char* titulo, char* autor, int ano, char* genero) {
    Livro* novo = (Livro*)malloc(sizeof(Livro)); // Aloca memória para um novo livro
    if (novo == NULL) return 0; // Se falhar a alocação, retorna 0

    // Copia os dados do novo livro
    strcpy(novo->titulo, titulo);
    strcpy(novo->autor, autor);
    novo->ano = ano;
    strcpy(novo->genero, genero);
    novo->prox = NULL; // O novo livro será o último, então próximo é NULL

    // Se a fila está vazia, o novo livro é o primeiro
    if (FilaVazia(*Fila)) {
        Fila->inicio = novo;
    } else {
        // Caso contrário, adiciona o novo livro ao fim da fila
        Fila->fim->prox = novo;
    }
    
    Fila->fim = novo; // Atualiza o fim da fila
    return 1; // Retorna 1 para indicar sucesso
}

// Função para exibir todos os livros da fila
void ExibirFila(tfila Fila) {
    if (FilaVazia(Fila)) {
        printf("\nCatálogo vazio.\n\n"); // Mensagem se a fila está vazia
        return;
    }
    Livro* atual = Fila.inicio; // Começa do início da fila
    while (atual != NULL) {
        // Exibe os dados de cada livro
        printf("Título: %s, Autor: %s, Ano de lançamento: %d, Gênero: %s\n", 
               atual->titulo, atual->autor, atual->ano, atual->genero);
        atual = atual->prox; // Avança para o próximo livro
    }
}

// Função para ler livros de um arquivo e inserir na fila
void LerDeArquivo(tfila* Fila, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r"); // Abre o arquivo para leitura
    if (arquivo == NULL) {
        printf("\nERRO NO ARQUIVO!\n"); // Mensagem de erro se o arquivo não abrir
        return;
    }

    char titulo[100], autor[50], genero[30];
    int ano;
    // Lê os dados dos livros do arquivo
    while (fscanf(arquivo, "%99[^;];%49[^;];%d;%29[^\n]\n", titulo, autor, &ano, genero) != EOF) {
// especifica como os dados estão organizados no arquivo
// %99[^;]: lê até 99 caracteres até encontrar um ponto e vírgula, armazenando-os em titulo.
// %49[^;]: lê até 49 caracteres até encontrar um ponto e vírgula, armazenando-os em autor.
// %d: lê um inteiro e armazena em ano.
// %29[^\n]: lê até 29 caracteres até encontrar uma nova linha (\n), armazenando-os em genero.
        Inserir(Fila, titulo, autor, ano, genero); // Insere cada livro na fila
    }
    fclose(arquivo); // Fecha o arquivo após leitura
}

// Função para salvar a fila de livros em um arquivo
void SalvarEmArquivo(tfila Fila, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w"); // Abre o arquivo para escrita
    if (arquivo == NULL) {
        printf("\nERRO ao abrir o arquivo para escrita!\n");
        return; // Mensagem de erro se o arquivo não abrir
    }

    Livro* atual = Fila.inicio; // Começa do início da fila
    // Escreve os dados de cada livro no arquivo
    while (atual != NULL) {
        fprintf(arquivo, "%s;%s;%d;%s\n", atual->titulo, atual->autor, atual->ano, atual->genero);
        atual = atual->prox; // Avança para o próximo livro
    }
    fclose(arquivo); // Fecha o arquivo
    printf("\nCatálogo salvo no arquivo %s.\n", nomeArquivo); // Mensagem de sucesso
}

// Função para remover acentuação de uma string
void removerAcento(char* str) {
    char* acentuados = "áàãâäéèêëíìîïóòõôöúùûüç"; // Caracteres acentuados
    char* semAcento = "aaaaaeeeiioooouuuuc"; // Correspondente sem acentuação
    for (int i = 0; str[i]; i++) {
        for (int j = 0; acentuados[j]; j++) {
            if (str[i] == acentuados[j]) {
                str[i] = semAcento[j]; // Substitui acentuado por sem acento
                break;
            }
        }
        str[i] = tolower(str[i]); // Converte para minúsculas
    }
}

// Função para comparar duas strings sem considerar acentuação
int compararSemAcento(const char* str1, const char* str2) {
    char copia1[100], copia2[100];
    strcpy(copia1, str1); // Copia a primeira string
    strcpy(copia2, str2); // Copia a segunda string
    
    removerAcento(copia1); // Remove acentuação da primeira string
    removerAcento(copia2); // Remove acentuação da segunda string
    
    return strcmp(copia1, copia2) == 0; // Compara as strings normalizadas
}

// Função para buscar um livro pelo título, autor, ano ou gênero
void BuscarLivro(tfila Fila, const char* termo) {
    if (FilaVazia(Fila)) {
        printf("\nCatálogo vazio.\n"); // Mensagem se a fila está vazia
        return;
    }

    Livro* atual = Fila.inicio; // Começa do início da fila
    int encontrou = 0; // Indicador de se encontrou um livro

    char termoNormalizado[100];
    strcpy(termoNormalizado, termo); // Copia o termo de busca
    removerAcento(termoNormalizado); // Remove acentuação do termo

    // Percorre a lista de livros
    while (atual != NULL) {
        char tituloAtual[100];
        strcpy(tituloAtual, atual->titulo); // Copia o título do livro atual
        removerAcento(tituloAtual); // Remove acentuação do título

        // Verifica se o termo corresponde ao título, autor ou gênero
        if (compararSemAcento(tituloAtual, termoNormalizado) || 
            compararSemAcento(atual->autor, termoNormalizado) || 
            compararSemAcento(atual->genero, termoNormalizado)) {
            // Se encontrado, exibe os dados do livro
            printf("Título: %s, Autor: %s, Ano de lançamento: %d, Gênero: %s\n", 
                   atual->titulo, atual->autor, atual->ano, atual->genero);
            encontrou = 1; // Atualiza indicador
        }
        atual = atual->prox; // Avança para o próximo livro
    }

    if (!encontrou) {
        printf("Nenhum livro foi encontrado: %s\n", termo); // Mensagem se não encontrar
    }
}

// Função para buscar livros por ano
void BuscarPorAno(tfila Fila, int ano) {
    if (FilaVazia(Fila)) {
        printf("\nCatálogo vazio, não é possível buscar livros.\n"); // Mensagem se a fila está vazia
        return;
    }
    
    Livro* atual = Fila.inicio; // Começa do início da fila
    int encontrou = 0; // Indicador de se encontrou um livro

    // Percorre a lista de livros
    while (atual != NULL) {
        if (atual->ano == ano) { // Verifica se o ano do livro atual corresponde ao ano buscado
            // Se encontrado, exibe os dados do livro
            printf("\nTítulo: %s, Autor: %s, Ano de lançamento: %d, Gênero: %s\n\n", 
                   atual->titulo, atual->autor, atual->ano, atual->genero);
            encontrou = 1; // Atualiza indicador
        }
        atual = atual->prox; // Avança para o próximo livro
    }

    if (!encontrou) {
        printf("Nenhum livro encontrado com esse ano de lançamento: %d\n", ano); // Mensagem se não encontrar
    }
}

// Função para remover um livro da fila pelo título
int RemoverLivro(tfila* Fila, const char* titulo) {
    if (FilaVazia(*Fila)) {
        printf("Catálogo vazio, não é possível remover livros.\n"); // Mensagem se a fila está vazia
        return 0; // Retorna 0 para indicar falha
    }

    Livro* atual = Fila->inicio; // Começa do início da fila
    Livro* anterior = NULL; // Ponteiro para o livro anterior

    char tituloNormalizado[100];
    strcpy(tituloNormalizado, titulo); // Copia o título a ser removido
    removerAcento(tituloNormalizado); // Remove acentuação do título

    // Percorre a lista de livros
    while (atual != NULL) {
        char tituloAtual[100];
        strcpy(tituloAtual, atual->titulo); // Copia o título do livro atual
        removerAcento(tituloAtual); // Remove acentuação do título

        if (strcmp(tituloAtual, tituloNormalizado) == 0) { // Verifica se os títulos correspondem
            // Livro encontrado
            if (anterior == NULL) {
                Fila->inicio = atual->prox; // Remove o primeiro livro
                if (Fila->inicio == NULL) {
                    Fila->fim = NULL; // Fila ficou vazia
                }
            } else {
                anterior->prox = atual->prox; // Remove o livro do meio ou fim
                if (atual->prox == NULL) {
                    Fila->fim = anterior; // Atualiza o fim se for o último livro
                }
            }
            free(atual); // Libera a memória do livro removido
            printf("Livro \"%s\" removido com sucesso!\n", titulo); // Mensagem de sucesso
            return 1; // Retorna 1 para indicar sucesso
        }
        anterior = atual; // Atualiza o livro anterior
        atual = atual->prox; // Avança para o próximo livro
    }
    
    printf("Livro \"%s\" não encontrado no catálogo.\n", titulo); // Mensagem se não encontrar
    return 0; // Livro não encontrado
}

// Função principal do programa
int main() {
    setlocale(LC_ALL, "Portuguese"); // Define a localidade para português
    tfila Fila; // Declara a fila de livros
    int opcao; // Variável para armazenar a opção do menu
    char titulo[100], autor[50], genero[30], termo[100]; // Variáveis para entrada de dados
    CriarFila(&Fila); // Inicializa a fila

    LerDeArquivo(&Fila, "livros.csv"); // Lê livros de um arquivo

    // Loop do menu
    do {
        printf("\n--- Menu do Catálogo ---\n");
        printf("1. Cadastrar novo Livro\n");
        printf("2. Mostrar todos os livros do catálogo\n");
        printf("3. Buscar Livro por título, autor, ano de lançamento ou gênero\n");
        printf("4. Remover Livro\n");
        printf("5. Salvar e sair\n");
        printf("\nEscolha a opção que deseja executar: ");

        // Lê a opção do usuário
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida! Tente novamente.\n"); // Mensagem de erro para entrada inválida
            while (getchar() != '\n'); // Limpa o buffer
            continue;
        }

        switch (opcao) {
            case 1: // Opção para cadastrar um novo livro
                printf("Digite o título do livro: ");
                while (getchar() != '\n'); // Limpa o buffer
                fgets(titulo, sizeof(titulo), stdin); // Lê o título
                titulo[strcspn(titulo, "\n")] = '\0'; // Remove nova linha
                printf("Digite o nome do autor do livro: ");
                fgets(autor, sizeof(autor), stdin); // Lê o autor
                autor[strcspn(autor, "\n")] = '\0'; // Remove nova linha
                printf("Digite o ano de publicação: ");
                int ano;
                if (scanf("%d", &ano) != 1) { // Lê o ano
                    printf("Ano inválido!\n"); // Mensagem de erro se o ano for inválido
                    while (getchar() != '\n'); // Limpa o buffer
                    continue;
                }
                printf("Digite o gênero do livro: ");
                while (getchar() != '\n'); // Limpa o buffer
                fgets(genero, sizeof(genero), stdin); // Lê o gênero
                genero[strcspn(genero, "\n")] = '\0'; // Remove nova linha
                Inserir(&Fila, titulo, autor, ano, genero); // Insere o novo livro na fila
                printf("\nLivro cadastrado com sucesso!\n"); // Mensagem de sucesso
                break;
            case 2: // Opção para exibir todos os livros
                printf("\n--- Lista de Livros ---\n\n");
                ExibirFila(Fila); // Chama a função para exibir livros
                break;
            case 3: // Opção para buscar um livro
                printf("Digite o título, autor, ano de lançamento ou gênero para buscar: ");
                while (getchar() != '\n'); // Limpa o buffer
                fgets(termo, sizeof(termo), stdin); // Lê o termo de busca
                termo[strcspn(termo, "\n")] = '\0'; // Remove nova linha
                
                int anoBuscado;
                // Verifica se o termo lido é um ano
                if (sscanf(termo, "%d", &anoBuscado) == 1) {
                    BuscarPorAno(Fila, anoBuscado); // Busca por ano
                } else {
                    BuscarLivro(Fila, termo); // Busca por título, autor ou gênero
                }
                break;
            case 4: // Opção para remover um livro
                printf("Digite o título do livro a ser removido: ");
                while (getchar() != '\n'); // Limpa o buffer
                fgets(titulo, sizeof(titulo), stdin); // Lê o título
                titulo[strcspn(titulo, "\n")] = '\0'; // Remove nova linha
                RemoverLivro(&Fila, titulo); // Remove o livro da fila
                break;
            case 5: // Opção para salvar e sair
                SalvarEmArquivo(Fila, "livros.csv"); // Salva a fila em um arquivo
                printf("Saindo...\n"); // Mensagem de saída
                break;
            default: // Caso de opção inválida
                printf("Opção inválida!\n");
        }
    } while (opcao != 5); // Continua até a opção de sair ser escolhida

    return 0; // Finaliza o programa
}
