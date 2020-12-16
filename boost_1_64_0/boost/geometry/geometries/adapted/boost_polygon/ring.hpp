// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_RING_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_RING_HPP

// Adapts Geometries from Boost.Polygon for usage in Boost.Geometry
// boost::polygon::polygon_data -> boost::geometry::ring

#include <cstddef>
#include <boost/polygon/polygon.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/tags.hpp>


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS

namespace boost { namespace geometry
{

namespace traits
{

template <typename CoordinateType>
struct tag<boost::polygon::polygon_data<CoordinateType> >
{
    typedef ring_tag type;
};

template <typename CoordinateType>
struct clear<boost::polygon::polygon_data<CoordinateType> >
{
    static inline void apply(boost::polygon::polygon_data<CoordinateType>& data)
    {
        // There is no "clear" function but we can assign
        // a newly (and therefore empty) constructed polygon
        boost::polygon::assign(data, boost::polygon::polygon_data<CoordinateType>());
    }
};

template <typename CoordinateType>
struct push_back<boost::polygon::polygon_data<CoordinateType> >
{
    typedef boost::polygon::point_data<CoordinateType> point_type;

    static inline void apply(boost::polygon::polygon_data<CoordinateType>& data,
         point_type const& point)
    {
        // Boost.Polygon's polygons are not appendable. So create a temporary vector,
        // add a record and set it to the original. Of course: this is not efficient.
        // But there seems no other way (without using a wrapper)
        std::vector<point_type> temporary_vector
            (
                boost::polygon::begin_points(data),
                boost::polygon::end_points(data)
            );
        temporary_vector.push_back(point);
        data.set(temporary_vector.begin(), temporary_vector.end());
    }
};

template <typename CoordinateType>
struct resize<boost::polygon::polygon_data<CoordinateType> >
{
    typedef boost::polygon::point_data<CoordinateType> point_type;

    static inline void apply(boost::polygon::polygon_data<CoordinateType>& data,
                             std::size_t new_size)
    {
        // Boost.Polygon's polygons are not resizable. So create a temporary vector,
        // resize it and set it to the original. Of course: this is not efficient.
        // But there seems no other way (without using a wrapper)
        std::vector<point_type> temporary_vector
            (
                boost::polygon::begin_points(data),
                boost::polygon::end_points(data)
            );
        temporary_vector.resize(new_size);
        data.set(temporary_vector.begin(), temporary_vector.end());
    }
};


} // namespace traits

}} // namespace boost::geometry


// Adapt Boost.Polygon's polygon_data to Boost.Range
// This just translates to
// polygon_data.begin() and polygon_data.end()
namespace boost
{
    template<typename CoordinateType>
    struct range_mutable_iterator<boost::polygon::polygon_data<CoordinateType> >
    {
        typedef typename boost::polygon::polygon_traits
            <
                boost::polygon::polygon_data<CoordinateType>
            >::iterator_type type;
    };

    template<typename CoordinateType>
    struct range_const_iterator<boost::polygon::polygon_data<CoordinateType> >
    {
        typedef typename boost::polygon::polygon_traits
            <
                boost::polygon::polygon_data<CoordinateType>
            >::iterator_type type;
    };

    template<typename CoordinateType>
    struct range_size<boost::polygon::polygon_data<CoordinateType> >
    {
        typedef std::size_t type;
    };

} // namespace boost


// Support Boost.Polygon's polygon_data for Boost.Range ADP
namespace boost { namespace polygon
{

template<typename CoordinateType>
inline typename polygon_traits
        <
            polygon_data<CoordinateType>
        >::iterator_type range_begin(polygon_data<CoordinateType>& polygon)
{
    return polygon.begin();
}

template<typename CoordinateType>
inline typename polygon_traits
        <
            polygon_data<CoordinateType>
        >::iterator_type range_begin(polygon_data<CoordinateType> const& polygon)
{
    return polygon.begin();
}

template<typename CoordinateType>
inline typename polygon_traits
        <
            polygon_data<CoordinateType>
        >::iterator_type range_end(polygon_data<CoordinateType>& polygon)
{
    return polygon.end();
}

template<typename CoordinateType>
inline typename polygon_traits
        <
            polygon_data<CoordinateType>
        >::iterator_type range_end(polygon_data<CoordinateType> const& polygon)
{
    return polygon.end();
}

template<typename CoordinateType>
inline std::size_t range_calculate_size(polygon_data<CoordinateType> const& polygon)
{
    return polygon.size();
}

}}

#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_RING_HPP

/* ring.hpp
fN+Q33eGXLex7Bez1iiixf4wZybvxiXoXG+F6NVzVrE9wVnlOpjk1rtsrHeorT2LimJ3qzPUenIB+M5+mSuozIzugK6Z6DmJQuL+qDPg/Lx1x8d+cTuKldeKtLSR8vzt5TzyOFtlnSeWFPdjne2YJbyDumznrATnszON0xoopzOC8yEOXQ/nrQAJvyVtSBPi4/sb/oG0SdjuxeztUc4f7OIEwnDigR2do9WXuKyxj2YPJspaox5s3e14UOJRQ2XuXP1A09n/viF5qd9313nBJXGTyzpvUU7k3c5s52CssxzFxXy/81eeM8xJP6NpnEfiVtiODu28FTfrzEss0gBxW0vvBzfz+KqjBXP6lxhYlLOvw61194kUGpnH6TzkQ7H/E/nQRvRb6lzkbdFntQ/9omJfHKj/jZ3lcaFlCHPcYe62zB9yxuBSzbO/q2CtbTeQPKussl3zIlb62cypxGMGZ72MvtFdw5bjrhS1k4mdLffeG5NnGiXxqmS9a5g9noZ/3hnYQ+XYM1OzOah3c+yZaVx5OWyr4a6DToWG+do9WrUww8483H6jfntd/cLRj6Xp4wu5hg3fM5n2XPi1TfzyDDVnRC4vbagj2n+2RMNd/ax1HuY7rzSU4WF3O1vyqTzzWdsT5Om92gRJC/zNQPnS4h+i4XRKuGq2ArVRzL4jTDcdjj9uRTVu0TM1TTKyPENJDj4WH85IS+aHa3H/I8qaH+4xOoICZjqIuRf323zuw91sLkoy5HFZ+xOGMstKInb/zivv4pfIdueLZacbdpbFGOVpSl3rjrdsdiZh5zXDTtS0etb7/NnsrMDOX0ZYeaYdte5ay1Yuj6gd5pvp3tgSNsteNr8uY2+FxGlqSsC9YWLnEeRo5B35gtY05bxmF+x8iDqt4zvdb8lxBqfLfeyjGmdvaL9l/CbvL6rekgP//3kcvTdG90mstjHobOjllfo9BQ9rn/AslP7yYOj+Uo9oB/eTWq/jDhluPvBov6l+lLnL/oaa0zYmaD9TXdyneF5j/HPHEW/7xNU3PEb7lBNilt9TyLY6yr/nR9RGjZEEMfuzvocNe+m8ub2TFrOdM8FcQ/xQ5nnOUsS8FbehHHHUs9bhbNnuJGOdTtI21PtmlY/59na96Jj9717RG22tV+75TOZQevY0MO7Nwue4f7GtiWxs+4fdkBejKgeMLwdac7CaH+u5G5F5k0Lkgqy5Xgm8Q8x6t+2ShN+SUwqJ1j1iieJmgquZrQBvIv0o/V2671mHsQBmjWUqSdx2eLL3h3V1blNIzFth3s0xyBFpH+98z94ibLLtWFiY7cewcHv+iCftz7g32pIi59tOR9axVYkqaM2DFn1m7rM2ln2/8lo+/P3nAN8ZMb177ag8x0B6s7CAvOFCor5DjVVaa2+3F/Sbm5dG4JeaJ+s+U6aMY/wXkVXW8VQVicd2zyvhKTZ7hMsW695u+9mdZCsXudh2KDLZVihqr62ox4Uf/vfAGn9iuOkR9J7XCtFr7hxjm+qI4xmZZ2leFyCv94SRv9aesrXmK+k/QuJsvgvUVcOoLWU0r+g9qn1/U9HjvLO5DmyFkYsw4lyEgRn2MXNbZnksM/96Ox/NG1Odi0L6DBuR6h87uiXNt1l3PNQT9496FlIHI4zzwq4KEfdTjn3u7QHhL3NGumaGr4yixdO0qStmm1kBfcdlna3V7xlIWYf9xE4aK7lNrfL/ieiVoSRHoafudO0+8FzuHLHnsOrRXJFrZ/PnKfzpQ7qoP1o+dBvCv+Z0WPyyj7KNVz12byQvWriL2gq6A9ynpQzGcX/51JQVl4uH9e4MHbteFnmCvTDhN+FExCB7mDWOHSr+FsCu+BlUprM=
*/