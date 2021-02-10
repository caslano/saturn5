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
ioGnhJQD4td01tnWx/c8QV9KtXyMzDu2a9szq7Hjp5QT8HULL3cBu165pWtlilJTUvrNom5GusY2i/bbmUu2A7BcxO2NDbK9s3HFnc2hOr7wHxL/5nr7e/T2BsRkVSLlkrY22FzKgI4eSfEEK5uMA5fjz+LuXX6EdSvq1CjNYcenQ48nObIpingRYRdRgpXkseeSG/vOohJw20i3QM0lR/f0rEu30jaNGnZfn47t73QWULfb7QxIr2SkQLfh7TUS2gr3ZK9YUof18tpZbkOYFyg2TQzbhjaSmxU3LlZX6+k7+XR6isE7TTGyAQBa2S1mR7HWp6e1LNis+TGHO9N+XWa/2FtMSpVVGRBYYNTyRuf8d4t2LeIRqLEBd7dthMO2689nrE0JuRUpbt8Ox/94gZeUL9uT0B158c54WLeNU+mL8YedtEakrtFMbdE7f+zGkQrDvRhLpF0pDZKuhqBbJ+k3LXYtMKZf0WcCiNDrS4G+2tZpYWpYrS0N5uMPo9H+9zFL67CxGNqJT666JrfpC8HjAisGDDQcJjt9Guuf+5p9bt8dkGP2ZQEbMY+muvN3m0E5TOzbTs5JKXzyFm7QY3CpHE66QGp+ERL2DQRioUxyWXYf928nd3+/aL21nb1a0mi60bJdRnXR2mQ/
*/