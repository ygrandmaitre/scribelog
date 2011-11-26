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
    std::list<std::unique_ptr<std::thread> > compress_threads_;
};

#endif // LOG_HH
