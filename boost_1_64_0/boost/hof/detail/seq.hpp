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
NL0ieifkGUoOKMxjkNp7TVhYQC4NoSdmHFQY9a9b2LnnpFd93pr9QzZy/yYeqCdoLbCciXWjiCVTddLO9eDq8qfQyoPdHCzcYEvWbj17/z+9vV4sZzJqS/sRKmKazDawkZOlOG9mVJFwOVTcbgtWDjqAtpLWYM4o654WEAXZsHAoZVKyPtTa3y/3blmw/XaGrXLStyOeei0UZWfJihJRe3qkpjQXtncWZiWDStBmI5Sq9P6YVzWLXAYP0Q6oK1IZqPoxzB6yWFqucPzjMYTCU5XOtTAoIdcYyjip2hMWR05X/6tGKsXrmVOSVqj8jregDu2s6Rz9/LeS1bR6j5KBr+qSseRo2nW/BeEffnMBFEaYKQBhZgHsOS5po+wSkysNuX62oLwjUvrqTkipzLTJt/Xi2SUhTBj9jzSzIRCUqdeeVxrxSlWDMjSrdP1jvGGYSv/4o6xje3dpxfkTfLMKsZQObU2Mblym2CpCEFZ3b+clOJRR3yWfkmpZgo6aQawp3GXyG9KDbupc2IvsFIyMBNtMkVih7mkkB+JKYZ0aY+drn+xelZu1hNJvIw==
*/