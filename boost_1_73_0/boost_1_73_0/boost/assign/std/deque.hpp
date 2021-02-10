// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_STD_DEQUE_HPP
#define BOOST_ASSIGN_STD_DEQUE_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <deque>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::deque<V,A> >, V > 
    operator+=( std::deque<V,A>& c, V2 v )
    {
        return push_back( c )( v );
    }

#else

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::deque<V, A> >, V >
    operator+=(std::deque<V, A>& c, V2&& v)
    {
        return push_back(c)(boost::forward<V2>(v));
    }

#endif

}
}

#endif

/* deque.hpp
LMSigMCROVmLeeAI4AhFFuGgw46acFrP3h23qT4P7KQHS4BFwY4TkfZC29w0ivE/14tp1HhtS7ifZ9nqcfQAwUnrCybkfXGSinixgju+VzYm3Im1R2hqCAQOc6oqtOrf0RcDH/N7mAdO93Xi4FYcdOLwVhx24uhW5J+Jk5n4AVBLAwQKAAAACAAtZ0pSrjm5dFMBAABfAgAALQAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3RsczEzLWNpcGhlcnMuZFVUBQABtkgkYG2R0YrbMBBF3/UV9wNqh2XfQimUPhUCWzbpByjyOBo6kYxmvMF/X8mxoYVFL5LmzJ17pVNOtyNM9OW1CzxFKuq+l3r1dTvNbARhtW8ukkxHXE5nvPSveNaxAgrLmJXcr5Ithyy6cu6HN7rlsqwTXNd17jxR4JFrxyNyiJ+qgBMsEkJOiYJxTuARbEhVzNg3sqlXFz0u8WkPedzEdFe7z/Va14ELPrzwsBM93skPmCdU7S2Q+9cKBjLPoq1ukRW/309H5xDNJj0eDmEu0isdhhz0oCr72/XR7uLcpbXk6WldUelCyWRp6YaqWXePSKkVpAHXmcX29G8TpfP5VD3VhVyc1MSlx88RS57hC1WM0w0eA48jNWm0hqsP
*/