/**
 * Encontrar una distribucion de n reinas en un tablero de ajedrez
 * de n x n de tal manera que no se ataquen, esto quiere decir que
 * no pueden encontrarse 2 reinas en la misma columna, fila o diagonal.
 *
 * En 1848 fue propuesto para n = 8 en un trabajo anonimo atribuido despues
 * a Max Bezzel. Gauss encontro 72 posibles soluciones y Glaisher probo la
 * existencia de 92 soluciones.
 *
 * PSEUDOCODIGO
 *
 * Funcion solve(board, row, col, N):
 *    Si en la columna cruzamos con una reina:
 *      regrasamos false
 *
 *    Si en la diagonal invertida encontramos una reina:
 *      regresamos false
 *
 *    Si en la diagonal encontramos una reina:
 *      regresamos false
 *
 *
 * Funcion backtrack(solutions, board, row, N):
 *    Si row = 9:
 *      agregamos solucion
 *      regresamos false
 *    end Si
 *
 *    For i = 0 hasta N:
 *      Si(solve(board, row, i, N)):
 *        board[row][i] = 'Q'
 *
 *        Si(backtrack(solutions, board, row + 1,  N)):
 *          regresamos true
 *        end Si
 *
 *        // eliminamos
 *        board[row][i] = ''
 *      end Si
 *    end For
 *
 *    return false
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 8
#define MAX_SOLUTIONS 92

typedef struct Solutions
{
  char **solutions;
  int top;
  int cap;
} Solutions;

Solutions *Solutions_create(int n)
{
  Solutions *s = malloc(sizeof(Solutions));
  if (s)
  {
    s->solutions = malloc(n * sizeof(char *));
    if (s->solutions == NULL)
    {
      free(s);
      return NULL;
    }
    s->top = 0;
    s->cap = n;
  }
  return s;
}

void Solutions_destroy(Solutions *this)
{
  for (int i = 0; i < this->top; i++)
  {
    free(this->solutions[i]);
  }

  free(this->solutions);
  free(this);
}

void Solutions_append(Solutions *this, char *solution)
{
  if (this->top == this->cap)
  {
    puts("Error! Mas soluciones encontradas que las esperadas");
    Solutions_destroy(this);
    exit(1);
  }
  this->solutions[this->top] = solution;
  this->top++;
}

bool solve(char board[N][N], int row, int col, int n)
{
  for (int i = 0; i < row; i++)
  {
    if (board[i][col] == 'Q')
      return false;
  }

  for (int i = 1; row - i >= 0 && col - i >= 0; i++)
  {
    if (board[row - i][col - i] == 'Q')
      return false;
  }

  for (int i = 1; row - i >= 0 && col + i < n; i++)
  {
    if (board[row - i][col + i] == 'Q')
      return false;
  }

  return true;
}

bool backtrack(Solutions *solutions, char board[N][N], int row, int n)
{
  // caso base
  if (row == n)
  {
    char *solution = malloc(n * n * sizeof(char));
    memcpy(solution, board, n * n * sizeof(char));
    Solutions_append(solutions, solution);
    return false;
  }

  for (int i = 0; i < n; i++)
  {
    if (solve(board, row, i, n))
    {
      board[row][i] = 'Q';
      backtrack(solutions, board, row + 1, n);
      board[row][i] = '_';
    }
  }

  return false;
}

int main()
{
  Solutions *solutions = Solutions_create(MAX_SOLUTIONS);
  char board[N][N];

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      board[i][j] = '_';
    }
  }

  // llamamos a backtrack
  backtrack(solutions, board, 0, N);

  // Mostrar soluciones
  printf("Total de soluciones encontradas: %d\n", solutions->top);
  for (int k = 0; k < solutions->top; k++)
  {
    printf("Solución %d:\n", k + 1);
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        printf("%c ", solutions->solutions[k][i * N + j]);
      }
      printf("\n");
    }
    printf("\n");
  }

  Solutions_destroy(solutions);

  return 0;
}