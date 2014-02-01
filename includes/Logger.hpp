#ifndef		__LOGGER_HPP__
#define		__LOGGER_HPP__

#include	<fstream>
#include	"ILogger.hpp"

class	Logger : public apimeal::ILogger
{
private:
  static Logger*	_singleton;
  std::ofstream		_stream;
  bool			_debug;
  std::string		_msgFormat;
  std::string		_logFile;

private:
  Logger();
  Logger(const std::string & msgFormat = "%(type) : %(message)", bool debug = false, const std::string & logFile = "apimeal-zia.log");
  ~Logger();

private:
  const std::string	getMsgFormated(const std::string & msg, const std::string & type);

public:
  static Logger*	getInstance(const std::string & msgFormat = "%(type) : %(message)", bool debug = false, const std::string & logFile = "apimeal-zia.log");
  static void		kill();

public:
  virtual void		LogError(const std::string & msg);
  virtual void		LogDebug(const std::string & msg);
  virtual void		LogInfo(const std::string & msg);
};

#endif
