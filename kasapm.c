
#include <stdio.h>
#include <string.h>

void versionKernel();
void filtrarCadena(char* directorio, char* busqueda, char* filtrada);
void cpuInfo();
void infoMemoria();
void tiempo();
void print_time (char* label, long time);
void tiempoCPU();
void pedidosLE();
void cambiosContexto();
void procesosCreados();
void cantidadFicheros();

int main(int argc, char const *argv[])
{
	
	cpuInfo();
	versionKernel();
	infoMemoria();
	tiempo();
	tiempoCPU();
	pedidosLE();
	cambiosContexto();
	procesosCreados();
	cantidadFicheros();

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
	return;
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
	printf("\n\nMemoria Total: %d %s\n",memTotal,str );

	filtrarCadena("/proc/meminfo","MemFree", linea);
	sscanf(linea, "MemFree: %d %s",&memLibre,str);
	printf("Memoria Libre: %d %s\n",memLibre,str );
	return;
}

void tiempo(){
	FILE* archivo;
	double uptime;

	archivo = fopen ("/proc/uptime","r");
	fscanf(archivo, "%lf \n",&uptime);
	fclose (archivo);

	printf("\n\n");
	print_time ("Tiempo activo: ",(long) uptime);

	return;
}

void print_time (char* label, long time)
{
	const long minute = 60;
	const long hour = minute*60;
	const long day = hour*24;

	printf ("%s: %ld days, %ld:%02ld:%02ld\n", label, time / day, (time % day) / hour, (time % hour) / minute, time % minute);
	return;
}

void tiempoCPU(){
	FILE* archivo;
	float usuario, sistema, sinuso;

	archivo = fopen ("/proc/stat","r");
	fscanf(archivo, "cpu %f %f %*f %f \n",&usuario, &sistema, &sinuso);
	

	printf("\n\n");
	print_time ("Tiempo usuario: ",(long) usuario);
	print_time ("Tiempo sistema: ",(long) sistema);
	print_time ("Tiempo sin uso: ",(long) sinuso);

	fclose (archivo);
	return;
}

void pedidosLE(){
	char linea[250];
	unsigned int lecturas, escrituras, total;

	filtrarCadena("/proc/diskstats","sda", linea);
	sscanf(linea,"sda %u",&lecturas);
	sscanf(linea,"sda %*u %*u %*u %*u %u",&escrituras);
	total=lecturas+escrituras;

	printf("\n\nCantidad de pedidos de lectura/escritura al disco: %u\n",total);
	return;
	
}

void cambiosContexto(){
	char linea[250];
	unsigned int cambios;

	filtrarCadena("/proc/stat","ctxt", linea);
	sscanf(linea,"ctxt %u",&cambios);

	printf("\n\nCambios de contexto: %u\n",cambios);
	return;
	
}

void procesosCreados(){
	char linea[250];
	unsigned int procesos;

	filtrarCadena("/proc/stat","processes", linea);
	sscanf(linea,"processes %u",&procesos);

	printf("\n\nProcesos creados desde el inicio del sistema operativo: %u\n",procesos);
	return;
	
}

void cantidadFicheros(){
	FILE* archivo;
	char *lectura=NULL;
	char buffer[250];
	int contador;

	archivo = fopen ("/proc/filesystems","r");

	while (feof(archivo)==0){
		fgets(buffer,250,archivo);
		lectura=strstr(buffer,"\n");//compara la cadena del archivo		
										//que toma fgtes y nuestro parametro de busqueda
		if(lectura!="\n"){				//si hay coincidencia, lo guarda
			contador++;	//copia lo obtenido en la cadena que								//le manda la funcion como parametro
		}
	}

	fclose(archivo);

	contador=contador-1;

	printf("\n\nCantidad de sistemas de archivo soportados por el kernel: %d \n",contador);
	
	return;

}