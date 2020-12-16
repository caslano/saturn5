// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_GEOMETRIES_POINTING_SEGMENT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_POINTING_SEGMENT_HPP

#include <cstddef>

#include <boost/concept/assert.hpp>
#include <boost/core/addressof.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>

namespace boost { namespace geometry
{

namespace model
{

// const or non-const segment type that is meant to be
// * default constructible
// * copy constructible
// * assignable
// referring_segment does not fit these requirements, hence the
// pointing_segment class
//
// this class is used by the segment_iterator as its value type
template <typename ConstOrNonConstPoint>
class pointing_segment
{
    BOOST_CONCEPT_ASSERT( (
        typename boost::mpl::if_
            <
                boost::is_const<ConstOrNonConstPoint>,
                concepts::Point<ConstOrNonConstPoint>,
                concepts::ConstPoint<ConstOrNonConstPoint>
            >
    ) );

    typedef ConstOrNonConstPoint point_type;

public:
    point_type* first;
    point_type* second;

    inline pointing_segment()
        : first(NULL)
        , second(NULL)
    {}

    inline pointing_segment(point_type const& p1, point_type const& p2)
        : first(boost::addressof(p1))
        , second(boost::addressof(p2))
    {}
};


} // namespace model


// Traits specializations for segment above
#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename Point>
struct tag<model::pointing_segment<Point> >
{
    typedef segment_tag type;
};

template <typename Point>
struct point_type<model::pointing_segment<Point> >
{
    typedef Point type;
};

template <typename Point, std::size_t Dimension>
struct indexed_access<model::pointing_segment<Point>, 0, Dimension>
{
    typedef model::pointing_segment<Point> segment_type;
    typedef typename geometry::coordinate_type
        <
            segment_type
        >::type coordinate_type;

    static inline coordinate_type get(segment_type const& s)
    {
        BOOST_GEOMETRY_ASSERT( s.first != NULL );
        return geometry::get<Dimension>(*s.first);
    }

    static inline void set(segment_type& s, coordinate_type const& value)
    {
        BOOST_GEOMETRY_ASSERT( s.first != NULL );
        geometry::set<Dimension>(*s.first, value);
    }
};


template <typename Point, std::size_t Dimension>
struct indexed_access<model::pointing_segment<Point>, 1, Dimension>
{
    typedef model::pointing_segment<Point> segment_type;
    typedef typename geometry::coordinate_type
        <
            segment_type
        >::type coordinate_type;

    static inline coordinate_type get(segment_type const& s)
    {
        BOOST_GEOMETRY_ASSERT( s.second != NULL );
        return geometry::get<Dimension>(*s.second);
    }

    static inline void set(segment_type& s, coordinate_type const& value)
    {
        BOOST_GEOMETRY_ASSERT( s.second != NULL );
        geometry::set<Dimension>(*s.second, value);
    }
};



} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_POINTING_SEGMENT_HPP

/* pointing_segment.hpp
713q/7thHbhBwz2YZ42a66vmYmFPHvEH+qoYf8CGRg/MNe7C5iq3NvEETRh6wy4qO/6yfrPtj4rgrw4a3o7QqF/gCU+ymouNYK6FmmsJY2ArNSd7GNVcrpqLhu3UXJ5lx8MYWA7ma3yOgxlwLKyvspNeI9W+KhHSa5PP9sdmGAfvgwlwO0yEW2Ea3AYrq7ob72pvjQjxfkzD9x0sA39S/yKLfcdhVfiz5oPvYabKjr+fPYu/z1N/N1F/tvTZ+aw5TDfxCSvBpsbfKrvlUe2dHKGcPKL57DEtj4/DS+AzcKDxEzRhfwGOgvvgWPiklst93vL4u+3OnAjufK3uHFF3jqq9x6Ex+6OW9xNwEjwJp5n4gzNUdtIh8w/bneYR0uF2TYf1Gt8bYJbK2aZcwfPgPbAJvAM2U9lJhwK1v0OEdFik+f4q2BgugS3gUtgWLoPtLPFEYXsjq70FJi7V3lVqb4Lka92LS/jqWtKeiPm58AI4T8vpAtjNuK/ps1jjfwmcbNyBxo3lcBa8xucJz5+2u+kRwvOZxtfnWi6/gHHwWxgPv4LJ8BtYUdUde9eovRUi2Ftd82smjIY1oOyn0XJXE5aFtWF5VXfsLVJ7m0Swt73P9k8HLacdNf9f5LPT+0KYbfTDhqru5Jvjam/9CPnmOo2H1Rru62EivFnrnxssu3zdqOV2Layn7516LPeMbX92hHqsQO2fBo36TI3PWTBd5boqO/VpgdoXjFCf1lf7GsAo2FDNteIpVHMj1FyU0afm1mo9cTNsBNfBrqbceOv/v7S9k/fh7n5T1o6Pb2GGKc/QmNtqzKq5JWouFd6h5pqXsf3bAqbAlrAabA2zYRto0qstbGriDZqwnA87mHSH3U26w94m3eEQeAEcadIdXgE7wWkm/eEik/7wKhMvcLHKxr9reA6rf69X/5aVcmz/ZaLPyDVgHZgFTb6pqf7MVX/Wgi1NPoatTT6GF8Ac2BfWg4NMesFRJh3geJNecA5sDFeqfU4+2mBFue1AeiA8H72v6f4B9MMPNX9+pPnpY8uu/z+xQvn+kNpXUcPpzfeLArZ9V8GAhSEYhIthvEnLgG3/NbAMvBqmqWzsX8FzXO3/UO03+hao/b3L2Pr7wItgX2jcvkzjpR+cCfvD+aq+HA6Am+FAuEPVH4WD4HMmXPBFOAS+oe+Nfw5In8/2z9fqH+P+k5Z7fkhhDW3nTbreD7O1PWur7b5Jvx3aL3oQDoc74RhYpPXrLjgXPgSXwd0+Ox33wJvhw/A2+CjcAvfC7So/qu2s8dMT8GV1/2Nthw+re055zgzY4YmNUJ6zND/UhFJOtR6vren/Pk+umn/OJ/Eh7cBBNT+ceDPlfDQ0dubB8+AYLX/5mp/HQRMfE6CJjys0H0/U8jUJmrwwBf4DFsCb4AzY3oyBwb5wNsyDc2EBnAfnqXwNXAhvgIvgLfAquBEWmvSHV8In4BWa3pnGraAdvjQJqyW/yzvhs0L61pyjvqJz1HfoHPUdP0d9ydGqT/JZuL5ugZC+3HPU18fRp++8+vpbnvg7i76LvfF3jvqKzqJvlDf+zkHf3iDxp/qyk+z8u8eUz6Ct7xXCW9vYFbDz75twIHwHDoXvwstVHqlyAXwPzoMfw+WqvhbujyLfmfoTeQP8Em41dQl8AP4bPg6/C9j1zvfwR/gDPA1/ghXMmAOsBE8bd+GvcDz8DU6Gf8IF0MK9a2EA3gHLRtn5Oxm+B8vDD2FVOJayXw1Og1lwMawNi+B58CBsDt+ArWD1AO0rbAjbw6awK+wCu8PesAccBC+Gw2BdOAZmwwmqfyXsDzfDS+FWOBT+CC+DJ+Eo+IfKhEXkhXA0XKLyMjgGroY=
*/