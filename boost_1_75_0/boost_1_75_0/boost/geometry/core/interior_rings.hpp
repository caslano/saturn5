// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_INTERIOR_RINGS_HPP
#define BOOST_GEOMETRY_CORE_INTERIOR_RINGS_HPP

#include <cstddef>

#include <boost/mpl/assert.hpp>
#include <boost/range/value_type.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/interior_type.hpp>

namespace boost { namespace geometry
{

namespace traits
{


/*!
    \brief Traits class defining access to interior_rings of a polygon
    \details defines access (const and non const) to interior ring
    \ingroup traits
    \par Geometries:
        - polygon
    \par Specializations should provide:
        - static inline INTERIOR& get(POLY&)
        - static inline const INTERIOR& get(POLY const&)
    \tparam Geometry geometry
*/
template <typename Geometry>
struct interior_rings
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};


} // namespace traits




#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template
<
    typename GeometryTag,
    typename Geometry
>
struct interior_rings {};


template <typename Polygon>
struct interior_rings<polygon_tag, Polygon>
{
    static inline
    typename geometry::interior_return_type<Polygon>::type
                apply(Polygon& polygon)
    {
        return traits::interior_rings
            <
                typename boost::remove_const<Polygon>::type
            >::get(polygon);
    }
};


template <typename MultiPolygon>
struct interior_type<multi_polygon_tag, MultiPolygon>
{
    typedef typename core_dispatch::interior_type
        <
            polygon_tag,
            typename boost::range_value<MultiPolygon>::type
        >::type type;
};


} // namespace core_dispatch
#endif



/*!
\brief Function to get the interior rings of a polygon (non const version)
\ingroup interior_rings
\note OGC compliance: instead of InteriorRingN
\tparam Polygon polygon type
\param polygon the polygon to get the interior rings from
\return the interior rings (possibly a reference)
*/

template <typename Polygon>
inline typename interior_return_type<Polygon>::type interior_rings(Polygon& polygon)
{
    return core_dispatch::interior_rings
        <
            typename tag<Polygon>::type,
            Polygon
        >::apply(polygon);
}


/*!
\brief Function to get the interior rings of a polygon (const version)
\ingroup interior_rings
\note OGC compliance: instead of InteriorRingN
\tparam Polygon polygon type
\param polygon the polygon to get the interior rings from
\return the interior rings (possibly a const reference)

\qbk{distinguish,const version}
*/
template <typename Polygon>
inline typename interior_return_type<Polygon const>::type interior_rings(
            Polygon const& polygon)
{
    return core_dispatch::interior_rings
        <
            typename tag<Polygon>::type,
            Polygon const
        >::apply(polygon);
}



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_INTERIOR_RINGS_HPP

/* interior_rings.hpp
tZwPjJrkUfmBcWR+stmLX9qzXWwdfai+dG5mw+Bjp90VLofvmKudaVbXXksfbj7lcG4HSDGWDXPenV6KJZyuxh0sRli7+78zmEk6FJS3jo/4fHGjalt9B3yQeju7RDZTbTnwddYowPE+al1nVrq/eQuUP9165n6w1mtrlkE5xQcg6K5UFFRFNnngYjnY8FVYySvc6dux0u+pk5a3LCrdbQekDp7fvna4ruXf6dR0FsbchHdLVWWsItucKdrDVvA0FfB0fuEztsRjozq+pHu4u74CsUvmRPz6tGg7Lk4nAr6q4ce0icyTHXjcpid+eKYjeOaK+JgEIn8g2VvP/JXorCV374Ukw4wxjpS8BNkRyGsQi2q/yfsEDB4bjenqH/GPZB9TYy/jHS+xvupuF5661ILpgFJtHCqaCi/4SLGd6RhvCo1fkhODCJUc6nUMpD5VkLoj+lW0dSSQ3DQPLD0COdqw1b1hbX8lUkUDA1srFkdnsCDgszHg5a4LwRm5z1ujBMXHDrL9oBiMAafCXQHDxHwG/QtPBFXRTCt+VqZK+C7sS7tDo0OrN37JoyzCQcc2j/F1onT8WYl0/LHQdHxyPhz0mopIYY6IWGmOyFFpzmRaaU5V2Q9toFudr9cUuIeNKyZ9w4D367YLUt3DjHD8s3S073rV8EW3pxrfUUvq5wZkQVf9fRUh34fUI/ltEA2Sr3Pbd1dozSNQ2DPJ
*/