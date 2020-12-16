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
0Juze/q4Fl2BSY8wHTshe3mTz2SPyCPXWvTR3+c2PQ1Tx9BT9kP01MbpCfY4ers9mHy0CN72Qy6MjP9T40E6c6uJlU79ZLmFLrgfh+jIF/OqbrBKROl57aouvSXLJh+qUR6ecq/50e5fLFHF1HbNR45vo/QkSkzroOn1WTU7fUY1bWE6cyBmpeM6G6GjTlEwfs29eERH56hcdcbQ7O7Yzx+YfAOtmm7JYvdWmfSW1izIR35go1SFe6S+jZ2eWjE7va/7OPnN1qsWH7Ms7Hyo9YrSUdGS9VjpzNYKfS5a8KRmnAsBPGx0sXbLctKAbLxwejyGnqqgjY76mJquoapHu6WjXs/Gx9JKMH3E61nprQIQvTKUcPyY1oHp9Fq1OQC18MEvB5FR1aan3bB2ua2tjZ0Paa8OH2p1gvSmpdamo3IP0NkOtNnojfo+c7ueO9IJL1u8aL2m+MGFEhpMyDqKmjdZsfKx1U97PLMemQpW42Q9Tqf55Z3oGOFRv8uODb3R9474E1HB9510MrbOOVHYNf0Ok+VyHPV7QYmE+v2fk+Agf/NJcXDd3tvhB5POufj0zx2EaPQ7YvTDeHW/37XzrpVCjjbJ8GrlXfaTmRbHDBxIo+csenbdsTZfCFCb8zYTy58wajxfk6OR87Y850bnbGW/BA90ecdz8YgzufhFsv3yLk/kNpAOnHZYf6f6B+/bP3j0xN1Punc/Oeg2Jq90LiFGsmx5ncIdODiIr94N9Q+eUrjQvMzZPbeFsuH0rIPecDw+nSl9kWv4It6FLpP1O7xUzwx5zLbd88E4jkGzXfLwGfUm7OlFN8vb5VcuhqPVj2dkNzae2ZsTi+Prb5pvhI5bCd4NXD8+ueA4fQUzWF+/ZkZj40fPu8byt5zpjo3v24c9/xZ29niajR1vmlWcPMGz2zHxTANsUH+x6ZoF0iA/X8q4+EFLq5sfz9Di9Vi/Pql4jdenWmZG7cNuiqN0zdhI3imeyktMREq3f3AQ36cYPIFvnOJ+v1ND6t53iu6D3t2Dq3gDR08cHXKJ/uS9XIp/hON59z6+36tf8Rnk98PMv4/vwNP9vh78FN3vfvQExcc73fFO8CPMR6ZH8nr3Pr57/AbVO6VHfPjO8qj0DoPPfeX9fup+nxP3ut8J5AfTVnz8Tp59qtIs8f0Q7i7jIPRBGPn90kMIhwE8gnCiD+99gCPI1Pv6ERD56ADiADZ4Eu8H5W83413iHoDvayDewH0R5xRCP2hxPzGIu8SflPKAJ94PHcHzAAJ9CVKecy9W6GAymYaerwmfaqx1pDNmjZmuWmuLlrVeumqt9ddbk6215l5rLb/WmnqtNWz7HL4et6M86AqvPYXXksJrO7XWbmqtQcSssdBlWTuhy1gTILnqzVzXm2mvNXPe6Mx//EqD1is+VOrvUySEth8sXk14gxFPXY3196oz1V3R9nMnfzPnTi14d3ENeGXg3gm/lAoow9U3kfAg4T23n7i/QtXA743Fm3w5/Z1HD9+JOq5be3rv79G1BCPsRLecIgXwx+m4406sbBLOh5tKZMzWSg28Kxd5KZLGYwOCf+iLUAxH2xBqCF3vN3uZzVbss9pWgaXAC3jDiDh60r2PNz5KBFaq4tbGI6WtlIiWW254cIcgDkkSTV/tH8WTlnQ7443y4t/O5V3Dsj5r/YCMkpXxz+UrsEtN1y/rlfxijzqG6qpjqFzmenxKvIyyJ7hZlvH2TGeu+RYdvObupIiK0+XRvI1ebeTOYD1wYtd4I+M7nR4dIZ9CVWpoXGjS0TcvQFdn3IvOJ31lwt2/390Ge9oOWG73zrs+Qv5UfGY8V96Fuxy7urd2qaOSOXI8cwRf4+0fzBw=
*/