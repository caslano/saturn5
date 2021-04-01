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
8d9LlbLbDGT6dlCtQU2BnqHzR/16qe1rMH2GzIe05564lq2YIGrcckYnMOAW6EFVQgfGiysR/3la1do64CxIhebsPb9E6nBeBiOqwP+3NvYn7LpuaGZUo63+MW92y3tpkD6UGaUFdWvW/VQsImZz9s6BXszz4FxkQlwCr/NmBNeqTAdCloZ1wg14RORW3MCbKwfyMnKV6STkMG14PpX1B2RYmn0/3ho3tkfVP5E0RI2MBfYzikRDoQQ4tcsMrpp1gDpxPn8gSBZhvEKDJITFyJSXTe1GrDmdtCM1kILC3u9LA0OF55Gz5aYn5xrJ9iOhA9XQFYw2Km7cxEKj47mhL0TAdHTLPApEkUb9hVW5U4gJwIvy8Q0yUS22mxt+LDiMNObWwvaXbfam4dU7mIyJPbeRR4jyYyjNDjJylpzkuIBY2IE5GAJ06t5cWksc5Anp8edijjb9GUhAgmWU6Fyv9SozjZwORDKfo73lEx+z9GWcPKIxCmcpe3J1dmepDbEud+9SN817dxQBX21WbyjQezXRcIGz5GPElxJCAn9+bqmhb3Ev+VDNMLy5uw==
*/