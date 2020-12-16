// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_DETAIL_INDEXED_POINT_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_DETAIL_INDEXED_POINT_VIEW_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

namespace detail
{

template <typename Geometry, std::size_t Index>
class indexed_point_view
{
    indexed_point_view & operator=(indexed_point_view const&);

public:
    typedef typename geometry::point_type<Geometry>::type point_type;
    typedef typename geometry::coordinate_type<Geometry>::type coordinate_type;

    indexed_point_view(Geometry & geometry)
        : m_geometry(geometry)
    {}

    template <std::size_t Dimension>
    inline coordinate_type get() const
    {
        return geometry::get<Index, Dimension>(m_geometry);
    }

    template <std::size_t Dimension>
    inline void set(coordinate_type const& value)
    {
        geometry::set<Index, Dimension>(m_geometry, value);
    }

private:
    Geometry & m_geometry;
};

}

#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename Geometry, std::size_t Index>
struct tag< geometry::detail::indexed_point_view<Geometry, Index> >
{
    typedef point_tag type;
};

template <typename Geometry, std::size_t Index>
struct coordinate_type< geometry::detail::indexed_point_view<Geometry, Index> >
{
    typedef typename geometry::coordinate_type<Geometry>::type type;
};

template <typename Geometry, std::size_t Index>
struct coordinate_system
    <
        geometry::detail::indexed_point_view<Geometry, Index>
    >
{
    typedef typename geometry::coordinate_system<Geometry>::type type;
};

template <typename Geometry, std::size_t Index>
struct dimension< geometry::detail::indexed_point_view<Geometry, Index> >
    : geometry::dimension<Geometry>
{};

template<typename Geometry, std::size_t Index, std::size_t Dimension>
struct access
    <
       geometry::detail::indexed_point_view<Geometry, Index>, Dimension
    >
{
    typedef typename geometry::coordinate_type<Geometry>::type coordinate_type;

    static inline coordinate_type get(
        geometry::detail::indexed_point_view<Geometry, Index> const& p)
    {
        return p.template get<Dimension>();
    }

    static inline void set(
        geometry::detail::indexed_point_view<Geometry, Index> & p,
        coordinate_type const& value)
    {
        p.template set<Dimension>(value);
    }
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_DETAIL_INDEXED_POINT_VIEW_HPP

/* indexed_point_view.hpp
emiFjqjzwOMhGdKgAIqhDCqhBtqhd5xzwnOhFCqgAZqhDTqhJ+ps8BmQAumQD4X/5TnhI6ecFZ4GmVAQdS54C7RDLwy/zHngRVAK1dFngv+H88Bzos4Cr4V6aIIO6Ia+qDPBkyETFkMeFEAxlEFl1LngvTA2+fSzwLMhF4qg9GXOAe+EHhiCUZjxCtoN6ZAFOZAPhaefCz7+meBR54EnQyYshmIog5qo8797YWCc87+zIReKoAIaoBl6oB+GYBSmvpI2QwqkQz4UvsyZ4K3QAX3jnAueCMmQCYshD4qhcpxzwttf4ozwDMiGXCiFaqiDBmiGTuiJOjc8dhr9gBmQAumQA/lQGHV+ePTZ4YMwAvGnnBee9x/ODO+CXhiA4ajzwrMhN+qs8LrTzggf/3zwFMiCHMiHQqiCJmiFjqjzwaPPBi+GsnHOBe+FARiD1POQ72nngZ9+Fngb9EA/xHrmdzpkQT6UvMSZ3x3QDX0QdrzxkBh19vdiKICy/3Du9xi83HnfRVHnfTdAG3RCDwzBKMSOc+53YdTZ37XQCn1R534nQxpkwmIogDKohBpogXbogl4YgGEYG+fs72zIheVQBKVQAdWnnQV++hngsZ4BngU5kA/lUAv1p5wF3nfh6Wd/541z1nc7dMEAjEHcxbTvvzjju+4lzvkegtFxzvlOh6yoc76roBbqoem/POs7GdIgE/KgAIpf4uzvXhiAMYibefr53xnjnAFeAdXQAJ3QA/0wBKMw1fO/syAfCqEcaqEJWqEDumEQRiJnf/8X537vgBZoh14YiD7z+38473vqa2gj5ESd710PTdDxH876ToPMqDO/i6EMaqLO/e6CARiGMUhIQbaQHXXmdzU0QDN0Qg/0Q+xs2gszIB2yxjnzuwpqoR5aoRv6YBBGIHTKud+Z/8W539Fnfo957ncqZEDuOOd910EDNEM/TH2ZM76roBaaoBU6/sszvhdHne/dGHWu9zCMnXKudxKkRp3vXQSlUAHV0ADN0Ak90A+xUed950Sd810PrdANfTB4yvneiVFnfBdAMVRCzcuc8T083jnf/8MZ353Qf8r53lOjzviOPt+7CuqhdZzzvUNX0BdIhGTIhDwogOKo8753QOM4530PQ1w6fUk//dzv5VAEpVABddAwzrnfQxA7j37ADEiHLCiEcqiC2pc493sEImd+J0MaZMJiyIMCqIw6A7zrJc79ToJUyIXlUASlUAc9MASxUWd8Z0EO5ENJ1PneHdAHoVPO9I4+y7sMKqEGdkALdI1zrncSZED2y5zn3QP9MAQzrqJ9kPM/nOM9CCMQXgzGQyIkR53nXQk7oBHao87zTnqZ87wros7w7oQeGILIGd7pkAX5UAglUAtN0Aod0A19L3Oed2bUmd7F0ed6R53pPQZxJ8/zHv8s7zpohn4YglGYejVthhRIhyzIh8Kos7zroWmc87sTxzmvuwwqoQZ2RJ3bPQDD/8eZ3XXQEHVudz8MwSjEZnuGN6RDTtR53fXQAd3QB4MQGue87sWQB8UvcWZ3C3RBLwyccl53EmRANuRGndldAXXQDG3QCT0w5FndKZAFOZAPhVACtVAPHdAHgxB6iTO6i6HsJc7m7oJeGIg6ozsBkiAVMiD7Zc7oboY26HyJc7rTIQsKoQSqoCnqjO4RCL0TXYdkKIBiKIMd0Agt0A5dMADDMAZxObQXkiAVMiAXiqAUqqEOGqAZOqEH+mEIRmHqEvQDUiA96szucqiFemiKOrd7EOJPObs77784s3v4lHO7EyAJUiEXiqAUqqPO7e75D2d1F0IV1EITdMAgjED8UnQZxjujewc0Qgt0Qe8453IvH+dM7mbofIkzuWeMcy4=
*/