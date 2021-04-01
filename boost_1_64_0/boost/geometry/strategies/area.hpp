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
tDw3Xzua8aHdGGVkd3RCBlCJNUa6a7oPh6+DBOJwL2tf5o76ucEo0RjdouGpHegqnxJC93NayJfoDHiVyMSKdWRKbnY9J0Z2Z7fGSFaRBnuteBPRfcXDBduUMve+/OlOzSojGu9uB1ykvpjkZmUzeo5tuWbWcs2Dqth60llJd1pU3gxhW+JMBskXdLm+16/RljZttEqay5nUEh5bLIvhxylWgv/347bzIxsvZv9qufkEPEOpmQaze0An7wXjeET5k5h6XRP5BATQshVbpe8/SoB3sBwupQ05TERGo2tZRMCkkL4OaKrGtZWGJ76JUK9b2wQ07/Y47a8klwp2gcfF6y2W514/QqGlXH2BAhmDu0sjm75IspBzMVGy3w7sCQwO4pl2NEKsY6fdLjWTuoXZzEb46QXDpNPLvrNxP/k/ZNDYE05DghA9UMCOs8ZGEc/C/Nv0tswnN3R4Obb0fs8js2VjbcS/q2HTeuTwP3KzXS0UTJSEHZA0sovV0Nz6biT4zSyLMW15XPiugbfJnxmM2D7EloYqAix/GPR+B2+bGTK2rP7ZIgeYcJRdZA==
*/