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