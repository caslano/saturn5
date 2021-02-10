// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_STD_LIST_HPP
#define BOOST_ASSIGN_STD_LIST_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <list>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::list<V,A> >, V >
    operator+=( std::list<V,A>& c, V2 v )
    {
        return push_back( c )( v );
    }

#else

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::list<V, A> >, V >
    operator+=(std::list<V, A>& c, V2&& v)
    {
        return push_back(c)(boost::forward<V2>(v));
    }

#endif

}
}

#endif

/* list.hpp
fygNKxV8NV4WKJk19rOQde6ySbXn7vYQm/PeuTrS/o+yBlD6oOIFxnfSL2uz+PYFifBgEVxpBXv3F1BLAwQKAAAACAAtZ0pSoHLT4g4BAAC4AQAAKwAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3Rsc2F1dGh0eXBlLmRVVAUAAbZIJGB1UNtKAzEQfc9XHPqk0F1UWoSlCFLwAgWl2x/Ibma7wZDEZELZvzebVvFB33LmTM5lds4eG7CJMvHIkyfxGPJgMz8fxAsZ3+CwazHTZFn3krWzOG8qRarBfX13W6/EVjIdXZiKWtkXVVWJlvg/gRrbFEIemmmJzMJZMyEm711gUnC+rOqIRbt/XyzF4MKsVWWEq/3TFuub9eq6xuuAqsquKVKAtOqMvIzx5IKCDIToqdeDzqpdYlH478azgXVcIuRgY4YXZ0WDTIYj2J0j1MDhF5/VP6IoqfVQGiSrKJhJ2yOM7voUzKzeJW0YJ83jT/xLyyVOo+5HBPpMOlAUb55s2+6Qmz7bNB/ur2+1+AJQSwMECgAAAAgALWdKUtiyN92lAAAA5gAAACsACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy90bHNwYXNzd29yZC5kVVQFAAG2SCRg
*/