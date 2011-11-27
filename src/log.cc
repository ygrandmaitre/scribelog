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
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>
#include <future>
#include <zlib.h>

#include "fork.hh"
#include "log.hh"

Log::Log(const ConfigParser::t_MapConfig& config)
: config_(config),
  fd_(-1)
{
}

Log::~Log()
{
}

bool
Log::write(const char* data, ssize_t size)
{
  if (fd_ == -1)
  {
    if (!open())
      return false;
  }

  auto it_delay = config_.find("delay");
  if (it_delay != config_.end())
  {
    //check delay
    auto now = std::chrono::high_resolution_clock::now();
    if (now - begin_ >= std::chrono::seconds(
                                            std::atoi(it_delay->second.c_str())))
    {
      close(fd_);
      // Compress the file in a fork process
      Fork f;

      if (f.is_child ())
        compress(filename_);
      if (!open())
        return false;
    }
  }

  ::write(fd_, data, size);

  return true;
}

void
Log::compress(const std::string& filename)
{
  std::clog << "debut" << std::endl;
  int fd = ::open(filename.c_str(), O_RDONLY, 0666);
  // FIXME get the compression level in config file
  gzFile gz = gzopen((filename + ".gz").c_str(), "wb5");
  if (gz == 0)
  {
    std::clog << "Couldn't create the .gz file: " << filename << ".gz" << std::endl;
  }
  else
  {
    char buffer[64 * 1024];
    int32_t size = ::read(fd, buffer, sizeof(buffer));

    while (size > 0)
    {
      if(gzwrite(gz, buffer, size) == 0)
      {
        std::clog << "gzwrite error" << std::endl;
      }
      size = ::read(fd, buffer, sizeof(buffer));
    }
    gzclose(gz);
    ::close(fd);
  }
  exit(0);
}

bool
Log::open()
{
  begin_ = std::chrono::high_resolution_clock::now();

  const auto it = config_.find("file");
  if (it == config_.end())
  {
    std::clog << "no file found in config" << std::endl;
    return false;
  }

  // Get date may be see std::put_time and std::localtime
  auto ts = ::time(0);
  struct ::tm local_tm;
  ::localtime_r(&ts, &local_tm);
  char buffer[128];
  auto size = strftime(buffer, sizeof (buffer), "%Y%m%d-%T", &local_tm);
  std::string date(buffer, size);

  // FIXME use stringstream
  filename_ = date + "-" + it->second;

  int fd = ::open(filename_.c_str(),
  O_WRONLY | O_CREAT | O_EXCL | O_LARGEFILE,
  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

  if (fd == -1)
  {
    std::clog << "could'n open the file: " << it->second << std::endl;
    return false;
  }

  fd_ = fd;

  return true;
}
