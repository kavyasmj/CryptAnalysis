/******************************************************************************/
/* Program Name: hw3.c
 * Author: Kavyashree Mysore Jagadeesh (mysoreja@usc.edu)
 * Description: main program to run homework3
 * COntains logic for command line validation, handling different inputs
 * and calling keygen,crypt,invkey,histo,solve programs
  */
/******************************************************************************/
// headers
#include "stream.h"
#include "keygen.h"
#include "crypt.h"
#include "invkey.h"
#include "histo.h"
#include "solve.h"
#include <sys/stat.h>

// method declarations
// get program name for showing usage information
void print_usage(int err){
	// if invalid command
	fprintf(stderr, "Malformed command\n");
	switch(err){
		case 0: fprintf(stderr,"usage1:./hw3 keygen -p=pphrase -t=period\n" );
        		fprintf(stderr,"usage2:./hw3 crypt -k=keyfile [file]\n" );
        		fprintf(stderr,"usage3:./hw3 invkey keyfile\n" );
        		fprintf(stderr,"usage4:./hw3 histo -t=period -i=which [file]\n" );
        		fprintf(stderr,"usage4:./hw3 solve -l=max_t file\n" );
				break;
		case 1: fprintf(stderr,"usage1:./hw3 keygen -p=pphrase -t=period\n" );
				break;
		case 2: fprintf(stderr,"usage2:./hw3 crypt -k=keyfile [file]\n" );
				break;
		case 3: fprintf(stderr,"usage3:./hw3 invkey keyfile\n" );
				break;
		case 4: fprintf(stderr,"usage4:./hw3 histo -t=period -i=which [file]\n" );
				break;
		case 5: fprintf(stderr,"usage4:./hw3 solve -l=max_t file\n" );
				break;
	}
    exit(1);
}

// check if file is a directory or if invalid
void check_file(char* filename){
	struct stat s;
	if( stat(filename,&s) == 0 )
	{
	    if( s.st_mode & S_IFDIR ) // check if it is directory
	    {
	    	//input file is a directory
	        fprintf(stderr, "input file: %s is a directory\n",filename);
		    exit(1);
	    }
	}
	//open input file
	FILE *file = fopen( filename, "r" );
	/* fopen on failure */
	if ( file == NULL )
	{
	    fprintf(stderr, "input file: %s ",filename); // error opening file
	    perror("");
        exit(1);
	}
	else
    	fclose( file ); //close after checking
}

 //execution starts here
int main(int argc, char* argv[]){

	char* pphrase, *period, *keyfile, *str_len_i,*max_t, *arg1, *arg2 = NULL;
	//command line validations
	if ( argc < 2 || argc > 5){
		print_usage(0);
	}

	// if executing command keygen
	if(strcmp(argv[1], "keygen") == 0 ){ 
		if (argc == 4 && argv[2][0] == '-' && argv[3][0] == '-' 
			&& argv[2][2] == '=' && argv[3][2] == '='
			&& ((argv[2][1] == 'p' && argv[3][1] == 't') 
				| (argv[3][1] == 'p' && argv[2][1] == 't')) )
		{
			// get command options
			arg1 = strtok (argv[2],"=");
			if (arg1[1] == 'p')
				pphrase = strtok (NULL,"=");
			else
				period = strtok (NULL,"=");
			
			arg2 = strtok (argv[3],"=");
			if (arg2[1] == 'p')
				pphrase = strtok (NULL,"=");
			else
				period = strtok (NULL,"=");

			if (pphrase == NULL)
					print_usage(1);

			if (period == 0)
					print_usage(1);

			keygen(pphrase, atoi(period));
		} 
		else//usage for specific command
			print_usage(1);
	}
	else if(strcmp(argv[1], "crypt") == 0 ){ // if executing command crypt
		if (((argc == 3) | (argc == 4)) && argv[2][0] == '-' 
			&& argv[2][1] == 'k' && argv[2][2] == '=' )
		{
			// get command options
			arg1 = strtok (argv[2],"=");
			keyfile= strtok (NULL,"=");
			check_file(keyfile);
			if (argc == 3)
				crypt(NULL,keyfile);
			else{
				check_file(argv[3]);
				crypt(argv[3],keyfile);
			}
		} 
		else//usage for specific command
			print_usage(2);
	}
	else if(strcmp(argv[1], "invkey") == 0 ){ //if executing command invkey
		if (argc == 3 && argv[2]!= 0 )
		{
			check_file(argv[2]);
			invkey(argv[2]);
		} 
		else//usage for specific command
			print_usage(3);
	}
	else if(strcmp(argv[1], "histo") == 0 ){  // if executing command histo
		if (((argc == 4 )| (argc == 5)) && argv[2][0] == '-' && argv[3][0] == '-' 
				&& argv[2][2] == '=' && argv[3][2] == '='
				&& ((argv[2][1] == 'i' && argv[3][1] == 't') 
					| (argv[3][1] == 'i' && argv[2][1] == 't')) )
			{
				// get command options
				arg1 = strtok (argv[2],"=");
				if (arg1[1] == 'i')
					str_len_i = strtok (NULL,"=");
				else
					period = strtok (NULL,"=");
				
				arg2 = strtok (argv[3],"=");
				if (arg2[1] == 'i')
					str_len_i = strtok (NULL,"=");
				else
					period = strtok (NULL,"=");

				if (period == 0)
					print_usage(4);

				if (str_len_i == NULL)
					print_usage(4);

				if (argc == 4)		
					histo(NULL, atoi(period),atoi(str_len_i));
				else{
					check_file(argv[4]);
					histo(argv[4], atoi(period),atoi(str_len_i));
				}
			} 
		else//usage for specific command
			print_usage(4);
	}
	else if(strcmp(argv[1], "solve") == 0 ){  // if executing command solve
		if (argc == 4 && argv[2][0] == '-' 
			&& argv[2][1] == 'l' && argv[2][2] == '=' )
		{
			// get command options
			arg1 = strtok (argv[2],"=");
			max_t = strtok (NULL,"=");
			if (max_t == 0)
				print_usage(5);

			check_file(argv[3]);
			solve(argv[3], atoi(max_t));
		} 
		else//usage for specific command
			print_usage(5);
	}
	else{
		print_usage(0);
	}


	return 0;
}