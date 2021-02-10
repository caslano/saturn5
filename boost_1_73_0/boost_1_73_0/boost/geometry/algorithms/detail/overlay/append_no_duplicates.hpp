// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPLICATES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPLICATES_HPP


#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>

#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template <typename Range, typename Point>
inline void append_with_duplicates(Range& range, Point const& point)
{
#ifdef BOOST_GEOMETRY_DEBUG_INTERSECTION
    std::cout << "  add: ("
        << geometry::get<0>(point) << ", " << geometry::get<1>(point) << ")"
        << std::endl;
#endif
    geometry::append(range, point);
}

template <typename Range, typename Point, typename EqPPStrategy>
inline void append_no_duplicates(Range& range, Point const& point,
                                 EqPPStrategy const& strategy)
{
    if ( boost::empty(range)
      || ! geometry::detail::equals::equals_point_point(geometry::range::back(range),
                                                        point,
                                                        strategy) )
    {
#ifdef BOOST_GEOMETRY_DEBUG_INTERSECTION
        std::cout << "  add: ("
            << geometry::get<0>(point) << ", " << geometry::get<1>(point) << ")"
            << std::endl;
#endif
        geometry::append(range, point);
    }
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPLICATES_HPP

/* append_no_duplicates.hpp
zLxtrFhR63zQP229aTt10pt0e56lEaxORS3o5ehVHrzxRbH0cPjzm75VTEJv/XYgw2qiDhXh/bgOvcCebzfEkydCvRsOT7s/t09OhiedV4fDYaPx6C9zmtUgGnrjcTLMHv2Fy5o3QJ7S4BJqizCOLq2+FBS4UEyMbeBq8GLsZR4unnmZQu2J++oqTrNg5r6D3X6J1Mh9myVelE78xH0L/Mib+bk2gUXAG7G9Qdvgp8HgDCnI5xuRzaMIeGGazScTAQhngRaPPuY6DKZeDrBpMM11BeQ3i+PJJCu8HnlpruynLEy38X/u61EMMI2KDfhJEif5+QsLJafzMAuC3KzSciwFiPcY7Gv3NTCXKJTT/2h7g6hh6KWZeCZ0IeRKqeLwFz5LAwHyD2RmzsxSL7MkiLJJSfdTfxonN7kh+dOxfzG/VACcxCOgn0B/gX9GIyR/KXaRZkAKR0QSRjHUw/UaJv7lPPQAcSW21GHkc5D2DrEz30tvxAbiZVNcxHEIz3HkN/bLmxrH96oc+ZXVdVGsOk+bj6rFPuoJePMUCiaVvUkcug+8QbqkkQVA8h9ZTzaDdcQG/pDdj31vXNU7IfEQP8FAR1e3GgcgFjdy6We4iysrV8JXOTLeINCmnwEl3CAaUb3gIPwsBXx2Bbtw
*/