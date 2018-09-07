
#include <stdio.h>
#include <string.h>

void versionKernel();
void filtrarCadena(char* directorio, char* busqueda, char* filtrada);
void cpuInfo();
void infoMemoria();

int main(int argc, char const *argv[])
{
	
	cpuInfo();
	versionKernel();
	infoMemoria();

	return 0;
}

void versionKernel(){
	FILE *archivo;
	archivo = fopen("/proc/version","r");

	if (archivo == NULL){
		printf("\nError de apertura del archivo");
		return;
	}
	char str1[20],str2[20],str3[20];
	printf("\nVersion del kernel: ");

	fscanf(archivo,"%s %s %s", str1,str2,str3);
printf("%s %s %s \n",str1,str2,str3 );
} 

/**
*Filtra una linea del directorio correspondiente
*@param  *directorio archivo del proc que se necesita leer
*@param *busqueda palabra o cadena que actua de filtro de busqueda
*@param *filtrada direccion de memoria donde se guarda la cadena resultado del filtro 
*/
void filtrarCadena(char* directorio, char* busqueda, char* filtrada){
	FILE *archivo;
	char *lectura=NULL;
	char buffer[250];
	archivo = fopen(directorio, "r");

	if (archivo == NULL){
		printf("\nError de apertura del archivo");
		return;
	}

	while (feof(archivo)==0){
		fgets(buffer,250,archivo);
		lectura=strstr(buffer,busqueda);//compara la cadena del archivo		
										//que toma fgtes y nuestro parametro de busqueda
		if(lectura!=NULL){				//si hay coincidencia, lo guarda
			strcpy(filtrada,lectura);	//copia lo obtenido en la cadena que
										//le manda la funcion como parametro
			break;
		}
	}
	fclose(archivo);
	return;
}

void cpuInfo(){
	char linea[250]; //variable donde se almacenara lo que filtre
					//la funcion filtrarCadena()
	char str1[30], str2[150];

	filtrarCadena("/proc/cpuinfo","vendor_id",linea);
	sscanf(linea,"vendor_id : %s",str1);
	printf("\nTipo de cpu: %s\n",str1 );

	filtrarCadena("/proc/cpuinfo","model name",linea);
	sscanf(linea,"model name : %[^\n]c",str2); //%[^\n]c guarda en str2 una cadena con espacios
											//desde la primera palabra despues de model name :
											//hasta que termina el renglon
	printf("Modelo de cpu: %s\n",str2 );
	return;
}

void infoMemoria(){
	char linea[250];
	char str[2];
	int memTotal, memLibre;

	filtrarCadena("/proc/meminfo","MemTotal", linea);
	sscanf(linea, "MemTotal: %d %s",&memTotal,str);
	printf("\nMemoria Total: %d %s\n",memTotal,str );

	filtrarCadena("/proc/meminfo","MemFree", linea);
	sscanf(linea, "MemFree: %d %s",&memLibre,str);
	printf("Memoria Libre: %d %s\n",memLibre,str );
	return;
}