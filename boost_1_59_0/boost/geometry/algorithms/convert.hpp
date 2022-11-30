// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017-2021.
// Modifications copyright (c) 2017-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_CONVERT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_CONVERT_HPP


#include <cstddef>
#include <type_traits>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>
#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/convert_indexed_to_indexed.hpp>
#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/arithmetic/arithmetic.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/util/range.hpp>

#include <boost/geometry/views/detail/closed_clockwise_view.hpp>


namespace boost { namespace geometry
{

// Silence warning C4127: conditional expression is constant
// Silence warning C4512: assignment operator could not be generated
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127 4512)
#endif


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace conversion
{

template
<
    typename Point,
    typename Box,
    std::size_t Index,
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct point_to_box
{
    static inline void apply(Point const& point, Box& box)
    {
        typedef typename coordinate_type<Box>::type coordinate_type;

        set<Index, Dimension>(box,
                boost::numeric_cast<coordinate_type>(get<Dimension>(point)));
        point_to_box
            <
                Point, Box,
                Index, Dimension + 1, DimensionCount
            >::apply(point, box);
    }
};


template
<
    typename Point,
    typename Box,
    std::size_t Index,
    std::size_t DimensionCount
>
struct point_to_box<Point, Box, Index, DimensionCount, DimensionCount>
{
    static inline void apply(Point const& , Box& )
    {}
};

template <typename Box, typename Range, bool Close, bool Reverse>
struct box_to_range
{
    static inline void apply(Box const& box, Range& range)
    {
        traits::resize<Range>::apply(range, Close ? 5 : 4);
        assign_box_corners_oriented<Reverse>(box, range);
        if (Close)
        {
            range::at(range, 4) = range::at(range, 0);
        }
    }
};

template <typename Segment, typename Range>
struct segment_to_range
{
    static inline void apply(Segment const& segment, Range& range)
    {
        traits::resize<Range>::apply(range, 2);

        typename boost::range_iterator<Range>::type it = boost::begin(range);

        assign_point_from_index<0>(segment, *it);
        ++it;
        assign_point_from_index<1>(segment, *it);
    }
};

template
<
    typename Range1,
    typename Range2,
    bool Reverse = false
>
struct range_to_range
{
    struct default_policy
    {
        template <typename Point1, typename Point2>
        static inline void apply(Point1 const& point1, Point2 & point2)
        {
            geometry::detail::conversion::convert_point_to_point(point1, point2);
        }
    };
    
    static inline void apply(Range1 const& source, Range2& destination)
    {
        apply(source, destination, default_policy());
    }

    template <typename ConvertPointPolicy>
    static inline ConvertPointPolicy apply(Range1 const& source, Range2& destination,
                                           ConvertPointPolicy convert_point)
    {
        geometry::clear(destination);

        using view_type = detail::closed_clockwise_view
            <
                Range1 const,
                geometry::closure<Range1>::value,
                Reverse ? counterclockwise : clockwise
            >;

        // We consider input always as closed, and skip last
        // point for open output.
        view_type const view(source);

        typedef typename boost::range_size<Range1>::type size_type;
        size_type n = boost::size(view);
        if (geometry::closure<Range2>::value == geometry::open)
        {
            n--;
        }

        // If size == 0 && geometry::open <=> n = numeric_limits<size_type>::max()
        // but ok, sice below it == end()

        size_type i = 0;
        for (typename boost::range_iterator<view_type const>::type it
            = boost::begin(view);
            it != boost::end(view) && i < n;
            ++it, ++i)
        {
            typename boost::range_value<Range2>::type point;
            convert_point.apply(*it, point);
            range::push_back(destination, point);
        }

        return convert_point;
    }
};

template <typename Polygon1, typename Polygon2>
struct polygon_to_polygon
{
    typedef range_to_range
        <
            typename geometry::ring_type<Polygon1>::type,
            typename geometry::ring_type<Polygon2>::type,
            geometry::point_order<Polygon1>::value
                != geometry::point_order<Polygon2>::value
        > per_ring;

    static inline void apply(Polygon1 const& source, Polygon2& destination)
    {
        // Clearing managed per ring, and in the resizing of interior rings

        per_ring::apply(geometry::exterior_ring(source),
            geometry::exterior_ring(destination));

        // Container should be resizeable
        traits::resize
            <
                typename std::remove_reference
                <
                    typename traits::interior_mutable_type<Polygon2>::type
                >::type
            >::apply(interior_rings(destination), num_interior_rings(source));

        typename interior_return_type<Polygon1 const>::type
            rings_source = interior_rings(source);
        typename interior_return_type<Polygon2>::type
            rings_dest = interior_rings(destination);

        typename detail::interior_iterator<Polygon1 const>::type
            it_source = boost::begin(rings_source);
        typename detail::interior_iterator<Polygon2>::type
            it_dest = boost::begin(rings_dest);

        for ( ; it_source != boost::end(rings_source); ++it_source, ++it_dest)
        {
            per_ring::apply(*it_source, *it_dest);
        }
    }
};

template <typename Single, typename Multi, typename Policy>
struct single_to_multi: private Policy
{
    static inline void apply(Single const& single, Multi& multi)
    {
        traits::resize<Multi>::apply(multi, 1);
        Policy::apply(single, *boost::begin(multi));
    }
};



template <typename Multi1, typename Multi2, typename Policy>
struct multi_to_multi: private Policy
{
    static inline void apply(Multi1 const& multi1, Multi2& multi2)
    {
        traits::resize<Multi2>::apply(multi2, boost::size(multi1));

        typename boost::range_iterator<Multi1 const>::type it1
                = boost::begin(multi1);
        typename boost::range_iterator<Multi2>::type it2
                = boost::begin(multi2);

        for (; it1 != boost::end(multi1); ++it1, ++it2)
        {
            Policy::apply(*it1, *it2);
        }
    }
};


}} // namespace detail::conversion
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry1, typename Geometry2,
    typename Tag1 = typename tag_cast<typename tag<Geometry1>::type, multi_tag>::type,
    typename Tag2 = typename tag_cast<typename tag<Geometry2>::type, multi_tag>::type,
    std::size_t DimensionCount = dimension<Geometry1>::type::value,
    bool UseAssignment = std::is_same<Geometry1, Geometry2>::value
                         && !std::is_array<Geometry1>::value
>
struct convert
    : not_implemented
        <
            Tag1, Tag2,
            std::integral_constant<std::size_t, DimensionCount>
        >
{};


template
<
    typename Geometry1, typename Geometry2,
    typename Tag,
    std::size_t DimensionCount
>
struct convert<Geometry1, Geometry2, Tag, Tag, DimensionCount, true>
{
    // Same geometry type -> copy whole geometry
    static inline void apply(Geometry1 const& source, Geometry2& destination)
    {
        destination = source;
    }
};


template
<
    typename Geometry1, typename Geometry2,
    std::size_t DimensionCount
>
struct convert<Geometry1, Geometry2, point_tag, point_tag, DimensionCount, false>
    : detail::conversion::point_to_point<Geometry1, Geometry2, 0, DimensionCount>
{};


template
<
    typename Box1, typename Box2,
    std::size_t DimensionCount
>
struct convert<Box1, Box2, box_tag, box_tag, DimensionCount, false>
    : detail::conversion::indexed_to_indexed<Box1, Box2, 0, DimensionCount>
{};


template
<
    typename Segment1, typename Segment2,
    std::size_t DimensionCount
>
struct convert<Segment1, Segment2, segment_tag, segment_tag, DimensionCount, false>
    : detail::conversion::indexed_to_indexed<Segment1, Segment2, 0, DimensionCount>
{};


template <typename Segment, typename LineString, std::size_t DimensionCount>
struct convert<Segment, LineString, segment_tag, linestring_tag, DimensionCount, false>
    : detail::conversion::segment_to_range<Segment, LineString>
{};


template <typename Ring1, typename Ring2, std::size_t DimensionCount>
struct convert<Ring1, Ring2, ring_tag, ring_tag, DimensionCount, false>
    : detail::conversion::range_to_range
        <
            Ring1,
            Ring2,
            geometry::point_order<Ring1>::value
                != geometry::point_order<Ring2>::value
        >
{};

template <typename LineString1, typename LineString2, std::size_t DimensionCount>
struct convert<LineString1, LineString2, linestring_tag, linestring_tag, DimensionCount, false>
    : detail::conversion::range_to_range<LineString1, LineString2>
{};

template <typename Polygon1, typename Polygon2, std::size_t DimensionCount>
struct convert<Polygon1, Polygon2, polygon_tag, polygon_tag, DimensionCount, false>
    : detail::conversion::polygon_to_polygon<Polygon1, Polygon2>
{};

template <typename Box, typename Ring>
struct convert<Box, Ring, box_tag, ring_tag, 2, false>
    : detail::conversion::box_to_range
        <
            Box,
            Ring,
            geometry::closure<Ring>::value == closed,
            geometry::point_order<Ring>::value == counterclockwise
        >
{};


template <typename Box, typename Polygon>
struct convert<Box, Polygon, box_tag, polygon_tag, 2, false>
{
    static inline void apply(Box const& box, Polygon& polygon)
    {
        typedef typename ring_type<Polygon>::type ring_type;

        convert
            <
                Box, ring_type,
                box_tag, ring_tag,
                2, false
            >::apply(box, exterior_ring(polygon));
    }
};


template <typename Point, typename Box, std::size_t DimensionCount>
struct convert<Point, Box, point_tag, box_tag, DimensionCount, false>
{
    static inline void apply(Point const& point, Box& box)
    {
        detail::conversion::point_to_box
            <
                Point, Box, min_corner, 0, DimensionCount
            >::apply(point, box);
        detail::conversion::point_to_box
            <
                Point, Box, max_corner, 0, DimensionCount
            >::apply(point, box);
    }
};


template <typename Ring, typename Polygon, std::size_t DimensionCount>
struct convert<Ring, Polygon, ring_tag, polygon_tag, DimensionCount, false>
{
    static inline void apply(Ring const& ring, Polygon& polygon)
    {
        typedef typename ring_type<Polygon>::type ring_type;
        convert
            <
                Ring, ring_type,
                ring_tag, ring_tag,
                DimensionCount, false
            >::apply(ring, exterior_ring(polygon));
    }
};


template <typename Polygon, typename Ring, std::size_t DimensionCount>
struct convert<Polygon, Ring, polygon_tag, ring_tag, DimensionCount, false>
{
    static inline void apply(Polygon const& polygon, Ring& ring)
    {
        typedef typename ring_type<Polygon>::type ring_type;

        convert
            <
                ring_type, Ring,
                ring_tag, ring_tag,
                DimensionCount, false
            >::apply(exterior_ring(polygon), ring);
    }
};


// Dispatch for multi <-> multi, specifying their single-version as policy.
// Note that, even if the multi-types are mutually different, their single
// version types might be the same and therefore we call std::is_same again

template <typename Multi1, typename Multi2, std::size_t DimensionCount>
struct convert<Multi1, Multi2, multi_tag, multi_tag, DimensionCount, false>
    : detail::conversion::multi_to_multi
        <
            Multi1,
            Multi2,
            convert
                <
                    typename boost::range_value<Multi1>::type,
                    typename boost::range_value<Multi2>::type,
                    typename single_tag_of
                                <
                                    typename tag<Multi1>::type
                                >::type,
                    typename single_tag_of
                                <
                                    typename tag<Multi2>::type
                                >::type,
                    DimensionCount
                >
        >
{};


template <typename Single, typename Multi, typename SingleTag, std::size_t DimensionCount>
struct convert<Single, Multi, SingleTag, multi_tag, DimensionCount, false>
    : detail::conversion::single_to_multi
        <
            Single,
            Multi,
            convert
                <
                    Single,
                    typename boost::range_value<Multi>::type,
                    typename tag<Single>::type,
                    typename single_tag_of
                                <
                                    typename tag<Multi>::type
                                >::type,
                    DimensionCount,
                    false
                >
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_variant {

template <typename Geometry1, typename Geometry2>
struct convert
{
    static inline void apply(Geometry1 const& geometry1, Geometry2& geometry2)
    {
        concepts::check_concepts_and_equal_dimensions<Geometry1 const, Geometry2>();
        dispatch::convert<Geometry1, Geometry2>::apply(geometry1, geometry2);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct convert<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    struct visitor: static_visitor<void>
    {
        Geometry2& m_geometry2;

        visitor(Geometry2& geometry2)
            : m_geometry2(geometry2)
        {}

        template <typename Geometry1>
        inline void operator()(Geometry1 const& geometry1) const
        {
            convert<Geometry1, Geometry2>::apply(geometry1, m_geometry2);
        }
    };

    static inline void apply(
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
        Geometry2& geometry2
    )
    {
        boost::apply_visitor(visitor(geometry2), geometry1);
    }
};

}


/*!
\brief Converts one geometry to another geometry
\details The convert algorithm converts one geometry, e.g. a BOX, to another
geometry, e.g. a RING. This only works if it is possible and applicable.
If the point-order is different, or the closure is different between two
geometry types, it will be converted correctly by explicitly reversing the
points or closing or opening the polygon rings.
\ingroup convert
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry (source)
\param geometry2 \param_geometry (target)

\qbk{[include reference/algorithms/convert.qbk]}
 */
template <typename Geometry1, typename Geometry2>
inline void convert(Geometry1 const& geometry1, Geometry2& geometry2)
{
    resolve_variant::convert<Geometry1, Geometry2>::apply(geometry1, geometry2);
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_CONVERT_HPP

/* convert.hpp
TTiU8HNCI8JOhLqEjRkafET4N+EtwquE5wkLCNMJkwhjCb8n3EAYShhAOJtwKuEkwjGEwwkHEPYilBG2IXyVrsGnhDWEvxNeJ7xIqCDMIjxEuIdwB+EmwtWEywjnEU4ndCYcT2hJOJCwD+FHhAaEb9M0+IzwPmEV4S+EpYRnCOWEKYSJhDsJtxB+naY5GZYTLiD0JnQjtCccpUKF2QB9mbiiQPPWAt8/WU3B90+GoqfOW+49lL0O/x7KsoR/DzWghH8PZQRzijFW+P6roOX7ogqx6SK+L6oXBazCtclIVY0lFUvu5mu/HxK9Q9+9V1RgY2l+q+/boD+FYI3vP/Nbvv/F9z/q/gdjJFy7/2p8AniRjCtQLXYS3r7HV173cH5aP4Mo+6pI50qLsrq8GzCGAOzAvlkHOL7tiZqXV1mauueRzvVQtxbr9mFdB1Wd6v2nJlQT6VwNIXzNrCjD0L087fdH2H/Xd+r+x4huydKiXEV7TS/1kc6PoBcZ9qJvA70kUS+4PKNk9ftn5WucGohlr1lldaRzFVTe+gUqbbFyofbyo9yqxITX0vtr1bRGLEvS2jjxWL8O6/u3rK8RE7TzizCfivkXuS3yCtFEM778SGc55EdCPvy8LNIZf+v+QCyuwGIFFOP6NL3SWp+2GBFGQySuZf/JokESrscW0cwA6+Vi0wGpfrMr/rxehBP+jENZ3Xkl9DIGe/GgXqKikp++fy9eOoCvoHcgPmgHvURVIuZoOsKWyIjtT1UdrVHi8A0jnZtgZin2Goa9voTH63L1uKGtDNrcsU2JbX8cZ+/TWXsNtA/FdpMx0F7Uor0C2jtj+0Zs39+iHft/8jO0V2L7ek27WyUe/5eGv5M2YUWksxKiFzGqPxaiU49rHe+q/88ZLh2SMjFCUyod8tux1ApLux/XPh3V5+OZI+r3qZXi+v3s/Y/KarY2ttjPRuznZzl3PFeJRpolKiOdyyHZDZMVmEyRt9jf1WJlk/q4le1nx0mlegl/Xoc6g3H4/Q85fX8hvFrngy34DbbwhfXvIt30xQSov9hsFfE1s8ISCy21FhgVldAIR8JCXGRUNKJPk+agaFQdFI2qg2L+de6Yno79BWB/NTla/bmViEaq8VeInvvU6+G0j63H+UjnQlx/LD+C5Sk5rVw/KhtZvinS+Tnka6/hcYb5VS3yUY9w0CmNOP5KxNt7ESsQd7KONpepVqVEvSp7rnGrEoF9G46Hvntg37h8J2/pYPEV3xZJ16+V4rMiNipD9Ub1xEonrPwrm9vfBmJlkfp+oeQr8IrXByvWYUVWtuZ4rhdNpr6jHK5vQzlebzC3NbuV7VMW+6Z5vhTzFZifnt3ieDIUnbRHHo95wRavfy3z9aIRn6/D6x/mB2P+RVaLvIHq+yfN8iMx7435S63lFYVa26Ut5rdgPq5lPlWsjOa2Tyxe/6+Codp75UAKOVbOUldiPpXPp0LqqCa/D/NVmDfNYt+/EcN2SzvZUgyK1toVy7BAZgcFrzKxAPMJc1XHh2hLdSO06yywzhXrLmTyq6Ra/zNa+6MthsMwHJfZcn+HFxuJL3zeNS/59QqeQlgyP7PF9c5IvOSjNZ7DmFdi3rx5foIh/PsvqdnFDPsPxfwbzOtq9y86xWjWe+zOd8135WisM7OHuisZ6ucHuH+f1jpeu2HIF0MpGS2+fwLjcWk+Hiy5+xOUbMeSkIwW4+/VPI+3rTzM52PePqP59q8Trfjx4H1qG4arMfxxRivng8FprePVC/OGDvj8k97a+XlK2j5mYtC3WvutF5baYml6Onu+Sj3F9Y/PAw1lEArE0Nb0VsYTdkr7/Md8Auant5Z3OqV9/mO+BPP9Wxu/AY0/awN+pckE/v2zv9kmxq3gib0Ijnj9S+Ofx8OLDcU2iVrr/TmGB2M4N03rkDHAJisnaNoDTZfbyDboy6qO6MlOIYjxcvwVP///+T/6iZiuL3wDCgBNA9mDzEHGIBlIAD2bpi8kIuOvaBPwS92CcAS8BFA+6ALoxjR1u7+HvrAOFAvKBClAZaAK0D+g56AOnvpCN5AJyArkDvIBBYO2gZJBclAhqBx0G1QHEqboC51BA0AjQY4gb1AgaDMoHpQKKgQpQdWgepATLLP3VFgv0DhQrDcsBxQGCgT5gNxBjiArUG9QZ9CrGfpCLagMlAmKAa0DzQd5guxB5qDPQIWQ7wbTDqAmL33hEagKdB10FnQF2m+B6kC6M2EZIEeQK2gOKBh0ANqyQXLgElA1SAl6BjL00Rd6ggaBrEATQQKsixdMD0D7D6DNM9X7wNhDPW0L+yoeFAfSA+mCoGUjPKtubAdqL+1LJ9h3PqAAkDmoH6g3qDMoDFT7Jew/kBx0ABQD2gYKAy0FeYOcQCNB/UBdQLqgBhhfDagSVAY6AUoFJYIiQCtB80HvIHv+S/WYDaSx95DG200aqxGorTT+NtL66IA+lNZBAcdnOehPUD3IALa5EcgM5AkKBG0AxXvptzgHGmbryi4t1ZXZBOrKMkJ1Zcx/OEVPdmwOzbNP+DoLd5zi71jEn+4yeq8nGN3TE8wFY8EGNBx/dF9ic+DhwkjBTJq3hj/4GSlYSo4F/MHMCE31cNW8VbN5K00P6rwFtzRsN9e0s3nLZvOWWvU4pubLM9Oa1+5/KNRZc2vIvBEtPHNgbc+M619Q9T8U1mmEljdSs5VYhk/QFlO3mbeopzk7YZWwUlih8h2FhUIgaCUIP+7gTwUOgulqyZsIHCIsgLnmLV6CH9QKgr2qH0Fww58CxrHE6cnMQINBJiBjkAHoeayerAa0PGSFk4PbqckRhhcGmbbpV7fq6a11xo5rXAo/s/POe/m91+JnPV50H93XKWmEQ/mRncoEl+ClcW+EQIeYPoV+3nE+m13Gvbna1v1v1+jt2wJ/8rd4Z3XQrMFvm437Ob24uXtsjsvK3/4jK+hb6Hpmziqvb/KSlrw99km0dcP4yRHK2JjsY0P73v72+OrbBw9PKOjsPMh0xC8GYxcFOfbtZuMa0THktFn860Hx44baxRmWuIen9j1SOfjv6QHbulv/67Fr8rFlvYKmNbbP/flJxt0AZaHdzgtpiXPSDYpPfNpB8ffs1RP3jxm2d3Y7R8cfv2yz27uq++Tcttv3LFub9aDSZYvLgll/OSY1PpnmXLx/69chO2b+s3ScS+y6oOTSJBud37ue3Hjt8U3X7N+M34xa9klK/LDR84aVySZm3fUwTbtcZHHu77vH+8+f4rBt8KKExCef5Z/fOkA5sb3tpKP3Pd1WfVDzb2k7+4VZj3a6b/s3rEfXqCkRZ1Jt7HybAiYpGnalr70+tlZr/v6OwzeUDVEFk47On1T7696fjxnMC/pzcs8I+9zH9+e9N48+0D3etcKodIZbWsydTTq7ejlfLbXu/WjFa6echiaHfbW1HYdbtv+weOUot7MKG7efzuj0KLKe36nq/h23jKgLfSLeHusdonez6B+rAc6nP3YyDX7yUeDKxIdTuued8Qg3veI7JL3H+H5GwdcWzjWeECUfMG1zl407PkwNiy4ckOwScX9FcXnjrV+Kg269Nbnz0i2rrm9W92H1E4K+yQj44sjaiXn7F025Z/hZSZeOT0I25ZTYpYvnckf1fzEtvtttG7dTG9xOnus/9kO9uhG9gq76lp/b7hFTlfUgqzHSsvp8WreFcWXOuy5vflGQqLfL2mf7wdlfPJ4QUXxn1Cv/365dOFFVH1n/neuec7VD25e6zq6dcznC5tspbmd9Cy/JHo0r6CBdFjvqC6pfo8o+lXAsl4MUoEzQPtAOUBjIH+QJGgMyAfF5I5ABqGm3nqwOVAkqAylAqaAE0HZQGMh/t7pvb5i6goKEuUKwsEYIhTM2BM7nTwX82WF3YbrgCn/UHwc4032F+ZAJhDMUz9UhwnJhMdSFwLnrD2f/AqgOhcwC1fxCmM6FeX9hGUyDVHNrhCVQg1fSuUB+KsI+V8FcICR9YTpXdS3A/vAKMlfV23JhEbQsVrUvBycQWnEJvqp+1aNeohrNUAF/FDP5vZ4suJsg6y3oy6plggxuWrJk0HlQQCtefiueoNPS662vL1MaCTLbKEFWD9NqS0FmAJ78vI7MGOQJqlb9KLAguEK9ADk5zBvDdN4FHVnyRR2ZANPgEpgW68jkoHkguNnK5NgOU1RwD0EWDTIeBctF7gl9jhBk/WGthwj0N35oGgr7DOeMYYsuUe0L5uPHU7WfFsPfC8EJhQTuQ2PYsiGwJ4JU197JsA3xmh2i2sd4bfbXSjT/qJcWJi0X5/H+tEhqw/uFmmfCkeQFKUs4hsxBZq145lqeWvDIJUyCe4Gx6v4qcPMWqgq878yH9cJ7D7I/rJWf6hhRjz1UdRdaKR0doar7iZ9qrrU2gWt3UB132E8wZIyhby/whglOqvVSP014QRKPwxXAE1Rp9ZEfAv14qMYULI1MvW1p7n++n3nPUr68dainQ8zUvm0eDLPw17vYPuGeqYdHcs5X/hfvOS0eU7pqicdshUv42JpxvwT13H/s0ENZ6KQf7JMGjs8YdLLjCu374dWvhkSN73d3Qm7l3N/iN5zfa+flMBz/dQEPc+mC1d6vgsSDTd8fKXaPNYpcrx/u/1T7/vnj1n0rlzb42Z2w3Ru56tbQopOfvg5ySLrquuncjM+Pd25joX1/9TW5+qS2KMUt8YDryGVXrsUOvJJz4D/2Ka75hsu+y81yDA/Qq4n2rbS222q7OWVHl/yyRYaHDwt75Y6bN2QUjpbXPP/fvj/fHz90qvLsKxf51jnXOy4ZrFz11d6ovD5RHoeiYz/OnHX18eOPsjbkTjKz3dG1V8aiZNPDyvby/N33RYe4lKDZvtuqd2vf3wAGLPnTU1a3W5Oz+pjzsdvlJ4VYn7M9V/fITwpvdNvaVP168KXKvqZ/hF/u7OfmerJ094Ojy/wErXkdrXldrXm9Lalp/ZJLfF0y8z41HVu0QT9uXsDXP8TXucZMWmTR0PRf5p4FLupi61lJLdLun8RXmfdfX/1CU1oBlcyrwPIW2FVApbrBsiy4uuyuuwuClZLvNBO18pqWlJpWZOT1S/NRm1qZ1xTzkVn24adpj1tRVtrtdc+cmf9zdwW73vt90Pifx5kzM2fOnDnnzAwdH25e9daCTya9b67fcGThxl6jVx+KK5pfMi87bf7d2Z9Fv3Tmk+mjjv3aSazMWbPim8CvE83ur+t+GRO95fH0Fya2vt7rkca+5q83lPZ/c2fGIl+fsy9dP6tlfdOBkU1LfCkvzCm8sHj+s6N+um3px6P+dOuoLX2Gdi/ZOThZr89c05gd2XK+JOnhcTvrzyaOuHfQ93d1nNh0a1ZTv2hvpwdO/LbSf+CXC2WmvCXLJ444GPHjb3r9Z/z2b2JiV/8yava9e9M7JZzO6z374IYFC6rT5+3qO7Gbu/qB4fv+Wny04oeU51dODFiWlveNv3He0O/3+kyLxmw1dprvyd755BXnXnwvO3PjqylXdrzu5416fWrbSdtTp658LWXu/o7vnfcM6XvNfEdm1dFX0ud8/ae8ASP27pp8/7F+a7IqzK923Trj+vG/3vTCwTO353zya/Zj5alf/fQ/p258tnDb6OcPD8vdcPjQRwOss/use+L0tq3zj5rrcsnBfh/tHt+7ZHLUnk0ZWU8fyDrke/e1Df9p/e0Py5LXJuc9mLPy7atvOzXb0Wft8hV581b3T1sxcOeka40bhWt/mJO2+DkhaVZ0dPWdbN1zcCRR3zf8jZONN7Y22tjObLzxxra9sW3btm3bto2J7UySJ9d13/W+9VQ9U/WZf6bq9Ok5fX7dp789Nf4275cT91iBDMjkRQubZmevrw1QsfFxj5eoJi5xH2+NXc1Zlx2cZNRjDlcnKpPU0++5jXvhOs70p0wqLftvkZ51Weq1d4H29WXsD1HWlpb89xqi+2WuNNYhXfu9Iq5kYtYXG2zuU0feC0vbHA4Dzu5p7RknAGKT97bDaNnozsf1PNc7rAvNO2O3zNLlG787VNeYrNG50GF4dbLv2xb3DqfsbRCxQ96kBs4T/o/p0ndE7k47gWG5sh86Z8V8HI78BTKU7F4exY6mho9xBICI6JNHxfOEympE7Q6n5pMT4HKnvtQlP5uRcL/026/kQqusZfmGk/fC0PkJE9mEgoyJFWaPNzSDrhF3u0kVMX2+6Aopz4Y7jqtBgleGm1Yx7uWt5X2p1z7Pqn5J7c4H6D9oVm3FFJ20uZ8wiOO48SqIslx1TDews4WIbQ7BYjCEm9wOx8Wp9U+bB15Wg0lize1tk5trn5pDSWCGhsvu6e9tDonaRETsHq8sZMZiB7zNbla2Q8XvQ1l4/NzimUtnZxwfjXdSGJ3qJk48L3Nv9cZpOlFetssRREQpGQyaNwbCV0alLE7R2ouOWgv7yRrdAIfh0ihvLzIKi4sjWaQ1vO3Po8/0Lh1Wp78Zbt2TEiEs5nMigQaLJxMLpPHcVlw/SH56oJMk9Kjwfnf65mGhXHfF+6ytiop6wJF7nS3I/zGdsdyAGN8QNGjWJQAjdCb/KUnRM/DbHRGWcg5AJTwklBV72uuMstu+zgMrCKQJ4AYcN6GAa5OyEn3LfGoAu/nYOPneu0/hZ4uNGjAa85Qv8IfbDCXAGztg6ZMNdkgBOhdnj+6aDgybbKH8E87BIoQjg43Kd9/CzwniCvwcbibf7FvLDyq0IsEOzPvbZmKkCw1TImKCFeQWEtbf3NdwPT3NLwgNiNeIMdbgKcawlay/eYyr6jcRDEjndQUvId89OFEzYuhd/WE1Xqc+9O+TosWKfJeAItnQJLMq5lZ+FDm9RVPd24R/JPyu/tRAYdYyIO7p5yAeYLVVFMq0HzuHKxfPW9W/XugXds5dVGKMb2rXTlw6KK536pspubZu4sF7nuGK//n5oLYlLwoY2P3F8OhCQA8oOVXooOe6vFEesW1fphke73RihfxVy3U6nNuEV497CVa5Pcpm1phluXw8RLq8nMpO25d8uv4zYMrSTwdV0l+vuFRi3ZyBNUg30wN3Ot4rrbqRvH6FQFyWthhQHXXAFq+vG0WJfEIcvMTFuG2v90Ho36oJ3fGAFcLRkyFILAtB9NvUFfoIs6vSAsyJ70CIG86vEHWMHftfVjoljmFGQ6EYWePZ4B3hNXQBhE8+YRfm2iV4D/y2D8y5/IhFGkLTiddO+uDM0A//f59KPeXVQjrEDb+/5cGKf9u2Qz9fLm981vjmHUrJ+wEty/jxEKsOEo0C/IuAfTq71kAC+xjdvVmWRRraBprTffyI6j7hRHXSqZzwt+VpjCV/Y4FvzZXAYBDqzsdwTWC2BUPJC1tvHP1J5DXf00X7O5ui/hNkCqPQlerH/gAZskj66Tbr5yBk4UVVn6dFlyd94edUgt8Se1eDZ2linl/0u6S3g14LXY10QyyAtWR3R5NTW2mJMRPWgpggBeref+Z776rSmT/j5c++5yp1V4NcIy2v7o5Sd8hjZN9zo7ohWLtiR5I7i5kbFx9o7fsRqd9rvMGPrah8y/qq8NwQJzFwc5Q4xj1wXN+RiIrOORm0C/RxTr47FHbX/p0e4wOYR9SmVAlnM1WKeOJaN5yXcpCyH+vEDpR4SKP/yr43+LDbzxGA
*/