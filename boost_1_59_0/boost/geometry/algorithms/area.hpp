// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017-2021.
// Modifications copyright (c) 2017-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_AREA_HPP
#define BOOST_GEOMETRY_ALGORITHMS_AREA_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>

#include <boost/geometry/algorithms/detail/calculate_null.hpp>
#include <boost/geometry/algorithms/detail/calculate_sum.hpp>
// #include <boost/geometry/algorithms/detail/throw_on_empty_input.hpp>
#include <boost/geometry/algorithms/detail/multi_sum.hpp>
#include <boost/geometry/algorithms/detail/visit.hpp>

#include <boost/geometry/algorithms/area_result.hpp>
#include <boost/geometry/algorithms/default_area_result.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/area/services.hpp>
#include <boost/geometry/strategies/area/cartesian.hpp>
#include <boost/geometry/strategies/area/geographic.hpp>
#include <boost/geometry/strategies/area/spherical.hpp>
#include <boost/geometry/strategies/concepts/area_concept.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/views/detail/closed_clockwise_view.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace area
{

struct box_area
{
    template <typename Box, typename Strategies>
    static inline typename coordinate_type<Box>::type
    apply(Box const& box, Strategies const& strategies)
    {
        // Currently only works for 2D Cartesian boxes
        assert_dimension<Box, 2>();

        return strategies.area(box).apply(box);
    }
};


struct ring_area
{
    template <typename Ring, typename Strategies>
    static inline typename area_result<Ring, Strategies>::type
    apply(Ring const& ring, Strategies const& strategies)
    {
        using strategy_type = decltype(strategies.area(ring));

        BOOST_CONCEPT_ASSERT( (geometry::concepts::AreaStrategy<Ring, strategy_type>) );
        assert_dimension<Ring, 2>();

        // Ignore warning (because using static method sometimes) on strategy
        boost::ignore_unused(strategies);

        // An open ring has at least three points,
        // A closed ring has at least four points,
        // if not, there is no (zero) area
        if (boost::size(ring) < detail::minimum_ring_size<Ring>::value)
        {
            return typename area_result<Ring, Strategies>::type();
        }

        detail::closed_clockwise_view<Ring const> const view(ring);
        auto it = boost::begin(view);
        auto const end = boost::end(view);

        strategy_type const strategy = strategies.area(ring);
        typename strategy_type::template state<Ring> state;        

        for (auto previous = it++; it != end; ++previous, ++it)
        {
            strategy.apply(*previous, *it, state);
        }

        return strategy.result(state);
    }
};


}} // namespace detail::area


#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct area : detail::calculate_null
{
    template <typename Strategy>
    static inline typename area_result<Geometry, Strategy>::type
        apply(Geometry const& geometry, Strategy const& strategy)
    {
        return calculate_null::apply
            <
                typename area_result<Geometry, Strategy>::type
            >(geometry, strategy);
    }
};


template <typename Geometry>
struct area<Geometry, box_tag> : detail::area::box_area
{};


template <typename Ring>
struct area<Ring, ring_tag>
    : detail::area::ring_area
{};


template <typename Polygon>
struct area<Polygon, polygon_tag> : detail::calculate_polygon_sum
{
    template <typename Strategy>
    static inline typename area_result<Polygon, Strategy>::type
        apply(Polygon const& polygon, Strategy const& strategy)
    {
        return calculate_polygon_sum::apply
            <
                typename area_result<Polygon, Strategy>::type,
                detail::area::ring_area
            >(polygon, strategy);
    }
};


template <typename MultiGeometry>
struct area<MultiGeometry, multi_polygon_tag> : detail::multi_sum
{
    template <typename Strategy>
    static inline typename area_result<MultiGeometry, Strategy>::type
    apply(MultiGeometry const& multi, Strategy const& strategy)
    {
        return multi_sum::apply
               <
                   typename area_result<MultiGeometry, Strategy>::type,
                   area<typename boost::range_value<MultiGeometry>::type>
               >(multi, strategy);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy
{

template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct area
{
    template <typename Geometry>
    static inline typename area_result<Geometry, Strategy>::type
    apply(Geometry const& geometry, Strategy const& strategy)
    {
        return dispatch::area<Geometry>::apply(geometry, strategy);
    }
};

template <typename Strategy>
struct area<Strategy, false>
{
    template <typename Geometry>
    static auto apply(Geometry const& geometry, Strategy const& strategy)
    {
        using strategies::area::services::strategy_converter;
        return dispatch::area
            <
                Geometry
            >::apply(geometry, strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct area<default_strategy, false>
{
    template <typename Geometry>
    static inline typename area_result<Geometry>::type
    apply(Geometry const& geometry, default_strategy)
    {
        typedef typename strategies::area::services::default_strategy
            <
                Geometry
            >::type strategy_type;

        return dispatch::area<Geometry>::apply(geometry, strategy_type());
    }
};


} // namespace resolve_strategy


namespace resolve_dynamic
{

template <typename Geometry, typename Tag = typename geometry::tag<Geometry>::type>
struct area
{
    template <typename Strategy>
    static inline typename area_result<Geometry, Strategy>::type
        apply(Geometry const& geometry, Strategy const& strategy)
    {
        return resolve_strategy::area<Strategy>::apply(geometry, strategy);
    }
};

template <typename Geometry>
struct area<Geometry, dynamic_geometry_tag>
{
    template <typename Strategy>
    static inline typename area_result<Geometry, Strategy>::type
        apply(Geometry const& geometry, Strategy const& strategy)
    {
        typename area_result<Geometry, Strategy>::type result = 0;
        traits::visit<Geometry>::apply([&](auto const& g)
        {
            result = area<util::remove_cref_t<decltype(g)>>::apply(g, strategy);
        }, geometry);
        return result;
    }
};

template <typename Geometry>
struct area<Geometry, geometry_collection_tag>
{
    template <typename Strategy>
    static inline typename area_result<Geometry, Strategy>::type
        apply(Geometry const& geometry, Strategy const& strategy)
    {
        typename area_result<Geometry, Strategy>::type result = 0;
        detail::visit_breadth_first([&](auto const& g)
        {
            result += area<util::remove_cref_t<decltype(g)>>::apply(g, strategy);
            return true;
        }, geometry);
        return result;
    }
};

} // namespace resolve_dynamic


/*!
\brief \brief_calc{area}
\ingroup area
\details \details_calc{area}. \details_default_strategy

The area algorithm calculates the surface area of all geometries having a surface, namely
box, polygon, ring, multipolygon. The units are the square of the units used for the points
defining the surface. If subject geometry is defined in meters, then area is calculated
in square meters.

The area calculation can be done in all three common coordinate systems, Cartesian, Spherical
and Geographic as well.

\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{area}

\qbk{[include reference/algorithms/area.qbk]}
\qbk{[heading Examples]}
\qbk{[area] [area_output]}
*/
template <typename Geometry>
inline typename area_result<Geometry>::type
area(Geometry const& geometry)
{
    concepts::check<Geometry const>();

    // detail::throw_on_empty_input(geometry);

    return resolve_dynamic::area<Geometry>::apply(geometry, default_strategy());
}

/*!
\brief \brief_calc{area} \brief_strategy
\ingroup area
\details \details_calc{area} \brief_strategy. \details_strategy_reasons
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{Area}
\param geometry \param_geometry
\param strategy \param_strategy{area}
\return \return_calc{area}

\qbk{distinguish,with strategy}

\qbk{
[include reference/algorithms/area.qbk]

[heading Available Strategies]
\* [link geometry.reference.strategies.strategy_area_cartesian Cartesian]
\* [link geometry.reference.strategies.strategy_area_spherical Spherical]
\* [link geometry.reference.strategies.strategy_area_geographic Geographic]

[heading Example]
[area_with_strategy]
[area_with_strategy_output]
}
 */
template <typename Geometry, typename Strategy>
inline typename area_result<Geometry, Strategy>::type
area(Geometry const& geometry, Strategy const& strategy)
{
    concepts::check<Geometry const>();

    // detail::throw_on_empty_input(geometry);

    return resolve_dynamic::area<Geometry>::apply(geometry, strategy);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_AREA_HPP

/* area.hpp
QRN99/2xx5nrpXEUf3fQ29vLqmiNUXKWofFJLWxmKi4I/2BESLD/VAx6LXHfXLqb+g64/XQY4Fi2LPceYBD04y4pJJLtL2L2Y5ay667x0we9tKDsG6E76HOonSoh8L9CK+3qJpdDVH44nzwuxy3Ks6uFakZ1goY12uXR2mxUSpefVyKQpjGnjNWyUFSH4KG+t27PGyEHPgAQQ28i8AiR+wv9PaKLPMqP94AxIhcVgvTHdt1VqSAK6593r0ndX/KQ1w+zn2ar65LC9kLYen2FVYEofEUx00g+lseb1j3NzJqQSK5Juc/Du/O4Yq1OdPj0SyrzmaT6pITl6EjxtiQ4//L7uQRB3F2KXJalaKAmQzzN+7BqW3Ud35B7XOjFaIMmQ0QY6lpq0RC2kGQkxi7Q27J1O6rsuhQUrpb1sWikO1sZmpUwkQqaEIsnkSxNPoEW/yta83ZWZPNT7tw8r7kn5M4QgnsyHruOZYhE0+/VCywyWdbovQgveTdG5rAc9KHZreIbIdMTIiPVgBEmJ6f3Rd5Av15ucXe8k508b4M9ZctPD2u8ZRYKtwBdwG2yow85/y/2mmIZj4CtyKmbPAFIFAC9L3aFNE1tdAuadBsH/TVgpWf/xvoUbOONfeSmcU/Hxttn9c2/h5ow3oEROLG3Nk38XgQgWnGNQzqXH6Z/eqz/SmQfpl0z64uQYLLvpUEsJ4b8EQwCzer4JEw+eEdETx87YcG+L2NJyUg+EBcCVGOnD/MRr5BCeY9BU4ELXqR2Suv9urK/ozwpWd2fENvIDGnE/9Owy3DURWDd1Htd91ABFDMRUAC/2fpdsHy1VRFuEZSrEmoxm6eSW07dciIREZbMWW8HXKK2gAcV5V4TjFVStOQynlxJpyHD6HFgQHXgWmweyNOSXHAFGVeArw4yP/RSnBhgcbOOB8DWua70bdX4zVRPV3rZD9sivKpcL1dgyniZqUUuTyCXWqoCaeddoIPKqYnmpRz9fKYxWgUGmqX1da6c3+YfUBnJxkVDXQQfiCWVkKvVNV6kkqe5RWENd7ynpFROMXFXPWJGwZZZg6SE6J1LkvDoW2pSDuinUCYJ8snaPdz00x8wYXBaAMft1lvFErEOpu8ITCoEjDfDivXHbQl1LFzI/3wfFdrCZDO7kq5y4ifbXjqT9BmjgQ+Hd+T7H1Ir7NV5YrFfRDHukPVwo6Xl5sFU51n0XivzVu4PxQF2stJwA0e5dDYbOCbn19Wco5mFoRUXgnhdTAl/xi1XITCEVx8Im1JS2wHPQExJL5Gfg9BcvK7w0qT4EYIm2JrGDQ2ylpkP3hN8FwDmKjoHmu97Y7+zdF+/DoYyBidLh2l4nmUqqsHqyvsjSFSd6aTKHo2j0/aAtfp29bv4B2KT3e6qrQTWVn0ITQ+QNrLsQBWPH6eOl/sl6rU6MHyVZ0mh1g6DuLMb5Rog0ZqsGXOMTswFIq4ajFW/X5fNU2DpD0S+utpPvxNl50Qb4o8vrYfjGu5iSsT4Be1SjOpwiCfPRc0KVUzl1PIncAZPu8+fbGCKgCYrQwLHIp2/p/MiGDkidyaHuGOjMFM30cBeSvOuhSI0F+wHnu2S+s3Fx8FdnjauWe2X88bgkUaWtkVTQ9GETs/tZJtN03BdZpdvwXd2o4pr/RMJuDc5srgxO1HNGTzziKm4bAjVct3hXw56D5GADMG+XUIWDrSngaypy9LgN2MJKfqy8+5mgbb5/x4rks/DKqb6PfpsigcU0Zs7OS2uBEPb3rFGZxMCw3sEoJApu0HEcQFRS+MWePI0ztIRjPh8PcneL0ydl1KK96m0Nz0PhV1rDkEntV6rHVL+SUekFwlb04jn75D7RJ/jsUkodmlPa3808Wzhd5BecyBwPWdQeGhGfwVTicqpl975XrGS+jbNrnZErUqLqRpFc4JWwJbt7ezXxe/Ir5ioDtD1cn3ksAneJAYurbkRIeRYOzeDAofa6nTmCv3bi8JCmKP0NnO5mh4CLr294CcK8r+UAg07vN1lhFY4he7IrTa65ClbxdALXc6DvywbpcQ7EyForhGBdclihEMm3EPPkxdYPWm5B/aV1NAticTYTBcYgYVPI5Fcc3odsQFLjeKOomjM/uPRgpPfQSqYg1ZFO+yrAxHKfQSfNVggl11e2zFVTeeJuO7x5w4pWWNVVXviGbxWb7Crp1ya9SnNvoD1Tey9X3XeozSZzCM0WaWKrvDldluJeBuu6qaw71l+Y9D9G5LGkXcxoJcPvL/pCqP4icslyetFyov5k9sz7pPDrsIxbBndbxbt6BB1fjK+hOHcj4KTxI/lbPNo/rvS06vik+AxEmjpFo7SJ/ohz2LzUWeoF6ekHoR3vbvBnwzqXoU4w7N8cjbDLjgHVG7/ICHyK8fPKARPkDY8VyxCjwcxjzBV6oWfUhs5idFgMrnEQJKg+WntkYFKRmSaw5C1koZrNBCAcIdNP95VLdbrLCRWvCSnWw+S3qX8Lmdffklc77M3h9qNLlvTWqammQv1TXOyHXkFYuNYDGup8kbgNdxxPWdEu3dFcyYgC34I8s+N/2jK9bHcoAPZxPcSLJg4x0DfguFwI7fyQ5Ihtpc55XJU1Padt0YBbtko8oBhvbdOciQPSF0V6Jk6fCGhbt/ow33lcL7NVYmk1PqYV4zQ39U8k84gc6wIHWhc8EP6Aw2QUQ74TeddFwhB06AiPq2czGjUAcP3Luolf8s/zbEA6UJKwmqIH8DZQydRlHUMygbHq0iyO7HUcVmMe/Epq8ksQLwlxeNrXhZSHFyKR5+fSvXSxlTdkVPi/qKX7sKNkALTm+gfiWhmYDBMUMx3IxUjGghWIY9lLfvGsV86Xi5USnmZ80UdvnNtuLlJqiNcoxMwTYQWsPUcutgfJ+vxGl7n1q5dJv2kMzURs/5w6buuMJzytt4C/Vz4RF/+MM81JL7Sq0u1d4m0TrtTqIoX64Gcz9NLoS4SgBw6Qy1Sq8zzlqZcUyApAkDPVA8VlgSkL7UZkvObvdetswZrlteX1a/Emx7bdAXSQvb7IxdrnwcJXTwjTPZ28G5ToD0dd7zqbtmMYf6+BODNWh7Q4sNutU21mPynTcdWIMc2BKQmLvphTnHjAqw0G52py3wYIN3p2rTFWqtzPGGSD0G3Amc2tivJ9Z51DZLZzWeWSq/aLOrqVmuUrdQKopfTjI8+XgpvGmpPWcghiTGX8QW3vSarTlUSk5T4K+/t4MIebLxat68N93VdXCYJjDFfYFDTx2e8A45yAg7w2zCrhtcv/MiPYKdAaVyrLxV3vYCtmR5LYxoiVOt/pJ6lNeo0erk6yNqI+1Cr1ShM6+Ar/mgXoyF4YmaD/7FPB0uLvyPsaM7cIcZBiEmpbhyzKTIogqWsG27wO0mD0UIWta8/GDoWs6o2vdaOGjek2nNxWwWzReqUzm1punXm6aoKadlxFNyPSmxF9t6J0hs0+bwebKm6dabosg5oyQqfGuoY8w43QsTLM6290KBOHsDPCOzg6H+AxBI+Et//2vyky3oI/OziMdGKtldibyT3EYlgrM0T+WsV+90fJng0uptXLdRy6MGrlXPzfrvt2Yk0D2wYkdt5GqD2utsODXd0bBn9Ka2bK9NXbFP4nvjlSpGiyWEWNsNk4ObKB/9TQXI9nILsQa/kfTdb9Yb3yfanuR1t6aYdhx9xq2xqv5sapngkBi10/SWkiSv4yS+4qxe3ptRHbXQF3FUU5XGzjIb4gdKN/VzWqnXRZD4KEsTjxpOKs9Z/TR5MpmDQOOxfSXMqlSt8RTfXknomR3H+2z+BuIFZJFtVeoiO1X+cPFPduZozD0o+QEXo3yCMkpkQuGDbAhVIXbb16uhqp/NFSzZeTQEL/hXaqW+g2W0Uf/3QV2ws0E/+iLLfDKnSNrSJEx5eUUbtJRdvLsELP3nA9IfpRSo9e3T4XYp+wP0govC/pR3PHG0XK//k2q8gHP7t/akV6bIU//L2Z0oo7+HbvzkZwHx6UX8rLf/2Kp0+2ZkpL7/lBGbEuOvBvbsRgp91j+v+tN5lvz5vIL8aQDN3t9doHPZesonU8PQ3Qat8+8CKT+CIBNYhcKfCpTZNHpJjUgbTIHakxKcpkqTOS7nzOLC2VoGYV3U/XZHu8Rw9TRKtOvDGYgmMbXpDcyMM7DOq3SvcxjmbBly3GIoz6vnjz4U+FQX473p06XpsATy3WemBvUr3en75T685/iB0ElN7Zt+4KiGvk7J514tj29X3XjxUHs+AKoGzkd4nSNd8Hkt4OXU+qRxXZDZXLtqekavnVDSL/83qOQypHqKocyAFMn6crBJLglcnysg7pDcJhwd29+JJDn3jVpTIlwYj5D6qbhG5sYPfZEpRKZm1P7aHJ8Va6Ct5T+YAns54EX5GTq7QD14zp/IsSJXgrRcBR5ONcZVeXI+ZRaTXi3d2p2AoPnNuHFer/LVBsjjJg/PBkOa3gH8DwakVxa0bfu++AhVyqxTsrAEi3wECQKYpy7ynAHWrLFNA03VX8eJuR0Ctiw/TxdvI2t/lBjtWUx5N6WVkSuDTmFft2pboCbft9BfpzJPLzTuOmcrNuUwywr4OMGona/WnbVoz/FuXUoQpkyKsFSdAFhtb2bAdAi8kA8hD0TwONlIS4AgxKDDGS21i9H8JWgB1YQToq5b3tfWh2kSLS+v3zP+uqDgWLIFENVmHwy5dMkIxsFDb85l4Eh2XSJunfmhbYnnn4DfyXnYhAbZqyCqn5Z4Xh67GswnxIGOdCkWCYNHZ0SwjWGEFNRelXpXcrbvpVLyGpV9qlWxT5q/Hk5kkPw06mlBsjfOdKOunjABtVKInvHwigp+5aPa67lVpYpFeCXbwKAqKhBNDdsXqSQAxwbBbLtpZ67xdKGJx4p79DGfygEl6CjB3KyGdcUfsIsjzfoglzxJUErHO7nNpB/TgThVtAbEsa9b4HcMBmYKquW3JaCooLq/VxSnYykSskAzyt11B2/wyVAi5VI4CzUiFn73iFzn35TE8eDN556Uc5dZTCK6AE9asqM/y3ZUXu0N/xDYaUY87zVrl8pO58q7WQdRkuooIOY7mk2ND74c8CPozUZnjOSmmxDDRqVR83dTNYesEqYByNaKBhnBwtckasuAVAtwnRKhe0irP6AOwufQqcnJr0FZtDl0T0frmsRFopM+E4cFEmeoYMIrQ68DtbERDZ+Xo3gtvIpkjvpD2S+XAUcq7hgRvccWAILAMoQwLVKipn4W21DocK1jB6paZ4yaCCwqEabUi2epZLkMK1gUbJzzFIQO6a3uAaxJhkKaoPQQv4Znk6bJySEHUmTyXKtKOcwtYo+wt9Ka+8jiNGY4bR/Ga0Zb5N0Ct4GF0qCiB6n06cMRYPdWQGrNbcZ999crzi2IwLcwdNnCkSTANMCC6/zZd7ki0Zh6t3FGz+pCmP9W3PfbehXZYpoVDrroxIaKym+FbmnFTrQNcArge3DDFuxo+wADb/jspMY0rQRynj8XWXEsLXhLm1+7ynSXT72eF7jBv9+scRkz3oiNh/hDNxBZnoXPmHWlL2gl0EGu8zo1fbo8LfXpZmEe4UPOAS2zab4O1GtpaB/SouZm0mEv5x/vqoAaXIYNUEms5X654LjheInOEXHIjpdgA4zlQ0CsZdxdzCRYN8Ap0VNh6Pm84c/a2wUYLwEn5LhapZNBPGcKo1/Jy9raX42pNy8NXD5vf0rcQNWNKYMX3Cd/3kwmsychmag2pxpai2QJiJXd5bN/r50wiEXQjiYbXNhcvJVlW6UuRVAqr+MWYZoEtW/BogGWk9MfZwR3TcteO7HMH6qel90fhlS7gR+S2B+BD7nkUselyjujW6PfjhpopuMUJPPnDHbLLATIDwo18ixN88k84dLfbEr+RbHJutm5Btven4faHMPh1qPi4i2ejNujspvNFFKLRbjC091+qOdG8SzDRhWRwFMeo7FRf4cJINnawu0NNv7ssjn/cdkvsu+X02F9esiB2Mjdocxn6u2ZC1x7Q75WBn2Rfr2m/qSPnIwesLp/Z0y8xjblVViJpi2rekERm6IwFBRtJSfAwBYfnNu03cNa1tz/5XXHGNyGsjwM/AJ9Mr/iBPyCfmn/cx5WZ2drol9tuH3uRVwvENm8dBxZAZSNdehcAZRGzCblBXaGIToJj5rhftQF+jG979ssb2yBX85bMHQR2iE4IeKwGN8+gcfUH7Y21QPQXXlqyZry3ol1cgJdvdSU2JKk/5m25qewAZbocNZA4LjPG4QVOGcVk5oCi2XdcYP6F0iRdcmRTfwcggpMcxAuRU9WIjEHvQj83mAf+bQy8SW38d4gY5ieHNYOd4/+g2IomXbKLFmm/HErMt6zUJvsR2/UBzwnbULYC9D1j+l02NszEVtt49YUGaeGq2WZ9dCaUMxIb6XQ9Hm5KycNPuLYx+MfDhsqaWvte/jCF8JuoSWCYuRp6Q0w0UVKv2laOieWiRtLale4gb2bH1hPewEapJurDxSpeiybc9vsD88MvL8UUFys058eS+z75fkd3n/PxLa/6he/j3+6X0Igu3QcZ+qHhzO5c+hEh8dHQywcBLEi02fHH90t8fG4OR0J87qHOLSSDyF8o67bSK/O5+iSeTEFF3gaCIuR4kzyiPe2EJwnViPA639VZLA/C4fEc1xdBs3g3beo/FnDm0LYBX4lm1SxO/J7aOvX/QEHEdwxPAOO9TfAkoo55/Dl9LkhrSwgLP12YZkAG6gLFAfBZ7U5QyWVkBqH9L3dul9C1eYQmrOTRqrSpTxYFwv94mFS4De8quYMyfyfAzy+582iYFFpV0fAuHltsyYOxZK8HczEhlE9faZcOTtnkxGca6kMND9VsVNnyH+ESl7XsOb67mzpnnaZs20wYuBgC3M9hcEH+acbLZTnHF53jyOC/9QnsAg9z/3OHG0Mqm596xXmfEXzyynNZYRmGrLHf3XHxCOssKTozc6yxSHJtc9yOUSGzgVxB9Jub+3lLfX4yea+eImh6Kd7eVYwtt5745qjLY3eYdvb98xoGDbW6VZLpLCQftJE/bqtd3IDCu2U8A1lzyXjn3xmeB7PebLh8Pka/U8AaJwvB6ocKX9NRjfhCipeJ6HicEP+EeVlHL/PitNmcwj7k8WN29NgH4XWSjLaH9vKVh/HvqeBBqjTQxOyFPpm5AJ7ZB349kIwtaB7rgrzVqAcaLGBGmDXTCTlIOEOCstzm/gVTH7lYLumWWZ65Szs8fEZjcY1Q6RKErZ4tD7JgIa/VMWO25C9AlfmMO+gYqHXekpr6O33RiZO+0kSwfAUMNRtVQqnyfBoTGxk4BGUZswUIekZ1A1v3FvEPbksiKbfCDzWdDx3iNloz19i50Mk3CbYJr23YBMKr1R1aQx+rneaLoPmUCgAql7rBomzb/f56K3X/qNHXMARo89+kcTO83f5Lop9Pr0Z9OWAIN8fgtugWf49Q24RxGXzdMfQomZyX6QqnPCZGMPOdOVflvBuXsPl9zR2rOwf0VtcG9fCZQWgdfkFvmvQ7Q/tqcQPgVlsXV71wCCrgw9g/3p7QSDVIRXXtepFLSzLbZSejDWpjKtNKhWD7YdIf1D3ve5FhQghMcSNWxMRou+R+wNJC8AQlnUQt6NL6KLUV
*/