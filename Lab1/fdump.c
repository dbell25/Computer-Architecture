//
// fdump.c - dump a floating point number in IEEE floating-point format
//
//
//   Examples:
//
//   ./fdump            - 0.0 is the default
//   ./fdump 1.0E20     - 1.0 x 10^20
//   ./fdump INFINITY   - infinity
//   ./fdump NAN        - not-a-number (NaN)
//   ./fdump 0x40490FDB - single precision floating-point approximation to pi.
//   ./fdump 22 7       - approximation to the fraction 22/7
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void show_float(float x)
{
    int i, len = sizeof(float);
    union {
	    float f;
		unsigned char  c[4];
	} u;
	u.f = x;

    // print out the bytes in hex format
    for (i = len-1; i>=0; i--)
	printf(" %.2X", u.c[i]);
    printf("\n");

    // print out each part of the float in binary format
    printf("Sign Bit: %d\n", (u.c[3]&0x80)?1:0);
    printf("Exponent: ");
    for(i=6; i>=0; i--)
        printf("%d",(u.c[3]&(1<<i))?1:0);
    printf("%d\n",(u.c[2]&(1<<7))?1:0);
    printf("Mantissa (Fraction Bits): ");
    for(i=6; i>=0; i--)
        printf("%d",(u.c[2]&(1<<i))?1:0);
    for(i=7; i>=0; i--)
        printf("%d",(u.c[1]&(1<<i))?1:0);
    for(i=7; i>=0; i--)
        printf("%d",(u.c[0]&(1<<i))?1:0);
    printf("\n"); 
}

int main(int argc, char *argv[])
{
  float x = 0.0;
  float y,z;
  int temp;

  if (argc == 2)
  {
    if ((argv[1][0]=='0')&&(argv[1][1]=='x'))
    {
      sscanf(argv[1],"%x", (unsigned *)&x);
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
  printf("x = %15.10E\n",x);
  show_float(x);
  return 0;
}
