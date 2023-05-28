#include <Windows.h>
#include "peb_lookup.h"

int main()
{
    wchar_t kernel32_dll_name[] = {'k','e','r','n','e','l','3','2','.','d','l','l', 0};
    LPVOID base = get_module_by_name((const LPWSTR)kernel32_dll_name);
    if (!base)
    {
        return 1;
    }
    char load_lib_name[] = {'L','o','a','d','L','i','b','r','a','r','y','A',0};
    LPVOID load_lib = get_func_by_name((HMODULE)base, (LPSTR) load_lib_name);
    if (!load_lib)
    {
        return 2;
    }
    char get_proc_name[] = {'G','e','t','P','r','o','c','A','d','d','r','e','s','s',0};
    LPVOID get_proc = get_func_by_name((HMODULE)base, (LPSTR) get_proc_name);
    if (!get_proc)
    {
        return 3;
    }
    HMODULE(WINAPI * _LoadLibraryA)
    (LPCSTR lpLibFileName) = (HMODULE(WINAPI *)(LPCSTR))load_lib;
    FARPROC(WINAPI * _GetProcAddress)
    (HMODULE hModule, LPCSTR lpProcName) = (FARPROC(WINAPI *)(HMODULE, LPCSTR))get_proc;
    
    char user32_dll_name[] = {'u','s','e','r','3','2','.','d','l','l', 0};
    LPVOID u32_dll = _LoadLibraryA(user32_dll_name);

    char message_box_name[] = {'M','e','s','s','a','g','e','B','o','x','W', 0};
    int(WINAPI * _MessageBoxW)(
        _In_opt_ HWND hWnd,
        _In_opt_ LPCWSTR lpText,
        _In_opt_ LPCWSTR lpCaption,
        _In_ UINT uType) = (int(WINAPI *)(_In_opt_ HWND,
                                          _In_opt_ LPCWSTR,
                                          _In_opt_ LPCWSTR,
                                          _In_ UINT))_GetProcAddress((HMODULE)u32_dll, message_box_name);
    if (_MessageBoxW == NULL)
        return 4;

    wchar_t msg_content[] = {'H','e','l','l','o', ' ', 'W','o','r','l','d','!', 0};
    wchar_t msg_title[] = {'D','e','m','o','!', 0};
    _MessageBoxW(0, msg_title, msg_content, MB_OK);
    return 0;
}