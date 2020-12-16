// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_POINT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_POINT_HPP

// Adapts Geometries from Boost.Polygon for usage in Boost.Geometry
// boost::polygon::point_data -> boost::geometry::point


#include <boost/polygon/polygon.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{


template <typename CoordinateType>
struct tag<boost::polygon::point_data<CoordinateType> >
{
    typedef point_tag type;
};


template <typename CoordinateType>
struct coordinate_type<boost::polygon::point_data<CoordinateType> >
{
    typedef CoordinateType type;
};


template <typename CoordinateType>
struct coordinate_system<boost::polygon::point_data<CoordinateType> >
{
    typedef cs::cartesian type;
};


template <typename CoordinateType>
struct dimension<boost::polygon::point_data<CoordinateType> >
            : boost::mpl::int_<2>
{};


template <typename CoordinateType>
struct access<boost::polygon::point_data<CoordinateType>, 0>
{
    typedef boost::polygon::point_data<CoordinateType> point_type;

    static inline CoordinateType get(point_type const& p)
    {
        return p.x();
    }

    static inline void set(point_type& p, CoordinateType const& value)
    {
        p.x(value);
    }
};


template <typename CoordinateType>
struct access<boost::polygon::point_data<CoordinateType>, 1>
{
    typedef boost::polygon::point_data<CoordinateType> point_type;

    static inline CoordinateType get(point_type const& p)
    {
        return p.y();
    }

    static inline void set(point_type& p, CoordinateType const& value)
    {
        p.y(value);
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_POINT_HPP

/* point.hpp
Z+tzxoV4TynjLmNMyj56UvaDzlnPHKB3ftI8lYZ/2nkW/Ex+K2ffNKhvz9S00O+nq/1yVr80TuRf7aHu5m1t2T9lP2C7ZN0RUn6TlPecZ1q0TZ0ubr6wW2cPRU7MPr6yzi9MEfNv7Xo3TtAa6Roxc2j7R56KPNT+hm2l1c7ml/jUCph/9klNC9jjf2SjYb5OZTP+dQPm2iTZeP9ZjAkSxmm733ykaS7l/YiYt7WLjH8lxb/6vn2pGGkjuOpQnFj7Ru0kDitVNuNQkjkfd972owym+eqx11XBE+UZwgXiqXIazhnFwTajf8ZeMewMRpln4hrJkTgaBUPQOmzam4fKMv1TfyKwF+UOOM+mYV9I0/vQM9ZiM3ekob8UvWOo9aK/2XDpkvNqavYjaqPhf2TGWtO/6tRTj803xyxIXdqBOov6EVUdPZfOE39Chsj/u44Zc7wGm4L3o3plq19pIepXes7zUNZ53m6iQ7uFp4Xgc1qXrm4KWZf6Uprutpasbqpa9alYliEPzlGfdP1Q7afYG5Hz622rrDrVYfO961R+8Xec1inTn9Ih61QcLCL20+yhynhL47nFvE/OMq7jrbJinhpUJ2P0nquBYvYzT038Rc+Mf17fHUW0Vd0HmWVqppSpbH2HVZdGiV83xd3VgfQ7g8wy96K/zKlZt0FWmZtplrkSGt6BQXrOs78c8/RMBhFUD+5ulvMyvTBfjTL7n4HUnYhofmFD6oLa2Ycyz37254CMGU7AnohVvi9Z5fr/K8/DN1vlOeQeSbcQ5blXiPJs3TWb7gtgGn1DSZgGKc8cOA1ZnvsPC302HfvBdx6VEfkxR8g7DSz7tay8rCVyc8fdynCimLdxaBlW94l3LcOFt0jbrzK3jhsyT5iA/dm+sbxxWerIUcYx0r59cBzq7EDnUSn9bdbeRZyMxc1zIDKH9e1Na5zKvyPretwQ8EW2d2dTsKPjPYl3VVY8E6wx39S3Q37bImh/gLNTOv+QXR6rLs4RtzfsCVZd1Bm20Y0Y1gPWUr0Sv2jdr6EFELkOt4DcDDh7OWz0KF81C5g/W+nRZ3DKyJGmWSIMmBsFvX9RR+KVjGymWWd8DVoH1/AGDMXAiuMLEqfC0rd1pwTMG6ZjSdeU8l5vBB/IyCsfYIkI8zpJkpzfM9PyVVX8KWWvYDst/d9tDAcPCxhDNvLUhi4nddkZq3fHqb1M7G3UMD0RMpyUs3Fmfa5Lfc5FWDXMdc84/9jyIfR28LseevVRtZAbqb3aWscz/o/zFJTb0OcptL5vD1Hf92Wr70W1nZgt7nKW+5igdUwp89ZaZrmAO8r1/Ia+I2+VE9FPtNxrGfGfz4Cij+3g79Ecw4Hx9y9pe6C2PVXfDdn2pPPyD5FPGdJ7cMj31tVdFevsV0+RVznW2h2h71ax3LA+rveJdRd5kmMyqzgbmLn/Q7+Z4/0UbeMeE7vrHG+xr6/tkvpXXsKLlYJPtG1BdVn3KdDX9AvcY9qwVdpR3hppi13/HtN7ol9ByvJJCsh2UvhN+RZfSY+XBck6YXxdJsobiVao7+rofJn6JfFr7Bhvt1tt42fbZF8ye/tjzdHW+p7J8Yi9UKjv61jvk0wWe7XleZJ1/26o6M3kNFsph8+uWNYwY6y21ah7+UawnzNS+/4UqXeeiSCXU++BxbzUyIB+2JtL5rSmWcORZh8vjvOZ9dX0e8tIne8m0owUZJjc3/+dnRaYTff77WprjI+1zpdR8yxDqXtvWD5PpDQgtCNB39nRMDWfClPY5uYnThFTIj25cRcfY0T9gWz3Vee871rb9+bkO3oq261yYK0bB7+LYX3n4uuAe2l62e/d3jS0m+0Nc0t7cPsy054=
*/