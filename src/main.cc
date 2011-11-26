#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/select.h>
#include "log.hh"

static const unsigned int c_buff_size = 4096;

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::clog << "Erreur missing argument" << std::endl;
    return 1;
  }

  ConfigParser parser;
  ConfigParser::t_MapConfig keys;

  if (!parser.parse ("/home/riki/projet/scribelog/test.cfg" /*std::string(argv[1])*/, keys))
  {
    std::clog << "Bad config file" << std::endl;
    return 2;
  }

  Log log(keys);
  char buff[c_buff_size];
  ssize_t n_bytes_read = 0;

  while(true)
  {
    n_bytes_read = read(STDIN_FILENO, buff, sizeof(buff));
    if (n_bytes_read == 0)
      return 0;
    std::cout << "nb read  " << n_bytes_read << ' ' << buff << std::endl;
    log.write(buff, n_bytes_read);
  }
}
