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
7Zg9XDyEgFpJI3MprI050q1iksYOp+s0jf+XUvuUjcLE/zQd0x6kZ1js7DrDMh358RmWdDyNxudUpeRkmxkWHmvmNNYsLopaWIvJdCrLl+K/AVBLAwQKAAAACAAtZ0pSqesTv5wCAAC7CAAAKQAJAGN1cmwtbWFzdGVyL3BhY2thZ2VzL1RQRi9tYWtldHBmLmVudl9jdXJsVVQFAAG2SCRg1VRRa9swEH7vrzjSPCSbG3d9Wks3ljm0M8uSEKeUQMHI1rnScCQjyUkK/fE7OSldoVtg1A9TiGWLu+/79Ol0x+/ebhwdw8GRNv+UBs0+YWb0T8zd68Fp+gi7HyXd0XyAIoTnjMe0DwczHqHXZKR7jkv/nqYHaO68MP8IfeJd6l9p5eiY8iJdPRh5Lxz0oj58OD//CCdwdnp2GsCIKYklJA5VhuY+gEverHwRbLsdWPwcADpg5aABWghpwerCbZhBoPdS5qgscmAWONrcyIw+pAInEApZIkTT2TKeXAewETIXhPGga7BC1yUHwdYIBnOU6x1ExYwDXVA2YXNpHeHVTmo1IGoEh2ZlCcKTs9JqYGsmS5YRDXMgnKvsRRjmtSlJech1bsP8aesD4Vb7XSxJwYo9gK4cOA21xQB8XAArzWXhZ7KCFqs6K6UV
*/