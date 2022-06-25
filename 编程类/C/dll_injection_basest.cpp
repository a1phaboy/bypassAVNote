// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

DWORD WINAPI    ThreadProc(LPVOID lParam) {
    /* your payload. */
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
        HANDLE hThread = NULL;
    case DLL_PROCESS_ATTACH:

        hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL); //加载该dll文件会自动执行 DLL_PROCESS_ATTACH 分支语句，利用此规则生成线程（注意线程的父进程属于此dll而非对象文件）
        CloseHandle(hThread);

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

