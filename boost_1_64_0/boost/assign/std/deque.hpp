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
x/+H7x62prp6lNDOJ0Hbm6jp7ZmjeuzggN1fI09XW2LzYXLBBXBBlMB1naUJzAjjurZcLMoSO0vQnRT9JeaHHStiKg5xkUbF+mCvlhbKPsHEB65LXFefNUeU2bWhOrpkKW9w7VkqsyuNZCEHqQLFjlT5ymirJgU7DPtRwxl5fRdji1v/3m+EoRfOeNnc32gK787hUutJyN0bil/AhFus8s+oYraqri6lP/4iGBmcTM9tLeV6iywY1IEVtZfKBHBe7aM8XI5meV/UCjwLobEjSRT3K98UmHhwvuq+QNqQAsU6pXUKj9aGgm578p4jT5N9RabC/oFSRI89p9vEkIlKk8xqdXJR/k1QpKQJezdrYBMKywdMDoOjb90MNE+l8W7aNJWr0qYacb8AX44DBa4CIgU8uzp61/rVe1Tj/du/D4P01DSxz68qdxyMUB/dveLgloWKoy8KnfKe9TDgKoOaGwdeaukwu0QLd8lod+vdMxOEDUa5sAIgZo88UXLZP5XvyXfaJ0l/ZjS3sfPJcP9siCvksWDkLnhtqC9r8f2Uf0fG5XlzMEISUt6Uiw==
*/