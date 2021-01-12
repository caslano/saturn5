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
acnU6ygBwrEfK0Lskr9E8oo2X49KFXRHKm03rPtv1Ee6BgqOKRHH8PZpEPD7P2t2U9oedCFUSNBVpiz1rAp/CPXBQjSOomf97Q0ymuGtHHlKnyvEWHqlPvmJhDGdjRxxHv+5U+oEVUKX37DuFzc6vH/FNa3G4b0RVwjXA7g+s8jhfRT3KV9xeCfdTpvlNCkOy+LWAc4B/HM6nQNgYBxv+HfDugDgv4Lrelzrvwp4O/+4E4Mn
*/