// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_WITHIN_HPP
#define BOOST_GEOMETRY_STRATEGIES_WITHIN_HPP

#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/tag_cast.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace within
{


namespace services
{

/*!
\brief Traits class binding a within determination strategy to a coordinate system
\ingroup within
\tparam GeometryContained geometry-type of input (possibly) contained type
\tparam GeometryContaining geometry-type of input (possibly) containing type
\tparam TagContained casted tag of (possibly) contained type
\tparam TagContaining casted tag of (possibly) containing type
\tparam CsTagContained tag of coordinate system of (possibly) contained type
\tparam CsTagContaining tag of coordinate system of (possibly) containing type
*/
template
<
    typename GeometryContained,
    typename GeometryContaining,
    typename TagContained = typename tag<GeometryContained>::type,
    typename TagContaining = typename tag<GeometryContaining>::type,
    typename CastedTagContained = typename tag_cast
                                    <
                                        typename tag<GeometryContained>::type,
                                        pointlike_tag, linear_tag, polygonal_tag, areal_tag
                                    >::type,
    typename CastedTagContaining = typename tag_cast
                                    <
                                        typename tag<GeometryContaining>::type,
                                        pointlike_tag, linear_tag, polygonal_tag, areal_tag
                                    >::type,
    typename CsTagContained = typename tag_cast
                                <
                                    typename cs_tag<typename point_type<GeometryContained>::type>::type,
                                    spherical_tag
                                >::type,
    typename CsTagContaining = typename tag_cast
                                <
                                    typename cs_tag<typename point_type<GeometryContaining>::type>::type,
                                    spherical_tag
                                >::type
>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THESE_TYPES
            , (types<GeometryContained, GeometryContaining>)
        );
};


} // namespace services


}} // namespace strategy::within


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_WITHIN_HPP


/* within.hpp
ANjkv392RsQhBwkiyHcIe2565LaS0wXI3kMO9iDm7+7oLv+89PuA3u+VhbajBmp+Qx/6Nh59cuqoRZf/LQWHf4GN+eCvflNBa7QJWxaOeSERezSCultZgC0NBosHtxXdjhHqM5lsP4aS8udoDztqEVPyOoKCbymkwPN+N49PPOS843nbmjpMVhk2s4zUyw6Gsl5kM5ornDA8g7BvVoPfn60B9jEPUhZ2su/fK/XH+JZ3j5HKx334mIE1IBwWbjndGB2q2Ut6ARx8J0qghCOZkpwSwZjy5FWNeIP2LWapdJLktunEi1wwjm1f5QNIkVZ6/vDPH408SAG6ktLyd2S4IVL26zqyd5ll6WYPi076I8kgTFKbgiPdj2QRvWIcws+9YolB31K+1qLOPKoKClqSf0piBO58Ec3kTiY2svkoMzGkSJ1ygXnsywCuzSZcJFQpzq9bqqMMMNZ06yePVDgS5xIgjYodO/oW/mfZVfoMBcWn1g/mXf1zoFrLsk1F2hrEY7HXC/3mC17L6vrhZtfvXTs7EC2d5693PaeTqeFqOTzfZ7WTh3IHSqZoNKyZJmhlCC3WMR1omKpQib7MaGquKrRLmLirZgDaKsYWZ/eufF7BDFba72+fnrs6X4ycwKnwZlOHD4d2d148PhiAjsz05B8vR5pM+JAynbKky9Fft2KRMj76Sp/iVi5k72Wik886XvJMVWpqdK1utFU0
*/