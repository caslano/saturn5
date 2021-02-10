// Boost.Geometry

// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERIOR_ITERATOR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERIOR_ITERATOR_HPP

#include <boost/range/iterator.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/interior_type.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

/*!
\brief Structure defining the type of interior rings iterator
\note If the Geometry is const, const iterator is defined.
\tparam Geometry \tparam_geometry
 */
template <typename Geometry>
struct interior_iterator
{
    typedef typename boost::range_iterator
        <
            typename geometry::interior_type<Geometry>::type        
        >::type type;
};

template <typename BaseT, typename T>
struct copy_const
{
    typedef T type;
};

template <typename BaseT, typename T>
struct copy_const<BaseT const, T>
{
    typedef T const type;
};

template <typename Geometry>
struct interior_ring_iterator
{
    typedef typename boost::range_iterator
        <
            typename copy_const
                <
                    typename geometry::interior_type<Geometry>::type,
                    typename boost::range_value
                        <
                            typename geometry::interior_type<Geometry>::type
                        >::type
                >::type
        >::type type;
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERIOR_ITERATOR_HPP

/* interior_iterator.hpp
78OF7SfCRbwqpgz37XIt+ASMboCkwl2nEPUhAxTpt0SlMrGZj5jjypx6pQFTEEuCGTdcap/vU33tyfSdFJD2dQ54e5hCuyq+RLRF4PnG3mAm8TvGadl2ZCmxx3KD4CcyfppL3JTjd+ZT/zVegfx/zW99BO35r4z60b+GV8jIIOYUBamROJyvdpxl17QUHe2wIxyezfsysIi/B45F9T1Y5HBuKTjA6+zcKmSjnLP+HDRBIDz5Yd9bWxBOL9pD8mG+M7IcN782Y2c+NrVs/ZVu+fs9DoUpeJJMBlcYtUd11fG9Oo+68PFs8DsKedRF5JFLblM6pHWbMcyaMx3DH3wE06KXCfBiQ6KECvL6pjXlxOEX65HojesHFbOa1MM/iI5YLJIut97s7GJvkC7KTINZMZ/hDvw5IYw8KSU6AzdNqYsBn80VtXMuolUkqVq2F91wmKkpHI3CLKX518GuUvi65H8GenGMIPOR7ZqIR7g4iDsH2PMuR2mKt6gLOTh0QssVEwJP+LcXkXJM8Y/n8dD9ThnK+5jU6UA+V4CRtpFae2btWnArn2xmswzhbpdNNfmOuMCzS6L5rI+arkxxTB8V9nViLSCo9jYbzwgziaovvR6y/Kjz6Kx7evbhAyWtQrvQ6+Mj+fg38XdAD+SJ
*/