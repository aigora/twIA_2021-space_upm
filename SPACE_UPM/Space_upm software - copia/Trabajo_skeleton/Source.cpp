#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "SerialClass/SerialClass.h" // Biblioteca para acceder al puerto serie
int main()
{
	Serial* Arduino;
	char puerto[] = "COM3"; // Puerto serie en el que está conectado Arduino
	char BufferSalida[200];
	char BufferEntrada[200];
	int bytesRecibidos;
	int contador = 0; // Contador para detectar pérdida de tramas
	char secuencia[4]; // Versión cadena del contador anterior
	Arduino = new Serial((char*)puerto); // Crea conexión lógica con Arduino
	while (Arduino->IsConnected())
	{
		printf("Arduino conectado\n");
		sprintf_s(secuencia, "%d", contador);
		strcpy_s(BufferSalida, "Este es el mensaje enviado por el puerto serie ");
		strcat_s(BufferSalida, secuencia);
		printf("Enviando %s\n", BufferSalida);
		Arduino->WriteData(BufferSalida, strlen(BufferSalida)); // Envía mensaje
		contador++;
		if (contador == 1)
			Sleep(2000); // Tiempos de espera para la primera trama (evita pérdidas)
		else
			Sleep(2000); // Tiempo de espera para el resto de las tramas
		bytesRecibidos = Arduino->ReadData(BufferEntrada, sizeof(char) * 199);
		if (bytesRecibidos != -1) // Lectura de mensaje desde el puerto
		{
			BufferEntrada[bytesRecibidos - 1] = '\0';
			printf("Recibidos %d bytes: %s\n", bytesRecibidos, BufferEntrada);
		}
		else
			printf("No se ha recibido nada\n");
		Sleep(1000);
	}
}