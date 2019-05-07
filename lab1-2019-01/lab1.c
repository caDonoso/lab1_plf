#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A diferencia de existInElementos, esta funcion valida de que la palabra que
// se está almacenando por lo menos vaya en buen camino en la búsqueda. 
// Valida de que pueda existir una posible palabra que pueda encontrar con el proximo caracter.
int isValidWord(char* palabra, char** elementos){
	int i, j;
	int contCharactersCorrects = 0;
	int contValidWords = 0;
	
	for (i = 0; i < 54; i++)
	{
		if(elementos[i][0] == palabra[0]){
			if(strlen(elementos[i]) >= strlen(palabra)){
				printf("Comparacion entre => palabra: %s y elementos[%d]: %s\n", palabra, i,elementos[i]);
				contCharactersCorrects = 0;
				for (j = 0; j < strlen(palabra) ; j++)
				{
					if(elementos[i][j] == palabra[j]){
						printf("el caracter en la posicion %d es correcto\n", j);
						contCharactersCorrects++;
					}
				}
				if(contCharactersCorrects == strlen(palabra)){
					contValidWords++;
				}
			}
		}
	}
	if(contValidWords == 0){
		// No existe una posible palabra que pueda encontrar con el proximo caracter
		return 0;
	}
	else{ 
		//Existe una posible palabra que pueda encontrar con el proximo caracter
		return 1;
	}
}

int existInElementos(char* palabra, char** elementos){
	int i, j, cont;
	for (i = 0; i < 54; i++)
	{
		if(elementos[i][0] == palabra[0]){
			if(strlen(elementos[i]) == strlen(palabra)){
				cont = 0;
				for (j = 0; j < strlen(elementos[i]) ; j++)
				{
					if(elementos[i][j] == palabra[j]){
						cont++;
					}
				}
				if(cont == strlen(elementos[i])){
					printf("Encontré la palabra %s\n", palabra);
					printf("palabra: %s y elementos[%d]: %s son iguales\n", palabra, i,elementos[i]);
					return 1; //Encontró la palabra
				}
			}
		}
	}
	return 0; //No encontró la palabra
}

int main(int argc, char** argv){
	int i;

	// Validación de parametros
	if(argc == 1){
		printf("Error: Faltan par%cmetros.\n",160);
		printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
		exit(1);
	}
	else if(argc == 2){
		printf("Error: Falta par%cmetro.\n",160);
		printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
		exit(1);
	}
	else if(argc > 3){
		printf("Error: Demasiados par%cmetros.\n",160);
		printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
		exit(1);
	}
	char* elementos[54] = {"main", "(", ")", "{", "}", ",", ";", "auto", "extern", "register", 
	"static", "*", "=", "break", "continue", "default", ":", "do", "while", "for", "goto", 
	"if", "else", "return", "&", "-", "~", "|", "sizeof", "short", "int", "unsigned", "long",
	"float", "char", "double", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!", "?", "+", 
	"/", "%", "^", "<<", ">>", "++", "--"};

	
	FILE *archivo_entrada;
	// Apertura de archivo de entrada
	archivo_entrada = fopen(argv[1], "r"); 
	if(archivo_entrada != NULL){
		FILE *archivo_salida;
		// Comprobacion de existencia de archivo de salida
		archivo_salida = fopen(argv[2], "r");
		if(archivo_salida != NULL){
			printf("Error: El archivo de salida ya existe.\n");
			exit(1);
		}
		else{
			// Se crea archivo de salida
			archivo_salida = fopen(argv[2], "w");

			// Se lee caracter por caracter
			char palabra[40] = "";
			char espacio = ' ';
			char caracter;
			int index = 0;
			while (feof(archivo_entrada) == 0){
				caracter = fgetc(archivo_entrada);
				printf("caracter obtenido: %c\n", caracter);
				if(caracter == espacio){
					printf("Habia un espacio, se ignora\n");
					caracter = fgetc(archivo_entrada);
				}
				palabra[index] = caracter; //Acumula los caracteres
				index++;
				printf("largo de la palabra '%s': %d\n", palabra, strlen(palabra));

				if(isValidWord(palabra, elementos)){
					printf("vamos por buen camino\n");
					if(existInElementos(palabra, elementos)){
						printf("Se escribe '%s' en el archivo de salida.\n", palabra);
						fputs( palabra, archivo_salida);
						fputs( "\n", archivo_salida);

						printf("Se resetea el coso para almacenar caracteres\n");
						index = 0;
						memset(&palabra, 0, sizeof(palabra)); 
						palabra[index] = caracter;
					}
				}
				else{
					printf("no va a existir ninguna palabra por este camino\n");
					index = 0;
					memset(&palabra, 0, sizeof(palabra)); 
					palabra[index] = caracter;
				}
			}
			printf("Se lee el archivo de entrada.\n");
		}
	}
	else{
		printf("Error: El archivo de entrada no existe.\n");
		exit(1);
	}
	fclose(archivo_entrada);
	
	return 0;
}
