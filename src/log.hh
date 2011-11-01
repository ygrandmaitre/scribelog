#ifndef LOG_HH
# define LOG_HH

# include <string>
# include <fstream>
# include "configparser.hh"

class Log
{
  public:
    Log(const ConfigParser::t_MapConfig& config);
    ~Log();

    bool write(const char* data, ssize_t size);
  private:
    bool open();

    ConfigParser::t_MapConfig config_;
    int fd_;
};

#endif // LOG_HH
