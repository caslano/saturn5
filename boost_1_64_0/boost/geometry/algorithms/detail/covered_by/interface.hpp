// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2013, 2014, 2017, 2018.
// Modifications copyright (c) 2013-2018 Oracle and/or its affiliates.

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

#include <boost/geometry/strategies/cartesian/point_in_box.hpp>
#include <boost/geometry/strategies/cartesian/box_in_box.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>


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

struct covered_by
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        concepts::within::check<Geometry1, Geometry2, Strategy>();
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2 const>();
        assert_dimension_equal<Geometry1, Geometry2>();

        return dispatch::covered_by<Geometry1, Geometry2>::apply(geometry1,
                                                                 geometry2,
                                                                 strategy);
    }

    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             default_strategy)
    {
        typedef typename strategy::covered_by::services::default_strategy
            <
                Geometry1,
                Geometry2
            >::type strategy_type;

        return covered_by::apply(geometry1, geometry2, strategy_type());
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
        return resolve_strategy::covered_by
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
IC4WpK8lvE5fT/ikSn+C+On0bTouVuniYI06fTfiYki7ONgqlX4QcTGkXRxstaT9ONgalf4L4mI7yWZPIZt/n/6WVxY7u7evd1tfT+sQb+uC5zfucEoS16d3RvaHx4c394/rin7X9ZsywD8IuPjmiqJv/rAeg4jm+mZ19xtw9L/DfQR++8Zmu+fdnlEv9z4G2ptAq8t44WL/3EfXkmK8SN4Lwm/CvNVzs5LrbCPzLSjr0yhL7VF3bTsIep67uDvMQH8b6JcT/TyUuww/onXlTOAOgA+AB81PnJf8HHh8HjxWyl6INHmbPYnivoeRzITscaCPlTSrYd+a9eYSZJ7bs/BF4hGL7RmJxfP5bHK4kE/kmpoSe9xp0UwhO5JoDeBNTXzcNJbw9zL4f7dEUrYYhmQkBxeLjHTYj6Tw5cu5cfAikqcc8nx5FvJkaHoyQRwCmZCelVy7I/rFTCVw/WOmJVGbuPuOTR/4EqUXe0c6e2LcV1ysucy707V1FI7PCvm4aq/S2dpdBHdnqel/PldYtcjni/Y6yOnbKa30dfCJpPGvESxSfPgm5sFcMA9xPCoCLoDVOosc5YlgnDI6fc71qsu/rtce/yV9tolNJdoymVQinvZg9wkMLh5sP+EGYvQL0lWiI0PH+bier+X9O7C9e6JsbzyRov2XIdCeVbF4Kk96maZzRNC1HMIuomovm5lNzkwyp9TDlcS32W8am/2GslnGfQs2+220eTNs8BvKBueT3u+ldJSEbEffULbG9Z9DNnSfju39j+r/SLnYWGt6/9Yc72aFjbVn2lPxXK4IKydY3xY2vexYfCThELA53idpEA7OeyW3JDhY5gMdrIpg7uS9gi1V+YGUclsUDswEd0DkBEaV7ZUJDhwVbk7CD1hr1B+AqwCO18FKRm9eQmkEtFVF2SQeqPPUojoG6XAtie6OHn+LgOZZfsA7QK2RSe+fyBSU/isOeNwuvHAaTYyF4dQ2W9O0bBE+gNN+1k66rQz1Ezi3S0dijD5e0HY0m4faZzCfLYzkfYTAqY1c4N/SU/tQaIqMLb/flsPt08kez+ahthlKTEymyKlKHoXTSinCyxPdqVRiVyAB4Nxerbn99MGO4pKkMMPvX8/b6GybVA1+LyOfeCJ84ndm6BMLnFU6F9KBP0Sihf+fZQ+85LB9IQrTbuAwymf/9134v8Dncfp78HnvXuxL1ASf9wDBg7qzz/s+pY0kcu8DeUO3Z/4S+LsfzNrfPT515HM7vk+L067tPIeu4c9ytHZNJYrj5lg2Edibl04U6CrsFGz2CG84k6c9LnvIdo6A7TwYZTv58Sx90Ce+IqOCBQajAC02Q/Q8bnhmdmKZQWkzK8O912LGwh+psZBxD8EufiLzN4uz8zdKY/72M96/DTtivlotPF/7uYYZeyJ6sSfWRQXZ0y+0PT3OulBrDpqxZTEm8jb+vYnRwE9Tem98v4tj6zXHr6LsIr5rV5ZcF8dwp5lWKcrHZW5v+ClVzLQkzO1/Y2zj18o2GPdb2Mbv0C4GF2kbv4dtPCy24fMlXcg8/iCltah2Hv9rNbfaDdt4RNvGf0kne2a2zqTjL4kk2dBMVpqGNrrd0zNrd8tR13LmpaHt/4i2D+ISj1K6VrUx4//k2rjc+zN0DzshWkMHO/kr6AwOdgIc7OQvsJO/4f+/0//nwV4e1fbCdxpT2lZQz8UfNeu+Wmcjqfh+2s4RG01MJtKjlNnXcyXZ0j/1Gc3/op53yjg1mkqJj0nsw7yJ6s3R8OQI0iRzIc1XCyXHksonde7oFHraeL2tu53TY2SrlbDVf0XZ6oSbcU1to4YmyjbPm5ltCielq+m5wxbLNvq22Eb29UQ=
*/