
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void
buscar_palabra_en_fichero (char *palabra, char *ruta)
{
  execl ("/bin/fgrep", "buscar", palabra, ruta, NULL);
  exit (EXIT_SUCCESS);
}

int
main (int argc, char *argv[])
{

  argc -= 1;
  argv += 1;
  char *ruta;
  char *palabra;
  int i = 0;
  pid_t pid;
  if (argc % 2 != 0)
    {
      fprintf (stderr, "error: bad number of arguments\n");
      exit (EXIT_FAILURE);
    }


  for (i = 0; i < argc; i += 2)
    {
      ruta = argv[i];
      palabra = argv[i + 1];
      pid = fork ();

      switch (pid)
	{
	case -1:
	  fprintf (stderr, "error del fork\n");
	  exit (EXIT_FAILURE);
	case 0:
	  buscar_palabra_en_fichero (palabra, ruta);
	default:
	  break;
	}
    }
}
