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
8hubDZ/PxISmSJeC0MLzDebD1rHAuAvnPpfu+9aTtJ3Kt40pgvndyf9V1qd4FFOsefL0i2WEfBsBLNX9G/O6dpmg0udcaklI2DjP5gqYCw93ok5a6KdhSemovnc9BlBBpP5Q8r4ymq/r9Z7qXuLlVv0OvZToths0mbenrQUO92UOfdAKOyYd6b5i65dpvbcJ87+d1uO5Qj7atYQ/tJ1dcqdLmAKiVMkAGDC/DA1FQ9vI879UKeZiAUqGPLJC1oyiLPHupj1kQcq3CA8uozDxVVLrr/fZ/QaG/FxDG/Q+sF0vgWK1EP48aUtPFhP1TCGm2ZVLoc3EB/Wn0Of6GG2OtcnejsZaR86KxlCxxYijmPxYF2oMiBGgenVTTlv6+zcJ45tT9vknS8Qj4SMdXQADE0OLYjfGMadGwbsvuOLRxs7S5zbFUhLvuNrj4+FcV73uffH2u5K/BNYcf9XFbxCKZ+R0r1n7+B6xgTvUxv8tMZN7GBlbOrvXPApdBcDPvb0KnzVyHPnQPZUvsRx9E7X18ae/B+CzOwougGCI6/dtOYYl1msVms/1RKwqe+omDfBZJXvJnZu1ukcZ3Dc7fdoAt/ZY8zViIWMnrffwNnf6YPD83mVZqxILrvJ5QuwPrbHkjqkU4TOEXhyeVeXfqOyE4llweBvY/fmLXQDstj1upA02zOSa3Y+0JkH2X/eUQskXniKILNa1G6bAmc4S
*/