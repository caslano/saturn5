// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_STD_QUEUE_HPP
#define BOOST_ASSIGN_STD_QUEUE_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <queue>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::queue<V,C> >, V >
    operator+=( std::queue<V,C>& c, V2 v )
    {
        return push( c )( v );
    }
    
    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::priority_queue<V,C> >, V >
    operator+=( std::priority_queue<V,C>& c, V2 v )
    {
        return push( c )( v );
    }

#else

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::queue<V, C> >, V >
    operator+=(std::queue<V, C>& c, V2&& v)
    {
        return push(c)(boost::forward<V2>(v));
    }

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::priority_queue<V, C> >, V >
    operator+=(std::priority_queue<V, C>& c, V2&& v)
    {
        return push(c)(boost::forward<V2>(v));
    }

#endif
}
}

#endif

/* queue.hpp
Z5z2tMe//C5QRmIRVnDOLRDc/FTzpv1fn/PntLdrxi3QD8gwADkmuoDDIRBX1mMNOgEuEutF7YPwUPK+ufzubMks3sHaQfiKvyhZIJE9rMZI83jZUONTXINZXAHk+8RfCHZ9+vDqbw5QjGcZuwu9NZGSTcrdIFdKVtdL+U57kfRIVWbr1X4VWbYw99lDL/87JDXcF287JnoP8soZY+uV65XI16hU11uv6Uoxl7VstcjPDcUWmBe7xEjP65gRGp6DklasBnN/jJcu9BsoDZ+XKdaP2UEKwygvVKM7fSGgFT7VYjQtQlMlkxOwiy9SeBKSFPwVXkN48C3ZjxBKxS2QAL7WSigLgbiKZYXaH3Hm5mnE37Hgqu8qg+3OidAihe33XSf++qgKPr+UuOhtgb8moRC/LFHuLGpVajbiWBIMYtKeDLWOS5onbJIPwltEiz1TFNiuONX5V34+KtBI/aSHfQjkjEyRdaW/RwLp2PstR6XFu4edRKwSY4G4vTJknaWnlYHXOXZyxFDyp9J4UEOx1jYHNUrs572HSTOJml31LNijZ+I8rjY34d3UEA==
*/