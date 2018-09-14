#include <stdio.h>
#include <string.h>

/* Returns the clock speed of the system’s CPU in MHz, as reported by
/proc/cpuinfo. On a multiprocessor machine, returns the speed of
the first CPU. On error returns zero. */

struct cpu_info{
	char model_name[100];	
};


void print_time (char* label, long time)
{/* Conversion constants. */
const long minute = 60;
const long hour = minute * 60;
const long day = hour * 24;
/* Produce output. */
printf ("%s: %ld days, %ld:%02ld:%02ld\n", label, time / day, (time % day) / hour, (time % hour) / minute, time % minute);
}


int get_cpu_info ()
{
	FILE* fp;
	char c;
	char buffer[5024];
	size_t bytes_read;
	char* match;
	char* match_2;
	char model_name[1024];
	float cache_zice;

	char get_vendor_id[1024];
	char kernel_version[1024];

	double uptime, idle_time;

	float memoria_total;

	float memoria_free;

	float cambio_contexto;

	float procesos_pc;

/* Read the entire contents of /proc/cpuinfo into the buffer.*/
	fp = fopen ("/proc/cpuinfo", "r");

/*imprimo el contenido del del FILE* */

/*
	c = fgetc(fp);
    while (c != EOF)
    {
    	printf ("%c", c);
        c = fgetc(fp);
    }
*/

	bytes_read = fread (buffer, 1, sizeof (buffer), fp);

	fclose (fp);

/* Bail if read failed or if buffer isn’t big enough. */
	if (bytes_read == 0 || bytes_read == sizeof (buffer))
		return 0;
/* NUL-terminate the text. */
	buffer[bytes_read] = '\0';
/* Locate the line that starts with “cpu MHz”. */
	//match = strstr (buffer, "cpu MHz");
	match = strstr (buffer, "cache size");
	if (match == NULL)
		cache_zice = 0;

	//puts (buffer);
	//printf("*************************************************\n");
	//printf("*************************************************\n");
	//puts(match);


	//match_2 = strstr (buffer, "model name");
	//if (match_2 == NULL)
	//	cache_zice = 0;

/* Parse the line to extract the clock speed. */
	//sscanf (match, "cpu MHz : %f", &clock_speed);
	sscanf (match, "cache size : %f", &cache_zice);

	match = strstr (buffer, "model name");

	sscanf(match, "%[^\n]", model_name);

  	match = strstr (buffer, "vendor_id");

	sscanf(match, "%[^\n]", get_vendor_id);




	fp = fopen("/proc/sys/kernel/osrelease", "r");

	bytes_read = fread (buffer, 1, sizeof (buffer), fp);

	fclose (fp);

	if (bytes_read == 0 || bytes_read == sizeof (buffer))
		return 0;

	buffer[bytes_read] = '\0';




	sscanf(buffer, "%[^\n]", kernel_version);

/* Read the system uptime and accumulated idle time from /proc/uptime.*/
	fp = fopen ("/proc/uptime", "r");
	fscanf (fp, "%lf %lf\n", &uptime, &idle_time);
	fclose (fp);


	fp = fopen("/proc/meminfo", "r");
	bytes_read = fread (buffer, 1, sizeof (buffer), fp);
	fclose (fp);

	if (bytes_read == 0 || bytes_read == sizeof (buffer))
		return 0;
	buffer[bytes_read] = '\0';
	match = strstr (buffer, "MemTotal:");
	sscanf (match, "MemTotal: %f", &memoria_total);



	//puts(buffer);

	match = strstr (buffer, "MemFree:");
	//puts(match);
	sscanf (match, "MemFree: %f", &memoria_free);


    //http://www.linuxhowtos.org/System/procstat.htm
	// ver info relacionada a /proc/stat explained

	fp = fopen ("/proc/stat", "r");

	bytes_read = fread (buffer, 1, sizeof (buffer), fp);

	fclose (fp);

	if (bytes_read == 0 || bytes_read == sizeof (buffer))
		return 0;
	buffer[bytes_read] = '\0';
	match = strstr (buffer, "ctxt");

	sscanf (match, "ctxt %f", &cambio_contexto);



    //La línea de "procesos" proporciona la cantidad de procesos y subprocesos creados, que incluye 
    //(pero no se limita a) los creados por las llamadas al sistema fork () y las 
    //llamadas al sistema clone ().

	match = strstr (buffer, "processes");

	sscanf (match, "processes %f", &procesos_pc);



    //https://es.scribd.com/document/89906346/Tare-a-1
	//puts(buffer);

	//puts(match);


	//printf("!!!!!!!! ver\n");
	//puts(buffer);

	//printf ("nuevo!!!!! cache size: %4.0f KB\n", cache_zice);
	//mostramos en pantalla
	puts(get_vendor_id);
	puts(model_name);
	printf("version kernel  : ");
	puts(kernel_version);
	print_time ( "uptime", (long) uptime);
	print_time ("idle time", (long) idle_time);
	printf("memoria total   : %4.0f kB\n", memoria_total);
	printf("memoria libre   : %4.0f kB\n", memoria_free);
	printf("cambio de contexto   : %4.0f \n", cambio_contexto);
	printf("procesos   : %4.0f \n", procesos_pc);
	return 1;

}

/* Summarize a duration of time to standard output. TIME is the
amount of time, in seconds, and LABEL is a short descriptive label.
*/


//https://en.wikipedia.org/wiki/Getopt
//https://linux.die.net/man/3/getopt_long
int main ()
{
	printf("hola mundo\n");
	//printf ("CPU clock speed: %4.0f MHz\n", get_cpu_clock_speed ());
	//printf ("cache size: %4.0f KB\n", get_cpu_clock_speed ());
	get_cpu_info ();

	return 0;
}
