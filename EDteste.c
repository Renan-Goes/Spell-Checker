#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>#include <fstream>
#define TOTAL_BUCKETS 20
#define TOTAL_WORDS_BY_LINE 128


struct Node
{
    unsigned char word[TOTAL_WORDS_BY_LINE];
    struct Node *next;
};

void Prepend(struct Node **n, unsigned char k[TOTAL_WORDS_BY_LINE])
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

int TotalColision(struct Node *n, int k)
{
    struct Node *new_n = (struct Node*) malloc(sizeof(struct Node));
    new_n = n;
    if (new_n == NULL)
        return k;
    else if (new_n->next == NULL)
        return k + 1;
    else
        return TotalColision(new_n->next, k + 1);
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


int hash(unsigned char s[TOTAL_WORDS_BY_LINE])
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


void ConvertWord(unsigned char w[TOTAL_WORDS_BY_LINE])
{
	int i;
	for (i = 0; i < TOTAL_WORDS_BY_LINE; i++)
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
    int i;

    for (i = 0; i < TOTAL_BUCKETS; i++)
    {
        table[i] = NULL;
    }

    int index;
    FILE *file = fopen ("C:\\Users\\Renan Goes\\Documents\\Engenharia da Computação\\Trabalho ED\\Trabalho Novo\\ascii_noaccent_noduplicates_FIXED_v2.txt", "r");
	FILE *output_file = fopen("C:\\Users\\Renan Goes\\Documents\\Engenharia da Computação\\Trabalho ED\\Trabalho Novo\\Relatorio.csv", "a");
    unsigned char palavra[TOTAL_WORDS_BY_LINE];
    unsigned char line[TOTAL_WORDS_BY_LINE];

    for(i = 0; i < TOTAL_WORDS_BY_LINE; i++)
            palavra[i] = '\0';
    for(i = 0; i < TOTAL_WORDS_BY_LINE; i++)
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

    int total = 0, totalCheios = 0;
    int mediaTotal = 0;
    int mediaCheios = 0;
    int variancia = 0;
    int varianciaCheios = 0;
    int colisoes = 0;

    FILE *fs;
    fs = fopen("C:\\Users\\Renan Goes\\Documents\\Engenharia da Computação\\Trabalho ED\\Trabalho Novo\\Colisões.csv", "a");
    for (i = 0; i < TOTAL_BUCKETS; i++)
    {
        total++;
        colisoes = TotalColision(table[i], 0);
        mediaTotal += colisoes;
        if (colisoes > 0)
        {
            mediaCheios += colisoes;
            totalCheios++;
        }
    }
    mediaTotal = mediaTotal/total;
    mediaCheios = mediaCheios/totalCheios;
    for (i = 0; i < TOTAL_BUCKETS; i++)
    {
        colisoes = TotalColision(table[i], 0);
        variancia += colisoes*colisoes - mediaTotal*mediaTotal;
        varianciaCheios += colisoes*colisoes - mediaCheios*mediaCheios;
    }
    variancia = variancia/total;
    varianciaCheios = varianciaCheios/totalCheios;
    fprintf(fs, "Média de todos os buckets não vazios: %d;Média de todos os buckets: %d;Total de buckets com colisões: %d\n", mediaCheios, mediaTotal, totalCheios);

    fclose(fs);
}
