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
#ifndef CONFIGPARSER_HH
# define CONFIGPARSER_HH

# include <string>
# include <fstream>
# include <map>

  /*!
  ** @class ConfigParser
  ** Parse a config file and stock config information on a map
  ** The format is:
  ** <section 1>: <info>
  ** <section 2>: <info>
  **
  ** Exemple:
  ** file: my_log.log
  ** foo: bar
  */
class ConfigParser
{
public:
    typedef std::map<std::string /*section*/, std::string /*info*/> t_MapConfig;

    ConfigParser();
    ~ConfigParser();

    /*!
      ** Parse the config file
      **
      ** @param filename the of the config file
      ** @param config Results. The map with informtions extract from the Config
      ** file
      */
    bool parse(const std::string& filename, t_MapConfig& config);

  private:
    bool open(const std::string& filename);
    void close();
    bool parseLine(t_MapConfig& config);

    std::ifstream file_;
};

#endif // CONFIGPARSER_HH
