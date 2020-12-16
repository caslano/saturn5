// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_HOLES_PROXY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_HOLES_PROXY_HPP

// Adapts Geometries from Boost.Polygon for usage in Boost.Geometry
// boost::polygon::polygon_with_holes_data -> boost::geometry::polygon
//   pair{begin_holes, begin_holes} -> interior_proxy

#include <boost/polygon/polygon.hpp>

#include <boost/geometry/geometries/adapted/boost_polygon/hole_iterator.hpp>
#include <boost/geometry/geometries/adapted/boost_polygon/ring_proxy.hpp>


namespace boost { namespace geometry
{

namespace adapt { namespace bp
{


// Polygon should implement the boost::polygon::polygon_with_holes_concept
// Specify constness in the template parameter if necessary
template<typename Polygon>
struct holes_proxy
{
    typedef ring_proxy
        <
            typename boost::mpl::if_
                <
                    typename boost::is_const<Polygon>,
                    Polygon const,
                    Polygon
                >::type
        > proxy_type;
    typedef hole_iterator<Polygon, proxy_type> iterator_type;

    // The next line does not work probably because coordinate_type is part of the
    // polygon_traits, but not of the polygon_with_holes_traits
    // typedef typename boost::polygon::polygon_traits<Polygon>::coordinate_type coordinate_type;

    // So we use:
    typedef typename Polygon::coordinate_type coordinate_type;

    inline holes_proxy(Polygon& p)
        : polygon(p)
    {}

    inline void clear()
    {
        Polygon empty;
        // Clear the holes
        polygon.set_holes
            (
                boost::polygon::begin_holes(empty),
                boost::polygon::end_holes(empty)
            );
    }

    inline void resize(std::size_t new_size)
    {
        std::vector<boost::polygon::polygon_data<coordinate_type> > temporary_copy
            (
                boost::polygon::begin_holes(polygon),
                boost::polygon::end_holes(polygon)
            );
        temporary_copy.resize(new_size);
        polygon.set_holes(temporary_copy.begin(), temporary_copy.end());
    }

    template <typename Ring>
    inline void push_back(Ring const& ring)
    {
        std::vector<boost::polygon::polygon_data<coordinate_type> > temporary_copy
            (
                boost::polygon::begin_holes(polygon),
                boost::polygon::end_holes(polygon)
            );
        boost::polygon::polygon_data<coordinate_type> added;
        boost::polygon::set_points(added, ring.begin(), ring.end());
        temporary_copy.push_back(added);
        polygon.set_holes(temporary_copy.begin(), temporary_copy.end());
    }


    Polygon& polygon;
};


// Support holes_proxy for Boost.Range ADP

// Const versions
template<typename Polygon>
inline typename boost::geometry::adapt::bp::holes_proxy<Polygon const>::iterator_type
            range_begin(boost::geometry::adapt::bp::holes_proxy<Polygon const> const& proxy)
{
    typename boost::geometry::adapt::bp::holes_proxy<Polygon const>::iterator_type
            begin(proxy.polygon, boost::polygon::begin_holes(proxy.polygon));
    return begin;
}

template<typename Polygon>
inline typename boost::geometry::adapt::bp::holes_proxy<Polygon const>::iterator_type
            range_end(boost::geometry::adapt::bp::holes_proxy<Polygon const> const& proxy)
{
    typename boost::geometry::adapt::bp::holes_proxy<Polygon const>::iterator_type
            end(proxy.polygon, boost::polygon::end_holes(proxy.polygon));
    return end;
}

// Mutable versions
template<typename Polygon>
inline typename boost::geometry::adapt::bp::holes_proxy<Polygon>::iterator_type
            range_begin(boost::geometry::adapt::bp::holes_proxy<Polygon>& proxy)
{
    typename boost::geometry::adapt::bp::holes_proxy<Polygon>::iterator_type
            begin(proxy.polygon, boost::polygon::begin_holes(proxy.polygon));
    return begin;
}

template<typename Polygon>
inline typename boost::geometry::adapt::bp::holes_proxy<Polygon>::iterator_type
            range_end(boost::geometry::adapt::bp::holes_proxy<Polygon>& proxy)
{
    typename boost::geometry::adapt::bp::holes_proxy<Polygon>::iterator_type
            end(proxy.polygon, boost::polygon::end_holes(proxy.polygon));
    return end;
}


}}

namespace traits
{

template <typename Polygon>
struct rvalue_type<adapt::bp::holes_proxy<Polygon> >
{
    typedef adapt::bp::holes_proxy<Polygon> type;
};


template <typename Polygon>
struct clear<adapt::bp::holes_proxy<Polygon> >
{
    static inline void apply(adapt::bp::holes_proxy<Polygon> proxy)
    {
        proxy.clear();
    }
};

template <typename Polygon>
struct resize<adapt::bp::holes_proxy<Polygon> >
{
    static inline void apply(adapt::bp::holes_proxy<Polygon> proxy, std::size_t new_size)
    {
        proxy.resize(new_size);
    }
};

template <typename Polygon>
struct push_back<adapt::bp::holes_proxy<Polygon> >
{
    template <typename Ring>
    static inline void apply(adapt::bp::holes_proxy<Polygon> proxy, Ring const& ring)
    {
        proxy.push_back(ring);
    }
};



} // namespace traits


}}


// Specialize holes_proxy for Boost.Range
namespace boost
{
    template<typename Polygon>
    struct range_mutable_iterator<geometry::adapt::bp::holes_proxy<Polygon> >
    {
        typedef typename geometry::adapt::bp::holes_proxy<Polygon>::iterator_type type;
    };

    template<typename Polygon>
    struct range_const_iterator<geometry::adapt::bp::holes_proxy<Polygon> >
    {
        typedef typename geometry::adapt::bp::holes_proxy<Polygon const>::iterator_type type;
    };

} // namespace boost


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_HOLES_PROXY_HPP

/* holes_proxy.hpp
n8iOx/P9XXzfRZ7xjzL9acxaOc/Yl8x95CT6qRT7uVDMizAfa8b9bVxpDZZ7grhNlfP7xqJHS3zWxoyNCZTds4FZg1LAdn95j+TFlzHb/ZmO+a1yyItcb6Je75nkQF3zaR5ku+Ihzs0coRTj3voMJv212OX5ws97TtG4PyBx/Qtznps0PYzEbgw8Z6XoOSauZ0fN80clX+PMfesJ0Zf77HpygehjopOoJ5dTT9b6Zsv4Z1aKjKmlr9gDB6QGzKamQJUZCGMcGXe/wM10IG5m4vZSGtUW+AQyCLPr0QfDIUgGMhTJRNQP/gNhNbjD4trBvmr1Ec6CqoCceyN9Nvli99lhZ4ulomeZPlrrrRmTuvvyiWYeeqC8MZNypezkPL/wdy/iTK6RZ9yZMpY+9H4pR8bNyQG9T73pU0Vvd6N3H1vIhaVW6L2iVO8V6TeF97H6kdU53PO8X2SK31zfSeZ+oeHpXLiqQJ2qWOjY62CU2J9GP59k5mglpQTvKy99jXuL8544/JyAw+s0nVdpOhsPk87C8kVFkcb6P8YfOuGbNGpYnTX+wbj/Ovnr3xt33+R9j8+YrvvB6fj8D34dn98cOT1yq/cel+PP/f7tStHf9T/BvwXUf8f427xju1vcPOe/mT5+oj/a1T86z2Y9JO5yGcVmmnkBLW/RNRLB+6npT5eKXVtnX2/Cim7Q+eb8l6r38Dsl/EL/AsLPkvOcMDfXyHDES58x9czSFeLvA3/oGoRUffa4Wuzf9D/ga8l+9y19eiaSKdcB1M9hqUF9OH8vSm5eOWeHPKeia1vXOFL2JzV4P5ux/7D8viAysncDlHFRQ3jZe06M8K4D6v8UM24YfKulPxzvKHuTd2PvkPNs5Z3kW12kB5F7TbHPdaazeSf90gbZ68Gcm7VSwv5ei7N4Nj6tRSvfzBZR5hzbbnfJOcc+x3nKhXqcsjlPeaiEd4V/N+2tgz9fx01+3xni90ZfvrXfl56ne5Zc65Z4R10z97+dt1l29/hbcCKvPW775A5xT62+3vRPX4q7xf4+nKBgv6OoujO4j1KGe2xixlGjJaxl0Yuo6ydEn27O5p4r8VxAuWYTT/tc3gqKifqj9fqdf1J2JnA2lmsAP9vMnJlzMGYYYyzZ96yTrbGTnbFFJQyDsY99r7EkIU1lDxHKUoySNUtZk0o3FUopKUK5iihd9/895/m+c87M4brz8/qf592/d9++9xP/T9qTeJaylOvKzIF62wdY5XuL+FFMxh29cL1ymawTuKra3DnKfHX9NudoSYs7EWHGlzKoMZMZnc6313B87XzMVsc10JEV/q0tE9M1EdxNot/vHCXh9LLVkDS1vgWcyn/WOOqixLUa685FuHL8wxDfNeszmoLYc0Cqf9z0krjxSj4lIteTuK12++M+aKiEoXF/z3g+UiI/Kb2DsVlRjd85SeN/O7pywvcY32q9ZVtkP8B7kTnmtpqXCyScUrbKumb+i8j9nBX5st8M8ukVnvRL3svqbH/W9q29Pd8SWmAr7kywxWnZXyL2m7tfc5Vx5nL7wjld2EaqD9V1tSbGXoD8HZNycyGsNeVmUVgTuZ9rmK5H/yzxruVoRSmOEzc+R6mS3hNtTUhvsY8+9gPLtqQvYxer7LgpO6lp/vF7NYnjGPdlV5jNGVbVGaLcid/5tGEqInGZy9NPV/3AuKRpXKz5+1DjC/epycN4ZdYafwacqfJ/83sI3rwgcSnt/iKiierZ1d/x4q+8Ty5lyhhZ+NfF3EsMO8PldLxVR+Q50606Uk/spFA76tpeYxVvJ+o89/IkaB1pL+bPRHgYh/5hqxbeLcIX3ijxixQLeC9sueRVWcvtQZHjHB3Jux8=
*/