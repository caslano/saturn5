// Boost.Geometry

// Copyright (c) 2017-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISJOINT_SEGMENT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISJOINT_SEGMENT_BOX_HPP


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

// TODO: spherical_point_box currently defined in the same file as cartesian
#include <boost/geometry/strategies/cartesian/point_in_box.hpp>
#include <boost/geometry/strategies/disjoint.hpp>
#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategies/spherical/azimuth.hpp>
#include <boost/geometry/strategies/spherical/disjoint_box_box.hpp>


namespace boost { namespace geometry { namespace strategy { namespace disjoint
{

// NOTE: This may be temporary place for this or corresponding strategy
// It seems to be more appropriate to implement the opposite of it
// e.g. intersection::segment_box because in disjoint() algorithm
// other strategies that are used are intersection and covered_by strategies.
struct segment_box_spherical
{
    typedef covered_by::spherical_point_box disjoint_point_box_strategy_type;

    static inline disjoint_point_box_strategy_type get_disjoint_point_box_strategy()
    {
        return disjoint_point_box_strategy_type();
    }

    template <typename Segment, typename Box>
    static inline bool apply(Segment const& segment, Box const& box)
    {
        typedef typename point_type<Segment>::type segment_point_type;
        typedef typename coordinate_type<segment_point_type>::type CT;
        geometry::strategy::azimuth::spherical<CT> azimuth_strategy;

        return geometry::detail::disjoint::disjoint_segment_box_sphere_or_spheroid
                <
                    spherical_equatorial_tag
                >::apply(segment, box,
                         azimuth_strategy,
                         strategy::normalize::spherical_point(),
                         strategy::covered_by::spherical_point_box(),
                         strategy::disjoint::spherical_box_box());
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


namespace services
{

template <typename Linear, typename Box, typename LinearTag>
struct default_strategy<Linear, Box, LinearTag, box_tag, 1, 2,
                        spherical_equatorial_tag, spherical_equatorial_tag>
{
    typedef segment_box_spherical type;
};

template <typename Box, typename Linear, typename LinearTag>
struct default_strategy<Box, Linear, box_tag, LinearTag, 2, 1,
                        spherical_equatorial_tag, spherical_equatorial_tag>
{
    typedef segment_box_spherical type;
};

} // namespace services


#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}}}} // namespace boost::geometry::strategy::disjoint


#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISJOINT_SEGMENT_BOX_HPP


/* disjoint_segment_box.hpp
PXrg91gPL2Jb/AF74Y84DH/CyViEs/ESLsNfcA1eRrkvzvNazj9vmiWfH6ZhEM7BPjgXB2A6DsZ52n1+eaYKmxncL4kvy/kDTsNGOB0vYQYTZMt0j8h9i1b8bpbz7TS5T5eOvjgP/XE+jsEFGIUZmIoLcRYuwjX4IG7HTNyFi/FtXIJHcAUew5XoLd+tFIirsTc+jPdiFkbiGpyMa3EursNc3ICv4SN4Ezehcn7yGA7GzTgaX0Yz5uJyfAWfxFfxaTyAe/F1/Bjz8Ft8E2/gW6is2EPoie9gAL6LbTEfe+N7OByPYBS+jzPxI3wQP8a1+Ala2oM8x4UdDNpDFNvLHSejF0ZjfYyR7RmL7XEKap8XyfxaGrSHRGkPSdgETRjMcSHh7rLkpneaw17LX7+N8Y4SRYRnjbJu3YlIIpPIIY4SFwlPLqSCiHDCRKwniue8zzzx1/Lel5Tzvll/xiO6E+uJjFvmvHee737bib8n3/2tc93/vXnu/xc57g+f0OW5v+0c9+7DGec2ctx3IBqXMsf935HfPrdm2b81x/3fnd/+/ym3fQHr6irhxw2VECKGWEnsJ44RVwl/37Ju/Yg4YhNxkLhIVPUr6xZITCTMxBYilzhH+NViGxATiXRiG3GYuEB4crOmAxFJZBLbiMPEOaJSnbJuzYhQIo7IJLYR+cRlIsCf14gEIos4SJwj/OpSfyKOWErkEHnEnZ87P3d+7vzc+bnzc+fnzs//w4/7P5v/n77+fz3/v5LH39uNabXc+mkdg7rQlzEpma6W5jRJrK+O9yz9bcztnIyndmPi8zLGM+Oxcc7GS4w3275KQM0Pf8AuP/xuue/RgfAl2hAD+CWIB9LKSJ7RUeMsKW0T4mMTzRF9e7u50A/K2nfd19Jn0Exltf5lwzyJMmm6vAuBckrpTZQnvIhQ6pGhrwf9/Gz1UPsSlqL/V6anVhdd2XllHdfBIH7J1ped4lD2ba4HH1kPtdRhSnpHdW763A/lHOsUxi9FWp1uf5to/R2dbJNBUof18pnhIQpsjs/jUOoQUqSrQ0x8srpzkHJ18jQyl6REmJMitH6g1CnO3bBOfSmE/aarV7i7UnYZ6lLe67Of1Xk3jk1OtvRVdbeuJ3WO6rA0d2t/W4qWZQjFYb7qMHUc1psuP7rkz5TpprAvKuvdkjcmlHWtlLOP1x+3LJv049PmoeUYCvfV+ulrfeBHq3Xm/juvKX9Hyt+j+Nt+fe4vr32fu7pNzbI+My7p1qdSOScrtORcU96sww9+sazDmKTEWAap6/VthunWq5vBetWtH1sfzYrqsPhE+5xjOy3tRRsWZLC+w/GMtQ+6mmVMtpW+vWn9WSdWkD4Lchz4iBjD+om8rK0fMl5ad76Sc51Y+1TXcswVxzCpq8O2jteWm2WU/VPfH7lA6jlfjlXziLHU03TFWs/bO05Zc6wttOyfurYTUtGWc7kaESb5Rz1/1ZUZmxYRE2WOihinvAmMHDVsRH/10MWbhQv9oe2XMURy5l9m5t74E45T2qpWnvQt1hZSaTOutc9eVx3bZ52rxdqni20xSN8Wtb7I9/lqx9a4qJQ4p9s9XN8WteU/Wsnx+DtR+eV36/Lf3vtBsf7Bzt4LdHn8wu4yzrcdrtTlH8y33UnKL5TyN8u62EhE8EuepXzd+5Ar+Sms2/J+yWVocFyQejrug12lTqMqO+Z0jGJ+WX+odUqIs+wCQ3sP6a/k0yhVjkVL20mgGevLPF7ZMZdltLIeDMqMT0zhCH57ZXrojrExum0xsYpjHaYpv1xzrAMJTF0uP1YtP25Kot0xMk4dFj2leP71cwZ1SOCXEIM6sKclx8c+cNvr37ouunvLurA=
*/