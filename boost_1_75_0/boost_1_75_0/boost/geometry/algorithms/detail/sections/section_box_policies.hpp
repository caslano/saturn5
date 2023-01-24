// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_SECTION_BOX_POLICIES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_SECTION_BOX_POLICIES_HPP


#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/expand.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace section
{

template <typename ExpandBoxStrategy>
struct get_section_box
{
    template <typename Box, typename Section>
    static inline void apply(Box& total, Section const& section)
    {
        geometry::expand(total, section.bounding_box,
                         ExpandBoxStrategy());
    }
};

template <typename DisjointBoxBoxStrategy>
struct overlaps_section_box
{
    template <typename Box, typename Section>
    static inline bool apply(Box const& box, Section const& section)
    {
        return ! detail::disjoint::disjoint_box_box(box, section.bounding_box,
                                                    DisjointBoxBoxStrategy());
    }
};


}} // namespace detail::section
#endif


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_SECTION_BOX_POLICIES_HPP

/* section_box_policies.hpp
IELs+BetWXzUQonm08lDwnY657sFLbmrU3rSoHF8hSMjP5A3U07o7VASGXMfmpBOS+azlbmGMbtb7WLAfQxhWFvQ2RbFkapgJ1atuEuBaxazKygzIIGSCZX/VLCObYMzQ4S2iMPxt81BHlykHP+MHSMBQijNx6W2Rd3HBUIvVD7Gpbsuz1t/4fG+IAsgvsJ/bCdUC20zv4l+8ogfjLU6zAWJ1TAp33OW2RakiRnsctONVuy7Jh654n2KFUQQ+/ukXeUapze+XU5rxK6JGWGYkIRdy/FXRQibdtwb2rUTkZSheAVK/B1Rkn4i792YXvSvwEo2pIOUb0DiYkyMW1bSPxl5TN1YThMzDlPUWg4aFHwh9PHcr+odR7/VDtZnHcZdK9dFxzYE1Y2bDYRN9jMajd3uZDC7G2ZYjpuC0IXLoCePWItHs4jxngdieXeqKN+NKflL31b2zzlRaz6u2XdGUm/rflo94rmr5TfbpHuiB/viBkc4RO28ERZyukTdzI5jn7+GoyGqT1YlOdPKjpKsV2LBRbdrHdqFPFITX1BLbA6vmrF1WO1F0B/9NYFtDioWvu8JllurReQL/xJSP7cYLGrKrU7mNSRd2DbB25Cgk7VTYXS9BLIyNSFZ8i+BOyFqF81W4AiEY5EmMLUkpCsGsTcK7sD/J+r7OR/syU3KwnVC/JuFHDH38hI+zQD41VBtruuadO1Inv6Yif3n
*/