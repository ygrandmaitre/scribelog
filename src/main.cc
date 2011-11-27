// Copyright (C) 2011 Yann Grandmaitre
//
// This file is part of scribelog
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
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

  if (!parser.parse (std::string(argv[1]), keys))
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
    log.write(buff, n_bytes_read);
  }
}
