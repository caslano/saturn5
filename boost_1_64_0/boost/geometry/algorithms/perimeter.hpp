// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_PERIMETER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_PERIMETER_HPP

#include <boost/range/metafunctions.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/length.hpp>
#include <boost/geometry/algorithms/detail/calculate_null.hpp>
#include <boost/geometry/algorithms/detail/calculate_sum.hpp>
#include <boost/geometry/algorithms/detail/multi_sum.hpp>
// #include <boost/geometry/algorithms/detail/throw_on_empty_input.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/strategies/default_length_result.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

// Default perimeter is 0.0, specializations implement calculated values
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct perimeter : detail::calculate_null
{
    typedef typename default_length_result<Geometry>::type return_type;

    template <typename Strategy>
    static inline return_type apply(Geometry const& geometry, Strategy const& strategy)
    {
        return calculate_null::apply<return_type>(geometry, strategy);
    }
};

template <typename Geometry>
struct perimeter<Geometry, ring_tag>
    : detail::length::range_length
        <
            Geometry,
            closure<Geometry>::value
        >
{};

template <typename Polygon>
struct perimeter<Polygon, polygon_tag> : detail::calculate_polygon_sum
{
    typedef typename default_length_result<Polygon>::type return_type;
    typedef detail::length::range_length
                <
                    typename ring_type<Polygon>::type,
                    closure<Polygon>::value
                > policy;

    template <typename Strategy>
    static inline return_type apply(Polygon const& polygon, Strategy const& strategy)
    {
        return calculate_polygon_sum::apply<return_type, policy>(polygon, strategy);
    }
};

template <typename MultiPolygon>
struct perimeter<MultiPolygon, multi_polygon_tag> : detail::multi_sum
{
    typedef typename default_length_result<MultiPolygon>::type return_type;

    template <typename Strategy>
    static inline return_type apply(MultiPolygon const& multi, Strategy const& strategy)
    {
        return multi_sum::apply
               <
                   return_type,
                   perimeter<typename boost::range_value<MultiPolygon>::type>
               >(multi, strategy);
    }
};


// box,n-sphere: to be implemented

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy {

struct perimeter
{
    template <typename Geometry, typename Strategy>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, Strategy const& strategy)
    {
        return dispatch::perimeter<Geometry>::apply(geometry, strategy);
    }

    template <typename Geometry>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, default_strategy)
    {
        typedef typename strategy::distance::services::default_strategy
            <
                point_tag, point_tag, typename point_type<Geometry>::type
            >::type strategy_type;

        return dispatch::perimeter<Geometry>::apply(geometry, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry>
struct perimeter
{
    template <typename Strategy>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, Strategy const& strategy)
    {
        concepts::check<Geometry const>();
        return resolve_strategy::perimeter::apply(geometry, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct perimeter<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    typedef typename default_length_result
        <
            boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>
        >::type result_type;

    template <typename Strategy>
    struct visitor: boost::static_visitor<result_type>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy): m_strategy(strategy) {}

        template <typename Geometry>
        typename default_length_result<Geometry>::type
        operator()(Geometry const& geometry) const
        {
            return perimeter<Geometry>::apply(geometry, m_strategy);
        }
    };

    template <typename Strategy>
    static inline result_type
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(strategy), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_calc{perimeter}
\ingroup perimeter
\details The function perimeter returns the perimeter of a geometry,
    using the default distance-calculation-strategy
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{perimeter}

\qbk{[include reference/algorithms/perimeter.qbk]}
\qbk{
[heading Example]
[perimeter]
[perimeter_output]
}
 */
template<typename Geometry>
inline typename default_length_result<Geometry>::type perimeter(
        Geometry const& geometry)
{
    // detail::throw_on_empty_input(geometry);
    return resolve_variant::perimeter<Geometry>::apply(geometry, default_strategy());
}

/*!
\brief \brief_calc{perimeter} \brief_strategy
\ingroup perimeter
\details The function perimeter returns the perimeter of a geometry,
    using specified strategy
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{distance}
\param geometry \param_geometry
\param strategy strategy to be used for distance calculations.
\return \return_calc{perimeter}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/perimeter.qbk]}
 */
template<typename Geometry, typename Strategy>
inline typename default_length_result<Geometry>::type perimeter(
        Geometry const& geometry, Strategy const& strategy)
{
    // detail::throw_on_empty_input(geometry);
    return resolve_variant::perimeter<Geometry>::apply(geometry, strategy);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_PERIMETER_HPP


/* perimeter.hpp
vP/B5Pugcu4DLej6vzcFcdPrc0gDNI15118v8KTj7KT5mQvodSl5vJyLzSExQEv0M/L+APXa5bfgD/EjHbJ9KfEH9h1hs9ihTeNHTLC9oH/yTt67SfST+klb1T0y4+zoPnqWdNeeJd2JZ0nXepZ0f3v+2dG95yzpVp5Pf+Omd+uniNf0ftPw88k9j+QejVGZeJ+i+7y/VF/Lg1+kr+vvMg4tkL+DKGP6Xam83o4YgrPuu6Y0sHVl/pzN51e9//UbpR7d4GrEmGgcTuqZzoJz/Wv9cTrV6pmu8htfxjm4f81Hp5v7PhXAuRbqFuoVUx+Ue3Krp/tPUzB0p0tdua6irqfR8yCUl1xbQXy6bRLJKyVeHOM/ZjVWxA8d/nfe/zRNxi3tYSP7NvhS1oBE25dxyzif8PqSc1P1nhy51q/Ox1bn4jjeFseY24+b5r/+BppnNK9k//iVPKL3YNB45W/8dXstvHVqcOO8D/6Vuo+yPPM6ntgXTfXfzs6E1uh+0vHkk9ZPWm+c1z86P5Y65mvPtH6uPi+48Uw8jxtLe9fHdacTR3RonwJf0KBrUtJvl/X/t6YEZ77StQ/pef/hif3BKcEto2um9E8f4vbq+P/7MJdEn9m/SxM3RaxjCP2ej7m+OVDPx9wjkz3jrv97SaAnr5Hunmy+Xv39XqxZs/fuTe5737Tg3MC0pn1FS8671HTCp3/dQNOYPLl392Ly1wG61l1V89gkeh0guP1Lb36/vDf3lO6b1P+a35Ka8vojNCWnZSC/p0XbFDTUe5/pPdbQJ/elkL535iR5Tq6mE8f6T2tP05keYN4GMmYGqvmhW2rChq+j+xUtEYvM6wA1n3b37fz6cFJgOje5+y8/0VdJ3TkB6p7JNpIboGYgaQ30b9h8du6Z71O5/vTFftbzlOkPAtBU/hYFYuh5/ZHzmn7WOz1R6sm/S0nrz1f/Hiutu/7zl9M+QLTBocf9rcnArs1Am11bvXuiXKcxbSenAvz7c1zaVkz0xHzm2mSgeTp+Yv9rRkzs+/zxv+xdV6g0NRRWsffee+9l7RV7FxTbg7+sszOz/45uGWdm7ViwtwcFRVHEjhUrFtQHQQX1QVGsiBVRVKygiKJ+SWaycdzdOd+46ouXO7t77+bLyUlOzklOThJJf3x993p2453lODo371697+47Z55Sto+gh740kUf0IZf++DlD15bBzn3K/jHkP/2s0F13/+f2Jy+BvJ36AU+ytmD60Du7VevCMXHGqP+/L9N37MbLGnt219ChsS8+L4Pnw13nmed+PGfiQVmRp+JHdqY16mBcW6KeDF3IJOpqersevqvda4T3ciykuw4vizfNeUf5kL/jP15nV8VH9Zy4mA9/s8vf1y3T2vvpXVS5uDW3x+bh7pW4GDQc/xTymMq7Le/Ru5j0v6ztphvvF1/X8GFplP1+5fTf7izP+5mdubwv3/mfmfMea8rh3B03vf7W23nc2Qeyc2vKZ82Wefh5J+tbAr6sk8fH/L68k7tH0qXN7RPc3ORrznDdqXwWrXnH9+U8y2VEGSbfkTMwZbX8l7Fl3G47ydMuQqR9c0d52tuItDGRdvcd5W28KJHvWzv8c3b6th2UTMjLEu9gsI4cWL/JnjsU5wuZci2wcFHO8rnlpf668D/H33I7VJ+h9nfy/3T76nMIgJ+6t8qtl3I/fGL7UX2DBvI1dMr3NyB/0HNtT/XdPldsX7T9+DM9ynLb3H6UX5mHZ7Yr/Dvjdf0mwILOpDOwMT6czT3Yqhw/bFe9NxN0/jR+uBiYUrlQptmNH47YbmST3D0in2xr6BXj+DLOPfO/rHvdcdeq26lyys95umSxXPZWMPSfccbKD2w=
*/