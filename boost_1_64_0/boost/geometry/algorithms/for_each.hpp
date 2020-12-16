// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_FOR_EACH_HPP
#define BOOST_GEOMETRY_ALGORITHMS_FOR_EACH_HPP


#include <algorithm>

#include <boost/range.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/geometries/segment.hpp>

#include <boost/geometry/util/add_const_if_c.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace for_each
{


struct fe_point_per_point
{
    template <typename Point, typename Functor>
    static inline void apply(Point& point, Functor& f)
    {
        f(point);
    }
};


struct fe_point_per_segment
{
    template <typename Point, typename Functor>
    static inline void apply(Point& , Functor& /*f*/)
    {
        // TODO: if non-const, we should extract the points from the segment
        // and call the functor on those two points
    }
};


struct fe_range_per_point
{
    template <typename Range, typename Functor>
    static inline void apply(Range& range, Functor& f)
    {
        // The previous implementation called the std library:
        // return (std::for_each(boost::begin(range), boost::end(range), f));
        // But that is not accepted for capturing lambda's.
        // It needs to do it like that to return the state of Functor f (f is passed by value in std::for_each).

        // So we now loop manually.

        for (typename boost::range_iterator<Range>::type
                it = boost::begin(range); it != boost::end(range); ++it)
        {
            f(*it);
        }
    }
};


template <closure_selector Closure>
struct fe_range_per_segment_with_closure
{
    template <typename Range, typename Functor>
    static inline void apply(Range& range, Functor& f)
    {
        typedef typename add_const_if_c
            <
                is_const<Range>::value,
                typename point_type<Range>::type
            >::type point_type;

        typedef typename boost::range_iterator<Range>::type iterator_type;

        iterator_type it = boost::begin(range);
        if (it == boost::end(range))
        {
            return;
        }

        iterator_type previous = it++;
        while(it != boost::end(range))
        {
            model::referring_segment<point_type> s(*previous, *it);
            f(s);
            previous = it++;
        }
    }
};


template <>
struct fe_range_per_segment_with_closure<open>
{
    template <typename Range, typename Functor>
    static inline void apply(Range& range, Functor& f)
    {    
        fe_range_per_segment_with_closure<closed>::apply(range, f);

        model::referring_segment
            <
                typename add_const_if_c
                    <
                        is_const<Range>::value,
                        typename point_type<Range>::type
                    >::type
            > s(range::back(range), range::front(range));

        f(s);
    }
};


struct fe_range_per_segment
{
    template <typename Range, typename Functor>
    static inline void apply(Range& range, Functor& f)
    {
        fe_range_per_segment_with_closure
            <
                closure<Range>::value
            >::apply(range, f);
    }
};


struct fe_polygon_per_point
{
    template <typename Polygon, typename Functor>
    static inline void apply(Polygon& poly, Functor& f)
    {
        fe_range_per_point::apply(exterior_ring(poly), f);

        typename interior_return_type<Polygon>::type
            rings = interior_rings(poly);

        for (typename detail::interior_iterator<Polygon>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            fe_range_per_point::apply(*it, f);
        }
    }

};

struct fe_polygon_per_segment
{
    template <typename Polygon, typename Functor>
    static inline void apply(Polygon& poly, Functor& f)
    {
        fe_range_per_segment::apply(exterior_ring(poly), f);

        typename interior_return_type<Polygon>::type
            rings = interior_rings(poly);

        for (typename detail::interior_iterator<Polygon>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            fe_range_per_segment::apply(*it, f);
        }
    }

};

// Implementation of multi, for both point and segment,
// just calling the single version.
template <typename Policy>
struct for_each_multi
{
    template <typename MultiGeometry, typename Functor>
    static inline void apply(MultiGeometry& multi, Functor& f)
    {
        for (typename boost::range_iterator<MultiGeometry>::type
                it = boost::begin(multi); it != boost::end(multi); ++it)
        {
            Policy::apply(*it, f);
        }
    }
};

}} // namespace detail::for_each
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry,
    typename Tag = typename tag_cast<typename tag<Geometry>::type, multi_tag>::type
>
struct for_each_point: not_implemented<Tag>
{};


template <typename Point>
struct for_each_point<Point, point_tag>
    : detail::for_each::fe_point_per_point
{};


template <typename Linestring>
struct for_each_point<Linestring, linestring_tag>
    : detail::for_each::fe_range_per_point
{};


template <typename Ring>
struct for_each_point<Ring, ring_tag>
    : detail::for_each::fe_range_per_point
{};


template <typename Polygon>
struct for_each_point<Polygon, polygon_tag>
    : detail::for_each::fe_polygon_per_point
{};


template
<
    typename Geometry,
    typename Tag = typename tag_cast<typename tag<Geometry>::type, multi_tag>::type
>
struct for_each_segment: not_implemented<Tag>
{};

template <typename Point>
struct for_each_segment<Point, point_tag>
    : detail::for_each::fe_point_per_segment
{};


template <typename Linestring>
struct for_each_segment<Linestring, linestring_tag>
    : detail::for_each::fe_range_per_segment
{};


template <typename Ring>
struct for_each_segment<Ring, ring_tag>
    : detail::for_each::fe_range_per_segment
{};


template <typename Polygon>
struct for_each_segment<Polygon, polygon_tag>
    : detail::for_each::fe_polygon_per_segment
{};


template <typename MultiGeometry>
struct for_each_point<MultiGeometry, multi_tag>
    : detail::for_each::for_each_multi
        <
            // Specify the dispatch of the single-version as policy
            for_each_point
                <
                    typename add_const_if_c
                        <
                            is_const<MultiGeometry>::value,
                            typename boost::range_value<MultiGeometry>::type
                        >::type
                >
        >
{};


template <typename MultiGeometry>
struct for_each_segment<MultiGeometry, multi_tag>
    : detail::for_each::for_each_multi
        <
            // Specify the dispatch of the single-version as policy
            for_each_segment
                <
                    typename add_const_if_c
                        <
                            is_const<MultiGeometry>::value,
                            typename boost::range_value<MultiGeometry>::type
                        >::type
                >
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief \brf_for_each{point}
\details \det_for_each{point}
\ingroup for_each
\param geometry \param_geometry
\param f \par_for_each_f{point}
\tparam Geometry \tparam_geometry
\tparam Functor \tparam_functor

\qbk{[include reference/algorithms/for_each_point.qbk]}
\qbk{[heading Example]}
\qbk{[for_each_point] [for_each_point_output]}
\qbk{[for_each_point_const] [for_each_point_const_output]}
*/
template<typename Geometry, typename Functor>
inline Functor for_each_point(Geometry& geometry, Functor f)
{
    concepts::check<Geometry>();

    dispatch::for_each_point<Geometry>::apply(geometry, f);
    return f;
}


/*!
\brief \brf_for_each{segment}
\details \det_for_each{segment}
\ingroup for_each
\param geometry \param_geometry
\param f \par_for_each_f{segment}
\tparam Geometry \tparam_geometry
\tparam Functor \tparam_functor

\qbk{[include reference/algorithms/for_each_segment.qbk]}
\qbk{[heading Example]}
\qbk{[for_each_segment_const] [for_each_segment_const_output]}
*/
template<typename Geometry, typename Functor>
inline Functor for_each_segment(Geometry& geometry, Functor f)
{
    concepts::check<Geometry>();

    dispatch::for_each_segment<Geometry>::apply(geometry, f);
    return f;
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_FOR_EACH_HPP

/* for_each.hpp
2JG4p99vO/pnjeNk33PIJuOozibj9sTUr/mP5+0JMie3ssm1bSN7IiyeCcCyZE+C8XuxOVha99J/z+Nd7CrvTa2H4p4s7772scn7uwNscsZviOwpcoZjRCx+LwQ2yibvX4+x6fkONnkfeoJN3k+eNDYlFu+HwGZM/eZMOReMLZk0V0zcmrENY1vGdoztGts3dmDsyNixseRPZ1uLsYyxdmPnjHUY6zLWY6zP2ICxIWMjxkaNjcHSOeSpsLhnhpVhLWQxn8EqEhfzNWyO42TcLhhbYpNzDCtiPA+usck5og2yCR0rZE+DxbsjsB02KeeusX02qcMBm5yNOBKLd1Vgx7AMWTwXhrXWz8c9Xc6LthnLGsux6bldE9ctFr8xBusle4asOf1ssj4MmrhhY3ljBTY9t8sm/azEJmeoysYqYvH7HbBpU/dZNukv82Jxjw5bJCvrWUQ2SXOVTdpsnU36xCabnkWEpX33mbC4h4XtU9yzpJwHbDpW2KScx2xSzuTPbFzO91+wBZaW89lN7z8tZ2pZsknYmz/45K+k1kVpPgcWdYD1iPEZoz6x6IOwAViG7OlXzj4vtTzFPVfSLBgrisUeGlYSi2e/sLKxCpuc+Zkmex4srgNsluz5UpZ5NqnDoolbJnuBlGUVliH72rPHbpTaFsW9EBbzNWyHTdLcZZNy7sMyZNP3zl45tTqbnCNq+Uuj/f1q7xlLLWusC3ZWWXrY5DxXn1i8pwMbIJuSM0ZDbHJuaUQs1lTYKNUBRvcrH75gieJe1PTh03u11MpikR+soob6pTYtFudFYbMmbp7sxVKWRViG7Lqz37hyamticY1g22LRJ2D7Jr8Dk9+JyS/z17Pzy8HS/F4Ci7kH1ikW8y6s21ivsX6xeP4JGxSLcyGwYbHoS7C8sYIpS1EsxgqsJBZzOawMayN73cvyldRmYRmyJw4+8HmpLbHJ9Vun/Kblum+KxbwL2zZWhWXI/lx/zklqB2LxrAR2IhZ7TFjm+GzLicXaCOuBcTljvob1sUlbD7DJ2ByS/J5807/9NK47x0m/Lop94RPPuGtcdxNXJnupXKMKleVlMsbmxDbXH/6D1JZN3IYYz5FVE3dA9nJY3MfBTqgOM9KezX9Dvya73u9u/MHUsjCO42uUI3sF7PxzlI9csJPslU0fOc0vtW5YG9kHXnrzG6Q2SHGzEjcsFuMWljdWEIs1DlYUi+/NwEpicS8DK4vF71PCKmLRX2DTppyzYrHXgM2Lxd/OYItiMcZgy2SvhsX1g62KRZ+HrYu9+XZfuU1qm2KxFsO2xb52k5tspFYVi+f6sD2xuJeB1cheA4vnZ7BDsbhnhtXZ5NqeiMXfemDNf2+0+P4ZrFWM+3wbmaaZNZZjk2vUKRbPoWHdYvFcA9YrFntvWL+xQWPDppx5E1cwVjRWMvmVjVWMTZv2nDVlmReL5z2wRTYZR8smzVU2GbfrbDJnbZr8tk3dq8b2yF4r825N7Mnj85XUDo3VjZ2IxTMPWPM/Gi2+owtrhWXI3t2/+7zUznGcXKMOsQt//jPvTK3LWA+bzMl9bDLPD7DJ+jAkdZh+5z2vFGNF4mLfCitK3OOHf3P/1CY5TuaCKTbpgzNs0ifmTNyCsSU2GWMrJm6NTfr1hrEtNllTd0zcrrF9k+aBiTsSi+dSsGOTZnJy9nhoIdM0M2yyNraT6Xg4RzYn/aWD7HWwuGeGdbFJ3Xtgaf98Pex48rIXTm1Q7HJLb/1caqOUJozewUJ92KSc42zSzybYpF9PGpti07FibM7YgslviU3ac4VN+suaidtgk7Vjy6S5Y8q5S/YGuQ77bBJ3wCZr3BGbtNmxyS/559n5tZBpfhk=
*/