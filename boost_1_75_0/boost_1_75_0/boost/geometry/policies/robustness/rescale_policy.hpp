// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2014-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2014-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_RESCALE_POLICY_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_RESCALE_POLICY_HPP

#include <cstddef>

#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/geometry/policies/robustness/segment_ratio.hpp>
#include <boost/geometry/policies/robustness/robust_point_type.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename FpPoint, typename IntPoint, typename CalculationType>
struct robust_policy
{
    static bool const enabled = true;

    typedef typename geometry::coordinate_type<IntPoint>::type output_ct;

    robust_policy(FpPoint const& fp_min, IntPoint const& int_min, CalculationType const& the_factor)
        : m_fp_min(fp_min)
        , m_int_min(int_min)
        , m_multiplier(the_factor)
    {
    }

    template <std::size_t Dimension, typename Value>
    inline output_ct apply(Value const& value) const
    {
        // a + (v-b)*f
        CalculationType const a = static_cast<CalculationType>(get<Dimension>(m_int_min));
        CalculationType const b = static_cast<CalculationType>(get<Dimension>(m_fp_min));
        CalculationType const result = a + (value - b) * m_multiplier;

        return geometry::math::rounding_cast<output_ct>(result);
    }

    FpPoint m_fp_min;
    IntPoint m_int_min;
    CalculationType m_multiplier;
};

} // namespace detail
#endif


// Implement meta-functions for this policy

// Define the IntPoint as a robust-point type
template <typename Point, typename FpPoint, typename IntPoint, typename CalculationType>
struct robust_point_type<Point, detail::robust_policy<FpPoint, IntPoint, CalculationType> >
{
    typedef IntPoint type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_RESCALE_POLICY_HPP

/* rescale_policy.hpp
jv6gCZguGkZ2im+cISvY9Dfu56QXfmx1zk+OlzPd44vMfpGLTHN5GfWMH08/qh/mA2Yhm0117ij96iktypnw02QliKf+BlVj4UL3x9NqLFL8gbAsz1HvnGzCDgpjxfEZ/M7HanYkKAXRhtIU+5sGAHfm0xgowhVUv8nuxJ3rnn3JOWAZ3Cf+G/aNQ90UKo2+gX5pjGpy6se67T6y2PlSfatMaWt7Izs8RiUTSmYlheUnKonXltWpFixlSPw465wdyLs37ggQlMbcjLqel7Au+bgWhTf2PbcyXlAKcJMseUr0MP8Gs88EZaAbmco1c+hE1Dt96HQfhO45Ww+yAREBFAh3FAOSTQVhXjgepSccUFYohV8KTGRgRlM8dIJ6z2HOYG67Z78DI/4O8SmqWVwOoorj05UGZj6+VXVCuJ3nTY8BppML3349m3cnc5uN0+syBJ5qXrhAyQXifpgMi61feo5YDIuFXzydpZNLZriTPRSROwDshnUMGver0pyntuMZ4yBeg6KtTtL2GedlnZ8DKn/FRmZeqAHpx2kE6FTiBW/HCoAdI+ZR9WMpKWPyYz/MUv7orxZVmlhYIlaIIFXOeuBIAsTdfp9bPIy5W6sZHxiOKxcyveA337XMlf3aD/VW4iveEMWj3YKhF+u0pjdzG5y+h5bfBQACOODCWgddZ/5D3JMxNVlH9/B4n89gODbYq8YLpbOqHaN0UpV2
*/