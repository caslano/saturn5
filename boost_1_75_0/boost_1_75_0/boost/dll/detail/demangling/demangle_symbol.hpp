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
uUJzWzt5pEgWC6ZTRWSgO6HM+DFB96mjHjL8Q0XkLc05rLWjgyBPVnciK/T3VsuA9HJzWtyjLF+k2BcW3eDzrwUv9lyxJWxucH4F3eBTryUlDe6ZOe3IDT7/Zw8MtKr5GPxA1c9sTUoFa9J/YczSzwOD4MhSGiNYk95dq1uTrhK9tBbfMeevjVPdB93GUY+aZMpxnKZfm6Y8g7G5mX2aQoz69IiHQm07aHBiAkN/brbANLvZucFUPAJmOem3s4BpxAgNTN3OIzAV1zGYeuEH8ut0MM04YoHJ3awhMD2+JhRMPw8XYCpeo4Np32EdTCi6arOUUFoeUw9KC7UXJYGgv7dY0KmMOTd0Rg+HyQ3/9SzQ6TVcg05MW4LO6J8YOnH4Ae9POnTuOGxBJyamIejcvToUOttyBHRGr9ah8+EvdiQS0/Rr05TgeatpPfBM5zfhVAREueT4yGZP10I8cfcYTiJoTgl8YkpTuF+OzzHqb3kYId8Jg2VXtj1WuS94oS3JrjO4+/78LjzHdy+ybXBtf2+wXmrV9NxLs/IagOwHR86yNE9foy1NoYeWZqXJS/MAfuBNU1+a2p+tpZnTpKGl2bkqdGlSxHfMlav0pUn42Y64DB5SqbGJwsKUJvWW51uxlyTIUIuQLOxC2553SNBZHzvsPDfcyofBtB86fBa43TxMg1tqHMGt/EeG20D8QPGPOtyeqrPgVuhsCG7P
*/