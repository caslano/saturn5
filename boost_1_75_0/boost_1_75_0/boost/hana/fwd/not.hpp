/*!
@file
Forward declares `boost::hana::not_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NOT_HPP
#define BOOST_HANA_FWD_NOT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Negates a `Logical`.
    //! @ingroup group-Logical
    //!
    //! This method returns a `Logical` with the same tag, but whose
    //! truth-value is negated. Specifically, `not_(x)` returns a false-valued
    //! `Logical` if `x` is a true-valued `Logical`, and a true-valued one
    //! otherwise.
    //!
    //!
    //! Example
    //! -------
    //! @include example/not.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto not_ = [](auto&& x) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct not_impl : not_impl<L, when<true>> { };

    struct not_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    constexpr not_t not_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NOT_HPP

/* not.hpp
s7dYjvUkAMx3r0FXvil3Q7Y3yL5MWk9LOn4Bnucwsc4LuOiyYOxm6uAr4d+QP5cpuxr3N+Tz/C/k0/135Es42FtYOdv9W4nHW3YDeDSJYwWzxtVxHnEm2CGgvLfCltUmKvIbVTD5WP/OXbyMqOgzifaFrYUlwu5OFUniUjQ/V4xcRtKUEButlSlviyl/7HDNeondWlM01HGOx8qGbE6o2sqW3+iMJ4Yf7ndu3VxFUHQETbibEN1Ob3e5bH8UAZ9ldULPtQgB8PqRlJzSH03J48fRX/CnJlhM0aQqaL6OXvJzpX9pEbiNunNJ9n+78NH+3pps4vrI1PCvbNVEqAy6DeLtQ46s0bZmVHmMumtMB/9JupOg9Dly5wKovav5lctA8bCddwY02u3GW/BCrLOZqlzZe6732L3iMvnT1ySelaXUP3Kese+PrlaJyJ9xo9h07DqjMvJXRoprTaIgebMtRNt5sx6GO7CdRPeZX6a4Vo2LfwVVtFM0RKhdFZa1yDV+s730WtHLcqXtOP1iWQ1X7KvJgq23kGOEIoW1ACi0xVBJFz4H9FhOhsJ5+xhEkF86Od46pJHCdc5m5ucPdWCUH6pO9S59gI/a3wodvC49Xiot6YYWgbmXsc2uh/vbcknCWo0vqRAsZPa3sciWI9llxpjPHqBrEIg/928pXsKZDiq2fM+Mw/6G7e1NsT6HGZXulw36GzLtH4/NfcV9
*/