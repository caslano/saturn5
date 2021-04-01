// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_INFO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_INFO_HPP


#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/enrichment_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/visit_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_identifier.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template <typename Point, typename SegmentRatio>
struct traversal_turn_operation : public turn_operation<Point, SegmentRatio>
{
    enrichment_info<Point> enriched;
    visit_info visited;
};

template <typename Point, typename SegmentRatio>
struct traversal_turn_info
    : public turn_info
                <
                    Point,
                    SegmentRatio,
                    traversal_turn_operation<Point, SegmentRatio>
                >
{};



}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_INFO_HPP

/* traversal_info.hpp
tHC8mBw638Hy+YLOrFlFlF3Kj1ArcWwylfk0gKigRRffe2Y76iPDppA2knjhf+niujDeEUsuUtMyem4aXQRYexMlp0HoHPLVdAAN4ct2TdjfK0kGr+AqyZJ615OuhIoj1n+C5PArvMRve3edjWpfRjIA2z0qmSRwNncS09Hh0sgDU/VtaA0tvnEDrv4Y3Tt/uZNjErJbLecSFXXcwLUXP+zR04MfcoHwzZaEAbLbZG4MFjbJqvl1uDXEbqFZmlKEJis0WV6KSt1DR+IEnpseW69vOIy0OCXl/avjASbOBRUl6Ap+nBjGSsk1bg4uy/CIHi2VrhlvePlKVEN/A0qFrEhOjHiYCOgAvUZjwiqrhts+Cn1mUzmvaxeyHH1aEoVN4La6Qbz3CwU1N+BwAifLSpByDf6hv7Za6t7585tWkKcpulqBY6POmo43Hy4IY52Vrf/kDietvCZpiyFmra0s5m2S96vOdUKimDxIrPx1f60MX3Lzlf99zIvi3JH+H8TDnS7IryUs5Tq+sWg75gqXi+9NaYzPxoEQW14Ucb09V958oZoNZ883PymNOA==
*/