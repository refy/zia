#include	<iostream>
#include	<vector>
#include	<stdlib.h>

#include	"Error.hpp"
#include	"PreConnexion.hpp"
#include	"ConnexionClient.hpp"
#include	"ConnexionAttente.hpp"

int	main(int argc, const char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage : " << argv[0] << " <port>" << std::endl;
		return (1);
	}
	ConnexionAttente	sock_attente(atoi(argv[1]));
	if (sock_attente.isOK() == false)
	{
		std::cerr << "Impossible de creer la socket d'attente" << std::endl;
		return (1);
	}
	std::cout << "Serveur :   IP=" << sock_attente.getIp()
		  << " Port=" << sock_attente.getPort()
		  << " Hostname=" << sock_attente.getHostname() << std::endl;

	apimeal::IConnexion	*ptr;
	PreConnexion		preCo;
	apimeal::Error		error;
	while ((ptr = sock_attente.accept_client()) != 0)
	{

		std::cout << "Connexion :   IP=" << ptr->getIp()
			  << " Port=" << ptr->getPort()
			  << " Hostname=" << ptr->getHostname();
			  
		preCo.preConnexion(ptr, error);
		if (! error.IsError)
			std::cout << " OK" << std::endl;
		else
			std::cout << " BLACKLISTE : " << error.Message << std::endl;

		delete ptr;
	}
	return (1);
}
