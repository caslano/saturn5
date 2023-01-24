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
D8IAM2mAEvACaoVz6yN7sbGBua0BpYJPG4NS2Fl676UtnaW7hzar8AWgh24S0LuZ39KAHngFBHqKgzy0NZ2sXBx2xhJtrvWvqq/eP82hj+zK0e4RSEw75UGAr6ymPfoQSwZh21H8JwC8I50iALA3cCLN4nQS62GwJ39H7EucVh/Xf67EfUrFPl2xWDNs4D5pIrVY7Q0aw1bFd53JEMNPCymHvjHlKDZKU/3TgN6qSMZnsBGsN806p2oxJNseUdXAHQlZgUGRyodfmE1zM8tW4iHtX0lptAOyME9xwhiU34fiAzy8oRaFUPOvZH3dymX0zkL6t5xF3/UY/8nv40N+JSusV3KStpW1/HOAmsLIMJWa0MfguxiKW+Q/oOnUJN97B0i0LqhTso3AJ8AsvEytiuA3Hy9FR9L3qqmy770a8Vsr5PJ3UudmswznWU3z14yoGd5bLN7HcZp87y0UzUQ+aWxGS1fWTnWk5aB96XtCDTA0WbnoT/SVjaucGWZXAQ/Gf9akXcWlV/83csQONyBoUx8DgkbcfKxhFNOHPMa8ZZmUtyzRXhpDnJvVtsOixaUG5FgmQpkmK0nxrJn+3YTmBKtoqYjq8k8tdiP6JftDgKErRmOSP0DAAt8OLZaeqGBd6DDgbIbFY6LG6ySfy2YLxhDWVlID51Q0GvOTjWMOxq0lQ3uO4/5sI2X1ala8/T/m3jw+iip7FK/uTich
*/