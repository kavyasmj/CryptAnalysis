/******************************************************************************/
/* Program Name: keygen.c
 * Author: Kavyashree Mysore Jagadeesh (mysoreja@usc.edu)
 * Description: Generates a keyfile with given period to be used by the full Vigenère cipher
 */
/******************************************************************************/
// headers
#include "keygen.h"
#include "stream.h"

//method declarations
unsigned long* get_stream(char* pphrase, int period){

	// create buffer to capture stream information
	unsigned char* stream_buf = NULL;
	int index = (208*period)/4, k = 0, s = 0;
	static unsigned long* random_int = NULL;

	random_int = malloc(index * sizeof(random_int));
	stream_buf = malloc(208 * period * sizeof(stream_buf));

	//generate stream
	stream(pphrase,208*period,stream_buf);

	while(s < (208*period)){
		random_int[k++] = (unsigned long)((stream_buf[s]<<24) + (stream_buf[s+1]<<16) + (stream_buf[s+2]<<8) + (stream_buf[s+3]));
		s = s+4;
	}

	free(stream_buf);
	return random_int;
}

//method declarations
// generates the keys and outputs to console/stdin
void keygen(char* pphrase,int period){
	unsigned long* random_int;
	int p = 0, i = 0;
	random_int = get_stream(pphrase, period); // get the random numbers
	

	while(p < period){
		char state[26] = "abcdefghijklmnopqrstuvwxyz"; // alphabets to be swapped to get key from random permutations
		char temp_ch=0;
		unsigned long l = 0;
		unsigned long r = 0;		
		int count_2 = 0;

		while(count_2 < 2){ // do it twice to ensure randomness
			l = 26; // no of alphabets

			while(l>1){
				r = random_int[i++]%l--; //get a random integer within 26 characters
				if (r != l) // swap alphabests at indices r and l-1
				{
					temp_ch = state[r];
					state[r] = state[l];
					state[l] = temp_ch;
				}
			}
			count_2++;
		}

		printf("%s\n", state); // final key
		p++;
	}

	free(random_int);
}
