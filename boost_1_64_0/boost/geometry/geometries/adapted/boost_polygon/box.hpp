// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_BOX_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_BOX_HPP

// Adapts Geometries from Boost.Polygon for usage in Boost.Geometry
// boost::polygon::rectangle_data -> boost::geometry::box


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
struct tag<boost::polygon::rectangle_data<CoordinateType> >
{
    typedef box_tag type;
};


template <typename CoordinateType>
struct point_type<boost::polygon::rectangle_data<CoordinateType> >
{
    // Not sure what to do here. Boost.Polygon's rectangle does NOT define its
    // point_type (but uses it...)
    typedef boost::polygon::point_data<CoordinateType> type;
};


template <typename CoordinateType>
struct indexed_access
<
    boost::polygon::rectangle_data<CoordinateType>,
    min_corner, 0
>
{
    typedef boost::polygon::rectangle_data<CoordinateType> box_type;

    static inline CoordinateType get(box_type const& b)
    {
        return boost::polygon::xl(b);
    }

    static inline void set(box_type& b, CoordinateType const& value)
    {
        boost::polygon::xl(b, value);
    }
};


template <typename CoordinateType>
struct indexed_access
<
    boost::polygon::rectangle_data<CoordinateType>,
    min_corner, 1
>
{
    typedef boost::polygon::rectangle_data<CoordinateType> box_type;

    static inline CoordinateType get(box_type const& b)
    {
        return boost::polygon::yl(b);
    }

    static inline void set(box_type& b, CoordinateType const& value)
    {
        boost::polygon::yl(b, value);
    }
};


template <typename CoordinateType>
struct indexed_access
<
    boost::polygon::rectangle_data<CoordinateType>,
    max_corner, 0
>
{
    typedef boost::polygon::rectangle_data<CoordinateType> box_type;

    static inline CoordinateType get(box_type const& b)
    {
        return boost::polygon::xh(b);
    }

    static inline void set(box_type& b, CoordinateType const& value)
    {
        boost::polygon::xh(b, value);
    }
};


template <typename CoordinateType>
struct indexed_access
<
    boost::polygon::rectangle_data<CoordinateType>,
    max_corner, 1
>
{
    typedef boost::polygon::rectangle_data<CoordinateType> box_type;

    static inline CoordinateType get(box_type const& b)
    {
        return boost::polygon::yh(b);
    }

    static inline void set(box_type& b, CoordinateType const& value)
    {
        boost::polygon::yh(b, value);
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_BOX_HPP

/* box.hpp
bDxhmrVB962y7Nr7UvUsicYrLf3n/l6+Bf7v+YdLH/NiF7xovvGH2Vd2pVw/PSb4DZYvgo682SLXvdGXJrod9gF/N197f5b/dN+z/mTnOifeS1nF7TPnuOwV/+f6klnvO5ZQu+n6u9+I+YaoaEynsPPe74hrUdRws4++7MMbiG4ViknrTeKvA+50HVSgTNSlrIeSusBPrzFHzM7S9VC7xGylL03ciUOTpuPYWeo+fz/scI9dvMOuk6/G/zgu9Pwy+T6/jbb8Dg+irWhwifF1v3be62T9hLppz0Pr45RZ9OUvsYAiPs4yb8JfEuYPivmr1qKLGHv+SJr6q8b++2J/Z8KChOq4ONxYdp0wz1a/lsfLH7AWTcXLNW37CuSxgF/LX5xt74zXTtw8IG5uwk10tGVei9mmYNjRlzdoWtRuB/IQdnjAmy8szC6naZxX5OGkTS9ZQ4KfQ8Ew26y4QsNUu074ecz4SW1th2nn8TjsE6w8Trgi13HvkDAGq5t63LS03ESv6JgY2ykxuu6rxNiWidHl8u9o69/4Uxx7YMcmh4iGp99ZeedpRPY6vhlae9j+o0PArGs7p5vmnUlXeVXI+SCOdwdp6LXmnY2rfzP7ZI/QcTH+cO/cD9ndL6XYZ87Jt+1An5Oq7ukHTPg+DSfDrHNztiWdS6D9fO1E3YNO71mzkDMIa/tq088XFBcVMJO5soK3L9W5E0pLOGUiy5paEOFMAvU7J6x/1P7c2Ntl3vfw3wLPivx9y5kX7u9Z7H8mv/d0nu+b+l5p3NWSLtd0F3kBJm98a6pC0mT2s5gj/p723R/cz0LD6uJY51NWNT/kfJC54uYZ333865rroGHcJvbjzLfRbUnN/d4Xm9zyGne9ywiZP/KFhM34uov7/Xf2mbpPKhdMhdN0//W8a8LzxvPloHe5q/+uZv7IpaJnyfktnZPd976p1r3vWux5Ax7Ml0IzB2St+O3k3L/d1KFy7EeJ32vxa+zN3KE7xW+0mXtyt+i9o5zncKXomWhnSjjZ/qd9q9QMn2vkvCRMktxncek8oOXi5zj/lbhItczQ8sSsmPvnlb7+/iTPeS2txU2Uya9nROekM20XN0g8N/gTqMX5viF+8Ud82oq7GOveLn3J98TdkKhg3pTPm6f3/grYXdw/6Lfs/5pk5l+Zc3guF/8TxP9msV+UX1YUvBcvFP/xkt4Z6FWiH++vD6QXMzu9c4hrg6Q3OM4okkW1drt5UK71A0Y1rC90pecpfwwjhHLy62L8B9dHV1SVzK8yaflloA7JuoYG2vTKLN470adxI/gwMTYO3JUYm+Az7adlMmLfp9XPZvzcYPlJuBx/ScGxs7o7Ab0leq+UwFkd/ZF6/j4B3iu053E153tZbPKlayLfD9ApQ/f5CRVmnx5NO213+hq77br7tU5n6flPOschV/u1iuuk7XpN49NW692vXSv+zvSdEpzboGEdp3n6zeawrb3OTod7DtuyaQGPW2Lp/4X63t8jHfLWoYpP0Xx5Y6ImX108nzPU71DT9/a43tKviK2MCuwH0VGuXC2H96VoW+gmblbFVkdFY2b6h8XO+WvJ8Ol63KGl6HPYvaJP8MdSf1P1DL+ZYnZq9Kl8I3k/aqDjDEK5pPidZfX5cs2/xOzx93S0Gz51FODGPodP3AyObR+VhpnjfDxuU5VE0l7L+vPvWu7y/Cmi+00cxvjelPZ9qlzfyjyfOWPytxL2+TEV/lN9b/jrosTc4bcDMzVW+a/0m/yQM4Fy5/Hex+THEAkj2pem/Wim6JWxvaNO9d0TnecfEjtc+1N3nFJMO5fizaXuy9g7Czr7zDTti354Q6BMW/BfB6QX0k3L2y/h/sU=
*/