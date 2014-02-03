#include <iostream>
#include <algorithm>

#if defined	(_WIN32)
#include	<windows.h>
#else
#include	<dlfcn.h>
#endif

#include	"ModuleLoader.hpp"

ModuleLoader::ModuleLoader()
{}

ModuleLoader::ModuleLoader(const std::vector<std::string> & modules, apimeal::Error & e, apimeal::ILogger *log)
{
    for (std::vector<std::string>::const_iterator it = modules.begin();it != modules.end();++it)
        this->LoadModule((*it), e, log);
    this->sortModules();
}

ModuleLoader::~ModuleLoader()
{
    for (std::map<std::string, apimeal::AModule*>::iterator it = this->_mod.begin();it != this->_mod.end();++it)
        this->UnloadModule((it->first));
}

void	ModuleLoader::LoadModules(const std::vector<std::string> & m, apimeal::Error & error, apimeal::ILogger *log)
{
    for (std::vector<std::string>::const_iterator it = m.begin();it != m.end();++it)
        this->LoadModule((*it), error, log);
}

bool sortMod(apimeal::AModule *f, apimeal::AModule *s)
{
    return f->getPriority() > s->getPriority();
}

// FAIRE DES TESTS !!!!111!!!!!

bool isModuleVectorSorted(std::vector<apimeal::AModule *> moduleVector, apimeal::eTypeModule type)
{
    std::vector<apimeal::AModule *>::const_iterator ite;
    
    for (ite = moduleVector.begin(); ite != moduleVector.end() && (ite + 1) != moduleVector.end(); ++ite)
    {
        if ((*ite)->getPriority()[type] > (*(ite + 1))->getPriority()[type])
            return false;
    }
    return true;
}

void sortModuleVector(std::vector<apimeal::AModule *> moduleVector, apimeal::eTypeModule type)
{
    std::vector<apimeal::AModule *>::iterator ite;
    
    while (isModuleVectorSorted(moduleVector, type) == false)
        for (ite = moduleVector.begin(); ite != moduleVector.end() && (ite + 1) != moduleVector.end(); ++ite)
            if ((*ite)->getPriority()[type] > (*(ite + 1))->getPriority()[type])
                std::iter_swap(ite, ite +1);
}

void ModuleLoader::sortModules()
{
    std::map<std::string, apimeal::AModule*>::const_iterator ite;
    std::map<apimeal::eTypeModule, std::vector<apimeal::AModule *> >::const_iterator site;
    
    for (ite = this->_mod.begin(); ite != this->_mod.end(); ++ite)
    {
        if (ite->second->getPriority().find(apimeal::PRECONNEXION) != ite->second->getPriority().end())
            this->_sortedMod[apimeal::PRECONNEXION].push_back(ite->second);
        if (ite->second->getPriority().find(apimeal::POSTCONNEXION) != ite->second->getPriority().end())
            this->_sortedMod[apimeal::POSTCONNEXION].push_back(ite->second);
        if (ite->second->getPriority().find(apimeal::PREPARSEREQUEST) != ite->second->getPriority().end())
            this->_sortedMod[apimeal::PREPARSEREQUEST].push_back(ite->second);
        if (ite->second->getPriority().find(apimeal::POSTPARSEREQUEST) != ite->second->getPriority().end())
            this->_sortedMod[apimeal::POSTPARSEREQUEST].push_back(ite->second);
        if (ite->second->getPriority().find(apimeal::CONTENTMODULE) != ite->second->getPriority().end())
            this->_sortedMod[apimeal::CONTENTMODULE].push_back(ite->second);
        if (ite->second->getPriority().find(apimeal::CGIMODULE) != ite->second->getPriority().end())
            this->_sortedMod[apimeal::CGIMODULE].push_back(ite->second);
        if (ite->second->getPriority().find(apimeal::POSTGENERATERESPONSE) != ite->second->getPriority().end())
            this->_sortedMod[apimeal::POSTGENERATERESPONSE].push_back(ite->second);
        if (ite->second->getPriority().find(apimeal::SENDREQUEST) != ite->second->getPriority().end())
            this->_sortedMod[apimeal::SENDREQUEST].push_back(ite->second);
    }
    for (site = this->_sortedMod.begin(); site != this->_sortedMod.end(); ++site)
        sortModuleVector(site->second, site->first);
}

void	ModuleLoader::LoadModule(const std::string & module, apimeal::Error & error, apimeal::ILogger *log)
{
    apimeal::AModule* (*mod)(apimeal::ILogger *);
    apimeal::AModule* m;
    std::string	modName;
    
#if defined	(_WIN32)
    HMODULE	handle = LoadLibrary(module.c_str());
    
    if (handle == NULL)
    {
        error.IsError = true;
        error.Message += "Cannot open library: " + module + "\n";
        return ;
    }
    
    mod = (apimeal::AModule* (*)(apimeal::ILogger *))GetProcAddress(handle, "LoadModule");
    
    if (mod == NULL)
    {
        error.IsError = true;
        error.Message += "Cannot load symbole 'LoadModule' for the module named " + module + "\n";
        FreeLibrary(handle);
        return ;
    }
#else
    void	*handle = dlopen(module.c_str(), RTLD_LAZY);
    
    if (!handle)
    {
        error.IsError = true;
        error.Message += "Cannot open library: " + module + "\n";
        return ;
    }
    
    mod = (apimeal::AModule* (*)(apimeal::ILogger *)) dlsym(handle, "LoadModule");
    const char	*dlsym_error = dlerror();
    if (dlsym_error)
    {
        error.IsError = true;
        error.Message += "Cannot load symbole 'LoadModule' for the module named " + module + "\n";
        dlclose(handle);
        return ;
    }
    this->_handles[module] = handle;
#endif
    m = mod(log);
    modName = m->getName();
    if (!modName.empty())
    {
        this->_mod[modName] = m;
        this->_handles[modName] = handle;
    }
}

void	ModuleLoader::UnloadModule(const std::string & module)
{
    
    if (this->_handles.find(module) != this->_handles.end())
    {
#if defined	(_WIN32)
        FreeLibrary(this->_handles[module]);
#else
        dlclose(this->_handles[module]);
    }
#endif
}

apimeal::AModule*	ModuleLoader::getModule(const std::string & m, apimeal::Error & e)
{
    if (this->_mod.find(m) != this->_mod.end())
        return this->_mod[m];
    else
    {
        e.IsError = true;
        e.Message += "The module " + m + " doesn't exist.\n";
        return NULL;
    }
}

const std::map<std::string, apimeal::AModule*>    &ModuleLoader::getModuleMap()const
{
    return this->_mod;
}

const std::map<apimeal::eTypeModule, std::vector<apimeal::AModule *> > &ModuleLoader::getSortedMap()
{
    return this->_sortedMod;
}
