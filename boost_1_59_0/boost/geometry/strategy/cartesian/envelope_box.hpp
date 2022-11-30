// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2020.
// Modifications copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_CARTESIAN_ENVELOPE_BOX_HPP
#define BOOST_GEOMETRY_STRATEGY_CARTESIAN_ENVELOPE_BOX_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>

#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/normalize.hpp>
#include <boost/geometry/algorithms/detail/envelope/transform_units.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

#include <boost/geometry/strategy/cartesian/expand_box.hpp>

#include <boost/geometry/strategy/envelope.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{


template
<
    std::size_t Index,
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct envelope_indexed_box
{
    template <typename BoxIn, typename BoxOut>
    static inline void apply(BoxIn const& box_in, BoxOut& mbr)
    {
        detail::indexed_point_view<BoxIn const, Index> box_in_corner(box_in);
        detail::indexed_point_view<BoxOut, Index> mbr_corner(mbr);

        detail::conversion::point_to_point
            <
                detail::indexed_point_view<BoxIn const, Index>,
                detail::indexed_point_view<BoxOut, Index>,
                Dimension,
                DimensionCount
            >::apply(box_in_corner, mbr_corner);
    }
};


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL


namespace strategy { namespace envelope
{


struct cartesian_box
{
    typedef cartesian_tag cs_tag;

    template<typename BoxIn, typename BoxOut>
    static inline void apply(BoxIn const& box_in, BoxOut& mbr)
    {
        geometry::detail::envelope::envelope_indexed_box
            <
                min_corner, 0, dimension<BoxIn>::value
            >::apply(box_in, mbr);

        geometry::detail::envelope::envelope_indexed_box
            <
                max_corner, 0, dimension<BoxIn>::value
            >::apply(box_in, mbr);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<box_tag, cartesian_tag, CalculationType>
{
    typedef strategy::envelope::cartesian_box type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_CARTESIAN_ENVELOPE_BOX_HPP

/* envelope_box.hpp
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
*/