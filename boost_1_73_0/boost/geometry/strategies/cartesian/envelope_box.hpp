// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2019.
// Modifications copyright (c) 2015-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_BOX_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>

#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/normalize.hpp>
#include <boost/geometry/algorithms/detail/envelope/transform_units.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

#include <boost/geometry/strategies/cartesian/expand_box.hpp>

#include <boost/geometry/strategies/envelope.hpp>


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

    typedef strategy::expand::cartesian_box box_expand_strategy_type;

    static inline box_expand_strategy_type get_box_expand_strategy()
    {
        return box_expand_strategy_type();
    }

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


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_BOX_HPP

/* envelope_box.hpp
XTbb5tzMZ+8abWEb+OZg3boV6U1b37OK3pAC5vekaI3MFZFF/VnGz3vFd+Ff8O3pWGb1t4Du70L3D8mb6/BwkaF+kfbC33o6rbvkSTEEMOi1vOsC2e4S4PxZvpL6x3ktixpAb/r5qRRPMeFLUeq/IeVtQHewb56GvPgseXZwlkTZPo3mv2ID58m+CsUPPeF97BaWVTZJmS9ZJePUr2EU74Xr2Az6mza5cbxyq3GP3D8AARBM
*/