/*
 * Escriba un programa en C para Linux que reciba los siguientes argumentos:
 *
 * Un número N en base 10 que indica cuántas palabras se deben imprimir Un
 * número L en base 10 que indica a cuántos caracteres se va a truncar cada
 * palabra Palabras (un número indeterminado de ellas, mayor o igual que
 * cero) El programa debe imprimir las N últimas palabras, una por línea,
 * en su orden de aparición en los argumentos. Si N es mayor al número de
 * argumentos disponibles, se imprimirán todos.
 *
 * Cada palabra tiene que estar truncada a la longitud L. Si una palabra ya
 * tiene una longitud menor que L, se imprimirá tal cual.
 *
 * El programa debe fallar si no se proporcionan N y L. También debe fallar
 * si no son números o son negativos (sí pueden ser cero). Cuando el
 * programa falla, el proceso debe terminar con un estado de fallo.
 */


#include <ctype.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
str_to_int (char *str, int base)
{
  char *end = NULL;
  int num = strtol (str, &end, base);
  if (*end != '\0' || end == str)
    {
      //esta igualdad comprueba que si strtol vuelve al principio porque detecta que no hay un digito, se salga
      fprintf (stderr, "error: bad value \"%s\"\n", str);
      exit (EXIT_FAILURE);
    }
  return num;
}

int
val_num (char *str, int base)
{
  int n_validado = str_to_int (str, base);
  if (n_validado < 0)
    {
      fprintf (stderr, "error: bad value \"%s\"\n", str);
      exit (EXIT_FAILURE);
    }
  return n_validado;
}

char *
truncar_argumento (char *arg, int longitud)
{
  char *arg_truncado = arg;
  if (longitud > strlen (arg))
    {
      arg_truncado = arg;
    }
  else
    {
      arg_truncado[longitud] = '\0';
    }
  return arg_truncado;
}


void
imprimir_truncados (int n, int final, int trunque, char **argv)
{
  int inicio_palabras = 3;
  int cuenta_palabras = final - inicio_palabras;
  int primero;
  if (n >= cuenta_palabras)
    {
      primero = inicio_palabras;
      //si la n es mayor que el numero de pals, imprime todas(empieza desde el inicio->la primera pal)
    }
  else
    {
      primero = final - n;
      //si no, empiezas desde final - n ->ajuste de indice relativo
    }


  for (int i = primero; i <= final - 1; i++)
    //final = argc - 1
    {
      char *arg_truncado = truncar_argumento (argv[i], trunque);
      printf ("%s\n", arg_truncado);
    }
}


int
main (int argc, char *argv[])
{
  int base_10 = 10;
  if (argc < 2)
    {
      fprintf (stderr, "usage: necho N L [word ...]\n");
      exit (EXIT_FAILURE);
    }


  int n = val_num (argv[1], base_10);

  int l = val_num (argv[2], base_10);

  imprimir_truncados (n, argc, l, argv);

  exit (EXIT_SUCCESS);
}
