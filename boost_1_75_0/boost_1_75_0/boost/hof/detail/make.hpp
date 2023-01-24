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
EQdONCzfp22T07OK+o5RFLxY2L/DNqvXKX5D2xLX2oThG4+FdJBNoldGs9HWUQuRIhlpmYDoaXt3+1Mq4Ssb68sQ1iTjaP1N79WEU/rTuH474fprzN4P+Lmwd/uGm54dGEAcqWb3MN79Xc5l+gaofchVMA1DW/lQBuSNcSGphG6IObqYhc6WYPMV1BAd1LkXt/TQKPelv1+8FuZA032EDRBkPLN6V/PRRUocC2QWxQd8p5xZU/uTfjGcWag10bcna5PRAU0xgoazvlksXBUaG6omEUNbtTONuOg7e1DXCUlKDXKQtz2WXo2zfZYJjg23++aS+bs7oHnIom6WeZPYYPPAnYHFKCIrONfZl+Fm1CcHxyYiFQ/mY77b9bESOSfl+Fjwfo9PzhY8cJ9Psal5eE/RgH+iZhEnHBr7e0lo9sVlWk+dIW27bpwdb7ZpvITIvS36HGjw0C+RtF0qv8dNqnk5HrwhhoI+r6iexp92C9XNmKaek5ntywEHzwRTjhsGUs8fAnhQ9OgePY7ZPdzEt1fJfg9ihp+mZAZqUGhCWCe46kZ2aXhRArCFfs6BU7NfZTNPz/xMzAECTdXUUymhfBBiDxImjhTaP9sZjX7M9RYZr4/EzEN+2NQiXqAeDJdayv4UT6FMQe3Hp2y3kzj53TauZzhR+1xh6CfcQtV0eNxhwLWV5p0cNvfMdO2zK9uxNahGdV0IbJXG3/Tk
*/