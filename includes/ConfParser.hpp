#ifndef		__CONFPARSER_HPP__
#define		__CONFPARSER_HPP__

#include	<map>
#include	<vector>
#include	<string>
#include	"Version.hpp"
#include	"Error.hpp"

class	ConfParser
{
private:
  std::map<std::string, std::string>	_xml;
  std::string				_file;
  std::map<std::string, std::string>	_search;
  std::vector<std::string>		_modules;

public:
  ConfParser(const std::string & file = "");
  ~ConfParser();

private:
  void			getContent(apimeal::Error & error);
  bool			cleanLine(std::string & line, bool comment);
  const std::string	parseLine(const std::string & line, int s);
  void			fillContent();
  void			fillModules();

public:
  void					initialize(apimeal::Error & error);
  const std::string &			getApiName();
  int					getPort();
  const std::string &			getApiVersionMin();
  const std::vector<std::string> &	getModulesPath() const;
  const std::string &			getLoggerFile();
  const std::string &			getLoggerFormat();
};

#endif
