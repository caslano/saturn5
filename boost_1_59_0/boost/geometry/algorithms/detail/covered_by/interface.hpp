// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2013-2021.
// Modifications copyright (c) 2013-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_COVERED_BY_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_COVERED_BY_INTERFACE_HPP


#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/within/interface.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/relate/services.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry1,
    typename Geometry2,
    typename Tag1 = typename tag<Geometry1>::type,
    typename Tag2 = typename tag<Geometry2>::type
>
struct covered_by
    : not_implemented<Tag1, Tag2>
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy {

template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct covered_by
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        concepts::within::check<Geometry1, Geometry2, Strategy>();
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2 const>();
        assert_dimension_equal<Geometry1, Geometry2>();

        return dispatch::covered_by
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy);
    }
};

template <typename Strategy>
struct covered_by<Strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        using strategies::relate::services::strategy_converter;

        return covered_by
            <
                decltype(strategy_converter<Strategy>::get(strategy))
            >::apply(geometry1, geometry2,
                        strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct covered_by<default_strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             default_strategy)
    {
        typedef typename strategies::relate::services::default_strategy
            <
                Geometry1,
                Geometry2
            >::type strategy_type;

        return covered_by
            <
                strategy_type
            >::apply(geometry1, geometry2, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry1, typename Geometry2>
struct covered_by
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return resolve_strategy::covered_by<Strategy>
                               ::apply(geometry1, geometry2, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct covered_by<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<bool>
    {
        Geometry2 const& m_geometry2;
        Strategy const& m_strategy;

        visitor(Geometry2 const& geometry2, Strategy const& strategy)
        : m_geometry2(geometry2), m_strategy(strategy) {}

        template <typename Geometry1>
        bool operator()(Geometry1 const& geometry1) const
        {
            return covered_by<Geometry1, Geometry2>
                   ::apply(geometry1, m_geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
          Geometry2 const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry2, strategy), geometry1);
    }
};

template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct covered_by<Geometry1, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<bool>
    {
        Geometry1 const& m_geometry1;
        Strategy const& m_strategy;

        visitor(Geometry1 const& geometry1, Strategy const& strategy)
        : m_geometry1(geometry1), m_strategy(strategy) {}

        template <typename Geometry2>
        bool operator()(Geometry2 const& geometry2) const
        {
            return covered_by<Geometry1, Geometry2>
                   ::apply(m_geometry1, geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool
    apply(Geometry1 const& geometry1,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry1, strategy), geometry2);
    }
};

template <
    BOOST_VARIANT_ENUM_PARAMS(typename T1),
    BOOST_VARIANT_ENUM_PARAMS(typename T2)
>
struct covered_by<
    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)>
>
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<bool>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy): m_strategy(strategy) {}

        template <typename Geometry1, typename Geometry2>
        bool operator()(Geometry1 const& geometry1,
                        Geometry2 const& geometry2) const
        {
            return covered_by<Geometry1, Geometry2>
                   ::apply(geometry1, geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(strategy), geometry1, geometry2);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_check12{is inside or on border}
\ingroup covered_by
\details \details_check12{covered_by, is inside or on border}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry which might be inside or on the border of the second geometry
\param geometry2 \param_geometry which might cover the first geometry
\return true if geometry1 is inside of or on the border of geometry2,
    else false
\note The default strategy is used for covered_by detection

\qbk{[include reference/algorithms/covered_by.qbk]}
\qbk{
[heading Examples]
[covered_by]
[covered_by_output]
}
 */
template<typename Geometry1, typename Geometry2>
inline bool covered_by(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    return resolve_variant::covered_by<Geometry1, Geometry2>
                          ::apply(geometry1, geometry2, default_strategy());
}

/*!
\brief \brief_check12{is inside or on border} \brief_strategy
\ingroup covered_by
\details \details_check12{covered_by, is inside or on border}, \brief_strategy. \details_strategy_reasons
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry which might be inside or on the border of the second geometry
\param geometry2 \param_geometry which might cover the first geometry
\param strategy strategy to be used
\return true if geometry1 is inside of or on the border of geometry2,
    else false

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/covered_by.qbk]}

*/
template<typename Geometry1, typename Geometry2, typename Strategy>
inline bool covered_by(Geometry1 const& geometry1, Geometry2 const& geometry2,
        Strategy const& strategy)
{
    return resolve_variant::covered_by<Geometry1, Geometry2>
                          ::apply(geometry1, geometry2, strategy);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_COVERED_BY_INTERFACE_HPP

/* interface.hpp
F+EoH8w4ohSblGRYsowj6CRrkVFZYAqYplEo2gUWZYEVivSt+gvIyKi1KwDWK4xKeYpSkKpU2JQF6UpB5vIImEhtPmkFMFF7AcGEuiYnUNzN7xgjmOf0s480A7aOToMrvdvFjpDo9fj5qXh4kTXHjvCD8MuT4D9gKFdhUM7T6oQZYxH5PQ1lv4UyOG2Q2gkpFNRCle3OPvI7bCkUtDQ02u7sJuz8coGq8t4LofNWiXdUs4Ji6AUXSKWEzUT74OyeUqV+KWIRf3bxilFpkseg1M/Sfi+A30o93rTNW3FRX3LhCtbPx+eyS8pLi+lnGT5fyqc07hgEGKwwH1bH3xLnYoV5Ra7A2ytQlPwToQySwA4A0VeEnOBAAL/mV4zQJWrWE+eJU9/GDgWeoaK4qYiLh2rD9fZu4bYRKsKm+dtUEfYYPQuHKqKid1JDFRWJalr48cvDq8HB8Z+PWA0VrUoVUvN9OCOiVeVtaoA5aeySGJPyNnV/jVNbGapYeZvq+BFk8iWDaVJMrI8z/D8+SpWyj7YnGLZA1bU+t7LtVWKGIYt2PSxqoEHEKCXv/K72BmRh+nqafco2kiZta6Yn3aXbdsFzobKNnMxsQwScP1QaJ52I75N+7zsxbXl7AzoTTCEv/6Rapmx7UQS7+Vc1uotwT204lxZiEmHns1XNN07uPuxH7S2Al//QQemahYy0HgApZwjGR2nB9xYaCsUL1X8MNOLA+IpT4zU9CZzVdh3OAL8hP8w1mgv3AP8GGm7jR9whHKZ5cHOMVkEP2aGeWGo3Ahwgz2uLYQy9SS4AB/79lt6ZRZDg/efTpCHqmqfzo4KhimhWSk1X7oZdJJK6IK5iuKMV51nFOUh6R2s1iz+0YfEOsNYMET3Y33IFr1rn2QznaU/S8/ecv8iWHXN018TDhR2MZ91IAbdNhwoffyS+yN9xJU82zIOiHgALhu9BDQJ2sYEPryjeY71JRY0wDTnQYdbxvP++UxI2kTEQMCQrzhaGXeoIGO5RnPtZG3wLt/6HNb3+mlM67x2eIp60mlz2dMO83xQwTIGb9Rh1Ue/sqISNKal7aBPUdGd38mu+QXKmC2X3gc2vEcL8sJF/cRpuK+d++AAlEs4+pCVwEzm7zUhrYEPzoaFXVwGC07UE44OYm5yHWEfrSSPQsnwMJsZ0MGdfidbWN57EJfw3F0Zq61Fqq1fn7Mv1crgDnS0Cz/Fy/88OmdXibu9marAAGswON3ijNjD4Uu/s82hjCuRb1exO9g2fO2JTZmgK6pK8E2mdegOmKRnOvoxW4b7L2aE6T0FxnHnT75D6CfEdBrvTpOjIJCUwVrjMFpnwEnsPEkZKuCiKyZJhBtLsw8CdvpLAk3io4c9GEiIoT5CPqffujpPYQhuMx1KJPiUxdBPgLJusUVYv0Woz1ih2oTWW05EedrHTgoyo3Abawo2o0/8uArGgAVlDSN+gR1WHKA78loRneFL9K+02OK51zIred0idHIFmYJ4hDDURvb9NnyYJ1VSKHAAMLPPTNWG+hXz2ZCEun0qhCeFrfj+ASuGTM0NFrhgypUSLm9bADsxuQd3aYfwIds+MQAG0I0KHbKdoznUHcMLKS/mzC+LIlvR/eEfp8FB08yO80yJxjs+hfnDuHnGQ0YWpUHJfa1PQh6Zsd8H/Mvi/WDvN+XYXdGp+BlSQMd+e72itmcIwDfnlmInxCkKOMINjIWc+5OSHcsqh9vkh57HzoapW/AbgQMX5K54i9P0In8MHGHsc49azboY1iJ334UW0oeDlD4U297XIkrNnd0af1jbY1Q+eg20JwxqyrXP6x0s9GHrPkI3cKGTcH19KRgmWBMGXxGDjGEvdhD8wRCAGIEuFv6bjj/sA0nQjS/T9v6dhcY7I3hLK3i2yZ6H9B2yfxp0hVqdw82djR1yUbHPxKgAmniL0J8uVnwuddNTwvOs4xwHZYM8CiLZAV7N6Z3YDtOuN74Inge18+wqA2/z5u+JgTGLE0B4MNt9jWcJXfx0ZuEuMHAf+Az4eX8vR4h7O0iErGkMb1i+HmfPDOAywC01W86axiOvg3MC8whsWioto3vz5FWJulgkrBvOf0kaK+ohhDkk8ZGRnyoWGyJ0T9ZICQ8ndThdfcX2Pb6GD0jV3iouPmZ5DLyTodKL9a4rOmMKKZjgatxBfG81K5okPqtvQOWq9KmOQMO44FzYrAKL9Y9cIRPuZ3ih2py+y76tiyfWNEd0WJ/L7UwkurID/K+F/Jfx/EPbsCnZGyGHpDFTbH2RL7ZUZ1faVGUvtK+oOvEJiQDhJ+TDaLPQajFqpuQUGcz3GTUcm8Yy/veMLRbMjMyCEA8Khs6MDyLc5CD9c4wT8sPOj/zeV1DEWCRdRqe5SwvnLNIWBniui+FaUxYRdkRkw1Es6zzw9VcruiYgwcszb22BTp0h3+T+77G8z1KvmRlQJQ/bsefjPzmd8BeUWNF7JAlj4JpThOflItufDpivDjQh/55/It5dpe1PDnMSOTO+V7StxV3YVxoUkJ67aseXk5IrC4y2Gbgfnw8Dy+Dx1Knn4gII86Jusb4NndcCQpogQIjDZMg4jMxTBJGQ8NAtmcRYh81kOVdUtJce8Fgf0zbzpXpVyMO6fNbcaNvamTPTwAuuA217T6RGTYw5C+7BIfuFOmpj4/Ot+9CPpLs3uLKG22QFeMZa8EW8colc2314FJyDpaJo0LCInnoHMaCMWYhajmwNU39HsQFKjbUHEdvJcdIvwhgIqwnUQ/NkJgu3kHRdVqdC0Q0PcThC6i7N9bwHAAORg8y8vo7dMRGHRBou0TFA4RiYeKHmqts8oRJlXeC5Jo4rm8lSuqjqgS7UBGNoMcb6/+2HM6DxZzeuQmLOfBgBXfAjtkJJZgRFGRxgBG2SA0uTJHwIVdMw/GGeu99OyrSRVjot/TJUyoLz42PnuKT0soe4zhNWlnniPXl1jCOTnqC7ePA7aKzDBO5Dv51DkYgmi6CUqMlCR3hMfyE+EibyVN0RnY6Yn3gVdgm9d3ANl/QeI1asTIYXgTWFRpxR3B0w5SnEvW2C8A5lCBSaPTinuU4p5kQcoyP3ogFK6NFWQqdoIcmEEDuehHTYRQgZtpFyB4i7+KLyHCkbsINGuU2ELsYGAcz8KjSz4YxC6BrQtiaOQckUx1Hk+lWSCX/IQ1drV7uyilfhhTohq3d/u3E+EbCFk8R8E06QYZPyE01h+It6KWPCZ4y0n/u+TvhPHz+3Pf2wUFJzYTrvDaT3e+lH/J31atvUExfk64bSEMhMgfaLCd6LAFzrQtOFiN9gMJxznGpukNGyhwPXfbjYS7frsRN1GAVBPWBkQGnN8+Ndyoo7asA53jlKuuTkSGmbtH6aiNtL/5aXFmPiYiKcxkleTpZFTt5iMhNUJmVRTDdTkOGCuP6EjwGIPH8NYqygB1QHsslZHsWmdHqN9l9kzHe/VjIbftUal2ASI9iITYmP4igVfscArWeIVC75iwVcsrEDO7pnnaDOv/z/agnFylr/lMvzecIcuYrHE7/5aSJ3RCWdpRGmx3y46SnGYZo6BslL4NUsDDUB4GuWx5DcFiu8djbEAFacJsg3yOAIhkH3XaEloBiJ4zAQyLwNRmtMYCjsdYbWGrOV9fAFzTmzDhepxIrKR/vGF4/zjkye2aTvBAruDNgRshXNzAAGfTf6HaDOUCukv9PsviC8GV4Q6/fjoIZ2mIfN2I1RZ7hO7LLTlYjbb1m9toQzrtmPdIgv9noyWohyFzLevFMBr1aE0aagGW2g7/PwIbgev5ksTFU0Ppw61Ngs5xgZKdxAZrjwMvGu4UnOa3C+d1XaMcyADyouN6NnY/6le/17rYJyjozqOdQhNVKWRYDItLZDBy7M/qOBHD6J0NsY86EbohSDt6zvDLjwyz08NKQNcxWJo+DmI0oyYITTJitzm9WhlXGSut4mtZXLxXqMUCjWVoq2SWBg8sLQgfj5dzi2SryuSxxZ554rC3um+uN/7gpPFG73x9MumldEvAWWC47Q3pos8WmB66/jfuj9EYHWcn9s/Rx7bSxsN4VH8o4bjLcFrxFvdH4WyWoMJGlgSW5Kq7e6h4sfGaz/p7Tlew4mPglNPHI/OjH9sdCgjGHe8U2x1AJhB6MNHAAQfzYj+YTvRfaIbtsQLh0jrchbFN5/+fmgznfgIdi1UEnssPrk97v8DG+Pz8oNDAIBDS6V9C3xU1bX+mcwkGWCSGWCAQScx4mijiW1qgjINaCAkpDXgxEkTqLxuizqN/NuIMxpLEqWTgMfjICoqKrW+sN5KW3tRjKIYHiZBFBFfIA9Fad3ppDVYCrEGzn99a5+ZzCT46L38fkzO2Wc/1n6vtfda30oatIZX+dio5Qn5C1ikm+LDdjw1fvR+2RH+9KEdAQeUtJGdF7RXVITG0avR7sPwKJuZ1+1YY6Ipx+JdxN6p6Q7ui448uPdATQM3TjCV6kZE1zQkbBd2LYN24q+ZkOZLU76ubvndZ+mJoBSGoeDRfreSNF4HuZQVP9g5OMJXo/JCO374Tvegs/2+19xfC8ab8ZXlGwcNvpzwx6fCrw33qb4cMWaPW0mwTaobUWcSv70kWxlii3P+zIRLwFVJtji3DbHFeSRRqgC0ErQnYGYCYN6doVSRN90FYPFJFvvqLcU7g5/p9S7x6qEsxa9vZKGuT3tT/PxwFiztIVQa4AVwcjeX/8+l/wvp/yLDs/VsCAnhdrfPELBXwz6ikVUvgOXqYfFjLokeJPCyjLLW85QUAUrAV+M0saOFg0woUipveAYkklxRcogvmm6igqoh1kN8z6v0VPiqGA2g2jj6KBGXfc4RZ4HDB4ysSfKl+WL1h1kMHo2dOFbPLgSIWz7KQhQIRh5ZVT8zr4YYabaaiYkL5m2TCJoVwesrghdUBB20ql3JOKyiJgqkcXoY+RmNSnjSoA3yqK53X2TA6dL7R/SupaUCHRfSPfxvYn7uMuN4ICjFfdqdHYYNPbvdgxF99xElnseoYyyj+nBqod23RhpDV+fhQGQrZEvKNMCZkUTbKKlXqz1BassGMSWdapFQvhw3vGcPJiHaDEEYIC9jSkbBfGOVLAm7OEQamNrLUxYfuwU1Qnx+v7gunbimjavlwUA1VJbwBc46UYJH2+UXFems0zVdemGeZEBBaLsiyEJE6KuXRk1wPmWwiBLPDeQoryPBQvzHIUZ9nlFN1Bc6V/W14gTg5mnYBDPhCtTDymNPHWJZz128zZifUgjLF7cfzELkSUGbn/W33hRNFPU2OSZjsh6fcE+/kH1IPhXzuSl+dCALctkjQ+x9bpP2Pku2DxXNpO2z3GLV5WuTN9ptn8U32m9vF52ov9VXo22JzBSFx6ERJTXT1VCvGjoWE+9qiIuISXcze7S3imdaiYH8sRWwjLvBP1rBP1qJfyyz7i87lrcFWKtlRz642koMw/6yI4e+EGu3JXENgxiVfqagJ0aBUbwa6kugoCdGQVlfHs7pcaK+Txy42npoh+j7MBuYU+ayXnAoBVyW9atq62d0GDBGXxTu54PCeUKd16PO61XnGVVWs3GRPCNYESyuCM2RbBJViKpy4E50k1hBBVLhv2OmY6+8DJARiJo6+qhmR7MPzmioorUNe9Fwxmvl6fZjEakcmaZmwnc1sVRaB589N24d0j4MV1HYDilcNaulFrXUqpbatKnBipraYF5FcJjfcH80S2LCjEIZcHYNlyfhLaNVXlBHR7MYxUH881TS52Hy8zD4ReGDwy/h2puxXkpteaWWuGegUmueOfbil3492VVMwhjtPm+7e8BPZhLi60v0JcnQfsVFX2VoPwjExy8ZwHD7qVqSQm6qkGYn4j0BwSN4aUIZs2NlnC+L8BhFwOeaMqicaKq4eZs7hsWfyIAahyxxECgfdG4B7eM0DF5wfDWXYaoSFSEL9xRvje3jFuyVJZY6SxxAitJdWXXllTR0C85ASmdSgfF0rXuM9WWaRSaq8sUuyX1coi1miIIT/u7e3ETG5dHFbx1umPIpLV8heGyYaQ2NLWz3Zqz6mBVsM1bTX/u97eH2lAFb3YoBN6gv3RW7YGuz3h23arG0/fmlgw3ilg/i94DQEpGmzlAcEfffFb+4u78+TRFT9ydxHDW1hbp21MsIn0GHdzNUSULWcJfevVlaLIqPfpvFumxRf+0ma26JTxTo3LEZMlEoFaEl2n0orbAd4Nt1pvDOAn+NJEC/W4J7h1Ip0+h1CaPhRyTIq+Cu4tDc2sNIIdOpy10jKfU9AAMPdwH8knO7B3DgrPED5BKgBk4SbqXGJ267Mw3eNkyA9mg0gZSrFgx11F27L5svZAr3e+c5qLFZbWhYMbyGQLcUAcQhbRxAOX78xWwGqy3+kk2EVsClCjux/UFtzImtOq+f+KrRtD4t6wCNNaJkJc3gXqrRcW75ND/9Y0SqABoQNzWMeK7tojoMA9G6zxJ9FOYFRy+k4i6lOtwv610AdwQSAj0toPQyEvyqXhNbHdxEdYmNt7bcu5OuX+OWp+jBXy4bp4SfhBoWjKvuNtAUbYPx4/BFvNL6jfhxSXk/+nV5d5oQ0n0d5SmpDMapDL/QxRZsMSvV5DWFb+Uvu3OcUqcEYGQISAutTzyWz+Zqb2F17kwwrzTqwFBdDB95idelLGu2Qs+A3h41EFzehOQgnv3EzZikyQgsVsbLPUNcO9VGS9JMYBfDAVUuG/++flrf8NI0kYbvWMpWntl7pF1iagLE6vqWccpgyeSRzXzsNEw5DQJNuGfygGw9iW/OtE4c5YrJGNXHcdEDL4z/lCfYHuMCTXrQC3qK4HMlfoFWkIdzGPhudoKbKsoDHFVNTY2YgnH2prjs9nEkeeVAz/5Cba/+ft13weSR1LVU55vDoMdRfMoOw2OJlY0TbMYk21t8KHgN+4MMLoAn7ipc3sGJYQn9n45rCWkvZzhKL/KJSw4yhxajKJ/+TqqDRyo3KPNc127O6yLuNr+K+UX4kJ9eI+6jDtepYG+jx2FfebPOd0PT5fHLP19MuBtqbW8YU7yMr3syNJWveyzLsOh051/iihnWYDQFLQlGbD7R8bI7Bk8HQ6NtA50UKbd0pjWspilBE12JlOeIK/jvZDGD/84WD5nxNygusfzn+htGEUGjiHuMLBebZRFho8il/Ncyv3uJRRkM0asdbdWDRWGSQb4HAKHgSLifyecReXMWJY7a60y14kwZYKNcaMbWCnW0MmT0V2GVAtgeAERp1BLDuiWnShSGTVi3h2Pdtoa3WKLE3fYns2uRqTnzuheYB+zSI9fniEsetwyAmjJE0U0WMYECIzfliDP472zRrabT36AYTu8LjNjdbyTJ+X7D3Q4a5sDzp5hCbW8wn/gHa2TWbHHDpnQFNadmbMzg3dgqfj9KUaIePO1IoaczoMJIXfQS4Jz2h0bw62xx1fOANR3wVVfnaFsPbXjv2zSk9kk4G33isx/CW/qS3VTKdlvhccMckf0YFGefgsqRCVA3ZdaAdTXGkguOv7fbpNFonakmBnIzffsIViXsY0d5Phe16UVIrM08UrxrADekzAob0IvOhmUVA8B852w2B131NusrRW6YLZ69LV3R0msCbioPWVXAOEpLD28L+gNFCWGphcfL
*/