/******************************************************************************/
/* Program Name: solve.c
 * Author: Kavyashree Mysore Jagadeesh (mysoreja@usc.edu)
 * Description: Applies the Method of Kasiski and uses Index of Coincidence 
 * in order to determine the period of a ciphertext 
 * encrypted by a full Vigenère cipher (with polyalphabetic substitution).
 */
/******************************************************************************/
// headers
#include "solve.h"

// output cryptanalysis first by kasiski method, average index auto-correlation method
//method declarations
void solve(char* c_file, int max_t){

	FILE *cfd = fopen( c_file, "r" ); // open cipher text file

	//get file size
	fseek(cfd, 0L, SEEK_END);
	int sz = ftell(cfd);
	rewind(cfd); // reset

	char* buf = (char*) malloc(sz*sizeof(char));
	fread(buf, 1, sz, cfd); // get all the file contents

	printf("Kasiski Method\n");
	printf("==============\n");

	int i = 0, j = 0, not_alpha = 0, k = 0, match = 0;
	int length = 4;
	char* comp_str_i = NULL;
	char* comp_str_j = NULL;

	while(1){
		comp_str_i = malloc(sizeof(char)*length);
		comp_str_j = malloc(sizeof(char)*length);
		for (i = 0; i < sz-length; ++i)
		{
			strncpy(comp_str_i, buf+i, length);
			not_alpha = 0;
			for (k = 0; k < length; k++)
			{
			   if(isalpha(comp_str_i[k]) == 0){ // string should only be characters a-z
				   	not_alpha = 1;
				   	break;
			   }
			}

			if (not_alpha == 1)
				continue;

			// search through the rest if the cipher text to find a matching string
			for (j = i+1; j < sz-length; ++j)
			{
				strncpy(comp_str_j, buf+j, length);
				if (strcmp(comp_str_j, comp_str_i) == 0){
					match++;
					printf("len=%d, i=%d, j=%d, j-i=%d, %s\n",length, i, j, j-i, comp_str_j );
				}
			}
		}

		free(comp_str_i);
		free(comp_str_j);
		
		// break out of the loops when no more matches are found
		if (match == 0){
			printf("len=%d, no more matches\n",length);
			break;
		}
		else{
			match = 0;
			length++;
		}
	}

	
	printf("\nAverage Index of Coincidence\n");
	printf("============================\n");
	long double ic = 0;
	int alphabet_arr[26] = {0};
	int total = 0, num = 0;

	for (i = 0; i < sz; ++i)
	{
		num = buf[i] - 'a';
		if (num >=0 && num <= 26)
		{
			alphabet_arr[num]++; // count of how many times a character is present in the text
			total++;
		}
	}

	//calculate IC
	char values[] = "abcdefghijklmnopqrstuvwxyz";
	printf("L=%d\n", total);

	for (i = 0; i < 26; ++i){
		printf("f('%c')=%d\n",values[i],alphabet_arr[i]);
		ic += alphabet_arr[i]*(alphabet_arr[i]-1);
	}

	ic /= (total*(total-1));

	printf("IC=%0.8LG\n",ic );

	long double kp = (long double)0.0658, kr = (long double)1/(long double)26;
	long double t=0, L = (long double)total, one = 1;

	// calculate EC
	for (i = 1; i <= max_t; i++)
	{	
		t = (long double)i;
		printf("t=%d, E(IC)=%0.8LG\n",i,( (one/t) * ( (L-t) / (L-one) ) * kp )+(((t-one)/t)*((L)/(L-one))*kr));
	}

	printf("\nAuto-correlation Method\n");
	printf("=======================\n");
	int count = 0, l = 0;
	for (l = 1; l <= max_t; ++l)
	{	
		count = 0;
		for (i = 0; i < sz-l; ++i)
		{
			num = buf[i] - 'a';
			if (num >=0 && num <= 26)
			{	
				if (buf[i] == buf[i+l]){
					count++;
				}
			}
			
		}
		printf("t=%d, count=%d\n",l, count);
	}

	printf("\n");
}