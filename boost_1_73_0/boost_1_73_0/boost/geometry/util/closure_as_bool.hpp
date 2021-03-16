// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_CLOSURE_AS_BOOL_HPP
#define BOOST_GEOMETRY_UTIL_CLOSURE_AS_BOOL_HPP

#include <boost/geometry/core/closure.hpp>


namespace boost { namespace geometry
{


template<closure_selector Closure>
struct closure_as_bool
{};


template<>
struct closure_as_bool<closed>
{
    static const bool value = true;
};


template<>
struct closure_as_bool<open>
{
    static const bool value = false;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_CLOSURE_AS_BOOL_HPP

/* closure_as_bool.hpp
WEd6YK1w98Djov0eKOlYDyytqmq/B0wbz8k+4zY+4xZdL0yLIqVaVGHVjO1g7MUE1oHWqxfu1oOXLWun9UZ2qPVqqu6oqIlVV3MjTcw+XSO5aFeB61R7rYIf5VatglRAXrPCfspYR1qgTrhb4DGB0HHbLTCiYy0QWyRvn4rT3T6zsk/XMub2qUi6fc6opRqFaSmk1HyosIWM7WDsxQTWgdZbJ87E/0U61Hq1sWXz/hX+b352Rxv3X+n/7hemtZE=
*/