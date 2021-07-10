#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "SerialClass/SerialClass.h" // Biblioteca para acceder al puerto serie
#define x_size 50
#define y_size 50
#define Tamano_com 200

typedef struct COORDENADAS {
	int indexx = 0, indexy = 0;
	char valor = '0';
}COORDENADAS;

int main()
{
	COORDENADAS coordenada;
	Serial* Arduino;
	char puerto[] = "COM3";
	int bytesRecibidos;
	char BufferEntrada[Tamano_com];
	char Salida[] = "Recibido \n";
	Arduino = new Serial((char*)puerto); // Crea conexión lógica con Arduino

	int i, j;
	char matriz[y_size][x_size]; //declaración de matriz, pudiendo cambiar su tamaño (PENDIENTE DE IMPLEMENTACIÓN EN ARDUINO)
	char mat2[y_size][x_size];

	FILE* ar;
	errno_t err;
	err = fopen_s(&ar, "plano.txt", "w+");
	if ((err == 0)&&(ar!=NULL)) {
		
		for (i = 0; i < y_size; i++) { //rellenamos matriz con 0 (vacío)
			for (j = 0; j < x_size; j++) {
				matriz[i][j] = '0';
				mat2[i][j] = '0';
			}
		}


		while (Arduino->IsConnected())
		{

			bytesRecibidos = Arduino->ReadData(BufferEntrada, sizeof(char) * Tamano_com);

			if (bytesRecibidos != -1) // Lectura de mensaje desde el puerto
			{
				BufferEntrada[bytesRecibidos] = '\0';
				printf("Recibidos %d bytes: %s\n", bytesRecibidos, BufferEntrada);
				coordenada.valor = BufferEntrada[0];
				coordenada.indexx = BufferEntrada[1];
				coordenada.indexy = BufferEntrada[2];
				matriz[coordenada.indexy][coordenada.indexx] = coordenada.valor;
				printf("%c en %d %d\n", coordenada.valor, coordenada.indexx, coordenada.indexy);

				if (matriz[coordenada.indexy][coordenada.indexx] != mat2[coordenada.indexy][coordenada.indexx]) {
					for (i = 0; i < y_size; i++) { //ponemos la matriz en el archivo
						for (j = 0; j < x_size; j++) {
							fprintf_s(ar, "%c", matriz[i][j]);
						}
						fprintf_s(ar, "\n");
					}
					rewind(ar);
					mat2[coordenada.indexy][coordenada.indexx] = matriz[coordenada.indexy][coordenada.indexx];
				}
			}
			else {
				printf("No se ha recibido nada\n");
			}
			Sleep(2000);
		}

		fclose(ar);
		if (fclose(ar) == NULL) 
			printf("Archivo cerrado con exito");
		else
			printf("Error al cerrar el archivo");
	}
	else
		printf("Archivo no abierto correctamente");
}