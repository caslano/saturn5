// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_STD_VECTOR_HPP
#define BOOST_ASSIGN_STD_VECTOR_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <vector>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::vector<V,A> >, V > 
    operator+=( std::vector<V,A>& c, V2 v )
    {
        return push_back( c )( v );
    }

#else

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::vector<V, A> >, V >
    operator+=( std::vector<V, A>& c, V2&& v )
    {
        return push_back( c )( std::forward<V2>(v) );
    }

#endif
}
}

#endif

/* vector.hpp
zovymQw9tV5QudUNaANNBLMV6lUguKMtvAvBzXQDKCtQsZB3JzxT8JFrs1BVx0WjIdsQ3hIL2DEXXyBcOGP3hn+xZLI14jtWek9nwa4/Jmq2wdQusvLcvz7s9z9Vs+yI29/CXqHghy2RYjlQ/xWkCa3Cc1I4EBAKk/OHThjBnMOoJoQrRUijYBXTvPfFprktnoqrH2J1ITOBljoXks3KnVFMRyX7WAvfCLxxG74BUEsDBAoAAAAIAC1nSlJkO7iFgAAAAKsAAAAqAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvdHJhY2UtdGltZS5kVVQFAAG2SCRgTcxBCsIwEIXh/ZziXSBRQRCyEzcuXHiFMRnaQNqEZFLo7bVUweWD7/2PPA8OWtmL0TgJ3SUVh2sI2Caa8lQaNO/msEh95SbIXUtX+jgJDhd7Otsj3VhlyHV1+DIyxtCzSpE5NPBfcisK+3HPItffBSnOAh1Z4XtNCLGVxGuz9AZQSwMECgAAAAgALWdKUmM067D2AAAAlwEAACUACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy90cmFjZS5kVVQFAAG2SCRgbVBNa8MwDL37V4jCbkl/QBiDMTpWaI9jZyVWUoFjBVvO
*/