#include	<iostream>
#include	<string>
#include	"Logger.hpp"

Logger::Logger(const std::string & msgFormat, bool debug, const std::string & logFile)
  : _debug(debug), _msgFormat(msgFormat), _logFile(logFile)
{
  this->_stream.open(this->_logFile.c_str(), std::ofstream::out | std::fstream::app);
  if (!this->_stream.is_open())
    this->_debug = true;
}

Logger::~Logger()
{
  this->_stream.close();
}

const std::string	Logger::getMsgFormated(const std::string & msg, const std::string & type)
{
  std::string	res = this->_msgFormat;
  size_t	pos;

  if ((pos = res.find("%(message)")) != std::string::npos)
    res.replace(pos, 10, msg);
  if ((pos = res.find("%(type)")) != std::string::npos)
    res.replace(pos, 7, type);
  return res;
}

void	Logger::LogError(const std::string & msg)
{
  std::string	res = this->getMsgFormated(msg, "ERROR");

  if (this->_debug)
    std::cout << res << std::endl;
  if (this->_stream.is_open() && this->_stream.good())
    this->_stream << res << std::endl;
}

void	Logger::LogDebug(const std::string & msg)
{
  std::string	res = this->getMsgFormated(msg, "DEBUG");

  if (this->_debug)
    std::cout << res << std::endl;
  if (this->_stream.is_open() && this->_stream.good())
    this->_stream << res << std::endl;
}

void	Logger::LogInfo(const std::string & msg)
{
  std::string	res = this->getMsgFormated(msg, "INFO");

  if (this->_debug)
    std::cout << res << std::endl;
  if (this->_stream.is_open() && this->_stream.good())
    this->_stream << res << std::endl;
}
