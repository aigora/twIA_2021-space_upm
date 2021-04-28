#include <stdio.h>
#include <string.h>
#include "SerialClass.h"
#include "SerialClass.cpp"
using namespace std;

int main() {
	char puerto[] = "COM5";//así podemos cambiar el puerto con facilidad
	char Salida[200], Entrada[200], final[200];//String que se envía, que se recive, y la que usamos para printear
	int bytes;//así podemos contar el número de bytes y "cerrar" la cadena que recibimos

	Serial* Arduino = new Serial((char*)puerto);//Configura el puerto
	if (Arduino->IsConnected())
		printf("Arduino conectado");//Nos avisa si está conectada

	while(Arduino->IsConnected()){
		printf("\nEscriba mensaje a enviar:");
		gets_s(Salida);
		Arduino->WriteData(Salida, strlen(Salida));//enviamos los datos a Arduino
		Entrada[0] = '\0';
		bytes = Arduino->ReadData(Entrada, sizeof(char) * 199);
		if (bytes != -1)
		{
			Entrada[bytes] = '\0';//"cerramos" la cadena
			strcat_s(final, Entrada);//copiamos los datos a una cadena
			printf("%s\n", Entrada);
			Sleep(1000);
		}
	}
}
