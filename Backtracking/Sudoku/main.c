
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Reglas del sudoku
 * - El tablero es una cuadrícula de 9 filas y 9 columnas.
 * - Cada casilla debe contener un número del 1 al 9.
 * - No se puede repetir ningún número en una fila, columna o bloque.
 * - El juego termina cuando todas las casillas están llenas con los números correctos
 */

void print_vertical_lines(int cols)
{
  for (int i = 0; i < cols * 2 + 7; i++)
  {
    printf("-");
  }
  puts("");
}

void pretty_print(int sudoku[9][9], int rows, int cols)
{
  print_vertical_lines(rows);

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (j % 3 == 0)
        printf("| ");
      printf("%d ", sudoku[i][j]);
    }
    printf("|");
    puts("");

    if ((i + 1) % 3 == 0)
    {
      print_vertical_lines(rows);
    }
  }
}

int solve(int sudoku[9][9], int test_number, int row, int col)
{
  bool check = false;

  // verificamos si esta repetido en la fila
  for (int i = 0; i < 9; i++)
  {
    if (sudoku[row][i] == test_number || sudoku[i][col] == test_number)
      return false;
  }

  // obtenemos el bloque 3x3 correspondiente
  int start_row = (row / 3) * 3;
  int start_col = (col / 3) * 3;

  for (int i = start_row; i < start_row + 3; i++)
  {
    for (int j = start_col; j < start_col + 3; j++)
    {
      if (sudoku[i][j] == test_number)
        return false;
    }
  }

  return true;
}

bool backtrack(int sudoku[9][9], int row, int col)
{
  if (row == 9)
  {
    pretty_print(sudoku, 9, 9);
    return true;
  }

  if (col == 9)
    return backtrack(sudoku, row + 1, 0);

  if (sudoku[row][col] != 0)
    return backtrack(sudoku, row, col + 1);

  for (int i = 1; i <= 9; i++)
  {
    if (solve(sudoku, i, row, col))
    {
      sudoku[row][col] = i;

      if (backtrack(sudoku, row, col + 1))
        return true;

      sudoku[row][col] = 0;
    }
  }

  return false;
}

int main()
{
  // creamos la matriz para el sudoku
  int sudoku[9][9] = {
      {0, 3, 0, 7, 0, 0, 0, 2, 0},
      {6, 0, 0, 0, 0, 0, 0, 5, 0},
      {5, 0, 0, 0, 4, 9, 0, 0, 7},

      {1, 0, 0, 0, 5, 8, 0, 0, 4},
      {0, 0, 0, 0, 0, 2, 0, 0, 6},
      {0, 0, 0, 1, 0, 0, 2, 0, 0},

      {3, 0, 0, 5, 0, 1, 0, 0, 0},
      {0, 0, 7, 0, 3, 0, 0, 0, 2},
      {0, 4, 0, 0, 6, 0, 5, 0, 0},
  };

  pretty_print(sudoku, 9, 9);

  backtrack(sudoku, 0, 0);

  return 0;
}