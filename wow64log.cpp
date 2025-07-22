#include <windows.h>
#include <stdio.h>

void LaunchCalculator()
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    const char* calcCmd = "C:\\Windows\\System32\\calc.exe";

    if (!CreateProcessA(
        NULL,          
        (LPSTR)calcCmd, 
        NULL,          
        NULL,          
        FALSE,         
        0,             
        NULL,          
        NULL,          
        &si,           
        &pi))          
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
    }
    else
    {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        LaunchCalculator();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
