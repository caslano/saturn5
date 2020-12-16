// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_TUPLED_HPP
#define BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_TUPLED_HPP


#include <string>

#include <boost/tuple/tuple.hpp>
#include <boost/geometry/strategies/side_info.hpp>

namespace boost { namespace geometry
{

namespace policies { namespace relate
{


// "tupled" to return intersection results together.
// Now with two, with some meta-programming and derivations it can also be three (or more)
template <typename Policy1, typename Policy2>
struct segments_tupled
{
    typedef boost::tuple
        <
            typename Policy1::return_type,
            typename Policy2::return_type
        > return_type;

    template <typename Segment1, typename Segment2, typename SegmentIntersectionInfo>
    static inline return_type segments_crosses(side_info const& sides,
                    SegmentIntersectionInfo const& sinfo,
                    Segment1 const& s1, Segment2 const& s2)
    {
        return boost::make_tuple
            (
                Policy1::segments_crosses(sides, sinfo, s1, s2),
                Policy2::segments_crosses(sides, sinfo, s1, s2)
            );
    }

    template <typename Segment1, typename Segment2, typename Ratio>
    static inline return_type segments_collinear(
                    Segment1 const& segment1, Segment2 const& segment2,
                    bool opposite,
                    int pa1, int pa2, int pb1, int pb2,
                    Ratio const& ra1, Ratio const& ra2,
                    Ratio const& rb1, Ratio const& rb2)
    {
        return boost::make_tuple
            (
                Policy1::segments_collinear(segment1, segment2,
                                            opposite,
                                            pa1, pa2, pb1, pb2,
                                            ra1, ra2, rb1, rb2),
                Policy2::segments_collinear(segment1, segment2,
                                            opposite,
                                            pa1, pa2, pb1, pb2,
                                            ra1, ra2, rb1, rb2)
            );
    }

    template <typename Segment>
    static inline return_type degenerate(Segment const& segment,
                bool a_degenerate)
    {
        return boost::make_tuple
            (
                Policy1::degenerate(segment, a_degenerate),
                Policy2::degenerate(segment, a_degenerate)
            );
    }

    template <typename Segment, typename Ratio>
    static inline return_type one_degenerate(Segment const& segment,
            Ratio const& ratio,
            bool a_degenerate)
    {
        return boost::make_tuple
            (
                Policy1::one_degenerate(segment, ratio, a_degenerate),
                Policy2::one_degenerate(segment, ratio, a_degenerate)
            );
    }

    static inline return_type disjoint()
    {
        return boost::make_tuple
            (
                Policy1::disjoint(),
                Policy2::disjoint()
            );
    }

    static inline return_type error(std::string const& msg)
    {
        return boost::make_tuple
            (
                Policy1::error(msg),
                Policy2::error(msg)
            );
    }

};

}} // namespace policies::relate

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_TUPLED_HPP

/* tupled.hpp
THNy4DXuoVuBEfMESzlWaGCcrMxxRFjveOS6b7NwGsBr5XUseux4fAnjYsfjzbczxm2/1xg0OxfOY88OgRGQ+DHzQQvTX8791zA9bsx8jjGxY2Zqp4Hx5PNti+7PpzXMmLgx8xvGaCKnvy7T3I6h+OLb7HsnYa2QL5WCAu4AT4WN6FJ6I1NtSO+ug/qYKvFvnX7oOnb6ajadSweZwJt+3zilJ7uOlT6fLFXTdVjYijp9KiuYNASXfF+sOydtvZatZkq5nJMWThactqbvT5tpM1mkDTO1sLC2t6paaM/FpW5SvSN8DvpZIrpLgK+NR85jbRZKtXj6pmeeSYn5kghTmXIwJXTeyGrE9GvXGXR4eD2mudgy30l423qmS6V+jNO+aYNDm8efcT6HginWpkNnbXTh+d7m9052bWaM1LmQAe03XJrKQOvhH9zi0M0MjDpeGmKcOA3BexSwKLAM624F3bLvqEj1CCYvGz3B2NY2jUWF1GlWuyVRuvlZfppYC9Ljt1GuozDefPkeyNJ24NgHltp4ZIf4LhRrzRt6pXzujut/g50CE7WL2cd31fHQJR33K+QYDifqU0Fmqlivib/mihX1ShDjzw0PxmsFdBx4JRMG4vlKCOdxadU0MFMY+OdcbyBevTDE+NnrD8Srl4R4D1m5gcBjJhrvbUmnd+os4QjF+PM3MvBKEvbjea7s3wU8vdEyhx0ljRV+5/TmGoPbPuASVwrLdnkrK01sSax95DZ7HxlWUpl6UFmbzb015o2pvsG7T+B5dfP1jPHvk1hv/xqd8aSyWWl+Ydq3LZq6B6No37NobI+/tV5X7DdTJ0/2sJudElcA+Pxg2MAwYGohh55SUMovUTB9cHgvd2u99zL3ewvLeAyeIO2aPgty+iJTq6WCYmpte3r0Bd1Pw5pRxBgekfxOiMF1LHrNfwkeaZFfaBn0yQdN4sWEqWI1iL5N4lslFDNCfIveVjgkvzFSp38AvkdI/naT6ykbXXSxjffTCd4foZBoyHmSV3tuIGjxa9bNb8h0aYhSQ+SmWhbciOm8L1PrzY2Z5lvvrjK9b7370y6bpkfmHXW5b2rT1SEO2rp9vLOCVWKMsR+8+SrYcc535JbAOuusRR/x0PexbDl4K6bHrcPvErajmHW4exuXZtvDZve4dO4UtQ6zr1L/ek70I7fz0fdRPknhH72G9X52L+N4vTfOwQU91vbNeu5FERfctpvwW3l3cmgNYf5R73DrfFyMsOy1cdGKD8D5DsqdXWwPsl3juExn78I49/5i5W5Mc+xHhDnLGEfmcB6FUcZAgFr3wvaMMc2Sado2N850YRxl/sb7K/sY41wQ5PPG/Yzp9CSPReER3FlsW2+nV+7OuNnO/CMbc515JdPYbskYTWa75QGmYSGheibvwd/Rs4snZSqevysHme67xGe22ZvuyVi2ozH94L2YjsPAxaWouuwfZdEXuhGZx/tL7i1lOj/9JgERnd+OsvU/5ZdA+jHfQ8sWq/VaLZsVz4jZ8dpLev3k49SapoVEO9FHO2ylE8KcaQ/ldETT6+cxK51uOfbJmOG0XvopottXbnXer7D4S2PwNL39bdHEqYE47mj2FuYh5vXb34wRb4TNt6d5bf8Q5w1ZKJgrLphCdLaGdjf3g9VCKleu5NamZx3ryDNe7SO5exj1lfz0a/cgdiNb/mtAEyXBLkOuybvV79VgqlDPRuv0LnwDS7o3jfmh75+rehwXHEm2jazT3zFr9IkRALohzPn3nPUmFiCWWVBOHRozYH+2TQqj6GhPfp3NmEf32WLgaDzwHurOQ6B77tJflN+Rxh4nlK6yjej4zPyO7FTf9VvDWpcf1t+FROHvw9c=
*/