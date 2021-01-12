// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_UNIQUED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_UNIQUED_HPP


#include <boost/range/adaptor/uniqued.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Geometry>
#if BOOST_VERSION > 104500
struct tag<boost::uniqued_range<Geometry> >
#else
struct tag<boost::range_detail::unique_range<Geometry> >
#endif
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_UNIQUED_HPP


/* uniqued.hpp
mVw/54RgnuEwb7n/uoe9Yw2ByZg1u2O7gOtXxPCaI33bnmc/D5Pj2hb78IJxgcl4hpi17sK5wyKEXTJ63oA9JsxCzqF22D6eHbDVec+pBbU9Hfy6G2s5NrR93jjNhhze25G5VFR/FtUsZ69LbfafME8xLuTx8lnsiWDRwmx/lGFtfQkLFvb11T3GzDHc8F7GLogrzlyCWQnbPsrjCfslWEFhhVYvWck5hMOF7bzx4SR7dliY
*/