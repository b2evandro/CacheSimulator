#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define TAM 16
#define TAMST 11
#define TELA system("clear");

// Structs
typedef struct celula
{
    char endereco[TAMST];
    char conteudo;
    int validar;

} t_celula;

typedef struct blocomemoria
{
    int bloco;
    t_celula celula_bloco[4];
} t_bloco;

typedef struct linha_quadro
{
    int alterado;
    int contador_de_acesso;
    t_bloco bloco_cache;
} t_quadro;

typedef struct ESTFILA
{
    int INI, FIM;
    t_quadro linha_quadro[TAM];
} t_Fila;

// inicia memoria principal
void insereConteudo(int num, t_celula *celula_memo_principal)
{

    char binario[TAMST];
    char binarioCorreto[TAMST];

    int i, j = 0, k, cont = 0;

    // limpa lixo
    for (i = 0; i < TAMST; i++)
    {
        binario[i] = 48;
        binarioCorreto[i] = 48;
    }

    cont = num;

    i = 0;
    // atribui binario inverso
    while (num > 0)
    {
        if (num % 2 == 0)
        {
            binario[i] = '0';
        }
        else
        {
            binario[i] = '1';
        }
        //num = num % 2;
        i++;
        num = num / 2;
    }
    // define char aleatorio
    (*celula_memo_principal).conteudo = (rand() % 26) + 97;

    // inverte ordem
    for (i = 10; i >= 0; i--)
    {
        (*celula_memo_principal).endereco[j] = binario[i];
        j++;
    }
}

// Visualização
void mostramemoriaPricipal(t_celula MemPrincipal[])
{
    TELA;
    printf("Mostrando MemPrincipal: \n");

    printf("Endereco");
    printf("\t\tconteudo");
    for (int j = 0; j < 2048; j++)
    {
        // printf("%d - ", j);
        printf("\n");

        for (int h = 0; h < TAMST; h++)
        {
            printf("%c", MemPrincipal[j].endereco[h]);
        }

        printf("\t\t%c", MemPrincipal[j].conteudo);
    }
    getchar();
    getchar();
}

// Funções da fila
t_Fila CriarFila(void)
{
    t_Fila F;
    F.INI = -1;
    F.FIM = -1;
    return F;
}

int FilaVazia(t_Fila F)
{
    if (F.INI == -1 && F.FIM == -1)
        return 1;
    else
        return 0;
}

t_Fila QUEUE(t_quadro linha_do_quadro, t_Fila *F)
{
    if (FilaVazia(*F))
    {
        (*F).INI++;
        (*F).FIM++;
    }
    else
    {
        (*F).FIM++;
        if ((*F).FIM == TAM && (*F).INI != 0)
            (*F).FIM = 0;
    }
    (*F).linha_quadro[(*F).FIM] = linha_do_quadro;
    return (*F);
}

t_quadro
DEQUEUE(t_Fila *F)
{
    t_quadro Valor;

    Valor = F->linha_quadro[F->INI];
    if (F->INI == F->FIM)
    {
        F->INI = -1;
        F->FIM = -1;
    }
    else
    {
        F->INI++;
        if (F->INI == TAM && F->FIM >= 0)
            F->INI = 0;
    }
    return Valor;
}

void mostramemoriaCache(t_Fila F)
{
    TELA;
    printf("\nMostrando MemCache: \n");
    printf("Alterado");
    printf("\t Acessos");
    printf("\tConteudo\t");
    printf("\tEndereco de inicio do Bloco");
    t_quadro VALOR;
    int cont = 0;
    while (!FilaVazia(F))
    {

        VALOR = DEQUEUE(&F);
        printf("\n");
        printf("%d ", VALOR.alterado);
        printf("\t\t\t\t%d \t", VALOR.contador_de_acesso);
        for (int j = 0; j < 4; j++)
        {

            printf("\t %c", VALOR.bloco_cache.celula_bloco[j].conteudo);
        }
        printf("\t");
        for (int h = 0; h < TAMST; h++)
        {
            printf("%c", VALOR.bloco_cache.celula_bloco[0].endereco[h]);
        }
    }
    getchar();
    getchar();
}
// Funções EstatÃ­sticas
int miss = 0;
int fail = 0;

void conta_acertos()
{
    miss++;
}

void conta_erros()
{
    fail++;
}

int stringCompa(char string1[], char string2[], int tam)
{
    int num = 0, achou = 0;
    for (int hh = 0; hh < tam; hh++)
    {
        if (string1[hh] == string2[hh])
        {
            num++;
        }
    }
    if (num == TAMST)
    {
        achou = 1;
    }
    return achou;
}
int buscaemCache(t_Fila FilaCache, char endereco[])
{
    int achou, cont, contCelCache;
    achou = cont = contCelCache = 0;
    while ((contCelCache < 64) && (achou == 0))
    {
        for (int contFila = 0; contFila < TAM; contFila++)
        {
            for (int contBloco = 0; contBloco < 4; contBloco++)
            {
                if (stringCompa(endereco, (FilaCache).linha_quadro[contFila].bloco_cache.celula_bloco[contBloco].endereco, TAMST) == 1)
                {
                    achou = 1;
                    printf("\nO conteudo do endereço é: %c \n", (FilaCache).linha_quadro[contFila].bloco_cache.celula_bloco[contBloco].conteudo);
                }
                contCelCache++;
            }
        }
    }
    return achou;
}

int buscaMP(t_Fila *Fila, t_bloco *Blocos, char endereco[])
{
    int bloco;
    int achouBloco = 0;
    int contBloco = 0;
    while (achouBloco == 0 && contBloco < 512)
    {

        int contCelulas = 0;

        while (contCelulas < 4 && achouBloco == 0)
        {
            if ((stringCompa(endereco, Blocos[contBloco].celula_bloco[contCelulas].endereco, TAMST)) == 1)
            {
                achouBloco = 1;
                bloco = contBloco;
                printf("\nAchou o bloco %d \n", bloco);
                printf("\nConteudo do endereco digitado: %c \n", Blocos[contBloco].celula_bloco[contCelulas].conteudo);
                t_quadro MemoCache;
                MemoCache.alterado = 0;
                MemoCache.contador_de_acesso = 0;

                MemoCache.bloco_cache = Blocos[bloco];
                DEQUEUE(Fila);
                (*Fila) = QUEUE(MemoCache, Fila);
            }
            else
            {
                contCelulas++;
            }
        }
        contBloco++;
    }

    if (achouBloco == 0)
    {
        printf("\n\n\tEndereco/bloco nao encontrado\n\tFavor verificar o endereco digitado\n");
    }
    if (achouBloco == 1)
        return bloco;
    else
        return -1;
}
int alterabloco(t_Fila *Fila, char conteudo, char endereco[])
{
    int achou_alterou, cont, contCelCache;
    achou_alterou = cont = contCelCache = 0;
    while ((contCelCache < 64) && (achou_alterou == 0))
    {
        for (int contFila = 0; contFila < TAM; contFila++)
        {
            for (int contBloco = 0; contBloco < 4; contBloco++)
            {
                if (stringCompa(endereco, (*Fila).linha_quadro[contFila].bloco_cache.celula_bloco[contBloco].endereco, TAMST) == 1)
                {
                    achou_alterou = 1;
                    (*Fila).linha_quadro[contFila].alterado = 1;
                    (*Fila).linha_quadro[contFila].bloco_cache.celula_bloco[contBloco].conteudo = conteudo;
                }
                contCelCache++;
            }
        }
    }
    return achou_alterou;
}
void lermemoria(t_Fila *FilaCache, t_bloco *Blocos)
{
    TELA;
    int achou, cont, num, contCelCache;
    achou = cont = num = contCelCache = 0;
    char endereco[TAMST];
    fflush(stdin);
    printf("Digite o Endereco a ser buscado: ");
    scanf("%s", endereco);
    printf("Endereço digitado: %s\n", endereco);
    fflush(stdin);

    achou = buscaemCache((*FilaCache), endereco);

    if (achou == 1)
    {
        printf("\nEndereço foi encontrado em cache\n");
    }
    else
    {
        buscaMP(FilaCache, Blocos, endereco);
    }

    getchar();
    getchar();
}

void escreverMemoria(t_Fila *Fila, t_bloco *Blocos)
{

    TELA;
    char endereco[TAMST];
    char conteudo;
    int disponivelnacache = 0;
    int alterado;
    printf("Tá dentro do Escrever Memória\n");
    printf("\n\nDigite o conteudo que deseja inserir(limitado 1 caracter): ");
    fflush(stdin);
    scanf(" %c", &conteudo);
    fflush(stdin);
    printf("\nDigite o endereco que deseja editar(limitado 11 caracter): ");
    fflush(stdin);
    scanf(" %s", endereco);
    fflush(stdin);
    printf("\nConteudo digitado: %c ", conteudo);
    printf("\nEndereço digitado: %s", endereco);
    disponivelnacache = buscaemCache((*Fila), endereco);

    if (disponivelnacache == 1)
    {
        alterado = alterabloco(Fila, conteudo, endereco);
    }
    else
    {
        int bloco = buscaMP(Fila, Blocos, endereco);
        alterado = alterabloco(Fila, conteudo, endereco);
    }
    alterado ? printf("\nConteudo alterado com sucesso ") : printf("\nConteudo não alterado\n");
    getchar();
    getchar();
}

int main(void)
{
    setlocale(LC_ALL, "");
    t_Fila Fila = CriarFila();

    t_celula MemPrincipal[2048];
    t_bloco Bloco[512];
    // t_quadro MemCache[16];

    // Iniciar memoria Principal
    int contador_bloco = 0;
    for (int j = 0; j < 2048;)
    {
        // inserindo conteudo em quatro células de memoria
        for (int i = 0; i < 4; i++)
        {
            insereConteudo(j, &MemPrincipal[j]);
            if (contador_bloco < 512)
            {
                Bloco[contador_bloco].bloco = contador_bloco;
                Bloco[contador_bloco].celula_bloco[i] =
                    MemPrincipal[j];
            }
            MemPrincipal[j].validar = 0;

            j++;
        }
        // mudando contador do bloco, mas continua inserindo conteudo
        contador_bloco++;
    }

    // Iniciar Cache

    for (int i = 0; i < 16; i++)
    {
        t_quadro MemoCache;
        MemoCache.alterado = 0;
        MemoCache.contador_de_acesso = 0;

        MemoCache.bloco_cache = Bloco[i];

        Fila = QUEUE(MemoCache, &Fila);
    }

    // menu
    int op;

    while (1)
    {
        TELA;
        printf("\nMenu");
        printf("\n\n 1- Ler memoria");
        printf("\n 2- Escrever memoria ");
        printf("\n 3- Estatasticas ");
        printf("\n 4- Mostrar memoria Principal");
        printf("\n 5- Mostrar memoria Cache");
        printf("\n 0. Sair");
        printf("\n\n Entre a sua opcao: ");
        scanf("%d", &op);
        fflush(stdin);
        switch (op)
        {
        case 0:
            exit(0);
        case 1:
            lermemoria(&Fila, Bloco);
            break;
        case 2:
            escreverMemoria(&Fila, Bloco);
            break;
        case 3:
            break;
        case 4:
            mostramemoriaPricipal(MemPrincipal);
            break;
        case 5:
            mostramemoriaCache(Fila);
            break;
        default:
            printf("\nOpcao incorreta");
            getchar();
            getchar();
            break;
        }
    }
    getchar();
    return 0;
}