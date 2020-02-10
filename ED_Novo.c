#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define TOTAL_BUCKETS 60000
#define TOTAL_CHARS_BY_WORD 38
#define TOTAL_CHARS_BY_LINE 128

long long int TotalPalavras = 0;
long long int PalavrasErro = 0;
//unsigned int tempo;
unsigned char ListaErro[10000][TOTAL_CHARS_BY_WORD];
int Pos[10000][2];


struct Node
{
    unsigned char word[TOTAL_CHARS_BY_WORD];
    struct Node *next;
};


void Prepend(struct Node **n, unsigned char k[TOTAL_CHARS_BY_WORD])
{
    if (!*(n))
    {
        struct Node *new_n = (struct Node*) malloc(sizeof(struct Node));
        new_n->next = NULL;
        strcpy(new_n->word, k);
        *n = new_n;
    }
    else
    {
        struct Node* new_n = (struct Node*) malloc(sizeof(struct Node));
        new_n->next = *n;
        strcpy(new_n->word, k);
        *n = new_n;
    }
}


int Search(struct Node *n, unsigned char s[TOTAL_CHARS_BY_WORD])
{
    if (strcmp(n->word, s) == 0)
    {
        return 1;
    }
    else
    {
        if (n->next == NULL)
            return 0;
        else
            return Search(n->next, s);
    }
}


int ConvertHash(unsigned char c)
{
    if (c >= 97 && c <= 122)
    {
        return c - 97;
    }
    else if (c >= 65 && c <= 90)
    {
        return c - 65;
    }
    else if (c == 39)
        return 27;
    else if (c == 45)
        return 26;
    else
        return 0;
    /*{
        printf("\nError! Invalid character: %c.\n", c);
        exit(1);
    }*/
}


int hash(unsigned char s[TOTAL_CHARS_BY_WORD])
{
    int i = 0;
    float sum = 0;
    while (1)
    {
        if(s[i] == '\0' || s[i] == '\n')
            break;
        sum = sum + (i+1)*ConvertHash(s[i]);
        i++;
    }
    sum = TOTAL_BUCKETS * fmod(0.6180*sum, 1);
    return sum;
}


int Convert(unsigned char c)
{
	//if ((c == 128) || (c == 135))
	//	return 99; //ç
	//else if ((c >= 131 && c <= 134) || (c == 142) || (c == 143) || (c == 160) || (c >= 181 && c <= 183) || (c == 198) || (c == 199))
	//	return 97; //a
	//else if ((c == 130) || (c >= 136 && c <= 138) || (c == 144) || (c >= 210 && c <= 212))
	//	return 101; //e
	//else if ((c >= 139 && c <= 141) || (c == 161) || (c >= 213 && c <= 216) || (c == 122))
	//	return 105; //i
	//else if ((c >= 147 && c <= 149) || (c == 153) || (c == 162) || (c == 224) || (c >= 226 && c <= 229))
	//	return 111; //o
	//else if ((c == 129) || (c == 150) || (c == 151) || (c == 154) || (c == 163) || (c >= 233 && c <= 235))
	//	return 117; //u
	if (c >= 65 && c <= 90)
		return c + 32;
	else return c;
}


void ConvertWord(unsigned char w[TOTAL_CHARS_BY_WORD])
{
	int i;
	for (i = 0; i < TOTAL_CHARS_BY_WORD; i++)
	{
		if (w[i] == '\n' || w[i] == '\0')
			break;
		w[i] = Convert(w[i]);
	}
}
/*int hash(char *str)
{
    int hash = 50;
    int c;

    printf("Passo 1 ok!\n");
    int p = 0;
    while (c = *str++)
    {
        printf("Passo 2[%d] ok!\n", p);
        hash = ((hash << 5) + hash) + c;
        printf("Passo 3[%d] ok!\n", p);
        p++;
    }

    printf("Passo 4 ok!\n");
    hash = TOTAL_BUCKETS * fmod(0.6180*hash, 1);
    printf("Passo 5 ok!\n");

    return hash;
}*/


struct Node* table[TOTAL_BUCKETS];

int main() {

    clock_t begin = clock();

    int i;

    for (i = 0; i < TOTAL_BUCKETS; i++)
    {
        table[i] = NULL;
    }

    int index;
    FILE *file = fopen ("C:\\Users\\Renan Goes\\Documents\\Engenharia da Computação\\Trabalho ED\\Trabalho Novo\\ascii_noaccent_noduplicates_FIXED_v2.txt", "r");
	FILE *input_file = fopen("C:\\Users\\Renan Goes\\Documents\\Engenharia da Computação\\Trabalho ED\\Trabalho Novo\\ASCII_text.txt", "r");
	FILE *output_file = fopen("C:\\Users\\Renan Goes\\Documents\\Engenharia da Computação\\Trabalho ED\\Trabalho Novo\\Relatorio.txt", "w");
    unsigned char palavra[TOTAL_CHARS_BY_LINE];
    unsigned char line[TOTAL_CHARS_BY_LINE];

    for(i = 0; i < TOTAL_CHARS_BY_LINE; i++)
            palavra[i] = '\0';
    for(i = 0; i < TOTAL_CHARS_BY_LINE; i++)
        line[i] = '\0';
	//preenchendo Dicionário
    if (file != NULL)
    {
        while (fgets(line, sizeof line, file) != NULL)
        {
            strcpy(palavra, line);
			palavra[strlen(palavra) - 1] = '\0';
			ConvertWord(palavra);
            index = hash(palavra);
			//printf("array ----> %s\nHASH: %d\n", palavra, index);
            Prepend(&(table[index]), palavra);
        }
        fclose(file);
    }
    else
    {
        perror("C:\\Users\\Matheus Gama\\Desktop\\Matheus\\Programação\\Trabalho de ED\\ascii_noaccent_noduplicates_FIXED_v2.txt");
    }

	for (i = 0; i < TOTAL_CHARS_BY_LINE; i++)
		line[i] = '\0';

	//lendo arquivo de texto e comparando
	if (input_file != NULL)
	{
		int linha = 0, coluna;
        i = 0;
        int j = 0;
        coluna = 0;
        Pos[0][0] = 0;

		while (fgets(line, sizeof(line), input_file) != NULL)
		{
			linha++;
			i = 0;
			j = 0;

			while(line[i] != '\n'){
				if ((line[i] >= 32 && line[i] <= 38) || (line[i] >= 40 && line[i] <= 44) || (line[i] >= 46 && line[i] <= 47))
				{
					palavra[j] = '\0';
					if (strlen(palavra) > 0) {
						coluna++;
						ConvertWord(palavra);
						if (!Search(table[hash(palavra)], palavra)) {
							strcpy(ListaErro[PalavrasErro], palavra);
							Pos[PalavrasErro][0] = linha;
							Pos[PalavrasErro][1] = coluna;
							PalavrasErro++;
						}
						TotalPalavras++;
					}
					j = 0;
					i++;
				}
				else
				{
					palavra[j] = line[i];
					j++;
					i++;
				}
			}

		}
		fclose(input_file);
	}
	else
	{
		perror("C:\\Users\\Matheus Gama\\Desktop\\Matheus\\Programação\\Trabalho de ED\\file.txt");
	}

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;


	//relatório
	fprintf(output_file,"Número total de palavras do texto: ");
	fprintf(output_file, "%lld", TotalPalavras);
	fprintf(output_file, "\nTempo total da verificação: ");
	fprintf(output_file, "%.2fms", time_spent*1000);
	fprintf(output_file, "\nNúmero de palavras que falharam no spell check: ");
	fprintf(output_file, "%lld", PalavrasErro);
	fprintf(output_file, "\nLista de palavras que falharam no spell check:\n\n");
	fprintf(output_file, "Num. Ocorrencia Palavra: Linha, Coluna\n");
	fprintf(output_file, "----------------------------------------\n");
	i = 0;
	while (Pos[i][0] != 0)
	{
		fprintf(output_file, "%d - ",i+1);
		fprintf(output_file, "%s", ListaErro[i]);
		fprintf(output_file, " : %d",Pos[i][0]);
		fprintf(output_file, ", %d\n", Pos[i][1]);
		i++;
	}

	fclose(output_file);
    return 0;
}
