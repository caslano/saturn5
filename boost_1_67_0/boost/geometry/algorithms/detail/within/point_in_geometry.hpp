// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2018, 2019.
// Modifications copyright (c) 2013-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_POINT_IN_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_POINT_IN_GEOMETRY_HPP


#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/range.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/geometry/core/assert.hpp>

#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/interior_iterator.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/strategies/concepts/within_concept.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/relate.hpp>

#include <boost/geometry/util/range.hpp>
#include <boost/geometry/views/detail/normalized_view.hpp>

namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace within {

template <typename Point1, typename Point2, typename Strategy>
inline bool equals_point_point(Point1 const& p1, Point2 const& p2, Strategy const& strategy)
{
    return equals::equals_point_point(p1, p2, strategy.get_equals_point_point_strategy());
}

// TODO: is this needed?
inline int check_result_type(int result)
{
    return result;
}

template <typename T>
inline T check_result_type(T result)
{
    BOOST_GEOMETRY_ASSERT(false);
    return result;
}

template <typename Point, typename Range, typename Strategy> inline
int point_in_range(Point const& point, Range const& range, Strategy const& strategy)
{
    boost::ignore_unused(strategy);

    typedef typename boost::range_iterator<Range const>::type iterator_type;
    typename Strategy::state_type state;
    iterator_type it = boost::begin(range);
    iterator_type end = boost::end(range);

    for ( iterator_type previous = it++ ; it != end ; ++previous, ++it )
    {
        if ( ! strategy.apply(point, *previous, *it, state) )
        {
            break;
        }
    }

    return check_result_type(strategy.result(state));
}

template <typename Geometry, typename Point, typename Range>
inline int point_in_range(Point const& point, Range const& range)
{
    typedef typename strategy::point_in_geometry::services::default_strategy
        <
            Point, Geometry
        >::type strategy_type;

    return point_in_range(point, range, strategy_type());
}

}} // namespace detail::within

namespace detail_dispatch { namespace within {

// checks the relation between a point P and geometry G
// returns 1 if P is in the interior of G
// returns 0 if P is on the boundry of G
// returns -1 if P is in the exterior of G

template <typename Geometry,
          typename Tag = typename geometry::tag<Geometry>::type>
struct point_in_geometry
    : not_implemented<Tag>
{};

template <typename Point2>
struct point_in_geometry<Point2, point_tag>
{
    template <typename Point1, typename Strategy> static inline
    int apply(Point1 const& point1, Point2 const& point2, Strategy const& strategy)
    {
        boost::ignore_unused(strategy);
        return strategy.apply(point1, point2) ? 1 : -1;
    }
};

template <typename Segment>
struct point_in_geometry<Segment, segment_tag>
{
    template <typename Point, typename Strategy> static inline
    int apply(Point const& point, Segment const& segment, Strategy const& strategy)
    {
        boost::ignore_unused(strategy);

        typedef typename geometry::point_type<Segment>::type point_type;
        point_type p0, p1;
// TODO: don't copy points
        detail::assign_point_from_index<0>(segment, p0);
        detail::assign_point_from_index<1>(segment, p1);

        typename Strategy::state_type state;
        strategy.apply(point, p0, p1, state);
        int r = detail::within::check_result_type(strategy.result(state));

        if ( r != 0 )
            return -1; // exterior

        // if the point is equal to the one of the terminal points
        if ( detail::within::equals_point_point(point, p0, strategy)
          || detail::within::equals_point_point(point, p1, strategy) )
            return 0; // boundary
        else
            return 1; // interior
    }
};


template <typename Linestring>
struct point_in_geometry<Linestring, linestring_tag>
{
    template <typename Point, typename Strategy> static inline
    int apply(Point const& point, Linestring const& linestring, Strategy const& strategy)
    {
        std::size_t count = boost::size(linestring);
        if ( count > 1 )
        {
            if ( detail::within::point_in_range(point, linestring, strategy) != 0 )
                return -1; // exterior

            // if the linestring doesn't have a boundary
            if (detail::within::equals_point_point(range::front(linestring), range::back(linestring), strategy))
                return 1; // interior
            // else if the point is equal to the one of the terminal points
            else if (detail::within::equals_point_point(point, range::front(linestring), strategy)
                || detail::within::equals_point_point(point, range::back(linestring), strategy))
                return 0; // boundary
            else
                return 1; // interior
        }
// TODO: for now degenerated linestrings are ignored
//       throw an exception here?
        /*else if ( count == 1 )
        {
            if ( detail::equals::equals_point_point(point, range::front(linestring)) )
                return 1;
        }*/

        return -1; // exterior
    }
};

template <typename Ring>
struct point_in_geometry<Ring, ring_tag>
{
    template <typename Point, typename Strategy> static inline
    int apply(Point const& point, Ring const& ring, Strategy const& strategy)
    {
        if ( boost::size(ring) < core_detail::closure::minimum_ring_size
                                    <
                                        geometry::closure<Ring>::value
                                    >::value )
        {
            return -1;
        }

        detail::normalized_view<Ring const> view(ring);
        return detail::within::point_in_range(point, view, strategy);
    }
};

// Polygon: in exterior ring, and if so, not within interior ring(s)
template <typename Polygon>
struct point_in_geometry<Polygon, polygon_tag>
{
    template <typename Point, typename Strategy>
    static inline int apply(Point const& point, Polygon const& polygon,
                            Strategy const& strategy)
    {
        int const code = point_in_geometry
            <
                typename ring_type<Polygon>::type
            >::apply(point, exterior_ring(polygon), strategy);

        if (code == 1)
        {
            typename interior_return_type<Polygon const>::type
                rings = interior_rings(polygon);
            
            for (typename detail::interior_iterator<Polygon const>::type
                 it = boost::begin(rings);
                 it != boost::end(rings);
                 ++it)
            {
                int const interior_code = point_in_geometry
                    <
                        typename ring_type<Polygon>::type
                    >::apply(point, *it, strategy);

                if (interior_code != -1)
                {
                    // If 0, return 0 (touch)
                    // If 1 (inside hole) return -1 (outside polygon)
                    // If -1 (outside hole) check other holes if any
                    return -interior_code;
                }
            }
        }
        return code;
    }
};

template <typename Geometry>
struct point_in_geometry<Geometry, multi_point_tag>
{
    template <typename Point, typename Strategy> static inline
    int apply(Point const& point, Geometry const& geometry, Strategy const& strategy)
    {
        typedef typename boost::range_value<Geometry>::type point_type;
        typedef typename boost::range_const_iterator<Geometry>::type iterator;
        for ( iterator it = boost::begin(geometry) ; it != boost::end(geometry) ; ++it )
        {
            int pip = point_in_geometry<point_type>::apply(point, *it, strategy);

            //BOOST_GEOMETRY_ASSERT(pip != 0);
            if ( pip > 0 ) // inside
                return 1;
        }

        return -1; // outside
    }
};

template <typename Geometry>
struct point_in_geometry<Geometry, multi_linestring_tag>
{
    template <typename Point, typename Strategy> static inline
    int apply(Point const& point, Geometry const& geometry, Strategy const& strategy)
    {
        int pip = -1; // outside

        typedef typename boost::range_value<Geometry>::type linestring_type;
        typedef typename boost::range_value<linestring_type>::type point_type;
        typedef typename boost::range_iterator<Geometry const>::type iterator;
        iterator it = boost::begin(geometry);
        for ( ; it != boost::end(geometry) ; ++it )
        {
            pip = point_in_geometry<linestring_type>::apply(point, *it, strategy);

            // inside or on the boundary
            if ( pip >= 0 )
            {
                ++it;
                break;
            }
        }

        // outside
        if ( pip < 0 )
            return -1;

        // TODO: the following isn't needed for covered_by()

        unsigned boundaries = pip == 0 ? 1 : 0;

        for ( ; it != boost::end(geometry) ; ++it )
        {
            if ( boost::size(*it) < 2 )
                continue;

            point_type const& front = range::front(*it);
            point_type const& back = range::back(*it);

            // is closed_ring - no boundary
            if ( detail::within::equals_point_point(front, back, strategy) )
                continue;

            // is point on boundary
            if ( detail::within::equals_point_point(point, front, strategy)
              || detail::within::equals_point_point(point, back, strategy) )
            {
                ++boundaries;
            }
        }

        // if the number of boundaries is odd, the point is on the boundary
        return boundaries % 2 ? 0 : 1;
    }
};

template <typename Geometry>
struct point_in_geometry<Geometry, multi_polygon_tag>
{
    template <typename Point, typename Strategy> static inline
    int apply(Point const& point, Geometry const& geometry, Strategy const& strategy)
    {
        // For invalid multipolygons
        //int res = -1; // outside

        typedef typename boost::range_value<Geometry>::type polygon_type;
        typedef typename boost::range_const_iterator<Geometry>::type iterator;
        for ( iterator it = boost::begin(geometry) ; it != boost::end(geometry) ; ++it )
        {
            int pip = point_in_geometry<polygon_type>::apply(point, *it, strategy);

            // inside or on the boundary
            if ( pip >= 0 )
                return pip;

            // For invalid multi-polygons
            //if ( 1 == pip ) // inside polygon
            //    return 1;
            //else if ( res < pip ) // point must be inside at least one polygon
            //    res = pip;
        }

        return -1; // for valid multipolygons
        //return res; // for invalid multipolygons
    }
};

}} // namespace detail_dispatch::within

namespace detail { namespace within {

// 1 - in the interior
// 0 - in the boundry
// -1 - in the exterior
template <typename Point, typename Geometry, typename Strategy>
inline int point_in_geometry(Point const& point, Geometry const& geometry, Strategy const& strategy)
{
    concepts::within::check<Point, Geometry, Strategy>();

    return detail_dispatch::within::point_in_geometry<Geometry>::apply(point, geometry, strategy);
}

template <typename Point, typename Geometry>
inline int point_in_geometry(Point const& point, Geometry const& geometry)
{
    typedef typename strategy::point_in_geometry::services::default_strategy
        <
            Point, Geometry
        >::type strategy_type;

    return point_in_geometry(point, geometry, strategy_type());
}

template <typename Point, typename Geometry, typename Strategy>
inline bool within_point_geometry(Point const& point, Geometry const& geometry, Strategy const& strategy)
{
    return point_in_geometry(point, geometry, strategy) > 0;
}

template <typename Point, typename Geometry>
inline bool within_point_geometry(Point const& point, Geometry const& geometry)
{
    return point_in_geometry(point, geometry) > 0;
}

template <typename Point, typename Geometry, typename Strategy>
inline bool covered_by_point_geometry(Point const& point, Geometry const& geometry, Strategy const& strategy)
{
    return point_in_geometry(point, geometry, strategy) >= 0;
}

template <typename Point, typename Geometry>
inline bool covered_by_point_geometry(Point const& point, Geometry const& geometry)
{
    return point_in_geometry(point, geometry) >= 0;
}

}} // namespace detail::within
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_POINT_IN_GEOMETRY_HPP

/* point_in_geometry.hpp
FWAIpwEV1sW3FvgESjypmaNqXS8Mu2Iw7j3lM75HhOiF9zBQb906gHKRHkjyXgR4PhW7F1aE62rAXh3WN+F7FJY4FCSR0KS+kF6mCxlgzpXLgGxu8tS0A1VQCaCctWoBcd5IwTVeKxZ62EJAg809bF8sL+zOe0jsCIpwgZlcRlkIIDNzQ3AMKWzC4V30i4ulr7k4y+nBnjU9sN3JqAV54cAdlNNGSFrcmigLxCtgiQQLak6lzVVABqoLGqgzl9lapA0cikOZRv2xR01X+Imqe8ykDGIPWHAnCMKOlhdurD/iItTgGII+TW3h1GPpE1DSfeJyyGDUqqf+vvKN4CJzVbadAC8c1O/pdILYQNm8cLP6nEj6qN2ReZJJrY7Po4NppoNCiU5RaMvWkkm85GImg4RWerwkvXIc8ObDC1F5Iynq7EBTS/HlmT9TPGPxsdwR4AQzbUQaffjaGpbgU6R8gWBFG6hj7hdL52pFFKCEfP4vNn5vsRIJ4joYmfvSVEccpBf9Xgp/1eiXncXcsxJPVgdA03xvCwWCJtBP96Mi7PKi1ZLn/LzbrveRYWkQT/99xkCg4UJfOBxTQYb+8+9u1FKQYYJLQHAEvsNPjByZGZMDSalGarTNMc1d4fr1GIFqIIMhJ6RUJL/aomPOBZfslovB9NFh82KWFYu7qUV+zmF95QY1792MZP70qXGlqc47q1bh0RZ3nLaEYajPlTHaUTWQ6TJTEaUJc5L+mdDmzkI5arYcoIbMUn0T7Qzukfo+8+NSsUG7b0q2ab7JtKuiGgbqWZZ44LQxq4OIcYqA8PjLKv9ooWa1mO/wYhusBNGVAN2keCyYkKHxjI4tyG2365PSynZVydhYnaCaQfNXbdnxGKtWleBmYI+GWG5tQxnGbHIJtDcQudCP/XfrDirJTd9+/jq/21KmOFHPDp9YJnUwluTv7p/T2MkjQPCIlj4QqxMMGYLe142GCz0g0CukezVM8MPeejh/VmvGxKrsoNGe8ODpj75kz4bdL4rjpwXbuvRAP3akj2DIReWTKBRxVv6J/yfjn3u/xPz6/ZIesfcyQE83T/XZ7eIEiVikNaGJZScPuf1kAiE0h3V8HhiwOjEVwvDWyC0fHN6f2gPRIhCNyhnRZERpfoSamL/xok6x6r4rE+Qj+QqLMaYd1iQKHHa0CXA+4WAavUz33GUPtZCIFyDMWpZbi3zNLRTudVEmmNHhM541xbFOzQ7pGQNyVEypo61t8NWTiZEmmEO8SpYzqAkyjKLkdgWF91PtDHU45eLcRIeBe09B/83/rwTq33wdJQO0gRTwhokY20jRQkywzXLyMcUT4kPj2QD6F2YRn4Lay2JxPvUtOin8EDsETHz/anIS0+brzGCn01cn7bCl76THFcQ4o8Wuzn8CAvPZKB0WwgLi9/+vhkNeQUVCkAsOGopDUVBOXlRa6vw7FIfUY0k+QTkuOlpaZg6aqx8XHQoqMoJnzRw0F18umkQFtGTkBIVElbn4JHj5xbU4aH61nDOmucGZQ0BQnl9OVEbhlyReSUEuaV07E30THUsCUl1zHT0zsjOZ580X1HcoOIQlpPl4JeQvqfl0bBUMnO25aCkJzv84aK4brnuFdPQMuOjoGSkJri8XmIvmCwyvnr2JowG/jrW9iZXlGZL+J/Js5Lc7L/BXPy6EMJ/JvPxw0Nxsv5wWS51b1ABGFkoCABPtxeVsju50/4nmNyF/6r8gFDK30rFXsLIyPxsbn5WtvoEtF4Ce+UzU1YWD5g+I6zmSN9bRt3LiAjDTnWGvLhezdNVxjRMwu0bSsZ6Bri4XyJ9d11gJEyNj+7vT+bP9cuYd7K1kbA0sHMztTazNXbgU5B4Lnk35ndYLqMgZlfk5pbCtjr6JgaW9gI6tGRcd4zljwLkagDPufwb9mf5KvQsGDOcXWoY/MLih7M8+AcvfdQCwMFASsN7kcAf1Vyyu1Tifc0YAJQET4I88/qQHv7GBnpmB/h+UYT5nRH+D0Z+gf8vs5uzQnhsQA9Nfs7uh3Nm62dkZ6PM52NtbWV4ZGd35uAAMZwZ8bvV/QtxWhQvAQnsuFnBuMzdHcQd3e9vfbr5AShpYOlwaJb+VuZUtF+MZ8vLDQXO379K1SUtLKIjKXPw4c1RyvEpa8oIyvHK8CtJyXEJnLufMOu+0XkLlpB9LCQgKaPFLy0mduborQ77beonll5aQltMSEpWQuJrfq8uZA/nVcxcqLMcrcOa3Fc4c78WSsJybPf1Nkp+Im6QKgsoKXMxMZ67j4nONv2i+ieOTlhM48+8AwLmDurpcg6/6LiaI5sYMcdDc8MMckryiUkpSAlcekveXez/zTNLXWkFxKAmKCosocElJy0nySnDQXP286pR9zCshqqDCxS8hyCt3Hl04aK6bLjnR/GJ15bXl7XVs7bmYznbP5efaYV+230QKmVia2BlzMZwZMwPL+ecaetVxib12r5f0AEb68215efnle28yv2674nK2Ty42y9WOudN7U58LM71jADd6bnO/BNOd464uv3jfgF/Rm9ibX7YCmBnOjYX1Nvuf3Xdk/Gz/K0F3CM+/8p9t/7MNfGnvNxouETdM5+yXvKiqINd5JKA/83EXP646rvfHues6355niHPju7lpaG6y4uB7rKAgLSV/TX9pTVe/zthZWdrZy5u4nkf9cxdyxutnyzVGVM/K8qIBcO7czlfquuEacaHgde8NbX+pe2ZwV393tD1T95ZKHPJn3/+kH4Dpkv3f6XdufHT/cf1uaHQ2tzem8wx6Y/NeOrZrF3BmR6xXXu2WV7i1Nj9X+Xzif+n1U6tzlc8zIOZz67q7zPKiZ7neTch5VL9svFTud7FakgKi/CKiEgL/D+XflskhqWNiyW9+Hgl5bQ10bqVrd7ou3OYNV8khKCCqcDWai1D4M4oZ6F8nFufJDe15zvob4ILbNYezAUrySf/f8Lqmu4rQf6a57rzEXxjO1dxdZwMX3lHKytZCx/zMwM/zGqZzFsxnDvdPkNvEl47ympr1PMzR0l0EvF/UtzB/kP3buOnozlfzfLX/EvcnLX7nw3DmTgGsrHdV+Z0Rn73lP16DP2H+MJw7y3HmD1gBd0Zyc1HujuIXOd1VLGMC3B3Abfqfiv0i/ZnAAW7ofcsUaH7ZwvmmujJFDklBqceXgOuM8jy1u7pw0NzIHOV0bA3Okn0AK+PFHJ+v+dkkXbXesM6zEMt4HZSZGK7N8hIhb2CtY6tjb2ULOONzvnuvLmd7+FfPbSQd12X2f3W5gaS7RArbWjlY852VpEZnXyz171aSd7svizh7A4vr5Jf2YtXOJ5D+vHz71fMLeUZ903nRXWS/f3Ref+XSrxhfM7pge5Gk3+R7HlsBDDf4XlL9wl2QyZ0ZhtU/QfYLx/G7AV9gL7fevziO33zSjQYBEzsdXfP/rJBbPDnk9WytzM3PLFxL4VY4ob0Mwv+SkLu8LvKlK691M0TcaP4JuzkLd7G/zdB5489hAJguUoLLyyXB7SFeJPXX8Y7v/KyFi/WM++XnbDuZ/7LGi+90v3fTXWcKv1hdbc7LrOt6U/7MVzh+q/auTf18e94yrbvIs3B55UI4+HivhQkICvE+lrheIj4zo4t9ee4zri5nfC4abzvES29z7kEvP7/c4C8/9At9UST/Cfyreqa5qchF9Xim4x+F3inb/qFcwHmNAmC8yA+Z/iD6F1zRwPbvZfwC/E74d7J+9l8ZvIOdvZXF2YpertDtEZxF96vYBDgPTn+L/Vt2FwLPi9WLOEf3l6xuKMZnddZhIWFiaXBZyd+kvtt3NQNyojIyd+qSs8jOcLsqUZDjlZI/K/Mvqu5zN0N7VUbd7LjKoG9x5FAQ5P1D0fPvc//F71bGdb2H6O56wFveif6PJcDNeP3nQu0y2f8T0/Opuvz7ra64TJVv+sRfyfPdIu6G3/t5iHPHF/7uDG8hf487t10hw0Xacnn5kyukubljL1KVv9q+/zmf8aeN+yeCf7hr/4rohqQbs3nnoOE/O8+sF2nx5eUP8/yXVgv4CwM7X7HLv98M7F/ZNjekXkaRn0stIy3zWObXWt+qaOkvtupvRe4f98hZlGX+8xDoLzYe/e8nGf/aHpETPGfO98ud8PHyi98+Ajj3uYC/OAEAXEj440TS3ODEIcovLaUlonib8ZkDYLnD95+f/fMk8RbTaxkK/xUhCrek3BkI4Dfv++8IUbxeoNtrwkFzy5g45BV4FR7L/7Ktm9P8F0cTtw7AWC7OvwALLPTTGP/CagAXAMDVeG5azU8xFxK1fh7w/hNS6f+RVPq/k/pLFIcMr5TgH3YJ3W/lDM1d5AWQT1r5Fh0AcNe0L7//xP2rDu6fjgyXcEFnewNL/RslAoD2vA64ulyS/Ya5yv1vWcH1efhfJofnpTXduTp0DHT/THJ4cYbAenG2S/vHGHNj+OdTcn7L8boauFlq0NxW7HxBL9eeQ4FXXvy6/r15e+lu8Xs3I/7T/aOfi/KH+0XCZ472+n7L7TPTW/cQznP+MxnXa013PlV05+OnOxvVjZ5r8IWEa/Tt2b3ZdZP3rZMa+nObpT8XQM90KeC3GHgt5fdTop/j/a3/p/f5p5bnT3H5Lvx37rcPcM9vCsgJ8v5xFm8r+49m8Q9DuwXnoPkl6Pb5N4e8jCC/6P9W9v+Plb21mNdJ0a2a6+b9wl/7m0OeX05aQkLrVt3xf3G6cpfb2axd+awz58Un/+to5KLyu7z1dTutvdlxG319x+tPUeU24IKOXuCv81zG8/sMDH8Z7i///rY646C54s8hJMGrcOvgBkB7cZh8ebl9dvPrpjnz2bpcfu7eSv9zYn6exzP+XeV3bqT/qcT8+uBI1NLSwPbaIO88q/Mb4DfCq0X8a8Ibq3xNKO1g/5Ph3Xn8DfAb4RXDvya8aVc01wt3bqOXpskhIsj7c5dcCrm8q0zHcGEwl5czP3qj6wb26n4y3WXtf3m5Bt+413yFvj44ZzkvBq4u1+g/PoFhoH+tzPlx2sVdSkbmW8emNzS60Xqt1kVmxUp/54mYn/13ya6PyhnOVTsXyXib7KaOVzcdrvS7fPzn4nCd9eejJTd0u2r5qdeFgPM9x/QTfVOn62dT/qTP7b6Lxfy1hhxyonx81/v1PLmV+EP6ryAtc6cwOU8lmVj+oni7eOrgooak/b16+8XrzAWf7SbJP3AGMP81Z9q/OMChucntVllxJ/ZI8D6W4hfR4lOQ+r3YAjD8G3ekf2N4LeK8+rotg+Vu0fiT+gb2XygOfg/GfyD4/RDkdjjmuPNM0K/ih5HxTg1z5+EhWV6F3+qevwoZf3muwEEj+ys43H484vKn1kUo1hK6PZV/ODz8J04Pf/rwO0xvi5L8b4iS/KMoif+GKIk/ipL/b4j641qdH1lpCWnx3xFI/x8QeIf1n8RK/nZQ85dSAf+aVMm/lCr53xus5N8MVvK/NljJvxmsxH9vsBJ/M1gJrd9ixX9qtBK/jfayDPxX9wzdP5B4h+sdYXy3hTGcP/Hw7zwi9Weu18Ju3YL8meyfcWL5m+B3Hhz/Vthtrndk/SES0p+FQvq/SiDOT6cvT+7+ocBbgfNulySvsOAfgjzTnRD8N2R3WZ6Fqt8G838ApSYx9g5OAIBDS+xdeTyU6xcfkWQny9DIWJIJMWMkjGyNbBmhMgqh7KGQ5UYKhREtIhq5idK91jRaJalxRZRE6lJdRaRkyUSLn9nMO6/h6neXv+7nYyzv87znPM95znmWc77nQcc9IFGz71lmc6hrzk2dA/MfUMcf4wtiSbMKixl2Phc/+hELxdllz5EqiBnYupFzMKPvArXn0kgQVTZmm8E9o9qatt7sklw9H2abOfdsM7hnVGaoube482EG7pmZBRYcYqFhMLU5qzuwOpOEna2Nm+NMi0Eh/38dA5IEstnAwTD1/hqbDRzYmHLojdZfY2PKCX0KAEROn16ZPjv6N+a5lVlnjl07Bw/atJsehBZh9/5PHwTBFNlwckx/ANOHwJ5sw1bGVh/YLI4vcWg3vYDVei2a7x/NyFoBlbK9w2wyR06g/jjsDNjpSc9U0qVFc1czRM4qYFMNFloZuEQwdYTDLDef7Qw13gZcOti9RZos/fgHAAT0wJQNM2jjiF2Ps8fPFsijJqnooWZHsq+hTa5IrZm+Pdah2tHEdBaRzuY8nIf3ECSzv3YS/hMggOZ0D6h9ceN8BkbOAGNrcqg8Pd9MDT7r7EUngJ5d1Gi6qLVnOiVZ0w2AIhsX+3lz0Z4e0Lm52E8H1gDKM0XFFphyw6ZYnGL6HFRrXroFCuuztAusXnPo13wUDKxhP6RiP6pjQCWbGTwCCg8gPfAiyAFcwrFXwKH4EbMBh2b+vVMCSNfY3I8g3QI4IOfyQM7LBcnmgwQ7IefyQs7HDQnyQ4LUGqwCf0n35uPpmzm881l6fnwuBTqOOc+k1DVz9Q+CpsAOR2oxazoC5eptNGHnh5qDoQ59EkLNHECqM3KaoNt6GxMHh7+LLIAaKFWJmlbDKboIPiLTE3CANWmvzrbM6804YbMtPXQNpp5DZl/lOWBi6GibWSCbqNkgmzNz4NiJomcH+cwPCUqXDRDJBJhU3H4QfKrNPF3O9FXPIIdxsLEEyMjRYtMG05kHWVBcku0gO21cM0IlAFoYO5tNIGcULdt1zf9BF0AKs8HS9m+jC6A19TZALBg7e9x6eyzLlmZuHPTmcqHM6ewCqD0onZK+pq6eCdSbB1wTlAfJ8KWxwGksawAHdGZUxVjamlvaTucC/9WGsVObGk2gbJkALmCeocMs0Zp/AgPKCuWY2+BMprv8zzEEsGFOM4zOW2PxrIz4GZMjzd/woxMZAMw4PTycwYwYTQB7jAXeDmtvY2lrDUpcpnmCaAkI1L0GGzSDmRK9VpcZkQYkQjNnnlD30LAQD3cWqAOJoh2TqVF9WuxuRgXQixx5gEsZmUfAPmA0WWHjqZnJxNaWiQjYErTHn56xgKRCa+hBe2r+DauAHt/3pKaV0h+A0A/AIkZdzjkSwOeMitM4F1BF1nNGwss6E6YBMe4jQQJRDFq0MUFN34yCBCbOM58xY/M6tFMiLddsDesNtsR5xkMUgwdjgNThcG3W7SsoDjxQ0zy0GOgyGlwAVArEeDAlSu0AmpEGDCxhpg8w+k9dDKZHj5pewgDsAEAeIJQHrbc6NF3RnonyAMM8aL4U6vEURT3XzIB5gHAebGMGBnkAUh/BmZSsAoauAiAq2Ihg98AdpkERjHwfWibsaqp4qFxApexv0MCh1BQj6r0yeqsBtVmwUZudXqE4L6+QnaFghB6ghJWOSVVY9tbDGZmYtBJWRYcwD9oTFNWi6e4+HWbSJrOMfpUFY8wwuE2ONjicNae98Q+CaplgkPVYdrwTeA6l7tq0QTBnoItofojCH8cT0t5gegDZjibsib2gHmDmwLbP2RUaupgubYCQ6bkY7OBhc9+AACDQWRsEdJ4un/HWnHhqVgW6yTIYUxd76g1Y9OuwON1nZj71kabdZ1b5VW+2+8wgcE8L+w0QSNRyCCQ2DgIZn5z6+RYCCUNCIP3bIBD9zCkigZ8Mzbim6o7R7z4baC1PjteSSHilHXdgW2JCX4A9/+axSLkXOi+X8Kg/fuprLEC4bVO+w5u3MlUgBOctu3+taWCtFiYF6fNcagRzbvR6Se0ldT6F7bD1rWFCBRJtYRpdeSTybthTilz4x++wWi1B0FeaO/SQO7SH4J59flxXLtxfw5Qv81C86PbihWImVpG+hHTxdfEr5SMGH1Gih0QHv9WFWy22QvgUa5okIU35hrg9ixNChB+ja6AOo+dfT/aKiXmkFP7C3xsptV5BERLReQrWS1STGhEevgXLtL9TuQvbJaHAEy9a7Y2b6vLkJDcEW2H2/mawiyPwFrJ/Rd4EhrxbzopzI/niX+26gPIORh57inHs0hePI3DtJ0k+0U38JhfYu9Q1pOmnlANdBmNdEfqbEm7UNpa13Qlz8Sl+RRz5LCVm4qWo+JH3y1J3PjPoHdFDWvEKgrRftZh/rKSMGzqSGrXELnJ1f9hph6og153Cy6QnqpZ3C9CF8I0AP4tNIqiCrmKbRQ7yNDk4l9648TfIgWuIIYdTNX7PjUUPVZ9sq7TvePkHTxR/wkTrmMZXdAxhbY7Ctcq+JZcDZbMPquFbnQcDRSolktIv8xTlxPFK7aWgjCa/jgxa+F3bFiVb7lzcHw2rIyq2DPHEUga7Kj9IE7DvbrqWvquy71d24q1VgPRW4N+5bjmdppvb0SPTW9r1EOtTfO36LZUNdWl8E7v3pyEPVYQ+W5xhgbjV2YWCCvodzEuWiM2ULh3qCr+UgrTxzoTs0+8pteCCLj/RVObUO/Vjc4xQ2QPU+Qrrm2GxFxoe1iJO57r1VyCEzu0QvLUVBtmI9qAYGD21GFb8djRfWojXxfvkL21aWcGUb2oj47DiZj6Z8mX2EuMmyKZri07ULlrYE/30KymqsqN0dZmx/2nvU5ckTJIR1or+xXxabc5Iv6EuedeCtd+HVSFXo83urAwlEWEewwMfXi/pmaSEKxyGxo9W5r81PL+iR6a4FdZvqpdSqm3t4x82Cv0Eh0kmnCUbaN75qtbw5HDaCp6bVq7km8F39yirCNumkGyPekzUU+R7nhfav01GLE88VeiOelVQpIxQEc+HytwdXTaS7vGHk7BRHsbcyo0wAk0yXHUQWkwilj6zMN9K6fmS7tGC3nWkVsGjogOOrbrR+WEoVnoCVyWR9hiC3Zh47GNMtfSB7maI7umLZn7DzskzLv77N+yOK4Ghb5lVfnfsoMa4O1UJBifV5JShwYiEVR/CPy0mwmA527ZFi7yAH6wIOoYIORvq6KeB3YW4uu6xgnPAoisqbgry8bdd9qyhfCG0+5EuORebd5S7lvZRvjR6VbTg9XOE+W9XX0qX939ddpRQf0kQoZCA5YKN/YT0yC977SF88C5MOUnM0cread8vVx/uE7lI7FGLx3Lti7mZLKaUgJXzzifCMtAlhovXpgbhfvumulJbGkUe4XG0CzRf0HAF+kJzv1+ulMFi9by7xst7hskIy5T06yVRjUa/QeXhPughTPXlFT5orrI2cewJe3yez0GS1BuiUqpn4OCHyMgz0jHan+Cv+4a4emFk6HFlBIl4XLkGGrI=
*/