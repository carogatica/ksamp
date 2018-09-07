
#include <stdio.h>
#include <string.h>

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

int main(int argc, char const *argv[])
{
	versionKernel();

	return 0;
}