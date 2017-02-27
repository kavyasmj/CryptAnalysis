/******************************************************************************/
/* Program Name: histo.c
 * Author: Kavyashree Mysore Jagadeesh (mysoreja@usc.edu)
 * Description: Produces a histogram of ciphertext character frequencies
 */
/******************************************************************************/
// headers
#include "histo.h"

//method declarations
void histo(char* in_file, int period, int alphabet_num){

	FILE *infd = NULL;
	char* one_char_buf = (char*) malloc(1*sizeof(char));
	char values[] = "abcdefghijklmnopqrstuvwxyz";	
	double total = 0, alphabet_arr[26] = {0};	
	int p_counter = 0, num = 0, i = 0, highest = -1;

	if (in_file == NULL)
		infd = stdin;
	else	
		infd = fopen( in_file, "r" );

	// read cipher text from input file, get count of character frequencies and total
	while (fread(one_char_buf, 1, 1, infd) != 0) {
		p_counter++;

		if (p_counter == alphabet_num)
		{
			num = one_char_buf[0] - 'a';	// get index pertaining to character
			if (num >=0 && num <= 26)
			{
				alphabet_arr[num]++; // increment char freq count
				total++;
			}
		}
		if (p_counter == period)
			p_counter = 0;

	}
	free(one_char_buf);
	printf("L=%d\n", (int)total);
	

	//output the character frequencies sorted by count, and then by their alphabetical order
	while(1){ //TO DO brute force time complexity n^2 , or 26^2 to be exact :(, must make it more efficient if time permits
		for (i = 0; i < 26; ++i)
		{	
			if( (int)alphabet_arr[i] > highest){
				highest  = (int)alphabet_arr[i];
			}
		}

		if (highest == -1)
			break;

		for (i = 0; i < 26; ++i)
		{	
			if (highest == (int)alphabet_arr[i])
			{
				printf("%c: %d (%.2lf%c)\n", values[i], (int)alphabet_arr[i], (alphabet_arr[i]/total * 100), 37);
				alphabet_arr[i] = -1;
			}
		}
		highest = -1;
	}


	if (infd != stdin)
		fclose(infd);
}