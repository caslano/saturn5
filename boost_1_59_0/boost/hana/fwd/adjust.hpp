/*!
@file
Forward declares `boost::hana::adjust`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ADJUST_HPP
#define BOOST_HANA_FWD_ADJUST_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Apply a function on all the elements of a structure that compare
    //! equal to some value.
    //! @ingroup group-Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor and `U` a type that can be compared with `T`'s,
    //! the signature is
    //! \f$
    //!     \mathtt{adjust} : F(T) \times U \times (T \to T) \to F(T)
    //! \f$
    //!
    //! @param xs
    //! The structure to adjust with `f`.
    //!
    //! @param value
    //! An object that is compared with each element `x` of the structure.
    //! Elements of the structure that compare equal to `value` are adjusted
    //! with the `f` function.
    //!
    //! @param f
    //! A function called as `f(x)` on the element(s) of the structure that
    //! compare equal to `value`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/adjust.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto adjust = [](auto&& xs, auto&& value, auto&& f) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct adjust_impl : adjust_impl<Xs, when<true>> { };

    struct adjust_t {
        template <typename Xs, typename Value, typename F>
        constexpr auto operator()(Xs&& xs, Value&& value, F&& f) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr adjust_t adjust{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_ADJUST_HPP

/* adjust.hpp
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
*/