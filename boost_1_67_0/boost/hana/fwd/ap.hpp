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
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
*/