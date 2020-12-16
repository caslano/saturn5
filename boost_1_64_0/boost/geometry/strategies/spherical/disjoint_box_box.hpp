// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISJOINT_BOX_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISJOINT_BOX_BOX_HPP

#include <cstddef>

#include <boost/geometry/core/cs.hpp>

#include <boost/geometry/strategies/cartesian/disjoint_box_box.hpp>
#include <boost/geometry/strategies/disjoint.hpp>

#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry { namespace strategy { namespace disjoint
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct box_box_on_spheroid
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        typedef typename geometry::select_most_precise
            <
                typename coordinate_type<Box1>::type,
                typename coordinate_type<Box2>::type
            >::type calc_t;
        typedef typename geometry::detail::cs_angular_units<Box1>::type units_t;
        typedef math::detail::constants_on_spheroid<calc_t, units_t> constants;

        calc_t const b1_min = get<min_corner, 0>(box1);
        calc_t const b1_max = get<max_corner, 0>(box1);
        calc_t const b2_min = get<min_corner, 0>(box2);
        calc_t const b2_max = get<max_corner, 0>(box2);

        // min <= max <=> diff >= 0
        calc_t const diff1 = b1_max - b1_min;
        calc_t const diff2 = b2_max - b2_min;

        // check the intersection if neither box cover the whole globe
        if (diff1 < constants::period() && diff2 < constants::period())
        {
            // calculate positive longitude translation with b1_min as origin
            calc_t const diff_min = math::longitude_distance_unsigned<units_t>(b1_min, b2_min);
            calc_t const b2_min_transl = b1_min + diff_min; // always right of b1_min
            calc_t b2_max_transl = b2_min_transl - constants::period() + diff2;

            // if the translation is too close then use the original point
            // note that math::abs(b2_max_transl - b2_max) takes values very
            // close to k*2*constants::period() for k=0,1,2,...
            if (math::abs(b2_max_transl - b2_max) < constants::period() / 2)
            {
                b2_max_transl = b2_max;
            }

            if (b2_min_transl > b1_max  // b2_min right of b1_max
             && b2_max_transl < b1_min) // b2_max left of b1_min
            {
                return true;
            }
        }

        return box_box
            <
                Box1, Box2, 1
            >::apply(box1, box2);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


struct spherical_box_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return detail::box_box_on_spheroid::apply(box1, box2);
    }
};


namespace services
{

template <typename Box1, typename Box2, int TopDim1, int TopDim2>
struct default_strategy<Box1, Box2, box_tag, box_tag, TopDim1, TopDim2, spherical_equatorial_tag, spherical_equatorial_tag>
{
    typedef disjoint::spherical_box_box type;
};

template <typename Box1, typename Box2, int TopDim1, int TopDim2>
struct default_strategy<Box1, Box2, box_tag, box_tag, TopDim1, TopDim2, spherical_polar_tag, spherical_polar_tag>
{
    typedef disjoint::spherical_box_box type;
};

template <typename Box1, typename Box2, int TopDim1, int TopDim2>
struct default_strategy<Box1, Box2, box_tag, box_tag, TopDim1, TopDim2, geographic_tag, geographic_tag>
{
    typedef disjoint::spherical_box_box type;
};

} // namespace services

}}}} // namespace boost::geometry::strategy::disjoint


#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISJOINT_BOX_BOX_HPP

/* disjoint_box_box.hpp
ie54BMvjGayAV7EiVlfOR9AHK2MTrIItsRq2Qw/sg9VxIHrhUPTGSXg3RmNNnIY+OAd9cQHWwi1YG5/DOvgvrIsHsJ71OFNGniWSZ4xyiQbKcUbWV7asr53YDF/AQbgLJ+FuNOEeTMa9uBz32eWwP4a5eAJfwT/wAN7Eg6jU4XW8B/OwO76JI/EtnIaHMAMP43LMx4fxA3wMP8Q9WIAH8WM8i59iOZbpGLbCz3Asfo7j8TguxVP4FH6Br+OXWIiEnDfIszz4oMF5Q7ScN07BuhiHTTEeg3AadsXp2BcTcAjOwJGYiBGYhHFowmScibMxBeejGS9hURnteR6e87HURzlOnpPt9ofkmr2B6v1O7IpuksOzDIajO47GKhiDVTEFq+E89MC1WB0fRU98Cb3xbayJn6EPfoW18Cesjb+iP9ZQ2hvWwfrYHBtgEDbEXtgYx2JTTMVmmI7NcSm2wCxsiZsxELdjK9yPrfENbIP5GIRHsC1+je3wO2yPbqyrDlgFO2Jj7IqJ2APTsCcuwhDcin0wB/vhHuyPBzAUv8NBqBz/wrAzDsXRGI5LcAQ+g6PwGI7Bn3AcNlDuX2JXnIC9cSL2xfuxP07SvptAniPCOIP7HLyXZfjjbhyEe3As7sWJuA8n4X6MxhetuUTd5XkfeQ5Ime96Zb93t8z3pHz3zFcYiF9jZzyL/fA8huO3OB4v4CT8D8bhd2jC73EBXsRl+AOuwR8xG3/C57AI9+LP+CZewvfxF/wUL2MhXsGv8Vf8Dn9Hb+X6EOvjNWyMN7AN3sSu6CbXm2UwHMviBCyH0VgBk7AipmMlzMRq+CV64294NyrvyzWwHPpgZfTH1lgXe2M9HIr1cSQ2xPuwEU7GxjgVm+FMbI7p2AKXYUtcgYG4EbvgduyKe7Abvo090Kcc7RfrYS8MwBBsiL0xEPtga+yHHbE/dsWBOBxDcQLeiwtxEK7AwbgOw3ATDsXHcBi+iCPwKI7Ez3EUXsfRWEG5f48eOBbvxvFYE+/DILwfB+IkHI4ROAsjcSFG4TKcjKsxBrMwFp/HOHwL4/EoTsNLOB2vYwK6l+e4i3dhElZBEzbBFOyNZgzDVEzGNJyHs3ExzsHlmI4rcR7uwAx8CxfiB7gIf8HFeAMfwgoVuA+MVXAZVsPlGISrcQCuxyjcgNG4GefgFnwSH8dncSs+j0/gC5iN+fgMfoLb8RjuwBO4E8/hC/gT7sKaHED+hZ1wN0biHlyAe3Ed7sOX8UV8BV/CD/FlPIGv4Cl8FW/iAbyrEu/vWAMP4Sg8jNH4NibhO3gSj+BpfB/9Of4cxZb4IXbGj7ALFmBP/AT746d4yXJ/TJ4BY15y3ufnxnys38Uj38m0F+vjPmyD+7Ezvogj8SWcjC+jCXMxGV/FTXgAs/EgHsbX8H08hKfwMJ7Ft/FHfAf9qM+72ATzsRl+gH3xQxyJH+F2/ARfw0/xLTyGcp9Rnvdinze4z+hRkXaE1bEWemJj9MKO6I2XMKesPKslz3Ap8xnB71tQ+fEsz3Eea2J39MFQrIPx6I8mrIdrsD5uwqb4DDbDvdgc38AWeBTb4hlsjxUpvANWx47YHjthV+yCa3EAnsVQbKu8v+ICHIofYDjWUd4/MR4n4n6MwJs4FYcon9fhZjThf9CMnVlxc3EQpmMUzsM4zMR9uB5v4EYMYz/ZhI/hFjyP27EId+BdFVmv2A6fxR74HI7C5zENd+IC3IWH8CV8H1/GU5iLf+Ar2LwS7Qx74EEcgq9hJOZhGr6JOXgI38K38T18BwvxXfwWP8Sb+BH6KPsP1sV/42A8gbPwJK7DU/gcnsaX8Qt8Hc/iITyHJ/Eb/Am/xT/wAlaszPs=
*/