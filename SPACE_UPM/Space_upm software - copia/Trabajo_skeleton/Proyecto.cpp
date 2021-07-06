#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "SerialClass/SerialClass.h" // Biblioteca para acceder al puerto serie
#define x_size 50
#define y_size 50
#define Tamano_com 3
int main()
{
	Serial* Arduino;
	char puerto[] = "COM8", ch = 0, inp;
	int bytesRecibidos;
	char BufferEntrada[Tamano_com];
	Arduino = new Serial((char*)puerto); // Crea conexión lógica con Arduino

	int i, j;
	char matriz[y_size][x_size]; //declaración de matriz, pudiendo cambiar su tamaño (PENDIENTE DE IMPLEMENTACIÓN EN ARDUINO)

	for (i = 0; i < y_size; i++) { //rellenamos matriz con 0 (vacío)
		for (j = 0; j < x_size; j++) {
			matriz[i][j] = '0';
		}
	}

	while (Arduino->IsConnected())
	{

		bytesRecibidos = Arduino->ReadData(BufferEntrada, sizeof(char) * Tamano_com);

		if (bytesRecibidos != -1) // Lectura de mensaje desde el puerto
		{
			BufferEntrada[bytesRecibidos-1] = '\0';
			printf("Recibidos %d bytes: %s\n", bytesRecibidos, BufferEntrada);
		}
		else {
			printf("No se ha recibido nada\n");
		}
		Sleep(2000);
	}
}