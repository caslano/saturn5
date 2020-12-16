// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2018.
// Modifications copyright (c) 2013-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_POINT_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_POINT_GEOMETRY_HPP

#include <boost/geometry/algorithms/detail/within/point_in_geometry.hpp>
//#include <boost/geometry/algorithms/within.hpp>
//#include <boost/geometry/algorithms/covered_by.hpp>

#include <boost/geometry/algorithms/detail/relate/result.hpp>
#include <boost/geometry/algorithms/detail/relate/topology_check.hpp>

#include <boost/geometry/util/condition.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

// non-point geometry
template <typename Point, typename Geometry, bool Transpose = false>
struct point_geometry
{
    // TODO: interrupt only if the topology check is complex

    static const bool interruption_enabled = true;

    template <typename Result, typename Strategy>
    static inline void apply(Point const& point, Geometry const& geometry, Result & result, Strategy const& strategy)
    {
        int pig = detail::within::point_in_geometry(point, geometry, strategy);

        if ( pig > 0 ) // within
        {
            relate::set<interior, interior, '0', Transpose>(result);
        }
        else if ( pig == 0 )
        {
            relate::set<interior, boundary, '0', Transpose>(result);
        }
        else // pig < 0 - not within
        {
            relate::set<interior, exterior, '0', Transpose>(result);
        }

        relate::set<exterior, exterior, result_dimension<Point>::value, Transpose>(result);

        if ( BOOST_GEOMETRY_CONDITION(result.interrupt) )
            return;

        typedef detail::relate::topology_check
            <
                Geometry,
                typename Strategy::equals_point_point_strategy_type
            > tc_t;
        if ( relate::may_update<exterior, interior, tc_t::interior, Transpose>(result)
          || relate::may_update<exterior, boundary, tc_t::boundary, Transpose>(result) )
        {
            // the point is on the boundary
            if ( pig == 0 )
            {
                // NOTE: even for MLs, if there is at least one boundary point,
                // somewhere there must be another one
                relate::set<exterior, interior, tc_t::interior, Transpose>(result);
                relate::set<exterior, boundary, tc_t::boundary, Transpose>(result);
            }
            else
            {
                // check if there is a boundary in Geometry
                tc_t tc(geometry);
                if ( tc.has_interior() )
                    relate::set<exterior, interior, tc_t::interior, Transpose>(result);
                if ( tc.has_boundary() )
                    relate::set<exterior, boundary, tc_t::boundary, Transpose>(result);
            }
        }
    }
};

// transposed result of point_geometry
template <typename Geometry, typename Point>
struct geometry_point
{
    // TODO: interrupt only if the topology check is complex

    static const bool interruption_enabled = true;

    template <typename Result, typename Strategy>
    static inline void apply(Geometry const& geometry, Point const& point, Result & result, Strategy const& strategy)
    {
        point_geometry<Point, Geometry, true>::apply(point, geometry, result, strategy);
    }
};

// TODO: rewrite the folowing:

//// NOTE: Those tests should be consistent with within(Point, Box) and covered_by(Point, Box)
//// There is no EPS used in those functions, values are compared using < or <=
//// so comparing MIN and MAX in the same way should be fine
//
//template <typename Box, std::size_t I = 0, std::size_t D = geometry::dimension<Box>::value>
//struct box_has_interior
//{
//    static inline bool apply(Box const& box)
//    {
//        return geometry::get<min_corner, I>(box) < geometry::get<max_corner, I>(box)
//            && box_has_interior<Box, I + 1, D>::apply(box);
//    }
//};
//
//template <typename Box, std::size_t D>
//struct box_has_interior<Box, D, D>
//{
//    static inline bool apply(Box const&) { return true; }
//};
//
//// NOTE: especially important here (see the NOTE above).
//
//template <typename Box, std::size_t I = 0, std::size_t D = geometry::dimension<Box>::value>
//struct box_has_equal_min_max
//{
//    static inline bool apply(Box const& box)
//    {
//        return geometry::get<min_corner, I>(box) == geometry::get<max_corner, I>(box)
//            && box_has_equal_min_max<Box, I + 1, D>::apply(box);
//    }
//};
//
//template <typename Box, std::size_t D>
//struct box_has_equal_min_max<Box, D, D>
//{
//    static inline bool apply(Box const&) { return true; }
//};
//
//template <typename Point, typename Box>
//struct point_box
//{
//    static inline result apply(Point const& point, Box const& box)
//    {
//        result res;
//
//        if ( geometry::within(point, box) ) // this also means that the box has interior
//        {
//            return result("0FFFFFTTT");
//        }
//        else if ( geometry::covered_by(point, box) ) // point is on the boundary
//        {
//            //if ( box_has_interior<Box>::apply(box) )
//            //{
//            //    return result("F0FFFFTTT");
//            //}
//            //else if ( box_has_equal_min_max<Box>::apply(box) ) // no boundary outside point
//            //{
//            //    return result("F0FFFFFFT");
//            //}
//            //else // no interior outside point
//            //{
//            //    return result("F0FFFFFTT");
//            //}
//            return result("F0FFFF**T");
//        }
//        else 
//        {
//            /*if ( box_has_interior<Box>::apply(box) )
//            {
//                return result("FF0FFFTTT");
//            }
//            else
//            {
//                return result("FF0FFFFTT");
//            }*/
//            return result("FF0FFF*TT");
//        }
//
//        return res;
//    }
//};
//
//template <typename Box, typename Point>
//struct box_point
//{
//    static inline result apply(Box const& box, Point const& point)
//    {
//        if ( geometry::within(point, box) )
//            return result("0FTFFTFFT");
//        else if ( geometry::covered_by(point, box) )
//            return result("FF*0F*FFT");
//        else 
//            return result("FF*FFT0FT");
//    }
//};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_POINT_GEOMETRY_HPP

/* point_geometry.hpp
e8qMv3yu4Sl/l+YgkcfmKhJ53CeWLGqMsKjHV3FKiRXN9uUvKA92wf/MUG/8+0Pp7F3NpbKPkzYQWTlD/RrCbpdFxBJKVXhihefqRXyKS6OY3cpJTvTHJF9kwUxSoyHDYLeadKvVP4m9zH7h09NU1/DqdewdQS+IWByQXEoNn5OJHqSKGtzj2DUyLSI29g12uH1d0eEo+tS47y/oISci0zgVTDCViYaQHISnF6lekozAZSnGcHQ6U5ButkB7LeHuDuQvmB/KNiqAzRRo+i4iahyFDrH5DDKCoZsEecCC+UBYoseME9BMDH40YfLxRdYJEiXJVm3ce7oEEnM8ZrXOrM9gX9ays1SUp4sakE2XaIpEiDLgBFh/q54vZgYS7WInYLc4rDzzBW17aPLe8JtE40hyhMaJ+uF3wmadPdMlToXziXF5s+awDcehxlETW2NmKfhmbmU7JzHb5pkyhn2rsJxxktPpfmk9Iq3HpfV0vIiok9USS46z3fQaTG4okkS4KEKSmPzO1WQNdAqWoX+BMi4k+ByeaolRIFvIZ0I2Z0O3aegqxl0OxIzriiiXyGvBqc1d0C1DvRHSSeELrUa4XxBroQVjk2fzFHAdRD6xs/aBWC+uNs5M0Q5YbJzovey1GF822RSz4zK6gFrS8m/6H/2p9/+pSt/szICO98t0KBhuOSrY0y9EXqxgQ0vSgHPmM6gmI3E3UKI3BlMkbT76oXCMntT69aZ98z47bao5ZTZ4s5xKTHe0rFleYhjjDI0sRW6TUlup87TRcH+5/vspdvqGxT9LcsTzh8gaWYQqBaSvxViXm7iYbRNXzRkXm2HJp+KXG7ggtnLcbIkdXPk0sTk7v0xszm7xAV30+C+mmDs4n4h9vFjE/nKCiH0Dnw31TPH7MX1ygMTX78kdRrAn/8aLTdnhJGK+lyDTytDLsTvizq1M7EM+IziB9shJoaEIgue5zxJzoaP9kO3my581R+5ErsEBACSV9lYvYoRq+Ngp85uHIAit3n4PmGzcUCz2fuOBBGfLq5CxS8wAZS5bSV81SxosRSlDp/oiswJNPTDlo4bbbxNnWdvEV8X+UG9EytBhQK3FUTe9iJ2VlArYjTuwJEvxUYDbIO6KyhK5GiCB5t+AlvmbnocT9F9PjnPtrCcHe77XPReCorpzkdOScSeqFci6HLbA/S3V5Hckr8ZfsP5yUVKtuz97PRmi5Kmvw/ThK90OcrVpuJmQ49MH3uaY5o+VuDs4J4pv6AlwsFTLatC0wDCvAO1wPPdlTbw1SdSEJx0KW7d6uncZfL7n8tfc55d4Fm6kQDhsipMGl8Q2elEESPIDpWNB49zsEr024KoLZG8MRJIGUzSO25OeNBi0hk6VN0b2JHJv9EXmwtr01T9ZnlJbeV5LLE9JeJ9z7iRRoHATdRe4YQoha7GW0gHTULSNX1I013comtUezrnZbA9mjSx9kVT6WAiBuTitji0U1mC87kOs+K/A50Klzy1QTQxhkelIL31+jTkUpzXKTBAgS+9N2xhJLQk7IUlyvLuVWXwZ/qSA/jqzmBzPom9iFum2LMqoC8KbttUb6SmzlNIn0571RtKQZRKzPIgsv16V+fU60SVz/WvjA7VuXlLuxmaP0OmQulYO1vEkf+uKKSkwrNBt3YJ0PB4kxx4LJyEjqRYgMxODyzYE6tvrP5molqb1At7krFVDv7OrY3FUVvsHdA5gVYR0VlckXdaVZtWVu/7L2vtZ7AviKNxoAbSn7kDtU7QmK787vGxvC2FK/Ze0L6S0bkzA1xf4VK8UPUp0yhJb+27xRnqUtGnf1K9uU9GYng5mXVXdqi07RmTJ6+p4Pp4+QbUK+YCpbVw=
*/