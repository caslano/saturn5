// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CONVERT_INDEXED_TO_INDEXED_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CONVERT_INDEXED_TO_INDEXED_HPP


#include <cstddef>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace conversion
{


template
<
    typename Source,
    typename Destination,
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct indexed_to_indexed
{
    static inline void apply(Source const& source, Destination& destination)
    {
        typedef typename coordinate_type<Destination>::type coordinate_type;

        geometry::set<min_corner, Dimension>(destination,
            boost::numeric_cast<coordinate_type>(
                geometry::get<min_corner, Dimension>(source)));
        geometry::set<max_corner, Dimension>(destination,
            boost::numeric_cast<coordinate_type>(
                geometry::get<max_corner, Dimension>(source)));

        indexed_to_indexed
            <
                Source, Destination,
                Dimension + 1, DimensionCount
            >::apply(source, destination);
    }
};

template
<
    typename Source,
    typename Destination,
    std::size_t DimensionCount
>
struct indexed_to_indexed<Source, Destination, DimensionCount, DimensionCount>
{
    static inline void apply(Source const& , Destination& )
    {}
};


}} // namespace detail::conversion
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CONVERT_INDEXED_TO_INDEXED_HPP

/* convert_indexed_to_indexed.hpp
p0YXX00dUEkjxUlWAsWe2N0tycX/rZS2PBw7rk+vPoTcPYa6pF47rX13PZprg4904UhVRB/iHPVJsPm7ZKqN5xsw54aaxJNs9kBZgufw5OQ1hQv8UpTlY/Tl489f555WUzhzwvc1CzU3669rOiJHYPQpkwwgpU4629K6k8RQC9AtR9njpLgLeBHUT2duOUWUy80jH0/XsYxigG5Yc+m43yMSmbySVCPVqh+N50xtIY4jXIHJ+FS7RHPlzQhXpAFje1c1dQXJluT03z0e/Pjz4Ojw9PTHw6OfrApvvS5xLBI78W/ItY5U/DTddNJtnVwuVg2GeUNFxqdOGf+sGu9PiV50fNY1gFfNft/A2DK8GwtCZTn8oCLt14G5NrHnYvQqtyn7liK+ihsHJ8xIuV6pJ9vZ7vGnKea0PsAM6Jj9nNAd0/nsV87GTyIGHeGUaG0CZhjh5LLLOdRP3nTPr3TY1mf33gZs4QfkNWP40poCuiiaexklOb66QOe9j7EuMCHWUsf3R+cYVjcREDinxAKqxeEOSaL8EfkPK0pMYFkfoyrXdSh0vQ+9eOvZaWu4IiMkoVlMStwVcSF7fJPvnvna44V1hgO514glpMQP2oePCDzWrUcmPE7nE7pnvf5h/6o3uDpD15GztjwI8D35
*/