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
iPYYjK3Fac/5+H/kg3/lAj9gOwc8j0Svv8Pt/zs4bdUpWiMiFY5JaGHNYvTfninxz7XX1vMydsh73tdg52D8cuXL72uxC94/RcNRk+2r+CnRlnaN9bHXLp/QQciSFGYLMsSTDQQ+TGLT2RNQmtZsyyRuD/eEi0Qf7QHn+yPeU8HJBUIQ4ncYeiQP/REqhaqJGENLD/vYa3b5OJL1LJLUf6jm3oLM21NY0+1geotTHfzp4EQf0+/97In1JJQwM9KMAf4lmMnmSHOcmWpa3maFmQlXsMc8BMV0DvrthlUFkuJjPyMqlWST50SiRwIJ8mg/JsxuXx7jyxI2FleQi8wPg4vK4M4h3yW0LguZ7YeMTkQG30DrYjH2h8DrwWDrf2bjHMkPozUMo5An+yM35iETnihETUM8P1f/GrvU///zv/7niJUTzs4UGaPvdi9Sa0LohGdFnTyc08fomdiU4ezkRHuTIu5utYu5OJdzo0iYu1dtdydXpzGis5NrukE0UuajLcVJERcnKt11mXMKBUHy4XOufo1O11i1tkOHnwa+rFkzU9F+SCned0L6mFJ1yRjXdDLGZVK6i7OTs7NXt7InZtmPAe1Fir6/Hic3nHm4fSEu7VzdSzq3i6BLkk+sF54lvdp3GxTfp3/v5AH9aV9SzNroUdKjbc+4fgP6x9EVSYC1xatkqVZ9eiQNGDSgV3JgowFJiQMc39dIVyWV
*/