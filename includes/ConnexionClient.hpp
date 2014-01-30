#ifndef CONNEXIONCLIENT_HPP
#define CONNEXIONCLIENT_HPP

#include	<vector>
#include	<sstream>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<netdb.h>

#include	"IConnexion.hpp"

class ConnexionClient: public apimeal::IConnexion
{
    public:
	ConnexionClient(const sockaddr_in &sin, SOCKET s);
	~ConnexionClient();
	
	/**
	 * \brief getHostname
	 * \return std::string const & : Hostname client
	 */
	virtual std::string const &getHostname() const;
	/**
	 * \brief getIp
	 * \return std::string const & : Ip client ex (192.168.0.1)
	 */
	virtual std::string const &getIp() const;
	/**
	 * \brief getPort
	 * \return int : Port client
	 */
	virtual int getPort() const;
	/**
	 * \brief get the Request
	 * \return std::string  const & : Request client
	 */
	virtual std::string const &getRequest() const;
	/**
	 * \brief set the Request
	 * \param std::string const & request : The request
	 * \return void
	 */
	virtual void setRequest(std::string const &request);

	/**
	 * \brief set the socket
	 * \param SOCKET : The socket
	 * \return void
	 */
	virtual void setSocket(SOCKET);

	/**
         * \brief get the socket 
	 * \return SOCKET: the socket
	 */
	virtual SOCKET getSocket();
	
	
	
    protected:
    	SOCKET		_sock;
    	std::string	_request;
    	std::string	_ip;
    	std::string	_hostname;
    	int		_port;
};

#endif

