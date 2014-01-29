#ifndef CONNEXION_ATTENTE_HPP
#define CONNEXION_ATTENTE_HPP

#include	<sstream>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<netdb.h>

#include	"IConnexion.hpp"
#include	"ConnexionClient.hpp"

class ConnexionAttente: public apimeal::IConnexion
{
    public:
    	ConnexionAttente();
    	ConnexionAttente(int port=80, int nbs_attente=5);
	~ConnexionAttente();
	
	bool isOK() const;
	
	
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



	/**
         * \brief Accepte une connexion d'un client
	 * \return Connexion*: une connexion avecc un client si OK, 0 sinon
	 */
	apimeal::IConnexion* accept_client();


    protected:
    	SOCKET		_sock;
    	struct sockaddr_in	_sin;
    	int		_port;
    	std::string	_ip;
    	std::string	_hostname;
    	std::string	_request;
};

#endif

