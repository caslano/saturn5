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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr ap_t ap{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_AP_HPP

/* ap.hpp
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
*/