#include <stdio.h>
#include <stdlib.h>

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
}

int main( void) {
	float b,c;
	unsigned char a = 0;
	//Need to type the equation out (ie a = 1;)
	scanf( "a = %i\n", &a);
	b = pwlog2( a);
	c = b / 32.0;
	printf( "log2( a) = %f\n", c);
}