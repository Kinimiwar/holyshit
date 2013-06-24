#include "../sdk/sdk.h"
#include "../common/hook.h"
#include "../common/func.h"
#include "../common/toolbar.h"

extc int __cdecl ODBG2_Plugininit(void) 
{
    hook_DRAWFUNC_cpudasm();
    hook_DllCheck();
    if(CToolbar_Global.init("D:\\src\\vc\\holyshit\\common\\test.ini"))
        CToolbar_Global.attach(hwollymain);

    return 0;
}

// 至少要有这个函数
extc int __cdecl ODBG2_Pluginquery(int ollydbgversion,ulong *features,
                                   wchar_t pluginname[SHORTNAME],wchar_t pluginversion[SHORTNAME]) 
{
    // Check whether OllyDbg has compatible version. This plugin uses only the
    // most basic functions, so this check is done pro forma, just to remind of
    // this option.
    if (ollydbgversion<201)
        return 0;
    // Report name and version to OllyDbg.
    wcscpy(pluginname, L"HolyShit");       // Name of plugin
    wcscpy(pluginversion,L"002");       // Version of plugin
    return PLUGIN_VERSION;               // Expected API version
};

static int MloadMap(t_table *pt,wchar_t *name,ulong index,int mode)
{
    if (mode==MENU_VERIFY)
        return MENU_NORMAL;                // Always available
    else if (mode==MENU_EXECUTE) 
    {
        LoadMap();
        return MENU_REDRAW;
    };
    return MENU_ABSENT;
}
static t_menu mainmenu[] = {
    { L"load map file..",
    L"load map file ,which maybe from IDA or dede",
    K_NONE, MloadMap, NULL, 0 },
    //{ L"odhs plugin v0.1",
    //L"About odhs plugin",
    //K_NONE, Mabout, NULL, 0 }
    { NULL, NULL, K_NONE, NULL, NULL, 0 }
};
extc t_menu *ODBG2_Pluginmenu(wchar_t *type)
{
    if (wcscmp(type,PWM_MAIN)==0)
        // Main menu.
        return mainmenu;
    return NULL;
}

bool bInjected = false;
void ODBG2_Pluginmainloop(DEBUG_EVENT *debugevent)
{
    if (debugevent && debugevent->dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT)
    {
        bInjected = false;
    }
}

void  ODBG2_Pluginanalyse(t_module *pmod)
{
    //Run(STAT_RUNNING, 0);
     Resumeallthreads();
    //Sendshortcut(PM_MAIN, 0, WM_KEYDOWN, 0, 1, VK_F9); 
    if (pmod)
    {
    wchar_t* p = pmod->modname; 
    p = pmod->path;
    }
}