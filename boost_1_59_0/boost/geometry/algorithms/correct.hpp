// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017-2021.
// Modifications copyright (c) 2017-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_CORRECT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_CORRECT_HPP


#include <algorithm>
#include <cstddef>
#include <functional>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/correct_closure.hpp>
#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/detail/multi_modify.hpp>
#include <boost/geometry/algorithms/detail/visit.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/area/cartesian.hpp>
#include <boost/geometry/strategies/area/geographic.hpp>
#include <boost/geometry/strategies/area/spherical.hpp>
#include <boost/geometry/strategies/detail.hpp>

#include <boost/geometry/util/algorithm.hpp>


namespace boost { namespace geometry
{

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127)
#endif

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace correct
{

struct correct_nop
{
    template <typename Geometry, typename Strategy>
    static inline void apply(Geometry& , Strategy const& )
    {}
};


// Correct a box: make min/max correct
struct correct_box
{
    template <typename Box, typename Strategy>
    static inline void apply(Box& box, Strategy const& )
    {
        using coordinate_type = typename geometry::coordinate_type<Box>::type;

        // Currently only for Cartesian coordinates
        // (or spherical without crossing dateline)
        // Future version: adapt using strategies
        detail::for_each_dimension<Box>([&](auto dimension)
        {
            if (get<min_corner, dimension>(box) > get<max_corner, dimension>(box))
            {
                // Swap the coordinates
                coordinate_type max_value = get<min_corner, dimension>(box);
                coordinate_type min_value = get<max_corner, dimension>(box);
                set<min_corner, dimension>(box, min_value);
                set<max_corner, dimension>(box, max_value);
            }
        });
    }
};


// Close a ring, if not closed
template <typename Predicate = std::less<>>
struct correct_ring
{
    template <typename Ring, typename Strategy>
    static inline void apply(Ring& r, Strategy const& strategy)
    {
        // Correct closure if necessary
        detail::correct_closure::close_or_open_ring::apply(r);

        // NOTE: calculate_point_order should probably be used here instead.

        // Check area
        using area_t = typename area_result<Ring, Strategy>::type;
        area_t const zero = 0;
        if (Predicate()(detail::area::ring_area::apply(r, strategy), zero))
        {
            std::reverse(boost::begin(r), boost::end(r));
        }
    }
};

// Correct a polygon: normalizes all rings, sets outer ring clockwise, sets all
// inner rings counter clockwise (or vice versa depending on orientation)
struct correct_polygon
{
    template <typename Polygon, typename Strategy>
    static inline void apply(Polygon& poly, Strategy const& strategy)
    {
        correct_ring<std::less<>>::apply(exterior_ring(poly), strategy);

        auto&& rings = interior_rings(poly);
        auto const end = boost::end(rings);
        for (auto it = boost::begin(rings); it != end; ++it)
        {
            correct_ring<std::greater<>>::apply(*it, strategy);
        }
    }
};


}} // namespace detail::correct
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct correct: not_implemented<Tag>
{};

template <typename Point>
struct correct<Point, point_tag>
    : detail::correct::correct_nop
{};

template <typename LineString>
struct correct<LineString, linestring_tag>
    : detail::correct::correct_nop
{};

template <typename Segment>
struct correct<Segment, segment_tag>
    : detail::correct::correct_nop
{};


template <typename Box>
struct correct<Box, box_tag>
    : detail::correct::correct_box
{};

template <typename Ring>
struct correct<Ring, ring_tag>
    : detail::correct::correct_ring<>
{};

template <typename Polygon>
struct correct<Polygon, polygon_tag>
    : detail::correct::correct_polygon
{};


template <typename MultiPoint>
struct correct<MultiPoint, multi_point_tag>
    : detail::correct::correct_nop
{};


template <typename MultiLineString>
struct correct<MultiLineString, multi_linestring_tag>
    : detail::correct::correct_nop
{};


template <typename Geometry>
struct correct<Geometry, multi_polygon_tag>
    : detail::multi_modify<detail::correct::correct_polygon>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy
{

template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct correct
{
    template <typename Geometry>
    static inline void apply(Geometry& geometry, Strategy const& strategy)
    {
        dispatch::correct<Geometry>::apply(geometry, strategy);
    }
};

template <typename Strategy>
struct correct<Strategy, false>
{
    template <typename Geometry>
    static inline void apply(Geometry& geometry, Strategy const& strategy)
    {
        // NOTE: calculate_point_order strategy should probably be used here instead.
        using geometry::strategies::area::services::strategy_converter;
        dispatch::correct<Geometry>::apply(geometry, strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct correct<default_strategy, false>
{
    template <typename Geometry>
    static inline void apply(Geometry& geometry, default_strategy const& )
    {
        // NOTE: calculate_point_order strategy should probably be used here instead.
        using strategy_type = typename strategies::area::services::default_strategy
            <
                Geometry
            >::type;
        dispatch::correct<Geometry>::apply(geometry, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_dynamic
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct correct
{
    template <typename Strategy>
    static inline void apply(Geometry& geometry, Strategy const& strategy)
    {
        concepts::check<Geometry>();
        resolve_strategy::correct<Strategy>::apply(geometry, strategy);
    }
};

template <typename Geometry>
struct correct<Geometry, dynamic_geometry_tag>
{
    template <typename Strategy>
    static inline void apply(Geometry& geometry, Strategy const& strategy)
    {
        traits::visit<Geometry>::apply([&](auto & g)
        {
            correct<util::remove_cref_t<decltype(g)>>::apply(g, strategy);
        }, geometry);
    }
};

template <typename Geometry>
struct correct<Geometry, geometry_collection_tag>
{
    template <typename Strategy>
    static inline void apply(Geometry& geometry, Strategy const& strategy)
    {
        detail::visit_breadth_first([&](auto & g)
        {
            correct<util::remove_cref_t<decltype(g)>>::apply(g, strategy);
            return true;
        }, geometry);
    }
};


} // namespace resolve_dynamic


/*!
\brief Corrects a geometry
\details Corrects a geometry: all rings which are wrongly oriented with respect
    to their expected orientation are reversed. To all rings which do not have a
    closing point and are typed as they should have one, the first point is
    appended. Also boxes can be corrected.
\ingroup correct
\tparam Geometry \tparam_geometry
\param geometry \param_geometry which will be corrected if necessary

\qbk{[include reference/algorithms/correct.qbk]}
*/
template <typename Geometry>
inline void correct(Geometry& geometry)
{
    resolve_dynamic::correct<Geometry>::apply(geometry, default_strategy());
}

/*!
\brief Corrects a geometry
\details Corrects a geometry: all rings which are wrongly oriented with respect
    to their expected orientation are reversed. To all rings which do not have a
    closing point and are typed as they should have one, the first point is
    appended. Also boxes can be corrected.
\ingroup correct
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{Area}
\param geometry \param_geometry which will be corrected if necessary
\param strategy \param_strategy{area}

\qbk{distinguish,with strategy}

\qbk{[include reference/algorithms/correct.qbk]}
*/
template <typename Geometry, typename Strategy>
inline void correct(Geometry& geometry, Strategy const& strategy)
{
    resolve_dynamic::correct<Geometry>::apply(geometry, strategy);
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_CORRECT_HPP

/* correct.hpp
feag7+2YI4b2YjTbFsrZLx2NI+e8E/DED3lz50mIh3DmK+i13SYtnR/yW95GtKLNZPa4x/Z29icnwst5tKONU2h2yi61x7R3ySRoKtFrTAnFJp7h60qylBX8ChrCF4CPsBnuhLX96oVy00oequPgvsfL8vdX82YJxdR2wUq7hYhe1CdJm1B3LWL0wjKEF7FaFXib7456OmYBhEDa7Ap0wr4XLe0+/hKbmVpM23F5VfGnj1PXOEVEKRhm5iNxykxW2bSgd64eyx1YXYrCUtG0kzEVqDlzr0+V70PRaropVM4MLCPBt5uI576rlJMJunm86bzpPp9RPimlA+Lyrn8rJQ+bNY+L4/UAyDk3jBBRMoJprvLO2cqvLIV0tJoqQfUdDRNnvV5QStHdnMK7vX8Ha810q9tHZNs4/woEV68ktNAIlVHRIryAEte8jEbmMymOi3TZovWjmzm/FbFfF/xVnRRI10SEBEOOgTGESP3NHfP9J0S+WTfBHXQNRA3Ej3/HFukbUPiQSN/efJFyCEwhHr+1+yrnQK1AnUM6fVv3tfrN8o9hBtISCtdXwxd25tsChONvur8QAb7mOd9hwQSIvz1/+2/L8L4OPXA/wX4kXtAcILOC6/VAGX6T2ZlJpuKoQQz51vgb8S8ipA8tMdofiDgwmBnXbx8+sCiQmODUPgTHz+BdPurE14Hq3q47CMRQ/769AYBPdENr57YQewRwEDDkSPyWIbwOK9cFqGRikYQsThvPcGiUXJSyqWm8Vq8RCf0mhEwWj7H28kBCR4c1pmHCZC8QHKXxBM/JwYTCEYNqy/HCfJ0MwMD2MVVyaozrLaOwdTypekSj9Vf3zsZiIL0z6lpXwQJQx15b10rN9RoUNjbT9oBXxq79T+9BpLv1+RO0fWj7+Fzg4J3x/myoV7S6Xix6zVS8Yvg8cH9n0NA9cB16ARSrd/z4JDL+0VB61d0GM3Cc/WFdRIiS763/9jLr3uP9enL2fBIfEC2Hs//qOeKxYby5vb8YvY77I9+jEnvLYbSQLZ2hveMxjKa6rP21eXlBx30zKejMpoXJbn6yecNt/craBvROdLniBtRy5ni/kX3acN9+97b22mFAtnY/3hVrArwuDzvxfgzE82S/rs+3Z7k+tiYBdVxqHwq7uzveElV01u9eAVumb8B0m8bu96l2gqvObudtGCKvhZcbyuzLz/M7BiSPl8VlmO6Xx/aqq8+H/lwi79cXACFsns7xGxsKyJno8/P19cqCOIrwE5D3AZThcx+llvxpdrkwnzyDLBKC9atDEU6HOLMQdGuamkBDTrOt8PlaaRCp5RRVP34/uMYliUWfCDMMHTWZ+u+0MbOOzHGgqNBBkJ4zN6eEeUf7KlNLGbeC6kl38q/aX80oV0u9QmBHX+NgIB7ISIxI6diZyFNRYJbbu0fBh5HPt7hkQUdZ3vpP4KhjT/gLQ+FdEgZW2zIWltuvaAS3MDf0GaPk5veKT+jgsXr4NiV4oQ7MJxb2Q+cNh+gh/flCUzYrc/T0qezJ7odRwTZFcVm88oL68VWJFFwZM33IrggnCabYqrW9ciRu/evDsL3ytT2aAAc6TB2rmTeELkE5j0ZVj0USLfmIVRVmB/OIy3L6MIb8zNsn1NipQT1bDwZaWAKwJrBgH/N0rcfBtcNAXSwUsMd1Rbw6Z9hbkmy6kHC0gYsjkP7CW6R8MEl1g6q9dkIVy1htRBTbsoBExaV/37m1bfYo00qsjkqFNQsh+8G4dW1p6OK41BMCXk4zOI+vP6aGuG46ZiHtRVLduUn2GE/k6pA65qpxk61g8coEe1wPBV0Y4Je/MRBlJfTUln/ZYKSyaZL2rNWSpXmS/niTvTOLjUdct/iQQzImW9nLYjuTHPbMC9kb9TV+UzNL0xTr7+RugqgiYd049Y9lswFr62AKf8A+ps87ffuW9/HHE6GpO37V/m+MGVyTS9n9E8/P3wQzTL8byQEQUIfE244hkigDRgMnL3FWjwwT9a1/PLw4sEHyXRrevtOb1zgMbUl4HvJZWu/3y6NWyaY3yfw9G0dqM60Q9/wrOIWTozJn/qF+/C4hF4bhWvHk3Rcz7QgvBGFxOvEkAC6JbFn0e3I1lCKr/fALO7eOVm9jAeA/7MHw14ZZUdcjlJM+TMDDDCqSZPQepeVNvL8D3Y3bm/xbs4Dz4JPXBWU7WB4T05YHHePrchNxHzO+G/bLaNAjGNtv+J0/v73g3PBiI00nSAHrqCZYA2y4t8TrR9qgK3/k9J5hfn/ksX1ddPdRMkKDODQH99vspJn5pRPUJ4CKX+s2dKUr7huExwJlynotqhvlTJYuv0o8zF4aY8xbqNhG1MH4Puqyq4qfa9YO9oo7oSPhjSOxfc7Ls10OPPTpsApWofaIjAPBCHpG8pDbbBNFwAW2aVW58vG7J76YQkLbnAf5d5DzJ4FUQCESMzBV3BtG/++Va5PIqMJdItV19eEs7OaA3n7n3pnAO7E9V31M1eReMdrrt2AjkZt54xs0YW6TvFZPhVyWHw8WBIWojdWzMq5OKCfgmDqLM43QOo1yHlC0Xbix1u2DKvD3hP7VQ1RdTRoeF7+533Tv8PnguA3+fR4dGzLg9rNlOwnw10PqrS1F1QT1HhmsS3hLGtRseV3IRVX27o3L+dlu7J19u8/tdcvOYyXVIcDUMfvDccZYX41wXNHvoGMm54FzkeBIMKek5rEoyIFfRJRPE1b9K7zarWDd6KYRpq1/p5w/rFoLU8c9RoYw7ylQbiE6t7+n8vcyyh1XFtn6oQwxq2ImB1dw2V2R2z+sGFYEIEsM4rMPbg4qJ+xIv60VYdWRyEsUeiVNzHbvj5sOhzeUu4zmwmjmNTojxSwyeoxpi3jDTiSqK8OX5BdpOqVhvTNHPuL04V3zY7cd7VVeCvPHuB7+dkVe0eaRI6Y26R2Vemn0Fe78CBtWrzeJQfu5iNwjr2TETA7Fadn6eEinPNCRvRdb4akLau3KpsVI9FAWwcyFkHu2vVnXT18GK37MEyN+TNSJ4QZXZWHW6T0uRWHG4LkoLlJOYyt6FNSJ2fQWwvVKg0dG+/dmwWbE+ehOaon3+MwknXbibsymsxrt4SCNKu8Ztf4HkHregZiTuheBZ4VAxDKxGgomakAjfB83pN7mHQTRFHD36MWXDO4kzsVrB20aOYJdfZv5UdyI/9v6xs/3NeHhQ9+ob+txr9r2Y2QLZwVHFjE5+AfdvZRd9Jcyc9Vahus3NLdWjw/nxRI8UTUNAIcl2M53Nh7qMK28nChDAVXhr6lWCbvOLli93csaJUAELhoNOhyW+Pgh8hQWY+yd8CqLZ2a9HUjmrbU1xM1EmEwLGw7b1yD9uJ9BYNb6Cd9pU8APk8Pa99ZNNtll2llQGfkDSm8tCc4bJ3/CwtfyuKdkaxnckLKN0KLrB9RHY2TV6NADo9WCqLr7z+99/938kudnO+zLUOo7Tr+hQErTy9+jjNkj2xWR6WYIx3zE/Twd3qB4K04JHrbIpo3P2mdWa9Rn0/qEfLQ2+D+4+evCeQn+ls1i1GKn2ONPRAYT/NJnIs//ImffYCOLBY5xc2KtGt7WE5RZgSRv/nJjdf3yScr+OhZqB2yc2XQnyAI8Q6dPStSRVET5mcwAobb72qPXSb8pPItHsRPhB4sGpUsGEq0L1TsXdF/rA8YwrEixRmXAcTzqeGdb0EMLUgQb0ZPA3P69nTzurK2F0xU+IY3jVESiUzcKzaLzkARXvqX8uF36ApgDmL3KSgFtDwwr+Lovew58zJ2l/PcYuAxkTShWMLqe5Z6cxBCYum9Ef+FZweZ+pbPi/oG59WH8B39Ne833z6NLeg12Aq4X2gXBFKLNx/bMck5/Rz4H7hn/jxry529IU7A2n3tEdjO0GYRzaKRvdonS3KiqyLxgDuBTkexm5P8gZuAiunooWn2/Lv56bEk8wPiJwRu+af2WYBtDsgTThmzzIaOvE3/pUeqZ/03JeMlBxfD3q1fuYMOD13DPPm++zT42DE1w3fWF7OutGxSyoevMQWu2QJf2awIopo2qtaMs2lF1dwtLqXIPE0idAxUunaG7DE+/VW+EdSLGBL3dgGMjRutduLJpdZnsge1g00OmLbRElZWE2yiDrC7ByWhzIwuGF7m1CQy3Ve7XP2fMBdIZK2+2rITVSHBqaIv2fFj4GSXeVwa8mLiypzQL91x+LdPyBkYGbx0uvj8tlic5p+qt89YIWYMuU0uWNivRBi9QtfU+ptqdAl+1I92OQki2Uq6GsSQ2l89VL9b4Runx3v6wNINdWFjFMIvTyc79tHV1wjtdZCl9YufU/aMBKPV+5wJsOHtvMYlfTVdqbjkJuEZ6AVoUrWAMPH9yLb7+O3rwIApRJjqRWfSuq3f+3La6bN8gKda+xH1cnwnezqNZdGqwJcp7Vn4Ueqc2YybqVtjQ3tz/TmTAby+eNam49S9rSxkn3t1mWVRIXYfIzBl3jv0+tsl/fGmUXVGW560mVvn0A/kxdsnsz1nGXPcH52FpFlDuEf3ONaG1DuiKnpHXJNmLbtvegmDU2pxt5OqpMs2/MWQEVx2xFYxsq8adn1A4+zfpvnR2PO+hda3Us4ErudCo0C3ydVjiwWbjCkLBtWvvNU7l5IX9aZdlMaapM7qBK6gh6mBrHlql1KgADizx01S98Km1gd/yFPHD07PASrtwadAA+hNx9N3iSmPNLYqAbvR1hURWYb2Rjmus0S1xi4H6vFLJnOdcq7CpHxjkYtCl0rHKsj1h5tbVmGEzxWrbZdfFtW37Yt6lcLfoET2BBWwv7TTpWkd8kZhf9NDIO0g3GOXIvqM78hi/nQSe8AofyVzlV64eJXk0MmwPvoI9tvo/2Ov+uiuv2Iaed2uLf1h+Oa3PA9TKUNVQP5HHfVfkg5N6EjCu44fmDTgNftgDf0idO6zYhDplKQRbwushy2HQ82RLuXwXU92Wy+G3dwOcicEvmMg413rh8IK9Si8RoZdMZxHqvgv5vp6f+Ngr8SW48qZ4VXP6P8jpukWZEJ7RMvKh1Cc8mDPyze+bEOh3YUtNv2uOvrox8mEtjLwSMnZSP+ktyfqedPZVVmx/m28P2zZ5x0nZCtwYXGtao5jf1uW1bCwb9pEtsM18wGfkAziAn4nsxJdG10/BzLvPS6hmIxd16ylOvtox8sG6EZyt9xTPpmU/+Ou6iV7CLU37Y82Doh/add38ZygrusGyC3k1C04FJsjgT1K1xdMm3DA5sV45l+56x08ImCvueu6xzsLUkn1VBGwMtSCKuic9Ec/Se+8nljIr0nvp27xqvTClAMcegY48KVuFd6hn1T33/PdEajya7KlbRiwbhaehO2wzwfUyEPNCipT1/BBSV65qQ2tQRU8omcNufCmE4OsDbVEvooyd60DkiiuIeQjddTXAhXx24gfPmbcfQwFT6APWxKd+lP0d9iBvlCv3neZ1IauKvieuC8v7VtJD6864mYeu1igI74imR2VWtefV6Xpxxlv/HeVO5gird3lOdeyV7xpTfb32I4qr6c9h7w7eCUdMRbGfTZ4Fw9l+KhZzNlQX4k25qntv8zxv0EPgRDKTDnyX/xJdxZXxB/zd/k77ifrkK9uRcwoAelvInn0J4H+Vf3UapsTntzrqAfkMNkA0/op+7c+KZdAJDkKZTFarhgIIbjfWdaGDqPgYpl4prg0ajgzfTa73Z7yN3hGexduwpl/pjpBTuyEB0vY0SzeE6SCEe8boMkqf7PwH9LP83un5u+gKWZMpI3rI7oBntoplX52iRraz8hQb3Q++Z7Y0njovSBD3/bZq98DGUEfyi/11+p8nPov2ZYp5ZwahjjLCcd5IrsQX4Wv3MZ5SRU92F4ZJG7VkZhVGHciPPy98AWXNPoCgD4IzgB+g0P2+IhvSG/od/Gw5lScFYPSRxFUkfCh8JDehkGLCUszCoKvd1/EDBFGpp5bs7x3Q5fNw9OOB4PtDhY1eV/gL2BHBxDRT9xiI3Z5yxTe0f7nCGxw5QIZKyfHH3c+j1IlhRhNmBmNtJEJod46zb5xwbhBnkinVxlGM22BFcGfvFURQ0f5bg69GRxypgG+ygiCwJYAPpRDy9c0zctZ3vqwHhKP8FKCvycDM078y7e/8+G5sFgD7kBf9a8sBna/5co1/LLr05AMUBEy8Uh8pH3H0DBN/eC5l+0b7X+pb3RmAgvknpvcB9sx3+Ne8A9k9bqjPhsf4Sy8T5BNAfyzirrSHwx2RmeXarsjW0BeB65MQb7+Hu53BGXfVbnh+tFe0pW1GSQsXEEx25HNsBaX/iUCUWkU0BIN/1vSr1BHvkf61xEBy7RbsVHCVnifis+Zxutr26MYECHsl8tlErRucPsja5B11Bf4d44wolQBYyot/LgYSXgr2n/aXMfBkdqG7x6lIfm/vKEeOL+O+MjGBBvwpy2dDp61Nh0SUZXXwJzpMJzB2SqXjae+fukQiBjN2vrzUbrW/cgFOee18p1HWR5/0E0RxoZJT/FHau/CzIdeYLcYSAZdVGK4x6Y+EmQFZpPBsUVO3/RSP/ZXHuWbWx2rN9NXLJNeV+9ZdVrT71Pte10B5iIq/TXBH8pyzL8sfm4J7lVAi8g+8PYgBwDfk359GEp/gHjBz3Xn3PANEP6LnOz4cQTyUuBefO+0xXVFzOsRZQh0oHsgHdAkfpM+Sf57+cgt1JD2P77yReKfMeSN6fTux+fu6PkA2AACz8QOxSXz+AKHM2Si8eurLhj16X6uQZP85mfYhEnDDLTT5ERySHpqMSjNgtscTwoFiQ7olDvp50xzy6euS8GwyYPPjE++Ga++ThLB6/kNWU9qD74ZuAGxPdI/TFsY2rCX72XoPJpSIZEsIJL3XTckv5ZHwTBQqi/ZJeXMVysD+U0ccJL5XOsDxY5rMmtiaXFvcA882ySXk2WuvckCHbEsMpLWHFaJDyi/jEfbMMUCE8jYXx0DZlfasvoe7tzrwMBAemozmjJY+4PxjWxKEckO/V40GkAR57mGFest4xD0vD1yhqmzKvAFuslG8057vBlhC/AekByRD4wegb3D33EOCQ51RAAIghBuBPSLUbgmQ7IBJyDb5R8izfPyj9x6A7AP/ZnKgcSA8ZD0UbQDXlujGbQ8mpBkVIApivdlGJSL9oL6B2/Mm4ZcE6QxgGZl+UmZJgdT2TgbsQ/sHmPYwBn7VinREPfPv0Q20h2aTfiDd3A2IhehQeoU/A0Km0dzpRpNRZUmz9F3vnpKVJ/+5fhiOurvq7ZWQXzFU1hx0Ek/GbXPqCDU5x29pS27xrNmsTrcFaZ1ym68+YUe3HGc5Hmc5zz6YWG1Ss2hdthqfrExLfPqrrX+WSK46KDd1Aiy2nzaO5Y2b+5tRsTbzDT85X5zGdtfX6Y3eO+vOB7TVmtqW6Xkck8Y7jX61B7gk5lvOFZ7/q97s2qRvI0PaJKNvMyFoA2o5lL8VbCu8Ga5bvFp+Fk84uRZJGKkorGqLrSrVM5xnPZ65l2lmx19kWAEo1zk0tu74ONtv7es+hjcvsuxXHiZzgRn2v9b5QAXtm0NcTZuHhir2te37Z5dOT5zn/JJOyJPU3lftRdtZEN3Z+8xR76xR74+1XI6XgZHb+7IqL+VhWWL0
*/