// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_STD_SLIST_HPP
#define BOOST_ASSIGN_STD_SLIST_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_SLIST

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/move/utility.hpp>
#ifdef BOOST_SLIST_HEADER
# include BOOST_SLIST_HEADER
#else
# include <slist>
#endif

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< BOOST_STD_EXTENSION_NAMESPACE::slist<V,A> >, V >
    operator+=( BOOST_STD_EXTENSION_NAMESPACE::slist<V,A>& c, V2 v )
    {
        return push_back( c )( v );
    }
#else
    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< BOOST_STD_EXTENSION_NAMESPACE::slist<V,A> >, V >
    operator+=( BOOST_STD_EXTENSION_NAMESPACE::slist<V,A>& c, V2&& v )
    {
        return push_back( c )( boost::forward<V2>(v) );
    }

#endif
}
}

#endif // BOOST_HAS_SLIST

#endif 

/* slist.hpp
j9nLxb2Q3SBnQBoLEZHoE9/JpCV+8h0jKYhOUxqYDb9RgU+8XMOTsQe5QvHX6NxWiRKR3wNkJ8f+5ucUYO8ClnKjJ4ICBn7nYTTTZNVSaFIk1RIASRymKJSpuhKBu240qOwKufSUKXpaPqgVooaAqG/3Sv1lWzoaeYtQFJwiUlsKPGq4EoI5/zr8YQK3v/v9GIgk3yHPCUljDP7KBqozEkCABVXD1hAHeZQP32q6PyZCZWMMONUE1Qk5bemLXp2BZ1zK1i+6EfCgHRk4nya7oHPGkIP9PQx5a9LhlMkVu5KA/Dc3tnUh7N5kYf6LFFoOIRgi1loLGn3hrds15H569XRIsCAz+v/CfRZAvsoLjBSSGzXgjWXad8AbAZQko2f3r185vPLZ9vUJo9oZtNMvU/mL+eZCHs7eqNa65LNi2eQZR0BNzw+Qubw106CGJbMsfcHlL7vMZYGv69NoDkmf6O0QqokWIqZ3l/xL/vvrelHwpwcYh0/r9YdlnsMpATwsb6os6SGzwob2RY3XJWkEet78yvxz4U7gBhbvNpwRi1ioMp8OPfaiS8E6OQ==
*/