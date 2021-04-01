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
u4MKA7t9n/XZo3eFZerBy/6tlUYpbaSz5qPZDfY9Gw/CqGf+Ge81zA8VRyV915WHXHefS2tdHU/zwCP5N6vOnvZYbxoTfX+m0ds6kwKeK29hJlOD/SfCEdkWjCZh1ZY3VHPSagIk7xG3ALxM5YA22b3/ryaA4MWyiD5ef+xZq8BcNHEk63Yt9+XPZtF78Jxn6b+PS5CadQ4b1azjT6gGMT5cBq5yk1de06xT9Hx/MFSBxxsuxsp9QIEYnrDkfcizsWCUZNm0O3/0eW/QJkj4dOrtYIKkGUXZwA2Mn4dlaNAmwMEVcQd6ODyHXT1mACrlXSjj/r5L2wMtCyrkMUssIF7Xw8iKnXX0wlXAnmVeWI+wGDxqlJqIS5g1YAgF7R8CLqJivmpil+nn37Ag1ct1vNeSXV7WCUV7IsQqxs7rj3zN0CpNj1EesnGWj0DKpTqaNUjgwkVqpkJf/UObseNUas/VDU40JLNT5RpsF+IsS3mUhwLScGEt1gfIp2TEly6BXcO22pN06Sjx11OFeM72ydLD+QTIUBFMHH13eSjzfXL202yS6MhAhJGEZA==
*/