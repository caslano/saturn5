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
33J+OCEJYLiDNbLy9QEGJynADwMA7bKHBY2Y/iNyoA9CtBKrqRXB+EA5szYOs/dZX0yGm16WDncbLrK8cL2w4TmUlP222Z1S2N6xCrnlXs0ZkdsaRKwVqwLFKQbpSX9G5A5shqc+9MPzb5P6CxeRyPN4b+4Z1AyxGQbk+qbbDDLdkyWi5NVXXR1yDJ1zkdSFurf+bAMrzMPGkV1v7tjGH2uCNhhbxhM6XFlLqsubkvvk1LCtcjuebZ+gn3dqimPGVHsAuSIbRvjQeTzr+paM9rGKqB8uTXASURifShp2t8pyLnW6nbGDjKpU75HO2Cq3ZQFr3kPDEGAQLl7KBU35b2JNXi3LaU126uHmA4sFJDjnVnxohJSwIRaBp6B6JktCDRFri/k9notsmvHQEBMIGnhu+AmGIiwneQtn1waqljXYejUKkY7FhAy7b0C5VW0G+5e2t9c9KTsotT/7+2IqFumXN2G0ahmA1O5/8+dTkTiowK4QG3xZpkWemdKNlwzxb4kIF05yOpszmnKPWAMkZ5g3fMF+uCUBXKAN4wzvpX4Lz9GdJh4rT9r8hw==
*/