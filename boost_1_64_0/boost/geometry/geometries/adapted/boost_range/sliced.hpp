// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_SLICED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_SLICED_HPP


#include <boost/range/adaptor/sliced.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Geometry>
struct tag<boost::adaptors::sliced_range<Geometry> >
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_SLICED_HPP


/* sliced.hpp
WCzmzoGI8BSt9MQT2NLbiW1Yh9Wg/ZVKtMjM0NeXNxi3IzGNboM9B47dm8guP/vXk47mPKU9B+onxs4gQZ3T0AyUIpoDPUt0qiWwYHoTbYey7q+pF5AW62I9E6MPGxGfbdzKAu5zZLbYuTeF12rxeXJT4/DvwAxRWTJHJKT/7IlTXqvKydbEZkSoUhTIUI0qtWLbiIrmUAYxvTyrvjQFMd4qljE50Xcuan2U2iYuxPUpfJvHIapZp5SSZ12NlpHMtjcITEZ0urrNyxxGWgXQrhHHhun1/AKtSI3MXg7vE1KFTDRn/ulEsdiiXkSJe4Ip1nxqcPfX5FmdOkRCzjwX+t0OPMCHM68mRVphteqCZUysITkiwSPwN31QXfd2aAweF6CDOiv6SeXzABrB2/ktm+0r7+yxznEkHvtFxYsTsUdMPqtnY1aMaJlnKGUeWKaGCMCz6+ogiUxx5xApb9yO2Pfaw/xvh0LOnP/sTTFUUcKNf1F9ok+mny8nrOpR17iFSDvD17mX0+lavSkiWjmNY8ycLTIU2DC2sfskBIXYNu0JbLRZF/t582WpUg==
*/