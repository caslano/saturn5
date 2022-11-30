// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_COMPARABLE_DISTANCE_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_COMPARABLE_DISTANCE_INTERFACE_HPP


#include <boost/geometry/algorithms/detail/distance/interface.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/comparable_distance_result.hpp>
#include <boost/geometry/strategies/default_comparable_distance_result.hpp>
#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/strategies/distance/comparable.hpp>
#include <boost/geometry/strategies/distance/services.hpp>


namespace boost { namespace geometry
{


namespace resolve_strategy
{


template
<
    typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value
>
struct comparable_distance
{
    template <typename Geometry1, typename Geometry2>
    static inline
    typename comparable_distance_result<Geometry1, Geometry2, Strategies>::type
    apply(Geometry1 const& geometry1,
          Geometry2 const& geometry2,
          Strategies const& strategies)
    {
        return dispatch::distance
            <
                Geometry1, Geometry2,
                strategies::distance::detail::comparable<Strategies>
            >::apply(geometry1,
                     geometry2,
                     strategies::distance::detail::comparable<Strategies>(strategies));
    }
};

template <typename Strategy>
struct comparable_distance<Strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline
    typename comparable_distance_result<Geometry1, Geometry2, Strategy>::type
    apply(Geometry1 const& geometry1,
          Geometry2 const& geometry2,
          Strategy const& strategy)
    {
        using strategies::distance::services::strategy_converter;

        typedef decltype(strategy_converter<Strategy>::get(strategy))
            strategies_type;
        typedef strategies::distance::detail::comparable
            <
                strategies_type
            > comparable_strategies_type;
        
        return dispatch::distance
            <
                Geometry1, Geometry2,
                comparable_strategies_type
            >::apply(geometry1,
                     geometry2,
                     comparable_strategies_type(
                         strategy_converter<Strategy>::get(strategy)));
    }
};

template <>
struct comparable_distance<default_strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline typename comparable_distance_result
        <
            Geometry1, Geometry2, default_strategy
        >::type
    apply(Geometry1 const& geometry1,
          Geometry2 const& geometry2,
          default_strategy)
    {
        typedef strategies::distance::detail::comparable
            <
                typename strategies::distance::services::default_strategy
                    <
                        Geometry1, Geometry2
                    >::type
            > comparable_strategy_type;

        return dispatch::distance
            <
                Geometry1, Geometry2, comparable_strategy_type
            >::apply(geometry1, geometry2, comparable_strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant
{


template <typename Geometry1, typename Geometry2>
struct comparable_distance
{
    template <typename Strategy>
    static inline
    typename comparable_distance_result<Geometry1, Geometry2, Strategy>::type
    apply(Geometry1 const& geometry1,
          Geometry2 const& geometry2,
          Strategy const& strategy)
    {
        return resolve_strategy::comparable_distance
            <
                Strategy
            >::apply(geometry1, geometry2, strategy);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct comparable_distance
    <
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
        Geometry2
    >
{
    template <typename Strategy>
    struct visitor: static_visitor
        <
            typename comparable_distance_result
                <
                    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
                    Geometry2,
                    Strategy
                >::type
        >
    {
        Geometry2 const& m_geometry2;
        Strategy const& m_strategy;

        visitor(Geometry2 const& geometry2,
                Strategy const& strategy)
            : m_geometry2(geometry2),
              m_strategy(strategy)
        {}

        template <typename Geometry1>
        typename comparable_distance_result
            <
                Geometry1, Geometry2, Strategy
            >::type
        operator()(Geometry1 const& geometry1) const
        {
            return comparable_distance
                <
                    Geometry1,
                    Geometry2
                >::template apply
                    <
                        Strategy
                    >(geometry1, m_geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline typename comparable_distance_result
        <
            boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
            Geometry2,
            Strategy
        >::type
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
          Geometry2 const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry2, strategy), geometry1);
    }
};


template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct comparable_distance
    <
        Geometry1,
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>
    >
{
    template <typename Strategy>
    struct visitor: static_visitor
        <
            typename comparable_distance_result
                <
                    Geometry1,
                    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
                    Strategy
                >::type
        >
    {
        Geometry1 const& m_geometry1;
        Strategy const& m_strategy;

        visitor(Geometry1 const& geometry1,
                Strategy const& strategy)
            : m_geometry1(geometry1),
              m_strategy(strategy)
        {}

        template <typename Geometry2>
        typename comparable_distance_result
            <
                Geometry1, Geometry2, Strategy
            >::type
        operator()(Geometry2 const& geometry2) const
        {
            return comparable_distance
                <
                    Geometry1,
                    Geometry2
                >::template apply
                    <
                        Strategy
                    >(m_geometry1, geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline typename comparable_distance_result
        <
            Geometry1,
            boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
            Strategy
        >::type
    apply(Geometry1 const& geometry1,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry1, strategy), geometry2);
    }
};


template
<
    BOOST_VARIANT_ENUM_PARAMS(typename T1),
    BOOST_VARIANT_ENUM_PARAMS(typename T2)
>
struct comparable_distance
    <
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)>
    >
{
    template <typename Strategy>
    struct visitor: static_visitor
        <
            typename comparable_distance_result
                <
                    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
                    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)>,
                    Strategy
                >::type
        >
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Geometry1, typename Geometry2>
        typename comparable_distance_result
            <
                Geometry1, Geometry2, Strategy
            >::type
        operator()(Geometry1 const& geometry1, Geometry2 const& geometry2) const
        {
            return comparable_distance
                <
                    Geometry1,
                    Geometry2
                >::template apply
                    <
                        Strategy
                    >(geometry1, geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline typename comparable_distance_result
        <
            boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
            boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)>,
            Strategy
        >::type
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(strategy), geometry1, geometry2);
    }
};

} // namespace resolve_variant



/*!
\brief \brief_calc2{comparable distance measurement} \brief_strategy
\ingroup distance
\details The free function comparable_distance does not necessarily calculate the distance,
    but it calculates a distance measure such that two distances are comparable to each other.
    For example: for the Cartesian coordinate system, Pythagoras is used but the square root
    is not taken, which makes it faster and the results of two point pairs can still be
    compared to each other.
\tparam Geometry1 first geometry type
\tparam Geometry2 second geometry type
\tparam Strategy \tparam_strategy{Distance}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param strategy \param_strategy{distance}
\return \return_calc{comparable distance}

\qbk{distinguish,with strategy}
 */
template <typename Geometry1, typename Geometry2, typename Strategy>
inline typename comparable_distance_result<Geometry1, Geometry2, Strategy>::type
comparable_distance(Geometry1 const& geometry1, Geometry2 const& geometry2,
                    Strategy const& strategy)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    return resolve_variant::comparable_distance
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, strategy);
}



/*!
\brief \brief_calc2{comparable distance measurement}
\ingroup distance
\details The free function comparable_distance does not necessarily calculate the distance,
    but it calculates a distance measure such that two distances are comparable to each other.
    For example: for the Cartesian coordinate system, Pythagoras is used but the square root
    is not taken, which makes it faster and the results of two point pairs can still be
    compared to each other.
\tparam Geometry1 first geometry type
\tparam Geometry2 second geometry type
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return \return_calc{comparable distance}

\qbk{[include reference/algorithms/comparable_distance.qbk]}
 */
template <typename Geometry1, typename Geometry2>
inline typename default_comparable_distance_result<Geometry1, Geometry2>::type
comparable_distance(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    return geometry::comparable_distance(geometry1, geometry2, default_strategy());
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_COMPARABLE_DISTANCE_INTERFACE_HPP

/* interface.hpp
l4zg6rai21GbgqqJZTFyUz1n5D5D5F/Hd0hY8DBBWpXI3dgH1waUW6s4yCgWzO33k1maRTIR78j1GNmc/0JSnUm2IzdX0anHI9Vlk+yVUykel19pqAfW/IRgM7qLRShPiIsh6+vs+ZLHYTaJFKY+7SDURO6QNSZAoOkDicUidOGN+ijOyxokZI2SOeIYSSZeJ+weo+Qa1BMC1BCbKKhSPwebAwK8MxJ6abW4RJVq8aLD2+zGRYwd0TD+3kagDuU3d/1RELhZ0cml/5Ls+sNJI71YLdl3uL4tYk+jDm0QiJV4vPhXMSCLFxoDY/+P3mQgOFv50mpt2sCCs4asOW37D9sUBo9liZsFG5P224IBuww3lkEI56T7z8BVKkfhu3k3xVLBCHDiUWKxb7gI5E6tG0avgHhBEqqUSGRu8VbEND3owcoG2rqTiQwtnHmwysexUcFz0TnIOP7waKh6cWFs/YaEnUYtkl78cXJ3XZV4Qk9CNxr+B82xZWDyBMnoGBFFUs1ssZlgsPbHfLuaayVp3Z+7UWW/g45DA69h6BwGSPxEsj3mvhxEx5Q/5BrdhcLLFRbuoGryT9GEmmG4IwOKE4f4+CiLlacW0c3RLup/SvJT5egGCk80s4WyUejFrW65lWE1dstBT1M15q99IqNLEZSIGgmjgLV/krDSX7SYjAJhgE0d6lDVdfg2zlmzDLm7ZPf4njoRotKXZkPVL4tz1RqkHDsh4IfXzMYTESYLl+7uRbY2R4/LCbyGTdN5ttUrV/NSU8Us2/9Illz2fmCrYPhTnYOKwj7hTss0PPlgPMApwGviuptRDe1bFEG8zh5js3T1kmzfFVG6eVt+i+3S7YffuusZTQPKvd+GqYuvJPRKR6MT4EP7CX8t/Gl2ZdlQPFU0LnObUEnOBG5Yz4qsLeG1P38p8ZukLPSqdAudVQfkPUlWvYS6ueVbwt6R4t5DlwVPNi/07WkPShd8r1K6esAmGNMgNrImLNH9knSvew89kq/X2/ohN+ypehGLVtNwXanvFLcg4kvY0Z4brzYgUOjhE6REuuPd7z1r/urfadw3vtdcwx4UpvIVjsNfPhh1BjmMbwh5wW4JooVipWK8GZuGRSzy5FUZjaZhrAyZ966ufjfXeEDs8dQzJ364lYIpTX48/rb/cSTXjlirC9d4AjTr7ruwDzN7TXD6W2h96RxnL89nxvzVJ2d1o3Y5RIN+urrxQonLXsovoWpyOHsY+zDohG7IctNkLaSESQJl1u9Pxcfm6muEbMgIKC4RjfkXxRO05+d1EOKjY9d8F/IgtOpJhG7+7oS5lEdqJcqDv3TVx/B2noY197G0fyp8QbsTq5XvHJWB5S3bapgSfFRM0wEKUCBCzVQt7fUthrGEdDcllEVEqXC9Z982LdGx/9kVEFKsa5OXy7eGzWjc6qaV6q6KJu/ykFcd0rleT99ZH339lb87SrgJDRDtYmvP+0AFi15epGdj4oRyIqySZz39KPTr82hD3v6MxOZ0v4S4uWB8cmQEZxwn9RD9qAHxpwkAhOMbd4eNQBj4GKDukV+tG28fdOZi6uNfayjY5RdMsHlB7xhQ3SGQBWz60r8VRSMLCyXr+nGadjOi6o8aERxePuLFy51AZy6RraFRS1tzBUrajHslwNeAIXJM+ofMT3UdafolkZiYaFuJRW6NvLVwtZH0W1sXGn8v3hiErQh+emrlRGQjlXmyuzhYvohczlDx43ZuqmtlaNSDytuw87eCkJJzda59E1cLKZ5tMU6TbVgPH9NisVT4SDHfA+VH2+7poT8UU/Yk/2DRI5a0+Biv2T847ize+x4csKx6/XGmA1sj0HrJYXVlw5yNgPi73q+jiam7NBfEGa4jNHEaGGEXiK9UmCvV8KOYuOYJX0v/3EI6XkvIJ2MpAYc71sTOsfEPJNkYAAAs/9MmKwWZooh+MWosh7+eSw0jHZS/Y0RJaNHSIuOX4XtDu0zey0tMPWzhWMR/eS6jmaF5bao7YLgjsZCSic2SBdMUju/8e7NNAKG2lOZH3bGhVkTbSSQlFHU2n6xHq/nqU9dnI80NshwZC1KgLsmB7bWikHOxRJcCJoUfRYmLYSVWStwhc3jrNGRbwsBmtKPTG4sMyUwKoEEPpy9ZhVivOmF+3tAI8wtVG4QqnrpWivVKhF4VOuTM3vspiOD50fBpMZQDezTaECrY1Sk2nmo5PgD4miSw63N3w/LIYlRkS/joI7L7s1icwYRMaNJNL1HUVJHaVNFZtEvVmGwQhWYKnNeIRrjMt2+lqk4VhSq9FF2qYw+6yA1vw9xqIgtsFaN1Roro3HMYjXcpUZQ0wL1MfXQQ5llcFZuCUfWigGGTJ8XddUrzkuJUNapOSpZiXODZpmld8ZfvWqbiL5inDap6o/z5/JBWDyXsxsVv0cTXMR3Nsc7n1fTCXFbZv8UAx58zR9ljsQKy+ACb79s1LM/0ZFewW9IuZHgP/4dMLTpmPuSzM4PfcNPVNbwtqJ3laAZ10y5/EEvQmOg58KnU4Ii4DWJKANSuCeAIj5VG6NCSo/S5+jhfI1w1vdrulPIqg0REI+qzdt9LxP4UlKyRR3FsVbnz5aZxsmjAlXfsN/C2ZI7XPPYvpI1mgklUTLqHhSH6goIfwbdskHvJ1KjtFvIZrIvT0lpuBiJPwaqoMSeAm6NxH+5pf84T7/q3pE7nznopKyEjQr2/7x0snRp9VGFvMSF5f75dyntf2YLLBLjXgPCrLVmx5t5EeqqwxGB7VC7vi0pikXLfP73MjMduNYbvXKmrJrPtD8LGYoVRSV/ZLktMdbUh51MkkivXwd1BIvRpV/cMGStwX7n2iqrqz0NsKgy4Nf6A/E35qJSTAuR4wMOj7Hx2dXGcws4j3iEEXbkrIaSqsPIfJ15GbEN27Z02t0kilLZ6UbcEF/5QYkOjvn/dh8h2tpxWNDiohj0aimqZbjSCmrIAfAvgtJnogmjqvQgxHH7/x9GV05oX6zczwXbdAFXpxh5BTlHAODjTN84Tbkk4SOkaCriC2qqJqQhF5O/dwNzAbN00aIlpGXrJ1nbJ1rI0l//jdoiJFRwXi6Xm6DxCnjGymijPdNxB7TnxXHFgG44ucovvHJv0bZg5zpggPkV405btP3eIU7+TKZ9fDRqliKCk+nj/rvedrSZxjElta0bPu8lmc+gt9RtI+GVI8/SZOIjYfpZG16TSXFFySI18T1tRaKCbsk7kW3IbKdp43InK2UOO0yrZs6td1SqabJaL9Hjm/Easgw2pAXA4jaSFD3d0yxlU3Mblyh8ZQ7EeEY/YCxMmEHbjUKkiMgHvogbNpFcMQBr9ZWZUM555Plf6Qu2AXm9VlyoiSPvM4HL/6AOGuhTkmtqXdhBxDBlqgIDUotS2zkMhpTkBYDaE9YY35laYSF6CstRYghMNhadMihlVpRtMwclCtsBVJhv8sQFUgB9oEYBdqQzQXFbCpr/OKmmk6/any65WLYNeAeZ66lJBQUGgVcUMEJ98bGbKJhI3IVizPL3ub2dntPLPXTkOv+n2GJHW3V4gSwIbohZiyrWm6lej6MfZCCM1rU9Mx872buoQPXLZGpLnIIcfQyIX0ySyIO0couduF8YnYvlDJuNlqD/HYsLrBVd83sFxVaU9v9Lv4wAqnHQaNc4DPAJsTaUy2ce2kQDOWsrNMoc7xk6hWe0dlJA60+z9ICx/7MXIA5pgp1AZJ0YrL7biyc1OICDOI7cLo4iVkRIpoWpakpA6usA0iQ6+KdbUNyrfucBNeUWfUDHfJ/CxdnW1FdVj+XQRbc6+4LVLV5UZUvjywnQyID753py9Xbg94REyxelf6bs9kXKPgyn2iIuPYm7omJj6XrNUVYOfeXyHjWBwdIB4NzvvEC7iE+Fm5Cci94qrBZQlDZac3qTA4wMYXHWuFZN8hgSNn9EYtRBKuPONfMSRmBdOzs8kIx3gza06T6QZ/Dw5E3fIgRZZ8FUR2p24Eo+4/8aG9yXw7j2JjpwwjuJFAj28lVTxxiZWilEICfNJ67PIG8k7DjXsFhbFmag6Ja6Q91smRKwLb5LQYdJu+3fbg5Mea0W9d2e8JbJqFLQp8VP2O2V0Pxx6hHWZPxcMPXhBVx/OMld/fGqKGAWP3Dku8luWlb+SakTP6ZEc2mxWDHA0yfl+rBGJiq2tsgyXwAXh6w9p/YafrGnwPP3PAh0KwNNlxxZr3U5IdB4vjEq38o4H3SbG2FNh2CIApquGYuBA7qoHozUI8Dy/oiHDr6xOYbcM2vJMSDJtiSobsx3WEwtpvBTPpi9TRmqmBv9UuNBlKakJV46uMbiImjU41opX1oprylYtTCvaePW/9pBKThrlq+OP827q3no/K+llRJKovT4lb6daLW4+PX41e9ks9n+MHkks9g9ZChdeTjrRElJdfnd1T5haH8dELIvlWJON9n28teX5IWZpRJd9F7GM2vNK6ub9bXnbwGyqwybkfOckOyTwA3LI7H1i0YO/o6+6bPN8XR3t80XXd1KT28sC+EG7t6P8AZs/Jdc7SJxw+Irvzo20yql9qlHJtmf7Wbm3w/2p3d9l/fwg+OELPMWvfdugU7rpxZXrTLutOzeUB9wHeENT9/Vsi6qzO9gdjod2neT7syTv87T4+QHz8x2tkMJ+VyeQuVyjrY39c31Yp/namehH/Mmd53dyf1NDp5+M2vA1ha14gtYv8re3vJF+rjy814XJrzU3qjusjvvNjVSYzQ6De+ho++cFIpK9f8jOWG1iBVGJ+Jh4Y2nY1uf0XsTEx/AOu9m1kxHDGfkoi/L+GKyTMBQSeR++Mo+vfyv/RM2x0Oj+mKiXk8oO6HM4FWfy+i5oJXn7ILDBI/JVUk2UuvGu7CDXPMlBcuulW2nde7Mdfe+FHS2xk7x3TH+0Y+BJV4DxXoMYVqNcv0ivz9euSkoQCWTJO0ZhZAsxVknNrxDSPXukKkGcS7blFb4SZoZQn6FF+crEl1M6BMOLUCiIzXpescxRe9QKLkXHug8nIq0Otj35kF3TV1XQThvTju5DtzYxe5WJI2Ln06TBG9mvzuR610Kht4OD9yjOkzKuUfRuwvC5/xPlzl12f2FodLUJm6xLFW5I7PnoeZHJFP773N/3xvMsMKvuC+NhW3RGX2JxIpWlKlZmHztjZGmO8SNsmsCbJhRFy1AksnUTxi7uBHszblAuVeR4fki0OpLs7mDUJ18nwOs1Rd6morMd9E87tqa7DnLNgDi0S3Q7Ak4sK0MobKE3xO7LbhRUhH/M0dqL3bhXmc8Pt8dN441e4UdqgB3At5T3CYE/X35SGgM4/3fjFWFWK5z6tsV64NazBvc3NkM7M4iExr/dEbd5H9GWk4Xw0TmHKwH5wyaJE4vB4odI5PyR0K84L5IhuUxGiZ96xnFCAOHmSGSrSFR9rjbV7OA/Iinf3ggOm8EffGWNRcxjWwg0G4KW9VRwQojqsO8kECyjBhRyccP6FWzZ3gNkp4RSzMv6FTAke8rFCe+LLyiTa5BYbKzpju9DXgLS96xA9YZ9wrCltp0diTbErIRGqSd29z972yvGusJbb9uG3BIdHYBapgN/U+cIOHVZOTgbALkxUGdLQ2VFkasO/+JDAmcFS2esIcRXrGDa9BMEVaYAP9oAu+6Uolw+kVRJQHQGNI9FE65slNOz6YdZY7HpCPlzM/IBuPhJAyZW/j6ZtMUamE02691/W5z07vB0/4xXapbd9RnPbdep0qyiTO319I/tFCd+ILz8ACxiVbI6XeXf7hlljI6IQitH1LukOwoarBao+/HA6Jx1EUYqT2xiEqnkTnFObLl7E9JNsm6q+zT0JtIc1vfIV1YZUBvUXf97RZEjn2F7uJvZRnyNYeTY1H7kKA9MdZA/26X8usDkqUekPGfneYhZSMNQXj6klV7uaMNej6/Unt5leLtG0P9extE/Hl99eXfqRuPEjROFvfNCEMQozTGGSLcV45T7ZtPBNkfi3onxcS3/RcP/Qz9athR3mirnt+zjhfLKOjfyfEIrehfOcO3CQctZ4LCQHSIF2WZGCrSFCrq0YYQpdrw+FPbkrYajKGCBl5WT5MFC9dhui6ItujUbelrSdli/r3YijSf9jgNKlQt3g0IoFJ6Zbg8rzbTb7tzjxhpv9yc5OT7bML1sjtQUole3QeCW+RGa6JtJdMRIZzQBg0AU+8o/pfoL1HTPlZC6+lU92MR+xv/dZ73YBabRhxEIv8CncRXAFhiFoAYA4CEUxXom8PsVhJrpfLKc+A2NJN7mtXihBv/EtS4sSUXv6oojQ0TvgsWzOciZA4djV1xWMpyEi30OEWRgC4ioXELdgRm8dsM/Kz5hTcE6ebgIL6aNOluRFrJvuu8mcsNDsErhKxmIlqA6ok7nIrj1cTFhcWd4AmlGtYe4tnYKz1vWunrVWxaL8mD7xwELpD0ho8axhikRKFqAzzGiFLnOcfSBspkJFMc4ts9mpZl3a5Lu930W7hubA0Pdu/bOzAdJ9uT8zYN30OrJicdBJFcy9Z9JjsmwtrFTicg4Zc4nSEt74tVsncZg8Jw8/TP1RoEblwLNx/W0gbnGzc2fiMRmaTPVOMkLAWKS4dpfhJ/D5LrAlJjTT3/BsVoxEtDoY3JDvsQjVmhTbHFJccH8XPMKvHyKZxw1uF+7hd28m9sh67Kk+BbR0b+xGvrY0S+A7wJs2vRndQM08vlHO7J12kaxb+9KZ2BdDDVvlmKGQTMEdFPRDdVEUwxVDKH87fGbrSl/ohEaJnKo0jBfkh6wmZVoTrQUQ4hGIv/gZKArEjV4+x/FELtPlK39xqrIVMkQrAzuJNpRSPL1wYohaAI6X3EfS6hU/QdgQGeykf1uY1JAFr8BUCz+i530X6OFhUuclZanKBIThdfZf6XmKixYYdHgf1/r2SFpnpr7uPfT5h8bj1V5UfuM59YmV1pd+s8S7d/yQlrn8QujiMhC8tJ5M70E1uDxL195B26z9THkja9lGPwjAHMnb6shtllPr0AYKIiA7cOhMqtp/+hbK46mXSwkwv1J+3IUldUgX11NridsAtYxMw+6F6a99GEfXceWKcc5o6aozRkSn8PTcPWKkj4NRrx0F0qYroROderSjRkTQZZ3n1cXw55KC4KzsDspWFdSN1jI/6t9279DFcsqzDxtuVHZIFDojd77mGIH1hh/HHNja1gPBN/lGgZfeQR2wV9cAGloBTZx7sNoxrKhv/QxWd5kl2o6gGhBkNlN/Ej0D47LsAC9v6TCKJyTYT+g0VJOYysNBoP67xvWbMADrRYgVvElp/3QfKn4/jwtUigfwOT7sFRPpM2EzE/AyJbNfHqJjW5IEJF8o1t4VwMJ4TeN3TsP9TeyTUVVP9sz5bEjVr+mmitKpiu7c8rQhrYnBYBNwmH2cLONGcZIYdeCicaSjJuEbpjH6h4EB3RTzdNnBnmeg3hXl/I8Kw2iS+keyAyyOLsUuq2KE5a5McFRbjiDN5SOZaLIMG5VQLFgIhwTjlFImym33IakdrVShUOOQEa1KBnsiXyXqR+UNvaQvMiQYxG94TgY3Q2vEZNi/KL5izAtYb+wp/jvTDWTxOizhakesOUhRxgCMnJvAmDkgATT7O6To6ZJYzvRAIP6
*/