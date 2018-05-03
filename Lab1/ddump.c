//
// ddump.c - dump a double precision number in IEEE 754 format
//
//
//   Examples:
//
//   ./ddump            - 0.0 is the default
//   ./ddump 1.0E20     - 1.0 x 10^20
//   ./ddump INFINITY   - infinity
//   ./ddump NAN        - not-a-number (NaN)
//   ./ddump M_PI       - double precision floating-point approximation to pi.
//   ./ddump 22 7       - approximation to the fraction 22/7
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len)
{
    int i, j;
    // print out the bytes in hex format
    for (i = len-1; i>=0; i--)
	printf(" %.2x", start[i]);
    printf("\n");

    // print out each part of the double in binary format
    printf("Sign Bit: %d\n", (start[7]&0x80)?1:0);
    printf("Exponent: ");
    for(i=6; i>=0; i--)
        printf("%d",(start[7]&(1<<i))?1:0);
    for(i=7; i>=4; i--)
        printf("%d",(start[6]&(1<<i))?1:0);
    printf("\nMantissa: ");
    for(i=3; i>=0; i--)
        printf("%d",(start[6]&(1<<i))?1:0);
    for (j=5; j>=0; j--)
      for(i=7; i>=0; i--)
        printf("%d",(start[j]&(1<<i))?1:0);
    printf("\n"); 
}

void show_double(double x)
{
    show_bytes((byte_pointer) &x, sizeof(double));
}

int main(int argc, char *argv[])
{
  double x = 0.0;
  double y,z;
  int temp;

  if (argc == 2)
  {
    if ((argv[1][0]=='0')&&(argv[1][1]=='x'))
    {
      sscanf(argv[1],"%lx", (unsigned long *)&x);
    }
    else
    {
      if (strcmp(argv[1],"M_PI")==0)
        x = M_PI;
	  else if (strcmp(argv[1],"M_SQRT2")==0)
	    x = M_SQRT2;
	  else
        x = atof(argv[1]);
    }
  }
  else if (argc == 3)
  {
    y = atof(argv[1]);
    z = atof(argv[2]);
    x = y/z;
  }
  printf("x = %25.20E\n",x);
  show_double(x);
  return 0;
}
