// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2019.
// Modifications copyright (c) 2013-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_AREAL_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_AREAL_AREAL_HPP

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/detail/for_each_range.hpp>
#include <boost/geometry/algorithms/detail/point_on_border.hpp>

#include <boost/geometry/algorithms/detail/disjoint/linear_linear.hpp>
#include <boost/geometry/algorithms/detail/disjoint/segment_box.hpp>

#include <boost/geometry/iterators/segment_iterator.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{

template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool point_on_border_covered_by(Geometry1 const& geometry1,
                                       Geometry2 const& geometry2,
                                       Strategy const& strategy)
{
    typename geometry::point_type<Geometry1>::type pt;
    return geometry::point_on_border(pt, geometry1)
        && geometry::covered_by(pt, geometry2, strategy);
}

/*!
\tparam Strategy point_in_geometry strategy
*/
template<typename Geometry, typename Strategy>
struct check_each_ring_for_within
{
    bool not_disjoint;
    Geometry const& m_geometry;
    Strategy const& m_strategy;

    inline check_each_ring_for_within(Geometry const& g,
                                      Strategy const& strategy)
        : not_disjoint(false)
        , m_geometry(g)
        , m_strategy(strategy)
    {}

    template <typename Range>
    inline void apply(Range const& range)
    {
        not_disjoint = not_disjoint
                    || point_on_border_covered_by(range, m_geometry, m_strategy);
    }
};


/*!
\tparam Strategy point_in_geometry strategy
*/
template <typename FirstGeometry, typename SecondGeometry, typename Strategy>
inline bool rings_containing(FirstGeometry const& geometry1,
                             SecondGeometry const& geometry2,
                             Strategy const& strategy)
{
    check_each_ring_for_within
        <
            FirstGeometry, Strategy
        > checker(geometry1, strategy);
    geometry::detail::for_each_range(geometry2, checker);
    return checker.not_disjoint;
}



template <typename Geometry1, typename Geometry2>
struct areal_areal
{
    /*!
    \tparam Strategy relate (segments intersection) strategy
    */
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        if ( ! disjoint_linear<Geometry1, Geometry2>::apply(geometry1, geometry2, strategy) )
        {
            return false;
        }

        // If there is no intersection of segments, they might located
        // inside each other

        // We check that using a point on the border (external boundary),
        // and see if that is contained in the other geometry. And vice versa.

        if ( rings_containing(geometry1, geometry2,
                              strategy.template get_point_in_geometry_strategy<Geometry2, Geometry1>())
          || rings_containing(geometry2, geometry1,
                              strategy.template get_point_in_geometry_strategy<Geometry1, Geometry2>()) )
        {
            return false;
        }

        return true;
    }
};


template <typename Areal, typename Box>
struct areal_box
{
    /*!
    \tparam Strategy relate (segments intersection) strategy
    */
    template <typename Strategy>
    static inline bool apply(Areal const& areal,
                             Box const& box,
                             Strategy const& strategy)
    {
        if ( ! for_each_segment(geometry::segments_begin(areal),
                                geometry::segments_end(areal),
                                box,
                                strategy.get_disjoint_segment_box_strategy()) )
        {
            return false;
        }

        // If there is no intersection of any segment and box,
        // the box might be located inside areal geometry

        if ( point_on_border_covered_by(box, areal,
                strategy.template get_point_in_geometry_strategy<Box, Areal>()) )
        {
            return false;
        }

        return true;
    }

private:
    template <typename SegIter, typename Strategy>
    static inline bool for_each_segment(SegIter first,
                                        SegIter last,
                                        Box const& box,
                                        Strategy const& strategy)
    {
        for ( ; first != last ; ++first)
        {
            if (! disjoint_segment_box::apply(*first, box, strategy))
            {
                return false;
            }
        }
        return true;
    }
};


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Areal1, typename Areal2>
struct disjoint<Areal1, Areal2, 2, areal_tag, areal_tag, false>
    : detail::disjoint::areal_areal<Areal1, Areal2>
{};


template <typename Areal, typename Box>
struct disjoint<Areal, Box, 2, areal_tag, box_tag, false>
    : detail::disjoint::areal_box<Areal, Box>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_AREAL_AREAL_HPP

/* areal_areal.hpp
Zk9p3Ocqd1ZSm+JvA8cPMLE95llOP6/8id6cjcp+wd/QOfs9AnQGF2m/FQTn/yvx/1z6f7jM2a/jr+13HqWhDG23RCd2a+8elnSVvt8bsBqvUEiqe7KWeqkRpH1deCPYIlfMs8LjmVWOik/vQmwY+ivCRxDaDvI0KBxZsMBbHNzdBCd8NjsYOKDcWvftcDw5Ooo7rQDbQneKMdcROroEOPF1964V6LvkhIbtIFo/uBJzimF7XEB9+EjWHf6d/zjb44uWYh8zvisd7cqiq++yOcT9GeZ8RypOIKT5ew+5Gk/ONR0jMrq7hzLpxL5kPuZGoljeiWRgfM8UfEYL1WmEbqeb8E9RxSb9U9yx3HhyjPWbpv5fhnNcT6ByZG9PglaHZ0yRt9n3ADOn9/XSLPOngj6pjHmUQNi64Lc0FZ3d57EV8lZtZA+S4yL9ADBd40Pz+MIk/5+Hi5qCgP3STSJP6wB98OedXx0SRyYYf312QPGjBBvc2t8/QIdWCOr8LcMGOrf0DXUOEpTPvSHGQfAtW3toVwGB/PxVDOvtG6TL0foGAFvqw4Yc376BIWLr4C2u/L72s1HOAU73tNKXun5vJenhSOihmvRAW7EIyRf3dvr1VgCuZ/i+QA5gFL+nVrh0naQrXXq1F+zBmefSa7zl2F+xcGPo2+SmrXhwwP1FhUV/W0ZD7KVjhDHalrAnhsePXM5oHPFiH8p1PE7KVD6U6jSfdhIcTzjyGGPJXYWsn987SDI4u65R+coOUwbuy3X45jDm9vhchrrFhvpj7a09PW2t7WeT9WzrHqAv89tWNzVJt2CvfEYB++YMsKVEdrfmUvfE2b1AF1X59zEEe5d3O//ezoHgwuSmbKaA/R4XOx+v4e20fTmRaqflyjAdA4cPwj15AxSpojPmKON5zte3jlCvieMAqfj0FxGulvZypLlXOqxwdDH3E0jntq4oy+EasEfwnCqi84K8/dkkX2u3v7g/oAX7Bbgtj6ad50tUW24upXvXlqUV+1ri5doP/2bZjhaSw25LA2yZRVPz+VVpa9njxXo8keprOUOPhGPaHNsjpWoqT6J0xczrMWt7JL25Nc1lVYHOZlXef0Vv0fe4iMOnc697I3u5xVpfc8oUvmZZhK/pha85Vfua/0COnd605xc3ddPpzla7QXRqEvmusXzjlPdv0ZaQoW5/yyP+hg9cgXw3wV6fQmm1X8qdZoM/If/kbprAHjbsnfVhPfQZLa99Tw3fd+Ff8jGUHPaUT+pKUug+dM/JUu0LQUd+KjucpKBcluLMiSwuqvH5PJVkrPXo7PIYnUPDvvDTVTs1lKhv+F2PCwuZPPGTfc1ZupmjeO/z04WfP5cbTe7BvAx/E7/datyQs46DnW6jIW4NsH1kSzI3Ih3VwlsiWfhzrNPL9PlEOr6Lb6Er4U9sEURLOJad02p/Vul7neROn4H43lD7LCzeEwSU2h+tcIkUfTEwdw8tKeL5dHHabaZW91gslXtFdPZHBH+K4HX2osynRtwz1IWx5RmqDVeY9jF3PUSqvT7kw/vH9+f4umF9RsHclcXqIzjZBe8BqFzF/vu/bBfLQ/22N7EPNk3cqO2L+z53wq5X63ne4+R/gn61QPcrpOehX61E+WvD5ad0x0LC8Swnnu5MMeU5U/tgrH3GaHEVS/iXBcfShVRqMp8Fn9IE4C37N1TspQyxl2a3fwN3YBTXIv76MEZtIksQC3ftEX0/1WHYHvvmdfDNsu5U8dgNhON9NG79yWejOY143cUn0B7LKn1PXbnXQnjmQ2xCsb22jY7e0a7f6NO2g3Yt4oCQRf5ereCsRS3XZshVi9bqBq9TkSf6TH3Ufnw6r4/6M78=
*/