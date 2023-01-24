// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_SELECT_COORDINATE_TYPE_HPP
#define BOOST_GEOMETRY_UTIL_SELECT_COORDINATE_TYPE_HPP


#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{


/*!
    \brief Meta-function selecting the most precise coordinate type
        of two geometries
    \ingroup utility
 */
template <typename T1, typename T2 = void, typename T3 = void>
struct select_coordinate_type
{
    typedef typename select_most_precise
        <
            typename coordinate_type<T1>::type,
            typename coordinate_type<T2>::type,
            typename coordinate_type<T3>::type
        >::type type;
};

template <typename T1, typename T2>
struct select_coordinate_type<T1, T2, void>
{
    typedef typename select_most_precise
        <
            typename coordinate_type<T1>::type,
            typename coordinate_type<T2>::type
        >::type type;
};

template <typename T1>
struct select_coordinate_type<T1, void, void>
{
    typedef typename select_most_precise
        <
            typename coordinate_type<T1>::type
        >::type type;
};

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_SELECT_COORDINATE_TYPE_HPP

/* select_coordinate_type.hpp
ypWxaeaQZ5BbJN9Lr2pTcJzocqp3tt7aWc6CMQUJ+ePQQfWll/gShiidSw52HQSWQx+Z63c7WigtG6yP9CaeZ6/hH/Ui1rBaCSryT/LSTyBoyggrGI+erMCOSyuS7YljYFbIS/dn/e/svnYhMUaFmzOIGXuTctyZ/tAkyXaS79ZBG6HF1iOb+5tWp5fumpbPVgBZjt3ph3YDw+QR1pozJ3Pmk7GWOoPz4zHX/c3W0Oj1Fw6ArCFaZVsbRENXmxxKJsL8taubwzBVU+i2AQQ3vOPVKLvzharqrnJI5LxwIGObcyYhVnll5yKkTWm3fv6FzGbsTep5eA0ywP5lsECAtEAuipBw4INj8W9i7bepNSgcJOCwXDdHLice4em85rq53++e+LwvdbjUk1BKerVsihWlglvkksIzjxgx9PHOULnI6WTCuAKLSK7OkDZxsdBxcxKTn38tMrMR9Q/8+EoXEvG1IJH0heDSJAa2Nt0KURSps9xsbWrcaW8PmYF+vEckXVAYER5vBF1IdrG9tTUm3skseq+PdD/jiznX8eSG+1D1i07o5DuvsFnvPYPo994gYkoUUXUkiTzTbYVW9dGp8OziuFm0dZJeZKaj1/DfSL42vfKYOXFqHGtOQN/AnIatJFQEskcJUo4EutdK5xutamLwABuX6rdtIU02PGeT+fSZFZ+vQYdY+aLh265ehs2HWvM7GP6SSsQ8AzZX
*/