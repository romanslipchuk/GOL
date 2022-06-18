#include <stdio.h>
#include <stdlib.h>

/* 2-D array that represent the cell grid */
int grid[78][50];

/* A copy of the original cell grid */
int grid2[78][50];

/* Height and width of the grid */
int height, width;

/* Resets the grid to the initial configuration (all cells are dead) */
void resetGrid() {
  for (int i = 0; i < 78; i++) {
    for (int j = 0; j < 50; j++) {
      /* -1 means dead. Non-negative values mean the cell is live and the number is its age */
      grid[i][j] = -1;
      grid2[i][j] = -1;
    }
  }
}

/* Reads from a file and sets up the grid */
void readFile(const char *fileName) {
  int numCells;
  int row, column;

  FILE *file = fopen(fileName, "r");
  fscanf(file, "%d", &numCells);

  for (int i = 0; i < numCells; i++) {
    fscanf(file, "%d %d", &row, &column);
    grid[row][column] = 0;
  }
  fclose(file);
}

/* Prints the cell grid */
void printGrid() {
  int row, col;

  printf("*");
  for (col = 0; col < width; col++) {
    printf("-");
  }
  printf("*\n");

  for (row = 0; row < height; row++) {
    printf("|");
    for (col = 0; col < width; col++) {
      int value = grid[row][col];
      if (value == -1) {
        /* Cell is dead */
        printf(" ");
      } else if (value >= 0 && value <= 9) {
        printf("%d", value);
      } else {
        printf("X");
      }
    }
    printf("|\n");
  }

  printf("*");
  for (col = 0; col < width; col++) {
    printf("-");
  }
  printf("*\n");
}

/* Calculates the number of live cells adjacent to the given position */
int numNeighbours(int row, int column) {
  int n = 0;

  /* We will consider horizontal, vertical and diagonal neighbours */
  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = column - 1; j <= column + 1; j++) {
      if (i == row && j == column) {
        /* This is the original cell. Don't include this cell in neighbour calculations */
        continue;
      }
      if (i >= 0 && i < height && j >= 0 && j < width) {
        if (grid[i][j] >= 0) {
          n++;
        }
      }
    }
  }
  return n;
}

/* Performs one step of execution
   If a repetition is detected, returns the period. */
int step() {
  int row, col;
  for (row = 0; row < height; row++) {
    for (col = 0; col < width; col++) {

      int neighbours = numNeighbours(row, col);

      if (grid[row][col] == -1) {
        /* Cell is dead */

        if (neighbours == 3) {
          /* This cell will come to life */
          grid2[row][col] = 0;
        } else {
          grid2[row][col] = -1;
        }
      } else {
        /* Cell is live */

        if (neighbours < 2 || neighbours > 3) {
          /* This cell will die */
          grid2[row][col] = -1;
        } else {
          /* This cell will remain live
           We increment the cell's age here */
          grid2[row][col] = grid[row][col] + 1;
        }
      }
    }
  }

  int repetition = 1;
  for (row = 0; row < height; row++) {
    for (col = 0; col < width; col++) {
      int value1 = grid[row][col];
      int value2 = grid2[row][col];

      if (value1 == -1 && value2 != -1) {
        repetition = 0;
      }
      if (value1 != -1 && value2 == -1) {
        repetition = 0;
      }
    }
  }

  /* After all cells are computed, copy the second grid into the first one */
  for (row = 0; row < height; row++) {
    for (col = 0; col < width; col++) {
      grid[row][col] = grid2[row][col];
    }
  }

  return repetition;
}

/* Executes several steps and prints the grid after each step */
void execute(int generations) {
  for (int n = 0; n < generations; n++) {
    int repetition = step();
    printf("\n");
    printGrid();
    printf("\n");

    if (repetition) {
      printf("Period detected (%d): exiting\n", repetition);
      exit(0);
    }
  }
}

int main(const char **argv) {
  const char *fileName = argv[1];
  width = atoi(argv[2]);
  height = atoi(argv[3]);
  int generations = atoi(argv[4]);

  /* Initialize the grid */
  resetGrid();

  /* Read input file */
  readFile(fileName);

  printGrid();
  printf("\n");

  /* Start executing */
  execute(generations);

  printf("Finished\n");

  return 0;
}
