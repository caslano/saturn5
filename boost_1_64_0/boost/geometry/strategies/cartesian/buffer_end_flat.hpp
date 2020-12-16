// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_END_FLAT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_END_FLAT_HPP

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/strategies/tags.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace buffer
{


/*!
\brief Let the buffer create flat ends
\ingroup strategies
\details This strategy can be used as EndStrategy for the buffer algorithm.
    It creates a flat end for each linestring-end. It can be applied
    for (multi)linestrings. Also it is applicable for spikes in (multi)polygons.
    This strategy is only applicable for Cartesian coordinate systems.

\qbk{
[heading Example]
[buffer_end_flat]
[heading Output]
[$img/strategies/buffer_end_flat.png]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
\* [link geometry.reference.strategies.strategy_buffer_end_round end_round]
}
 */
class end_flat
{

public :

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    //! Fills output_range with a flat end
    template <typename Point, typename RangeOut, typename DistanceStrategy>
    inline void apply(Point const& penultimate_point,
                Point const& perp_left_point,
                Point const& ultimate_point,
                Point const& perp_right_point,
                buffer_side_selector side,
                DistanceStrategy const& distance,
                RangeOut& range_out) const
    {
        typedef typename coordinate_type<Point>::type coordinate_type;

        typedef typename geometry::select_most_precise
        <
            coordinate_type,
            double
        >::type promoted_type;

        promoted_type const dist_left = distance.apply(penultimate_point, ultimate_point, buffer_side_left);
        promoted_type const dist_right = distance.apply(penultimate_point, ultimate_point, buffer_side_right);

        bool reversed = (side == buffer_side_left && dist_right < 0 && -dist_right > dist_left)
                    || (side == buffer_side_right && dist_left < 0 && -dist_left > dist_right)
                    ;
        if (reversed)
        {
            range_out.push_back(perp_right_point);
            range_out.push_back(perp_left_point);
        }
        else
        {
            range_out.push_back(perp_left_point);
            range_out.push_back(perp_right_point);
        }
        // Don't add the ultimate_point (endpoint of the linestring).
        // The buffer might be generated completely at one side.
        // In other cases it does no harm but is further useless
    }

    template <typename NumericType>
    static inline NumericType max_distance(NumericType const& distance)
    {
        return distance;
    }

    //! Returns the piece_type (flat end)
    static inline piece_type get_piece_type()
    {
        return buffered_flat_end;
    }
#endif // DOXYGEN_SHOULD_SKIP_THIS
};


}} // namespace strategy::buffer

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_END_FLAT_HPP

/* buffer_end_flat.hpp
im8yFvlqnjoeg7ZOPwLf0bxKtstipRzeGv+ygL9ppW95gAeJr0GyeXxbajo7eT0w3Sa9He0JuQVnfwf64ZHUD49BP+zQE9FgSE/VxZNN4aRvoF9PRkL1ek8kpqdEHxxOQvS/zPN/KhWVgzb/as7/08z5M79YWU/MIDr7PtM2d07H7wHgLOAxbO7PNefnNM2ds2kunGOZ08280GnkyaI5vZTylDnsmXmO0TLbK6e8FZR3J829Uzlf35IOmPPvALPGaT3RYK+YP+fyOTkYDgdC3XK+PI7Pyz1JXWdETuN2J3K5YLKXaJV8bk4EkykuaMjNFDQueSLqZSTqep4xp/L5eiCVjvcH4ApNpLyKHFTU1vSM9Rruk9XKv0Gux7Lm6Aum+gIxttbmNF7uVKQ3ZqXlcVowFpbiolwoE4tlkjE1+fswLcmktMVaDl/DLjDKw2KVjqYCEA9Ge1PSMYUk292JGcuiDyYCoUiiT09iFbJFZrdSuQZez9VUzwuG1NUfVvWYFFPHYtJRmVFHKN6fUDXI32b+JZR/8dB9Tk+lIvGYVGEhmX3wRNJzKtXdonxehlgowJeEzCiP//G8jQoaqwTZTk9g7ZT7m4RyUa8n8fUjGYMd2ReKNT0RD/Vpy6j+lir1N1MLo7YqAkk9nQzGUv2RNLzE+pH7npk1dH1+hLbNYlArr18oBnXcLyYi+ucxrJ2K34FQfIBfh9bCLoyOqFfboNNuKrPhFPf9vSzj2rGFLSICtd6Gtg6vmDclrW05zen1RKjrCDR5W1ra2GTd3LA2wNYu3k4/9Im1mCnW2bGKZOW8ZfLqvB1+OT/k2Ohsnedf2cnt5iq85d61Ae+auiaZbyR4H/f6v1AbOcEDeXbddHG1GPsZLYtoO9pN2mR+ncDqyKQVk9wzc01aCdEOKLRjiXZzvUmrAm0baFfnmLSFRDss16TVEG22Iucl2v0KrRG0m0ALZpm0ZtB+BdoSxeflRJur0FpZ24OD9yi0lWTjAsXGaso7TpFbS3JLFLkuolUqtFMob52SNw7aKti9TKFdSHkfUvJ+gWgHPCbtq6B9Dr+LlLy3gPZN0M5XaHeD9jvQ1iu0H4E2CR2nWaE9Tf51KLTnKaZ/UWgvgrYCeWsV2uugnQdam+LfAdCeAa0+S6m3AlGOjQptfYHI+2dF3ymgFUPmNYV2KuW9TrGxlWhbsk3a2aD5kfcIJe9loO0G7UiF9hTlXTfCpP0KtP2Q+57i31sFIlZRJe8HBaJsryp5cwuFz7oil18o6qNRoRUWivjNVmhHFgpfupU6P4ryFihy1YWiHz3crsSU8voUXxoLhc9TlLxthcLnexXaGpJborZJolUqtM2gTUOMn1ZoW0FbB1pCqY/zqGzVitxVpG+DQvsqaBcj7xMKbQ9oj4A2Q6HdSXlXKbR7QMvLsdblvRQrn0J7iOJyvBKXx0FbaMv7G8p7skJ7GbRzITdToU0ZK/RNUcamqWNFnS9S5ErGilg9ptBmjxXlaFdoc4nWq9CqQHsAdqsU2vyxIlY/VmiLyO6bCq2e/PMr5V0/VpStWJHrBS0XZXhVqbdrKe99Cu3msWJselCh7QFtRa51zLkrQ3kfz+DzU6TvWwrtFYrBsQrttxnK8UeirVJor491tskDY1kbspb3vQx5C8aJGPyJytah5UzQkOoXd8UTeiwVH0iGdPE1FS3tHohEw6UVZRVl5T2lg6nK8oqFBm/LgqrSVF8wqYdLw3r3QC/xobPB1BnWB7so36q6Ln88Hk11tXbia0VVWUV5WeV8xumOxLqa4qn0mgVVXVvwCUXLvGtwjTib9JSVdeEf2SVvuvC1i92EA5aFtP3dn3Y5uuJg8oVeJFQ=
*/