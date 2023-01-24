// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SIDE_HPP
#define BOOST_GEOMETRY_STRATEGIES_SIDE_HPP


#include <boost/mpl/assert.hpp>

#include <boost/geometry/strategies/tags.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace side
{

namespace services
{

/*!
\brief Traits class binding a side determination strategy to a coordinate system
\ingroup util
\tparam CSTag tag of coordinate system of point-type
\tparam CalculationType \tparam_calculation
*/
template <typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<CSTag>)
        );
};


} // namespace services


}} // namespace strategy::side


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SIDE_HPP

/* side.hpp
jMQ6y829+uRSeq2yz66u5Qmauy5+He1K1TxWZ4V7SeVtBReGIbuUqG5xoY/FBFCs9yRaMeueiunWJzAmzud6UizFZet87opKYfq80P3tLocixZRMbdlK0sVigFZsRQVIIk6vvVq92yZtZgGp1amJrUK6XwdndX5bCKny+9uGwonyl/vsmll3ne2o1UV5I7Qd6VBKNPOhsjPBOW6VOANGLQUDJeeSEfWm5ruslGOzqqNhDpU5Y15UE5ieQoONKaJMHUfaJvVv/3QzFS6LoJnWyAA3kZ/1EpNUH4NAQX6g+yvBW/0o0vu5VyHyE2FBqU+t8pMSWtp5L76Ul1imUWw6t6OIE89VWnfexa0188cTRdVJbFQIRTDGtI7YlANPS4Y1G5h5zLJKfJnQN8uX/ffm2OgBfYte3DPnerH0LJZcQFU2EH3SXMK8M1VpwvZbNafvKk2tQR+Y83ChFohyiXQxd/kRE2/mQuExFg8hhBtcKW4Z4yilLYy6POr4+xX0+LTSUamZV0jIAJKm8llIjYyto9bYcsiDbHOypKTGVLHdNbgL/+IVP9UGWgea6eaJq7VRKCch5DeoEXufr28Ue+/prJGijceddkmmpYezZdYpE05xi+0ZsvFjzolsxXsHrQPrBZgea9746IfheGsEo3zBC6LavSO8dQVH2j4QPX4XdzEtNGAUIRW1y46I493fFdj9zEE1NSQjWYAzzPxH
*/