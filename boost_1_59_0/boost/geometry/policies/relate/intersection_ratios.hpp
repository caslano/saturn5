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
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
*/