/******************************************************************************/
/* Program Name: crypt.c
 * Author: Kavyashree Mysore Jagadeesh (mysoreja@usc.edu)
 * Description: Encrypts (or decrypts) an input ASCII text file with the keys specified in keyfile
 */
/******************************************************************************/
// headers
#include "crypt.h"

//method declarations
void crypt(char* in_file, char* keyfile){

	int period = 0, col = 26, index = 0, i = 0, j = 0, period_counter = 0, num = 0;
	FILE *infd = NULL;	
	char alphabets[26] = {0}, ch = 0;	
	char* one_char_buf = NULL;
	char **key_arr = NULL;

	if (in_file == NULL)
		infd = stdin;	// take input from stdin
	else	
		infd = fopen( in_file, "r" );  //open plain text file or cipher text file
	
	FILE *keyfd = fopen( keyfile, "r" );  //open key file

	//count number of lines to get the period
	while(!feof(keyfd))
	{
	  ch = fgetc(keyfd);
	  if(ch == '\n')
	  	period++;
	}
	rewind(keyfd); //reset
	

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
		if (index < 0 || index > 26) // malformed key file validations
		{
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

	//get plaintext characters one by one, convert to cipher text or vice versa
	while (fread(one_char_buf, 1, 1, infd) != 0) {

		num = one_char_buf[0] - 'a';
		if (num >= 0 && num <= 25)
			printf("%c", key_arr[period_counter][num]);
		else
			printf("%c",one_char_buf[0]);

		period_counter++;
		if (period_counter == period)
			period_counter = 0;
	}

	if (infd != stdin)
		fclose(infd);
	
	fclose(keyfd);
	for (i = 0; i < period; i++) 
	  free(key_arr[i]);
	free(key_arr);
	free(one_char_buf);
}
