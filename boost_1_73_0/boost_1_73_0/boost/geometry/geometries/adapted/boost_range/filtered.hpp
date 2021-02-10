// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_FILTERED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_FILTERED_HPP


#include <boost/range/adaptor/filtered.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Filter, typename Geometry>
#if BOOST_VERSION > 104500
struct tag<boost::filtered_range<Filter, Geometry> >
#else
struct tag<boost::range_detail::filter_range<Filter, Geometry> >
#endif
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_FILTERED_HPP


/* filtered.hpp
Xl0zzTU/vefL8Jlu2P5SYrnHqTZyqqnTFLpdlxhLN8xbfBUybpdqPjty7xRkyQz9yppKT9eI/pcAWjb+r3WVHdeswtwMaBrdikHNubjroHQR1EPC0nNRzS8uEgRKxoWNyPxZFjchVveNRd3tTYjVly3omzNeRs+nNWPCUqpbNhFEMDO3c7arOIHN9Ifyy4Rmi6al3TEJubdzfnp28FOPnZ9193u2nuVeEX/POAnFe86IcIPWWYOtrgWjVfEEtq3FcFYb23xZmQBhdTZzxfcWHYWr2ypYUJXTRLZLvggvswfwmfeGPKGlFHyM1gRekrttXDhr4R/9TpmQ3nxWiWV0+SNpN25gRNxGYeU9zJYZCuG0spCSozZL7mNyjYxDvcOw5GYr7+xj1ZYdBzVgmvc0jZ2cRWwhSKKHjZq1liXMdt4cFs5tjK6txxW4TS5xhOlCgbufu0Lz+abGEg1qC3QSv7VV3pufZNSrPDLYNeClsZqXDytUD1SB5hID7dfA5atdzolgGLMelysm5Bqen7siDYwexsJ/PQB+pWIlqW4YaD3u9/R/njzBbA5Kl5CP/uGb/x6eqFP3xH5jjkXmDfhCAmNiCkxdQORxyYZ2IRrWsjQmv9t7f77fPTvrnfbrwiPgS/ytveSNLuiQCVpg
*/