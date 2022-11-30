/*!
@file
Forward declares `boost::hana::at` and `boost::hana::at_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_AT_HPP
#define BOOST_HANA_FWD_AT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


namespace boost { namespace hana {
    //! Returns the `n`th element of an iterable.
    //! @ingroup group-Iterable
    //!
    //! Given an `Iterable` and an `IntegralConstant` index, `at` returns the
    //! element located at the index in the linearization of the iterable.
    //! Specifically, given an iterable `xs` with a linearization of
    //! `[x1, ..., xN]`, `at(xs, k)` is equivalent to `xk`.
    //!
    //! If the `Iterable` actually stores the elements it contains, `at` is
    //! required to return a lvalue reference, a lvalue reference to const
    //! or a rvalue reference to the matching element, where the type of
    //! reference must match that of the iterable passed to `at`. If the
    //! `Iterable` does not store the elements it contains (i.e. it generates
    //! them on demand), this requirement is dropped.
    //!
    //!
    //! @param xs
    //! The iterable in which an element is retrieved. The iterable must
    //! contain at least `n + 1` elements.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the 0-based index of
    //! the element to return. It is an error to call `at` with an index that
    //! out of bounds of the iterable.
    //!
    //!
    //! Example
    //! -------
    //! @include example/at.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto at = [](auto&& xs, auto const& n) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct at_impl : at_impl<It, when<true>> { };

    struct at_t {
        template <typename Xs, typename N>
        constexpr decltype(auto) operator()(Xs&& xs, N const& n) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr at_t at{};
#endif

    //! Equivalent to `at`; provided for convenience.
    //! @ingroup group-Iterable
    //!
    //!
    //! @note
    //! `hana::at_c<n>` is an overloaded function, not a function object.
    //! Hence, it can't be passed to higher-order algorithms. This is done
    //! for compile-time performance reasons.
    //!
    //!
    //! Example
    //! -------
    //! @include example/at_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto at_c = [](auto&& xs) {
        return hana::at(forwarded(xs), hana::size_c<n>);
    };
#else
    template <std::size_t n, typename Xs>
    constexpr decltype(auto) at_c(Xs&& xs);
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_AT_HPP

/* at.hpp
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
*/