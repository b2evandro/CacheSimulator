#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void mostramemoriaCache(t_quadro MemCache[])
{
    TELA;
    printf("\nMostrando MemCache: \n");
    printf("Alterado");
    printf("\t Acessos");
    printf("\tConteudo\t");
    printf("\tEndereco de inicio do Bloco");
    for (int mostratodoCache = 0; mostratodoCache < 64;)
    {
        for (int i = 0; i < 16; i++)
        {
            printf("\n");
            printf("%d ", MemCache[i].alterado);
            printf("\t\t\t\t%d \t", MemCache[i].contador_de_acesso);
            for (int j = 0; j < 4; j++)
            {

                printf("\t %c", MemCache[i].bloco_cache.celula_bloco[j].conteudo);

                mostratodoCache++;
            }
            printf("\t");
            for (int h = 0; h < TAMST; h++)
            {
                printf("%c", MemCache[i].bloco_cache.celula_bloco[0].endereco[h]);
            }
        }
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

int FilaVazia(struct ESTFILA F)
{
    if (F.INI == -1 && F.FIM == -1)
        return 1;
    else
        return 0;
}

t_Fila QUEUE(t_quadro linha_do_quadro, t_Fila F)
{
    if (FilaVazia(F))
    {
        F.INI++;
        F.FIM++;
    }
    else
    {
        F.FIM++;
        if (F.FIM == TAM && F.INI != 0)
            F.FIM = 0;
    }
    F.linha_quadro[F.FIM] = linha_do_quadro;
    return F;
}

t_quadro
DEQUEUE(t_Fila F)
{
    t_quadro Valor;
    Valor = F.linha_quadro[F.INI];
    if (F.INI == F.FIM)
    {
        F.INI = -1;
        F.FIM = -1;
    }
    else
    {
        F.INI++;
        if (F.INI == TAM && F.FIM >= 0)
            F.INI = 0;
    }
    return Valor;
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
int  buscaemCache(t_Fila FilaCache, char endereco []){
	 int achou, cont,  contCelCache;
    achou = cont  = contCelCache = 0;
	 while ((contCelCache < 64) && (achou == 0))
    {
        for (int contFila = 0; contFila < TAM; contFila++)
        {
            for (int contBloco = 0; contBloco < 4; contBloco++)
            {
                if (stringCompa(endereco, (FilaCache).linha_quadro[contFila].bloco_cache.celula_bloco[contBloco].endereco, TAMST) == 1)
                {
                    achou = 1;
												printf("O conteudo do endereço é: %c \n",  (FilaCache).linha_quadro[contFila].bloco_cache.celula_bloco[contBloco].conteudo);
                }
                contCelCache++;
            }
        }
    }
		return achou;
}

int bucaemMP(t_celula Celulas[], char endereco []){

	 int achou, cont;
    achou = cont = 0;
	 	while ((cont < 2048) && (achou != 1))
        {
            achou = stringCompa(endereco, Celulas[cont].endereco, TAMST);
						if(achou ==1){
							printf("O conteudo do endereço é: %c \n", Celulas[cont].conteudo);
						}
            cont++;
        }
	
		return achou;
}

void lermemoria(t_Fila FilaCache, t_celula Celulas[])
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

 		achou= buscaemCache(FilaCache, endereco);

    if (achou == 1)
    {
        printf("\nEndereço foi encontrado em cache\n");
			
    }
    else
    {
			achou = bucaemMP(Celulas, endereco);
       
        if (achou == 1)
        {
            printf("\nEndereço não foi encontrado em cache, mas foi encontrdo na memória principal.\n");
        }
        else
        {
            printf("\nEndereço não foi encontrado em nenhum lugar, favor conferir o endereço digitado.\n");
        }
    }

    getchar();
    getchar();
}

void escreverMemoria(t_Fila Fila, t_quadro *MemoCache, t_bloco *Blocos ){
		TELA;
		char conteudo,endereco[TAMST];
		int disponivelnacache;
		printf("Tá dentro do Escrever Memória\n");
		printf("\n\nDigite o conteudo que deseja inserir(limitado 1 caracter): ");
		fflush(stdin);
		scanf(" %c", &conteudo);
		printf("Digite o endereco que deseja editar(limitado 11 caracter): ");
		fflush(stdin);
  	scanf("%s", endereco);
		printf("\nConteudo inserido: %c", conteudo);
		printf("\nEndereço digitado: %s", endereco);
		disponivelnacache= buscaemCache(Fila, endereco);
		
		if(disponivelnacache ==1 ){
			printf("\nDá para editar em cache");
		} else {
			int bloco;
			int achouBloco=0;
			 int  contBloco=0;
				while(achouBloco==0 && contBloco<512){
					for(int contCelulas=0; contCelulas < 4 ; contCelulas++){
						if ((stringCompa(endereco, Blocos[contBloco].celula_bloco[contCelulas].endereco, TAMST)) == 1)
						{
							achouBloco=1;

						}
					}
 					contBloco++;
				}
		}

		getchar();
		getchar();
}

int main(void)
{

    t_Fila Fila = CriarFila();

    t_celula MemPrincipal[2048];
    t_quadro MemCache[16];
    t_bloco Bloco[512];

    // Iniciar memoria Principal
    int contador_bloco = 0;
    for (int j = 0; j < 2048;)
    {
        // inserindo conteudo em quatro células de memoria
        for (int i = 0; i < 4; i++)
        {
            insereConteudo(j, &MemPrincipal[j]);

            Bloco[contador_bloco].bloco = contador_bloco;
            Bloco[contador_bloco].celula_bloco[i] = MemPrincipal[j];
            MemPrincipal[j].validar = 0;

            j++;
        }
        // mudando contador do bloco, mas continua inserindo conteudo
        contador_bloco++;
    }

    // Iniciar Cache

    for (int i = 0; i < 16; i++)
    {
        MemCache[i].alterado = 0;
        MemCache[i].contador_de_acesso = 0;

        for (int quadro = 0; quadro < 4; quadro++)
        {
            MemCache[i].bloco_cache =
                Bloco[i];
        }
        Fila = QUEUE(MemCache[i], Fila);
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
            lermemoria(Fila,  MemPrincipal);
            break;
        case 2:
						escreverMemoria(Fila, MemCache, Bloco);
            break;
        case 3:
            break;
        case 4:
            mostramemoriaPricipal(MemPrincipal);
            break;
        case 5:
            mostramemoriaCache(MemCache);
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