// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_EXTERIOR_RING_HPP
#define BOOST_GEOMETRY_CORE_EXTERIOR_RING_HPP


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>


#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/add_const_if_c.hpp>


namespace boost { namespace geometry
{

namespace traits
{


/*!
    \brief Traits class defining access to exterior_ring of a polygon
    \details Should define const and non const access
    \ingroup traits
    \tparam Polygon the polygon type
    \par Geometries:
        - polygon
    \par Specializations should provide:
        - static inline RING& get(POLY& )
        - static inline RING const& get(POLY const& )
*/
template <typename Polygon>
struct exterior_ring
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_POLYGON_TYPE
            , (types<Polygon>)
        );
};


} // namespace traits


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{


template <typename Tag, typename Geometry>
struct exterior_ring
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};


template <typename Polygon>
struct exterior_ring<polygon_tag, Polygon>
{
    static
    typename geometry::ring_return_type<Polygon>::type
        apply(typename add_const_if_c
            <
                boost::is_const<Polygon>::type::value,
                Polygon
            >::type& polygon)
    {
        return traits::exterior_ring
            <
                typename boost::remove_const<Polygon>::type
            >::get(polygon);
    }
};


} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
    \brief Function to get the exterior_ring ring of a polygon
    \ingroup exterior_ring
    \note OGC compliance: instead of ExteriorRing
    \tparam Polygon polygon type
    \param polygon the polygon to get the exterior ring from
    \return a reference to the exterior ring
*/
template <typename Polygon>
inline typename ring_return_type<Polygon>::type exterior_ring(Polygon& polygon)
{
    return core_dispatch::exterior_ring
        <
            typename tag<Polygon>::type,
            Polygon
        >::apply(polygon);
}


/*!
\brief Function to get the exterior ring of a polygon (const version)
\ingroup exterior_ring
\note OGC compliance: instead of ExteriorRing
\tparam Polygon polygon type
\param polygon the polygon to get the exterior ring from
\return a const reference to the exterior ring

\qbk{distinguish,const version}
*/
template <typename Polygon>
inline typename ring_return_type<Polygon const>::type exterior_ring(
        Polygon const& polygon)
{
    return core_dispatch::exterior_ring
        <
            typename tag<Polygon>::type,
            Polygon const
        >::apply(polygon);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_EXTERIOR_RING_HPP

/* exterior_ring.hpp
Lg9dTBctwlxvIWOc2dL005VqcdKFaOQu8KU/fO5PHng6B79YqSLpoL6l7Bkchcoo+QNwn5JwFrpJqboMqc2EI4dTUi/If7lcgIFRPHdsmszfoIfhZDP4pppHB6JwWrliJkcdXKq0oXQkvUseXdcOn4760YosLr47XckadkOJ8QcB+Tt7lvSoReAKY9Ipq+Ezghm4T6u89hbA5DOOml8dyWerNejJFtBbINu10MP04SRHYf+ZMe7TWPmUpkcmCqPSQ4XpiZj1kM+xJio19I+aM4HKRJXLxsdXpI1+CmZBCjXopNllRs5VqTdOF2l8JF99RB41SDpJGHfk17aC9KZ/JHq7RwrSVeFGKpMF1F7ITYbB+Dy1d+SWTL6GcWbQN8rIdFhyOx1cKqmMVCJLMtDv4n4quZr8FPVzre0HpSv7bXAW0/AZqkvjOSq/S0P0XMjUCrIKdGtWgx859gwfXtU9Cn2xBZPBc840n9P5KojkUtukrMshXfrxXIZT7kYKkfLwzceUxsNPlyZU/Q22DAqrz3vCQqrSE3hw7mOR45YHUqnTUtCKKNJB0ioYT/L5UmVMZBeFSDeextPU5SqgmhBD1WZ4XU8LXx7p1uGbt5c7EREfLJ5KH5Dn+HL80lBPSV3kHINWQ1w9PPfvajXjRM/uTqozg+qYyXqDbaEvanPR9OhOjUqNRIrIUy1PmHSyRa6Sm1OOBsOJXHESA88I3YxHm58ZxSiggno143quj76yacbn5d5RKDDo24getgRBfeNk4gB90V7hiB4l6o+QooZP9PBb2Qn8l94rE/QAqirJ4ZO0XDdbOTdF6AA9ehH5sjQBeUqdeqqanvMMHsp81aigBr069c5L8KF1bSQuHSycLqwafQHpdSNyVMOufbxaLVWk3c2cC4xEKD5VRs9pU8YDdCYBxUcjWpqukoFB4YFyL6Ajgykcf6SnijQon6UZEdB8CdKh0yh9xxh3xWx0UxxfOkXyxlXT1QTiw0ynS5HCiNLDOGgiKkDHUlJLa9LBX6OjiyQnUbeEJT1qdJjQQqe9oq1e6s6RUlCUfmqscHoaViI5yFmvCB3mEuTXcEN0VZceiI66Jz6d7OlFypLpVC8AEw06KQtdtSizG6CrwGTk/AuPVaN0epyiJzEhvDn7EORXlu0M5seoEsfy43GPSU9jW+P7CrH0iEe/mUnChOWAM56WQ8FKCfajWaFNk3zgwsqkEwxRRh6WxyBDKgdEsD5rvtQkr2xTKuzRg/xkM9EIQ/uQUudP6a++vq2tip0P6zlCVxkvlqt2utr69caCmCv36dAd460/BDLjydEvugrcaAX9H2yxMBGxaL6goIpsuXJouLiLQf0Ok54qHtRsG18yPeaA7By8z2LITPeo5Ok9TI+5mujoyKRHRyocn9t+M8Eo3VT+EQG6mHxSfPgslpPgGCLein5GN+di6x5XO9ef0zXtnbsZNM5XbZ5Fz9XJkqv6yjpdorNZkp0eujY5RPiUz5Yz6D4G+jt+PNiIoeaKP10Y4EPFrAdF0xNosso2erT7UCaRR+lBQ5UgUyH7t9JD24b+MFPqeUZty25oRkfHl9umqDIZjYhfQSJ8aAIV6ULYCJ8Td8/Apwfiu1G/gc4HZLbVAqLjfgz12kNSUDrU9TPja6mjspFcQ/ePsSm6aH4dlf9sXpppRaYvdy6ZOr5NqNtPQ2C/f0ujAJNhMH2eboHovtyct4DIpB/q3k5i2jfD3XlyQ5qulKf5Hszs00pRMB2qphyPMkvjiqh9cXxZTWHXJV6kIm5M708Pm5Zjo7cUJNEH1hCtdFTQqn7BwmlsY9KzurmvZ6GvZnTfIxOdpGc+mEIv++Vkk8P+LacgvTE=
*/