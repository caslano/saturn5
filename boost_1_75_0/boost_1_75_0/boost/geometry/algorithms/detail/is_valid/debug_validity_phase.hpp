// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_VALIDITY_PHASE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_VALIDITY_PHASE_HPP

#ifdef GEOMETRY_TEST_DEBUG
#include <iostream>
#endif

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry
{

namespace detail { namespace is_valid
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct debug_validity_phase
{
    static inline void apply(int)
    {
    }
};

#ifdef BOOST_GEOMETRY_TEST_DEBUG
template <typename Polygon>
struct debug_validity_phase<Polygon, polygon_tag>
{
    static inline void apply(int phase)
    {
        switch (phase)
        {
        case 1:
            std::cout << "checking exterior ring..." << std::endl;
            break;
        case 2:
            std::cout << "checking interior rings..." << std::endl;
            break;
        case 3:
            std::cout << "computing and analyzing turns..." << std::endl;
            break;
        case 4:
            std::cout << "checking if interior rings are inside "
                      << "the exterior ring..." << std::endl;
            break;
        case 5:
            std::cout << "checking connectivity of interior..." << std::endl;
            break;
        }
    }
};
#endif

}} // namespace detail::is_valid

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_VALIDITY_PHASE_HPP

/* debug_validity_phase.hpp
U+ntomqBp9RTplYos4Juu2zntus2MP2q/t/CmHsO/l7+LdFLY0SKSRD7hFrcg6PjfkLjXkxD223sbnfDO+lJeGd9MjqdYiHWnt+gdkdi4ZOcBzEDPCFwtz8Zuc+ayXnkyPqhOL9klE3vy+R2sqVP6myRwrMONFtOfQZXi4XSOCwXKTeaLdlKj1gipBLBS6KiqPi4XUM6p2AZCaTHvTft9JOcl3oWPOlPAR73lCZzE3MnKhO7NpmjdNW5XIksXDsSRv9tTAfzM7OgWm2TnqJyN1c/pcvdXITxdD4pSuFS9V3G34rN8galz1Kk1lirbHvN1iuwHJTKqYRsI7VPYVWJ2Vza/mHW/muf4rqWG8DTK/YIu7iuJdVbVdGowCgi10rb/tBT/Nya2PE4DoE3SJkwFl54SseDifXZyWa5H28VQqhP0O18RePxwmEjjtmXhpIPU5qrCy3EzF4MsdttZTZjTjG73fmHOc21ZW86mgaB/zzM8PCZh6PxytmC5RBuERuFdbgQlRvsYI7h9kGsER74usNchnYLeI6A++PhGPsgFwwIk2YlhJ6Ws/vRT+p5U/MgD0jeE/h5MU9aLucpfssuxS+3SIXUHmA1twfoIvYACd59KhrvdvxOo8HBEwBX/juy59Kxze//DBGZ4cLf6Wj+70c60ZkEy1F8SmzCQhkqFIpE/e7K+HpH3b/jPLC7wHMS3J9+p/HY+T2jF4zC
*/