// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_AS_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_AS_RANGE_HPP


#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/add_const_if_c.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename GeometryTag, typename Geometry, typename Range, bool IsConst>
struct as_range
{
    static inline typename add_const_if_c<IsConst, Range>::type& get(
            typename add_const_if_c<IsConst, Geometry>::type& input)
    {
        return input;
    }
};


template <typename Geometry, typename Range, bool IsConst>
struct as_range<polygon_tag, Geometry, Range, IsConst>
{
    static inline typename add_const_if_c<IsConst, Range>::type& get(
            typename add_const_if_c<IsConst, Geometry>::type& input)
    {
        return exterior_ring(input);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

// Will probably be replaced by the more generic "view_as", therefore in detail
namespace detail
{

/*!
\brief Function getting either the range (ring, linestring) itself
or the outer ring (polygon)
\details Utility to handle polygon's outer ring as a range
\ingroup utility
*/
template <typename Range, typename Geometry>
inline Range& as_range(Geometry& input)
{
    return dispatch::as_range
        <
            typename tag<Geometry>::type,
            Geometry,
            Range,
            false
        >::get(input);
}


/*!
\brief Function getting either the range (ring, linestring) itself
or the outer ring (polygon), const version
\details Utility to handle polygon's outer ring as a range
\ingroup utility
*/
template <typename Range, typename Geometry>
inline Range const& as_range(Geometry const& input)
{
    return dispatch::as_range
        <
            typename tag<Geometry>::type,
            Geometry,
            Range,
            true
        >::get(input);
}

}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_AS_RANGE_HPP

/* as_range.hpp
8qzI5n9bugDXaGm2pT2n6fr5Owp7J3jT8MrayO1X4LOSwOtzSf4KBWzfHHiLLOnwmv4GDjjLjfI/fl5dXaus7NSxDiQLcyTtLT22sw65MJINlgy75TTB5X0S4iG6EuId/nh+2deoTFwYU8PoGmh2pQhy4IrQxLSNR0kHJZLJlBILIWhccFsvvWmeS5DomOV8fqhlwyrEhzXabZ+HcN8+2qbr/hrmop970n6dDHpQtzCfiNV0/6GSRNO3RuKzbLiyDANjyGuYWSGdGioIX0xlho6wL09Ou1Va9tnC6j7e+KjZuDa+iUNk4IjLmU0ik3j1kaw/1cihpC1fWIPxy7LoKHWdZbBmTCnDzL+M00N9SXypbc8fbNZDKXXoltv7otqGl/3eRUtnFrMuOWl8j6lkbdoux1OCCuJ4nMzhtSmm45TmIO1oQ0pHnWYcWNFgba7jJms9dsQBmcZHtep99OCwLx86z7HicJaqpwfqf37qdi/gNh79SWMJAa+UTipQ6Nbxz3hrikrBbilbL0zO2a1QCcZVetBDRRhSEBsoUIL8eDvznBl2vRE5cnQyYQ5t/EAe73RtOe8xUDa4abADzqjckNpH6LjW0PuEXfLH4jVqt4OOBLZeM7bRlVD0oB3so50cPq8t5VQ/oEmUBH3W
*/