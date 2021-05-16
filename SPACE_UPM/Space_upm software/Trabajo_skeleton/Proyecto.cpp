#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "SerialClass/SerialClass.h" // Biblioteca para acceder al puerto serie
int main()
{
	Serial* Arduino;
	char puerto[] = "COM3", ch = 0, inp;
	int bytesRecibidos;
	char BufferEntrada[200];
	Arduino = new Serial((char*)puerto); // Crea conexión lógica con Arduino

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
				Arduino->ReadData(&inp, sizeof(char));
				printf("%c\n", inp);
				if (ch == inp)
					printf("Misma señal\n");
				else
					printf("Señal distinta\n");
				printf("--------------------------\n");
				break;

		default:
			printf("Input incorrecto\n");
			break;
		}

		bytesRecibidos = Arduino->ReadData(BufferEntrada, sizeof(char) * 180);

		if (bytesRecibidos != -1) // Lectura de mensaje desde el puerto
		{
			BufferEntrada[bytesRecibidos] = '\0';
			printf("Recibidos %d bytes: %s\n", bytesRecibidos, BufferEntrada);
		}
		else {
			printf("No se ha recibido nada\n");
		}
		Sleep(111);
	}
}