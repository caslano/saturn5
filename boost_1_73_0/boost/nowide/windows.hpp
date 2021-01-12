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
YoC+WIM1xtodoy/Wao2xEjTGeqW/vljrNMZ6N/qbY51OrnLjKcQ71VgzNMY61E9fLF1xbtZYpyyNsT6J0herSWOs2RpjfdlXX6wWjbECv8/lMXtFXBZDimmIx7bJY/JYX0Xqq9cdGmMt0BjLqjHWvX30xSrQGCtcY6yHXPpiFWmM1UdjrF0R+mIt1RgrQmOsh5z6YumKs1hjnewaY+0I1xdrrsZYuuL0OvTF0hVns8Y6naMx
*/