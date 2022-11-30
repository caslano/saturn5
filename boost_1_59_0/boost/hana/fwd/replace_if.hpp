/*!
@file
Forward declares `boost::hana::replace_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REPLACE_IF_HPP
#define BOOST_HANA_FWD_REPLACE_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Replace all the elements of a structure satisfying a `predicate`
    //! with a fixed value.
    //! @ingroup group-Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor and `Bool` a Logical, the signature is
    //! \f$
    //!     \mathtt{replace\_if} : F(T) \times (T \to Bool) \times T \to F(T)
    //! \f$
    //!
    //! @param xs
    //! The structure to replace elements of.
    //!
    //! @param predicate
    //! A function called as `predicate(x)` for element(s) `x` of the
    //! structure and returning a `Logical` representing whether `x`
    //! should be replaced by `value`.
    //!
    //! @param value
    //! A value by which every element `x` of the structure for which
    //! `predicate` returns a true-valued `Logical` is replaced.
    //!
    //!
    //! Example
    //! -------
    //! @include example/replace_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto replace_if = [](auto&& xs, auto&& predicate, auto&& value) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct replace_if_impl : replace_if_impl<Xs, when<true>> { };

    struct replace_if_t {
        template <typename Xs, typename Pred, typename Value>
        constexpr auto operator()(Xs&& xs, Pred&& pred, Value&& value) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr replace_if_t replace_if{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_REPLACE_IF_HPP

/* replace_if.hpp
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
*/