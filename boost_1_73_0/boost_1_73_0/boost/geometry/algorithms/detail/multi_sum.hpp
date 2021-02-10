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
uZ2z2Im1RQ20vCCF77iF4iabc8mNx2KFzLyOwpBgQL0kfGGfXWWL8RDxkb6UxTWbORjJQvDBRm5NmYEgJDEW0oeDkOlgynJU9lQGAgjHokqARAPq2IvuD3O0ddI89DwccjL5MqNt7+yk2znod05Ojk/8vsoN7jAZLgZzGh4aXu8Wrm4Q+0fpbO01xeQI9AmIzX48mNe2ye8zIxhtgHGdJPOrbDjz04EaIN5Ev5ixRFsKTA+kGhlijsCRuecCrrIG7EHp7bbQBJG6tBEdzm0Cpnm0RYFUW8g1lJLUpzrRsE/hl6UwAN0RnG3pwK/s6c/HBQapFmryEgIVGjG6XeVyIn+nCCy860OKjfDKoC1sb5M0mYLCDDTfEyIDspl58DrBimRGeawIQXvoMlHt6dI2n7SeRh20hdK8UrL2zTqfvGAmsyQnZs3tAARvlC4SbTbUZfauVJ4vQqgi0w1a2sCpOJpAYrvzZBCDwwKSwWQwuS4/ly0K75NX6MihBLvDJJkwvk3dKcR9CXNm6WJc6VQgSYKtL1jGzCzPKRd5PrqElYVpaCj3hS7HMusA5h06uGwUgkkVF3/cKb5J0L058BOOR+cQXhLckDCFDo65I+VJvphppgwjptvIAzSIp0PPp4XvKWMT27ALLqx6taFh
*/