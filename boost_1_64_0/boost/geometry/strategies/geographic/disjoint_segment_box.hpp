// Boost.Geometry

// Copyright (c) 2017-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISJOINT_SEGMENT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISJOINT_SEGMENT_BOX_HPP


#include <cstddef>
#include <utility>

#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/calculation_type.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/disjoint/segment_box.hpp>

#include <boost/geometry/srs/spheroid.hpp>

// TODO: spherical_point_box currently defined in the same file as cartesian
#include <boost/geometry/strategies/cartesian/point_in_box.hpp>
#include <boost/geometry/strategies/disjoint.hpp>
#include <boost/geometry/strategies/geographic/azimuth.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategies/spherical/disjoint_box_box.hpp>


namespace boost { namespace geometry { namespace strategy { namespace disjoint
{

// NOTE: This may be temporary place for this or corresponding strategy
// It seems to be more appropriate to implement the opposite of it
// e.g. intersection::segment_box because in disjoint() algorithm
// other strategies that are used are intersection and covered_by strategies.
template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
struct segment_box_geographic
{
public:
    typedef Spheroid model_type;

    inline segment_box_geographic()
        : m_spheroid()
    {}

    explicit inline segment_box_geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    typedef covered_by::spherical_point_box disjoint_point_box_strategy_type;
    
    static inline disjoint_point_box_strategy_type get_disjoint_point_box_strategy()
    {
        return disjoint_point_box_strategy_type();
    }

    template <typename Segment, typename Box>
    inline bool apply(Segment const& segment, Box const& box) const
    {
        geometry::strategy::azimuth::geographic
            <
                FormulaPolicy,
                Spheroid,
                CalculationType
            > azimuth_geographic(m_spheroid);

        return geometry::detail::disjoint::disjoint_segment_box_sphere_or_spheroid
                <
                    geographic_tag
                >::apply(segment, box,
                         azimuth_geographic,
                         strategy::normalize::spherical_point(),
                         strategy::covered_by::spherical_point_box(),
                         strategy::disjoint::spherical_box_box());
    }

private:
    Spheroid m_spheroid;
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


namespace services
{

template <typename Linear, typename Box, typename LinearTag>
struct default_strategy<Linear, Box, LinearTag, box_tag, 1, 2,
                        geographic_tag, geographic_tag>
{
    typedef segment_box_geographic<> type;
};

template <typename Box, typename Linear, typename LinearTag>
struct default_strategy<Box, Linear, box_tag, LinearTag, 2, 1,
                        geographic_tag, geographic_tag>
{
    typedef segment_box_geographic<> type;
};


} // namespace services


#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}}}} // namespace boost::geometry::strategy::disjoint


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISJOINT_SEGMENT_BOX_HPP

/* disjoint_segment_box.hpp
1rL8Lw/Z74+r3+/WXj/a4r8TSr/fc/HHLZ51v2l6tTOzx3fwXFW24/GTUT/X3r/Dfv9y+ssxvqo8O4sp0q+xPAYSfMz9LutjGHbAcfgghmMvNOBQjMQ4jMJEjEZ5bzkXpOWYTOzN+95y6S9XFn2wEvqidT4Pma+KznwtZb5WWBlb4w30IHxkvpEyXqgjVpP5VpSxfS+jiN8zP3uJhkK+t7YI37tOWJ5bZJqMM1qb/74k35tcinFGcQrWwxnYHOdgN3wCh+AijMQlmIxLcQauwoX4NG7BF3A3rsd9uAHfw434EW7D8/gyfoHb8Sruwhv4Kj5APl9DX9yDD+NeDME3cAq+iVPxAC7Et3AJHkSWQ39VeQ4Sd0j5VMIkWe+rvPfcFa+hB36HbfA6dsHv0RNvoA/+gIPxRwzHnzARf8YF+As+izdxG/6KSn18UdoUxJV89WpiGeoVxqEzxqNSHwuYL0zmG4fOGI7MR70mZL5aMl9Z7CTzrSzNfPgUVsJV6IxPY01Mz5PvUFlOe53035Z6cwRb4TtonW+tzFdFZ74Rku+RWBmD86zvwQLm6yHz9ZT5Hswz38UC5usr8wXIfP2U+eQZOaipM98gvlcBg7AGDs67XQqYz1Pm88Ia2C3PfD4FzNdL5vPDGuiPynaQ+dx15ouW+WKwNo7HG2gk0mS+zTLfAxgh8yXyPTdMwsaYjP1wMj6EKTgGp2IqPoYLcRouwen4As7ADZiaJ7/GDfbzO0/yO1/yuwCVelPAfEtlvjSZb1me+U4VMN8YmW+szPcI3sAgwvycEvjKfPehv8y3UI4Pi7AuLsYGuARb41L0wjTsgcvwBl4kQmW5PIfEci3bO1OWe4n9xAW/xFp4BevhVQzAb3AQfovD8BrOxeu4Hm/g6/gDfoA/4kX8CW/iz3g/if+CTfEm9sZbOBx/w0S8jbPxd1yHDuT/LXTE81gGf8NyWNFUNtgMy6OyH2yyf3waLceZh9EZx6CyHxQwX4jMF4rOGIaW4xrTZL6WOsc12t5sZ8oBXfBnrI+/YAu8iUo9KyD9yZL+FEk/JU/6B2U+H5304/leFTRiQ5yELTEBvTFRWX95DgedddL/TdoZt9EJf1fyTch8HXTmC+R7rvgQtsaBKPnmuRf75fatlNs1dMHvsD5exxb4fZ70M2Q5lXTSHy7lNgIr4khUjusFrG+MzDcenXBCnvK+KPPV0cl3H5mvL1bCAHTGfuiO/W3L4TkQ+8vxluX4YCX0RWfshe7ol7feynK8dNYjgu+5oAE7YSTewPlEmsz3rcxXGafJfI3lONwEO2NT9MfmGIQt8BFsibHYCmdia1yFbTAd2+LL2A7fwfb4MXbAK9gJb2AGIc9q0E635Kcq/71B8lNejpf3YzOsgK2xIvpjZXwYnTAanTEZXXAKVsVFWA03oavkyw2PYE3MwVr4E9bGX7AOupKfutgZ6+NwbCD53kuYn+3AwZLvapbf+nyYJu35Ydgch2N7HIHDcSSOwdE4AR/GR3EMLsCx+Cw+gtswBN/EULyAYfgzjsNbaMDa5CMSW2EU+mE09sXxGIgTlPcKyLMi+KTOewVaSH1riQ2xFfbFNjgA2+FIbI9R2AFnYkeci53Qms6pAtKZJuk8LulMl3RSJZ1Zks5sSWeOpDNX0pmn7A/yzAb20Gt3mcoHA7Ar9sszrs0pma85cSXfuDYPsfz7cSA64yCsjkHYCAdjMxyCsjx5PoIy1FleV1meJzqjF1bHbtgIu2Nz7IHKOD6yvKd1lveA7OeV0RuroB+6YDJWxeVYDeX3rjy3QB0iruT7vdtVjrsPYkP0xk7ogz3QF/tgLxyJfjgG/VG2A88k2D+ftZfzSQc=
*/