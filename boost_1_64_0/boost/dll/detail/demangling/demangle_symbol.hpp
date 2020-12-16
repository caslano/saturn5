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
e0qPR5rAqNQEXmTTBI5nTWCphFRXE1gqNIEXoSZQztgEOMmLXagPfEvTzq35w0ybevxfT3RZT1rp68lLkxzryYm4y7ItKFtPcI41fXFZq6V66iwu5ZzKoyyCo4wlbefy4aL0c2N43UfulbXiA/ta8YLOtR85xbFWDAfNlH1xvPd4J2X0heMqLdXjtnCcxxmYOBMUcYrrWxdY2Yh4J6BQfPjvdgVAfyTHOPyljLOHz3Kkrx9jD691pH/vSB/rgPe2I/9BYXv4Qkf4WWf6WHu4BYYb1l/8+QRlQBs5iQ1oI6jajLPeWXM1f6j1aHkbVkaA8VlNhxSlilh3EL+UUdHhx9FkLpu3yG/kCbZGCgTixjlU4tCvoSYVPRQGaMkwDbaPhlhZtU97XTjeIe8fXVmDjrl47GpY8ZCEwuT+m9QZpCX/yqqVl5SKkG834UkPJiiNSjlkhkYRi65AHdW2rrG4XhfkhyTEzbwXk+gRsBymBcJCSlQ6yyFe0GYNswOwMkICrxtqlPJCil4Y0wNh5S7z+4BWG5bDpx4GZgrZI0MvhpNTWNBQU7J6xeIb2kOQSrSBIKfmmikQpNr/1UcmYDti2bE4KvXiJZ110IzM85BerixY0LCtGsSGfafx2bNfYnugARE1X7Im8HwJ4JQoMEr2o40maCFrDpWKvgII+djfJN5BiXe47M2uomeztDucI0FfQvlxjcFx6LO6MgsJ/ssCv8G9lGWe0xMLoDAzqrfWLdOHCmWqnK78SIyZ1ZvHhtK73gsAFcI+EYXzBHDCj008YbD0lZ/H4yorjXQCsTlTIbGxlzbr046mWT9Oq0ENdPIkJz116mBJ3QgDZTloLfaOmVLSP1d9f6YH7b/+pPo793jqb+AzhkcY9wbEW8QTkXlkYd5nO5G72UsypbvZst3ektZbF4qMQh19MOe9WeY9wcqbWtKK81rwowdymZ3HkJUdhHMw/CPso2PDxQDhuI8hjgvcTwVowPwwEobJWzx++naXqy/mxhqR9N0mCePTTM9eXo3r8X+ar9nXLe5o6c9z6ro8vSKRp1P2g9qwy9MQ1XQdGJ8l4/c0lxXYxL2XB4HkK/bYkq4e/z/jEvsXeyZi8//Tw+7/J5ysf7HubZqgMatrVjUkoptVbexuM/I6LJykf7FrM34NxVdi+s48JrF94pOjdfp+lmWj75QxydsnXp+h2ydOO7AJ9K5rn3jgaJ3ekSwbvf8+Omn7xO/9un3itgN+Dfon1R9FYv6H942/t10h3bDjL8fq5hPeA23mExeOaqK/tynH6aZx53Xbqw5Yflf+3nA/c6RjPxN07Hcc4SUcTrTeeqw9YH5Cf1oPjuYD5gBy9GC0PTm/UYQPmK+X+utx5MT7ozwNH4J9IsE2p42Hv1zWSj9Mph/Wxj29g0z/6yHu6d+MovRnEqS/LtO/6OGe/qhM39HdPf06mT5gpHt6iUwf1cI9/USZfmyC+g+T6XMiMj0JewnPKM0/54FHQcAymrh8qO6uM+Uoej4RQzmh8hYO153GwY0wXnBiMTcksFBigrgEakSDVPF7LQzDQqpZlkAqm0JHQwjPcbJBDkBjCrIAOnYcIY77m2TQecHJ9WJHK6nyH2N4F1GAD7Uhesp/kTqhQulMuqIETsV+o8AuYk5L9RhBrHte1aUkfR8HIxtutZbCH7MViFeYBQmH7RgsnB2jyDiCtmk/9KA1DyGifyRl+IQ6Vcgwwhzgo+eohOOmEnk3vERcGJ3XH+81YERYQEWSjBr07KhBsD8gfM84AncjqtSRkBjCibshlfmy2S4Wx6i/lr3fPHVT9e7U8u2UUJEnNjKyqFddmyhAMXV25FfeSia0bxl4VJ37KEY=
*/