#include "arq.h"

// Funcao de criacao do descritor da lista - P.V
struct descritor *cria()
{
    struct descritor *desc = malloc(sizeof(struct descritor));
    if (desc == NULL)
    {
        return NULL; // O -1 foi escolhido como padrao de retorno de erro para todas as funcoes
    }
    desc->numLinhas = 0;
    desc->primeiraLinha = NULL;
}
// Funcao de importacao do texto para a lista - P.V
int importaTexto(struct descritor *desc, FILE *fp)
{
    int numLinha = 0;

    desc->primeiraLinha = malloc(sizeof(struct noLinha));

    if (desc->primeiraLinha == NULL)
        return -1;

    char linha[900];

    struct noLinha *aux = malloc(sizeof(struct noLinha));

    while (fgets(linha, 900, fp) != NULL) // Esse while le ate o final do arquivo
    {
        int numPalavras = 0;
        numLinha += 1;
        int numCol = 1;
        int acabou = 0;
        int quantEspacos = 0;
        struct noLinha *temp = malloc(sizeof(struct noLinha));
        if (temp == NULL)
        {
            return -1;
        }
        temp->lin = numLinha;
        temp->primeiraPalavra = malloc(sizeof(struct noPalavra));
        struct noPalavra *aux2 = malloc(sizeof(struct noPalavra));

        char *palavra = malloc(40 * sizeof(char));
        int i2 = 0;                                    // Esse i2 sera usado para servir de indice da palavra
                                                       // Representando cada caractere
        for (int i = 0; i < strlen(linha) + 1; i += 1) // Esse for le ate o final da linha
        {
            if (linha[i] != ' ' && acabou == 0 && linha[i] != '\n' && linha[i] != '\0')
            {

                palavra[i2] = linha[i];
                i2 += 1;
            }
            else if (linha[i] == ' ') // A logica por tras desse bloco else if eh basicamente contar quantos espacos
            {                         // tem apos a atual palavra e settar a flag que a palavra acabou
                quantEspacos += 1;
                acabou = 1;
            }
            else // Condicao indicando que a palavra ja acabou e os espacos tambem
            {    // ou seja, a proxima palavra comecou
                struct noPalavra *temp2 = malloc(sizeof(struct noPalavra));
                if (temp2 == NULL)
                {
                    return -1;
                }
                strcpy(temp2->palavra, palavra);
                temp2->col = numCol;
                if (numCol == 1)
                {
                    temp2->antPal = NULL;
                    temp->primeiraPalavra = temp2;
                }
                else
                {
                    temp2->antPal = aux2;
                }
                aux2->proxPal = temp2;
                temp2->proxPal = NULL;
                aux2 = temp2;
                numCol += strlen(palavra) + quantEspacos;
                quantEspacos = 0;
                acabou = 0;
                i2 = 0;
                if (palavra != NULL)
                    free(palavra);
                palavra = malloc(40 * sizeof(char)); // Reset da palavra lida
                                                     // caractere da proxima palavra - Pedro Vargas
                numPalavras += 1;
                if (linha[i] == '\n' || linha[i] == '\0')
                {
                    break;
                }
                i -= 1; // Temos que diminuir o indice em uma unidade, pois lemos ate o primeiro
            }
        }
        /*char *palavra;
        palavra = strt*char *palavra;
        palavra = strtok(linha, " ");
        while (palavra)
        {
            struct noPalavra *temp2 = malloc(sizeof(struct noPalavra));
            if (temp2 == NULL)
            {
                return -1;
            }
            strcpy(temp2->palavra, palavra);
            temp2->col = numCol;
            if (numCol == 1)
            {
                temp2->antPal = NULL;
                temp->primeiraPalavra = temp2;
            }
            else
            {
                temp2->antPal = aux2;
            }
            aux2->proxPal = temp2;
            temp2->proxPal = NULL;
            aux2 = temp2;
            numCol += strlen(palavra) + 1;
            palavra = strtok(NULL, ".!,? ");
        }*/
        /*char *palavra;
     palavra = strt*char *palavra;
     palavra = strtok(linha, " ");
     while (palavra)
     {
         struct noPalavra *temp2 = malloc(sizeof(struct noPalavra));
         if (temp2 == NULL)
         {
             return -1;
         }
         strcpy(temp2->palavra, palavra);
         temp2->col = numCol;
         if (numCol == 1)
         {
             temp2->antPal = NULL;
             temp->primeiraPalavra = temp2;
         }
         else
         {
             temp2->antPal = aux2;
         }
         aux2->proxPal = temp2;
         temp2->proxPal = NULL;
         aux2 = temp2;
         numCol += strlen(palavra) + 1;
         palavra = strtok(NULL, ".!,? ");
     }*/
        if (numLinha == 1)
        {
            temp->antLin = NULL;
            desc->primeiraLinha = temp;
        }
        else
        {
            temp->antLin = aux;
        }
        aux->proxLin = temp;
        temp->proxLin = NULL;
        aux = temp;
        temp->numPalavras = numPalavras;
    }
    desc->numLinhas = numLinha;
}