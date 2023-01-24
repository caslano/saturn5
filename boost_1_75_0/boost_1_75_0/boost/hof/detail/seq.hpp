/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    seq.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_DETAIL_SEQ_H
#define BOOST_HOF_GUARD_FUNCTION_DETAIL_SEQ_H

#include <cstdlib>

namespace boost { namespace hof { 

namespace detail {

template<std::size_t ...>
struct seq 
{
    typedef seq type;
};

template <class, class>
struct merge_seq;

template <size_t... Xs, size_t... Ys>
struct merge_seq<seq<Xs...>, seq<Ys...>>
: seq<Xs..., (sizeof...(Xs)+Ys)...>
{};

template<std::size_t N>
struct gens 
: merge_seq<
    typename gens<N/2>::type,
    typename gens<N - N/2>::type
> 
{};

template<> struct gens<0> : seq<> {}; 
template<> struct gens<1> : seq<0> {}; 


}
}} // namespace boost::hof

#endif

/* seq.hpp
4MzgQfzlkmkdgen5ldz7c1/zqBMIZ0XE3sHPtybBA7rUPYINvtrLVn9je9lLBRipwk/dU3duo7fYVKjbof5P2Z6Nn5sH2JJN3+wlXxWUfa0CClmtk50kMaq2X7imneYZ8M1t/PsyVWXHHDfP0ZHz8RyGt+OAyyk+PhOohrBfoE9GfequCq7ZPByWa3aldnEW2r9PBfxXtHWOj9bRLN1SdwhsIUqtAj1OG0F+C8nTw1lsycomwXhVYQ2T5joGGON6VwJKa6mOUioF8sTjyo1WOu+luSjhBYZwllt86suPl6u7OvHJwGipdkGp531LzFqf/zlP6TjW0zse+iCfK+jxvMO1OqiAfjHjgrfjeh6qheufufE9u8XhzZ0URvZY1d3oFHdKCUNCsAOiIrHCnGomnMhEUQx0yVphIkK3GIS/T+9xAim93mCbbGBMTuo4PNlWlhlOk2Xtutka7mJAhi0+zTvnKMtQsOjezTGU+2Viokh1ibmjdrqgdKps8jqMWtXc1dCiwNr4B1u+ga/10uUYdi16T8ncmRSbZQ6Sps5OE4/aji9zJWMT8CeW7RELbKm5RVQND8eiIbcOnsjdVM8iPhgJoE1+LEsZjZYmdrOEJI+OREybZ962GZUjI7dTDyUWBvcEZkKiPSi7zwuqLtTu6lRf7l+l3EJegMgQ2dXG0uiBnEY0+PK0hZNG9mHk8cnVKzzt2slEtlV7w8Gc
*/