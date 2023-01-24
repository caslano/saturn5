/*!
@file
Forward declares `boost::hana::ap`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_AP_HPP
#define BOOST_HANA_FWD_AP_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Lifted application.
    //! @ingroup group-Applicative
    //!
    //! Specifically, `ap` applies a structure containing functions to a
    //! structure containing values, and returns a new structure containing
    //! values. The exact way in which the functions are applied to the values
    //! depends on the `Applicative`.
    //!
    //! `ap` can be called with two arguments or more; the functions in the `f`
    //! structure are curried and then applied to the values in each `x...`
    //! structure using the binary form of `ap`. Note that this requires the
    //! number of `x...` must match the arity of the functions in the `f`
    //! structure. In other words, `ap(f, x1, ..., xN)` is equivalent to
    //! @code
    //!     ((curry(f) ap x1) ap x2) ... ap xN
    //! @endcode
    //! where `x ap y` is just `ap(x, y)` written in infix notation to
    //! emphasize the left associativity.
    //!
    //!
    //! Signature
    //! ---------
    //! Given an Applicative `A`, the signature is
    //! @f$ \mathtt{ap} : A(T_1 \times \cdots \times T_n \to U)
    //!                   \times A(T_1) \times \cdots \times A(T_n)
    //!                   \to A(U) @f$.
    //!
    //! @param f
    //! A structure containing function(s).
    //!
    //! @param x...
    //! Structure(s) containing value(s) and on which `f` is applied. The
    //! number of structures must match the arity of the functions in the
    //! `f` structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/ap.cpp
    //!
    //! @todo
    //! Consider giving access to all the arguments to the tag-dispatched
    //! implementation for performance purposes.
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto ap = [](auto&& f, auto&& ...x) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename A, typename = void>
    struct ap_impl : ap_impl<A, when<true>> { };

    struct ap_t {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const;

        template <typename F, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, Xs&& ...xs) const;
    };

    constexpr ap_t ap{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_AP_HPP

/* ap.hpp
FV9qxor/vQ9V3M1NHxBpmglCMy8DCGhlVbj84vzxO5XWsZY/pqWm7ZtqvuS/38dWxRLrXHijs5nPyVA0NNWmOGXC8ub0UZriN+/T8przAXdeDs5F4IJ1oQcaBR6NLhzE0znqIPXA4lmC2tpbwSIHM0Jy/80ufgIdhUClopidd/7yIioZChoGgF2LCshmYdTFtwKRgZ4+359wz/EArxbQ5OAO30tK0FYR5PE1KAH/raZp9Nn+LIKeRFVSZxRDJ/gmKoFrE+nErRNqSHzxshn0/YlH/gSbf+g3qLSvNqD2DlSdaQZqd2hFD/huPvBqC31w/vn8y2k25D0iKLFF2e+RLe5tv4Qt3ph/GVt8eO4StphrRIK+YFEI2lbZgy0enN+TLR66QkV+TVmSLefXQU5oPRO/yXxJ632choXdpBYWqiQUGtl12EzyR2gUWYx+swTME2g8GUDhTZ9Gv5Yfv5FyejFpoL/v/j+hjv9e/tAvcafcWtFEHeUEX+2GpnZhTL4SUyO6ELuO2uAjqunR0ANHNQr3lqMaG6yt1w/2ipqOp5qW9xLl8WPbFe5dPO9yAvxKRJ6QP4JaUu/9iJXsbZmKmmN5lTTQ7OB/ee9qA82YMhxoCnfQQHN8faZCqz8bsAY6UQNWzd8bSxMPjG7Avgf8Eyrv1Bhs3PMjFMCkwjoccUpg8mnkj6ACIkhXXp8LmNIlORv4SfQzANgCJMCb
*/