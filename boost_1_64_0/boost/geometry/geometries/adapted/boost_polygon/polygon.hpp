// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_POLYGON_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_POLYGON_HPP

// Adapts Geometries from Boost.Polygon for usage in Boost.Geometry
// boost::polygon::polygon_with_holes_data -> boost::geometry::polygon

#include <boost/polygon/polygon.hpp>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>

#include <boost/geometry/geometries/adapted/boost_polygon/ring_proxy.hpp>
#include <boost/geometry/geometries/adapted/boost_polygon/hole_iterator.hpp>
#include <boost/geometry/geometries/adapted/boost_polygon/holes_proxy.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename CoordinateType>
struct tag<boost::polygon::polygon_with_holes_data<CoordinateType> >
{
    typedef polygon_tag type;
};

template <typename CoordinateType>
struct ring_const_type<boost::polygon::polygon_with_holes_data<CoordinateType> >
{
    typedef adapt::bp::ring_proxy<boost::polygon::polygon_with_holes_data<CoordinateType> const> type;
};

template <typename CoordinateType>
struct ring_mutable_type<boost::polygon::polygon_with_holes_data<CoordinateType> >
{
    typedef adapt::bp::ring_proxy<boost::polygon::polygon_with_holes_data<CoordinateType> > type;
};

template <typename CoordinateType>
struct interior_const_type<boost::polygon::polygon_with_holes_data<CoordinateType> >
{
    typedef adapt::bp::holes_proxy<boost::polygon::polygon_with_holes_data<CoordinateType> const> type;
};

template <typename CoordinateType>
struct interior_mutable_type<boost::polygon::polygon_with_holes_data<CoordinateType> >
{
    typedef adapt::bp::holes_proxy<boost::polygon::polygon_with_holes_data<CoordinateType> > type;
};


template <typename CoordinateType>
struct exterior_ring<boost::polygon::polygon_with_holes_data<CoordinateType> >
{
    typedef boost::polygon::polygon_with_holes_data<CoordinateType> polygon_type;
    typedef adapt::bp::ring_proxy<polygon_type> proxy;
    typedef adapt::bp::ring_proxy<polygon_type const> const_proxy;

    static inline proxy get(polygon_type& p)
    {
        return proxy(p);
    }

    static inline const_proxy get(polygon_type const& p)
    {
        return const_proxy(p);
    }
};

template <typename CoordinateType>
struct interior_rings<boost::polygon::polygon_with_holes_data<CoordinateType> >
{
    typedef boost::polygon::polygon_with_holes_data<CoordinateType> polygon_type;
    typedef adapt::bp::holes_proxy<polygon_type> proxy;
    typedef adapt::bp::holes_proxy<polygon_type const> const_proxy;

    static inline proxy get(polygon_type& p)
    {
        return proxy(p);
    }

    static inline const_proxy get(polygon_type const& p)
    {
        return const_proxy(p);
    }
};



} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_POLYGON_HPP


/* polygon.hpp
s33JtAe1L1ZbQXlHj3Kta8irJK7kXd5sdwloA3jZ5ZuPfgqNer9ve8h6P2JkStD42VrjvyL297r03Iu67+4qx7tp5rjiguhNc5rzrX67pfznbA80ve+I/d66fmr62cBK/6fFfaWcY23d974t9rNcZhv0p8hvuzo6L2gbYfpZK+fYBT+qwogdcm7E5X/XKz0lNZVb3WW44V+fDNsl8wGHyNazlbfex6Me08KPTx/VM3iv74OdvnclHrKF6RjEdMupAat9Guh/b1DCaSl1PVYLT5TosRMjelLALHsRtgLmPZb8sdItB477Dxum5xoex3rMe/5930y5q1yy2ZpHx0oa9HWIbD1bU1tR7M+KFvspXGmSvTOT9oQxcMD7b+yv+a3JM7TVtskm6RAmz9BV26Uw0ZvFfykO9GWP2m3pT3VOsp+3k0/Sr/0tcdzstJ7VSm95Vknvx/B2wC7xk9XYyqpn17Rqw05FmJ4Z0DToqX4ElMkUCbuoM1sZlHbrOBZvjqcvkHnPek8LOgF3I9tdv60WDxfv0HKiZ0M+EPmgsxqu9vJ82foBq7y9vkO/uyiy6e5jcdeE9LpX3/Cs2K2Enr9vmCR61dWeWFQ/Y9QeaW/plUbPl+4jRK7rmoKOkQbFxtF2kwZv6Z5+X89I6TWKYlYK/V4os8/IOOupCaPM9jpB7WSgpO8Iy/gax0534HfTNIw/sLNJwnibDiS/1YEYfszE7IA/HFfGYelAzP5DzK+istQ9HUh0cAcS3H+Yebt2AuvXcUb/MbWVN7yQ18nAU9Z/8Ws1Zvvz5jSLR38FakE2M7mrH/2lKLmrO3xqXwyC75zWNiLvLr2PGDfJ2F9kqLzy/uCIwHhaaaTxTZvoiy/2krzOOl5HpNcRpv37m/iRijlxDml+DPNemC/IaS7PdRnz7pgv9JmPVsOQ93vfkTrTSOLvxU03lMTfMXXaveLvmkT8fPbOs+rFteVepxm/wfhhw3xBCHP5Hivmt834uaZeVsOQ8Xtjl1nOSRfc3ERp+t6WOIUoC4smWWn3gzcszOso5AvXjf48iVeQmeR3KfQzURKnsKk/YxAYH+s9jMUSn1jaz3CJU0PczEH50myaI3uc4sz0mszzxYnf7/O8IcvSKH1WWRuchAZuiI/pBhP8Qv82SvPoWKiw0v1hLbxbWJ0lLLeE5cb+YCss3GhYSeiloTSs10Klte0psxxMKyPpWdiX1qNwdxu1INhMwstE/6YV3rSKGITM+wsaR8l77P+B0nRufrdyucKMj3NaOdoVvjHKsqyWSxdmS1ELQphL+4bZIpSvXE6roYbB5UDv9vrOiBu+Rug3CJribh5qkc/vptnjV0bjV+5p+T4aY+9pWd5cubyxeb2xBfRfHjaHDXur8acU9pbd3V7I+/HjkYvLeKGZXWRrvFLcajPrMxbOjb1CAXszjeIsWvs478LGql8rRmjt16z9H/PymQHzcsIPmpcfzzYvPxliXn4227y8hK7XzRJ3occzelZI3z8OGssEjannTPVFdr7eSz/TXJfeE3JMzVvIoc/sR+6VPW17ebv1fq76UdAWcp/HMn/KPoCbgu82Vw7f67NTTeedyZa7OFv2vZuBmFUR+1V8Mm7a7ZN5j688Z5BvU7S/b2PsikaykZFjLci6I7y2+FVGZdOvQuJXPvyZhNJ+29Ml3Cl+ydqxms9D+eaVbazyVkLj4Z2qY4KCsjRlbb142VUx7CzF7Y+W/+yo6L5LdMC+S1G158avLPWLSMimC+eNxI4139M7wJpShr/X83L/UAKaIS+6j33HkOdaQpTV5KCyGnzu7L3nfB5eZ8xSBJ6FSYXJz31WWQs67hP08nPovRB1WxlZ3yc=
*/