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
tYLtjyu3JAwWXOa999b0nZvAiIf0lb2armgiSHQUJO8xzc4SCmrE9r8DsLHrCJflqXchHMrC3+EboL5HLUlv072D1tz0oVwumHDW7bMuXcwTWUbjbT4Xw/ON18t32fchpJaltJmEgXvBu21cZB5jIJ2/vVPjdGYWR863D2dzrOl1xl0780G1HBTS/+3aqfv+HP5s87WromfXMd1pM8L8hjFu23McxPXAxLcD27E3WDi3HXhebgTOaH9Ft+KL33mTjbFzZNzRzTbOzpHH4Li2hUZtpMyWbC+6VtMj835Dj7tRNyYJNxCfUb5Y97+OVMKxgU8RTdXg5FIb+bZIZ32bpruxTnh8dWcEJos3TRtcEN3bZlyp29hvveULhXRQTcqorXePzgj64nq9zUxzz3KtUitDqVFpji20TjpvxJ6z8NVSulYMshmFby3MtxVe26q/beLHc4VMHioTbiIUIty8xl20cOVatRSmK3iXOe3gvm/hwkoJ9mDkP5FVuJq2pZg4qCLlAlSlSmFtdiaPnjpi5ZsNyyUcWeZk/N2We4d2723sO/ZhRrwGWCpF8YmFyRn6FFSAY+gPpWHuv7Uxp7cmPN3MNlmc4bqYSPaj2I1ZGege4571FBcrbLPE6/seek+sho8ep8VkXK9BG1ysXlbbrWh08+C9nS7rRjeNhWR9apONY2HFdpBrfZjohKvJe1HGz2z249VM0wk4vuIWxjtzndrryJCLcectt9efJBad7gY6N4WZ6DFDV/jKVp1mUZ42iNMLwfZ2Ov9tXjoi2Yq8ue6XNW5wvhwD8zrA2/GUNA2xaEGz5BuX9zc3UDRbvlHaoVva9HljHJ+6NdP89gTO5+a3EVgunM4IfUe2U6bb/UHv6D7CL0dxkEyyNvRjlGcB290vPJJxzgA7OT/NZ6bjeh2Y9eP7hyOvWS94DO/FjcZtEH1WxcCSEJ0nx3471Rb0Ltgut/W7CGSLajEtqhzTEseZFlnI2NYwmuYySUuOdieI9jRLNe2LeGtb/tbCYqVczGf/W/mr+SVNmQqBXw4z5TAfpPz7Qoxtc08YbcGm5L4Qdux/YcyKnhjTXZFNTaUMmXVOjNvY9ZZxU+ttnD1WeGzu2sA4Z9zRfN2+EZg1jSe1N/Hjox1m89EQyI9ptLsL0zNGmudsQpo1j0F1prcZafrHGMcN3ga6327I8eKuwxixiVIIyuPidqaz7RNzTdN3gL667ZPj5O1kPM8b43z3xibd2JMfE0oo5zu1C7jVbaiUb/cmjDeEFO1rN95M0GfQO+y7gcHSPDEXxQu+ozH+tgy2ibKNYb2Fde2s5As1s0Hges0lBGU/sP9Y23oL4dbOmT02JvVqpb6muRqJCXEmJ8+RLmNuRZ94DXiXOCtMdDk+Je8lsUdhGuYDpTm6Ht8VJ+WARrQXbGBaxJBpezcyTUVMp/45s8mkLYnD7IVFI+3oZqbLwhi0l9i0lSWDltzCtMi7iGlfsWgLXcsnbAg0W86SXTwxATlrjSW9b6cllte1HGMdJy/2hywzRrazXu/y/N2NHTqcIZqSfUy7EjBN+aM1yDZeIxo7Fhl26G7IdDdY4m6tb2/FmJSy6tFjhkNkW9PPmPRxRujyJaeVTRxk9Yhei2zcx5hGVPxQ+Y2040wn3mdl+pbFnPZ7TLMSKz9Pf72YHlcvK87kJklXAfut8qm3E9ZpDBE5PdHUMyMM4bcX1gPDZXDyYXn3CgunAcznTxbdzY/LdGQD4+zcuE7nDIwi8hq0kWl2LlzWJYnpazaOZa7pXD5Ou0nTmDnnj7SajuzdCuxmOwVjPG3wcYvuz2dkC2PGY/J5qoXpz+eSRffnkx1ijJ0L98ebGKOJ3B4=
*/