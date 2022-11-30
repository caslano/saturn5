// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_TRANSFORM_HPP
#define BOOST_GEOMETRY_ALGORITHMS_TRANSFORM_HPP

#include <cmath>
#include <iterator>
#include <type_traits>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/num_interior_rings.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/transform.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace transform
{

struct transform_point
{
    template <typename Point1, typename Point2, typename Strategy>
    static inline bool apply(Point1 const& p1, Point2& p2,
                Strategy const& strategy)
    {
        return strategy.apply(p1, p2);
    }
};


struct transform_box
{
    template <typename Box1, typename Box2, typename Strategy>
    static inline bool apply(Box1 const& b1, Box2& b2,
                Strategy const& strategy)
    {
        typedef typename point_type<Box1>::type point_type1;
        typedef typename point_type<Box2>::type point_type2;

        point_type1 lower_left, upper_right;
        geometry::detail::assign::assign_box_2d_corner<min_corner, min_corner>(
                    b1, lower_left);
        geometry::detail::assign::assign_box_2d_corner<max_corner, max_corner>(
                    b1, upper_right);

        point_type2 p1, p2;
        if (strategy.apply(lower_left, p1) && strategy.apply(upper_right, p2))
        {
            // Create a valid box and therefore swap if necessary
            typedef typename coordinate_type<point_type2>::type coordinate_type;
            coordinate_type x1 = geometry::get<0>(p1)
                    , y1  = geometry::get<1>(p1)
                    , x2  = geometry::get<0>(p2)
                    , y2  = geometry::get<1>(p2);

            if (x1 > x2) { std::swap(x1, x2); }
            if (y1 > y2) { std::swap(y1, y2); }

            geometry::set<min_corner, 0>(b2, x1);
            geometry::set<min_corner, 1>(b2, y1);
            geometry::set<max_corner, 0>(b2, x2);
            geometry::set<max_corner, 1>(b2, y2);

            return true;
        }
        return false;
    }
};

struct transform_box_or_segment
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& source, Geometry2& target,
                Strategy const& strategy)
    {
        typedef typename point_type<Geometry1>::type point_type1;
        typedef typename point_type<Geometry2>::type point_type2;

        point_type1 source_point[2];
        geometry::detail::assign_point_from_index<0>(source, source_point[0]);
        geometry::detail::assign_point_from_index<1>(source, source_point[1]);

        point_type2 target_point[2];
        if (strategy.apply(source_point[0], target_point[0])
            && strategy.apply(source_point[1], target_point[1]))
        {
            geometry::detail::assign_point_to_index<0>(target_point[0], target);
            geometry::detail::assign_point_to_index<1>(target_point[1], target);
            return true;
        }
        return false;
    }
};


template
<
    typename PointOut,
    typename OutputIterator,
    typename Range,
    typename Strategy
>
inline bool transform_range_out(Range const& range,
    OutputIterator out, Strategy const& strategy)
{
    PointOut point_out;
    for(typename boost::range_iterator<Range const>::type
        it = boost::begin(range);
        it != boost::end(range);
        ++it)
    {
        if (! transform_point::apply(*it, point_out, strategy))
        {
            return false;
        }
        *out++ = point_out;
    }
    return true;
}


struct transform_polygon
{
    template <typename Polygon1, typename Polygon2, typename Strategy>
    static inline bool apply(Polygon1 const& poly1, Polygon2& poly2,
                Strategy const& strategy)
    {
        typedef typename point_type<Polygon2>::type point2_type;

        geometry::clear(poly2);

        if (!transform_range_out<point2_type>(geometry::exterior_ring(poly1),
                    range::back_inserter(geometry::exterior_ring(poly2)), strategy))
        {
            return false;
        }

        // Note: here a resizeable container is assumed.
        traits::resize
            <
                typename std::remove_reference
                <
                    typename traits::interior_mutable_type<Polygon2>::type
                >::type
            >::apply(geometry::interior_rings(poly2),
                     geometry::num_interior_rings(poly1));

        typename geometry::interior_return_type<Polygon1 const>::type
            rings1 = geometry::interior_rings(poly1);
        typename geometry::interior_return_type<Polygon2>::type
            rings2 = geometry::interior_rings(poly2);

        typename detail::interior_iterator<Polygon1 const>::type
            it1 = boost::begin(rings1);
        typename detail::interior_iterator<Polygon2>::type
            it2 = boost::begin(rings2);
        for ( ; it1 != boost::end(rings1); ++it1, ++it2)
        {
            if ( ! transform_range_out<point2_type>(*it1,
                                                    range::back_inserter(*it2),
                                                    strategy) )
            {
                return false;
            }
        }

        return true;
    }
};


template <typename Point1, typename Point2>
struct select_strategy
{
    typedef typename strategy::transform::services::default_strategy
        <
            typename cs_tag<Point1>::type,
            typename cs_tag<Point2>::type,
            typename coordinate_system<Point1>::type,
            typename coordinate_system<Point2>::type,
            dimension<Point1>::type::value,
            dimension<Point2>::type::value,
            typename point_type<Point1>::type,
            typename point_type<Point2>::type
        >::type type;
};

struct transform_range
{
    template <typename Range1, typename Range2, typename Strategy>
    static inline bool apply(Range1 const& range1,
            Range2& range2, Strategy const& strategy)
    {
        typedef typename point_type<Range2>::type point_type;

        // Should NOT be done here!
        // geometry::clear(range2);
        return transform_range_out<point_type>(range1,
                range::back_inserter(range2), strategy);
    }
};


/*!
    \brief Is able to transform any multi-geometry, calling the single-version as policy
*/
template <typename Policy>
struct transform_multi
{
    template <typename Multi1, typename Multi2, typename S>
    static inline bool apply(Multi1 const& multi1, Multi2& multi2, S const& strategy)
    {
        traits::resize<Multi2>::apply(multi2, boost::size(multi1));

        typename boost::range_iterator<Multi1 const>::type it1
                = boost::begin(multi1);
        typename boost::range_iterator<Multi2>::type it2
                = boost::begin(multi2);

        for (; it1 != boost::end(multi1); ++it1, ++it2)
        {
            if (! Policy::apply(*it1, *it2, strategy))
            {
                return false;
            }
        }

        return true;
    }
};


}} // namespace detail::transform
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry1, typename Geometry2,
    typename Tag1 = typename tag_cast<typename tag<Geometry1>::type, multi_tag>::type,
    typename Tag2 = typename tag_cast<typename tag<Geometry2>::type, multi_tag>::type
>
struct transform {};

template <typename Point1, typename Point2>
struct transform<Point1, Point2, point_tag, point_tag>
    : detail::transform::transform_point
{
};


template <typename Linestring1, typename Linestring2>
struct transform
    <
        Linestring1, Linestring2,
        linestring_tag, linestring_tag
    >
    : detail::transform::transform_range
{
};

template <typename Range1, typename Range2>
struct transform<Range1, Range2, ring_tag, ring_tag>
    : detail::transform::transform_range
{
};

template <typename Polygon1, typename Polygon2>
struct transform<Polygon1, Polygon2, polygon_tag, polygon_tag>
    : detail::transform::transform_polygon
{
};

template <typename Box1, typename Box2>
struct transform<Box1, Box2, box_tag, box_tag>
    : detail::transform::transform_box
{
};

template <typename Segment1, typename Segment2>
struct transform<Segment1, Segment2, segment_tag, segment_tag>
    : detail::transform::transform_box_or_segment
{
};

template <typename Multi1, typename Multi2>
struct transform
    <
        Multi1, Multi2,
        multi_tag, multi_tag
    >
    : detail::transform::transform_multi
        <
            dispatch::transform
                <
                    typename boost::range_value<Multi1>::type,
                    typename boost::range_value<Multi2>::type
                >
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy {

struct transform
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2& geometry2,
                             Strategy const& strategy)
    {
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2>();

        return dispatch::transform<Geometry1, Geometry2>::apply(
            geometry1,
            geometry2,
            strategy
        );
    }

    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2& geometry2,
                             default_strategy)
    {
        return apply(
            geometry1,
            geometry2,
            typename detail::transform::select_strategy<Geometry1, Geometry2>::type()
        );
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry1, typename Geometry2>
struct transform
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2& geometry2,
                             Strategy const& strategy)
    {
        return resolve_strategy::transform::apply(
            geometry1,
            geometry2,
            strategy
        );
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct transform<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename Strategy>
    struct visitor: static_visitor<bool>
    {
        Geometry2& m_geometry2;
        Strategy const& m_strategy;

        visitor(Geometry2& geometry2, Strategy const& strategy)
            : m_geometry2(geometry2)
            , m_strategy(strategy)
        {}

        template <typename Geometry1>
        inline bool operator()(Geometry1 const& geometry1) const
        {
            return transform<Geometry1, Geometry2>::apply(
                geometry1,
                m_geometry2,
                m_strategy
            );
        }
    };

    template <typename Strategy>
    static inline bool apply(
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
        Geometry2& geometry2,
        Strategy const& strategy
    )
    {
        return boost::apply_visitor(visitor<Strategy>(geometry2, strategy), geometry1);
    }
};

} // namespace resolve_variant


/*!
\brief Transforms from one geometry to another geometry  \brief_strategy
\ingroup transform
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy strategy
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param strategy The strategy to be used for transformation
\return True if the transformation could be done

\qbk{distinguish,with strategy}

\qbk{[include reference/algorithms/transform_with_strategy.qbk]}
 */
template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool transform(Geometry1 const& geometry1, Geometry2& geometry2,
            Strategy const& strategy)
{
    return resolve_variant::transform<Geometry1, Geometry2>
                          ::apply(geometry1, geometry2, strategy);
}


/*!
\brief Transforms from one geometry to another geometry using a strategy
\ingroup transform
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return True if the transformation could be done

\qbk{[include reference/algorithms/transform.qbk]}
 */
template <typename Geometry1, typename Geometry2>
inline bool transform(Geometry1 const& geometry1, Geometry2& geometry2)
{
    return geometry::transform(geometry1, geometry2, default_strategy());
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_TRANSFORM_HPP

/* transform.hpp
84jZZV+zIsoXHtopLwymQ4IC28ddXKLlkji10jIEvGtiV5e61obF0puDidg5YL0uyG5JPY3n6L8rhTZ7c2ctHlzTOhdl90SV/+4xrhic44S7lX7VOI/H/paQGfSUchApLch1NeuA1YkWf9sgsVkISvDPw/Z+nR7lBScNGEhTvC7ThNx51b1hsV45UiLPGEamiiFYgxKvJ/8fP6BImc++AQ8nqckhnIB4NPi1JBoQp9AEIKPuq8Kfg+0hUdjFTMKosDkxHk5k/oBdq9zSZd1RI5UHlNNQZt4CUyYR5pJ5GeCeXhkwUuXKWaFd4bFkqAZqRuWqm9XUaBsuPWx2WSqJJTBeSPP5FRrWyGuVqXkWK4LkOG6DWJuPEzSJpj0WkvsTKyRXT6RkYyXA0kfQFtwq6G14FX8eIf3SzkUaNAwtKBn3FZ3XGKZP8VrsZ0bJXG32cS4dzmWumuuRd787O9eNTekP9o2v+aGvrK57oqeSp33pSL+/b688AAa8t8w9j7hfWYS3flc7MMo66z0ZUAdlt+VhO2ivDrcd8L5Wu61QvtS67zv3dmL/PyN/6b8B+FzXe//Z26E5OUr3+3vNrzPfk/El3yTLcIdM536y+/KY9x3ixyzztfWZpdj2k+rHjOoKv4sQgA+cB/aasZsG1eP8qqH3/Tth6aw55KcOYA/r7cbn/U+i31/G5+x0nw9xipe758t0UCxc2YcxAeTlMOz1gR2raPGHxvOF5Al/zsPmoqtZNwg/Yer/ACaA2X90LBmk+L4Q1vBfRg3DCldwk6NA2Hp0qqjyyhcKEE6JhGx9UdN1zGD9y281WM+r7+NmqAZr47DBOpyK+ifIxCnhFHhj6JvOeoxCtQYQrhGmcglKGXwfVIL1bVIUTYr1odH7Rd3UnSn9J5Uakf5xSQEuUdivYX+ns4TPwFgrtMkQLgQ1jfE0qlnD/lpn2fCVFESnpfQc8l4c/Ldald0pstO0eSEoIRlOo+g0yKXm8Jcwb6S+Sbvoqg5Msuuy7tpwfyeX3OI4obgJPdFEts2Cl9gWEcIBOFD3QLVoR+jpFHoXg+K0mf2jw6RxGKKlJc/FfSO0qJ4WB3qJiO32oVefzlVA4RSfHz9qcz46rsYz7BEs4u3rUXsBBEU0+yC6NoepdiKu7X8AsLW8UeQNuNH88xZH5wWFHIDc+80MXiuGhaTSPQO0kOOQqGmUvfHPT/2b9sbfPDXa3mh6nNob21WbYyf8eqrZDT0aND4ugD8fzq9mV8xOp8nQEvnNEewcaIVUjIVbP1HshDMUO2F6Nftx4tfsqjPVrLsX3rmYOfLjy+lLrgxTJKV8bjyEauq+QWtmx1dbYPrRhGh8zd4WwAi0ODK03P36THgCvu8GGAgNAuwDb5xGy2aE4dHoma+WInSnVbMTgUGj9k58MQj7U9HkKXxhQKtn2nqYy0AS4UAaqpup96L/m+sutpM8laydFdM6j2Yq04F3qUeM7AqjsoH8hFhrKCOFOcryIejhdv7BMrLQpp5BmSZEhkCrP4Lqfqtygk1rpGp/WP+6678Npr48yzZ+Lia9DJOaRxwO0+r8SsK9NKHd4uXM5MMrYhjdlKlsuc+u6OJnlRGOqhHRfeBl5JcFdBmkzE366FnItAvWPzJVrRgXX8pHblpqLjDiEtRdRDudKk1S0X1iilRUIy7VSSm2cZ1/MKA78nE/e8Fg8hWt4xNIwjOoxIGiZtPv/h1ETkb1KxZvINU/oRobhPbZ18XxZqFoXRwUokEPtADZrsPIUb61sV/5QYWtppvAeoS9eApVs3UibsH36BBr4zPKFnyT5G2lPjYM7B5dkdCp8+KxnwTJGRHuWHc+atHMNWOH4SfgTohxR6ACkDgPElc0KYd+fGhuLY/ZgaPF/2NoVPGT6QmAMg21Q5LGXQoGE0ZhMLuMOpe5NA7mUTjQ5FEstqpYeAfsGyZ5B9I3xLO/P/LhF004CfaemvkhacKbk2JIulUs8xBL3sDui3eR/UiWyNqwsYB9DT6H6N7tcv4MjXz2GcqXm3ktqGCSs0cS30LEExvjGxMbUgoaUxriG4ONKQX1bfzZyiznINoxI8Lq4SoMl/m+4ni50SDxPfVt3CTpJxTUhMYJCw/SDfsA45+NBjvE3RBO9g6sxa38jmjMaelIkTcrk/tG+qGCQUlj6sLLVvKaosYk+6IGTNKHNKxUMPi/6oHTCCRPAIBDS619fWAUxdn4fWdJLuwBCQQMECEoGrDRgBKPQBAuhGrgYuRChAS0GNMrtQi7oG0+uznNZr2Kb7GVqi0W7Ytvv2wVBCx4l8OEAGr4EBMBDZraORc1SEwOiNnf88zsXRK079s/foTbnZmdeeb7mWdmno/BEnR8AZmeSfmos/fggp9aswJDdRYXFuJNKUPLwni6s+p8HvsFubJkQOz9qI14FHLHkZ/8lrKg0jty6EMdutcwiNFfZtxJCNsD5LmGckr3LENr8h5zn4f8kLKUO8oGE3Jk7cCQQcSC3hoYPq6KoP1Sof2UdqL0a1pWq7NDnEK+mRTdSXpnxAYPa3m82WgNZRdwmzqyC+zVVig0XjlKgRG4xx5BmjDpFDVUPKcgRZikLE8C5FRg538XyGqVbp+JJ6sR8xElSG7FiVSVJM2fqVwUbc3mmf6NRlQ0XZ3cuBSooO6GkUot7QpDoyGvwZYVmONK4bcGzC67uRuaVROt0hFNtWZ8aC7lKnIBHcOG8HhZlOlE8C81ZbscgrnZ5lIW27Frv6cstuQ/autrb84zzpQiaysTtnnXwkbJkGdSmqRIPPrjqd+sNBnyLL3WFJgextVCUm12psh7zf4FyHllvEiZi4e1CezE/kU1x1Byg3TdGN1MSednDFXgyaGsRhJKanjHrizyF3QV+gtOFjKWo0qKPpJ8yNdRPZEKb3xxI+o2UX+suPCYO4wyX5aEgJoELVl1EpsyI5jV6uvlfwcOBORfaix0Q1fQjwH9k7nFfKiQ7HlO51sRrM1xBnUCdrrrpNfghvVcacHTdfIZPVBPiTGKb9seYxTHoTNc9m/SVaK/6Z5iOo7OtLjO4/KbhZpmMqmN88uonjSpyixXJaHMU584lfw2NTq8Em7E4UVoU3ax4RW+xkz5nDe1K64kKZDQbDOgbPAIUpFKR9Yh3HHG4RXNYgusTuGkfbiCF009nHXaeZj3/ZcuY9vINHlEG80sBQawGkn+MpMbNtjpmi6BIYzH/CETpvERBbsBRYafRhWKzpmipdk2M0+qSoEYmdCoA4fSOy2PNOQZvQ8AxvKQHxzRjyDql6NaKIgH3TLQWnuusza4voFrzjUbwqijkZ6bZ7UmHBIoQKU0BcoYBdd3+prTAB6gKsss0ied7HAZOjJ0fdbxhKCY3pxnyoRPSlzdOTxRhU0thFrl5edVB7T3gBmVl0Ccm+GD0pwnu+zZy5NES4ND5fH+K4pTRzRwQ4DIBZHNnLOJfwxP6eTlPShdbQDYVUmG6ruUYsvU5REljn+zoH+qq4edDJPeS5pWLgUy+dcDUiR7k8kcwgXlx/2WBpvi6uH/dMgSDFvytIKkcjwgRNVVBZGqv1BPZeF3g9xBQUa4TTf787RGrvZSOWqbzQOEYMjMV79AZVlJGJwtxtWGbm9IUUcMBBs41TyQq9GSItHrzfSQK8/TWWnGxQxmu0E0Kd3YG3+bFW3l9VDIOCgEybyE9lem4aCZeiLDdb6o5Jpjj/A1FmdowwhADRnQr2oixRHNpr72MSf6PlAGoHecJyrT96KOGYgZ3DC+qPBuN3ngWYPBktlgy5OXdytB5QQM7gTf8cpJNVbALxvGeQ3etRBrvh4LIuUNiTUZY8VvSIFY8RBr/LBYcmk3eqAYw6dHVoAe1Q1ib5h2SUpE2WxROgCLLyXNvbC+noY5dvv46Bz77+u+hcLDe5k4qGHT+7UoqZ/sFO2iA0bcfMQc5ubyFktKpmEYblaQ/7wm1eMvM5Kz+XTZKSI9n2satA2qQ7uomhAxAwIvpHH2RuO0fU5JlkFsDh1RY0FkpD16Xd9HmL9oza6yVwKGsANqVEJkAnRRsTeziKQ/913IdujF8HD86mG4tcwzHLembRvErVNSqFbu/5pGD1PXFSmlDmgvB4ln4T9l4UVAWjvbhUSGapUQRbYKark6WagUtJvfGYJozS1usuLXw/ArYMoUil89aGJ9KRO5jzEVzn82hlm/VQFAkcXesauLh1dg9TOsAr3iGHLfOKra+Vg6Kt8KP80UAfpahU+hKu1ZgTv1UvnnZkqXEPe1qqaMQ1AYQPVJhcXkL78aLKnNoBYrrvZ8Zzv/XFCK9FfOdLqSqqYDiRTfGLe4PiBealg8oC8VRhxo72AL1rCbV7yXZV/oItLM1geygyqhSIlV9u7fxCqL+DzygLBairiEe6VIuTheE9PoyhJdVq4f0CXDpch9wiQpskBgUVKHxWqCWGrmd3z4CYwbddx3fYgMXa5wHUi9ekVjQumplLwqztK019GqjZZcidIuj6MbDx606Rs+XY0klqfCYDAbKlA5T1avhyx6Jsab6sF/5Bxsi8qi8prTAWvsSNvFOeTEVHwmp+BzYhI+ZzvwmWOHZ/kTyXPoK3EGfU3k6Mtqoa9pBvqa2f8a53juSWsm+BSXYUc6fVt2TN+Ft9ncjlno93UCKddiXQ9RjVDCF/DjjvTX0PBOCjxHWAyBFmsq/apLksq+dkjyQhd1nkED4MnPoIRTBUTyGkkIhncJNFvyVgisyAdqS0vegoJlORjBIHIQ53cYpwJha8kcyqFpyU+gVAHsob8MFBYpQamTB8qsBoitj2uCJE64zf9iOp6RlPM1sLeuWeDARxo+MvGRiw83PtbgY71fxjPlfLHNd1y4TWkKEovAq2b/Eprev8SRL/ZKH/NCKuxNTgc/MwmcPN6/xPJ9MSJ1mgVbw/gF+eLllStCSnvfaSnkyDiRFbhbOSF9jN+MC74vXg6qmAYgWe4UI/eGl6PaoHgt+TlsBjzFzgqEWowroOrh+9+OiqSgQAkGkWVvD0p5aM1XC5Qw+ysov7PY7+Zqb0eNmmg8B1YSIQkZH+4mn92js0lQ1bm9NpNg7Y3jhK+AhFEMO43oMwpdO2mwSTgNG42YQDBu39BS+d0LF3YKk3MKlsErJQePocQbyTHUv759C7ZzuM8B9FgAA/bQgOoE8nfwaQ1b6BkC1Z8/B48f/GnI/e9QSrm6Ggu2eo2NP7ARll1lIyeLXaQSU9VuiQptiUnC/dKAVm11brZUWskZB6JQvGGcFZTFTp1zX6oMWmChkTdyFWa8voHvmhC0EOMoBgVp0vMkQ6MaA5Dzol8vgiJ2Qp7qtuhxwXhU2wFZWslGyAjgkalpTIkh8hafsw+t3gl7tHohxcCO5sQ50iMOs3iLkp9UdynN+svxgqPu0rX45uouTYG3OE56JBUNzPzKjuKKC+QGFORQgijg7eUq1mADrZtMt9eAdW+sy6ZQpygLUCnBNdR0DXQqFN+tPZxC5v9Kiyld/NlkVL8DGxk8q8FKkgf46E5BKbArRrwANDdLj1oMlQ6l0KIsgSa8RbGPNB82B6O9DcvOebszIsYTARKTqfBocGlAbGXHVS8rkl0RDzU/lKrk2pUU/3qLmoYHiA+nKjY3DEEzbkIf/Caquiz+TqnZ4jtdcwaVhGlGDQ3f9EiuiMMZV7mnbGWjC5nfLXveOW9zkJZfojnRBGxe1L2M1ri+Gsn6jpxCR0G/RraCg5Qm0NZB7WdyAzVBXQJk8lHvjIp2bLzvwQ5R6cCVXuTk0i7pgaMGZXG/7DqjbYJF86Cb7Pk1FXhztZMxCKm2gZlqIlbqe4L62khfPBoTwm/kfDxdBOWGJ/QhSSUMHbCkMkRfBJi+mNieieoroePtJ4rrPPkUmoL2xMvxOE+wpw2wzEPh6qpjI38ZjnwYzmUO5AdCfUp59o0pPwokKfekWJyHqxc470rhapx4xnRXG1fo8RqKyd/66SKJB7t0KIucPgpaUBEblDkpav9hIp56uTrV/2YtorjOyIuh3O3Egs1AHLRuJ+UGWlMT9bWxmtbNo0PvDqkaBvRcJS8ph47nkTl0OMfl0NGcLlUdNYiTKBdYCrQweexXTOkJShB4yI1UyhgPHg3rUP8H7LGyjiPbF+CdfKgcX78CZuucQo6vX4b3s/mc87Bo78Mq1PL1czEIT659gUcsfuFmu7y8P+v0wqKdnLAAcJ62OYU0P6Wzy9Wjmh7YpO+KBZzDJlicIiNXHmJBN7nQT3veFj6Cn6rwZEpbn1I/Wcgn1bFk/8Pg/DgWsA3vEDbrkT1k9SdMWVNNkoX3IYMWcp0LlVILV6w+l12cIs4hN+tphfsAUHrUcw8AwVgMEFlLC+P2kJEMoJpNLm3Ro94A6c5HPalYzw+3sHtnvjfO4jWsgBmOQq6qlbydEDtPR+nRkagrAkfcDxOomp3ya5AlnatIw+ZPuoZuWlnzClal1K7GQ5PjBcaqUXY2kJI8qGxNwWPePEZY5guT88VZXqM/j3NjUf54hRYcOruIvPkUkEQp0S9PDfny0lODmOncBIqZWMHa4mPHF7CDQkVEKUWUod3DTqCkKlRowYlmj2oGWov8AABptzFiykP2XEK7rpYKAz2UTM2FcDkPDZgpdzKNQ19fQSjToaniPG7y+RZNG5TgQQRYN89Mx9Z5FOwlo+IQ4dRShLOYmMHnpz6SbzUYsuOELMXGVrwb2fo3VRPTo1RlUlSysPopStshpwCll6tSpBo77DrIzTidkIrtcSNTA5QvrZg0/5eG4vKAKpwFPRsfpGb6IkX+R3qct1Uudq6P1NyhcMFzFnO+RSnsAWLEVvtTziDO9Jd095pzxWlQAAVJyrRhpyYc+R96KJqKu5iDqagaDLIIJKGi3IKeDS8M3dbNgsUAiPkUZaHFU4xMoTlRTLQEMdESDvbVQNtXWpyHYLn98QjKw/km4oLsebwPNaMiRngDkQHvuwGnaF6SMySMZnghgeIF3ofEn1SdauB9NhRz32nFhkYkY+DrP0GzLL9CVesUwcpolc4aRb5eoweQK/ncr/NpWslnHPTFPPE6iojSWG7DsVAC5gQxAxCT5Fhjiwhfj0y0JAOB0xCSZqWH2Vm98ivUHwfjqQS2IquyTmdPrp6Ihz53mS0Ve4AiJ3sOokEXMTEPCDronE9IMofFw9a+O4IjnZnCPNri4tYgldbThHyf6xjfZ4vrKCXd9h+kh9Wx9nvJyNqP9z3775ru58bYIOIfw3s+pk6w201tMMIQkrbgEOqmQ6iTl3C37X/EIVd1KQUR/+JuWNqyOf5JPKJyLuvhn6zDQcmOtGAdJL5A9QYlD1dw/woLXiyeh5Cp2qZUBXUu9sBKSV78OrqET9AKzkshS7brfM1ZrYBIrh4HauOuOaDehCOxqh0KpJT2aOIZusJHRyRuNMm4flp1paqLDsluvFloSYJiOl2d/M/d9IQ2pbYq1SDEQ6eTgV5sU2Qu5n1/oUVGXr7JtG34nz+HITWpqKbtKcqdVNBHe47hYJIPs5osxAfOb33hzsI7s6r0wcXbI1phxiJeSScJfixdilfz0CLbSSmttAMagjzYh5xPKdLP7IZN12EJeZ+G6i70yR8pGjL7f0cRThppNg2lXW61MSuYoaFi
*/