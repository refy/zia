#ifndef		__CONFPARSER_HPP__
#define		__CONFPARSER_HPP__

#include	<map>
#include	<vector>
#include	<string>
#include	"Version.hpp"
#include	"Error.hpp"

class	ConfParser
{
    
    ConfParser();
    std::map<std::string, std::string>	_xml;
    std::string				_file;
    std::map<std::string, std::string>	_search;
    std::vector<std::string>		_modules;
    std::map<std::string, std::string>	_docs;
    std::vector<std::string>		_hosts;
    std::vector<int>        _ports;
    
    void			getContent();
    bool			cleanLine(std::string & line, bool comment);
    const std::string	parseLine(const std::string & line, int s);
    void			fillContent();
    void			fillModules();
    void			fillWebsite();
    void            fillPorts();
    static          ConfParser *_singleton;
    
public:
    ConfParser(apimeal::Error & e, const std::string & file = "");
    ~ConfParser();
    
    static ConfParser *getInstance();
    void setFile(const std::string &fileName);
    void					initialize(apimeal::Error & error);
    const std::string &			getApiName();
    std::vector<int> getPorts();
//    int					getPort();
    const std::string &			getApiVersionMin();
    const std::vector<std::string> &	getModulesPath() const;
    const std::string &			getLoggerFile();
    const std::string &			getLoggerFormat();
    const std::vector<std::string> &	getVirtualHost();
    const std::string &			getDocumentRoot(const std::string & virtual_host);
};

#endif
