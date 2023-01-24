// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DEFAULT_LENGTH_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_DEFAULT_LENGTH_RESULT_HPP

#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/geometry/util/compress_variant.hpp>
#include <boost/geometry/util/select_most_precise.hpp>
#include <boost/geometry/util/transform_variant.hpp>


namespace boost { namespace geometry
{


namespace resolve_strategy
{

template <typename Geometry>
struct default_length_result
{
    typedef typename select_most_precise
        <
            typename coordinate_type<Geometry>::type,
            long double
        >::type type;
};

} // namespace resolve_strategy


namespace resolve_variant
{

template <typename Geometry>
struct default_length_result
    : resolve_strategy::default_length_result<Geometry>
{};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct default_length_result<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    typedef typename compress_variant<
        typename transform_variant<
            boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
            resolve_strategy::default_length_result<boost::mpl::placeholders::_>
        >::type
    >::type type;
};

} // namespace resolve_variant


/*!
    \brief Meta-function defining return type of length function
    \ingroup length
    \note Length of a line of integer coordinates can be double.
        So we take at least a double. If Big Number types are used,
        we take that type.

 */
template <typename Geometry>
struct default_length_result
    : resolve_variant::default_length_result<Geometry>
{};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DEFAULT_LENGTH_RESULT_HPP

/* default_length_result.hpp
1uRUCJaa2MuBGA0OK2Yjdrdmmv7ItztWk7dY1eG+YZL47PxLDwPKvch2upV1yVycYGpyvDYaTnMBLAQiCph/m70zRkPkgMd6fxYZRIyAEgMfinYyxRGohTeDwpei2oV5328sWHVAj4mvJc+Guus49SXOPl6BkcWTSf11eud4hMHBA3Yy3mSXfkgHzjHX/Se6Y5weqDZigeq+xfKmC7rTTEbYpNG5+jndv/cFwJc5w5g2QxIhXThJwWhe26ddyPXjT3c8NFpvYQt8c64E8ehDX0K7D9z9xiaLiJcB8hZvu+I9Mj3e/u76d6nd7jEvL7Rs7ebPUrsv32xzwt+kdn3E+79I7Wb76f+U2nnYG/wwtiRxYKTzfQhE9a1Pu/jCmvEp60IJGAJRHf+z1F4F1YVF2nc3dNvhzt+vz2glfTGPRLb97vvLCnkAMh2N/X8S7Uz/meA87/h5/sKqfXL55GlvY/2P/sZzewVOD+qZOaT5QwEK4rvZM5IvzlJs9Azs9VOIhgXCt19STlAW2Zekye1a6CGTdNbgzNKx3ssdmbC8eIi+9yu9l+VaSbrcwUlU/UqMOpTHDCNZC5PpR5PqaV0MN6YvOPfuLJ1W51d5q59kZ14cVmmlB12r+fYh/Fbr1o9ODvKmmzzXySQCT7rSSE4LxODW3VkvvgAmIp7vRJDzIEfv7tqHqJGOd/EvaNAFapYDPalOYu5zSNHeS3F/
*/