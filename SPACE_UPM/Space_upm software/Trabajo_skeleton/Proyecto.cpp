#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "SerialClass/SerialClass.h" // Biblioteca para acceder al puerto serie
int main()
{
	Serial* Arduino;
	char puerto[] = "COM4", ch = 0, inp;
	int bytesRecibidos;
	char BufferEntrada[50];
	Arduino = new Serial((char*)puerto); // Crea conexi�n l�gica con Arduino

	while (Arduino->IsConnected())
	{
		ch = _getch();
		switch (ch)
		{
			case 'w':
			case 'W':
			case 'a':
			case 'A':
			case 's':
			case 'S':
			case 'd':
			case 'D':
				Arduino->WriteData(&ch, sizeof(char));
				printf("%c\n", ch);
				Sleep(100);
				break;
		default:
			printf("Input incorrecto\n");
			break;
		}

		bytesRecibidos = Arduino->ReadData(BufferEntrada, sizeof(char) * 50);

		if (bytesRecibidos != -1) // Lectura de mensaje desde el puerto
		{
			BufferEntrada[bytesRecibidos-1] = '\0';
			printf("Recibidos %d bytes: %s\n", bytesRecibidos, BufferEntrada);
		}
		else {
			printf("No se ha recibido nada\n");
		}
		Sleep(10);
	}
}