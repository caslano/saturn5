/*!
@file
Forward declares `boost::hana::is_empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_IS_EMPTY_HPP
#define BOOST_HANA_FWD_IS_EMPTY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether the iterable is empty.
    //! @ingroup group-Iterable
    //!
    //! Given an `Iterable` `xs`, `is_empty` returns whether `xs` contains
    //! no more elements. In other words, it returns whether trying to
    //! extract the tail of `xs` would be an error. In the current version
    //! of the library, `is_empty` must return an `IntegralConstant` holding
    //! a value convertible to `bool`. This is because only compile-time
    //! `Iterable`s are supported right now.
    //!
    //!
    //! Example
    //! -------
    //! @include example/is_empty.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto is_empty = [](auto const& xs) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct is_empty_impl : is_empty_impl<It, when<true>> { };

    struct is_empty_t {
        template <typename Xs>
        constexpr auto operator()(Xs const& xs) const;
    };

    constexpr is_empty_t is_empty{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_IS_EMPTY_HPP

/* is_empty.hpp
R98vUfuxrGyJFfnMT6nUZ1U2Ek6jR+en/wdoFAxs0l9fAgNTJUx1QLlc2jg23UPRoevpZIAAfrhpxXRQ+U8LmlO2krYiuZ0ycFp/7ByVc0YKyi3ChlWyOMPQXJylyAC3NUumZrzB/ph97dO6AtI/LFFjgPt4SmNIzrSQfUcSPw+zyZ5BvXZu6JQSXdszYkz/C4je6y5woRRwmbK9KpGSe4WlspR8kAjMzjxPkRpL5vRcvqhabWCt2v57brKcEsbYtm+ji60KtzZg2UnXxZsIUM8nS0xx6A4oJnLOV+/oLnCw8kP5gK2cGTBodZ3BszfAaO6hJ6ADZpuYT3D+XgDaBjGDwtcF+ucsIdNbVmXr8RgmC0Pe8aPGoucIuSlVemzuPaLb7hyX769iRWrDlRgIADwLmKbeqdhtaodnJ2kMvG8wdutD5tRh5ltCw9+8+05dj/oTCX8X2QVrxRzqbOTZa+qJCvsOjQPlaU/4tsHDoWv0OsC5RojJR/jT0pQ7yCBRKrYz7BM+SdcYL1CNVw8du2qAgNsZOyL+otDDkeSUPrOlmNAFlYjelkPLWg==
*/