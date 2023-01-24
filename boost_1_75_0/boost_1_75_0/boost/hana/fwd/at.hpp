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
WO03Vz6PpOo7CkcDoBRqAHYlRf+2vyMr9pKsULm7RpIJGpbXSuiaeb9tl6NL1xYrq8oBXcSVzAqs36OgayN0fUZhb/BN4Ra+9+tLDTbPrnV3GGxo1WMw2jKkMFj8fA7rFt9DRqjg6yO6ZTQXhTXehjVeDrUhS2og/ts7fPHXccQKdvGbjcogQ4uuyXNI8U/Svof3RhxVwSn57DQf9Hel4VoV4f6Od67WcCx8ReEeLQO6+O/S1Ia7eQQJc0K4H1J5BGvYPgLZ7wRuwpZYeKaMKvfIfnld7DRe0S+e1itoFeMfr/ibYEO3b8IfkA0fFJBrnc1aRYkD5d9ml+DLE25gy5/miCt+qOg64xReZcgKRy/j0Zv/hnL3s3/AftnEr0H1lyV4RUyIGM2hMbTBjBdbZWB3X1QklEz8a4PSEWD+nqIUeX72VWT1+q04WM7SBC1kegoGj5ESiEpT3L6sP4qSnydwNiR6IxH9BD/696sRXfMEEf3EJUQ/fBGJ/iODSvSm61NWVLbKc0j0jcOBkUts/LWLpITX4ZsAjOFGxhhgINwFX/BZeI2RI/3QM1mSIlya4lHoASmd3FdG+U00YCsDA6QWUP456yojw3tvKQzWTLhyzv92NVxbBa78Ely/7EJcZ+hVXNuzezBYthZw/fX1ZNlMYbC3IQeObyeup/FN6cA3vyU0YQQj9WSjJmzTW2cJNnr1B9mI/xXZKErD
*/