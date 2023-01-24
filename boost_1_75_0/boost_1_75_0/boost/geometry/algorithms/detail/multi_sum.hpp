// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_SUM_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_SUM_HPP

#include <boost/range.hpp>


namespace boost { namespace geometry
{
#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct multi_sum
{
    template <typename ReturnType, typename Policy, typename MultiGeometry, typename Strategy>
    static inline ReturnType apply(MultiGeometry const& geometry, Strategy const& strategy)
    {
        ReturnType sum = ReturnType();
        for (typename boost::range_iterator
                <
                    MultiGeometry const
                >::type it = boost::begin(geometry);
            it != boost::end(geometry);
            ++it)
        {
            sum += Policy::apply(*it, strategy);
        }
        return sum;
    }
};


} // namespace detail
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_SUM_HPP

/* multi_sum.hpp
tgNDgBh5w4yJVWrXJSj1KApbZBn12soMqigIPEKwCv5COwUL/B2+dm+bp9XNzh/1UETkAbichhRgtgLNhX+F6ZP3Fb1o34JLiF7i9PJ9eplML3PppYFefkEvj9PLUXp5mV7+BBcJDv25gRazHVNg7F2/YcPYS7sZQn1vcl1yxk2n3nt4uruVYeytZN61C3CgW4y9ips2jL0JkPmJKHPqTScvdcXlPo4n2xD3ihni3q309Dtv2vT0+yHz+5t8rB7tVN8v0rUJVE8/HeNtpp7+Vvp/e7kZXwP/97Xg/752lvuY0P+Ps+n/b2F/WfW1sL+cDsR9kFZ9nYxN3cJiU/PjOPczWGy9rPVr6L+LWmAqxo0S7IpwhJYfxlKWi2zDG8hmZigRlLmNQDd2Hm1f2zACKR7eJfjBeB16TqAB5pkeXeiW9hbeb2z2FgMh891v+Lwd/I1zY+xF5E0YH74VHmzNN7Y1gGKY3fMNw7ubB5xxjmM9sXycNtqfoTFiH4MfaDhY08cpxTn65W9s/mIXIfP3b3h/XrbqzIwPx9E1rYisgsaoxTqJdbOO+1HYqsMgyHwPEsO/on9ta9clLDfj09wXKcXaWGMv5x7ILBTl0P2AvIDXIXRLG+qdcDuTWe4HQksLo+GQcrnO1ERErbVWI7teOsnuvcHclVqFPIevlqV1i/iQtAmK0nCidH+65PZ4c+AlwWCY/kHhnNvhj5C2
*/