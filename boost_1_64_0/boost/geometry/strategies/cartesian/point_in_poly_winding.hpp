// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013, 2014, 2016, 2017, 2018, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_CARTESIAN_POINT_IN_POLY_WINDING_HPP
#define BOOST_GEOMETRY_STRATEGY_CARTESIAN_POINT_IN_POLY_WINDING_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#include <boost/geometry/strategies/cartesian/point_in_box.hpp>
#include <boost/geometry/strategies/cartesian/disjoint_box_box.hpp>
#include <boost/geometry/strategies/cartesian/side_by_triangle.hpp>
#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/within.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace within
{


/*!
\brief Within detection using winding rule in cartesian coordinate system.
\ingroup strategies
\tparam Point_ \tparam_point
\tparam PointOfSegment_ \tparam_segment_point
\tparam CalculationType \tparam_calculation
\author Barend Gehrels

\qbk{
[heading See also]
[link geometry.reference.algorithms.within.within_3_with_strategy within (with strategy)]
}
 */
template
<
    typename Point_ = void, // for backward compatibility
    typename PointOfSegment_ = Point_, // for backward compatibility
    typename CalculationType = void
>
class cartesian_winding
{
    template <typename Point, typename PointOfSegment>
    struct calculation_type
        : select_calculation_type
            <
                Point,
                PointOfSegment,
                CalculationType
            >
    {};
    
    /*! subclass to keep state */
    class counter
    {
        int m_count;
        bool m_touches;

        inline int code() const
        {
            return m_touches ? 0 : m_count == 0 ? -1 : 1;
        }

    public :
        friend class cartesian_winding;

        inline counter()
            : m_count(0)
            , m_touches(false)
        {}

    };

public:
    typedef cartesian_tag cs_tag;

    typedef side::side_by_triangle<CalculationType> side_strategy_type;

    static inline side_strategy_type get_side_strategy()
    {
        return side_strategy_type();
    }

    typedef expand::cartesian_point expand_point_strategy_type;

    typedef typename side_strategy_type::envelope_strategy_type envelope_strategy_type;

    static inline envelope_strategy_type get_envelope_strategy()
    {
        return side_strategy_type::get_envelope_strategy();
    }

    typedef typename side_strategy_type::disjoint_strategy_type disjoint_strategy_type;

    static inline disjoint_strategy_type get_disjoint_strategy()
    {
        return side_strategy_type::get_disjoint_strategy();
    }

    typedef typename side_strategy_type::equals_point_point_strategy_type equals_point_point_strategy_type;
    static inline equals_point_point_strategy_type get_equals_point_point_strategy()
    {
        return side_strategy_type::get_equals_point_point_strategy();
    }

    typedef disjoint::cartesian_box_box disjoint_box_box_strategy_type;
    static inline disjoint_box_box_strategy_type get_disjoint_box_box_strategy()
    {
        return disjoint_box_box_strategy_type();
    }

    typedef covered_by::cartesian_point_box disjoint_point_box_strategy_type;

    // Typedefs and static methods to fulfill the concept
    typedef counter state_type;

    template <typename Point, typename PointOfSegment>
    static inline bool apply(Point const& point,
                             PointOfSegment const& s1, PointOfSegment const& s2,
                             counter& state)
    {
        bool eq1 = false;
        bool eq2 = false;

        int count = check_segment(point, s1, s2, state, eq1, eq2);
        if (count != 0)
        {
            int side = 0;
            if (count == 1 || count == -1)
            {
                side = side_equal(point, eq1 ? s1 : s2, count);
            }
            else // count == 2 || count == -2
            {
                // 1 left, -1 right
                side = side_strategy_type::apply(s1, s2, point);
            }
            
            if (side == 0)
            {
                // Point is lying on segment
                state.m_touches = true;
                state.m_count = 0;
                return false;
            }

            // Side is NEG for right, POS for left.
            // The count is -2 for left, 2 for right (or -1/1)
            // Side positive thus means RIGHT and LEFTSIDE or LEFT and RIGHTSIDE
            // See accompagnying figure (TODO)
            if (side * count > 0)
            {
                state.m_count += count;
            }
        }
        return ! state.m_touches;
    }

    static inline int result(counter const& state)
    {
        return state.code();
    }

private:
    template <typename Point, typename PointOfSegment>
    static inline int check_segment(Point const& point,
                                    PointOfSegment const& seg1,
                                    PointOfSegment const& seg2,
                                    counter& state,
                                    bool& eq1, bool& eq2)
    {
        if (check_touch(point, seg1, seg2, state, eq1, eq2))
        {
            return 0;
        }

        return calculate_count(point, seg1, seg2, eq1, eq2);
    }

    template <typename Point, typename PointOfSegment>
    static inline bool check_touch(Point const& point,
                                   PointOfSegment const& seg1,
                                   PointOfSegment const& seg2,
                                   counter& state,
                                   bool& eq1, bool& eq2)
    {
        typedef typename calculation_type<Point, PointOfSegment>::type calc_t;

        calc_t const px = get<0>(point);
        calc_t const s1x = get<0>(seg1);
        calc_t const s2x = get<0>(seg2);

        eq1 = math::equals(s1x, px);
        eq2 = math::equals(s2x, px);

        // Both equal p -> segment vertical
        // The only thing which has to be done is check if point is ON segment
        if (eq1 && eq2)
        {
            calc_t const py = get<1>(point);
            calc_t const s1y = get<1>(seg1);
            calc_t const s2y = get<1>(seg2);
            if ((s1y <= py && s2y >= py) || (s2y <= py && s1y >= py))
            {
                state.m_touches = true;
            }
            return true;
        }
        return false;
    }

    template <typename Point, typename PointOfSegment>
    static inline int calculate_count(Point const& point,
                                      PointOfSegment const& seg1,
                                      PointOfSegment const& seg2,
                                      bool eq1, bool eq2)
    {
        typedef typename calculation_type<Point, PointOfSegment>::type calc_t;

        calc_t const p = get<0>(point);
        calc_t const s1 = get<0>(seg1);
        calc_t const s2 = get<0>(seg2);

        return eq1 ? (s2 > p ?  1 : -1)  // Point on level s1, E/W depending on s2
             : eq2 ? (s1 > p ? -1 :  1)  // idem
             : s1 < p && s2 > p ?  2     // Point between s1 -> s2 --> E
             : s2 < p && s1 > p ? -2     // Point between s2 -> s1 --> W
             : 0;
    }

    template <typename Point, typename PointOfSegment>
    static inline int side_equal(Point const& point,
                                 PointOfSegment const& se,
                                 int count)
    {
        // NOTE: for D=0 the signs would be reversed
        return math::equals(get<1>(point), get<1>(se)) ?
                0 :
                get<1>(point) < get<1>(se) ?
                    // assuming count is equal to 1 or -1
                    -count : // ( count > 0 ? -1 : 1) :
                    count;   // ( count > 0 ? 1 : -1) ;
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename PointLike, typename Geometry, typename AnyTag1, typename AnyTag2>
struct default_strategy<PointLike, Geometry, AnyTag1, AnyTag2, pointlike_tag, polygonal_tag, cartesian_tag, cartesian_tag>
{
    typedef cartesian_winding<> type;
};

template <typename PointLike, typename Geometry, typename AnyTag1, typename AnyTag2>
struct default_strategy<PointLike, Geometry, AnyTag1, AnyTag2, pointlike_tag, linear_tag, cartesian_tag, cartesian_tag>
{
    typedef cartesian_winding<> type;
};

} // namespace services

#endif


}} // namespace strategy::within


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace strategy { namespace covered_by { namespace services
{

template <typename PointLike, typename Geometry, typename AnyTag1, typename AnyTag2>
struct default_strategy<PointLike, Geometry, AnyTag1, AnyTag2, pointlike_tag, polygonal_tag, cartesian_tag, cartesian_tag>
{
    typedef within::cartesian_winding<> type;
};

template <typename PointLike, typename Geometry, typename AnyTag1, typename AnyTag2>
struct default_strategy<PointLike, Geometry, AnyTag1, AnyTag2, pointlike_tag, linear_tag, cartesian_tag, cartesian_tag>
{
    typedef within::cartesian_winding<> type;
};

}}} // namespace strategy::covered_by::services
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_CARTESIAN_POINT_IN_POLY_WINDING_HPP

/* point_in_poly_winding.hpp
vseKlt84luH9PIfjWY8PsAEfZOhDn3Gd3/X/Y/vQPxT6+E5iFT7KOnyMF3Eye/NJjuUUPsynOYcz+CafDfObycN8jsXN73lW5Rw25Vx25jzexPmcwIVcyDQu5ctcxiXhfUfnCtf1w/V+65F+jWt45IVw71xN3sB67MeL2Z/xHMhrOIgpTOZQDua9vJHTOYSvcii381b+xNuYP3J84f0cw4c5lnv5AP/MB/kDJ7CgZZzIQnyIxfgwK/MRNuejvIaPsTMfZz8+wVRO5jBO4URO5e85ne9xBrfxWX7BmdzPWTzA55k/j/LnyZzLopzP8/kye3MpB3I5h3AFR/I13s+VnMBVDPdYhuv81imHeyyfCPfkTeZpfJJNOIXxfJpXcwY7cw77cj5H8gWO4kt8gAt5gIdyhWv74Zq/+abvG7szruOHepCLFzA3GzMP45kv1IMTOI4n8kGexEdZiE+zCNNYlO+xGL9hcUb245I8g6ewEUvxEpZmS57KRJbhYJblSJbjHSzPB3gap7MC5/B0prEiX+E53MDq3MQarGWd67Iez+VveR4v5/lszXqhXjXkLDbii7yIr/BirmRjrmNT9rd9mzGZTTk6r3aPPfJp95jIePbjZRzFlpzI1pzCNlzIK/gq23IN23Ed23Mvr2Ul2+96VmU31mZ3NmQPxjOBrZiYWe/CNXu+lEO9WxfumVzPanyTdbkx1L932Ifvcgjf49PczJl8n7O5hfP4IdPb5VwZ19G1BaH9OSvSLod6d3reaL2rycasxY6szf6sywd5Lh/jeVzK8/kG6/FdNuA2NuQ+Xsgf2Ih5c9luLMQm/C2bsQMv4QO8nM+wFRexNTewDbfxCn7PdixuHdqzGjuwKa9mJ17DZHbkA+zM19iV77Ebv2J3/sweLKFcEliTPdmCvdmDfdiLfRnuicq4xu7a+7H3RL0ajkvrWZkbeDHfZAu+xTZ8m535Lofzj5zIP3Ey3+MMbuY8vs/F3MLV/Jjv8BO+z238iZ/yxHAPTyXu4AXcyYu4i+35JUdwL+/lPk7k1/w9D3A6v+Fsfstl/I5v8RA/4Pfcxh/4GX/kDh5mOC8I19m1jTmcFwxUrhWZxLM5iK2ZzBs5mM9zSOb5Y7jWzcE53Ctwa17rzdt4AUeyKW8P73sHO/FOJvIuJvHu8P5d48K1ZGwN2zdyvtg+vP+D4fx0AmvwIcbzYb7ASYz88aO8gY/xT3ycW/gEo89tDdeEOSvMJ+tzW28I7cEAVuFANmASu2S5dzqFtzGVMziYJ3m/G1mFw3gub2ZP3sZhHMEnOJJP8U5O510M9TzjGrFrx9nrefSeufJszXP/wt6dwFk97QEAb1cUlTYppUK7UpQWilK0LxKibaZFy4xmShSFUE+RXp6Q5IkXQgghhBBC9uwhZIl54cn2vO+de+bO/GfuaOG9z3uf1/34+Xb/87//c/7nf/7rvecc9mRn9uFA9uUI9ucZPJGTOYDTeDIX8FTeytN4P0/nUxwc6nEqq3IED+RoNuFYHs9xvI3j+SPTeJS8pnMxz+TtnMCHmMGnOInv8Sx+zMn8lmezlfWdyuN5HidwOi/n+VzCC3kLZzC73hQLz4fDc2PlpRmF9Wd2f63FXO/yJfbgy+zPVziCrzKTr/FcvskH+TYf4ztcz3f5Ht/jx9zILH4QrvM+5N78iIfxY7biZg7iZ0zn55zHL3gbv+RT3MLX+RU3cis/5Tf8mt9yX+v0HavxBzbkTzyMP7MNf2FnFlefhrIER7Mk57AU53Ef3sXyfJkV+DYr8UtWZjnlXIVVuB9PY20u4YG8j3VYuoRzG6vzENZifR7IhmzARuzBJuzL5kzjYcxkS07j4VzA1vw=
*/