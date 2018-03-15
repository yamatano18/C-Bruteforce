#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* tablica dostepnych znakow */
static const char alphabet[] = "abcdefghijklmnopqrstuvwxyzBCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

/* deklaracja zmiennych */
char *password;
char *brute_pass = "";
int password_length;
int max_length;
int tries_number = 0;
int alphabet_length;
int i;
int j;
char *curr_pass;


/* wyswietlenie pomocy */
void warning()
{
	printf("W celu uruchomienia programu, musisz podac haslo jako pierwszy argument wywolania, np:\n");
	printf("./a.out [haslo] [max_dlugosc_hasla]\n");
	printf("Program powinien wyswietlic po ilu probach udalo mu sie odgadnac haslo i jakie ono jest.\n");
}


void generate_password(char* str, int index, int max)
{
	/* j to wektor i zawsze bierzemy nastepny */
	for (int j=0; j<alphabet_length; j++)
        {
		printf("jxxx = %d\n", j);
                str[index] = alphabet[j];
		if (index == max-1)
                {
			tries_number++;	

#ifdef DEBUG
			printf("%s\n", str);
#endif

			if (strcmp(str, password) == 0)
			{
				printf("Haslo zostalo zlamane po %d probach!\n", tries_number);
				printf("Szukane haslo: %s\n", str);
				exit(0);
			}
		}
                else
                {
                        generate_password(str, index+1, max);
                }
        }
}

/* funkcja lamiaca haslo */
void bruteforce(int max_len)
{
	curr_pass = malloc(max_len *sizeof(char));
	for (i=1; i<=max_len; i++)
	{
		memset(curr_pass, 0, max_len+1);
		generate_password(curr_pass, 0, i);
	}
	printf("Nie znaleziono hasla!\n");
}


int main (int argc, char **argv)
{

#ifdef DEBUG
	printf("\nLiczba argumentow %d\n", argc);
#endif

	if (argc < 3)
	{
		warning();
		return -2;
	}

	if (argc == 3)
	{
		printf("\n===> Program glowny <===\n\n");
		password = argv[1];
		max_length = atoi(argv[2]);
		alphabet_length = strlen(alphabet);

#ifdef DEBUG
		printf("Haslo do zlamania: %s\n", password);
		password_length = strlen(password);
		printf("Dlugosc hasla: %d\n", password_length);
		printf("\nAlphabet:\n");
		printf("[%s] = %d znaki\n\n", alphabet, alphabet_length);		
#endif
		
		bruteforce(max_length);
	}
}
