#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXVAL 16383
#define NUMTODO	16000

#define ADDITION_VALUE_128 224
#define ADDITION_VALUE_64 192
#define ADDITION_VALUE_32 160
#define ADDITION_VALUE_16 128
#define ADDITION_VALUE_8 96
#define ADDITION_VALUE_4 64
#define ADDITION_VALUE_2 32
#define STREAMSIZE 100

/*
unsigned char pwlog2(unsigned char x) {
/* pwlog2 = piecewise log2 */
/*
	if( x < 1)
		return( 0); /* error */
/*	if( x < 2)
		return((x-1) << 5);
	if( x < 4)
		return((1<<5) + ((x-2)<<4));
	if( x < 8)
		return((2<<5) + ((x-4)<<3));
	if( x < 16)
		return((3<<5) + ((x-8)<<2));
	if( x < 32)
		return((4<<5) + ((x-16)<<1));
	if( x < 64)
		return( (5<<5) + (x-32));
	if( x < 128) {
		return( (6<<5) + ((x-64)>>1));
	}
	if( x < 256)
		return( (7<<5) + ((x-128)>>2));
	return( 0); /* error */
//}

//unsigned char pwlog2BSearch(unsigned char x) {
/* pwlog2 = piecewise log2 */
/*	if( x >= 16) {
		if( x >= 64) {
			if( x >= 128)
				return( (7<<5) + ((x-128)>>2));
			return( (6<<5) + ((x-64)>>1));
		} else {
			if( x >= 32)
				return( (5<<5) + (x-32));
			return((4<<5) + ((x-16)<<1));
		}
	} else {
		if( x >= 4) {
			if( x >= 8)
				return((3<<5) + ((x-8)<<2));
			return((2<<5) + ((x-4)<<3));
		} else {
			if( x >= 2) {
				return((1<<5) + ((x-2)<<4));
			}
			return 0; //error
		}
	}
}
*/
int pwlog2Reverse(int x) {
/* pwlog2 = piecewise log2 */

	//int[] lookUp = {0.0, 0.0, 1.0, 1.5, 2.0, 2.25, 2.5, 2.75, 3.0};
	if( x >= 128)
		return( (ADDITION_VALUE_128) + ((x-128)>>2));
	if( x >= 64) 
		return( (ADDITION_VALUE_64) + ((x-64)>>1));
	if( x >= 32)
		return( (ADDITION_VALUE_32) + (x-32));
	if( x >= 16)
		return((ADDITION_VALUE_16) + ((x-16)<<1));
	if( x >= 8)
		return((ADDITION_VALUE_8) + ((x-8)<<2));
	if( x >= 4)
		return((ADDITION_VALUE_4) + ((x-4)<<3));
	if( x >= 2)
		return((ADDITION_VALUE_2) + ((x-2)<<4));
	return( 0); /* error */

}

static char MuLawCompressTable[256] =
{
     0,0,1,1,2,2,2,2,3,3,3,3,3,3,3,3,
     4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
     5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
     5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
     6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
     6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
     6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
     6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
     7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
     7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
     7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
     7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
     7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
     7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
     7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
     7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
};

inline int pwlog2WShift(int x) {
	if( x >= 128)
		return 7;
	if( x >= 64) 
		return 6;
	if( x >= 32)
		return 5;
	if( x >= 16)
		return 4;
	if( x >= 8)
		return 3;
	if( x >= 4)
		return 2;
	if( x >= 2)
		return 1;
	return 0;
}

unsigned char pwlog2Reverse2(unsigned char x) {
/* pwlog2 = piecewise log2 with bitwise ops*/
	if( x >= 128)
		return( (7<<5) + ((x & 127)>>2));
	if( x >= 64)
		return( (6<<5) + ((x & 63)>>1));
	if( x >= 32)
		return( (5<<5) + (x & 31));
	if( x >= 16)
		return((4<<5) + ((x & 15)<<1));
	if( x >= 8)
		return((3<<5) + ((x & 7)<<2));
	if( x >= 4)
		return((2<<5) + ((x & 3)<<3));
	if( x >= 2)
		return((1<<5) + ((x & 1)<<4));
/*
	if(x != (x & 127))
		return( (7<<5) + (x & 127>>2));
	if(x != (x & 63)) 
		return( (6<<5) + ((x & 63)>>1));
	if(x != (x & 31))
		return( (5<<5) + (x & 31));
	if(x != (x & 15))
		return((4<<5) + ((x & 15)<<1));
	if(x != (x & 7))
		return((3<<5) + ((x & 7)<<2));
	if(x != (x & 3))
		return((2<<5) + ((x & 3)<<3));
	if(x != (x & 1))
		return((1<<5) + ((x & 1)<<4));
*/
	return( 0); /* error */

}

inline unsigned char LinearToMuLawSample(short sample)
{
	//int exponent = 6;
	//int exponent = MuLawCompressTable[sample>>6];
	int exponent = pwlog2WShift(sample>>6);
	int mantissa = (sample >> (exponent + 2));
	int compressedByte = ((exponent << 5) | mantissa);

	return (unsigned char)compressedByte;
} 

//if argc = 2: regular, if argc = 3 reverse, if argc = 4 binary search if argc = 5 outputs the approx log valuez
int main(int argc, char **argv) {
	int i,b;
	//unrolling helps
	for (i = NUMTODO; i; i--) {
		b = LinearToMuLawSample(i);
		//printf("%d\n", b);
	}
	/*if(argc == 2) {
		start = clock();
		for(i = 0; i < 1000000; i++) { 
			b = pwlog2( a);
			c = b / 32.0;
			//printf("%f\n", c);
		}
		end = clock();
		elapsed = (double) (end - start) / CLOCKS_PER_SEC;
		printf("%f\n", elapsed);
	}
	
	if(argc == 3) {
		start = clock();
		for(i = 0; i < 1000000; i++) { 
			b = pwlog2Reverse( a);
			c = b / 32.0;
			//printf("%f\n", c);
		}
		end = clock();
		elapsed = (double) (end - start) / CLOCKS_PER_SEC;
		printf("%f\n", elapsed);
	}

	if(argc == 4) {
		start = clock();
		for(i = 0; i < 1000000; i++) { 
			b = pwlog2BSearch( a);
			c = b / 32.0;
			//printf("%f\n", c);
		}
		end = clock();
		elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("%f\n", elapsed);
	}
	
	//Used for comparing the approx value to the actual
	if(argc == 5) {
		b = pwlog2BSearch( a);
		c = b / 32.0;
		printf("%f\n", c);
	}
*/
	
	return 0;
}
