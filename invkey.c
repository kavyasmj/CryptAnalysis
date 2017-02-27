/******************************************************************************/
/* Program Name: invkey.c
 * Author: Kavyashree Mysore Jagadeesh (mysoreja@usc.edu)
 * Description: Creates an inverse permutation key file from given keyfile
 */
/******************************************************************************/
// headers
#include "invkey.h"

//method declarations
void invkey(char* keyfile){

	int period = 0,col = 26, i = 0, j = 0;
	char* one_char_buf = NULL;
	char **key_arr = NULL;
	char values[] = "abcdefghijklmnopqrstuvwxyz"; //alphabets to be used to get the inverse key
	const char *ptr = NULL;
	char ch = 0;

	int index = 0;
	char alphabets[26] = {0};

	FILE *keyfd = fopen( keyfile, "r" ); //open key file

	//count number of lines to get the period
	while(!feof(keyfd))
	{
	  ch = fgetc(keyfd);
	  if(ch == '\n')
	  	period++;
	}
	rewind(keyfd);//reset
	

	one_char_buf = (char*) malloc(1*sizeof(char));	
	key_arr = malloc(period * sizeof(char*));

	// create 2d key arr
	for (i = 0; i < period; i++) {
		key_arr[i] = malloc(col * sizeof(char));
	}

	i = 0; j = 0;

	//get key characters one by one
	while (fread(one_char_buf, 1, 1, keyfd) != 0) {
		if (one_char_buf[0] == '\n')
		{
			i++;
			if (j < 26){ // malformed key file validations
				fprintf(stderr, "Error: Key File is not of correct format! Line %d does not contain all 26 alphabets\n",i); 
				exit(1);
			}
			if (j > 26){
				fprintf(stderr, "Error: Key File is not of correct format! Line %d contains more than 26 characters\n", i); 
				exit(1);
			}
			memset(alphabets, 0, 26); // reinitialize after every pass
			j = 0;
			
			continue;
		}
		key_arr[i][j] = one_char_buf[0];
		index = one_char_buf[0]-'a';
		if (index < 0 || index > 26)
		{	// malformed key file validations
			fprintf(stderr, "Error: Key File is not of correct format! Line %d contains invalid characters\n", i+1); 
			exit(1);
		}
		alphabets[index]++;
		if (alphabets[index] > 1){
			fprintf(stderr, "Error: Key File is not of correct format! alphabets are repeating in line %d\n", i+1); 
			exit(1);
		}
		j++;
	}


	index = 0;
	for (i = 0; i < period; ++i)
	{
		for ( j = 0; j < col; ++j)
		{
			// find character's index in key file... proceed alphabetically
			ptr = strchr(key_arr[i], values[j]);
			if(ptr){
				   index = ptr - key_arr[i];
				   printf("%c",values[index]);	// print the character at that index, it is the inverse of the key file
			}
		}
		printf("\n");
	}

	// cleanup operations
	fclose(keyfd);
	for (i = 0; i < period; i++) {
	  free(key_arr[i]);
	}
	free(key_arr);
	free(one_char_buf);
}