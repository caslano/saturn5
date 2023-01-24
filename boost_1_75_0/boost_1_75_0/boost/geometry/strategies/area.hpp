// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AREA_HPP
#define BOOST_GEOMETRY_STRATEGIES_AREA_HPP


#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace area
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// If user specified a CalculationType, use that type, whatever it is
//   and whatever the Geometry is.
// Else, use Geometry's coordinate-type promoted to double if needed.
template
<
    typename Geometry,
    typename CalculationType
>
struct result_type
{
    typedef CalculationType type;
};

template
<
    typename Geometry
>
struct result_type<Geometry, void>
    : select_most_precise
        <
            typename coordinate_type<Geometry>::type,
            double
        >
{};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL
    

namespace services
{

/*!
    \brief Traits class binding a default area strategy to a coordinate system
    \ingroup area
    \tparam Tag tag of coordinate system
*/
template <typename Tag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_COORDINATE_SYSTEM
            , (types<Tag>)
        );
};


} // namespace services

}} // namespace strategy::area


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_AREA_HPP

/* area.hpp
X+GCb7764Ka54r+P2iykvbJl2wUUg9PCcAwOAzLN+6LpNLsATPCawhjKedch+YFCbmHNlAYIGc7XnkLUVDZ4TZdfUVFrzbWR+nFZCvD3jps9Qxo9qbAl3tDJH6plCCglKT3ZmSf52+STb+RPPqekPQ9/kFVXHH9b/inY6UMlS+v39cP1pd/rs2vrR0f7x2cLhziwgDa44K2vy+V1M1zA9RTXy39ZoNlDz+FimIqZ/PcnzVL0+qzvdyEDgTTHZJQNdMAUNoEJ3JpPjo7LzWW1Lc5E1q+xE6tIdCXqe+4cPSCcq0I8cdxGotzyjnYKCvMSoi4uZ/uHeJFWuzdzvYBtdd6w0O2HDcczv2tEr+lT1wP8QeazQTAN05Pichle7dMI2BdcYzHbeholI/P7a21MdnhrT6tfJnEiOE2IN/EisX7RyRhEFbC1oWrJlg5LjEqST5Nhjp2GhFuxDLae2DuIvDPd+i6+O53d5erqENZTT4xB95gbO+4M2qXQ5PZ7C+IWn61lwn1HGIOrrsYXLcwI6RgOry/cxJ6AzCe8oIy89L31ax+l/1o25H3RYbOxwuMm0WGTvU2WkaxTrsrf+RTQZ4G07Gb1i8vIYOXvMSEU4ZXcCXEQM/VfUZ7lnRj8GjAD+MW7oXco0BY0b8Kgkn5sXHjE6rakH5JsFNiFcr2vy+Kt9/nMPHds+sdTdSk7WlB4COTNhuhEzXxHGUaq
*/