#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

typedef struct
{
  pid_t pid_killer;
  int pid_victim;
  int status;
} ProcessTuple;

int
check_pid (char *str, int base)
{
  char *end = NULL;
  int num = strtol (str, &end, base);
  if (*end != '\0' || end == str || num <= 0)
    {
      fprintf (stderr, "usage: killprocs pid [pid ...]\n");
      exit (EXIT_FAILURE);
    }
  return num;
}

int *
argv_to_pids (char **argv, int top)
{
  int i;
  int base = 10;
  int pid;
  int *arr_pids = malloc (top * sizeof (int));
  if (!arr_pids)
    {
      fprintf (stderr, "malloc error\n");
      free (arr_pids);
      exit (EXIT_FAILURE);
    }
  for (i = 0; i < top; i++)
    {
      pid = check_pid (argv[i], base);
      arr_pids[i] = pid;
    }
  return arr_pids;
}

void
usage (void)
{
  fprintf (stderr, "usage: killprocs pid [pid ...]\n");
  exit (EXIT_FAILURE);
}

void
kill_pid (int pid)
{
  char pidchar[32];		// los pids seran de 32 chars.
  snprintf (pidchar, sizeof (pidchar), "%d", pid);	//execl solo admite char como argumentos; snprintf() convierte los (int)pids a char
  //printf("matando al proceso : %d\n", pid);
  execl ("/bin/kill", "mykill", "-9", pidchar, NULL);
  exit (EXIT_SUCCESS);
}

void
wait_children (int *arr, int num_pids, ProcessTuple *tupla_kv)
{
  int i;
  for (i = 0; i < num_pids; i++)
    {
      int status;
      pid_t children_finished = waitpid (-1, &status, 0);
      char *killed_victim = NULL;
      if (children_finished == -1)
	{
	  fprintf (stderr, "waitpid error\n");
	}
      int idx = -1;
      for (int j = 0; j < num_pids; j++)
	{
	  if (tupla_kv[j].pid_killer == children_finished)
	    {
	      idx = j;
	      break;
	    }
	}
      int code = WEXITSTATUS (status);
      if ((WIFEXITED (status) && WEXITSTATUS (status) == 0)
	  && killed_victim != NULL)
	{
	  code = WEXITSTATUS (status);
	  tupla_kv[idx].status = code;
	}
      if (code != 0)
	{
	  fprintf (stderr, "ERROR: can't kill PID %d\n",
		   tupla_kv[idx].pid_victim);
	}
      else if (WIFSIGNALED (status))
	{
	  tupla_kv[idx].status = WTERMSIG (status);
	  fprintf (stderr, "ERROR: can't kill PID %d\n",
		   tupla_kv[idx].pid_victim);
	}
    }
  free (tupla_kv);
}


void
kill_procs (int *arr, int num_pids)
{
  ProcessTuple *tupla_kv = malloc (num_pids * sizeof (ProcessTuple));
  int i;
  pid_t pid;
  for (i = 0; i < num_pids; i++)
    {
      pid = fork ();
      if (pid == -1)
	{
	  fprintf (stderr, "fork error\n");
	  free (arr);
	  free (tupla_kv);
	  exit (EXIT_FAILURE);
	}

      if (pid == 0)
	{
	  pid_t pid_prueba = getpid ();
	  tupla_kv[i].pid_killer = pid_prueba;
	  tupla_kv[i].pid_victim = arr[i];
	  kill_pid (tupla_kv[i].pid_victim);
	}
      tupla_kv[i].pid_killer = pid;
      tupla_kv[i].pid_victim = arr[i];
      tupla_kv[i].status = -1;
    }
  wait_children (arr, num_pids, tupla_kv);
}


int
main (int argc, char *argv[])
{
  argc--;
  argv++;
  int *array_pids;
  if (argc == 0)
    {
      usage ();
    }
  //array de PIDS validados.
  array_pids = argv_to_pids (argv, argc);
  kill_procs (array_pids, argc);

  free (array_pids);
  exit (EXIT_SUCCESS);
}
