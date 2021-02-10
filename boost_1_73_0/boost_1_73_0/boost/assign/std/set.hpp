// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_STD_SET_HPP
#define BOOST_ASSIGN_STD_SET_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <set>

namespace boost
{
namespace assign
{

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class K, class C, class A, class K2 >
    inline list_inserter< assign_detail::call_insert< std::set<K,C,A> >, K > 
    operator+=( std::set<K,C,A>& c, K2 k )
    {
        return insert( c )( k );
    }
    
    template< class K, class C, class A, class K2 >
    inline list_inserter< assign_detail::call_insert< std::multiset<K,C,A> >, K > 
    operator+=( std::multiset<K,C,A>& c, K2 k )
    {
        return insert( c )( k );
    }

#else

    template< class K, class C, class A, class K2 >
    inline list_inserter< assign_detail::call_insert< std::set<K, C, A> >, K >
    operator+=(std::set<K, C, A>& c, K2&& k)
    {
        return insert(c)(boost::forward<K2>(k));
    }

    template< class K, class C, class A, class K2 >
    inline list_inserter< assign_detail::call_insert< std::multiset<K, C, A> >, K >
    operator+=(std::multiset<K, C, A>& c, K2&& k)
    {
        return insert(c)(boost::forward<K2>(k));
    }

#endif
}
}

#endif

/* set.hpp
76wYaYULpbhddp6Y36m+FuhxtEuQHE0UkkTIIRcRgscZk29hBFnGI0cMPVvezP4ireVUPdkfCFe1URWG6MQuY5H4MghTnf4fbdQvUEsDBAoAAAAIAC1nSlIGwULd8wAAAG8BAAAnAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvdGxzdjEuMi5kVVQFAAG2SCRgTZDNSsUwEIX3eYp5ABP8A6E7EUThLgR1fUmTuW0gzZRk0tq3d9JeweX8nO+cmROloQOOZbkz9+oN49zBd0H4On22DlCGIaNlzOojE5OjWLo2Vc/eo+/gyTw8mlv1IisD5W1nKa21eqXssICrOQIT1AMKC+YSKMEVHhsa1hETOEoJHYc0tH0LGSfiQ1Qwi84o9Z6Aov+DFKDL1WAMUszcyKst4MnVCROj31kx0gpnSnE77zwxv1F9ZehxtEuQHE0UkkQoobAIweOMybcwguTxyBFDn23ezP4ireVUPdkfCBe1URWG6MSuIEt8GYSpTv+PNuoXUEsDBAoAAAAIAC1nSlLv0fQT7QAAAFcBAAAnAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvdGxzdjEuMy5kVVQFAAG2SCRgPY7RSgMxEEXf8xX3UcFdq0WE
*/