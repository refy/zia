#include	<iostream>
#include	<sstream>
#include	<string>
#include	<iomanip>
#include	"Logger.hpp"

#if defined (_WIN32)
#else
# include	<ctime>
#endif

Logger::Logger(const std::string & msgFormat, bool debug, const std::string & logFile)
  : _debug(debug), _msgFormat(msgFormat), _logFile(logFile)
{
  this->_stream.open(this->_logFile.c_str(), std::ofstream::out | std::fstream::app);
  if (!this->_stream.is_open())
    this->_debug = true;
  this->LogInfo("--- Start ---");
}

Logger::~Logger()
{
  this->LogInfo("--- End ---");
  this->_stream.close();
}

const std::string	Logger::getMsgFormated(const std::string & msg, const std::string & type)
{
  std::string	res = this->_msgFormat;
  size_t	pos;
  std::string	date;

#if defined	(_WIN32)
#else
  time_t		timestamp;
  struct tm		*t;
  std::ostringstream	c;

  timestamp = time(NULL);
  t = gmtime(&timestamp);
  c << (1900 + t->tm_year) << "-" << std::setw(2) << std::setfill('0') <<(t->tm_mon + 1);
  c << "-" << std::setw(2) << std::setfill('0') << t->tm_mday << " " << std::setw(2) << std::setfill('0') << t->tm_hour;
  c << ":" << std::setw(2) << std::setfill('0') << t->tm_min << ":" << std::setw(2) << std::setfill('0') << t->tm_sec;
  date = c.str();
#endif

  if ((pos = res.find("%(message)")) != std::string::npos)
    res.replace(pos, 10, msg);
  if ((pos = res.find("%(type)")) != std::string::npos)
    res.replace(pos, 7, type);
  if ((pos = res.find("%(time)")) != std::string::npos)
    res.replace(pos, 7, date);
  return res;
}

void	Logger::LogError(const std::string & msg)
{
  std::string	tmp = msg;
  std::string	res;
  std::string	line;
  size_t	pos;

  while ((pos = tmp.find("\n")) != std::string::npos)
    {
      line = tmp.substr(0, pos + 1);
      tmp.erase(0, pos + 1);
      res += this->getMsgFormated(line, "ERROR");
    }
  if (!tmp.empty())
    res += this->getMsgFormated(tmp, "ERROR");
  if (res[res.size() - 1] == '\n')
    res.erase(res.size() - 1, 1);
  if (this->_debug)
    std::cout << res << std::endl;
  if (this->_stream.is_open() && this->_stream.good())
    this->_stream << res << std::endl;
}

void	Logger::LogDebug(const std::string & msg)
{
  std::string	tmp = msg;
  std::string	res;
  std::string	line;
  size_t	pos;

  while ((pos = tmp.find("\n")) != std::string::npos)
    {
      line = tmp.substr(0, pos + 1);
      tmp.erase(0, pos + 1);
      res += this->getMsgFormated(line, "DEBUG");
    }
  if (!tmp.empty())
    res += this->getMsgFormated(tmp, "DEBUG");
  if (res[res.size() - 1] == '\n')
    res.erase(res.size() - 1, 1);
  if (this->_debug)
    std::cout << res << std::endl;
  if (this->_stream.is_open() && this->_stream.good())
    this->_stream << res << std::endl;
}

void	Logger::LogInfo(const std::string & msg)
{
  std::string	tmp = msg;
  std::string	res;
  std::string	line;
  size_t	pos;

  while ((pos = tmp.find("\n")) != std::string::npos)
    {
      line = tmp.substr(0, pos + 1);
      tmp.erase(0, pos + 1);
      res += this->getMsgFormated(line, "INFO");
    }
  if (!tmp.empty())
    res += this->getMsgFormated(tmp, "INFO");
  if (res[res.size() - 1] == '\n')
    res.erase(res.size() - 1, 1);
  if (this->_debug)
    std::cout << res << std::endl;
  if (this->_stream.is_open() && this->_stream.good())
    this->_stream << res << std::endl;
}
