#include <stdio.h>

void print_time (char* label, long time)
{
	const long minute = 60;
	const long hour = minute*60;
	const long day = hour*24;

	printf ("%s: %ld days, %ld:%02ld:%02ld\n", label, time / day, (time % day) / hour, (time % hour) / minute, time % minute);
}

int main()
{
	/* code */
	FILE* fp;
	double uptime, idle_time;

	fp = fopen ("/proc/uptime","r");
	fscanf(fp, "%lf %lf\n",&uptime, &idle_time);
	fclose (fp);

	print_time ("uptime",(long) uptime);
	print_time ("idle_time", (long) idle_time);
	return 0;
}