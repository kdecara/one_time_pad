/*
 * The one time pad is a type of stream cipher which 
 * is unconditionally secure if the following hold true:
 * 1 the key stream is truly random
 * 2 the key stream is only know by communicating parties
 * 3 every key key stream bit is only used once
 * Encryption(x) = y = x + s mod 2
 * Decryption(y) = x = y + s mod 2
 * The one time pad has the drawbacks in that the stream cipher must 
 * be as large as the message, so we are essentially doubling the size of the message
 * and that the since the stream cipher must be truly random, parties must generate and 
 * agree upon a truly random stream for each new messagea
 */

#include <stdlib.h>
#include <stdio.h>
#include "../file_pack.h"

#define MOD(x, n) ((x % n + n) % n)
#define RING_SIZE 128
#define SEED 0

void encrypt(FILE *in, FILE *out);
void decrypt(FILE *in, FILE *out);

int main(int argc, char *argv[])
{
    /*TODO: may have to change the "rb" and "w"*/
    file_s *in_file = open_file(argv[1], "r");
    file_s *out_file = open_file(argv[2], "w");
    /*seed will be set by the user on each program run*/
    int seed = atoi(argv[3]);
    char *mode = argv[4];
    srand(seed);
    if(mode[0] == 'e') encrypt(in_file->fp, out_file->fp);
    else if(mode[0] == 'd') decrypt(in_file->fp, out_file->fp);
    
    close_file(in_file);
    close_file(out_file);
    return 0;
}

/*Note that while the book "Understanding Cryptography" provides the definition
 *of one time pad (and general stream ciphers) as bit by bit encryption
 *namely, e(x) = y = x + s mod 2 and d(y) = x = y + s mod 2
 *i will be encrypting and decrypting byte by byte here, as dealing with individual
 *will take much more time
 */
void encrypt(FILE *in, FILE *out)
{
    char c;
    c = fgetc(in);
    printf("encrypting file...\n");
    while(c != EOF)
    {
	    printf("c = %c\t", c);
	    c = c ^ rand();
	    printf("enc_c = %c\n", c);
	    fputc(c, out);
	    c = fgetc(in);
    }
    printf("file encrypted\n");
}

void decrypt(FILE *in, FILE*out)
{
    char c;
    c = fgetc(in);
    printf("decrypting file...\n");
    while(c != EOF)
    {
    	c = c ^ rand();
	    fputc(c, out);
    	c = fgetc(in);
    }
    printf("file decrypted\n");
}

