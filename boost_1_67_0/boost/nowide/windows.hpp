//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_WINDOWS_HPP_INCLUDED
#define BOOST_NOWIDE_WINDOWS_HPP_INCLUDED

#ifdef BOOST_USE_WINDOWS_H
#include <windows.h>
#else

//
// These are function prototypes... Allow to avoid including windows.h
//
extern "C" {

__declspec(dllimport) wchar_t* __stdcall GetEnvironmentStringsW(void);
__declspec(dllimport) int __stdcall FreeEnvironmentStringsW(wchar_t*);
__declspec(dllimport) wchar_t* __stdcall GetCommandLineW(void);
__declspec(dllimport) wchar_t** __stdcall CommandLineToArgvW(const wchar_t*, int*);
__declspec(dllimport) unsigned long __stdcall GetLastError();
__declspec(dllimport) void* __stdcall LocalFree(void*);
__declspec(dllimport) int __stdcall SetEnvironmentVariableW(const wchar_t*, const wchar_t*);
__declspec(dllimport) unsigned long __stdcall GetEnvironmentVariableW(const wchar_t*, wchar_t*, unsigned long);
}

#endif

#endif

/* windows.hpp
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
*/