#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include <string>

class ProcessManager
{
    inline static HANDLE globalProcessHandle{};   
    inline static DWORD globalProcessId{};
    inline static std::wstring targetProcessName{};

    public:
    static DWORD FindProcessIDByName(const std::wstring& name)
    {
        DWORD processId{};
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (snapshot == INVALID_HANDLE_VALUE)
            return 0;

        PROCESSENTRY32W processEntry = { sizeof(PROCESSENTRY32W) };

        if (Process32FirstW(snapshot, &processEntry))
        {
            do
            {
                if (name == processEntry.szExeFile)
                {
                    processId = processEntry.th32ProcessID;
                    break;
                }
            } while (Process32NextW(snapshot, &processEntry));
        }

        CloseHandle(snapshot);
        return processId;
    }

    static inline bool InitializeGlobalHandle(const std::wstring& procName)
    {
        if (globalProcessHandle != nullptr)
        {
            if (targetProcessName == procName) return true;
            ClearGlobalHandle();
        }

        targetProcessName = procName;
        globalProcessId = FindProcessIDByName(targetProcessName);

        if (globalProcessId == 0)
        {
            globalProcessHandle = nullptr;
            return false;
        }

        globalProcessHandle = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, globalProcessId);

        return globalProcessHandle != nullptr;
    }

    static inline HANDLE GetGlobalProcessHandle() { return globalProcessHandle; }
    static inline DWORD GetGlobalProcessID() { return globalProcessId; }

    static inline void ClearGlobalHandle()
    {
        if (globalProcessHandle != nullptr)
        {
            CloseHandle(globalProcessHandle);
            globalProcessHandle = nullptr;
            globalProcessId = 0;
            targetProcessName = L"";
        }
    }

    static inline bool IsHandleRunning(HANDLE procID)
    {
        if (procID == nullptr)
            return false;
        
        DWORD exitCode = 0;
        if (GetExitCodeProcess(procID, &exitCode))
            return exitCode == STILL_ACTIVE;      

        return false;
    }

};