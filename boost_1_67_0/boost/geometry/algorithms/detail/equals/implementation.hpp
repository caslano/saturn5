// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014, 2015, 2016, 2017, 2018, 2019.
// Modifications copyright (c) 2014-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_IMPLEMENTATION_HPP


#include <cstddef>
#include <vector>

#include <boost/range.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/equals/point_point.hpp>

// For trivial checks
#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/length.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

#include <boost/geometry/algorithms/detail/equals/collect_vectors.hpp>
#include <boost/geometry/algorithms/detail/equals/interface.hpp>
#include <boost/geometry/algorithms/detail/relate/relate_impl.hpp>
#include <boost/geometry/algorithms/relate.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace equals
{


template
<
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct point_point
{
    template <typename Point1, typename Point2, typename Strategy>
    static inline bool apply(Point1 const& point1, Point2 const& point2, Strategy const& )
    {
        return Strategy::apply(point1, point2);
    }
};


template
<
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct box_box
{
    template <typename Box1, typename Box2, typename Strategy>
    static inline bool apply(Box1 const& box1, Box2 const& box2, Strategy const& strategy)
    {
        if (!geometry::math::equals(get<min_corner, Dimension>(box1), get<min_corner, Dimension>(box2))
            || !geometry::math::equals(get<max_corner, Dimension>(box1), get<max_corner, Dimension>(box2)))
        {
            return false;
        }
        return box_box<Dimension + 1, DimensionCount>::apply(box1, box2, strategy);
    }
};

template <std::size_t DimensionCount>
struct box_box<DimensionCount, DimensionCount>
{
    template <typename Box1, typename Box2, typename Strategy>
    static inline bool apply(Box1 const& , Box2 const& , Strategy const& )
    {
        return true;
    }
};


struct segment_segment
{
    template <typename Segment1, typename Segment2, typename Strategy>
    static inline bool apply(Segment1 const& segment1, Segment2 const& segment2,
                             Strategy const& strategy)
    {
        typename Strategy::point_in_point_strategy_type const&
            pt_pt_strategy = strategy.get_point_in_point_strategy();

        return equals::equals_point_point(
                    indexed_point_view<Segment1 const, 0>(segment1),
                    indexed_point_view<Segment2 const, 0>(segment2),
                    pt_pt_strategy)
                ? equals::equals_point_point(
                    indexed_point_view<Segment1 const, 1>(segment1),
                    indexed_point_view<Segment2 const, 1>(segment2),
                    pt_pt_strategy)
                : ( equals::equals_point_point(
                        indexed_point_view<Segment1 const, 0>(segment1),
                        indexed_point_view<Segment2 const, 1>(segment2),
                        pt_pt_strategy)
                 && equals::equals_point_point(
                        indexed_point_view<Segment1 const, 1>(segment1),
                        indexed_point_view<Segment2 const, 0>(segment2),
                        pt_pt_strategy)
                  );
    }
};


struct area_check
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return geometry::math::equals(
            geometry::area(geometry1,
                           strategy.template get_area_strategy<Geometry1>()),
            geometry::area(geometry2,
                           strategy.template get_area_strategy<Geometry2>()));
    }
};


struct length_check
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return geometry::math::equals(
            geometry::length(geometry1,
                             strategy.template get_distance_strategy<Geometry1>()),
            geometry::length(geometry2,
                             strategy.template get_distance_strategy<Geometry2>()));
    }
};


template <typename Geometry1, typename Geometry2, typename IntersectionStrategy>
struct collected_vector
{
    typedef typename geometry::select_most_precise
        <
            typename select_coordinate_type
                <
                    Geometry1, Geometry2
                >::type,
            double
        >::type calculation_type;

    typedef geometry::collected_vector
        <
            calculation_type,
            Geometry1,
            typename IntersectionStrategy::side_strategy_type
        > type;
};

template <typename TrivialCheck>
struct equals_by_collection
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        if (! TrivialCheck::apply(geometry1, geometry2, strategy))
        {
            return false;
        }

        typedef typename collected_vector
            <
                Geometry1, Geometry2, Strategy
            >::type collected_vector_type;

        std::vector<collected_vector_type> c1, c2;

        geometry::collect_vectors(c1, geometry1);
        geometry::collect_vectors(c2, geometry2);

        if (boost::size(c1) != boost::size(c2))
        {
            return false;
        }

        std::sort(c1.begin(), c1.end());
        std::sort(c2.begin(), c2.end());

        // Just check if these vectors are equal.
        return std::equal(c1.begin(), c1.end(), c2.begin());
    }
};

template<typename Geometry1, typename Geometry2>
struct equals_by_relate
    : detail::relate::relate_impl
        <
            detail::de9im::static_mask_equals_type,
            Geometry1,
            Geometry2
        >
{};

// If collect_vectors which is a SideStrategy-dispatched optimization
// is implemented in a way consistent with the Intersection/Side Strategy
// then collect_vectors is used, otherwise relate is used.
// NOTE: the result could be conceptually different for invalid
// geometries in different coordinate systems because collect_vectors
// and relate treat invalid geometries differently.
template<typename TrivialCheck>
struct equals_by_collection_or_relate
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        typedef typename boost::is_base_of
            <
                nyi::not_implemented_tag,
                typename collected_vector
                    <
                        Geometry1, Geometry2, Strategy
                    >::type
            >::type enable_relate_type;

        return apply(geometry1, geometry2, strategy, enable_relate_type());
    }

private:
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy,
                             boost::false_type /*enable_relate*/)
    {
        return equals_by_collection<TrivialCheck>::apply(geometry1, geometry2, strategy);
    }

    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy,
                             boost::true_type /*enable_relate*/)
    {
        return equals_by_relate<Geometry1, Geometry2>::apply(geometry1, geometry2, strategy);
    }
};

struct equals_always_false
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& , Geometry2 const& , Strategy const& )
    {
        return false;
    }
};


}} // namespace detail::equals
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename P1, typename P2, std::size_t DimensionCount, bool Reverse>
struct equals<P1, P2, point_tag, point_tag, pointlike_tag, pointlike_tag, DimensionCount, Reverse>
    : detail::equals::point_point<0, DimensionCount>
{};

template <typename MultiPoint1, typename MultiPoint2, std::size_t DimensionCount, bool Reverse>
struct equals<MultiPoint1, MultiPoint2, multi_point_tag, multi_point_tag, pointlike_tag, pointlike_tag, DimensionCount, Reverse>
    : detail::equals::equals_by_relate<MultiPoint1, MultiPoint2>
{};

template <typename MultiPoint, typename Point, std::size_t DimensionCount, bool Reverse>
struct equals<Point, MultiPoint, point_tag, multi_point_tag, pointlike_tag, pointlike_tag, DimensionCount, Reverse>
    : detail::equals::equals_by_relate<Point, MultiPoint>
{};

template <typename Box1, typename Box2, std::size_t DimensionCount, bool Reverse>
struct equals<Box1, Box2, box_tag, box_tag, areal_tag, areal_tag, DimensionCount, Reverse>
    : detail::equals::box_box<0, DimensionCount>
{};


template <typename Ring1, typename Ring2, bool Reverse>
struct equals<Ring1, Ring2, ring_tag, ring_tag, areal_tag, areal_tag, 2, Reverse>
    : detail::equals::equals_by_collection_or_relate<detail::equals::area_check>
{};


template <typename Polygon1, typename Polygon2, bool Reverse>
struct equals<Polygon1, Polygon2, polygon_tag, polygon_tag, areal_tag, areal_tag, 2, Reverse>
    : detail::equals::equals_by_collection_or_relate<detail::equals::area_check>
{};


template <typename Polygon, typename Ring, bool Reverse>
struct equals<Polygon, Ring, polygon_tag, ring_tag, areal_tag, areal_tag, 2, Reverse>
    : detail::equals::equals_by_collection_or_relate<detail::equals::area_check>
{};


template <typename Ring, typename Box, bool Reverse>
struct equals<Ring, Box, ring_tag, box_tag, areal_tag, areal_tag, 2, Reverse>
    : detail::equals::equals_by_collection<detail::equals::area_check>
{};


template <typename Polygon, typename Box, bool Reverse>
struct equals<Polygon, Box, polygon_tag, box_tag, areal_tag, areal_tag, 2, Reverse>
    : detail::equals::equals_by_collection<detail::equals::area_check>
{};

template <typename Segment1, typename Segment2, std::size_t DimensionCount, bool Reverse>
struct equals<Segment1, Segment2, segment_tag, segment_tag, linear_tag, linear_tag, DimensionCount, Reverse>
    : detail::equals::segment_segment
{};

template <typename LineString1, typename LineString2, bool Reverse>
struct equals<LineString1, LineString2, linestring_tag, linestring_tag, linear_tag, linear_tag, 2, Reverse>
    : detail::equals::equals_by_relate<LineString1, LineString2>
{};

template <typename LineString, typename MultiLineString, bool Reverse>
struct equals<LineString, MultiLineString, linestring_tag, multi_linestring_tag, linear_tag, linear_tag, 2, Reverse>
    : detail::equals::equals_by_relate<LineString, MultiLineString>
{};

template <typename MultiLineString1, typename MultiLineString2, bool Reverse>
struct equals<MultiLineString1, MultiLineString2, multi_linestring_tag, multi_linestring_tag, linear_tag, linear_tag, 2, Reverse>
    : detail::equals::equals_by_relate<MultiLineString1, MultiLineString2>
{};

template <typename LineString, typename Segment, bool Reverse>
struct equals<LineString, Segment, linestring_tag, segment_tag, linear_tag, linear_tag, 2, Reverse>
    : detail::equals::equals_by_relate<LineString, Segment>
{};

template <typename MultiLineString, typename Segment, bool Reverse>
struct equals<MultiLineString, Segment, multi_linestring_tag, segment_tag, linear_tag, linear_tag, 2, Reverse>
    : detail::equals::equals_by_relate<MultiLineString, Segment>
{};


template <typename MultiPolygon1, typename MultiPolygon2, bool Reverse>
struct equals
    <
        MultiPolygon1, MultiPolygon2,
        multi_polygon_tag, multi_polygon_tag,
        areal_tag, areal_tag, 
        2,
        Reverse
    >
    : detail::equals::equals_by_collection_or_relate<detail::equals::area_check>
{};


template <typename Polygon, typename MultiPolygon, bool Reverse>
struct equals
    <
        Polygon, MultiPolygon,
        polygon_tag, multi_polygon_tag,
        areal_tag, areal_tag, 
        2,
        Reverse
    >
    : detail::equals::equals_by_collection_or_relate<detail::equals::area_check>
{};

template <typename MultiPolygon, typename Ring, bool Reverse>
struct equals
    <
        MultiPolygon, Ring,
        multi_polygon_tag, ring_tag,
        areal_tag, areal_tag, 
        2,
        Reverse
    >
    : detail::equals::equals_by_collection_or_relate<detail::equals::area_check>
{};


// NOTE: degenerated linear geometries, e.g. segment or linestring containing
//   2 equal points, are considered to be invalid. Though theoretically
//   degenerated segments and linestrings could be treated as points and
//   multi-linestrings as multi-points.
//   This reasoning could also be applied to boxes.

template <typename Geometry1, typename Geometry2, typename Tag1, typename Tag2, std::size_t DimensionCount>
struct equals<Geometry1, Geometry2, Tag1, Tag2, pointlike_tag, linear_tag, DimensionCount, false>
    : detail::equals::equals_always_false
{};

template <typename Geometry1, typename Geometry2, typename Tag1, typename Tag2, std::size_t DimensionCount>
struct equals<Geometry1, Geometry2, Tag1, Tag2, linear_tag, pointlike_tag, DimensionCount, false>
    : detail::equals::equals_always_false
{};

template <typename Geometry1, typename Geometry2, typename Tag1, typename Tag2, std::size_t DimensionCount>
struct equals<Geometry1, Geometry2, Tag1, Tag2, pointlike_tag, areal_tag, DimensionCount, false>
    : detail::equals::equals_always_false
{};

template <typename Geometry1, typename Geometry2, typename Tag1, typename Tag2, std::size_t DimensionCount>
struct equals<Geometry1, Geometry2, Tag1, Tag2, areal_tag, pointlike_tag, DimensionCount, false>
    : detail::equals::equals_always_false
{};

template <typename Geometry1, typename Geometry2, typename Tag1, typename Tag2, std::size_t DimensionCount>
struct equals<Geometry1, Geometry2, Tag1, Tag2, linear_tag, areal_tag, DimensionCount, false>
    : detail::equals::equals_always_false
{};

template <typename Geometry1, typename Geometry2, typename Tag1, typename Tag2, std::size_t DimensionCount>
struct equals<Geometry1, Geometry2, Tag1, Tag2, areal_tag, linear_tag, DimensionCount, false>
    : detail::equals::equals_always_false
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_IMPLEMENTATION_HPP


/* implementation.hpp
jt2YyU+p0MbMySDzEojDZaVADWsP7mOF1/fgzr1EfcOCX0SMEhRPxN2eTke6+Rg5+cF+FCVZOaQcJ6jiRijy+JW0Gny5ygnzhoW0XVBJ+QCAr4MdRvVK9Kh7A3Ah50C74lv9iglrp+GUV0U40sBNJXEIXbRa/sLssadsgupT+YYwjXZtDD0uc+fRvjgCJHk5nfyyFPfOHceyYnVgNuQHRzxo3WA5Hs/OYaNsu6OgNdN5R5QpVB2sTvcXly6wBFbYxmewJQnTQusBZeK46wr7bN+SkiPqIrfVHqRpmbA7pa1+Jvd8rJhlK/ci4wPqAtJecEs3XIrH9FgMwacTOM8pkbJ5uieyLrSB4rRLtWh5Q6qGlryUX2M8evEVPBwbT11NLBFURivemEU7xE+66PXym/Dx9YVTPk/Ua5p7zOUwsGSjz6z6Yta41TeabsCMzdgHKR5mn5Un9AGZbS+NnqHgixZn0FxsCPwSJVG64PA6gwbj8Q/z4g90WNXwCnZb3BYXBGsyatylIcyREhPl+2o4fga9NSjQRT3EJBDB3Sd11hK1eU03B37hk86H18BXiqmse07kAIYawoH2A2KUevJYHRqu7CCWbhqN7vMjNBxDWx9PkNoNdGPjMRuTbWxhfE6dtcRBmFu16w3FQOzaIpA6fRqtq0jAfpOY7UbzlJo8TbI0fVYxNTA+3JaGzEso9cfPhAFBGm2DHDg2feNVqtokC8pry21kWkkDQK7VSdt3LD0GXjfqHIXB684YpUH9twS/QQaO2nCiCZ6IQ2D96yt+zJfd7CkIOYTMMNhgiUkqSY4Ly44BkT2bxD9y6b7Eg5z4EPap+DNtcGFMWh534y2j4VVJ9xFM1artlfk8TWD+K8m+BLh1fnaLU0YUFUOG9Jj2T4VCVoZQ6FMqed+wWze6nB+iNQSHRzpGfLSKIBE+OLmONs6hjsDvlHkfqi8eXc4puXazQExx0AhdsEGWU+AoKs1xQBgeQ2GTFf7a2wO0q5ruTJiUr1kSaamQPtyP5qkqIu9YC3FdzcJmEJnWjB6rfQ85txsFty4W9vyqNgvSbhvHwxBXBUmq51Tt/XRJewo5DxjGt7y8ReSXCWJZ1InKLLxU2PylfljloJYBuDjAytJAfHI9Ry15LXnWwecwYksTSiiVO+jBQ34L1x8XqcYTL+Cu3pOwJUNutCMDsTsxaFEgFE6BUk0RIVkFYQqZCwCaKmD6vqhUAF9hUKvlRJzKUdyJvGxbsZJPuEiaI1Sysywy5gQg8xUFYQwHSH+nsdVp1AqZdstLJMwob7eEt0UjjITgQg4riFAixg0NG9upZp6j+qfrxFSrNb4JNMrw1WRsAcsHh63NqQfCiz/tn0CfwuhRHUcbzmIkjcsTg+bCCAPaLg7kKNoK0QdvyTWWxiISM7XGYRFrn2TxaSiPAE9uZoO0tj8pSnN8pKspHER428llhtoOmsJr4XbhJCTtZ1Pi0T5q0fTbh3CwCulKvfQNAAnK1Yk1vsI2rxSTIV+ur4su19UkOA/NKS2XN3Q2WkxzU7pSjuzG+GhIGxI3z/58ctjF4jXTkuQc8TZNYfZcQDgqQwAL+AZ0EG1yjbKSP9TQ2k7NAMXSAjlj8ARkgpnQHYTycZJJcUq6hn76vZ+DZulqoCbjRmbOVnfqzhYSxzSyWnhZLzzuLqPSY5puYDVvpcDjPZGYjmGO6cpRVsX/erHHyy362SF7XIzvimXWxz+6KqGlmSOY1ZSy9OwUHWR/Lhw13+Lq7AKuZ52WcxnAX9fPXdeRYSPb/mJPFq+R9M3ackvlsrFoOgIVoV8tO9gZpwfVoVuhxSqnFZ3+ed6R53glATIX1b6w9h5HOajD4warsGPxSbKE79G+TtdURmZPmKetiTdKJNp58kX8AzjdJxkS4HOIKFAusV56NrE6j5H78rX07uEQJoM0VTU7szi6CssmwcmM0c4XYJfkzSc01FC0DXdqxGFZAO0kaPphvn2YWR0SS982WCQDGAGFgYuQ0sgiPS9QwbZlUKQJAzqYlnaza23DfeDjehrdXeR3EgkhNYJdTNMsOsJ8vnDxtsR2+Ye70OrkSQvGeXdYQ7bFpNpPKio9z46tSwS+GMTRuV6dfPjo31nCHjzPvNvf3gXY6qYW3aWvxZNeIXy9E/auxY6x6ugvqoRHVbFUY9pZxoRN/g1IN0gb49AL/dIdcCkK44dRsru6P23rAsHxiH/7ZDXGyhuWskHVBYnBgDVz9IIAoaxodq26NR7R2RaBFfxwZP9ybOualPZmarNHdIHgvE3wl7t+XBNuZDWCzih6h1p1MIxHGTctyrHHTPXG7v91LDU4LTCeUydjHsTfeX44lRNWx6UPQ7FEFFjorFQcX3aJGO35oMbRRyjg6Z06se7OaKOtqQZMCpGhEtKYPjVxjEaisweWmuermbZZcJEanH1yQCwnI+gDB+pAoi2CqDUPDKtbFF5OiWSOKIlX+Ho0fhJPB6CH3i4boZUpYoH2Ob5fZaDuqTSboFH70Hdu70hDdn10NcnRS+UyScr/LMETu/O14eUUfwloCrJB7KnqXD9sIfjMyONXvCwa6Fi/PMpAbE8B5AP0j1POSAPico8EmoSLvXcaQwFOsMhqNaUDyw/9m2908Y9CBcFNjvsuv2lFm9xfr6gG+3vkG2lMEaYuX4Y+acuTOm28xgpFIc58BStZX3HFMD1A4EQBg/hMCJKYgbiBCJwpquEwypyAlYl5QKgIm1TFC/RhPh0D5mOUYcL5zKYvIQdqeGyTdbYs0og8wZL9hVx/YcOOwBsh2ibSf0WUXDsnUAbgRvEHhd30taV2+gRTeSUVu2Fl6z5HrG41wNVdF5LpSPtL1+YfClLiBSBsW6u7ZSpvxAeq3QBzZw+0dxpTXvj9DCGYHQswRvfzWg7QlgqUkcIIoxsbHG3BO53dOJeUb9BoXeF0UT8exUM/sbhs7it/wuKTYuuDexpV2cqZA5zLSAOZ2Fg/d9nIJslXS5093CUQ0QjsyaVCCsY0g72j9hDhdImlz/iT67+3flhYx/KYYb9WoPdM0BKRNlR4Z2gjeCqbQeCf8Jxd5JqTKIdajI7zK28zHPTJgpHrJRF+jrl6HfQwSvwkQXXxbAGm6ojc4ddn1UEx5qjOoABX9dv9lbEKr0oWlZH0l1dxMQadxFteLV2ODPBP3/N0qaySyDJ4Hh4iYPIazf5+IcNCxe0VNAsMVUhn3kjxuJ4L6SEvZEiZU5bs+lavc0v7dYQfHMbICNUvgAfNG1RMWMQ7KYApwFCIAz5wVWlJK07RdX1psWEw9wuhvwxWnPDHNqm0RUbCEh/3cXlZp9wawFWw56h8G41U/TnMKjUv6YwrrtMQMJ/PSXD6S2Eprn021ZFduXeZ2eoGndOP3rLMEdnpplv4Vv5FcmCLYHGSwTZdgLLwLXKwOkFOE/EovbkZWHiggZBQ4TLZYWX0FU/eZ1jz6K/zcDpWFwyH99Wx3X/hcDX7iehScgd5wS01XucpO6TS8b5XKDuM/rwj5dRfGTNcN7jtFbAaKPQZNVDC8trdUE7EyXr6JB/9Jb3mVWbGpOxD1/gLajs87NsyWd8JPfTUQCkjQOedfGREyunYTko3S77UImwDxOyXBWyxcOjm6tUOvecCEzbCzQyVzjGDUYt7mLagt0BzssoZctjJtumeTRUQOs9vkpAe77XFUGpK3YCnfgxdPzkTOavWkc6MIEkQL73W5gqLjLuekvgarPdMd+kucahxXRjkFtTon54wljp0cKghmLsSi/3C2Dx24HuNtZH9U1ukXdnu1Ajd7PYdFEnbmYFz9U0kBgULpPcKKS3/feRDPZqwdNPrhxvINiiGpzR/few0mZS1d89992jhJUy0G/KxO5adQL4X4hAQCSf5slJE+2mL22F7pbpsUqnuOj0I+o2utbTszU8hf9hFIMPpdAg1G5YA1QQ7OqTxvT1y6RcXeeaMeBSTZpoaNCmcL8iQLV2i/1WV0o9xbVKpV+djUC61XvzWDkjjiTadHB6IGjzDp/sywGPM7SjreQerALazmwPgXdb6xGEv6P6Ojv7XMk8iJw04emq9eew9HGv8/ScQ+Xtuomx13N+ZOII4/TMk+5nGkYzg67KEtIDOtpS0mXfN3YUxkD//SY4bOBPeRvWh2gzgzHr4WLn1M/R1ROIxyEpktWGkLClHmLAknuAzq3xWPDri7ofW6HrI3QzGa/zzlnzR7Qi9+tGlxC7LRBfnHn04nbzDzOsxFUjIVAzVLoWC6qk5gliQ7pBzwL5E6UV8Mf+IpaxZ8BI0ATwGc8Lcg4mqQEt4JysZNnjzKsdXKIZdm5Exh6WZLRlRodoBZGhOGvbfoc6g1E9gE/1E1mi8vpHb1GR9cgNvSok2sXURZVMVRa2W7aNQoVJES7jqR9WmPJU2Rbh5NzBuaS37p3GvVQThWUfos8iCEethnVTgyXZERolc2UzfjMIUCjD0CfTPO9Eqi52Ez675VR//3XOOFrPZPyDB2boKLt8Iy4CFotHuKYMKiXKYFv49LKSfToIxYmZLQJOq4b9GBKnLRZbsMbnY+2lGgwMM5EaODeTptOU7ri1xf/ZO5OEmUtQfpwXvvQtSVRBWdTqWZRkEMDo+5x/R0leFIlNPRDg2tPHK12ktil0pmsUFu/f7F29CHKmL2ok7QaSn94YVOuOrJPjRsBjMc21yG9ML9lXbo0//YMNMxYjlG8tFNJGVTuN3fWLt71O2fuLDSx+4zAJAhkDw6TcrrbRqiOcFxT85tLzWHfzj9hk0TojfIexALmFNLYIVmhLQMJ2iG59mb5WNYRi0py3kU4cTcBHbx6qgpBo6Qhcwj3KQGbYgHhmd2UP2Oh6OYqRnYKkX7JhzTYdnCjEkUJI4kTDlqbpNZKoMMkTedD4Lu0qyg3D9mDZnUau23G4tjfyr/m/jzh+0mJyX9vF04yh+bHG0QVSiYiaS1ZVYpwMJRouQrH3TYmp3dI6qg8Dg6J0om9xQVUhMmdZ8KwTFUMYeGg3yqcS3doZ7J2/HNmJcNq5UkZzc6LpXbpoOLuh7RgeagHbwuC6qPmPSij0abKOoL3xRc0F87dmujAoNmYnJ6CZ0lmuNVrWLa/G0nkKhTsj9WEDfQOs76CRx/xaqo+cwk55pe7DxU3OXN8Er2Wyns4ZO7CZ3DX2V+5yNQSdNEan0rdtPlBk/0JW830q2d+yKJ7q6fVYsEKcqvLvFpWIKQmE02R92pIyEIDuV+Q4e1gLRhg74A+tZsCnMxiN/XXDJwNqlcKQxDK9Zs5aMOBhlefL9z6h6MbaDP9yzn9pngObxGLTiMZNyWoE+29kQLpzLcWwcuNYXkHKJHwKJS4yK+9HZAgzigFteBEy3tWNb3ubyfBVEMoUEHMouczpH8XzGkGHMZqRAjH0CwHpyDpSsy6pJ7O0DM9e7zy48F0hRd+iLkOd+iExcpx9XNU0VV7XCKsels4ObAb/NXavKAlE3CwZGrHG9cff1qJdmCktluyWxuWsDvLEvoQBZg6ESM21/msU415N+4oYlAqzScJGHsWJ+HaahJJFdjueZURPVQJFG+Tf7qDej8mLjrOApmV5DJtosJPeUvqF8cNRV3pqavd9asOLIzbgvvIuqEtUQpkzM/m9PqmMS5gXUIogjYi0g9PngYCpOXpJ21SLMzv1JoxhnFZFbTWFPZRygYWewQUtTV09KggsERRipNZdkabakU1Y2ElWAqi5/acJT70zudpt641XlGaJcT1JbQaeW0TKCxdKxObUDJAezppTig20JtUm1osC/i+3iMGodFQiCBdEBeUvAhVV4nfjYAJvyNz31Sfl7Ev2d+70dHWCzYa7/cCPvSIjZyd7UbbZYEorp+VZY+oD7lCc90/2tw+9+gWI4ZMlrTxjPCX8kKh5nH9JGUDis07bdyv7NTHxh/OBT58lrzFGt/iStjyHPw0P0rz4k6yKFPaqG6E0TZeEPmnuitjbCb3hrvOJdDFFdSaG/d7oAP0izEC5sPLppfbtxURCXW2tZwZZ+YFjPnWDDeG4rpshSrar1wJH9XfjLNiG242COvkcvQMGDji7FNrUIdeVxuwbsS8x1aO3nFqe9fURzY9fy71Fy/yGxISXE2+3j8N4r4aRJBBKic6GRSNO4ZJ7N4PCl3q3Jjeu0kvNxjNuyCysoz9fSwuWBozW1hWR50M/thjlyYSLmz7ZFOuGGE89S+YsOlM4sohd6JpAJay1YNU7MpjHRRQdxSifHG7anZ25APUtbOGuBRMZeqCa8FzG9uDhdrS/0lgfCsnQUyVaFnkdv4J0tjIgHexHTs1lUiRE3j0YHgFpaVIe4dDm6kfrBGK+JAH3Shc1mnmYNSch6z3NKaLFhl+Bp423uhaJVMMPsnCNkk13pAYV5EiZcJMyaNB4m9PwCBgJpTsR91Gz3CX/3DRulTYqd+9gYQI/C1O6dAQZZMuwcNPqEzQIp2olO7hlFaPg+mpp72wKG5pZesCc4jHPEaFNlkP0b1KSTTUEcOpewjRYQ8vAFZG5DivbWGAAXLCoqBl8ywmBJAucAPU2XqnGcO8GRhVZvB+L04XTudrjJaWD4GHi4CQl0T1Q/sQvoUM7rtLybib2JWn9CG99dwKmXmwL3SkcI8r9MS2SKikEVTZIDJxScPBnUtTp56ixsoQizBOovvCC+Oz5rfieDlqADhBzV4T4F//20zdWQQWv57dxVmRbj4EjCl3MQ3y6QZRoq3hLNgzplnQFgUKUQp+RrnUe8zQ6kK5LkW5SMiye+gUaKxmMothe9+co50VeAlp719Jdhve2PxTFE/wCUWPTBG55wTWLjKv+IPjayTwudog39VA8nt43GDo2LodknrHklJ+WIHZdn9MZAd23yVBYRKd9xmTDMmMJVU6tokFdeMmY7kwDJHH2HOuBx6GKRLzSTxYJuEuiGorqkr7MOVQhw4xEgK1Fc5mVujqcqXa5HtocnttfML/O4s33naHPKHDWqL6CpMk9oEbfdVoZLiP6682xVfoqXmJqTpA5rHbeWFdppdCZhWp77+Ok9wIB9ulfxW4eYiXvh2d2VbIBNGYkWelA77Hw9lMaTtvO5Ft2kfB/K4ONnzMVVuSRDdvw7bAQWTklDuqLaMA5SEZqiG4DOQ7y7AuDZvaWX9O8oOHKCERVn/4HlU53QbQIvYRvf0qIGQ9yDI0rOfCpCu2daMEDObbV5YEviU4b8KkdEJI6W+ohWV0am8PZ3lrXhWtqv0OXpj8GKgLPmUbzB86GlEIFQ9giaohbvhG2MH3j0T7uQweY5aw0jVS4icQp4ieQSP5rAAHsFeGPooS+TeatL6MqUHCQfiKKNZi/3AvmeDpWiQitIEjJlLF5WF8sK0LCv/ghbxXX+vjiAGEwFczYE3Q4FYSCsXVFf8n5GnFxKrL+3VHDaUqnbtW9dia2iviRTor4jFi9bIb4+R7iPRMJAnNoUr8KAO7X7jNZwE94p1hXHvB5L9NPaScged7uy4VTuZ7MJdTlBtB6i8D2sqC4Map8+JvKhm8+nkBvwJXJbBWVX6e0CCi198Xuky0HnelJc8lrY1DyTqkI52V/pyXMkBXUYdCXfmSUifevqDcDdSsAnny2wCmdHQKWbkR6M4Pvd6wUly9VfD/rRzKqjdgAS7qzfI/ym9eTwb3e6VRffHXoDNbBhszKluMls5hEKZTXdN7ppS7LVuSmR0FYXBqU6+xJAAjbQBwkpEeZxL16UXe0I/sI4xHIkKIz2wAVkWk8dj4G5cf2bsW+xq8j+wvalAw+QuVIc0Qs0KLazo/UXk7lxN+EmKsP+wt6xJvASWRYbl3KCZNyXgdgG9GcNo4dpisSIzlEE5HHdGWCDITx58CyG9KQlszBDCWEKU5V0i9wJovY7CYL0yeeTY/GCwg72xCKh3EHUiJ9RbzpeVv8WwQh3vIY1ayLDSR+re/tUPSYvEVNoQsmhtVi3qK67k3kU4nlWT5gxR322mBAAaijiPjnkEQoSzSE9WGXPVmCHQvqR9mHBDnokoTABGmB19AFeYSZqNFzjA8K6NUzAcHdpMh1ABcke8aJPl1wFQQc+iz9nvezq+Kdmc1i2kK9mLW72XVNjNAk4GKk0u0v8hc1AEP9R8sDBMtzEE3m9f5mK/R4D261KHnRwE5FaRwBYiLAr03pYQYh3kolRNqLKNgWxZ1CVsjlfTxi4HIXh47JuQ5KXdgbgiOK3ljyL0IgIKM9DlHmGjGrDR+i9VdjAfZ1FiTg2QbpfJugek0zRAWz1XjExgr0lD0WVOHIMJ/joxdiz7V+9rxjw9pElpby/wbBRwqQX6PdXBIDq0uVfeP442CLLGb/lADuRLjzdzGbpLOtHhdVwQaEl6FBL1aMINjmjM++Fis+f6HVBw66siQ32LegPr9FERjA+9mdvl6SytUR8EqdzL1Ev3D3D6hRmHAmTKHT3G6bP4g9A62ujI5vAJeCiHjwgxB2VUhWNfaouJHobZulFakEyJKJ/Wg2nG4nR79fFYAax1GlY73rkCSCkBb3kw4wDLdLVRR28ZYBFadfC2m0F4DRHBBRZgj/rdFEW3uv3RT7tHqnCakukFd4kRM//LcbvKgTOCkc8LxqBUYhoGi75BJMXThcuXZvvDE1/ozeLZlfxAObRBz3SP4KmWIx+R3Vl2KpA5SO6ZcfkxUEqgbVjDbPUHU5cPZDCBtyONys3qF3xDI2gj37WNnL/EJwCE+F3EJLkzwLn7rU2a+u8VevtgAZ51BH9UTjaD7mR97vRmSreabuFIPBGMJcBdyqcDVO+dos4QGCSpaC8NV76/uJgRnyw8mMhlUbxsVYUBwhM6Fx4Hc5ShKnyNpvTAxr1nkuNjm94yi+TDVlcsxDZgsHkCKFzXkPu1UnKhVs8pzbrZJdqtlL7aipdJQE7irYq5TZVuHtcfS25sFxaVvbRirc1bNVbVgRtKJZcVP0EX0JHmTFvZll5qSZt0RkvvHgnspOu5Ip2nfGjHrGd8eMWWQxr0nEueB3mu9x7bRert140OX47yVGuousJc1F4QzrW6Rs3D8iq141SIVBmqk0yKX6udPm7EQtGHK1LNfpkpyErPzOJglBpwdD0XFmpMRVzNxJBkk76YK7W9SfB1hPI6xsL08cbqN066hOgbLLRlMqpzts2rg5vRa9h6CSJ+HXQptRcHMOI9yo=
*/