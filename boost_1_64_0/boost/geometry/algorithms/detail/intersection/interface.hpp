// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014, 2017, 2019.
// Modifications copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_INTERFACE_HPP


#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/overlay/intersection_insert.hpp>
#include <boost/geometry/algorithms/detail/tupled_output.hpp>
#include <boost/geometry/policies/robustness/get_rescale_policy.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

// By default, all is forwarded to the intersection_insert-dispatcher
template
<
    typename Geometry1, typename Geometry2,
    typename Tag1 = typename geometry::tag<Geometry1>::type,
    typename Tag2 = typename geometry::tag<Geometry2>::type,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct intersection
{
    template <typename RobustPolicy, typename GeometryOut, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            RobustPolicy const& robust_policy,
            GeometryOut& geometry_out,
            Strategy const& strategy)
    {
        typedef typename geometry::detail::output_geometry_value
            <
                GeometryOut
            >::type SingleOut;

        intersection_insert
            <
                Geometry1, Geometry2, SingleOut,
                overlay_intersection
            >::apply(geometry1, geometry2, robust_policy,
                     geometry::detail::output_geometry_back_inserter(geometry_out),
                     strategy);

        return true;
    }

};


// If reversal is needed, perform it
template
<
    typename Geometry1, typename Geometry2,
    typename Tag1, typename Tag2
>
struct intersection
<
    Geometry1, Geometry2,
    Tag1, Tag2,
    true
>
    : intersection<Geometry2, Geometry1, Tag2, Tag1, false>
{
    template <typename RobustPolicy, typename GeometryOut, typename Strategy>
    static inline bool apply(
        Geometry1 const& g1,
        Geometry2 const& g2,
        RobustPolicy const& robust_policy,
        GeometryOut& out,
        Strategy const& strategy)
    {
        return intersection
            <
                Geometry2, Geometry1,
                Tag2, Tag1,
                false
            >::apply(g2, g1, robust_policy, out, strategy);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy {

struct intersection
{
    template
    <
        typename Geometry1,
        typename Geometry2,
        typename GeometryOut,
        typename Strategy
    >
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             GeometryOut & geometry_out,
                             Strategy const& strategy)
    {
        typedef typename geometry::rescale_overlay_policy_type
            <
                Geometry1,
                Geometry2,
                typename Strategy::cs_tag
            >::type rescale_policy_type;
        
        rescale_policy_type robust_policy
            = geometry::get_rescale_policy<rescale_policy_type>(
                    geometry1, geometry2, strategy);

        return dispatch::intersection
            <
                Geometry1,
                Geometry2
            >::apply(geometry1, geometry2, robust_policy, geometry_out,
                     strategy);
    }

    template
    <
        typename Geometry1,
        typename Geometry2,
        typename GeometryOut
    >
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             GeometryOut & geometry_out,
                             default_strategy)
    {
        typedef typename geometry::rescale_overlay_policy_type
            <
                Geometry1,
                Geometry2,
                typename geometry::cs_tag<Geometry1>::type
            >::type rescale_policy_type;
        
        typename strategy::relate::services::default_strategy
            <
                Geometry1, Geometry2
            >::type strategy;

        rescale_policy_type robust_policy
            = geometry::get_rescale_policy<rescale_policy_type>(
                    geometry1, geometry2, strategy);

        return dispatch::intersection
            <
                Geometry1,
                Geometry2
            >::apply(geometry1, geometry2, robust_policy, geometry_out,
                     strategy);
    }
};

} // resolve_strategy


namespace resolve_variant
{
    
template <typename Geometry1, typename Geometry2>
struct intersection
{
    template <typename GeometryOut, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             GeometryOut& geometry_out,
                             Strategy const& strategy)
    {
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2 const>();
        
        return resolve_strategy::intersection::apply(geometry1,
                                                     geometry2,
                                                     geometry_out,
                                                     strategy);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct intersection<variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename GeometryOut, typename Strategy>
    struct visitor: static_visitor<bool>
    {
        Geometry2 const& m_geometry2;
        GeometryOut& m_geometry_out;
        Strategy const& m_strategy;
        
        visitor(Geometry2 const& geometry2,
                GeometryOut& geometry_out,
                Strategy const& strategy)
            : m_geometry2(geometry2)
            , m_geometry_out(geometry_out)
            , m_strategy(strategy)
        {}
        
        template <typename Geometry1>
        bool operator()(Geometry1 const& geometry1) const
        {
            return intersection
                <
                    Geometry1,
                    Geometry2
                >::apply(geometry1, m_geometry2, m_geometry_out, m_strategy);
        }
    };
    
    template <typename GeometryOut, typename Strategy>
    static inline bool
    apply(variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
          Geometry2 const& geometry2,
          GeometryOut& geometry_out,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<GeometryOut, Strategy>(geometry2,
                                                                   geometry_out,
                                                                   strategy),
                                    geometry1);
    }
};


template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct intersection<Geometry1, variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename GeometryOut, typename Strategy>
    struct visitor: static_visitor<bool>
    {
        Geometry1 const& m_geometry1;
        GeometryOut& m_geometry_out;
        Strategy const& m_strategy;
        
        visitor(Geometry1 const& geometry1,
                GeometryOut& geometry_out,
                Strategy const& strategy)
            : m_geometry1(geometry1)
            , m_geometry_out(geometry_out)
            , m_strategy(strategy)
        {}
        
        template <typename Geometry2>
        bool operator()(Geometry2 const& geometry2) const
        {
            return intersection
                <
                    Geometry1,
                    Geometry2
                >::apply(m_geometry1, geometry2, m_geometry_out, m_strategy);
        }
    };
    
    template <typename GeometryOut, typename Strategy>
    static inline bool
    apply(Geometry1 const& geometry1,
          variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
          GeometryOut& geometry_out,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<GeometryOut, Strategy>(geometry1,
                                                                   geometry_out,
                                                                   strategy),
                                    geometry2);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T1), BOOST_VARIANT_ENUM_PARAMS(typename T2)>
struct intersection<variant<BOOST_VARIANT_ENUM_PARAMS(T1)>, variant<BOOST_VARIANT_ENUM_PARAMS(T2)> >
{
    template <typename GeometryOut, typename Strategy>
    struct visitor: static_visitor<bool>
    {
        GeometryOut& m_geometry_out;
        Strategy const& m_strategy;
        
        visitor(GeometryOut& geometry_out, Strategy const& strategy)
            : m_geometry_out(geometry_out)
            , m_strategy(strategy)
        {}
        
        template <typename Geometry1, typename Geometry2>
        bool operator()(Geometry1 const& geometry1,
                        Geometry2 const& geometry2) const
        {
            return intersection
                <
                    Geometry1,
                    Geometry2
                >::apply(geometry1, geometry2, m_geometry_out, m_strategy);
        }
    };
    
    template <typename GeometryOut, typename Strategy>
    static inline bool
    apply(variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
          variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
          GeometryOut& geometry_out,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<GeometryOut, Strategy>(geometry_out,
                                                                   strategy),
                                    geometry1, geometry2);
    }
};
    
} // namespace resolve_variant
    

/*!
\brief \brief_calc2{intersection}
\ingroup intersection
\details \details_calc2{intersection, spatial set theoretic intersection}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam GeometryOut Collection of geometries (e.g. std::vector, std::deque, boost::geometry::multi*) of which
    the value_type fulfills a \p_l_or_c concept, or it is the output geometry (e.g. for a box)
\tparam Strategy \tparam_strategy{Intersection}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param geometry_out The output geometry, either a multi_point, multi_polygon,
    multi_linestring, or a box (for intersection of two boxes)
\param strategy \param_strategy{intersection}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/intersection.qbk]}
*/
template
<
    typename Geometry1,
    typename Geometry2,
    typename GeometryOut,
    typename Strategy
>
inline bool intersection(Geometry1 const& geometry1,
                         Geometry2 const& geometry2,
                         GeometryOut& geometry_out,
                         Strategy const& strategy)
{
    return resolve_variant::intersection
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, geometry_out, strategy);
}


/*!
\brief \brief_calc2{intersection}
\ingroup intersection
\details \details_calc2{intersection, spatial set theoretic intersection}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam GeometryOut Collection of geometries (e.g. std::vector, std::deque, boost::geometry::multi*) of which
    the value_type fulfills a \p_l_or_c concept, or it is the output geometry (e.g. for a box)
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param geometry_out The output geometry, either a multi_point, multi_polygon,
    multi_linestring, or a box (for intersection of two boxes)

\qbk{[include reference/algorithms/intersection.qbk]}
*/
template
<
    typename Geometry1,
    typename Geometry2,
    typename GeometryOut
>
inline bool intersection(Geometry1 const& geometry1,
                         Geometry2 const& geometry2,
                         GeometryOut& geometry_out)
{
    return resolve_variant::intersection
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, geometry_out, default_strategy());
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_INTERFACE_HPP

/* interface.hpp
i5XJSpEGdhfH78CjsMlZlu2VBf5u/oPHRnYYILmPG7IrMW/rBF5193GTDDhkeddEFpJRWHu3RZ3D3Y00+kfO2zm2w8y8CjY4j58HnOxxM3A6gi/Hpy2OcFSX8oKcnxzIcaDj5DRcHAdHOKqTjcbFcW/mAIz1vA/jDU6Dbf5m5Nr2tGZWHLzhS6YrOBjrHi48lOBvLvcWGGOVOX7HK8D0N8COOBGc+ZmZ/cbUQn4vJ6e5iSJHlkX9vC/yCkMlJ1xN5ZJt+H4nU5s5t9Dft23blr7+rSYwrYX7s7gKZ36Gy+OBER7vAzpS4aB9e/yoGEe5cBpHR7hr12yXBxNnb61SQuB860zGe4xfhXHT38V7NZT2Tj703fTNRkUgsLMcNguQxlf28UvMukXdOgD7eImT9uudBjmWPAoJVsJYIe5UeaTEyO2Y9BHLYI/bjqG7XmZz7iNw9phV7XG3ao+3sc40NIq2/OYURq0g/F5LzGFIrkmJuF8mcZrTeOx9EiNb+3gvlxh/SPLZK4mTUj7sqyUm5hjGpsth0yOPJZtemLOPJZviV/yuTJe2F+g4pGGWA+W6zPFWxqfvGFspsHR9XM0YfVNiV7nDTvYYfyM67BSH8Uk6PrfDmNhJzv1Qt8PJ/eflvU4+FPq11ks5ukTZHjY6zJ7UcvKHWTmfW2Bb2CJfcNUp79hv7pjYVUF3r76DdHSXNh6eivSGBgb7TCj263HeHuFwwnL7wEgXupYh9oEtU3V5lE2LQrkU861x2/RwalvLe6eaXp9LD6G0vP/8cIvXZs1cJ/dZNqtLTc97l6pLv9Oldo/z3tDPzp3Qpa1JD9r05CcS+fCYc4bkQCPmcFvffoyZm2NO36A+eyvCnIH+ZROwfXZetx2yOmSHWdnqPHlCU4ptd0qXut6N+N2jEWhjC24f0E6rywUHULq8z4L5ron5tVGOiyY1pA/wKCw/XlqbDd74NfMgChy+LCbfPF/cjEczKT3O1KthreMknotzqR5nY3+1yHO7GPNzOz282Ugg3pmNMApO46oWHifsJitTwDkOBbexgKPFYV/HLo7PVsL31nROZGOFVzJbiSroTyIbqzynX9M4bXVvGafl5YoTp7rNvLhlnJaXy471kjmj3sHxZXIoOmHz80+WXAzarqUgcTOertbSVV53le+TLW7FtVroearW3EUEDVk3dI6PqzMjLlddM+OR1ZXyoMajZIPGGBdvDn66LJ+9VIbh55Xrc8zZdbLKqUkfytLDMzh00V1GP3ARFlPifoAx0tbfUQQ9rkL/fDy4CznnontKk7t241c8NpyjzkXHzTwLu8rknKxoZYXBhdnxKs8nyyzHclIRcwFtno/ElXn++ySuzuUlZkqP8XdLnP2QPNcPcBgz57wAbPOTcY7/iV0tz/HDFlwvqcwugI1+diztn78o5zeZ0QM7Snqwn0Ypt5KmB9vbBpQ272Sbh5zU9+rlGk625/PLEYftz2vTIYfKgNvADGzioZ30HLiKoW9xdrwQ8gd1ItfgPMnOk+as7IFGlvPMxLRJDb+TJ9Qb2ty3ptp3Qcxztp2JzqVUpihEH3BRFofepgYvO675xviUi3E1x6fyZKydapxEoPmBFhdHkHeO7uyG30rb2KfO0Z8SpkknlQT+tBRew/RL6vwMBS+M16eCtfuAQw+Ey77g2QEevvV+cYjRs6n7qklblmk8L+C5t+A5jUtCnHzdehrwoyXP16Nssuzk3odnPV+YKrssPV+ULuO6KS58jwtbYKilvlr2l5CTcefnKtNmQzfal7Bvmbp9L3sp+Rfr1Zz7inCGyvwUSlMN5Rvl+V3aWZVXIo3tA+vJpSDkr7by9NmG11r5mNnXMFk=
*/