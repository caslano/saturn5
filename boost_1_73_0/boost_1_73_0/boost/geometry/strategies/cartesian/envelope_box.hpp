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
gVHacy+beDVY6LPc8TCVPvZ4BxJxWR0AdrYRvXwEmwtWwpp2VUW/EBegSwWnLnwMHRDQ5nERZiCJF6ZuIXVgh4wi5CDyLgzILrcYHff/eu8VD3FC8qNvNA/dM4x0o9G+1J3yYTdKH1LqVYL4Gq0lHgUY2ajDhCInd2cn58GLD73gi0Fp4Tnjo8PpyLn/V4Qrs7gXOu/qGrtzX5Kl3BmAh5L/m/lrF7fFQFrd1eOc8aKBffZ9fuic7/TK19jrm5ArbqW2CUU5UKbsyjc7PtrgJrY9kOurG1OM5DyD5wmAnwFRlZ2U3MGC613vMNzrBmWCsqF9w/Dzrj5B/rjVpA4N9w9QSwMECgAAAAgALWdKUihf46FOAgAAGwUAABgACQBjdXJsLW1hc3Rlci9saWIvc3RydG9rLmhVVAUAAbZIJGCtVN1P2zAQf89fcWpfoMoaxtPYEFpV2KiYWtSWoUpIkRtfsDfHjnwOHxJ//M5pSoXE1BdctbYv9/vwOb2+Lq3EEi4vRucX83x8M/+VL5bz5ewqv0z6/ERbfP9hNvi4kcAA9o68/eY8eG4R1979wSK8n53nL7D5MOqO530iGewgL/kh7Ie8wEELyTuV07jO831Cd9Fb/Mki8i6PS44wLCLHrn72+l4FOBgfwueT
*/