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
#include <cstdlib>

#include "configparser.hh"

ConfigParser::ConfigParser()
{
}

ConfigParser::~ConfigParser()
{
  close();
}

bool
ConfigParser::parse(const std::string &filename, t_MapConfig &config)
{
  if (!open(filename))
    return false;

  bool ret = false;
  while (!file_.eof())
    ret = parseLine(config);

  close();
  return ret;
}

void
ConfigParser::close()
{
  file_.close();
}

bool
ConfigParser::open(const std::string &filename)
{
  file_.open(filename.c_str(), std::ios::in);

  if (!file_)
  {
    std::clog << "Can't open the config file: " << filename << std::endl;
    return false;
  }

  return true;
}

static void removeComments(std::string& line)
{
  size_t pos = line.find_first_of('#');
  if (pos == std::string::npos)
    return;

  line = line.substr(0, pos);
}

static void eatWitheSpaces(std::string& str, const char* delim = " \t\n\v\f\r")
{
  size_t pos = str.find_first_not_of(delim);

  if (pos == std::string::npos)
  {
    str = std::string("");
    return;
  }

  str = str.substr(pos);
}

static std::string getToken(std::string& str, const char* delim)
{
  size_t pos = str.find_first_of(delim);

  if (pos == std::string::npos)
  {
    std::string token(str);
    str = std::string("");
    return token;
  }

  std::string token = str.substr(0,pos);
  str = str.substr(pos);
  return token;
}

static std::string trim(std::string& str, const char* delim)
{
  size_t pos = str.find_last_not_of(delim);

  if (pos == std::string::npos)
  {
    str = "";
    return str;
  }

  str = str.substr(0, pos + 1);
  return str;
}

bool
ConfigParser::parseLine(t_MapConfig &config)
{
  std::string line;
  std::getline(file_, line);

  if (file_.eof())
    return true;

  removeComments(line);
  if (line.empty())
    return true;
  eatWitheSpaces(line);
  std::string key = getToken(line, ":");
  trim(key, " ");
  eatWitheSpaces(line, ":");
  eatWitheSpaces(line);
  std::string value = getToken(line, "\n");
  trim(value, " ");

  config[key] = value;

  return true;
}
