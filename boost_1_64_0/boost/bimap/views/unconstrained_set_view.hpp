// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unconstrained_set_view.hpp
/// \brief Unconstrained view of a bimap.

#ifndef BOOST_BIMAP_VIEWS_UNCONSTRAINED_SET_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNCONSTRAINED_SET_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief Unconstrained view of a bimap.

template< class CoreIndex >
class unconstrained_set_view
{
    public:
    template< class T >
    unconstrained_set_view(const T &) {}

    typedef void iterator;
    typedef void const_iterator;
};

} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNCONSTRAINED_SET_VIEW_HPP

/* unconstrained_set_view.hpp
ifRoICMYCR/O7TLMtimdojrFZYEnnNXLapCIvTw1UUfkQbAXIagupGqnTrG2+UXtHvALICfacpi7L7NS+CzBGYSl2U853t9mWnUuRmlylpndDNQOwL0HqeB+T/Ek1wlphCMNxR+Ouz/kgJ5RgSUYfHR2mXeUddXete5o56xBbw8G00iMFciMP8xj7plttLwjrEeBUJvuB8eNVILbEd3fDGa/O1ShobhyoTnvihRldYkT+pNldxNDqrREFI/7Nh8zJEZCQ1bgfSe1NbhrTO2Y7p6JymQogvgdbLJyJfDklLSvJ+lh461wjCmGsRJZYHTgpa1aPIxIu/fz8U9lHBXnSygjkXVrQOs0xvb6LwjpAfocexHl4ul9jCSOKy45HBjG+YRl6t32xdfd9UFKL50qnMt+9hcjYHn9LtG3heonpvfRUjnNKgpl8oC1v9OAvyIxYpia5P8NV2Pe0+wW7Xxmyt4heikru4bkY0RtvoV4dPL838Yw0XGsnTi2NnAAheZv1UbEOLQsWmVqn3JAPAPv+RnVYnl0pByL1IvJLmgVrSi2hItVL2MU4dQiag==
*/