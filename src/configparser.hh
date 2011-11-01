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
