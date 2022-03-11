// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2019.
// Modifications copyright (c) 2013-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_SEGMENT_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_SEGMENT_BOX_HPP

#include <cstddef>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/radian_access.hpp>

#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/envelope/segment.hpp>
#include <boost/geometry/algorithms/detail/normalize.hpp>
#include <boost/geometry/algorithms/dispatch/disjoint.hpp>
#include <boost/geometry/algorithms/envelope.hpp>

#include <boost/geometry/formulas/vertex_longitude.hpp>

#include <boost/geometry/geometries/box.hpp>

// Temporary, for envelope_segment_impl
#include <boost/geometry/strategies/spherical/envelope_segment.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{

template <typename CS_Tag>
struct disjoint_segment_box_sphere_or_spheroid
{
    struct disjoint_info
    {
        enum type
        {
            intersect,
            disjoint_no_vertex,
            disjoint_vertex
        };
        disjoint_info(type t) : m_(t){}
        operator type () const {return m_;}
        type m_;
    private :
        //prevent automatic conversion for any other built-in types
        template <typename T>
        operator T () const;
    };

    template
    <
        typename Segment, typename Box,
        typename AzimuthStrategy,
        typename NormalizeStrategy,
        typename DisjointPointBoxStrategy,
        typename DisjointBoxBoxStrategy
    >
    static inline bool apply(Segment const& segment,
                             Box const& box,
                             AzimuthStrategy const& azimuth_strategy,
                             NormalizeStrategy const& normalize_strategy,
                             DisjointPointBoxStrategy const& disjoint_point_box_strategy,
                             DisjointBoxBoxStrategy const& disjoint_box_box_strategy)
    {
        typedef typename point_type<Segment>::type segment_point;
        segment_point vertex;
        return apply(segment, box, vertex,
                     azimuth_strategy,
                     normalize_strategy,
                     disjoint_point_box_strategy,
                     disjoint_box_box_strategy) != disjoint_info::intersect;
    }

    template
    <
        typename Segment, typename Box,
        typename P,
        typename AzimuthStrategy,
        typename NormalizeStrategy,
        typename DisjointPointBoxStrategy,
        typename DisjointBoxBoxStrategy
    >
    static inline disjoint_info apply(Segment const& segment,
                                      Box const& box,
                                      P& vertex,
                                      AzimuthStrategy const& azimuth_strategy,
                                      NormalizeStrategy const& ,
                                      DisjointPointBoxStrategy const& disjoint_point_box_strategy,
                                      DisjointBoxBoxStrategy const& disjoint_box_box_strategy)
    {
        assert_dimension_equal<Segment, Box>();

        typedef typename point_type<Segment>::type segment_point_type;

        segment_point_type p0, p1;
        geometry::detail::assign_point_from_index<0>(segment, p0);
        geometry::detail::assign_point_from_index<1>(segment, p1);

        //vertex not computed here
        disjoint_info disjoint_return_value = disjoint_info::disjoint_no_vertex;

        // Simplest cases first

        // Case 1: if box contains one of segment's endpoints then they are not disjoint
        if ( ! disjoint_point_box(p0, box, disjoint_point_box_strategy)
          || ! disjoint_point_box(p1, box, disjoint_point_box_strategy) )
        {
            return disjoint_info::intersect;
        }

        // Case 2: disjoint if bounding boxes are disjoint

        typedef typename coordinate_type<segment_point_type>::type CT;

        segment_point_type p0_normalized;
        NormalizeStrategy::apply(p0, p0_normalized);
        segment_point_type p1_normalized;
        NormalizeStrategy::apply(p1, p1_normalized);

        CT lon1 = geometry::get_as_radian<0>(p0_normalized);
        CT lat1 = geometry::get_as_radian<1>(p0_normalized);
        CT lon2 = geometry::get_as_radian<0>(p1_normalized);
        CT lat2 = geometry::get_as_radian<1>(p1_normalized);

        if (lon1 > lon2)
        {
            std::swap(lon1, lon2);
            std::swap(lat1, lat2);
        }

        geometry::model::box<segment_point_type> box_seg;

        strategy::envelope::detail::envelope_segment_impl
            <
                CS_Tag
            >::template apply<geometry::radian>(lon1, lat1,
                                                lon2, lat2,
                                                box_seg,
                                                azimuth_strategy);

        if (disjoint_box_box(box, box_seg, disjoint_box_box_strategy))
        {
            return disjoint_return_value;
        }

        // Case 3: test intersection by comparing angles

        CT alp1, a_b0, a_b1, a_b2, a_b3;

        CT b_lon_min = geometry::get_as_radian<geometry::min_corner, 0>(box);
        CT b_lat_min = geometry::get_as_radian<geometry::min_corner, 1>(box);
        CT b_lon_max = geometry::get_as_radian<geometry::max_corner, 0>(box);
        CT b_lat_max = geometry::get_as_radian<geometry::max_corner, 1>(box);

        azimuth_strategy.apply(lon1, lat1, lon2, lat2, alp1);
        azimuth_strategy.apply(lon1, lat1, b_lon_min, b_lat_min, a_b0);
        azimuth_strategy.apply(lon1, lat1, b_lon_max, b_lat_min, a_b1);
        azimuth_strategy.apply(lon1, lat1, b_lon_min, b_lat_max, a_b2);
        azimuth_strategy.apply(lon1, lat1, b_lon_max, b_lat_max, a_b3);

        bool b0 = formula::azimuth_side_value(alp1, a_b0) > 0;
        bool b1 = formula::azimuth_side_value(alp1, a_b1) > 0;
        bool b2 = formula::azimuth_side_value(alp1, a_b2) > 0;
        bool b3 = formula::azimuth_side_value(alp1, a_b3) > 0;

        if (!(b0 && b1 && b2 && b3) && (b0 || b1 || b2 || b3))
        {
            return disjoint_info::intersect;
        }

        // Case 4: The only intersection case not covered above is when all four
        // points of the box are above (below) the segment in northern (southern)
        // hemisphere. Then we have to compute the vertex of the segment

        CT vertex_lat;
        CT lat_sum = lat1 + lat2;

        if ((lat1 < b_lat_min && lat_sum > CT(0))
                || (lat1 > b_lat_max && lat_sum < CT(0)))
        {
            CT b_lat_below; //latitude of box closest to equator

            if (lat_sum > CT(0))
            {
                vertex_lat = geometry::get_as_radian<geometry::max_corner, 1>(box_seg);
                b_lat_below = b_lat_min;
            } else {
                vertex_lat = geometry::get_as_radian<geometry::min_corner, 1>(box_seg);
                b_lat_below = b_lat_max;
            }

            //optimization TODO: computing the spherical longitude should suffice for
            // the majority of cases
            CT vertex_lon = geometry::formula::vertex_longitude<CT, CS_Tag>
                                    ::apply(lon1, lat1,
                                            lon2, lat2,
                                            vertex_lat,
                                            alp1,
                                            azimuth_strategy);

            geometry::set_from_radian<0>(vertex, vertex_lon);
            geometry::set_from_radian<1>(vertex, vertex_lat);
            disjoint_return_value = disjoint_info::disjoint_vertex; //vertex_computed

            // Check if the vertex point is within the band defined by the
            // minimum and maximum longitude of the box; if yes, then return
            // false if the point is above the min latitude of the box; return
            // true in all other cases
            if (vertex_lon >= b_lon_min && vertex_lon <= b_lon_max
                    && std::abs(vertex_lat) > std::abs(b_lat_below))
            {
                return disjoint_info::intersect;
            }
        }

        return disjoint_return_value;
    }
};

struct disjoint_segment_box
{
    template <typename Segment, typename Box, typename Strategy>
    static inline bool apply(Segment const& segment,
                             Box const& box,
                             Strategy const& strategy)
    {
        return strategy.apply(segment, box);
    }
};

}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Segment, typename Box, std::size_t DimensionCount>
struct disjoint<Segment, Box, DimensionCount, segment_tag, box_tag, false>
        : detail::disjoint::disjoint_segment_box
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_SEGMENT_BOX_HPP

/* segment_box.hpp
rCqos0RfzZR/TB7tr27IZK/Km4cz9R7OtHfA9NY2G/RTEBxIfNFogR8nxpaFpK1qfgkOtl8C/RKwBm6TIinlBgWYkSpTKm5g9GVCcQlfplE6QqqtHtLCZPVAbxPMiw7s4StQsijYwnf/7xAGasPL2Cf1aB7aLkigU2SslQubYWmPGsTb601shcYxdvZHSfg2CSAWDABAWCzMbRVwLMxtE4gszG33C1QW5nbEXiYn0/0CoIUfigCf8BxhWH+uhMxwxizAuGCw/yyL5JGS2a6vuY3qrDPKmayNaq0z4U+qt86CP6nmOiv+pLrrbPiTKq+z488OmukOOSO16BrBMtTK1SMo2z0iaeoffLoXOZOIQxJGtT42C0VJPwg775if73sF5ZOg5ZL3gfGsNha/eUl3U2PpX0PF0VNzQtnRU1eEnYsWBTKo9SNsY1KvpMeKj8+MnvKFxpe+GpqMOcZDjkxkTF+HgqCMeu3TlfSJQuA+Xdy5tDftQDMBAcpTqONp20Oxo/mMk0qa6ed1lW4WkUI5DQObNqDVSOrnmho1AQahdpNlaugbcPIi1VWFrLxIdo/E3MO0kqqHhSm7+Xn3iPn56mFgGMS9S3DEF8jeiGvQC2uwsXf0sYvmx19+wonIzcSpp8UIRwV5LnDEwBhrcef9SS1uWrXAJ43rwMBX8eyoQxplUltni14raSnGsYp8mXS41oRBzasvtUf4a3gLdXwlMMJZ4UVoahxekABzLJkmYDjRWghW4EMoD1QPsgoMvJUbeLt1eUTJfQ3h1qptcgZzD8ZvwPb2wBtI8BHf+Dgi+b0mmMLZYhzRO/oX/xxS1Bg3zH1MWX3Cq2UK7VOLoqAPv38ckRz55ODoaCiTb8EQTEhzDrlDVTP5NXH9Myd6Rz0iwGPQhWtSzIFEkMxEXcDovP8zIFClHSusogoJbYbvvEVXq9Rx8etQ686AWmuIag2PY2EbjJraxQ2CoFz6ZNZ1j5wT/yZrU/thltYPNv7Ih0PC9MptSyPMA4TJOfAeqfrtz6gbxt2SBt0Mn6G8KwRBZqrV0V1utBPONj0eh8eL8TjNWrJSNkLLsonS1PCGqJonwqe6Gixh2LRtIrlcb4x78dYNnutjTyP5K+Vx3XONklQkscml+0JFKD2oaKmG6I3GHDbb1VgfmoCxj7JVtgIxzQ2le+l7eVMjrPFE7ZAirT1GNNu49EnlMyVb0KnOZ9jiMjemunKnAkpbhXl92ATkWorflMNHETLYzUv/at50F+kKzJt+iH8/C7XCxvMDaLAtK3ydq84RLiHL3dscct0xuW5Qrjsh1w2r2PVuWEMnYMLLWQUH5MnyNESP3sOquZwBXVkqRhRK+xcqGsj4GIvaxRtuwYhIkPco5ZUnQCkFB5j7iGyJv0gDkDDrfXg+mvU60lkkE9p1W2CTSE4uH26GDUYVBcjiVdYR7KPgQ0n0QIX2flJoDxxQFBrDyai8xwg35uff2vOBZeKf5IXGuCG60ijJd75GR+TYnB7w265/6PhtRyq/XST4bYwuqsKH4i36xKkmFNeFSiNsKh7CCxe+47lhtApwoL0Fz7s2W/KrPiNlGbz/PJPkI446MIg2icDLwofKTD7jG9moO7K98MT3miKu206EzbGKQfhUksF3PTKkxAsFUtKfjwxRhD36ojLBHh59hPwyrD6+vltRiof8ZAnzfbUuhzdQtCFZVxb/zXXZEqHFAx2u1SdCeV41ymBpV/MELMfLzxxXFCKbX56keLWuFAO/BUpBCqCEsBnIQJKy+PDDQOxsQaxDR2xWgth3HhbEBhCdK4CAXj6e1aWRbefPTUlUuFtXYTYfLhurwjsfTvbOb94fq8LvPKz1zs3Hk9XcmKyG66rJ4feOWY0Dq7lSVFM1ZjWfPySqCWb4+DvDyYo+tCQqKtqYrGgcz8eKgJt2rTsRnoDuNS9CCfGLRR1H3xN1wHsPf/whrQU50ALNMi32EAGcOvn5JUQxOUdFHsKdExIXpUk2+sN4yG0yIHMwFT0x7voWrF2CPdn+RBrQT3Fvt0Sgd1UmucoiVxnlKoNcZe0ut03QWQRg/F2PwU+7+P69FokZWcQoL8Rw9znRmwySWH5soUU2KgtNsscC6f775XES69brUga7c7Aq/iP4kqLlICOIubaTB9hxtn93RuhCZa2J/6DMJLG1hvjEmMfo59WZZxQ2G3aO4/FLavl2/IZhTvP8MbeRF2WiUG8EqfC1i4eV+eGPljaNVvypledB5ecKCwCJVVUOwekbA7cYdEygl182JzdNhVKDpx06bUAlYTVm57U/heHMEYbP3Iqooypu8a4iCirTmHR72FPcWwGbO3a7kYbAGu1VZIvsNcleW3e5HW9Y5SqHXOWUq/LlqkK5qkjFBNzRrsMERJHztutyVV8/hMy0b4bmzp9skmKeSLHilUvkiEGGYYuogQDllymQ3stoptfUvRm1kRMIzbjxPwJaFFoyT4iwjqnOdx8Q6MbTb1A1Hh2WzUlKNbcxOAjkR7Dux/qqWaR4CBfjpb6gJSBtoPisFEwqIMHBzAtrciXv7zEZf+zHQ0rpeyD2HwKxf6mDjfP5an3wP5IuSampzMKEbL9P8a4YyzMfjoH4L3UQy0+lwNvtHgVv16mDt8OFu5xPCeaJsN89KpiR6m1Cvvjw3zL0sBQSK90PTf9cUfi+91G4i76h+ISnIQh5qMdzhZxl4QvRvTgIx54VpxiaKHt9AulioF2iNOXhYjhvysgNeOIqAQpH6eBHIIFtYgEJ3kLYJge2n1TiCICyDF/teJWAKRBEGUnGU6WktCucFfxWPRZQjr6CCgKCAGXkPIjeI3xm4DNFzSGRX38Vm1UGkgKBSganKe9E0QsWdRFhIz6yQUJEqSScZaCNaFzgXOHlq9oQMm+rCA4wKTiFevEpf54Ut3h5BvSml94chTdYHPBXzU6L+b5OQkloesUikQ3Zcv7H+jzJR79+siRPiq0JBUIfoGUl/8WZYcLTuVFEmmY9J/trTvZhTy7WcHcoYjV6NhbMaS5Y4PSW9rRMQU/sLKCUxPMM+MFmM8+JoAWq8NZ4ffFL2E+xOP/JQ7X6onJY1YmgM7bY6V1ENomrYuhp7l1NDUfqZkBDolup53D7XsabAgRc1zkKuG63AK5bdf0YwHUwUa+Q/lNUn7CN9QOLYmk/ZN70W7xSXY/y8G68OHIbvbH1ERC8JNJOh6ay2bH5IR8PTsKbNPOmaKYkMLLDRuT65od28a/9ZEipJU7joe9AkzQEGRpKDPFIQ+ng/6gTQzk7IIbSwaf7aCitMJTwLwwlHR07XoKjo8Va0GKigYMqEJOcD5wWo1f/WAhRN1c4y9GmolIiYJg5oYAFdmDo7UqYygvI3qTqhOj4QoQxgY5nw2LcszqzhgsqyevLkoXzdRB1U3EHHc2xOaEY8m69HyICM00TKTYTDWds6kx18G9DQxjbRqF/fk2KmXL0M6yzFLwj1xnj41mdMWa4GiOaV5vYMzijCtY0xwwu2W0t2FPa1WJm85vFTJOrTfCSlmgws3ioZhEQvzxfYASU6412lNyO6RQ178XpNCrnQZ4VXhVbbAuMVNzsoydfsEjJ/R1iMrrxyq+ELXYWseECNB8s+Ffp560Ig3R+6Z7WiWwPzG+bXG2MT3bVGVvQ3dmW9SrQL1PGMhgByDuzAOE31JzH4zNY2Fp6HDIfx1BUQH3c5KoztUzIQsfQOpMcthaETQVwHGJgFJ9X804n9Tl//sk8iW7/juOPjKA02geQ//FXBom29rRAgXrcIP78zbROxgZrmftNoaNTJSY0iqSwVeOCEo9AxbpLG1Toz70XeCdPRPOxh/PoT4oebX8lHtmakgwndCiPSB+NaZLul1tTg35AqO1YaOggd4+e21e2nUJ77nWNpT2hcWw/b4S6zM97YBIMw5/JKM/duS15HYiRNYZrvOQctE2nnFEtYtcaRWplrSFF/2REr6JjlWiY06sDOqYgrgfrp0kBghNf9uKIGm4WgRtGgKJsnkdRM5Yk8IQfvDMVT/ijf5ul7hznluURNKjBbWn4v+HQeA7DwfEnx2QLOr6ALcBkwRKcKceRCb3oxDlqmCdqSFMo6XK3nyu3KS139LGn6JZSJgVeVCYE0ehjaBuitr87A4vqbtMKGjh40qzyKrYtKbyKTyMhRpfrPFR8CtX4/1WSm46wifMO91iRzo7pcoJ01/tGYDOZ2zkFLKe+h9r2YOqGgSNXnVJG3/tRSR9ceUpBP3OcACbBRQ5cnyu4+JTOTqP08quT+SYJD0foyHVLc1OAZIBqHVpxFTTLG3jyLuDihq/BUBBQwERVJ00+lrCMPjhlThftncmjyYHm2n7Y2az84M1mXE54Dmjl82sS5e+E8osVDDahmv9tdMwjfAlbaXdoDbvgbdjqgtmQP14vrqx0buzwXyFR7RVafBWfbE09cUZorO9AC+F81CLkIlZj0h3Kz8fvzkNzgWCmT3nLy33XoCNg6cnwAwxdZYH9EDcC/deOOpL1SNlo1EENDffJ7gN8+excaqr7ba2ln89OtPR/ZkNRfcWd0NY+8yYM2+aKYlvNd6ND2Sh/67UJf2tMlOUeJJfrFwnTzd0jAilGhzNCE6LDmaHs6LAhfA2u88Oy+4jsPiq7ecILm3qnug+fuR94kuA4FdW3+mgBbA+vaThe4b5Y+EVC8pLdr+/iXzdaJNjhDzD365o9JquGFr8t1DuvuPSoLG3lmVIqPCkG/yCOKgjirTcRtyk5WducqVl8bBZu0XRle0p5B/0034m+gqdoRuz5bZnkqoexVxAScVdT4yitc4sx9vQ2FSco3eA9+rKVbEguxxuq3RSXlWxfseMyWidFXy4hMDGj8Ets3CtitGhbXZshSWmbSffbqPtt0f1ekfgdlDrus22O8GtrURPNux4X1k5bXyV9EilI3+B1n4FYf/duOwZSac+xEC4kf+u90xTq51htGq5l9Fh+ClQ79lc/X5WdI8VWL4619NEE4cWdu87uwl89zMJHmXuwIHyYHSw4UPqvltku9+Hm613VR1sLmZu7qpa3OoGZspO//jDvuQ3EbnosHYaNoJqzG5aXVg9v+HtC2ff0NWI2wDdXRX3LP3WZs/SZ36DM9aXVg81/j+/RnTwvXpkrRReGlOjKiBRd2Qy7/IM7YJcfddxMeij3HMdNx5a7UrZtYiUxnGunSa6wjCUEPq7Hsy1JbmBFqWrBKg0u08jWwPSkeKCwxbQPmbegTWJsjt2r2jshsxaUfIH7M/Sh2G9sRpGG36aYSfmnrLGxwQLYHU++N2OouNNTemPIvKMTOuvDKtiV+oIZwEW9Nx+R+AIvIljtPsWLgJJ29BBpHwoV8KgAaLHCpuwXq/e2ZuBryxAulPXsUravEPFTwmZlFsHdZhFsaNyoQY3GUG/Z7CzatSso7QoOkQOWGvUrGabY+vlEggYEPtybNC3mTWjphDAfWQFk0iDpzBpl7Qm2zyfEH7uorSjmGeQH7yJCq1IZuSLYWltnjYFWlW41Jy7RjVflqpfQUWBLFbRLe4HhJa44V2aqIJcYTRWBhO3Ku+2drZViQIDOwE4VjJ+CqROoic4V3apgBFcv3Qe/C3KKqbkrjgiedL8ebY1I4SuZxwEVO1DKtZNLXrcHj0FEF7JZxF87biD8jduM0hLmCUExlpCPXVBPVUTsBGzgTdJB0ZSFn+5beNjIntAXJUswokmDubKZY9in60MCCJWMv1iRWyOl3c2zMThZovjU0A7UubD+hCVO4gSi+3HyfYFtke8rTkHqwPW4q8eAa/VeDBCGZgMZeiZxwLVv9Io7c7VuxTlSkRJGK+IJA4b4iLseFnun9yUTCoYlIKIZ8hFGKMOCjgHfEI8+PgeeYVivLB6CMStR+F39pxXWla4ohUUIPfjZ1docREiM7ENQQxRLiT3zaCbB1tpUMBji1jNJZyP20W0CgNSqEnFT4zByWZciTgGITnYRxTe/AEGvyI6mB/8FEWX7I3lS8ZBnYLkmhXRsu0sX/caJwSInVavBSpCLu9HQPa4kBvxD9T5YSW68ewiPyHONeIc/14QX+HNteHs/1x6b6+ATYJvtnltW9uPlEXldlbxugbyuUl5XLq/zds9djHo9Ckw/1yavs8jrrNBt4/2x1Q7e00GxBDdW/8cRVDWalyxIBFhBarvdaPMgFR+K5yJZnQNkXZ40l3I1FYY/ZHPt8HKuq94Rup6tQ/YUJJ4b7Ww2fyuHQnh/AiliWx68gSyRL3ItcYTOZzda4PfUmtpAxhSYxk+9eINm68P8ttK3Qk52vTM+KVZlhFRulytkpBC9nxR3Qk3G2DwH/3j5sBJbV9adg33EJ+8eJ8XWOUCmwCcJnthcA0Zvmb55SOGroVF7+dEnVfcdbOx4DI+6ar4WnujIv8ziFvnuAxRk7kkGxcxrOKN0b8YXi2MYGaf5AjXKS++IosTu3uRWY8BknsJHg0eNEPPgwjPwiK2l0ES/uhwjF+HjYqAt+nPrPMJAK5xHYW/h353Tb47w6ecjO969uWqeJgstgF8cTQVZF//N/FHxcj7KONdwDjwItKe0deM8ta0J7AweHavRdcvO0ui3T6c0etJwSqN/UZ3S6Gcv+zKNdk4fs9GHMqjRfwCKE/Agxo5fKhj/54ZRrZg/VivuWXqWVkxObcXckymt+GBBSis+ufTLtKLRNmYrckUrTtyQbIW4j+gNTSRNRzZf9CsL4erXmWQKui7fa5tHSoVx0cfQVjyJAwqj2PFLbH9VYnliO2F5IrojQqYhUdzxIVpSp0Cmlcwjc8bY80T1nRqR6kp55wlYN/dgUyhsVvAZDG6UaH/vLnxM9E4R9s49ib6b9yP8mujZ3D8a4PGApIKNzIARUKMf/QSkfX6sSpvCUdkO9cHp392GzcXwDGrz2/JRZmxz0r8oLqnqjUdZuhCP1qB7T5sxRsVVhC9XEH35dbLn/Qr0+Sv1wwreNwcMU3W3PeQLgHtnutB+rChTuzQgdE0Bg+dnXfJDxzAy3Woojg3TdUSs/QS8AaZjtVV7kNsPw7+x9gP4oTZQBlV20wNxFhQqTpF0PCQqZ3chr/nwARHp/v1QuWu9I1SqPIu1xWhicc9tMFGfw56IxbCWoOKvQZz+dgRx4FNgkSrPEp5DbgfeFtAkRdn7Ls2Vl4TwdiwRWn2Xf1jxBlBLxD+5HMVXEF7fF244LPoUafIx/oAFVfQdQKsSyIR/vH6/n0IjiEYHLxFLgzf8PFeqpagwQYNXvFPpuhMmDKOfcvRFAfXopsKXAU0hf4Kez3wJepouR8WEyK81QIX+FdX6A+gmozz3hBtDoIlWewMP6N7FHsZJCP1Yg/24IFHLjmQtpy5TI2Fe2daF/Vt6MpTtajWEs6O9SjyHxSjHVH+N6GzsaYF3kwAv3fm1dPBSn2qUvH8YZIFhdCfp/Mys7kKwxk20xnP8fBWMlRgfWJnT0KINnRWNKkKc8FC4UnQUIh5QgguFYuiiqahg9QZ+mGysClGdZictZqyoBT2M7VRKHvsG28vvroNegLp+ota1SNQFE6879FUcFifbC3V9VyTjv0af0dFV1sKnI6e09pXuD0103eEI5dTyGKzzURdzrK1oHtrshY1whnuN7W+GClxXh3IYMnSfoBKqbQ/tV19dMoxm7+NVy3qvgRrGr92lO6n7jwJb8uocdd8r7iwecoWNeJ3UFc7mFkjJGizR00o4izWYgvX8il+MYDRzC3BXwBbl+REvqqdWPSu+PaTowm23ddOq+TxU6VrnCH0TeDDIQcugK2UZ+Hw+0jrBmOwPXsIbH4fpj7eUPpj+bL88x8Lv+Vmu5Apbw2YWHqxt66K2lf0GeLG9/MScNBgq0jURXHY/9IQJ+LYybsG0bqN851MCEUy+k0B33FY/LPk7UeHJ/zJkRqfc90KXutY4Qg4oub92WPH5Ru1x+/hlpxUxJKPclUNJNn21cFe2wJiSyS+h+jdnkM7OFIviiiqmBfmytqM8K1Hg0W9DtWzw3Eo8+gqUPFWZJ/mB3xYitVP4MucXVDodwQy68inA4AwMK0MJr5AQjv71I8jkD6AMApNu6nZ4QkeDHfSWWrs2uZXe/TvkkJ7BEqC+v57AALNUnvJj9E0duC+TQFhN5k0sk8h/fNGw4meDWvmIxMt/cwAPLPDTb564+fUHJkwli+nExS8GKUvUh/gXmeI6MYF/AQJ0fUHI6dXC20S7svVdAv8V6RWA2HaSKLqCebFKo9nLojbx2sn2ZaEXF041P7/6R3mJiDkJL/D8YEa0c4h66uR7PoxEoDyDuaF7XtqeJ8KraURrkdX0Y7IMx8Q+J49C4YiKsyqTQXFQBMcQY0EUkMtSQuJEX8DT1RA2KHhXBWJ6AYY9W+A0BS04jmXwOPNlvD1C4tAbuczH/2s7xQpzfwxjAn//+alZOFfDPyYUtVepovfqTPE3dHER/Y2M13yxUaRWQptWQe6nY1AYgt0Nmzc9Lu5+LWzB1lXRU+PDk07OiRAUzyYZrXBPYTnhnKE5kY3h9Tp1QiVa81MUETqL1T4pQ9qM11PwApMk9Mvhy1WT+MUopMMwncZmLWD7ffyBewn4F8uyxi/Aa3R1RItEjBJIirc6ayCZgnqHZqfFYP5hMRzUqJ4gp23z1osUgiJsxrs8oQJwOce4Mo4em5miyCKehP/9Rlh/dxO/hO6mp1RHkOCK+mIFl40FDgyJkzqnqCb2MHJvPq0HWBZxMbCpaNDXy5wzlW0IVSw2ALLkFszjdrxm9gczxI7PMgLG/HJvrbKtDBNPDWbg/2PEYiNf8lwE19z2TkIiFFn4Pctz0AvJ75c3OwWio/0FXL/oT4Bbh7aIWy8lsNk3+PeHyFgKNTkWv782sauhGqb5EPl5ohFzMHNp6T5zO4awDn4Hr1Pzi5XYw7iXUyAwLzWvCP6bmUD5XubM5/IDuRL0D7YKhvwYTKjYw8QLvB+60LXeEJpO6PWwRbgmYR3qQyE8sIfxOIubMDbFDES9wFvC98ODSKvff+423f/vL2zTMOr4ThnM7RilPvhdtImgFuExzbJqAjUZZ2uTGvlQa5T8nASjzafEaI5+IWmfn/hC0hqItCxz+yvCQfGOT+AUUmBWBFdiXB3s/CLBfpHDaDqqOnkNPfh7EAyIq5Wf2+hGG6VNF+K/kQuJNTwPw64=
*/