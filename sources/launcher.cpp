#include	<iostream>
#include	<fstream>
#include	<ctime>

#define	LOCK_FILE	"./lock.txt"
#define	SERVER_NAME	"./zia"
//#define	SERVER_NAME	"C:\\WINDOWS\\System32\\notepad.exe"

#ifdef WIN32
    #include    <process.h>
    #include    <windows.h>
    #include    <Tlhelp32.h>
	#include	<tchar.h>
	#include	<stdio.h>
#else
	#include	<limits.h>
	#include	<unistd.h>
	#include	<stdlib.h>
	#include	<signal.h>
#endif

std::string	my_realpath(const std::string &src)
{
#ifdef WIN32
	DWORD  retval=0;
	TCHAR  dst[1024]=TEXT("");
	TCHAR** lppPart={NULL};

	retval = GetFullPathName(src.c_str(), 1024, dst, lppPart);
	if (retval)
	return (std::string((char *)dst));
	else
		return ("");

#else
	char	dst[1025];
	realpath(src.c_str(), dst);
	return (std::string(dst));
#endif
}

/**
** \fn bool server_are_launched(const std::string &name)
** \brief Gere l'ecriture du nom du programme dans le fichier
**
** \param name Nom du programme
** \return Retourne true si OK, false sinon
*/
bool	server_are_launched(const std::string &name)
{
	std::ifstream ifile(LOCK_FILE);

	if (ifile)
        {
        	std::cout << "Server already running" << std::endl;
                ifile.close();
                return (false);
        }

	std::string real_name = my_realpath(name);
	std::ofstream ofile(LOCK_FILE, std::ios::out | std::ios::trunc);
	if (ofile)
        {
        	std::cout << "Server launched" << std::endl;
        	#ifdef WIN32
                	ofile << real_name;
                #else
                	ofile << getpid();
                #endif
                ofile.close();
                return (true);
        }
        return (false);
}

int	start(int ac, char* const*av, char* const*env)
{
#ifdef WIN32
STARTUPINFO StartupInfo;
 PROCESS_INFORMATION ProcessInformation;
 StartupInfo.cb   =sizeof(STARTUPINFO);
 StartupInfo.cbReserved2 =0;
 StartupInfo.dwFillAttribute=0;
 StartupInfo.dwFlags =0;
 StartupInfo.dwX  =CW_USEDEFAULT;
 StartupInfo.dwXCountChars=0;
 StartupInfo.dwXSize =CW_USEDEFAULT;
 StartupInfo.dwY  =CW_USEDEFAULT;
 StartupInfo.dwYCountChars=0;
 StartupInfo.dwYSize =CW_USEDEFAULT;
 StartupInfo.hStdError =NULL;
 StartupInfo.hStdInput =NULL;
 StartupInfo.hStdOutput =NULL;
 StartupInfo.lpDesktop =NULL;
 StartupInfo.lpReserved =0;
 StartupInfo.lpReserved2 =NULL;
 StartupInfo.lpTitle =NULL;
 StartupInfo.wShowWindow =SW_SHOWDEFAULT;

    std::string cmd = my_realpath(SERVER_NAME);
    for (int i=2; i<ac; i++)
        cmd += " " +std::string(av[i]);
    char tmp[1024];
    strncpy(tmp, cmd.c_str(), 1023);
    if (server_are_launched(SERVER_NAME))
        CreateProcess(NULL, tmp, NULL, NULL, false, CREATE_NO_WINDOW, NULL, NULL, &StartupInfo, &ProcessInformation);
#else
	const char *tab[4];

	tab[0] = my_realpath(SERVER_NAME).c_str();
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;

	if (ac > 2)
		tab[1] = av[2];
	if (ac > 3)
		tab[2] = av[3];
	if (fork() == 0)
	{
		if (server_are_launched(SERVER_NAME))
			execve(tab[0], const_cast<char* const*>(tab), env);
	}
#endif
	return (1);
}

bool	stop()
{
	std::ifstream ifile(LOCK_FILE);

	if (ifile)
	{
        	#ifdef WIN32
        	std::string name;
        	ifile >> name;

        	HANDLE hSnapshot;
            PROCESSENTRY32 proc;
            int result;

            hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

            result = Process32First(hSnapshot, &proc);

            while (result)
            {
                if (!strcmp(proc.szExeFile, name.c_str()))
                {
                    hSnapshot = OpenProcess(PROCESS_TERMINATE,FALSE, proc.th32ProcessID);

                    if(hSnapshot != NULL)
                    {
                        TerminateProcess(hSnapshot, 0);
                        hSnapshot = CreateToolhelp32Snapshot(2,0);
                    }
                }
            result = Process32Next(hSnapshot, &proc);
            }
            #else
			pid_t	pid;

			ifile >> pid;
			kill(pid, SIGKILL);
            #endif
		ifile.close();
		remove(LOCK_FILE);
		std::cout << "Server stopped" <<  std::endl;
	}
	return (true);
}

int	main(int ac, char* const*av, char* const*env)
{
	if (ac < 2)
	{
		std::cout << "Usage : %s <commande> [option]" << std::endl << std::endl;
		std::cout << "Commande :" << std::endl;
		std::cout << "  start <config file>" << std::endl;
		std::cout << "  reload <config file>" << std::endl;
		std::cout << "  stop" << std::endl;
		return (1);
	}

	if (std::string(av[1]) == "start")
		start(ac, av, env);
	else if (std::string(av[1]) == "stop")
		stop();
	else if (std::string(av[1]) == "reload")
	{
		stop();
		start(ac, av, env);
	}
	else
		std::cout << "Bad option \"" << av[1] << "\"" << std::endl;
    #ifdef WIN32
	Sleep(1000);
	#else
	sleep(1);
	#endif
	return (1);
}

