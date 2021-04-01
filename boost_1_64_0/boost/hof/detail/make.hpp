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
63uZ1j8N/n5yHsukbIdz83k0Wnf3+HFAgEK0ws7D4KP9dFFITZbL+imHTg+IABlXgvbhCpLxT2a58NinS++paWZda4ThOZuQhr2r8QIAVKo7Ia9KOmMI7378hBfs34UpdAAq5f+96WOSzEEWfCkRbLSfbxp5uxc/sDhd7qge6Mb80ZYgvTQiA/5kCazX/4exoQjD0Px5MW1wAyY9cUSTHdY/qDnM7qUM9lRXxqnwXssE+Yrjr6ebTPKq9hbc+MY/W7uccGR7CUZtYKoaSGP7mvN6QAvqloSnWyzLkO4cJdkqXdDtDGIPiEQI1E7VJXBvHIaXAu4hY2ZZy7Jj0BvU9KPtmelu3LPVXmf7hQXcosPAn9w/iouE2mLFxQJkkPunHBObAQhdHavJ6BxGAg6xH29LF/yz1c9GccQibuAMFCa8gQtFIn0Wd9BzKUQKAI6g883UyIpE/PJZ3ujvLAdz3pfqnwCzVLrKxblWGoUicgDKM0J0ovvHhhfCDKyZbnKqR9CZ0114Krr5sVZU2b8V8hH1A+yg7dnQNtJBY/fv1bQrMFQ4ySPwgYH5Mg==
*/