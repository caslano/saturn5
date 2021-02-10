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
pFrdQKaNPf3FmTnvT3uTwTgcBCPmUzHwtcBUI8EcObuY9zSlwitDLZnB0e2bIuV56TOp88rMb2Sauhpha34rHFdQNOf5lniOgo2eVtgEbCvcZuIMeIZpjDih1L5vbTab1krn6xaaEoqCixssERw56MGJM4A/yy2seEnKNVrGAlivtUqdhdgBiAVkEx2feozN0KpWgoh7vRocYnEx6A/PpyfPT69XY2LUwWui98MrrMolQWAyEWGhYjFh/cfccjokFFzRPWpn8Gd/Z4p96cZi6E/e1ffIDiUBw3QmjPwHa40Fzg2eptgnqK9FyJws13cyFjtXHAaFkZhqFD80N+n75xezUY/yXdl54DLdOPdDv/a2ihoLmHQpRjbXBYbqEmwKrHK0qLR13n4NY7zG1Rb7LLqF6thoNhx6cIVKqwDohQthg+WOXIkwyiWPbstAnVGbc2WopeFPGWCUFOpWxMy9WYm85YhDbzCnO7kaSQKxbmJ7Uw9AejxrX8zrYdZqlmA5aBDKzYjKQ6gdK8Mx1MG2WHHYz6oBhsWQ6yyX3AoW1uH063DKOmhiKGVdEd9aNURehM2Ro0aiyLyihb4TeU68cNGKFS9SW3LjuAhLzVRXCJMlW+hgDnqjmIPnIHCq90tkSH9SxusqjCScWnfb
*/