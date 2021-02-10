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
4qiWXW9sh8FnNJlAs+3IHQr/uKg7Iqcae/hWA+LrHpzflA9nXb0XKA3ANvq11k+FnpCwaJjG4IWRU8PbRIZVvuJtQFf98gfqB80XFocnKgf0juLvmPuhbtMDjhGaehgauhxewHOhsN7TthPfdZSdGW/e/+da/1sBjPYPIex33hKJtyPMmkfzRw5a0lOUpHpTyNs7rOlYtEuBPhVJbC7bvSeEh3/8x452QGo3Tvpf7fdx/ztROu+8G52ZCKCzTsmYG91K/2q8JRNbEvMwiOzWgx/e/kEz5zKLMwnt0jiaQjpaM2yEeEOmd+o8mTv7ZC4NdG+sL/R1OPzWbuQq3kNhA1roIwk27iSUyhQWQ37GXk3y7lSn/mT+ctZx8FEorbBZtX64YtF2t1/V9PJxdqI9GAyMeiPi+V8QqyEZXw2+/kNf/6mv35p6w2krVFnGJo32+WOTxEPja0cuOfT1gtbW8Sv6lxqgPpr1OzHvo14bkf5XPuuZpvntnfnu7xc0/IkOv/5RJ+2HiPsG56X6aLiMH89RrN31sFc/HQ4wimt8pw9B9bkIx6RkncTtXv8x+Z/qvJmWrZvt88swtSMvw/Safh0mfSwK11mFPfYVXdRbl0SKc5wGlF4rdCGRTD++MtasI81gU6U76rc2+l/b
*/