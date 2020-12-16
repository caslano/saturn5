// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_TAG_CAST_HPP
#define BOOST_GEOMETRY_CORE_TAG_CAST_HPP


#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace geometry
{

/*!
\brief Metafunction defining a type being either the specified tag, or one
    of the specified basetags if the type inherits from them.
\details Tags can inherit each other. A multi_point inherits, for example,
    both the multi_tag and the pointlike_tag. Often behaviour can be shared
    between different geometry types. A tag, found by the metafunction tag,
    can be casted to a more basic tag, and then dispatched by that tag.
\ingroup core
\tparam Tag The tag to be casted to one of the base tags
\tparam BaseTag First base tag
\tparam BaseTag2 Optional second base tag
\tparam BaseTag3 Optional third base tag
\tparam BaseTag4 Optional fourth base tag
\tparam BaseTag5 Optional fifth base tag
\tparam BaseTag6 Optional sixth base tag
\tparam BaseTag7 Optional seventh base tag

\qbk{[include reference/core/tag_cast.qbk]}
*/
template
<
    typename Tag,
    typename BaseTag,
    typename BaseTag2 = void,
    typename BaseTag3 = void,
    typename BaseTag4 = void,
    typename BaseTag5 = void,
    typename BaseTag6 = void,
    typename BaseTag7 = void
>
struct tag_cast
{
    typedef typename boost::mpl::if_
        <
          typename boost::is_base_of<BaseTag, Tag>::type,
          BaseTag,
          // Try next one in line:
          typename tag_cast
            <
                Tag, BaseTag2, BaseTag3, BaseTag4,
                BaseTag5, BaseTag6, BaseTag7, void
            >::type
        >::type type;
};

#ifndef DOXYGEN_NO_SPECIALIZATIONS

// Specialization for last one
template <typename Tag>
struct tag_cast<Tag, void, void, void, void, void, void, void>
{
    // If not found, take specified tag, so do not cast
    typedef Tag type;
};

#endif // DOXYGEN_NO_SPECIALIZATIONS


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_TAG_CAST_HPP

/* tag_cast.hpp
X/Q8qfevl+9vZvuiO5r+oi8157fodJP/S/L3Q+Z+UXSV6S+6s+kvuovpv8HRGeb8Ft3V3O/Z2uNTn+m0v0nqa3s589vomKM3Gh1Kc46/0fVOffbNpn+Wc/yMrnN0vdHBvZ3zxegax8+3wPg79blGN/R08jfa19PJx2jVw1nfbjF+/Zz+Rvt8zv4Y7fc5/Y0O9HL6LxSd7+SbY3TUaT/T6AYZD6MDfZzxMNon/ReZ7Tn1c5u1Ux8zOt/x8y02/SV/o/2OrjNa9XbmX3P7dGf+3mraOzpkdLCrcz1v1k59U7N2xm/gbaJzHF1qdKy7c/4Y3dDN2X5z+yyn/+2iG2X7Rsec+jqjA52c/Tc6x9G+JSYfR+caHXP0TKOjjq43OtDDycfoBqc+cIfJx9GlRkd7Ovk01zt6i6OpcPx8d5p8nP3PNzog/Y0OdXW2b3SNo7PvMueH41djdL7jt9HoHPxsQ9Gqs9Pf6GimM55G+5z6eqPrnPnTaHTM2X7gbjMfnPalRuc47RcbHXDqtxhd4+Tnu8fsn6MnGZ3fzdn/5npHNxid4/hl3WvGz9G5Rjc4+1NrdL5Tv9roGsevqVk79QOXmv5Zznw0OijHz+hap73vPpOfs785Rsd8zvEw2t/D2b7R0Sxn+0bXd3X632/Gu7OTP9qpd/RGo6Odnf5Gxzo7/R8w+Tt6ptGNsv9Gqy7OerTMaGf8S432OfX1Rvsd3WB0wNFZD5r+vZz+RvscXWd0oK/T3+j6LGf7D5nxk/XM6BzHP2R0TV/Hz2i/o2NGB7s442F0rczPh017md9Gh7o4x9foGtk/o2sd7V9u6p388o2uc+oXGx3t4cwPoxscHVhh5p8zf2YaHXPqo0Y3OjprpcnPaZ9vdIPPOR5GNzr712i0cvbP/4gZf9lfo6NyPTE6Jse/3vg7OtfoUD9n/hldI9fDZu34ZT1q8nH6B5u1k+/cZp3l9DdaZTj9HzP5Zjj9jfZnOP2NDjg6anRdV+d4G53vjF/O42b+ZDj5G626Of0dTUVPp7/RQZl/q4x2+s90NBV7O+eP0fkZTn+jQ44e+IQZH0eXGl3r6Hqj6xy9zdFUODrwpBkP53wMGR3NcLZvdMzR6ilz/BydY7Tq66w/RjfK+DXXM362odleb+d6YHQs09n/5nq5vhsd7OX0f9rUO9sLGl3X0zl+Rvud9luMjsr6/4w5vrL+Gd2Y6fQ32t/b6W90Th9nvNcY7Ww/ZHSwrzNeRuc7Wq01x8vRuUbXOrrW6Lq+zvaMDjjbz1pntufoUqODvZ3tGZ3v6PRnzfYcPcnoYB9ne0ZHnfMtZnS+U5/+nOnv6Fyja+R+z+haR280ulHuN6Mmf5nfRtc57WeKZs+c/KPGX/J/3vg7Otfout7O9o2ud/yizdqpb2zWMt4vmP3t6/Q3OtbXyd/oBkenv2j2R+aX0aqf09/oqGzf6Jij1Xrj5+hso6NOfjVGxxwdbW4v+RvdKP1fMtqpn2m0ku0b7XN0k9GBfk7/DWb+ODrf6KCjlxmdL/PB6Kjc/9l6z2fPZ89nz2fP5//lM7g7r3DsBv/ST7L92v7Yz087qP/lZ+L/2M/k+dOOpsaGaM3PVoe99t7/xMtN+eYL/K+XvPnzz0Puef+wWw912x/hj3v3XsqqF+PDJ973fzmWez57PrUBfvMGE77saHNssFLlxJq3grnEOUOYi2AJseZFR/LeELHmmIZuM5TfUsBW4jr4mGOV+pw4/zgYZDR2VL5hvJYA+hPH4F8P5/dT4iC8GgykfQNcfTyJaR947AlKZRLXwL1O5D5Xbwu+BYzW7eEmjX91tP+YexyY+1VHFYKvA4uJa+FPwXC2pfnwk9hfYs0=
*/