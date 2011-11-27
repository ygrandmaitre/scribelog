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
#ifndef LOG_HH
# define LOG_HH

# include <list>
# include <string>
# include <fstream>
# include <chrono>
# include <mutex>
# include <thread>
# include "configparser.hh"

class Log
{
  public:
    Log(const ConfigParser::t_MapConfig& config);
    ~Log();

    bool write(const char* data, ssize_t size);
  private:
    bool open();
    void compress(const std::string& filename);

    ConfigParser::t_MapConfig config_;
    int fd_;
    std::string filename_;
    std::chrono::high_resolution_clock::time_point begin_;
};

#endif // LOG_HH
