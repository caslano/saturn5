/*!
@file
Forward declares `boost::hana::tap`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TAP_HPP
#define BOOST_HANA_FWD_TAP_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Tap inside a monadic chain.
    //! @ingroup group-Monad
    //!
    //! Given a function `f`, `tap<M>` returns a new function which performs
    //! `f` on its argument and then returns the argument lifted in the `M`
    //! `Monad`. Combined with the property that `chain(m, lift<M>) == m`,
    //! this provides a way of executing an action inside a monadic chain
    //! without influencing its overall result. This is useful to e.g. insert
    //! debug statements or perform actions that are not tied to the chain but
    //! that need to be executed inside of it.
    //!
    //! @note
    //! Since C++ is not a pure language, it is possible to perform side
    //! effects inside the `f` function. Actually, side effects are the
    //! only reason why one might want to use `tap`. However, one should
    //! not rely on the side effects being done in any specific order.
    //!
    //!
    //! @tparam M
    //! The tag (a `Monad`) of the monads in the tapped monadic chain.
    //!
    //! @param f
    //! A function to be executed inside a monadic chain. It will be called
    //! as `f(x)`, where `x` is a value inside the previous monad in the
    //! chain. The result of `f` is always discarded.
    //!
    //!
    //! Example
    //! -------
    //! @include example/tap.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto tap = [](auto&& f) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct tap_impl : tap_impl<M, when<true>> { };

    template <typename M>
    struct tap_t {
        template <typename F>
        constexpr auto operator()(F&& f) const;
    };

    template <typename M>
    constexpr tap_t<M> tap{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TAP_HPP

/* tap.hpp
vFNk4EnoJcXQBjxRYJrshpWh1QdfSEg/iJUBlVlo9RWYWzBji8wuGMH15xfkwcMyDC5zwPZ7e5YBKm3A3yGN8Qx4XkKK3HAftpAhd2YoTH6By1EYncImMWjCXCml4fxqTzyba/qs9Dd9xCihHy/6+HFr+9nOH388ER8zev7k48fNLfrvZmVk9/5kX5LnT7ZY4mI2HafNwweWkK05kBefKxIdGtvdZu3m6Wd/u8oDBXXD4+Hic5bzwTxva8+LSUebrKOr4SghOHxJtshm8eQfkYPijZt73DX0uC16jBgufW/uohgrxhM/owbkP9U0EuUEhJ3IAYuWrO0/jx3e5XwpHPP57ouXP4oB0p8S+Oq/bj3ZlP6+tanpQ3+esILI4dKGbG1vxQ6VMMzKkG235YXJs2gX5Q2ZW9+Jd8dH7cb3aO6TrFmLhJQ9LIK0LmbT4SIrtrWmxY9JIJSNLvk+kJUhiosPqOk7cqu28hhYvRcm+uKdk/jsOqVfCR/PPhvf3vVrZ3wqza2Q0r6UDiT762B/f+3j5YDwXbKT8UQo/xUVCFGGmnwssmmalzVnau9l1DADEs8MhAJmQDgkQmRAlsmFaiyFdxtEG8cR0HX7nJ2Gig8X7Tk8oSsZ+PYr6cdV7kIUhz2Kp2AxI9EbOxMY
*/