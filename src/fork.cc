/**
 ** \file fork.hh
 ** \brief Declaration of Fork.
 */

#include <sysexits.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>

#include "fork.hh"


Fork::Fork ()
{
  if ((pid_ = fork ()) < 0)
    {
      perror ("fork failed");
      exit (EX_OSERR);
    }
}

static char**
list_arg_to_argv (const std::list<std::string>& list_arg)
{
  unsigned int size = list_arg.size () + 1;

  char ** argv = new char * [size];

  unsigned int i = 0;
  for (std::list<std::string>::const_iterator it = list_arg.begin ();
       i < (size - 1) && (it != list_arg.end ());
       ++i, ++it)
    argv[i] = strdup (it->c_str ());

  argv[size - 1] = NULL;

  return argv;
}

int
Fork::fork_exec (const std::string& cmd,
		 std::list<std::string>& list_arg,
		 bool wait_child)
{
  // Fork the process.
  Fork f;

  if (f.is_child ())
    execvp (cmd.c_str (), list_arg_to_argv (list_arg));

  if (wait_child)
    {
      int status;

      if (wait (&status) > 0 && WIFEXITED (status))
        return WEXITSTATUS (status);
      else
        return -1;
    }
  else
    return f.pid_get ();
}
