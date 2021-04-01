/*!
@file
Forward declares `boost::hana::front`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FRONT_HPP
#define BOOST_HANA_FWD_FRONT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the first element of a non-empty iterable.
    //! @ingroup group-Iterable
    //!
    //! Given a non-empty Iterable `xs` with a linearization of `[x1, ..., xN]`,
    //! `front(xs)` is equal to `x1`. If `xs` is empty, it is an error to
    //! use this function. Equivalently, `front(xs)` must be equivalent to
    //! `at_c<0>(xs)`, and that regardless of the value category of `xs`
    //! (`front` must respect the reference semantics of `at`).
    //!
    //!
    //! Example
    //! -------
    //! @include example/front.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto front = [](auto&& xs) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct front_impl : front_impl<It, when<true>> { };

    struct front_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const;
    };

    constexpr front_t front{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FRONT_HPP

/* front.hpp
BPFCQkJRum004j+Bj+ZBeeiY1kSzBuqrc8Ygnw4NowuAwvKPjf9K3OGHeD1XlYHCIg9bauyvFoezz96K8MXNCTfrgTzE74fCVxT5Lkl2tMHsAi2rYycrOttJYRsJQ+lfNUnjHjCx18Z/zIRI4te75iSeowz8J8xQV+NQLGHCytTB+T20CIZqJa2k5QPs3CadE0idwK76mRQqJQhVuH4kCTwKtKXKI+qBI+sxHN6ceO0k+izASPr7EKsA5jnCOuhfJdwsnyY+/jgM+9L7IUpAVW2VIe+zS5tXJqb3h4+Di4xzHRoXUVbatptEeopVbtKbgO1rzQacVkczx4ep3wM8rqaplAJTljOfhv8jhfmL3VHRd1oK7roqsP+acXeQE0xgOwp6KcolrCje3BPaJWiFijAm1MzEyrCJsalCDZJQqsbqJMT0BMQj+UHVt9i+0ywaEMGWkJ63wv9A4LxCM8fBZpANpJriVYUNrmn2FMhnAfGHjBl0JajHNK8oTwG37AGOIezM+xXbajsC5T74G2UKh+c3+5FQdWNUU059kasjBCPJ9VdOfGZAi1EhKw==
*/