#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
  if (argc == 2) {
    srand(atoi(argv[1]));
  } else {
    srand(time(NULL)); /* Don't put srand() in a loop!  Call it exactly once */
  }                    /* before you call rand() for the first time.         */

  printf("%d\n", rand());
  printf("%d\n", rand());
  printf("%d\n", rand());
  printf("%d\n", rand());
  printf("%d\n", rand());

  printf("%d\n", (rand() % 8) + 3);
  printf("%d\n", (rand() % 8) + 3);
  printf("%d\n", (rand() % 8) + 3);
  printf("%d\n", (rand() % 8) + 3);
  printf("%d\n", (rand() % 8) + 3);
  printf("%d\n", (rand() % 8) + 3);
  printf("%d\n", (rand() % 8) + 3);
  printf("%d\n", (rand() % 8) + 3);

  return 0;
}
