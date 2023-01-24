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
Om3fhryLi+U/1rR7ferm0N/5kg9i8veHzmpTrpFHtDRl9Hi/hNtHc1qOGNP/+NlSsZ5+k2dndDKVo2bgqH71o8uNOjZF2nPwgByfWze6XNV7tXw9Owamjll57/TcJjPHnzgojr1adN7Iw2e35c2PyB3m+fS3qpU9uk/o2LdP2deJLyK4L59Vo8tOmDg1u92C12vD+FKvO92ac3RdxLyaXeusvFateNzhR1k1Br9DtCLoEbePwGt41ZtLi+5rVyfev2b3Mb3PP74mSB3/AlZVuecX2zZN9LoX8ueQP7+tnXWQ/7Y4iXSAFaCKAKrSm0xo9H8EVo63rVG0BxFRaUNV9EdQBaAioR9BlfafQdU/Hjn5nxDc85/Qq9mBIV92on8ZcFab/2hEwhdzS4bXcStT3ndH46VbU59EndqbVXlLXL9uAbn38+88nXm/0TL/xgdfvnywflvM6Ln9Wm5t9GeNbsM8I0duerFxnteW5ENr8+uGHxr1ZlTrpfPP1wjeviH36qbpY6tM+/Hx8Ffd/Prtv3NiXNbV5bs7uW2/Hfm0e4WEGqt6tHz569KXu6+O/7pnn4isbQPnxVXvtffww5jue2Y80Re1bEgVPSW5+VXveLmWW8vRfedLub8Mmr/sx9TwoMUr7jw1pww7ETm/c7VeKxq4B29sfmhL29l3rziPjXvT6tzblste1Uy5dN9cp91jJx3bXyU2J0Z1zfLa
*/