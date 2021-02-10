/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    tap.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_TAP_H
#define BOOST_HOF_GUARD_FUNCTION_TAP_H

/// tap
/// ===
/// 
/// Description
/// -----------
/// 
/// The `tap` function invokes a function on the first argument passed in and
/// then returns the first argument. This is useful in a chain of pipable
/// function to perform operations on intermediate results. As a result, this
/// function is [`pipable`](/include/boost/hof/pipable).
/// 
/// Synopsis
/// --------
/// 
///     template<class T, class F>
///     pipable constexpr T tap(T&& x, const F& f);
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [UnaryInvocable](UnaryInvocable)
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     #include <iostream>
///     using namespace boost::hof;
/// 
///     struct sum_f
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
/// 
///     const pipable_adaptor<sum_f> sum = {};
///     int main() {
///         // Prints 3
///         int r = 1 | sum(2) | tap([](int i) { std::cout << i; }) | sum(2);
///         assert(r == 5);
///     }
/// 

#include <boost/hof/pipable.hpp>
#include <boost/hof/apply.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof { namespace detail {

struct tap_f
{
    template<class T, class F>
    constexpr T operator()(T&& x, const F& f) const
    BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT((boost::hof::apply(f, x), BOOST_HOF_FORWARD(T)(x)))
    {
        return boost::hof::apply(f, x), BOOST_HOF_FORWARD(T)(x);
    }
};

}

BOOST_HOF_DECLARE_STATIC_VAR(tap, pipable_adaptor<detail::tap_f>);


}} // namespace boost::hof

#endif

/* tap.hpp
skjjUFhyUK+JKhZHglY+XK6FWvK4ieKYGLmh5Vsa+sllCQEUYDs/xjTtVi9W4MqckhDCl0wqxpZslaUJLb3GtEASLYnLcnUB16rALZAkaxrCKh0k/H1BQcgKhvwqCKMAqlRf+CKIIir/MDI4ZLwVb7xyyE3IsEhJZjFqRq4eJDiMcgYWT95FeZrgqpCXZuDWFrTB8hbfq6/OBEsTLYNMx9A8MD14BYTl26BS72z25e6uNzk/Pzv3pqevxsfTI+/l2fT0AhcUYLxgzYI0Yuzbk5A4Wsr6eprss6yGbXo6u/zmm+nhdHJ64c0uzs7HzyeEZvuZllSJzxZfGfrzACNFk9weA5SFRg7VPtuXHL6QZMhZe3pvxleufBF3Kfw+y6zogQL9UNGc4JAfc8yPa4pz4HalEsyxHqRHwAAeHORuOq9a4J1sQOv92/Hp0fFkVLapknI321mgPNcZj0MY6O8vbnRVlS+G7J5m58p2A9Oz19SwKgJW9TuFlTkmZPP3luzjZhEBhN5bXGcyEjGTc46Q3o5Klsxc3tvtZzpY9q33b/t65ttIoOo/tgdTWP9LhT4EUCVireNsYLouzNaQJgVSNa59Y1xKP1VLyJQOuiNbudhWtbLWCNeooHvFqrqSHhZntKLWQLm3sly4beHg
*/