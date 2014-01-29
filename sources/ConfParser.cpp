#include	<fstream>
#include	<sstream>
#include	<iostream>
#include	"ConfParser.hpp"

ConfParser::ConfParser(const std::string & file)
  : _file(file)
{
  this->_search["/Zia/Api/name"] = "apimeal";
  this->_search["/Zia/Api/min_authorized_version"] = "0.1";
  this->_search["/Zia/Logger_info/log_file"] = "apimeal-zia.log";
  this->_search["/Zia/Logger_info/format"] = "%(type) : %(message)";
  this->_search["/Zia/Server_info/port"] = "80";
  this->_docs["NO VIRTUAL HOST"] = "";
}

ConfParser::~ConfParser()
{}

void					ConfParser::initialize(apimeal::Error & error)
{
  this->getContent(error);
}

bool					ConfParser::cleanLine(std::string & line, bool comment)
{
  size_t	beg = 0;
  size_t	end;

  if (line.find("<?xml version=") != std::string::npos)
    line.clear();
  while (line[0] == ' ' || line[0] == '\t')
    line.erase(0, 1);
  if ((beg = line.find("<!--")) != std::string::npos || comment == true)
    {
      if (comment == true)
	beg = 0;
      if ((end = line.find("-->", beg)) != std::string::npos)
	{
	  end += 3;
	  line.erase(beg, (end - beg));
	  return (this->cleanLine(line, false));
	}
      line.erase(beg, line.size() - beg);
      return true;
    }
  if ((beg = line.find("<", 0)) != std::string::npos)
    line.erase(0, beg);
  if ((beg = line.rfind(">", line.size() - 1)) != std::string::npos)
    line.erase(beg + 1, line.size() - (beg + 1));
  return false;
}

const std::string			ConfParser::parseLine(const std::string & line, int s)
{
  std::string	res;
  size_t	beg = 0;
  size_t	end = 0;

  if (s == 0)
    {
      if ((end = line.find(">")) != std::string::npos)
	res = line.substr(1, (end - 1));
    }
  else
    {
      if ((beg = line.find(">")) != std::string::npos)
	{
	  beg += 1;
	  if ((end = line.find("<", beg)) != std::string::npos)
	    res = line.substr(beg, (end - beg));
	}
    }
  return res;
}

void					ConfParser::getContent(apimeal::Error & error)
{
  std::ifstream	file;
  std::string	up;
  std::string	key;
  std::string	value;
  bool		comment = false;
  size_t	s;

  file.open(this->_file.c_str());
  if (file.is_open() && file.good())
    {
      while (file.good())
	{
	  std::string	line;

	  std::getline(file, line);
	  comment = this->cleanLine(line, comment);
	  if (!line.empty())
	    {
	      key = this->parseLine(line, 0);
	      value = this->parseLine(line, 1);
	      if (value.empty())
		{
		  if (up.find(key) == std::string::npos)
		    {
		      up += "/" + key;
		    }
		  else
		    {
		      if ((s = up.rfind("/")) != std::string::npos)
			up.erase(s, up.size() - s);
		      else
			up.clear();
		    }
		}
	      else
		{
		  key = up + "/" + key;
		  if (this->_xml.find(key) != this->_xml.end())
		    this->_xml[key] = this->_xml[key] + "-" + value;
		  else
		    this->_xml[key] = value;
		}
	    }
	}
    }
  else
    {
      error.IsError = true;
      error.Message = "An error occured during the parsing of the xml file.";
    }
  this->fillModules();
  this->fillWebsite();
  this->fillContent();
}

void					ConfParser::fillContent()
{
  for (std::map<std::string, std::string>::iterator it = this->_xml.begin();it != this->_xml.end();++it)
    {
      if (it->first.find("Zia/Modules") == std::string::npos && this->_search.find(it->first) != this->_search.end())
	this->_search[it->first] = it->second;
    }
}



void					ConfParser::fillWebsite()
{
  std::string	host;
  std::string	docs;
  std::string	tmp_h;
  std::string	tmp_d;
  size_t	end;

  if (this->_xml.find("/Zia/Server_info/website/virtual_host") != this->_xml.end())
    host = this->_xml["/Zia/Server_info/website/virtual_host"];
  if (this->_xml.find("/Zia/Server_info/website/document_root") != this->_xml.end())
    docs = this->_xml["/Zia/Server_info/website/document_root"];
  while (!host.empty() && !docs.empty())
    {
      end = host.find("-");
      if (end == std::string::npos)
	end = host.size();
      tmp_h = host.substr(0, end);
      host.erase(0, (end + 1));

      end = docs.find("-");
      if (end == std::string::npos)
	end = docs.size();
      tmp_d = docs.substr(0, end);
      docs.erase(0, (end + 1));

      std::cout << "HOST: " << tmp_h << std::endl;
      std::cout << "DOC ROOT: " << tmp_d << std::endl;
      std::cout << std::endl;

      this->_hosts.push_back(tmp_h);
      this->_docs[tmp_h] = tmp_d;
    }
}

void					ConfParser::fillModules()
{
  std::string	ext;
  std::string	root;
  std::string	path;
  std::string	tmp;
  size_t	end;

  if (this->_xml.find("/Zia/Modules/ext") != this->_xml.end())
    ext = this->_xml["/Zia/Modules/ext"];
  if (this->_xml.find("/Zia/Modules/root") != this->_xml.end())
    root = this->_xml["/Zia/Modules/root"];
  if (this->_xml.find("/Zia/Modules/path") != this->_xml.end())
    path = this->_xml["/Zia/Modules/path"];
  while (!path.empty())
    {
      end = path.find("-");
      if (end == std::string::npos)
	end = path.size();
      tmp = path.substr(0, end);
      path.erase(0, (end + 1));
      this->_modules.push_back(root + "/" + tmp + "." + ext);
    }
}

const std::string &			ConfParser::getApiName()
{
  return (this->_search["/Zia/Api/name"]);
}

int					ConfParser::getPort()
{
  int			ret;
  std::string		m = this->_search["/Zia/Server_info/port"];
  std::istringstream	buffer(m);

  buffer >> ret;
  return (ret);
}

const std::string &			ConfParser::getApiVersionMin()
{
  return (this->_search["/Zia/Api/min_authorized_version"]);
}

const std::vector<std::string> &	ConfParser::getModulesPath() const
{
  return (this->_modules);
}

const std::string &			ConfParser::getLoggerFile()
{
  return (this->_search["/Zia/Logger_info/log_file"]);
}

const std::string &			ConfParser::getLoggerFormat()
{
  return (this->_search["/Zia/Logger_info/format"]);
}

const std::vector<std::string> &	ConfParser::getVirtualHost()
{
  return (this->_hosts);
}

const std::string &			ConfParser::getDocumentRoot(const std::string & virtual_host)
{
  if (this->_docs.find(virtual_host) != this->_docs.end())
    return this->_docs[virtual_host];
  return this->_docs["NO VIRTUAL HOST"];
}
