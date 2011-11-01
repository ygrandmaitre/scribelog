#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <ctime>
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

  ::write(fd_, data, size);

  return true;
}

bool
Log::open()
{
  const auto it = config_.find("file");
  if (it == config_.end())
  {
    std::clog << "no file found in config" << std::endl;
    return false;
  }

  // Get date
  auto ts = ::time(0);
  struct ::tm local_tm;
  ::localtime_r(&ts, &local_tm);
  char buffer[128];
  auto size = strftime(buffer, sizeof (buffer), "%Y%m%d-%T", &local_tm);
  std::string date(buffer, size);

  int fd = ::open((date + "-" + it->second).c_str(),
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
