// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013, 2014, 2015, 2017.
// Modifications copyright (c) 2013-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TOUCHES_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TOUCHES_INTERFACE_HPP


#include <deque>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/reverse_dispatch.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/relate.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch {

// TODO: Since CastedTags are used is Reverse needed?

template
<
    typename Geometry1,
    typename Geometry2,
    typename Tag1 = typename tag<Geometry1>::type,
    typename Tag2 = typename tag<Geometry2>::type,
    typename CastedTag1 = typename tag_cast<Tag1, pointlike_tag, linear_tag, areal_tag>::type,
    typename CastedTag2 = typename tag_cast<Tag2, pointlike_tag, linear_tag, areal_tag>::type,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct touches
    : not_implemented<Tag1, Tag2>
{};

// If reversal is needed, perform it
template
<
    typename Geometry1, typename Geometry2,
    typename Tag1, typename Tag2,
    typename CastedTag1, typename CastedTag2
>
struct touches<Geometry1, Geometry2, Tag1, Tag2, CastedTag1, CastedTag2, true>
    : touches<Geometry2, Geometry1, Tag2, Tag1, CastedTag2, CastedTag1, false>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& g1, Geometry2 const& g2, Strategy const& strategy)
    {
        return touches<Geometry2, Geometry1>::apply(g2, g1, strategy);
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy
{

struct touches
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return dispatch::touches
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy);
    }

    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             default_strategy)
    {
        typedef typename strategy::relate::services::default_strategy
            <
                Geometry1,
                Geometry2
            >::type strategy_type;

        return dispatch::touches
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry1, typename Geometry2>
struct touches
{
    template <typename Strategy>
    static bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2 const>();

        return resolve_strategy::touches::apply(geometry1, geometry2, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct touches<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<bool>
    {
        Geometry2 const& m_geometry2;
        Strategy const& m_strategy;

        visitor(Geometry2 const& geometry2, Strategy const& strategy)
            : m_geometry2(geometry2)
            , m_strategy(strategy)
        {}

        template <typename Geometry1>
        bool operator()(Geometry1 const& geometry1) const
        {
            return touches<Geometry1, Geometry2>::apply(geometry1, m_geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry2, strategy), geometry1);
    }
};

template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct touches<Geometry1, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<bool>
    {
        Geometry1 const& m_geometry1;
        Strategy const& m_strategy;

        visitor(Geometry1 const& geometry1, Strategy const& strategy)
            : m_geometry1(geometry1)
            , m_strategy(strategy)
        {}

        template <typename Geometry2>
        bool operator()(Geometry2 const& geometry2) const
        {
            return touches<Geometry1, Geometry2>::apply(m_geometry1, geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
                             Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry1, strategy), geometry2);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T1),
          BOOST_VARIANT_ENUM_PARAMS(typename T2)>
struct touches<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
               boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)> >
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<bool>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Geometry1, typename Geometry2>
        bool operator()(Geometry1 const& geometry1,
                        Geometry2 const& geometry2) const
        {
            return touches<Geometry1, Geometry2>::apply(geometry1, geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
                             boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
                             Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(strategy), geometry1, geometry2);
    }
};

template <typename Geometry>
struct self_touches;

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct self_touches<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor: boost::static_visitor<bool>
    {
        template <typename Geometry>
        bool operator()(Geometry const& geometry) const
        {
            return self_touches<Geometry>::apply(geometry);
        }
    };

    static inline bool
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry)
    {
        return boost::apply_visitor(visitor(), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_check{has at least one touching point (self-tangency)}
\note This function can be called for one geometry (self-tangency) and
    also for two geometries (touch)
\ingroup touches
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_check{is self-touching}

\qbk{distinguish,one geometry}
\qbk{[def __one_parameter__]}
\qbk{[include reference/algorithms/touches.qbk]}
\qbk{
[heading Examples]
[touches_one_geometry]
[touches_one_geometry_output]
}
*/
template <typename Geometry>
inline bool touches(Geometry const& geometry)
{
    return resolve_variant::self_touches<Geometry>::apply(geometry);
}


/*!
\brief \brief_check2{have at least one touching point (tangent - non overlapping)}
\ingroup touches
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return \return_check2{touch each other}

\qbk{distinguish,two geometries}
\qbk{[include reference/algorithms/touches.qbk]}
\qbk{
[heading Examples]
[touches_two_geometries]
[touches_two_geometries_output]
}
 */
template <typename Geometry1, typename Geometry2>
inline bool touches(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    return resolve_variant::touches
        <
            Geometry1, Geometry2
        >::apply(geometry1, geometry2, default_strategy());
}

/*!
\brief \brief_check2{have at least one touching point (tangent - non overlapping)}
\ingroup touches
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy \tparam_strategy{Touches}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param strategy \param_strategy{touches}
\return \return_check2{touch each other}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/touches.qbk]}
 */
template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool touches(Geometry1 const& geometry1,
                    Geometry2 const& geometry2,
                    Strategy const& strategy)
{
    return resolve_variant::touches
        <
            Geometry1, Geometry2
        >::apply(geometry1, geometry2, strategy);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_TOUCHES_INTERFACE_HPP

/* interface.hpp
rlW4cFx1u9267k7DP/zwjl+6pmW43R78NE+XX2bKMz/gN66n/+lfV38Tye39rt/LHqQrtC3Y172mS27s18mN/Sqzx+D1JZtDB9WtN3dCGsNcGS8koi2n4xNscTElc8PPJEo2G4EP6nbJVLTYo3b8FWrHX8tlUzy9IlOPcVJvFNv8GY9O5paDh0I8hM+CucPH7FzwhQQk6Gt9sWqfxf0dJ8XUfcNTssVnBFa1H6GGzRqzuVPGrSVNPmPMqjKs1lcEsOgTWxgDWMVdcYVnQ5lY1gPPtPdXkAhnYwqclcaYZ4C7HexgCtZxHwmPMQWgw+ax7HUXJBLdOq3IVzrwLe2vP/2v+UkHQZUeMUNge9uvOAep86V7+rpan6c+nHqwVec1HLpyuOsn/ed5zavgKmuSh0cvRdT0JAk1gtTzDEdgabR+YYoKfe1KwrF8V4Lvf/0QV+iccKJ0JmR6zpXcvJOuFoI3l+NmvVEmLLXa4GK38Esop1CD09IBQOVVGqmvRlB7uQI1VoJ6/SoBKpeg7voYUDMIqn5iKqhlCBIOrGAihGSuTofMKUI6WrlinoUMhGIlD+1XprBBVvls31RUqrCdl4h30SsI/Co9mnSzHqgV4McP2bYlrLd+i0dUc3BCnbl3Dcec6kVSnXUyyg/R8mrufbuxVZojhkhKI4Z8r/ByetdwG3V/4WFbvCBd9PphlHsUtECr4BeALV0bJUqDwCqX/AwB0RFF7adJCchMJCheLsxr9bIT1pC9jLRbVFoHwCT2jSYVvA8RocyxZodivRzUkO9YIHyVE3REJ2+mp5JaLRNMjNZnJ8nXePN0eusp3Aqjug6FqegLHrU+00/Ibyq+Fhs71ccvFU9r620aaCjPFFM56k6yVaQHJExfnkN+I5324zhiCvn0wmURJfgxAdZ46hIzv2UMgOc6k6HEjIhr6c/4EF/ALrzBkUkGsnOpFmaywo66xE1P2yyemuLckIej4ri/JxKKT2E98AB7+3yOFp/pKKCiZ0ZZd9+7N2E7eX1VU6Z1aNXWIdr6ot+Mt3Sm+f/A75QQxXG3D/XCVLY1hqCU87i3Faj2i1LJieozySQwDwEjKs3mHmBQC65BKqOLpEWQE2WJQdocRsh7Uz1E3j8R5O7LHXL39tIuPpN/ds/ehKhBe6bD6ULbi9lN7H2C6KGv20dVV3k+OdJiv3aIvnKYUZey2mMMUEpiaTdWGQOEgQa/VCoG3odakYKZxmHRZovWSoG0WHYmWoUMDO4DdNRDm1ThPbnSDGl4D1TsOL/loFJZ3PBLwSeigZXSIScbdTni4Ro4usqQT1hk9rrEExzC7UyOEsljqKDxytHYdzvxNbtnEaVJFlGcBvT5fp3o5zpyPL5TTGjciDq00MghmaHhrRkpHIckC4KTQObMqaCYFGpTaa3NYyqbF8QspMvyK+VQGvc9DKWwM5R+eWanoeSxvn03h1L8l6lTI36H4OFjbBlLDIf/wdLYM+/EXwryepH9fuxP0KmyQJgyUVEme+q2hkWbs8anQwcaPOYxmtDQwosuHpwsUj/jLJKVVhWW47yz4+0vncb+Vf5S5f3n/sLeD2Fnicthyl4Y9EsGe+h4WKQIFcjWoXtaQbQOeVf0VB1NWxDQ27q+/XwcYjetsJlst8rgIe3DENzkBN9lBx+Dvm+tsRRqZu26S6xvZ8eqK5mMA5q4BMZO/+9i7FztjJ1Jw8h1a3W4bv3ulFaBR93LIZSiVdB1J4TPd/XJ6xhtqnIHdeblS2IzYXxl6MkB9AD3/ambHsycCN/2loutfKjTymvE0n43x+9Fstlc0kOk6JWqBhL9zdbyEq8neMgK28zGBtnYZ7QfV272AOq5SBM=
*/