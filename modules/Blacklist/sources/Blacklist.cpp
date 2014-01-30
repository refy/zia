#include	<mutex>
#include	<thread>
#include	"AModule.hpp"
#include	"Blacklist.hpp"

Blacklist::Blacklist(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("Blacklist")
{
	load_blacklist();
}

Blacklist::~Blacklist()
{}

std::map<apimeal::eTypeModule, apimeal::ePriority>	PreConnexion::getPriority() const
{
    return std::map<apimeal::eTypeModule, apimeal::ePriority>();
}

const apimeal::Version &		Blacklist::getVersion() const
{
  return (this->_version);
}

const std::string &			Blacklist::getName() const
{
  return (this->_name);
}

void	Blacklist::preConnexion(apimeal::IConnexion *c, apimeal::Error & e)
{
	if (time(0) > this->_t_last_blacklist)
		load_blacklist();
	if (c == 0)
	{
		e.IsError = true;
		e.Message += "Bad pointer\n";
	}
	else
	{
		std::string	ip_tmp = c->getIp();
		std::string	hostname_tmp = c->getHostname();
		
		this->_mutex.lock();
		for (std::set<std::string>::const_iterator it=this->_blacklist.begin(); it!=this->_blacklist.end(); ++it)
		{
			if (((*it) == ip_tmp) || ((*it) == hostname_tmp))
			{
				e.IsError = true;
				e.Message += "Blacklisted client\n";
				this->_mutex.unlock();
				return ;
			}
		}
		e.IsError = false;
		e.Message += "OK\n";
		this->_mutex.unlock();
	}
}


void	Blacklist::load_blacklist()
{
	std::ifstream	file(PRECONNEXION_BLACKLIST_FILE);

	this->_mutex.lock();
	_blacklist.clear();
	if (file)
	{
		std::string	line;
 
		while (std::getline(file, line))
		{
			if (line.size() > 0)
        			_blacklist.insert(line);
        	}
	}
	this->_t_last_blacklist = time(0) + PRECONNEXION_T_RELOAD_BLACKLIST;
	this->_mutex.unlock();
}


extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new Blacklist(log));
}
