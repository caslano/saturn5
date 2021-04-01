//  Copyright 2015 Klemens Morgenstern
//
// This file provides a demangling for function names, i.e. entry points of a dll.
//
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_DLL_DEMANGLE_SYMBOL_HPP_
#define BOOST_DLL_DEMANGLE_SYMBOL_HPP_

#include <boost/dll/config.hpp>
#include <string>
#include <algorithm>
#include <memory>

#if defined(_MSC_VER) // MSVC, Clang-cl, and ICC on Windows

namespace boost
{
namespace dll
{
namespace detail
{

typedef void * (__cdecl * allocation_function)(std::size_t);
typedef void   (__cdecl * free_function)(void *);

extern "C" char* __unDName( char* outputString,
        const char* name,
        int maxStringLength,    // Note, COMMA is leading following optional arguments
        allocation_function pAlloc,
        free_function pFree,
        unsigned short disableFlags
        );


inline std::string demangle_symbol(const char *mangled_name)
{

    allocation_function alloc =  [](std::size_t size){return static_cast<void*>(new char[size]);};
    free_function free_f      = [](void* p){delete [] static_cast<char*>(p);};



    std::unique_ptr<char> name { __unDName(
            nullptr,
            mangled_name,
            0,
            alloc,
            free_f,
            static_cast<unsigned short>(0))};

    return std::string(name.get());
}
inline std::string demangle_symbol(const std::string& mangled_name)
{
    return demangle_symbol(mangled_name.c_str());
}


}}}
#else

#include <boost/core/demangle.hpp>

namespace boost
{
namespace dll
{
namespace detail
{

inline std::string demangle_symbol(const char *mangled_name)
{

    if (*mangled_name == '_')
    {
        //because it start's with an underline _
        auto dm = boost::core::demangle(mangled_name);
        if (!dm.empty())
            return dm;
        else
            return (mangled_name);
    }

    //could not demangled
    return "";


}

//for my personal convenience
inline std::string demangle_symbol(const std::string& mangled_name)
{
    return demangle_symbol(mangled_name.c_str());
}


}
namespace experimental
{
using ::boost::dll::detail::demangle_symbol;
}

}}

#endif

#endif /* BOOST_DEMANGLE_HPP_ */

/* demangle_symbol.hpp
mUunHx6rDLw96NOApK7JTbkno5HxcU6u00RtEVV2NLjtrjOfIjIhsC0Y2ThDKFkyFxodLMPpqeHNn56OHSc5HyxbQftiQ6ODOTIUEDTWzMNTqL3/7JkqO3QOfRxQfrPIs9k3Nq0yrQ4RIPsl1y5MrwuxL3dnyOhxHEvijLbDYSkxB8WE6aAZF08lQd+Tnb601iLJtpM1GLSYSejs+4guZNbL9OaV5yyZ3G34KmxB04h88duda1tV5wTYUnEqT7C4bD8Z2D+FOXfOKrIhBBfyJ+O2T/NoL8/IKxkUqbmkeL0/STty6qym+vjXn300+dxyNbxHMfis4DEbuIJZ8+1C2AU+NwlKeBSPK4aquXa2fuJR3OQDTCQF3ixykmq9YulU9CirmRGJSvr6AkkAwf6jTpkjHi86XLJvi40Gej0p6+IlHLqjUSCzI1KIW5epCahn1HPj2+lZFrQdS+MPiMPBcfQwRVkP7fpp6R6zR75q5tViP+cQ8QCTI9tVogdGpMQpXPU7zUCmSl3Vs2ljz8KbVkRZB8HNvxTURIm/az/mTRHhizf9z/9Em543Mw==
*/