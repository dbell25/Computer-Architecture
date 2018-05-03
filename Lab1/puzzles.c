//
// puzzles.c
//
// (y>>4)<<4 <= y
// (x<<4)>>4 <= x
// dx * dy == (double) (x*y) \n");
// ux == (unsigned) (float) ux \n");
// uy == (unsigned) (double) uy \n");
// x > y  implies  -x < -y \n");
// y * y * y * y  >= 0 \n");
// (int) (ux - uy) == (x-y) \n");
// x >= 0  implies  -x <= 0 \n");
// x <= 0  implies  -x >= 0 \n");
// y != 0 implies y != -y \n");
// ux >> 3 == ux/8 \n");
// x >> 3 == x/8 \n");
// x>0 and y>0 implies x*x + y+y > 0

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
  int x, y;
  unsigned int ux, uy;
  double dx, dy;

  int i, solved = 0;  // index and flag to keep track of solved problems
  int num_solved = 0; // note that "solved" means that a counter-example has been found

  printf("PUZZLES:\n");
  printf(" 1. (y>>4)<<4 <= y \n");
  printf(" 2. (x<<4)>>4 <= x \n");
  printf(" 3. dx * dy == (double) (x*y) \n");
  printf(" 4. ux == (unsigned) (float) ux \n");
  printf(" 5. uy == (unsigned) (double) uy \n");
  printf(" 6. x > y  implies  -x < -y \n");
  printf(" 7. y * y * y * y >= 0 \n");
  printf(" 8. (int) (ux - uy) == (x-y) \n");
  printf(" 9. x >= 0  implies  -x <= 0 \n");
  printf(" 10. x <= 0  implies  -x >= 0 \n");
  printf(" 11. y != 0 implies y != -y \n");
  printf(" 12. ux >> 3 == ux/8 \n");
  printf(" 13. x >> 3 == x/8 \n");
  printf(" 14. dx * dx * dx * dx >= 0.0 \n");
  printf(" 15. x>0 and y>0 implies x*x + y+y > 0 \n");

  printf("INT_MAX: %d %X\n", INT_MAX, INT_MAX);
  printf("INT_MIN: %d %X\n", INT_MIN, INT_MIN);
  printf("UINT_MAX: %d %X\n", UINT_MAX, UINT_MAX);

  printf("Enter x and y: ");
  while(scanf("%d %d", &x, &y) == 2)
  {
    ux = (unsigned) x;
    uy = (unsigned) y;
    dx = (double) x;
    dy = (double) y;
    printf("DECIMAL:     x = %d, y = %d, ux = %u, uy = %u\n", x,y,ux,uy);
    printf("HEXIDECIMAL: x = %08X, y = %08X, ux = %08X, uy = %08X\n", x,y,ux,uy);

    if ((y>>4)<<4 > y){
      solved |= 1<<0;
      printf("1. (y>>4)<<4 > y for y = %d \n", y);
      printf("   (y>>4)<<4 = %d \n", (y>>4)<<4);
    }
    if ((x<<4)>>4 > x){
      solved |= 1<<1;
      printf("2. (x<<4)>>4 > x for x = %d \n", x);
      printf("   (x<<4)>>4 = %d \n", (x<<4)>>4);
    }
    if ((dx*dy)!=(double)(x*y)){
      solved |= 1<<2;
      printf("3. (dx*dy)!=(double)(x*y) for x = %d, y = %d \n", x,y);
    }
    if (ux != (unsigned) (float) ux){
      solved |= 1<<3;
      printf("4. ux != (unsigned) (float) ux for ux = %u \n", ux);
    }
    if (uy != (unsigned) (double) uy){
      solved |= 1<<4;
      printf("5. uy != (unsigned) (double) uy for uy = %u \n", uy);
    }
    if ((x>y)&&(-x>=-y)){
      solved |= 1<<5;
      printf("6. x>y, but -x not less than -y for x = %d, y=%d\n", x, y);
    }
    if ((y*y*y*y) < 0){
      solved |= 1<<6;
      printf("7. y*y*y*y is less than 0\n");
    }
    if ((int)(ux-uy) != (x-y)){
      solved |= 1<<7;
      printf("8. (int) (ux - uy) != (x-y) for x = %d, y = %d, ux = %u, uy = %u\n",x,y,ux,uy);
    }
    if ((x>=0)&&(-x>0)){
      solved |= 1<<8;
      printf("9. (x>=0)&&(-x>0) for x = %d \n", x);
    }
    if ((x<=0)&&(-x<0)){
      solved |= 1<<9;
      printf("10. (x<=0)&&(-x<0) for x = %d \n", x);
    }
    if ((y!=0)&&(y==-y)){
      solved |= 1<<10;
      printf("11. (y!=0), but (y==-y) for y = %d \n", y);
    }
    if ((ux >> 3) != (ux/8)){
      solved |= 1<<11;
      printf("12. ((ux >> 3) != (ux/8)) for ux = %u \n", ux);
    }
    if ((x >> 3) != (x/8)){
      solved |= 1<<12;
      printf("13. ((x >> 3) != (x/8)) for x = %d \n", x);
    }
    if (dx*dx*dx*dx<0.0) {
      solved |= 1<<13;
      printf("14. (dx*dx*dx*dx < 0.0) for x = %d \n", x);
    }
    if ((x>0)&&(y>0)&&((x*x+y+y)<=0)){
      solved |= 1<<14;
      printf("15. (x>0) and (y>0), but (x*x+y+y)<=0 for x = %d and y = %d \n", x, y);
    }
    printf("\nEnter x and y: ");
  }

  num_solved = 0;
  printf("Problems Solved: ");
  for (i=1; i<=15; i++)
  {
    if (solved&1<<(i-1)) {
      num_solved++;
      printf("%d ",i);
    }
  }
  printf("\nNumber Solved: %d\n", num_solved);
  return 0;
}
