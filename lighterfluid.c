#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define WRITEFILE "/sys/class/backlight/radeon_bl0/brightness"
#define READFILE WRITEFILE
#define MAXFILE "/sys/class/backlight/radeon_bl0/max_brightness"

#define MIN 1 // set this to whatever minimum you want... 0 if you want to turn off the screen

int max = 0;
int current = 0;


int getval(char * file){
	int retty;
	FILE * f = fopen(file, "r");
	if(!f) return -1;
	fscanf(f, "%d", &retty);
	fclose(f);
	return retty;
}

int setval(char * file, int value){
	FILE *f = fopen(file, "w");
	if(!f) return -1;
	int ret = fprintf(f, "%d\n", value);
	fclose(f);
	return ret;
}


int smallstrcmp(char * one, char * two){
	for(; *one && *one == *two; one++, two++);
	return *one == *two;
}


int main(int argc, char ** argv){
	if(argc < 2 || smallstrcmp(argv[1], "max")){
		max = getval(MAXFILE);
		if(max < 0){ printf("Unable to read max brightness\n"); return 3;}
		int want = max;
		if(setval(WRITEFILE, want) < 0){ printf("Unable to set value to %d\n", want); return 4;}
	} else if(smallstrcmp(argv[1], "half")){
		current = getval(READFILE);
		if(current < 0){ printf("Unable to read current brightness\n"); return 2;}
		int want = current/2;
		if(want < MIN){ printf("Truncating requested brightness from %d to %d (min)\n", want, MIN); want = MIN;}
		if( setval(WRITEFILE, want) < 0){ printf("Unable to set value to %d\n", want); return 4;}
	} else if(smallstrcmp(argv[1], "double")){
		current = getval(READFILE);
		if(current < 0){ printf("Unable to read current brightness\n"); return 2;}
		max = getval(MAXFILE);
		if(max < 0){ printf("Unable to read max brightness\n"); return 3;}
		int want = current*2 + !current; // need the +! shit so it doesnt get stuck at 0
		if(want > max){ printf("Truncating requested brightness from %d to %d (max)\n", want, max); want = max;}
		if( setval(WRITEFILE, want) < 0){ printf("Unable to set value to %d\n", want); return 4;}
	} else if(smallstrcmp(argv[1], "set")){
		if(argc <3){ printf("set needs a value\n"); return 1;}
		max = getval(MAXFILE);
		if(max < 0){ printf("Unable to read max brightness\n"); return 3;}
		int want = atoi(argv[2]);
		if(want > max){ printf("Truncating requested brightness from %d to %d (max)\n", want, max); want = max;}
		else if(want < MIN){ printf("Truncating requested brightness from %d to %d (min)\n", want, MIN); want = MIN;}
		if(setval(WRITEFILE, want) < 0){ printf("Unable to set value to %d\n", want); return 4;}
	} else {
		printf("%s is not a valid command\n", argv[1]);
	}
	return 0;
}
