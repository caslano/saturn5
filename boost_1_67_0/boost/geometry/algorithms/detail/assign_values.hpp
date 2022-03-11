// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_ASSIGN_VALUES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_ASSIGN_VALUES_HPP


#include <cstddef>

#include <boost/concept/requires.hpp>
#include <boost/concept_check.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>


#include <boost/geometry/util/is_inverse_spheroidal_coordinates.hpp>
#include <boost/geometry/util/for_each_coordinate.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace assign
{


template <std::size_t Index, std::size_t Dimension, std::size_t DimensionCount>
struct initialize
{
    template <typename Box>
    static inline void apply(Box& box, typename coordinate_type<Box>::type const& value)
    {
        geometry::set<Index, Dimension>(box, value);
        initialize<Index, Dimension + 1, DimensionCount>::apply(box, value);
    }
};


template <std::size_t Index, std::size_t DimensionCount>
struct initialize<Index, DimensionCount, DimensionCount>
{
    template <typename Box>
    static inline void apply(Box&, typename coordinate_type<Box>::type const&)
    {}
};


struct assign_zero_point
{
    template <typename Point>
    static inline void apply(Point& point)
    {
        geometry::assign_value(point, 0);
    }
};


struct assign_inverse_box_or_segment
{

    template <typename BoxOrSegment>
    static inline void apply(BoxOrSegment& geometry)
    {
        typedef typename point_type<BoxOrSegment>::type point_type;
        typedef typename coordinate_type<point_type>::type bound_type;

        initialize<0, 0, dimension<BoxOrSegment>::type::value>::apply(
            geometry, geometry::bounds<bound_type>::highest()
        );
        initialize<1, 0, dimension<BoxOrSegment>::type::value>::apply(
            geometry, geometry::bounds<bound_type>::lowest()
        );
    }

};


struct assign_zero_box_or_segment
{
    template <typename BoxOrSegment>
    static inline void apply(BoxOrSegment& geometry)
    {
        typedef typename coordinate_type<BoxOrSegment>::type coordinate_type;

        initialize<0, 0, dimension<BoxOrSegment>::type::value>::apply(
            geometry, coordinate_type()
        );
        initialize<1, 0, dimension<BoxOrSegment>::type::value>::apply(
            geometry, coordinate_type()
        );
    }
};


template
<
    std::size_t Corner1, std::size_t Corner2,
    typename Box, typename Point
>
inline void assign_box_2d_corner(Box const& box, Point& point)
{
    // Be sure both are 2-Dimensional
    assert_dimension<Box, 2>();
    assert_dimension<Point, 2>();

    // Copy coordinates
    typedef typename coordinate_type<Point>::type coordinate_type;

    geometry::set<0>(point, boost::numeric_cast<coordinate_type>(get<Corner1, 0>(box)));
    geometry::set<1>(point, boost::numeric_cast<coordinate_type>(get<Corner2, 1>(box)));
}



template
<
    typename Geometry, typename Point,
    std::size_t Index,
    std::size_t Dimension, std::size_t DimensionCount
>
struct assign_point_to_index
{

    static inline void apply(Point const& point, Geometry& geometry)
    {
        geometry::set<Index, Dimension>(geometry, boost::numeric_cast
            <
                typename coordinate_type<Geometry>::type
            >(geometry::get<Dimension>(point)));

        assign_point_to_index
            <
                Geometry, Point, Index, Dimension + 1, DimensionCount
            >::apply(point, geometry);
    }
};

template
<
    typename Geometry, typename Point,
    std::size_t Index,
    std::size_t DimensionCount
>
struct assign_point_to_index
    <
        Geometry, Point,
        Index,
        DimensionCount, DimensionCount
    >
{
    static inline void apply(Point const& , Geometry& )
    {
    }
};


template
<
    typename Geometry, typename Point,
    std::size_t Index,
    std::size_t Dimension, std::size_t DimensionCount
>
struct assign_point_from_index
{

    static inline void apply(Geometry const& geometry, Point& point)
    {
        geometry::set<Dimension>( point, boost::numeric_cast
            <
                typename coordinate_type<Point>::type
            >(geometry::get<Index, Dimension>(geometry)));

        assign_point_from_index
            <
                Geometry, Point, Index, Dimension + 1, DimensionCount
            >::apply(geometry, point);
    }
};

template
<
    typename Geometry, typename Point,
    std::size_t Index,
    std::size_t DimensionCount
>
struct assign_point_from_index
    <
        Geometry, Point,
        Index,
        DimensionCount, DimensionCount
    >
{
    static inline void apply(Geometry const&, Point&)
    {
    }
};


template <typename Geometry>
struct assign_2d_box_or_segment
{
    typedef typename coordinate_type<Geometry>::type coordinate_type;

    // Here we assign 4 coordinates to a box of segment
    // -> Most logical is: x1,y1,x2,y2
    // In case the user reverses x1/x2 or y1/y2, for a box, we could reverse them (THAT IS NOT IMPLEMENTED)

    template <typename Type>
    static inline void apply(Geometry& geometry,
                Type const& x1, Type const& y1, Type const& x2, Type const& y2)
    {
        geometry::set<0, 0>(geometry, boost::numeric_cast<coordinate_type>(x1));
        geometry::set<0, 1>(geometry, boost::numeric_cast<coordinate_type>(y1));
        geometry::set<1, 0>(geometry, boost::numeric_cast<coordinate_type>(x2));
        geometry::set<1, 1>(geometry, boost::numeric_cast<coordinate_type>(y2));
    }
};


}} // namespace detail::assign
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename GeometryTag, typename Geometry, std::size_t DimensionCount>
struct assign
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_OR_NOT_YET_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};

template <typename Point>
struct assign<point_tag, Point, 2>
{
    typedef typename coordinate_type<Point>::type coordinate_type;

    template <typename T>
    static inline void apply(Point& point, T const& c1, T const& c2)
    {
        set<0>(point, boost::numeric_cast<coordinate_type>(c1));
        set<1>(point, boost::numeric_cast<coordinate_type>(c2));
    }
};

template <typename Point>
struct assign<point_tag, Point, 3>
{
    typedef typename coordinate_type<Point>::type coordinate_type;

    template <typename T>
    static inline void apply(Point& point, T const& c1, T const& c2, T const& c3)
    {
        set<0>(point, boost::numeric_cast<coordinate_type>(c1));
        set<1>(point, boost::numeric_cast<coordinate_type>(c2));
        set<2>(point, boost::numeric_cast<coordinate_type>(c3));
    }
};

template <typename Box>
struct assign<box_tag, Box, 2>
    : detail::assign::assign_2d_box_or_segment<Box>
{};

template <typename Segment>
struct assign<segment_tag, Segment, 2>
    : detail::assign::assign_2d_box_or_segment<Segment>
{};



template <typename GeometryTag, typename Geometry>
struct assign_zero {};


template <typename Point>
struct assign_zero<point_tag, Point>
    : detail::assign::assign_zero_point
{};

template <typename Box>
struct assign_zero<box_tag, Box>
    : detail::assign::assign_zero_box_or_segment
{};

template <typename Segment>
struct assign_zero<segment_tag, Segment>
    : detail::assign::assign_zero_box_or_segment
{};


template <typename GeometryTag, typename Geometry>
struct assign_inverse {};

template <typename Box>
struct assign_inverse<box_tag, Box>
    : detail::assign::assign_inverse_box_or_segment
{};

template <typename Segment>
struct assign_inverse<segment_tag, Segment>
    : detail::assign::assign_inverse_box_or_segment
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_ASSIGN_VALUES_HPP

/* assign_values.hpp
21oEm0K6jTnREr+bwfR02hWdVvzLgceG/DKnPnk84OkMpJv9ID4yJVtXox8SUmQ50x9iDsFbfcViLK0VwI0uHXeN1d1OAaOgfHqto/S01uZ7tU1pNII0iyol6aohDfACBucH8J3uEbPwbLU98xix/JmnlCIJqZMLcVrPo9MUvgNHt5RKDe2+HG04T5E2PUT4ht5Z2eg2K6jJpxnmYpQLJQOtXPvC88I+xvfkvR2vIj3klWO8EHASdsucpBtJIsLFAFjzW9hoWzfXHa/MH4Hz29+a+Qit9Qy4uEQTdPYc0qignH6Auf0psmSXRy7X3AVvHIxZ0QYWCyMpkEYxH72LGGph7okZTohvgKdbWN9qyDvwfqIxq66dg9JE8Q/OnidCaO4VlvfuhODFk72iJbSEDbikLiE5H09ypikohJQu+QqIlYUH9YhN6Qfhmm/oX4epSt8puq/qL7Qc4+q3lXSQufdsOazU1IZiHjT9YxaWr52rMbeeadWXr7Z+wj+hUPhbf/jl3mTy4h6oxdSb7p+2Lv3B0/hKn6eeOlbLFESga2ElJwQYC3M9OEQvtsC0BbJaYHTBsgIkbiopzMezOpwh8dGdFuqqn7AYkBCnIWCiO+vE3kbu8pXD8fB35nuM5NwXwSenvP4hFv+SnWI1VR5LNrIstaj8TjwbabwNhNu3Uh7DfEvvFHUFzUCzwIE06kbZLFQgG9mVkPqSwqRhdD4/X4cWap7qObJ8YSxVc73YLa/zEIV6Oj5H32ajg4YoawOvZtVsdY0qNno0hbimI8qt3B7C+vZGxwrKfeOCLo3f4ZeXI026HdzemNP+e5grbTA/vdRxJEiHlIG6GnZ79AiUSBP4NDXqoOe7ch3OEx47EPuyukvMDos5JNjbDAylWW7UvYKtXQVql0EwYwGGxpv8b/Qghl7cGJjApl84zT7sLu2ugtjLImpY1kOpfnZUPOk5mBI3LmOmBnKjuAPduRoo6yMtv8prZvj+ViuJQpzj0qOmZXBqI4lAsxnJtjkQsIPvuWLS9HnAHYLGvv1CJzgxupQFJblksbRRo5iQPCsLyV4WJBkThM7YBLLs335ZdwSK5qdxoJqj028v8TmpbGTv3IypADTPjI4JolU3fMs3tNALp/YRlmwDNyT2Z+63vDu6430oR9Fc+s4RemgrlKwj3v87aDHuX3Pn4N1NlqNax4w7l1DW/l2efgXeZCmPKYJjyT4xQxzmajm8FmKANrwTaF1pbhfchdt1QnQD3gcse2C/wueTgH6Pfaqyo0h1cNivZXQ5Dyny16EcfObguvGy/VB/hAh480p71tB3Wv7isQHc6Xw0PKWvPqamErXt6NXGWaT0Mg0nKrv7khooW7xOslGO4GWVBXGF2ebAq/zhBKIPyHBY2GuomB9vIDeRfDZlxAhsUfc3EQLBV6RUdrwJ5v1lk2Wdc/Jso0EHVLtOrxrcDJeBRWYsH6dF/wS7X9J34ce37FvOULxoHEIOm342zHOavlqiKWTKs6tqIFyrwWvdjKRTPusfthUNDdqmShebgVv9WxFC54WgYjh0UtNHae00jMFWfKiA1+RYDq8IUBCzArKWSbkCxlsUSu2RLA+ipsSzfY7p9JfTrqDuEG5SIlUqJZWqJ+RDRtrcYckNnTvFsioZnqypvzn+pRsprCnKKvowUBsyvewcibzgI7lUHXRGGXRiNG6l3FEwJQf4/3zUoFgY4Kp90hnvgOjZ+l7SmI7s0fZiZ0M16d9BtPVSZxt5QgsD5/tQ0VpQ9z2cNTrz4QS0DiTb4BmUOZNbIIfhbX+7l+elYDZr6rvUIYpKgvL2S+JEZmKpCGtZHQ8c0MxBKlyHy189FMglgwU3Nxc3Ve17UQYYebHhlyyuqFdR4FRmSDjAb/D89YLITV0Zmfg7UFEA2mSGD47PK5Kb+uILEEDhA19JTsMlcHciqJZBQsTRk6OIv3eWFdQ8MS57Rhielzd4hrDwaudF+oRwhB+mlx9lN3wABiz50yhh6sJbJUWRitao2qANVoQifY+lMoIOVIdq+y1JYZ4NeQGKPlgfnJ8UkBDM3znjo4rsU5LdvCZQweXKiOU5ZICtb7tONYo6YN6/qnrLXsckGZsTSdG0yvPYFhSDE9RE+KHbnL9Kk+OUrjIBdcxcCCV7kw9xQp7CFfXrMewv+xxhUTXZhirddVbw6fplOOCXoPjFF/GUm+le+Gea13Q6FL0rrpUnNNHVOUTyB/F+aL3fhbPhrd8RH9a7sAjUE9ViHGUcOP4qlcbAFBI6ONtxEcGzu+jCtRjLbrmX8IrFpDUxqi8ApHOedOCvDdyhPLcfp1Xrrt3A06omEgJ5RZQUm+YwQ8bfHpen4+32LOYeh6FnIHVCU2YEko/m8Wumy4ksuWq2bsfbkAjzxFzhHaKPt9hnPNuqE4gNKQPT9qx0pJbixx65aR+tjRfoakLhav6JASpNJlwW+enSZBoX6xv82ktlFL9WjOr9idEMXZOOGfSPdxEJo+i8UIHXvSTe4WSw1n/cbWwl1QAIs7UTmDPmLYlyPW1FVSNxA2r5jaYD7KQFsgqtvSLwiUAvH8/SAQ57u6oV3T3trJEOYhcfzuX0XVi3b9DqcAwhI4RWGLMG+O7h+aChP2osDQri2HnP8ggH6dT4gpvB0lUkUjjxYr8MxyLRrkbufEc5gVZecHLXf/Eu1G2SyLjr2bEcFku761n+rKIwrlFuWQ99aFQFnQZDHmuDdo5gzvS2T/T2PoumwoGn2MjPK2YIctA9YDHksWUtg01xG885WDqb01hmqBzFGh/Yjz2XNCtt48vFFHOJgMbSPqOnGZRyfYMV4Nl+rWyhu1Jj7/BjxXzm/g2wpguhc3JwGoJxRJn644ssaXODeEgCphiTJF4pGI87Sn9DXMzBgK01Gbca6b5jKVoRT48opnZn83jGvkXP1FbfEtVsypZDJYgZYBoFziNFnKXYJzGEZqwKVPxgA5enKmGGANyuLJ2rEcuPplCLfhHFCsFjOxQYpsKOZ0o6x2+0LzlOilJyrX1uPsTPzXL/proRq9zD0p4aBfm3gFU7fEfmdSc6QY/emP5zMtQwt2yilihjXJAhnxsat2xVSuQRs0uXMt8dr4lopkgUSxOYV11wl+Cr9SHdDpBJRP88N6+mk8x28RvqST9oiit4cxWf03Kx+k7UyLpvEFaklG1urmCAImBXlugLrSac5xR95Xf6PJG8JT0+FzPADMk/h56vMBQt+YgWGYI7Whyk3DivXNxcrP78oSgEpBi4Hn9QjBz+RI6IaIwgC5tpQYQY/94EgL1wWU4C9Y0fBR1EFlmqY2F0hl8MVIRUKlP/pGK32ykhxVc2FUnLQwzRewyf4kRKxze4kDgFL5aAUVD/RpjPT87szGfo4LOfidE5o3aw0U0RlcANnmCrOA8wJKrkFQiXwCMdnc4mS20X7Rzn/vzwNj7YL0hEUkI8GTMRCB+XuM6BLeKhtB4MJSadTRklIXXnjI/5haax3nA7Hh7uqLFn+NY1dMj+FlokBIe0EPr4VFBDkFO02oRLmqOr7EieLKGzOAZ3RluIGa8JuQv30kRIg59vZ/Jauk7xsI94PFE+mpZYElduVszGwWpqYCj4R3SqjmkoS4IsKA0HDReJCjo2M5O/mTITHVncFOI9jvTcARmCOIhcSF80uqZPPo0AHt4Er8Y8VwNx/6W9deHhHDo1/4a2+mvYoZXSeL5whcGtV+PlKKA+sZDT9Sd1cnvbdo/tAao3y8iejBKcVKXpQVB0cS88G9JM9Y99+Dbdv1zDXHsxWYqB5hGCtYV02ppX3p8/mazrjxiiYoX9uviY+rRVbneZusOjvvV86PA7zT+4C8jq0pNFFaudcGcg4uNhshKaP7ivBtC94makLRf6zbxiHTIZGottR8aflTbiDQF8jq8/q5Y+y/5FlMmUO923lKYZ4/l8LCNpDP+efJo/Ade5gzp7u1VeY/0O/9cy7UTq496GX+pr2ZcTFd4OmWAkZJXyUp3BbXYYcxcNogYrMeYtttHRSUKtlRYng102045CW1RSqu/3LsX4abYQcT6zQ2totCBfITetHy4sR0y4+CJQw5/Vkyj9TTzt7Sm1UNh2uD2TqKqJFrt5e/yxc/j94T1JT2QZ1kwkeqjZBMYd2eNnxWwBxq4J+dtuCFFR+JPASyik/JWm3sXo5phEeOGxkE/n0/JjRqL/GhBY6Ecc/cuaFFVpkjyz0VmYnigFj0IbY+XGwenI/a0n7OseKFKqQQ8Ho5MlGd3tZguuZfXAUuaFIgci8HzmiJkXzo67s9TScj92vl/vNxJc6/KNdSMd28biovFFcSUsqC0VLg97UsGW+6Ld4NjVA5UPmu4Uz/nH+Ur3M3ugTLtK7Q18aVfuR5W7ge0Z7Vu/zWZKK1obLeXDtrvWbJHBcVdJRVMfqBMvn4qrZeBL+yih03BDKZpdr4/V2wWXW1Jt7rYlE4WE5e7HVRBSDwA5sBfDY3qTfEKsjcyn5yHDjKmADVWG68iNwnEbkO4qlPNuNztLv8NmZTOe19ANPovXTsnlEHKZTtLIiiHP0U50+5w7bsfWOXK0RPz5NG4mlrG4I6trKDmfZoIcHW5oPmUtcFc6VjerI4YYMfMRU5lByJ6DnH9XMDY1R5Dzpx+jQjbhrPJbz54pnwyWxWX4gFQ6KyoykpPiq7LpZI+w/erNygOXzi/iOr3FbzDzvWh5xGsX4/b+qKng2MFU5UstO4PYhgq5MOZGfZ/xw/Pr9/rLuB44zXsv290K3bMxauehsgZerseGWbTXVXzVmIjG2SdVSJgucpMdAi/3XU/w7cd5lRmLxnyj17HWydVGIhvpxknDcBhfuaDJP7vPLfS7d43m7XYko32Za9hUZryGb9aXUazQWdLqnJ3317uyeypw1ysyRNhSNh5sWtoy2E3usfPn7j4SMIuA1/YGxdmCv6BoYhe1tlKEq4l+XN01wwf/2NYLL0twqnJSXdyiDRPJqf8F4muY615fhMQ1dBoNAxeWHfu8XLW2dVlymGq+fAjrdR71km+YRdlle8Xm88yOP5Z2WMB1RtQS+zntsFuuRH/e8zRKt4L78m5TluHxeHdP6y8rQWvQRZdgdWcPtxxqWXSk+tAj2yPHEn9K9HrnfuSvCx2PH0kM8nAXJB5so+0zOMfKap/GN+HDOvIkJCAZoYpNKnEHDJSHn8iaxOejC/nzcwdgy77vM1NM4Q4xtzmfKerAjJA6aSZYUZNnvAuLPvdW4e82e5PNmQ3loqX6tsaimyJoMpPvL15FgANoXmz9zLXuxxuDsWgTXZ9BZef9jVq0OS1P3nfIBlWjchDX0VU8bvAccqc1VTKdyDfV74b1+NQdaFptLCoO5XedGGZH5SihXbf12cwjeqwcqwuvxgTQwr7CVavBzfhsYzF1RaJS3S/TOvcBp3kKXyOlq+c0nYmc71PVS8fY6z05XlREfluFWdxG4U+VuuUJUvORaEW9ExhK8rf9h0yTs9hXHvpOd0aFAlQSD1Y5N9kzWS3nJ3I0Sjfb2hgeQ0Uzi/807mf+tqN5472zAp4k24/9hgEr55EeMm4rO01eOIV8F6dML450qSQOtHIbK3AuX/cZUvQiPq4KS2TQCngPb6JcpMpItGLUNcHsotSZnXKJYJ+8XTP0C7NO6GcSnl6AX2d3hQm9ILVMJLYG1hHezwNF1/ecqz6Ivhya365rhJvvx3N/b89TxarkYO85TTgMHD/PwYGEarou2tefhkrSNmOQmORyfGpdkg/fCodLVyt47aiipDISN/xmtpFMYhsoM3BxfU08+k4DeW1x0UT10imvmw9fB9KCDZRqtl/PjtN5KlUsWlWjUd6tfTS7tfwqBrvcMmqU6dL/1e8HRbY5nz++Pc/bLSAT4baE64y80SRfTHNzHTi2zOYNw5T4ud0yyVN7dFPxGqxfAYCw+Na7x5xX/kK2KMTrdtLV4PLVzUZ5EFjZeRpnyFH7OmzZ+nwIpcpV5+Sy9SaZbMTXE5uob49OPrOISt5IRTSEJvHscvIw0TMRWlkJxh/kzY0MdeVtPtzUnLcaABWwYQCrVYi9nxewv3/jbMW0L/1FoLf+3TcAjy2Y7u72USZH2RXbldpdz3hzI/ndl9eB2lDaEdAsb32pLx6EFHl2oOXvLSseGb0gkNcS03jLXZnmPmE4uLPuCbzoIkFwgVcsXY5pgo/xUeKt6J7yCdIrYwIoxdzWdhvoVbugm5jFnIiRcTxPLsNrdfQ318tlgNuXQqN8T4p943wY92xc9PTDUH0YnPCSYBJ6tu5ZW/M2EnrKZgLJQH7BgurecKScEfNjqVpeOZtKyPzikvIsvnSd6NbWtOQw0RHbWV+ry675vCf8NjyubYiQgeFxydd/uoUUUUBgG/d6+fD06zy+U+l9RFOVvTBcKCjet4l1gwrkTokd53kTdSd5FlmbriR8S0GUCHA4qLmoaUTJ53saa7S/R9k4IS9u3uya6MXTQeNtOI9kYbuZudPYnTfT0jWaX6BIDGklA0fj4iuEWDKI4LcZuYx3vtB3vj56MYptggCaI9dbGLUiF8no4rbAZPlNwkMgUZL6QbZW+FUELclJ/HuYZDpSJgU0NHRMcGAU7uWNzGEVGM2k+WqVflAKGZIFRQRMWTgBM270NwRTHEQ+v2HEceSt/5v4cBw9zBS4RsQ+UU1Kfk4SNdcxkYQUTyu3Qo8XugmmJXmGHCeOgtKN381NZvonzEN5ttd1+22j3+6GV233i6ZVbfPzV9q6qZG6eNG8OawH99ld3VxNyMxCFiflCXLCOGnxLDYPi5/2zCmgo/VoePoR8iqH8sPgrVil1S/D7zHFzKISGqswoOvh5nHSne47eq/Yx3IXh32m3Ha9ytcptpf7aALa2VttP0hrtpfv6JxITI+Sq6nqSsvq+arLwWcl/FKJIETWDizkcDRXRrP+NDBDrdASVvvt6pYp9zNea5O+wlnl02yHbeUq52G0fhWW4+VdOTF3XmaT3Wx08AE1Zounyit2bfBmixYP8V/m162ukUzp5atuvBZ4iy2Tj0fUqsxG1+NjXdlLx9XEWfxWx+sZExJtF2DsPpgkp3Flnmuxsy0FXG5FFdRNo+v+sKcZqNzrHdY1nVffcv+4TYEsZcZh8v105u2N4jpeq5X12dtNdbeZrgebta3z5Pyqd3WkJqY3DZmoRIk1FL6pyzhWaaqWj3aTg6n8aPrzO+1pZbswQno8f/R111hy8Z70xPhbi5EEutQiJruZ8Ntp/WJMa/7o5Zv902U8rbYjF+P+TiCDp/JqzkcHzOumoov3C/Dmhnq9m3OzSrCXuyrn03xl1DhCZqnkuBQxzgb3uAX/6Jk8KraoCXq19j5Qrv+yWFv8rY37PRJjf7MPrUvm7bfBcW6vKSq9C9q6mXv63u9Gdawn/tl1fQ7jtGmQoQeePDVFV+X1NeP9CZDa9fY5ykHgRbH5o2O5OjOhu7/ZDTCjiCxE0vN4uh+/0eWI3yEiPM5ar1oXn+bBjCl2Zk+qsx853hVEhb3wtXwZSE1tGt9lvVe9sMXKfZmRgJiI0IV/yDhLxQHAJsGcpzHbe599NfiCZJ9VigaWu23MXknxfm5fnEPm5gZy2nhVGHja7KXrXA/v8LlE8C5wObfYgnGvOJNFj8hzf387TJasiW/EdFBGrDaeEldO62BtaHPLCvW2kMXKywWqb4DpDm7Io0Ep+XVe9VUG01qBm6IMtUx9jf5KzRtrVIOREEw8zhcVMhYZJcT7Gt/EftP6GH3wglwr9SebC2JRR2gwoaxamHk4NbUyn3iaHnlnnX9CCW/d503D8vbyXzcybyUJHgF523zQSk9JznZy2VSgP7E/eVW1Ysz1I6PM2y32zgXx03OwCX6wL4Xzw/h6Sp41cn2LPsfJQPZbOFpjo+vB2r+X9HYfXqvqBEFdxrng4HioJXmDtIvi6j5daUhyKTmpWV0O9uXqmRyffHdZv76Z7qjn/H6YH1SLobQZY7LJSDx7PwhZ2+Xl4GpaNiuOVrmIRdaulGTm7bzraz+ojkWGxU3MqWcym7872eGpszW9PP7yJ8AqPfsMOGigA+Bp+jacvLAQ+AZC+3F53J3vTrZgc6uxMRDX249FoMG+pmy79tDLHXASWBxOkkkaZXV7XfOsPJn3t1hJtcJFw6x96HxkrMv6hqzL4lhr2kNmXy1hE7d+t7Wvh/KL6LsmT1cbpuVnm1vhtjzowLw3pbCHthyeQMe/mkXRPzLDWhhaagHQ2IJqp6bcmx8WcJB2ObF33iInv1y/QtPDLsiu6Upa1d1PQiFvDqN3DjjPN+mQNlt83HVDQxKovFR7V6pN1+fhQFJOZ63FV79Mtq4/hZw73mM7AU0SWM45rJ+LNiN4BBe4Xu0GCwlGd+ssdEmifBjvKi6KXKs3is/fToPrtWQoqL0Ylz1BH3ZdL8amB6MaG1SReFhOd846C6dHZ4UnqCM5ui72NtqKrrMjqRt6vIn0+4tyCzV0bz526xG5nBY1PhcPIgo6hvu73pa7vM74jtaDcVshTxdKpC/qC9ZXa7GuNx1cd+Na4A2+m8rOtnPxn52o2tu8pb1SXicYyceZG2lzoCderVOMItM00ZdXBteI3F3r/XRMqyfUlzfJd/MhDaaiRjLfW1hEnnJYSqu8tUVYnXRGY4a+4FSdSQHbfTomnbOXPXyXE4Jyvdk5TdOfeX7JJTcC30DtB/ePYcxGpaZySyfGchlB0m/r8+/ldNILsZlFfoQ8SnwIMSfzqDQZLvEe3m9H83ioqtca+m+thAUXAascYPaXfLRkqfMqu+CPpOeR4vfaNkJ80NUpwB88zNOHUuZJaOoPfsgcUYVIAF9wmN7GufRdm8DcSsTtb1avCxPHY5iuwxFd1p/BLHl8Vw9CTuz4DeVXrC9udgZb8nbvEOAx4cTCDSj2rH+J/IPdiYseEYVDCk0Ftb3ODAalnvZRk9JwnwH46nqlpNGhbDdox/9cYBb0k7sO4hRZThl2CYgNJNt/mR9Nn2YOZQ3CGcTzrGwMB/33I6sRI3/v7wLqPFx2DHOwlF9If1H6hPVR7PFvIeyB63DbWP3las2h63DsseZ+LSHDk4Bk/yXy19QHmkNqS0ueJawwPurrrsJWP7Dmm0XnjBVxRnmE5mf7yThQysB1gTD91dZBlfmnoh39W5u020Q=
*/