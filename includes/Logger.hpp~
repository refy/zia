#ifndef		__LOGGER_HPP__
#define		__LOGGER_HPP__

#include	<fstream>
#include	"ILogger.hpp"

// ML		21/01/14 - 16:00
//
// Different message type :
//  %(type) : print the message type (ERROR, DEBUG, INFO)
//  %(message) : print the message.
//  %(time) : print the timestamp (not included)

class	Logger : public apimeal::ILogger
{
private:
  std::ofstream	_stream;
  bool		_debug;
  std::string	_msgFormat;
  std::string	_logFile;

public:
  Logger(const std::string & msgFormat = "%(type) : %(message)", bool debug = false, const std::string & logFile = "apimeal-zia.log");
  ~Logger();

public:
  const std::string	getMsgFormated(const std::string & msg, const std::string & type);
  virtual void		LogError(const std::string & msg);
  virtual void		LogDebug(const std::string & msg);
  virtual void		LogInfo(const std::string & msg);
};

#endif
