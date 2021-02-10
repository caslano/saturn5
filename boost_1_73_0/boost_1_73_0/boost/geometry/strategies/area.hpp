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
w8LwEb4w7j2dBYBoIWih7d/nILblXdWoK66iaJ266Zv42tyC1/3eavASn0xAn9jbNrydnMLbaa9/3un2MciPL/jaOlcI/MQugEpbp+or8sinrz6j7yjyhfxRZ2wXr+2K8fZsGbhvfP7ohh6F2sVrV8LaFohXQkiYKPtHSMiKLstiUyuKcHXbXWy7S20lsWWa7F1mxFqlXDZ2nj1/zr4H/mQ7t6NRhWARct/0XmSAPc0DZsLSUORLATsTwBSHnrZ7KDqDyUcuWBRVs1gkhgtj+dlVE0C5knBG4taTIycBOcLY09wkgx94T/JGLuFXhVqosscgUxUXiLDGQCkUIQ6cZrfb6Vb0ANJOIo3zi6NExutOTweM0GnPhXQu3JZkIUUCUZuZlSPdMo/d/cDfovgnChuN2RFwvcXyBhR79kk85PPa8vk0TzWga9iUzF0rnIK+L4kQFwQxj9CTUhN0/bt4jDOGmbsTIANFbwVj/6xUQ87I4p7wrwoNdZrNYMwHH2BbMDhIGTRy5tB3k/OisLMf3KjpCGVL9DTioI8cdzgMMzRVBlOqIrSEJZxhq4CwYKdlhEOSgdPovW+fvJZoNM0MF0MFNTEovB8VNwFtiiFGsG60m5VDIq/lFNmTR9ETdgMO6iiY+8N8wlhp2wWN
*/