// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2021.
// Modifications copyright (c) 2013-2021 Oracle and/or its affiliates.
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

#include <boost/geometry/strategy/cartesian/expand_point.hpp>
#include <boost/geometry/strategies/side.hpp>

#include <boost/geometry/strategies/cartesian/point_in_box.hpp>
#include <boost/geometry/strategies/cartesian/disjoint_box_box.hpp>
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
                using side_strategy_type
                    = typename side::services::default_strategy
                        <cartesian_tag, CalculationType>::type;
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
mmJtnHtrmoDaJv0gBiz9MGFl41ZKkIh7ZKkjg6sCRwuYKGo9SXvNr+vXi6XGZjMjJbgW5V0z1iCkzCfpLvAQRmIS+0v2rgZp/dWSNkXyyZrJmnPyx7EHJeNXPcIQn/q19vRIfBk9+tCPvPgEATjzGpj4mM0/ugaHP+zmMd/yMx2TcKIIrE3g1N+xAhCqJCk8QkBICXoEwRgwmJchFTS1e+waQgAALP/TGdc0iH4EyslB6iEQWCyO9QSoxSLJoLnPz2rYUax2TOnaxkR3BKefVoOp9KuLZOzOg6AGTvcHn10TIg8J5idyW1WkI6JTVaAFzoX7n4a+vjn0ACauvrrU3OSjtTvm/l4BgY2sglFmCEw0StAW0dpbgsi++052x8ZiHdScb1eXl9EAHu5fB46ErpbABT89/rnxnr4d6GbK3xCxBlRdPMSP0dt+F1eLj5aBnqsYt4Nv9yc+zK4Sc3JgOP+qEYnZiI1jLs+BPzNR6q6u+I9pa2RLYNX/yaATKXTkQ0ZxuUC5pPh2cXg7K8cxEKA1dRSlinTA/p3EqRhDNpVBUkAbO0gEryScpggFNuo3qQuoCm0OUiabLhJQHyYtiCHt+8Yoa0CAwJ83EDgpr1mBt1/ohIuNKjXFHI6YT4JQorBiodSS2imFyOX89P3EdXNicpcBqA48e0+FnOeR+Mtic9AKkDhND6jDuU5ERui69udZDhsa8QttZwjqQxivEhDGLMKg/SBDmLHq4nsXSDspFUVO4TYqHRqqmLXqAPjtBQPBkhMpheHS/EtSaVZuoTIJRvuw4iHVSQ5sAGGJ4BE2wZTQvPz5mMDgSSdHMhtKA6vKnjIQYz1Qrv1qNSyNCFwIvSCs+zsaIQyo3LXNtI5KYaHPdMySQH8G4bBHhwlKgcHzylUO6jbKC+u2DCjRX+D8Z0AV/QL9ZtHpm3eLO3r7DrysxYlVo90BG/B9+2R1Nd6FbIl7vbe72hzeOl5zIVYZeJxhfu/w9wQhrubmO49XifXbWW7wrvUtOCioiR/C/p7mXT7d3nrYrbefRxgtWW0HbNbYyBZkth/unc6SJomEhoXtghEc95/Z2Np/mMbHSp7gFGDTK1lrmcGho6FtmE9mBFsABAk0eUliLlVO+N/R6f6QyAEckIJY3VyJTi5CiRaE22msgEujEsoAFBjlT62LZ7fKtOnIYIEtbGAf3b4BrGMAbEgplOJ82vOQ/3jzNK/9HJQfWpLqesYNqejkdWXUljgYwUh4z0tCIduSOXBdqME65FcJtsa8VAhz20PWhPEbLuwIetgFGzGmG4N8iLeTh7ZzAyMNw+SzMPYKM+ijqikt6mwjJDEksLDddr8PRKLQ5+aq5cg7cTzLuBMaQn5/eR9+ggjNdlHxybbY6z5+0yPrD1Zv6pnfee2gTzfnDaLf6efKW6T0CfXls0Pv69vfc+vnyXMjmsXZg/SQlzdDliW6ygBl7oHwzgafbz5db2OYGIR7SohKq9ZAlg0BAhAKEYypAJWBBIT0Ed57CADuhYahpJDks5OFgANOoGYCLQLjckIRBL3W0WMIW/m4aAACJibjAmkes2jEkOpfoDRFV6mai/EPAEoM2L/0M5YpGEJfiqKFS74fr+xP4hfBXmecGxLJCoqzkfQPEXmXZocsmmlDWi3M1MWliZD4Tpk7sr034mgatmAxYwB6dkfwsyjjeGmDToLP9xjLCcmjxNuve6XUk8E4pga11VQwS6AFCOLUUV9sA7sDIpb95euZRDMCv69KNHL6SO/5ghaOiUQAai0njmA7E5j+K7cP++9LvTO9r05w79BdCUng1hmIREgG876qAm6bDxm/DpA4teKWqn3CEnqDqI9IEXKAuOCvcF5LJZYmYUjRqvbei2gFnXRlpg3b8npihrlF/bUvwPtQPB0uGN+I7J8tS2P0YYTQ1j6Rx301FxYCLyHW5Tkg6bh0ZIMm70CKEOOqAqcFJlP07Qhogy0XKtoOi3iqaeyGq2pQetbbfCBUycRpuDZ4qoFbJIChf1hOlRb7TEBrAYKQSRXp0f0ICZM2IcZE/WlNY0Ss3On3bvQRoZNFNpSmKmeJLipldz3WKwAIZYwhRHDZ5WSy7ZHM12ZyvLDU2XUwyq7/aJbVUTmxV+yVZtBT9NxbtW24Naixz2LpbKt3oHTYDJbaqmymCpGFyWxppp2wOgsOMR/gnhcyqV2y8xNAHJJhm3S8ZJQCm4vkAsuITKfmylU3e8BzFP8iY2tDhV18kjzhiu7IdiGlIbJYB5Kc5zQJ7jjVUg94rjbMcQnmxPlfFfMJimQpnyQIlmNQXPm8A3osFiQJ4UFPazjjwf/gGsz7JyE3J2IYh+ZOEHfRjIkPtTc7kefFtIwb4EgLlfZQ4a/K1rN2Hktiif6d3TGdWfX6o78h1IResFWondD8Ruhpp5XJd8fWPoyTPq/zVTnoMd8Vfb6n6bFjlzpELnMZzDaaztIyRlH/4+KQnoa4+FRzgYeuwI+5g3BAdDToeXnktXeD6OIMzpd03Lacci1LU9fz0Pr4KNQXDMnI+QwA5bZL3/70x/ph0G3lz2ZoLHENgLLOAeMuCvMcgls8UOQHSa5omKX/m4zYfQaal7ZUohUnQNK7FnYKmF/YBuRzcXIDceDD/c6VkPsrLMqN1VfWpR+Ry1VmLycGeXqR5KCdw0v5mA8JqIX21fSYqeHR/ZdCkG6r6a6eufjN4sm/xRNuQnE2zm+9nFXs76xEXWoCP4vwyX/cs7b05vt0Kv04Kv1EC8OO7u/u2tAYgPwFQsc6KOORUy+0/t+H2sKerjlS+JvPORIOVBEsOWbkejdwjl/EgkwYpg4FHP2SVDqSOmfVDhdL1J6kdl2pMdmpQnzxLtYWXbSZMJ871gDthU+FgJ/sNisshm8P/afoF0Zk+ZIBb2XHV1y0Cszj2yjZMvLiXiziWxsBvI9V2eMtHo7B4S6Nlj3mWXUPfo+KNtFv9QFNV6Ji/C0C4OP3ZDsQK3sqh1AON/3ok34Uk5jrVNzz9u1lTucnTWR6I8kxGPEw7peeFTujT+F1AfVjjdlPdcT2SSt05W18ydXRwq4Q5DFV0LvaoGOa/aSYVmiChVXu3nsn5fqKpY5VgMpMfGACZiAs4lRhdGsz3Gd6aEYm+7I808CK3UtgiSGokI1VgPUgnk1tbIbjq8qZYMWWRWwo1VLs0mWyca4Qw0IjBz1ZPSapwvi6XjoA7XrghJzwxDW044zuAqIDDCZQ6EKYN/CdfEaHdJytJZ0XEnOhkcsYaDHGdm88b3QqjJXByLXMVSficP+24oEt9zAWxDh0PRu+4IqV+8EBu4ToY4kna+2sqNQWNGwWAT0aslCMc2HGiNsVQSIDzICJwk2tJbGYvFxTM73haYItR0adPnWE/EgLzx8o6SfZOIKpdNAgMQ+aS+usbYsAWqrKn8YzAfE7/apOAq87x+olmRodKmOcvuBI3Dw5XvQ2UVlR4dYOvKESRtbGsYwEUrRItQLOKTAm5i/vaH6slgK7/0CHCP7Blg86LJa0I+uE/nJ2k6rXil8eWLbANKukX364qFxtTXqaXnrOkz1zGr5yt5FsS/wyXNk9IcDPl6DHuH/FKUJiQjNNqlUywWUhpOpBGU5RCXsQnscUP6EgPYR8fdKy5c6fpG0RLPPmFISBbBQlifXry2Wg52Egd6wvg9YJ+KaA8rGQzQdNnNA9RzfL04W9tvgpB7RDqGSuUq02u+ph1jAVV6lJXadi0G+AlgwMh5QZT5cbaNrsthQ6kbWnnGzWI2mG7WK4/N4JNotvysVw8ibdU6ktqE/YGMvpMBwUu101Pn5r0MrK92vGYGVgIMj4R1DKYoljw7eXRF4C1zO5bIBXumn63aqHfm1G4NDnlPBPFQWPpSGAV/KGFAiUsfz0H+WfItvjOXriqkB9LzD+wFEK+UfI168dfUsrbvuz7bN/taGMzq0iK7hV5xfLMey6CzQEsJtEW3gtPbl5bfT8poHezVedeAxTeOITubi5NT5yRU/64gSA2Hg1Kl24tnJOO9bg8p91IUHoCBLKzAHuGn30fj/Mdj9pMVuz3r4/i5OIPZ0Y4VA9yWxrHq44WsSBsXl5aZfb7A5GOD7ymiA9YVOX6au10zpuj4/so3rK2PNb7Sb0CBGEw02V5tMh0eXs6R0qJcWoPRJcx26PxkOS1AjmPTEdUotdQkVoIURULiJCRbtUFOeaxYSe05rAQLpnUQC+ETCiNT2SDRWn4HJKFmJriuGIqOt9V6kK/3xdMABnKp4m+CEvQM+V0ZaVOmX9RRQQGX28SaRzQT0o546aJYR9tIVBxqOqH6/mg63MRJJQxZq7Pl3+1T2pF4x7U0BeQeSVIAGwnzf4stuD6bWOR8K/thNyRjaV9vcwshrDrjQtI/VWAiIFhrg3Thtxh9g048lNgTUoBvG7gbWsuQAWSgzCBCeDnwg4H30B8OhD1BFD84Kx6V71SuhjkWlZhi6nRhPmXOLG1gFxatuZVRBrRYlCsJTxSYOASPgHV42d61R9K/E/EA0TPxrEkV9YgbqXtSpZV2dD8afCBQCa+KJbxva3cS51FIjuWlNS0RGBk4UOW8yv14ioW2wYzEne9qs+swgyPZepIwvwyw+QrQI/QlVX9isQleJnkQuSsSRYqcWZh1iRF+OWTieRsbl4uu4zBcJjR2rCaFIrM0gUAJSFy9xWJMOJQ0bAeRXnrwms5jMHJCipnG09sy/xcMkfkoEEYR2Q6SQ9sGIJJ44YuB4lArGmFlCaHsepHtB8DJfGy/uvcnDYcAiO2VgA1ts1lXlFtG5xHht+qbIzgLUpYjLA+7AqFkiJ7zvWsE/1VXVDMENt5Vf1fdthtbeDkCICkvo0mxk+A2ztvQBRqZn19HMlzho0IZoE6s3LJEsMZRMTlW7gEA1d7yiJixhWjwYYMFVsjW1TVXKiAmCiIXG8rKy/RQ2a3DNwzLUMdr7lQ5rL6M6KUha3losWa4ohbEK9C5fOR8GodLRklftfLqipVk9EDKOyVPoBY2eiXKg0x9Rc0WC3LYo3CtWAww1GyBd7q/yhApdoS2m5ZIFVTMRxW+pxLY+iGYReWTUYOyrZX/pTQw7ZnFIT0kvUmT+tKCRGx0+NyGevrdLJSNksL7pXPlybSVvcrIwldXP2lD9M4Y4utQbpdTHczCUwWgEoQqQCY7TDTY+qDRj6gFrOfE1qv+0MnBsTR+yyoaYl/YTDirxMDTnTWCpCoZo9wiYK+6Xt1nuBgA0tXoaDggeg//UZDws19DoyU3QRWWu5HMKK1c7YrSQNIfUK0Syq1skqYj5hC8wbMO0GuV7x2k/rKQI8YafZaXU8FWmTMNyi+CB7cFuq5gqqsZiJ+xGa7uD3hQUOGBcG5Ks3jgUNB0m7pVlpk+ql83alr+4XQVsXdlTX5LoCwZM36pqrMhnG9wP7VXJd7Q+tE8Kyz6ayMojdaw4B2Cbfmg7Ae+XtUfMi6nRxuo3S/11tEeQ7O3oId8vcvGv+FZuGJZT1gMrS/1ELeFJ/W7lx8T1RST+mhzMXsILb20odAJ9JHeh7enqRwQ81d70j8JoUoh+MKb1AipB/+lDwfHF4eHV20VR/SufzB1XEuvEGof+Ga40/qOnUMfyn+I4y8lIcNE7vY7HrBf/PPKpRwIzax/u/hYZqhBqsbjbcLyfRsMV3KV7J0YIUt7dax0mWIgm8KLm6dd21NjIvODbzM2ZWjDG9emIlon6Nc6xN6oAkYRsyWUpMQ6Tg4QLO/MvxiBm3O+x6fNxNA6tTt2EYHsJILVc3Ip38mbUpi3QB1Hg9u0uOymf12eTNzVNocA0/P1RyuFhlUAVkfDg45MZOZn45qrHsJSc4HMJb9raYkfdPspqZLY22euCS3gadpb1/rTFhQBpoqxMuseMFN35lfcxAsVA5LTOwTkajurM0TgujyMjTgWKkAfQ8pFLLnAnbl2Xql3981y/ZcMYTii93LAJnQY5AXminJvUVPSzw/FX/4ZupHaq32gmko3P1B+MZejrRudfWqBRrz0bLkRx4l4HSua49T4fjHgzohQgr6d1130UrimbiFzgdUXt5RRX1FIAqt4b7eAPxawk03zlh8Q8sWVxA7GzmOj7vzr8S0/kGaA0Q35T3OLoEDGeWzWmpHY24k26e5m73rit5rL2/Eq+ADVpMIwdFWQrvY6xlbq4rFKpP0roL79Y5+4AFQusby8WG/pC4b4/5q/wAEpyfnlbftfY0FV/FlSglJuVmzx0N2yGpBnH+u3UkNH2LGYsLJIKDYCvEUBIUOt4aoDnPWcZ/LuXm7N3I8IEEnBGctCX61+6dVa9RAhnlSrw6sQCbQ511AhDa3eEoKkF5lQN1yqibRAy4/Fb3EEdNbr4sTgNpMAFxgrU6+XLG1rn3rq+xpMNijSN/V2Lxg5Ae+kPM8OV43KeoBkX3kuxTc+VY9bA0GP13R+oPXApL85yICjjNSphNt6VldlHL6AlaLfDOPxbnmOALtrNSEUa5kNotNZNVJalkon8IwHewQQZPkOj3qKa56XjizpvYvUkBVS6bbs5B55dCtrbMiJs59Cs/cE2ppt4Tq3Q5vl7mfaxHo12GRyJWapHNPF7iFwmVYbZ6hIae6PEPRnfasQtHDko9LVgPqIvsowsX8zADVWfNXlOCpn/H6poS/447FtSw7wiqgGI347iE4a8gxW4aiff6046B6X7IMPEtZCwq7cuGOOdYGIDERek2cPYFGSnnh2AdyN3L9K0aLsODPC/PnecqyUpH2rfnDJhnIO47Ce2DcOWJfh0M7scPSrA9bIS6nudkxxuDDEEeFuPJGphiTCes9GFp4fb6PPe38uOkZPugP9Dz9FheFMxl6UH0b9ZfRrvs40E/aAYytXTMABzmh0+nJt725Dw/tZaQVujXT3ZNl3++vvZtGTDbku23lYx71a3HtmjtdIRq2bou3gLPbH4isgtYdocvZW6fCjnfO8irV0VrludMsg1D8IAy3biHpfBuFvWbGFLVokABpW5n5BWNKdUeFphcaoWNjqhaotY8lAW7Z6gP9adZ9ztOER9WMmXnJTtitFgpX2TbBRms8mqek9L4kxQmGMa0HHB05Vl5KIh9FdlMHcyrLQ+CzdJOFVakqDjHMFOAGwdzbXIYrCeQInZMF2f5aK/WhR7qLdCOG5PISJcQkfUWSDUcBIjvY2JeRuk/3iubVIAYR5VzODU3nHfbHsSynxw6sn5OlYOpFgcX95UgTw8Du2Ftdbc8vPARGqIpi6h/1Cr44uDN4nnOrB0XePaK+Olc6n6yDpUKGnnsZEjYkDaQL2OGL1x73JB3qXUXOAZDDldAS+z9vZHfPjxOhIkIdLdWdtKgjRFx5OgKdbC5om7iVPXTLXyYcjgdaZEso2TT3Dc6xWUXUe+K8glpE0s1XiwnsVi4J/5I3d9DuNipXrTGKm0DESZVdQMXsHnfJl6TSjzJJ6pU6ZwZA0rkkMBKksgK9ib+g4B709BEMHPOjxQK7NoWWkYwWmcw6MEnZRobJ4vYm4D1MoH4vXLb1N27Vn06kUM2kPilbYR1p35P/weNiB3hXBT2CH8Eoc1sLzqlfgUKZG1voHI4e8vEZU10cTRM5c6YtpAjuc9d3wMJ3r1WzginwA9+siOE
*/