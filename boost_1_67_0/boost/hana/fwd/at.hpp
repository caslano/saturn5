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


BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr at_t at{};
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_AT_HPP

/* at.hpp
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
*/