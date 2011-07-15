#include <stdio.h>
#include <stdlib.h>
#include <time.h>


unsigned char pwlog2(unsigned char x) {
/* pwlog2 = piecewise log2 */

	if( x < 1)
		return( 0); /* error */
	if( x < 2)
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
}

unsigned char pwlog2BSearch(unsigned char x) {
/* pwlog2 = piecewise log2 */
	if( x >= 16) {
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

unsigned char pwlog2Reverse(unsigned char x) {
/* pwlog2 = piecewise log2 */

	if( x >= 128)
		return( (7<<5) + ((x-128)>>2));
	if( x >= 64) 
		return( (6<<5) + ((x-64)>>1));
	if( x >= 32)
		return( (5<<5) + (x-32));
	if( x >= 16)
		return((4<<5) + ((x-16)<<1));
	if( x >= 8)
		return((3<<5) + ((x-8)<<2));
	if( x >= 4)
		return((2<<5) + ((x-4)<<3));
	if( x >= 2)
		return((1<<5) + ((x-2)<<4));
	if( x >= 1)
		return((x-1) << 5);
	if( x < 1)
		return( 0); /* error */
	return( 0); /* error */
}


unsigned char test(unsigned char x) {
	return 0 ;
}

//if argc = 2: regular, if argc = 3 reverse, if argc = 4 binary search
int main(int argc, char **argv) {
	
	float b,c;
	int a = 0;
	int i;
	
	clock_t start, end;
	double elapsed;
	a = atoi(argv[1]);
	
	if(argc == 2) {
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
	return 0;
}
