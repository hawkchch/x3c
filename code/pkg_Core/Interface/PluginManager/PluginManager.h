/*! \file PluginManager.h
 *  \brief Define plugin manager wrapper class
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.28
 */
#ifndef X3_MANAGER_PLUGINMANAGER_H_
#define X3_MANAGER_PLUGINMANAGER_H_

#include "Ix_ObjectFactory.h"
#include "Ix_PluginLoader.h"

/*! \ingroup _GROUP_PLUGIN_CORE_
 *  \brief Plugin manager wrapper class
 *  \see   Ix_ObjectFactory, Ix_PluginLoader
 */
class CPluginManager
{
public:
    CPluginManager() : m_dll(NULL)
    {
        wcscpy_s(m_filename, MAX_PATH, L"PluginManagerX3" PLNEXT);
    }

    ~CPluginManager()
    {
        Unload();
    }

    //! Unload plugin manager and plugins
    void Unload(bool all = false)
    {
        if (all || m_dll)
        {
            Ix_PluginLoader* pLoader = GetPluginLoader();
            if (pLoader != NULL)
            {
                pLoader->UnloadPlugins();
            }
        }
        if (m_dll != NULL)
        {
            FreeLibrary(m_dll);
            m_dll = NULL;
        }
    }

    //! Load plugin manager.
    /*!
        \param subdir PluginManagerX3's path, absolute path or relative to instance.
        \param instance used if subdir is a relative path.
        \return true if plugin manager is loaded.
    */
    bool LoadPluginManager(const wchar_t* subdir, HMODULE instance = NULL)
    {
        GetModuleFileNameW(instance, m_filename, MAX_PATH);
        PathRemoveFileSpecW(m_filename);
        PathAppendW(m_filename, subdir);
        PathAppendW(m_filename, L"PluginManagerX3" PLNEXT);

        if (GetModuleHandleW(m_filename) || m_dll)
        {
            return true;
        }

        m_dll = LoadLibraryW(m_filename);
        return m_dll && GetObjectFactory();
    }

    //! Load plugin manager and core plugins.
    /*!
        \param subdir plugin path, absolute path or relative to instance.
        \param instance used if subdir is a relative path.
        \return true if any plugin is loaded.
    */
    bool LoadCorePlugins(const wchar_t* subdir, HMODULE instance = NULL)
    {
        if (!LoadPluginManager(subdir, instance))
        {
            return false;
        }

        Ix_PluginLoader* pLoader = GetPluginLoader();
        if (pLoader)
        {
            long n = pLoader->LoadPluginFiles(subdir,
                L"LogManager.plugin" PLNEXT
                L",LogWriter.plugin" PLNEXT
                L",ConfigXml.plugin" PLNEXT
                L",StringTable.plugin" PLNEXT
                L",ChangeManager.plugin" PLNEXT
                L",FileUtility.plugin" PLNEXT
                L",TextUtility.plugin" PLNEXT
                L",PluginManagerEx.plugin" PLNEXT, instance);

            if (pLoader->InitializePlugins() > 0 && n > 0)
            {
                return true;
            }
        }

        return false;
    }

    //! Return the object creator object.
    Ix_ObjectFactory* GetObjectFactory()
    {
        typedef Ix_ObjectFactory* (*FUNC_GETREGISTERBANK)();
        FUNC_GETREGISTERBANK pfn = (FUNC_GETREGISTERBANK)GetProcAddress(
            GetModuleHandleW(m_filename), "xGetRegisterBank");

        return pfn ? (*pfn)() : NULL;
    }

    //! Return the plugin loading object.
    Ix_PluginLoader* GetPluginLoader()
    {
        return dynamic_cast<Ix_PluginLoader*>(GetObjectFactory());
    }

private:
    CPluginManager(const CPluginManager&);
    void operator=(const CPluginManager&);

    HMODULE     m_dll;
    wchar_t     m_filename[MAX_PATH];
};

#endif // X3_MANAGER_PLUGINMANAGER_H_
