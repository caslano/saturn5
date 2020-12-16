// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_SEGMENT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_SEGMENT_HPP

#include <cstddef>

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/dispatch/envelope.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/envelope_segment.hpp>
#include <boost/geometry/strategies/spherical/envelope_segment.hpp>
#include <boost/geometry/strategies/geographic/envelope_segment.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{

template <std::size_t DimensionCount>
struct envelope_segment
{
    template <typename Point, typename Box, typename Strategy>
    static inline void apply(Point const& p1,
                             Point const& p2,
                             Box& mbr,
                             Strategy const& strategy)
    {
        strategy.apply(p1, p2, mbr);
    }

    template <typename Segment, typename Box, typename Strategy>
    static inline void apply(Segment const& segment, Box& mbr,
                             Strategy const& strategy)
    {
        typename point_type<Segment>::type p[2];
        detail::assign_point_from_index<0>(segment, p[0]);
        detail::assign_point_from_index<1>(segment, p[1]);
        apply(p[0], p[1], mbr, strategy);
    }
};

}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Segment>
struct envelope<Segment, segment_tag>
{
    template <typename Box, typename Strategy>
    static inline void apply(Segment const& segment,
                             Box& mbr,
                             Strategy const& strategy)
    {
        typename point_type<Segment>::type p[2];
        detail::assign_point_from_index<0>(segment, p[0]);
        detail::assign_point_from_index<1>(segment, p[1]);
        detail::envelope::envelope_segment
            <
               dimension<Segment>::value
            >::apply(p[0], p[1], mbr, strategy);
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_SEGMENT_HPP

/* segment.hpp
lpE1NZdN6rVIfz/l/DVVdzDbU/uin3N8kS/C70H1df94rvuB/ESu+yzneNAeNLnfB9rEuLP10MVt0Er83VSdg76a8nUCAmHQqKOW8ODuOK9hDnewJ9ROlmNxIeaImMR3A/Aok5xepdF9+ukdbOYf2nQT2+pPM6e/a2rDyqbvmvLp4p+ovj2ijlVllNMktaZrTXTma0hgQ/Uqv6msYHRpC/dBmxgP+uNKKA/8UJsJQ0dAHw9dWsOQw7GHjw9YKQNN/23QFgO41Gh4uFL0f0R6eVK1RQ1pdtoghRV0M/pR9gzCwdNxCutxC2r4TaMuuV24dhyVD7ieXtfo9OmBE6dH/dQW8O5FPzXf+JKb1tOIOYzWH90rjyFP09MbZJ7k7fKPbVO6g/G3lO3VdN8o00WwtvblPulcjmfkx+Nj2Ta9jcXtbic1/2+W6SKYyH9DZ1KCdNV3CJ6tpvtWmS6Csb0ae8MnTHekkgxo/dsuQdrevy/SRqdq09Vx5CvC3yFwd3v/ttWzqlLPdlf1dYZMsyrrGc0dzgS+8y50t+YFDY7jA1hzbhwwtU17+3EvVXdnm3x09PZRqObeZLDpwdqarWap6Z3r0kOoZt9kcOmNqnVjXzW98116sg+RZwUtjnqTi21jPqu6Heap+bzIpVXdZjsk+huFB+2ljc8fculxfaezjJAfgXq3GzgfbLSv2lTEf/Yf9e2QF6l5+IjJw6Yi/mtfVBigs3QOuxyYiZCwat3dK3OFzd8Ck79G28VIcQC/CmhuY5uivC1U87YK31dNOKOb7Hnd5Q4zOwmazENNzUO7moePcjpDoziWELwrlcFo8cp5PBW4cVGMZ85Xngd5zZTJBPY34olvoRKnrxv8bUJimTtvrokwM8vksO8NcJNZDvv+APNzGDrjCnuPw95monBJg2sjq+tiXA+PVNveVaYerunoNAt5pxLZD1wrcFIJMCVs9s6+6wRGXmUs6jeltz0HfsXrBS97BvxzDqMDtl5+g5N3h3a/2crdwVonv8XJcaB2fITvErkV8vTeqc2j6bjzNfz/5dD3HcA+bNvcN6xs7xksu9PKPit4d1nZcsG728rWCt49VrZQ8O6zsrLgPWBl3xay31nZ6UL2sJU9V8T3iJX9XvD+amWnCNljVnaECPuUlf1N8HZoJdmXhWwnK3tYyHa1si4hO8jKzhWyQ6xsX5HuAivbIHgvtbIdBW+FlX1K8FZC9kPIThK8Yyzvn4K3zso+LGRFKxsRsgErGxeyspXdL2QVK7tJyCatbLGQvdfKfmZkDfeZifkpmHdE43G0os2r6G3xNb2FjjGscfvH4Skt9KKHLPDbKCrnOCzFByfp7dWYNz62qTyKPWhoUKUVuBcih9eJU5SVwZTWmb6Sn4Co5K3TnmvnyNAXRZzRMaTZjdcX4GTpb5kKRwRR+BWVoXIisntwBscyr1hLxodNkURcqp5oSRgT56m8UEcxZ6I8DHNLTjZv3UkyXq53jJZ6YZXi8Fq6xleP79iuY7tLyBP0PhVnvfGnVkTeF2Y55cmOIXTfTJSxYq/5tHxETOlr3D54uhONm81HT70yhJ4etwhwBnrqiCEqW8S3kaJe5nLWjePk8wBiU8vUg2peF5V4pXGqjnGcERcR+TZE+dN5UcFRbp03UUXC+BJjiJy8otN1xSQxjsEoakVH4JQrtbH1dL0kpT9L53BbirFkJTZGaG3J58E3gHx7NVJfPAfRcC3Q7RCqjLod2TbPayVeb3q6xXDMBL1acvPpC+24MUnjRlR2Dqf3U6Zzlf3YPA2vh6VQ4xD1dzc398Fv9P9YumHek5FtLtYrBsjK6+XNKp/Yj0byBPJGz2X48WhM+8byfnU=
*/