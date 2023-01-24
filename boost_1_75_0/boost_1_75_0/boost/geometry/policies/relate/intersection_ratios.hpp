// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_INTERSECTION_RATIOS_HPP
#define BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_INTERSECTION_RATIOS_HPP


#include <algorithm>
#include <string>

#include <boost/concept_check.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/strategies/side_info.hpp>


namespace boost { namespace geometry
{

namespace policies { namespace relate
{


/*!
\brief Policy returning segment ratios
\note Template argument FractionType should be a fraction_type<SegmentRatio>
 */
template
<
    typename FractionType
>
struct segments_intersection_ratios
{
    typedef FractionType return_type;

    template
    <
        typename Segment1,
        typename Segment2,
        typename SegmentIntersectionInfo
    >
    static inline return_type segments_crosses(side_info const&,
                    SegmentIntersectionInfo const& sinfo,
                    Segment1 const& , Segment2 const& )
    {
        return_type result;
        result.assign(sinfo);
        return result;
    }

    template <typename Segment1, typename Segment2, typename Ratio>
    static inline return_type segments_collinear(
        Segment1 const& , Segment2 const& ,
        Ratio const& ra_from_wrt_b, Ratio const& ra_to_wrt_b,
        Ratio const& rb_from_wrt_a, Ratio const& rb_to_wrt_a)
    {
        // We have only one result, for (potentially) two IP's,
        // so we take a first one
        return_type result;

        if (ra_from_wrt_b.on_segment())
        {
            result.assign(Ratio::zero(), ra_from_wrt_b);
        }
        else if (rb_from_wrt_a.in_segment())
        {
            result.assign(rb_from_wrt_a, Ratio::zero());
        }
        else if (ra_to_wrt_b.on_segment())
        {
            result.assign(Ratio::one(), ra_to_wrt_b);
        }
        else if (rb_to_wrt_a.in_segment())
        {
            result.assign(rb_to_wrt_a, Ratio::one());
        }

        return result;
    }

    static inline return_type disjoint()
    {
        return return_type();
    }
    static inline return_type error(std::string const&)
    {
        return return_type();
    }

    template <typename Segment>
    static inline return_type degenerate(Segment const& segment, bool)
    {
        return return_type();
    }

    template <typename Segment, typename Ratio>
    static inline return_type one_degenerate(Segment const& ,
            Ratio const& ratio, bool a_degenerate)
    {
        return_type result;
        if (a_degenerate)
        {
            // IP lies on ratio w.r.t. segment b
            result.assign(Ratio::zero(), ratio);
        }
        else
        {
            result.assign(ratio, Ratio::zero());
        }
        return result;
    }

};


}} // namespace policies::relate

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_INTERSECTION_RATIOS_HPP

/* intersection_ratios.hpp
MiFvLLBCh0GwuvQyzDLfsK10rfxjdaJinqW8q1k2lPfqAqs18emznwAcJXHWRmhWv5VjIhbL6BGHRvPYi+JCh42hEgdF3vDAI8r5n4sRtxI55WWiLMZd7LhcoFMA4IcIpbUS9j1J5zYR5tDPxdmViCNh4pytViYiTPFwkiJDXU1tHItkR4OBm7C+ISJmqXcX3MHeKOT1sWvY9sMoDWsxZNUJwkPS+uEqU48rBFjfJUu6PDBD3VrDD2yuoh7MBNdtua4of0+euQdYNuWuL6714+BF+wApdvd4KNHOS2OUuKhWM+wsq7Q+ug0HWZoqPabqlFiIk2KOYaJqg62HH3rU0EGqNxWJlwLW1nEHDvxtBpQpqgcO17/Lgkx2c4dJD54P9H3b1zqxzm4kRR1mgA5Nct2CMaaZcWPP0A5Rz7nX6FllROjigUP/RQc7kLFZNAXrt3P5+vlpOBzLsW+5ns7q8sVbbaskqolYYFoqwPu9htF2UYf+xD4rslNa8FO5+C/pAUNbSJ7gvstLSjRDda2aRHHyFvEJZ68izhHrt4vmN4Ipa34ZPaueTDjKB+I/vspuc7RXDaS2GicxHxrblulpRknV47to7uWc/8YoHOsxoLXm3HeZf9twc0smGxgd+LdVU7icgWuQdac9xJpT8KKSX3Hqq8eWoiLda2Iuqz6j8cmXufGFNeNPnHCN2qcuHqHyVoxluG0ZWYUq3YXi
*/