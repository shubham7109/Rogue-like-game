#include <stdio.h>

void times_table(void)
{
  int i, j;
  int table[10][10];

  for (j = 0; j < 10; j++) {
    for (i = 0; i < 10; i++) {
      table[j][i] = (j + 1) * (i + 1);
    }
  }

  for (j = 0; j < 10; j++) {
    for (i = 0; i < 10; i++) {
      printf("%3d ", table[j][i]);
    }
    printf("\n");
  }  
}

int main(int argc, char *argv[])
{
  times_table();

  return 0;
}
