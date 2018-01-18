#include <stdio.h>

char board[8][8];

void mark_position(int y, int x)
{
  int i, j;

  for (i = 0; i < 8; i++) {
    board[i][x]++;
    board[y][i]++;
  }

  for (i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
    board[j][i]++;
  }
  for (i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++) {
    board[j][i]++;
  }
  for (i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--) {
    board[j][i]++;
  }
  for (i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++) {
    board[j][i]++;
  }
}

void unmark_position(int y, int x)
{
  int i, j;

  for (i = 0; i < 8; i++) {
    board[i][x]--;
    board[y][i]--;
  }

  for (i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
    board[j][i]--;
  }
  for (i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++) {
    board[j][i]--;
  }
  for (i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--) {
    board[j][i]--;
  }
  for (i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++) {
    board[j][i]--;
  }
}

void print_board(char board[8][8])
{
  int i, j;

  for (j = 0; j < 8; j++) {
    for (i = 0; i < 8; i++) {
      printf("%hhd ", board[j][i]);
    }
    printf("\n");
  }
  printf("\n");
}

void print_queens(int row[8])
{
  int i, j;

  for (j = 0; j < 8; j++) {
    for (i = 0; i < 8; i++) {
      if (j == row[i]) {
        printf("* ");
      } else {
        printf("0 ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

int main(int argc, char *argv[])
{
  int row[8];
  int i;

  for (row[0] = 0; row[0] < 8; row[0]++) {
    mark_position(0, row[0]);
    for (row[1] = 0; row[1] < 8; row[1]++) {
      if (!board[1][row[1]]) {
        mark_position(1, row[1]);
        for (row[2] = 0; row[2] < 8; row[2]++) {
          if (!board[2][row[2]]) {
            mark_position(2, row[2]);
            for (row[3] = 0; row[3] < 8; row[3]++) {
              if (!board[3][row[3]]) {
                mark_position(3, row[3]);
                for (row[4] = 0; row[4] < 8; row[4]++) {
                  if (!board[4][row[4]]) {
                    mark_position(4, row[4]);
                    for (row[5] = 0; row[5] < 8; row[5]++) {
                      if (!board[5][row[5]]) {
                        mark_position(5, row[5]);
                        for (row[6] = 0; row[6] < 8; row[6]++) {
                          if (!board[6][row[6]]) {
                            mark_position(6, row[6]);
                            for (row[7] = 0; row[7] < 8; row[7]++) {
                              if (!board[7][row[7]]) {
                                /* print_queens(row); */
                                for (i = 0; i < 8; i++) {
                                  printf("%c%d", 'a' + i, row[i] + 1);
                                }
                                printf("\n");
                                break;
                              }
                            }
                            unmark_position(6, row[6]);
                          }
                        }
                        unmark_position(5, row[5]);
                      }
                    }
                    unmark_position(4, row[4]);
                  }
                }
                unmark_position(3, row[3]);
              }
            }
            unmark_position(2, row[2]);
          }
        }
        unmark_position(1, row[1]);
      }
    }
    unmark_position(0, row[0]);
  }

  return 0;
}
