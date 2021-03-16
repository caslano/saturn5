/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    make.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_MAKE_H
#define BOOST_HOF_GUARD_MAKE_H

#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/join.hpp>
#include <boost/hof/detail/delegate.hpp>

namespace boost { namespace hof { namespace detail {

template<template<class...> class Adaptor>
struct make
{
    constexpr make() noexcept
    {}
    template<class... Fs, class Result=BOOST_HOF_JOIN(Adaptor, Fs...)>
    constexpr Result operator()(Fs... fs) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(Result, Fs&&...)
    {
        return Result(static_cast<Fs&&>(fs)...);
    }
};

}}} // namespace boost::hof

#endif

/* make.hpp
DUV6jSt6dlmwtRn4G+CDRTpk4SHgn4APA98BbuXzUJZHgPsBtwHLgY8V6ZjLJ4Bc+PAk8w3sBP4rcAfwDeBTwDeBzwC72VKBB6KFPQtkKNFO4Czgr4H1wOeBi4EvAH8O/C1wK/A/gI8Afwd8HfhfwA+AvwcOZPtjesA/AA8D7gKeDPwjcALwLeClwPeBzcC/ANcC/wr8J+CHwE3Aj4FbgJ8CPwF+BvwSuBtYjPcLvRyMAX4BrAT+jekDvwKmgHs=
*/