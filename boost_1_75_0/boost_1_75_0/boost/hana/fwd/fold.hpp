/*!
@file
Forward declares `boost::hana::fold`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FOLD_HPP
#define BOOST_HANA_FWD_FOLD_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/fold_left.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Equivalent to `fold_left`; provided for convenience.
    //! @ingroup group-Foldable
    //!
    //! `fold` is equivalent to `fold_left`. However, it is not tag-dispatched
    //! on its own because it is just an alias to `fold_left`. Also note that
    //! `fold` can be called with or without an initial state, just like
    //! `fold_left`:
    //!
    //! @code
    //!     fold(xs, state, f) == fold_left(xs, state, f)
    //!     fold(xs, f) == fold_left(xs, f)
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/fold.cpp
    constexpr auto fold = fold_left;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FOLD_HPP

/* fold.hpp
ur4Tlxtdy8Wymk5cbnStEMuqOnG5Kc7eWm69xPXhbnF9UJ3lcrOe5XK7/yyX29izXG5TxOv0s1w+eWe53B4/e3u5UNzw/tzmcumQ1WT7kxWcN63i9rYvKFrafp28ddt/QIwDxl6+tV+qjm1Omz2uyVfWi7RV3oS2QF+5XtHSV65StE7bexduTtMRXHeIbk7TnOgmmlZ15jSldr49TcrOLWmK6Nw6TT1vQ9PelOY03TOjiaaILpym+v+ApvJWaNp6E5quX7o5TcW4fiG1OU3nU5ti6a0iTau6tE5TYCyd3KVlLB3fpXWa1PVcr8z13KcOree29EA9t6Wx9dyWHrrFelhOsebQ5rRPGtZEe05XTnt819vTHta1Je2yrq3TPuoCp33CBU771Auc9rQLnPYsMZ3Xii4IQpMfyx0haWGHxV2bYqGQMO6bKluhPxDfDxf4OuUV0wti6rvQMl6lHfHSyc1ldmkylxn5xY1hXGaLwlqXGfmtUDEfL7ah645imTGsdZltE9fQEnENPSCuod+Ja+hP4hr6x0XuO+svcl8pvcR9Z6dLfM3p0YouB/5FduMyi+rGaVsnytrfVia2C9xHzHhZ0oKP+G6yRpmsEXEmd7v1PNRd5XKvvyr68wbOa0gD51XRwHkNb+C8RjRwXgc0cF6VYntjA+c1WryOb2g5j7QHrnxawsYLjOWF7k2xfHx3cf/TvXW6119tvr5t
*/