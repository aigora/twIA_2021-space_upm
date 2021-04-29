#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "SerialClass/SerialClass.h" // Biblioteca para acceder al puerto serie
int main()
{
	Serial* Arduino;
	char puerto[] = "COM3";
	int bytesRecibidos;
	char BufferEntrada[300];
Arduino = new Serial((char*)puerto); // Crea conexión lógica con Arduino
while (Arduino->IsConnected())
{
	

	bytesRecibidos = Arduino->ReadData(BufferEntrada, sizeof(char) * 180);

	if (bytesRecibidos != -1) // Lectura de mensaje desde el puerto
	{
		BufferEntrada[bytesRecibidos - 1] = '\0';
		printf("Recibidos %d bytes: %s\n", bytesRecibidos, BufferEntrada);
	}
	else
		printf("No se ha recibido nada\n");
	Sleep(150);
}
}