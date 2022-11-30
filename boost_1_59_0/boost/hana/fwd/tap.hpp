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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr tap_t<M> tap{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_TAP_HPP

/* tap.hpp
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
*/