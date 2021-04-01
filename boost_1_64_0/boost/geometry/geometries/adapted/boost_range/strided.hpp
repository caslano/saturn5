// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_STRIDED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_STRIDED_HPP


#include <boost/range/adaptor/strided.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Geometry>
struct tag<boost::strided_range<Geometry> >
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_STRIDED_HPP


/* strided.hpp
SZetVRqfg7LA07rkPYNXg+mR7p4uuXVZU5+C+6TSjutKM/WqqNBiH/Xcra1tNP0ulYAeNK3UaGmNDmSrc3tmKHOLY00cGcyt5w57v3dj2ywBD+dsJbLORwQsO/VAfxA2rXDY/mnN0ScQjPYX2lgsRMAP8I2SGNhYQCph4lLucsFSlMHQQuJWkNwYus9JoWafA6cOUjboR4Q3MdHao89A2UPwnjJIMxUhZVBNkcXl4eIlXpQoiHhh6v0PfXdQiYd9Y+GlAp+sufu73KpDmmKpeIk+B50ZJgsZhrGiS+nqirpMSf7fhKRv3IYTeLGM4VZndGFHMvCF7Bv20LnSbjdHCZw2FCJzrdb4mAN3I1EzkrxQQ7wE1aB0fnDiP+1Z/c83wPV25ZtFDSClWaDvKMr6S0D6hktK5NsWlbpmAU3wOUPHX9bhnimI5KC5igwWV6fcs1lHgn0pN7YtnXJqvhKKNx3vpc37jLJsqlq8Ms8xZMCU67r+JP3r0ZD3RrfHwIx4OqzcyLTdlha+rwCJ0B20ZirV8HgbQUPn/RWuas0rf539tWBYdu+8T6s/BA==
*/