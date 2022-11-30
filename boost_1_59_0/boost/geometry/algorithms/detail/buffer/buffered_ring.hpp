// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFERED_RING
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFERED_RING


#include <cstddef>

#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/strategies/buffer.hpp>

#include <boost/geometry/algorithms/within.hpp>

#include <boost/geometry/algorithms/detail/overlay/copy_segments.hpp>
#include <boost/geometry/algorithms/detail/overlay/copy_segment_point.hpp>
#include <boost/geometry/algorithms/detail/overlay/enrichment_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_ring.hpp>
#include <boost/geometry/algorithms/detail/overlay/traversal_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{

struct buffered_ring_collection_tag : polygonal_tag, multi_tag
{};


template <typename Ring>
struct buffered_ring : public Ring
{
    bool has_concave;
    bool has_accepted_intersections;
    bool has_discarded_intersections;
    bool is_untouched_outside_original;

    inline buffered_ring()
        : has_concave(false)
        , has_accepted_intersections(false)
        , has_discarded_intersections(false)
        , is_untouched_outside_original(false)
    {}

    inline bool discarded() const
    {
        return has_discarded_intersections && ! has_accepted_intersections;
    }
    inline bool has_intersections() const
    {
        return has_discarded_intersections || has_accepted_intersections;
    }
};

// This is a collection now special for overlay (needs vector of rings)
template <typename Ring>
struct buffered_ring_collection : public std::vector<Ring>
{
};

}} // namespace detail::buffer


// Turn off concept checking (for now)
namespace concepts
{

template <typename Geometry>
struct concept_type<Geometry, geometry::detail::buffer::buffered_ring_collection_tag>
{
    struct dummy {};
    using type = dummy;
};

}


#endif // DOXYGEN_NO_DETAIL



// Register the types
namespace traits
{


template <typename Ring>
struct tag<geometry::detail::buffer::buffered_ring<Ring> >
{
    typedef ring_tag type;
};


template <typename Ring>
struct point_order<geometry::detail::buffer::buffered_ring<Ring> >
{
    static const order_selector value = geometry::point_order<Ring>::value;
};


template <typename Ring>
struct closure<geometry::detail::buffer::buffered_ring<Ring> >
{
    static const closure_selector value = geometry::closure<Ring>::value;
};


template <typename Ring>
struct point_type<geometry::detail::buffer::buffered_ring_collection<Ring> >
{
    typedef typename geometry::point_type<Ring>::type type;
};

template <typename Ring>
struct tag<geometry::detail::buffer::buffered_ring_collection<Ring> >
{
    typedef geometry::detail::buffer::buffered_ring_collection_tag type;
};


} // namespace traits




namespace core_dispatch
{

template <typename Ring>
struct ring_type
<
    detail::buffer::buffered_ring_collection_tag,
    detail::buffer::buffered_ring_collection<Ring>
>
{
    typedef Ring type;
};


// There is a specific tag, so this specialization cannot be placed in traits
template <typename Ring>
struct point_order<detail::buffer::buffered_ring_collection_tag,
        geometry::detail::buffer::buffered_ring_collection
        <
            geometry::detail::buffer::buffered_ring<Ring>
        > >
{
    static const order_selector value
        = core_dispatch::point_order<ring_tag, Ring>::value;
};


}


template <>
struct single_tag_of<detail::buffer::buffered_ring_collection_tag>
{
    typedef ring_tag type;
};


namespace dispatch
{

template
<
    typename MultiRing,
    bool Reverse,
    typename SegmentIdentifier,
    typename PointOut
>
struct copy_segment_point
    <
        detail::buffer::buffered_ring_collection_tag,
        MultiRing,
        Reverse,
        SegmentIdentifier,
        PointOut
    >
    : detail::copy_segments::copy_segment_point_multi
        <
            MultiRing,
            SegmentIdentifier,
            PointOut,
            detail::copy_segments::copy_segment_point_range
                <
                    typename boost::range_value<MultiRing>::type,
                    Reverse,
                    SegmentIdentifier,
                    PointOut
                >
        >
{};


template<bool Reverse>
struct copy_segments
    <
        detail::buffer::buffered_ring_collection_tag,
        Reverse
    >
    : detail::copy_segments::copy_segments_multi
        <
            detail::copy_segments::copy_segments_ring<Reverse>
        >
{};

template <typename Point, typename MultiGeometry>
struct within
<
    Point,
    MultiGeometry,
    point_tag,
    detail::buffer::buffered_ring_collection_tag
>
{
    template <typename Strategy>
    static inline bool apply(Point const& point,
                MultiGeometry const& multi, Strategy const& strategy)
    {
        return detail::within::point_in_geometry(point, multi, strategy) == 1;
    }
};


template <typename Geometry>
struct is_empty<Geometry, detail::buffer::buffered_ring_collection_tag>
    : detail::is_empty::multi_is_empty<detail::is_empty::range_is_empty>
{};


template <typename Geometry>
struct envelope<Geometry, detail::buffer::buffered_ring_collection_tag>
    : detail::envelope::envelope_multi_range
        <
            detail::envelope::envelope_range
        >
{};


} // namespace dispatch

namespace detail { namespace overlay
{

template<>
struct get_ring<detail::buffer::buffered_ring_collection_tag>
{
    template<typename MultiGeometry>
    static inline typename ring_type<MultiGeometry>::type const& apply(
                ring_identifier const& id,
                MultiGeometry const& multi_ring)
    {
        BOOST_GEOMETRY_ASSERT
            (
                id.multi_index >= 0
                && id.multi_index < int(boost::size(multi_ring))
            );
        return get_ring<ring_tag>::apply(id, multi_ring[id.multi_index]);
    }
};

}}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFERED_RING

/* buffered_ring.hpp
203hTciSEJlEFftJsUbxpu2gey9yryOQ9AwAivVHuRr878zoRhoGPzHHKkbI+BwI8eLRqSMGjmI0O7i9Gg7eCJZVX9zBuP2Jq4MnO6AechwOJml0Qq/4fqHdfB8P3VBIMRfGiYxYZJle1job7KUiPisIdNKevStXNsBzmn/J3pkrWHaY6QG7K96qJaBOIPpBkSumTrTqvrIrrk4M626UK/J2ZMtulSu22j/wbUhz1qSysUJ6p7SjSQkT1IZo9RkpPVK/r+K6hTVMK0sdMDPbolaJ3yhCZw3F7hNIH6LeV7HPaNXe/HuNYohULqSYT50n/o/4HUkQEthqRMvgLz9SciAponglsTOSaFjDoPI+zV2iq6QnMWC8nngpkQJBwqD4PjFkPJF4OJF0PM0YAPNM8qHYPdFbPJB4XKGaAgF5UqL4OHFSPIV4VqHO/B/zRCbx9D4GTWLreGfxkEJFf/EyBemy5kQwigJa5kSGwmIFRzlsImO//dDC5Vz2aAVTOVyXMtLT6BomgERSJSzIdWTSKPAn8fhi3+9CSUY+v/oidr2zt3mg2icDc8hTubRGnMRSCQ1wjcU/1iAftsnNvnhN/J5nsc7jJ5zgA1go6ULC6bkSTIXQ6wohnfa6XPcTVMTkJsWHE1pMva8Tojo55qONegQk8PtRtIy+5IbD9Iqp5pP/TMAYE9KALRShHuYmrfxGNyCXC8XpIIRqITj74+yCyFDA5clgPckCRkFoxwklwijyo0tJsUJJ8gNmjcwbzKi80AzUGy7VpisBkiNRwRH/RCVNjxuh1o2rHVW6qwBXQHpKJVRNsYDAMoKDUuql1E6sOe0a4lpZR/8Vsm2rCvZ3KnYMZyPOVJABLsla6Js7OndUz1W/1pKtpmVNxR6LOjFxfOj7Of/j8M9/xvzh0Y0rG5fWF3084sD43uHPtfLd+d/sxtvGNzRPNN3BlgPOh6237U8AbzLd4ZgTUj9Sk9uGN7dPIG/6nkTd6Zr9lQfst6lPFW/OngRZVDPof6DBQIp+Qb6g3hakdsGvB9QQCIFQRv6u/PF/pGP/jqId+v2gQY+DTAGVy2mWUjKhpENRB1LliZ2SwaCNB2L2W+l31yqokVqhOEMxCx8TJI9qH1JDoRWFzguvERwRrL7dfyTrHivhq/+xDKXpI8PbF8ej8FO3EbgSQ+5E3HNuJcWD2k4F3FaFctyE+S6aMqJTlxItZmWMTwNh1OilCniz8msrRCwGibEj8YTEjANyVBVKHKhsQsKQRG+UHXQIWgsPSBvXR22gUI+qZEFDdaCCTsV1cabjxPNkhDcpC98atDG17Mf5O4skm1oAIhflmZrHIcM4GcuSAsh4OPoU3CYOlEW1m+zH0Ny7OetaTMc4zaWbHZnSP3GMejfuBtupEkrf7umYiqqaGsOWGoaTGiCB8cWC4eKFYW+JcaGHcfQPYweJPylXfJZmNrBOOHbMDUowCJKu+g0h7fwPgxNEkzAMhrIoxpJYqGRaPpB8WinevlxJKAkL6sPgNIKb0T6KfXOrmBbc+TyURT70+V+gJggAJzFgZjKwG1sQ2xJ/F01f1o6Al+GAlmM/FxU/VoFk1ZJFMelRc8TDxmyEIKQ/FROiRbtBU6XA5gEa9X/iPQJ4Sfwk0HxplgPgnPeZisldcxhdc2C4aDPUQThWe61AdReIJ/8eOBID9U7Mh+Lkp5YSYYWx+EPhGQPiHU1DmQwFkB7VSagp7wpe7QoGWw02G3rUC65B5ma9Ifxc/NEY6woFDL8ZvQPDl9g3EtikPVh01GDLwsFaQeEaxfwUHZYGvCHfT3bE/mOhz6WdzS476Ai6E3ZQ5HeC8kDRZ7vuqtTN4xrN/CpF5yrJ8SoO6SqG/BpM4goK5HMLIisGgD+Kngh13vvNCbIuAKbWXTCriUEuhWQCBR1oHJvR5Lu1IFRMkD2qfkgZ77dlGhEudJQPJl8BgXwRPjVEUFfBxodDKoN8EhrxF4rJ/1yR/4iab2mLf+iAv+mBr6iCL2mDOD23G2JxGXmRGXCRCX+xAW5RIa6FWT9cObYJEbjuj+SDSFxsinE+0OjguTz0oQ7TJsrJ3nRuGkOo6RpCzzg/qSY/qVPasRQimREAI55JaeQaSAMhAddfHzKwLsu/HJAg30gj7yfV17w1Pjo/nb/n/If3k6cH1UK/z+McqGAk2M/FJhEiTpKeC+E5uTFxplSQUeEggT4PAmqnpjiOcgrgRTqUym3DQo4gCfHDcrlS9oU/LQTtcdujUkn+R3TN8BJ0g0LhPsi1aeFRNt00aLRxP4KC7UviS0dnOWoKWR4nNedPyvA5TGpizyyieuxh7WBk8k+gntJj8sp5paWzaDU+z3+/KycWSw7qj5cqXKDka2y5i0v5d5KrlR6VnRiUu2rGmbA78c8pfQrWVD3CP599lNgGlmkZEFaEvQ7VCmxlO1JL07z36v7m5fm52pbCmsV0n1/3eT8Y+bUiYpGBc3+cUwAOqHRbv1bSsnbd9Y2Keas11WynDNyDtuQbe+vH3UclWlnP5n532ZFMG+2L3aUv96Aj70kB0UOy5EzlBJv8u7g0aqmZejqtuGDhnaTVQjudqY0KDY8MVWAJiS2qb9PfgaNsNnH4WM/X1Ev0FC83M0unD9/rFQpDObgGFpIfUEIm79LPJ+dWQiJHueTr+0v6Yt+D+Xw2p8fiU3WXiIgYRSw4YV1wksljfsZxFXB9trrUjMK4sW/9crWh6a3rKqJi7NnFBqzoxvr9Nra/cyV1ovSxCk27trT6HHad08pQ6Ho4FBUAlQ8Gh8vrcgv4+RwS5k1hw/nS6VQvF9Gwo9+Uf3w3PJIzfy0bFz5TbYmzURdrlr1zIKgpFS79fAK1FIb9ogW/1c5j5LZ7q5uc9bxEXcNFu9il3txobUe7luU07EHb+fEnAv/5dGvVT9I5a43BQvd8ISvmGWZB8/CFxpGm67H7otkevqTHp7RhwuAim284KRiWOumOUwvnigd7s2VBbeXB3U6h/3HNHvB5qdsQrSPnHFuX/mfpTdFRuVeBvE1yp6DoBkXRvFBwqeD83agL9qW6PN54aUfnUcG9Yom9757FoNzSP6yizFyObDFvFAXTxyuGbMxd1/sKaQ8f15xcMdX/E50GCpvxXDLPs9iCwOk1T6AvVmkaTNEtNECNfRIn0ertyOindNbmRIOcuryDf21dTQAziBs7Tb5JPqaGW25JiMNhVXMbCfVTCDdtYmehTHB2l4uOYhPgSVUDTlonr19HhB4xghWK9C3mfL4otXy5mPlBlyYt/LkThufz2y95rg4y7HyhjYeT1HpJ82nRLitZ+3Wj1jT7rvSoJlaZZI77Q4jtcnukxCWSrbbMrDdtaabYphfKsnEEv3LAxcI9Rm3WzcdvDuXkk++L9KHKNN0agtclmvMj5W96hXX2dje9sAXTjPkbBPcTJqdbQ9THoQzTq/EdYqLYFGiM7tvQgZPFhltSjkz9QBlsAyM4nB2xx+dPIzy5F8Ze541n6tjP+QDjj+ZVQ28sylXMp8tVRxBIELjI2Efve4t351YP6U71YeoYDWeJIUdOS9Pbk52mbqJbxWz+y2r47cwYQctY18eSXBEh7/V27d4wZM8bd9c0J+kIj1U9runnRcQCobWstTUEjY41994Qw7a8e9DYBcBMs/ckRAr5xnPRYZkWPn2p+2bXxrfqR42eO+rUKhu1T0NbhcwPOrbNG+QVKdbS891p23Se4003r2kYLhRBAV6Nx6WiNKfGtyRfcJ99Q6AHdUqUy+JXXr3eRueTjp+pzmNK0jpRjNniPxnNlGbnxWQ354CAmqOJ4635O4PqRzVxnJ493bNGdTn5u8RTtzfl697nJFIbnPR6BdeQdku/O/4Fr+QTAkqZ1k8GpQfBmYMOUqvFTlHGmHXFqscDoXEUDETWwq+pKyWE4EeUbwKfF1aagjjf/A52VwQoIcJ29tdcWh6KCLyi2zu3ueQ53WLZvdNNW2PleFHnpCfoO0J0UBzu8R1bJYSFeV46qLBEi14RkH7HSgcRJ15NGggfRxaxPp/zo0mbfZZjK7HqabUtftUsW5n7G9qsPvKrJwjYZHyWvHPCrsCcCnxx4kMWdFIqHU4gRxtNRmT7A4eEYHOhU/xOw+VUxZy8dtK1ISvL5Kbyvat08AdaOEiVHrdAdRzn+i2DUt65SxSE5Yu5tD9ZLhZul7OvqO6mOTidHrdj1sNrbV0VPknMeHfdjpmcqyzX8pt7Fo4UhC4zFfZH5AMr50Ra+S7bz9GwOXSCI96R0q41+SWdlcD+GRqO5lnBDxHIaGiBjT6TPPlVrPdLSLTUdyQ1H+7o7zSwA1RuXfchNXWtLrVe6zbj395raCoywLaY+JwP5DSG+2mHwGHkCxuDQ8gtU6QiGjRc66Oz55wva1bANevJuGbhQ1CkZ3PrxCeyEpEBX1v10SGjUBSRQpLLzFnkzFa5w7lCTXaxFDG0DMylVXpjgEs4DYrUj4lRqNg+H3/pyb91SN8LvCWyZu8gIqHiODtAB8g3d+4tFeYaarZXgGFc3hogYVL41jpDS9lbEe6SQFPvicVRN/yGhcAZPo1g2q6EAu4mM1hnGNBkooMTUE2QUc9G6F7w4ShMwqgSWQyeq5yHgpVhgIwo/sjlcThgAkUJ6jJi4Njb72e8+wXeIZ5UvFNz334Zz8nbGncXsfMM8rIRjdJ+WqoUzal69Wf21oaaeSIwKGm12/TYyjJ5l8QhBWn2gtZfCfgLGHnnwZB22HbhDL02c9INwHaT45W81mvnffpFqR2vvCv/CH/9qEi/lHCLX1s3nuqvhjmNkQ29znooEm651TBHIzVVsHY+res9TWxcgXPiUDY/GIBOUDKxsBh7MZweJcklbr8odJt+LVYB48yc2migyfNME7k0mOStlOtohCnmSxVbMUNSp2qwXm6n4jLeXrSZvLj8m0wG494R0EzZLsk+3sRw2joVuVsmZuWoB+GXzSam2axbrNjaU70a6MiyugHjaLFVb/4a7wvfib6SIrvCnLe098hBRAaBzg72iu1ebqtyMt0q6TZm72M1JPwuNBdey6c3T/lOfVrX/up9C+VfkBqoUXUDq5mTdSUUq2bQ1Dh+Lh3jnfFhyHiaoNjLjJrwrJ8W7uGsvd/SxQe7wqT7aqoymsmosWhHEDHKNnCIeqcoTKRKW5Z42iekMThBYHetX1rRIlnPwSBm/RsU6mUa3mzTPC4IBdqQsNKbGx63WerxTsKpEM95SY71pTwHIddCm18uMMf4ybnwrS5RGH7svPDAdxgj1XHW5v0SWOXhJLYqPebTidWW+1NRAch8Q1PQhO3Cq83W6LX5tmRZ3VIG6/W2e189FVpdXdQ5PDdLjiFIAduvuCJa4jfOhRiA+J22X8zxbE4+3qXM4xl+2FIhGt1ULUNnF8Zda7cTnIR6PPzYMRHsU77Umm53EkXK62OchlllgVhD8vEyjK7ojMecfYLqoLJ8YXKA9tAfcbFRe2iQUJmIZ2J6h0oN+MWim015xXvzUHXFrnLVLEwoChepy5okj4eJK3fKM3wyxC3BPKVrndOj98TiUdw6LDO1MdbhYrBQyMxy8eKT7mnDNTE+cjeXs4pYYvq1pCMn+q2sLN/RHiO2nrE8vjnC9lGc/z075HYTnKPZ7mw86sfNnboia711F7mBtXbiK/ueYOhoIctL4dzpsrdf+/weHt1lnSA0wSzAUn+Scd1qt5p4kJLhxfGZ1RvITnwom/U16UQm3wVOdn1BG84J6dE6MlngyHf/AHtyMYJ44i23Cf3TgqLq6zoOxBZKJka4T9ddA6Qk3q1arxtJxUYgUedVpxVH2C94cvA8qkLemo8PssJsYmIWyjvATEE0SWvx/ZJDjcky3m70cIT5RzNvAIJe/oUKZduh5+z2Z/r2/qbwtWqsFZOzugTPkKcs5/7a+KEtLwIaloH3yFYn8Y7UFO7KfVKhMRCr83B/NJV/SSTd3EWQwdnesQGdhMm688Wfc7tEpPSDoK37+orOuUxddrua6Wfqy5HZ5ZL6XY7bwyT/YekvK/i269Mf8VQOg36Gmn/jgQ8dBuaSwWXDOastrnNlGz5lSXD/JuHctJJJkdb04juw8VSYTCe7WNIc4LA5ljX+uW7Mbq139COplGRQV3KTM3uaNO19DRw9TOM9s7XynUZvgm1njb1znSp8ND4dT+BxvLioXz7R234NE7tU6B4PdXqu3ciGjOCCycMmVwJyRriw0/J4W/k3u45T/rMmNX1qCly9AEvmLEdvEKl6pRjK0RPa/nl8MCpU4BdEOKzcoSwd8SnN/Y6b0x6rDofCYtq9WUr+VGe8zJi1UPyKnWk+Y9cxo0j3J7kw99MHB9UADZoUiC0giKJt8Shtt8TTwYzVqrV4ymRsgmy4wH2iRsNSI2DkTqD1x8ZCRLnz6qibgyKpCSuC4SiYFWPiMlWLVq8Xb4Gf3clCObsRjYQyoASCrdBkohMV/Bkw0yuEoXIXe9HUkz9DM/g2/v5aeh3piHbEGsIZukj2+WGi+QePI1kNcs3h1fGkhj3vbjjhU1Of43t4QTrXO/CKSFmzeZN/IC+RJ+rNd4NtbjkRo2zOS6UVa9h5WA1se1k6Kyl5DBdqG7XplWst4Ghr3fLyZeIZb8yRRqPJsWhXVS0Y1+CzXmdd+d7wTN2VDBulUrWRhYawzOayRejBvOOtSHrPye104lk+48HjE13cLL1oWF3XvgyZQKrQUckv+8miiiv2co2iq6NMp4EzWkaLpplRsyZUwYypwRxtT+91+8hkugwqPyB43RSKG3lQaSpoe3nx1EpwsdW8/9cyLPQQbcbQ5I4Bd0aWHviriNn1s5gZmNWqzC5C+n6cRuuje/ftnbdYFc6eM+v0uKdHlnbl6NHP4EUcW4G6fugCzMykTD1bs2fA/gqVK84dIr/PGxUKlJr7p0cJwOe+Le+i2Gx6nsDo1nq/Scn+6ppV5+/YlfsK8gr/VsyzIIk2qYJ9bYfw+9hMI6nTpgebV8ex4P5VkCqYf9Bo0wb5+quZUZZh5u3DyWUH90C3NV+/akwcPIgnE2x08skqVMybzmRZGAoVHzpq2scmO0+zn0dj3uEnvrUfIS9GS4crT0F1eSMLCmwHs/OX5xdxjUcauK6ke7zdG4Wq0/DyHPyORnXbIj2j06ov73KaffQ6kbo+GgWPIilumhz3+K1/8MPSLh1nsQqUd+vSk53IU2WVs9XHkDl/ialJGR6m0haXudLFR2yed5HsvPceT2uJC9HPMWRHDDqHrTLqOly5HZemlSup06lRxOHSWZdtiViLrvsni0/zuPkEKmxCCtM3x0nQ3oHkzYvm5cwS1tFabfOT9MZaMtlzeGjF84c66hC1rbTEU31GSWb2de1chXIqoj3nG8vPU1jk8yxlxuViaG6LoS7d9aG62Twpbj1sBtW2zWO5p2a+hGxiaf4cM/65K0ERMEiXtk27/M8Ca623A3hVRpi06PsWdaXpypcPFMZqC6GFq+0QKS/a9MAbyPS+9Edfb+rYZnZByghJTlXlk+efo1XI+5vcnFRBk/S6SEvOualRs4u0RjaCERjoKV27t34CDd2f2XrIDhNVMWZSYqp2qbZ2yWYyKtY2of30L90qcyy3BbL/fZJj
*/