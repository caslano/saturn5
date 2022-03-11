// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2013, 2014, 2017, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_COVERED_BY_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_COVERED_BY_IMPLEMENTATION_HPP

#include <cstddef>
#include <boost/core/ignore_unused.hpp>
#include <boost/geometry/algorithms/detail/covered_by/interface.hpp>
#include <boost/geometry/algorithms/detail/within/implementation.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace covered_by {

struct use_point_in_geometry
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        return detail::within::covered_by_point_geometry(geometry1, geometry2, strategy);
    }
};

struct use_relate
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        typedef typename detail::de9im::static_mask_covered_by_type
            <
                Geometry1, Geometry2
            >::type covered_by_mask;
        return geometry::relate(geometry1, geometry2, covered_by_mask(), strategy);
    }
};

}} // namespace detail::covered_by
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Point, typename Box>
struct covered_by<Point, Box, point_tag, box_tag>
{
    template <typename Strategy>
    static inline bool apply(Point const& point, Box const& box, Strategy const& strategy)
    {
        ::boost::ignore_unused(strategy);
        return strategy.apply(point, box);
    }
};

template <typename Box1, typename Box2>
struct covered_by<Box1, Box2, box_tag, box_tag>
{
    template <typename Strategy>
    static inline bool apply(Box1 const& box1, Box2 const& box2, Strategy const& strategy)
    {
        assert_dimension_equal<Box1, Box2>();
        ::boost::ignore_unused(strategy);
        return strategy.apply(box1, box2);
    }
};


// P/P

template <typename Point1, typename Point2>
struct covered_by<Point1, Point2, point_tag, point_tag>
    : public detail::covered_by::use_point_in_geometry
{};

template <typename Point, typename MultiPoint>
struct covered_by<Point, MultiPoint, point_tag, multi_point_tag>
    : public detail::covered_by::use_point_in_geometry
{};

template <typename MultiPoint, typename Point>
struct covered_by<MultiPoint, Point, multi_point_tag, point_tag>
    : public detail::within::multi_point_point
{};

template <typename MultiPoint1, typename MultiPoint2>
struct covered_by<MultiPoint1, MultiPoint2, multi_point_tag, multi_point_tag>
    : public detail::within::multi_point_multi_point
{};

// P/L

template <typename Point, typename Segment>
struct covered_by<Point, Segment, point_tag, segment_tag>
    : public detail::covered_by::use_point_in_geometry
{};

template <typename Point, typename Linestring>
struct covered_by<Point, Linestring, point_tag, linestring_tag>
    : public detail::covered_by::use_point_in_geometry
{};

template <typename Point, typename MultiLinestring>
struct covered_by<Point, MultiLinestring, point_tag, multi_linestring_tag>
    : public detail::covered_by::use_point_in_geometry
{};

template <typename MultiPoint, typename Segment>
struct covered_by<MultiPoint, Segment, multi_point_tag, segment_tag>
    : public detail::within::multi_point_single_geometry<false>
{};

template <typename MultiPoint, typename Linestring>
struct covered_by<MultiPoint, Linestring, multi_point_tag, linestring_tag>
    : public detail::within::multi_point_single_geometry<false>
{};

template <typename MultiPoint, typename MultiLinestring>
struct covered_by<MultiPoint, MultiLinestring, multi_point_tag, multi_linestring_tag>
    : public detail::within::multi_point_multi_geometry<false>
{};

// P/A

template <typename Point, typename Ring>
struct covered_by<Point, Ring, point_tag, ring_tag>
    : public detail::covered_by::use_point_in_geometry
{};

template <typename Point, typename Polygon>
struct covered_by<Point, Polygon, point_tag, polygon_tag>
    : public detail::covered_by::use_point_in_geometry
{};

template <typename Point, typename MultiPolygon>
struct covered_by<Point, MultiPolygon, point_tag, multi_polygon_tag>
    : public detail::covered_by::use_point_in_geometry
{};

template <typename MultiPoint, typename Ring>
struct covered_by<MultiPoint, Ring, multi_point_tag, ring_tag>
    : public detail::within::multi_point_single_geometry<false>
{};

template <typename MultiPoint, typename Polygon>
struct covered_by<MultiPoint, Polygon, multi_point_tag, polygon_tag>
    : public detail::within::multi_point_single_geometry<false>
{};

template <typename MultiPoint, typename MultiPolygon>
struct covered_by<MultiPoint, MultiPolygon, multi_point_tag, multi_polygon_tag>
    : public detail::within::multi_point_multi_geometry<false>
{};

// L/L

template <typename Linestring1, typename Linestring2>
struct covered_by<Linestring1, Linestring2, linestring_tag, linestring_tag>
    : public detail::covered_by::use_relate
{};

template <typename Linestring, typename MultiLinestring>
struct covered_by<Linestring, MultiLinestring, linestring_tag, multi_linestring_tag>
    : public detail::covered_by::use_relate
{};

template <typename MultiLinestring, typename Linestring>
struct covered_by<MultiLinestring, Linestring, multi_linestring_tag, linestring_tag>
    : public detail::covered_by::use_relate
{};

template <typename MultiLinestring1, typename MultiLinestring2>
struct covered_by<MultiLinestring1, MultiLinestring2, multi_linestring_tag, multi_linestring_tag>
    : public detail::covered_by::use_relate
{};

// L/A

template <typename Linestring, typename Ring>
struct covered_by<Linestring, Ring, linestring_tag, ring_tag>
    : public detail::covered_by::use_relate
{};

template <typename MultiLinestring, typename Ring>
struct covered_by<MultiLinestring, Ring, multi_linestring_tag, ring_tag>
    : public detail::covered_by::use_relate
{};

template <typename Linestring, typename Polygon>
struct covered_by<Linestring, Polygon, linestring_tag, polygon_tag>
    : public detail::covered_by::use_relate
{};

template <typename MultiLinestring, typename Polygon>
struct covered_by<MultiLinestring, Polygon, multi_linestring_tag, polygon_tag>
    : public detail::covered_by::use_relate
{};

template <typename Linestring, typename MultiPolygon>
struct covered_by<Linestring, MultiPolygon, linestring_tag, multi_polygon_tag>
    : public detail::covered_by::use_relate
{};

template <typename MultiLinestring, typename MultiPolygon>
struct covered_by<MultiLinestring, MultiPolygon, multi_linestring_tag, multi_polygon_tag>
    : public detail::covered_by::use_relate
{};

// A/A

template <typename Ring1, typename Ring2>
struct covered_by<Ring1, Ring2, ring_tag, ring_tag>
    : public detail::covered_by::use_relate
{};

template <typename Ring, typename Polygon>
struct covered_by<Ring, Polygon, ring_tag, polygon_tag>
    : public detail::covered_by::use_relate
{};

template <typename Polygon, typename Ring>
struct covered_by<Polygon, Ring, polygon_tag, ring_tag>
    : public detail::covered_by::use_relate
{};

template <typename Polygon1, typename Polygon2>
struct covered_by<Polygon1, Polygon2, polygon_tag, polygon_tag>
    : public detail::covered_by::use_relate
{};

template <typename Ring, typename MultiPolygon>
struct covered_by<Ring, MultiPolygon, ring_tag, multi_polygon_tag>
    : public detail::covered_by::use_relate
{};

template <typename MultiPolygon, typename Ring>
struct covered_by<MultiPolygon, Ring, multi_polygon_tag, ring_tag>
    : public detail::covered_by::use_relate
{};

template <typename Polygon, typename MultiPolygon>
struct covered_by<Polygon, MultiPolygon, polygon_tag, multi_polygon_tag>
    : public detail::covered_by::use_relate
{};

template <typename MultiPolygon, typename Polygon>
struct covered_by<MultiPolygon, Polygon, multi_polygon_tag, polygon_tag>
    : public detail::covered_by::use_relate
{};

template <typename MultiPolygon1, typename MultiPolygon2>
struct covered_by<MultiPolygon1, MultiPolygon2, multi_polygon_tag, multi_polygon_tag>
    : public detail::covered_by::use_relate
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_COVERED_BY_IMPLEMENTATION_HPP

/* implementation.hpp
Ur5GaitmIhz8Q7184RE+qzyJXBQM2QwwfVTs6awAe6+uHnApF2kea+PW5lxS3mJYsjs/xiuZl1wHoiV6ESMQtogXZtma3y5VyhATAK4UC3jK54wUSvcHKHlN0zM/sTgfcTSqRckogbx6WbjOHCNMMEozY6LF4BDevIv0OzHVXAMJDQ1zxW9NX4puvYc5GK0D6BUX7NkD4PRfMBkgJm1jR0hK783ZraciJCf5Ll+HopgATi5ZnOCquicQsfwC4OvA8NgpGGSad0iCCcwf1JcnAIU5cOGg6WmKdqYlWtJoo6Hjet0E3qMH+fayhfKwETD2mozZNbltkX1zwqM7QXVcPVJ7B2GUetOjIRnmuCGQH8PMv5zRLZN/6bhk8aBU5UZszy6TQgzOdRJ8Jk54/zbPDXtoAMFH+LXTZZpMjIZl96704947YmzrhLYBPzQh6JRZX//hAdVcPSL6Bxa3JjrCe2FzfFcJ11CSLTEAYYbek4LXRUGmH1emqvACya3tX3/H3khmbatzOqdIW8oMdngd08/4Z/OFQusiwCD+nJCep680dHlwzF8xLt+TxKkw90PUmQz7BAibjavMMTR033DGqMp4TEihfIln/XAZaYg1aPXNW6QK5Yow5cExhyU1iPweN19BaeyTyIWRtXFFCgX8sHJoO7694ym291avMMjGHjiAiC8t8Jgj1C3Bv6YJ/AKvrcNhJ4LM/vVa8xRkfS4QjxkftD7oQ+CpmCkf51bV3lvRdJIa2qgyL3jyyKq1/EGVI467ivOTBPaYC87ZBM9MfkmToj6MSk4eLPFKpKIDw0TgAGnroQn1Mopgc6FQh98OmZuwr29ockTFaKX2veKboLx//zm0WKGBTGdv202mQnREnZoNFFgCS324ygDtmnOaFtFpCF2DDzrg0yM4luA6GmreyENq5jcqS7h0H7xvtV6Eb57PbIw5Z0TpnsWqrZ8kYXbOK/huO6i0tC0cJ7BsHduBA9zS2kDAEHoXB10wlYWBDVspqbkjuoIs1xQuvB5DuFgwRCp4fXXUrmi1AAAs/9MbJGGz2m1LuIwDhqFlJTpfo4sx4AHcPhG4A8jSXzgbTeFq74nZfwFxBo5K2WsZb9lVuqvJw4/9VaF/k7ytG9i73kua9iyC1g1zLzL1unJ8jD+JOaOK73WfEnqgHaW6K+6Qq5aZNhJ6mD5ZlzfZ1Xel448ye8U6hz5/MPaafghw3wlg3Fup1twE4CLPOUucwWiFovXI+Qh3KaeZGW4pgrB+3jVnOTCGjiau7iVkgaT0qhtdg3qEe1qLeor2Qs/bvrP0vWxIWHZU1NObc3iScmlEvecG57icUs11nRZxMpXAfmdsfD1fOt1WKqmu4aHxRlydsq2KGvS3NEeM9j3wDwxO6x4Ds+nR3r89wWD/GqOsL+KUxRSGoVSJx5QR1brM2NQF2hdRwisD6/pUMkYaFhthQTW2LLxh9XBtBQXX4oRUib9Gf62SSKw/be1oPXNZxkU4WB07ENcLXmkaEc74pPi4QEUicr99OESNVM5P8JjIub/t1MBfSX3J7wU+ErHEiZtF3SIblmz07CQ/DwQInjfOLydoaou94MgfLQw2JrvkJJhvZQ7NXyumR8nCdFk3Wr7U0LdgmRWYdoNW1CKwnh7VUBYCFD8idDp/PHe7Te2dCk+szk6JazGLNSlOhcBaiemKhhitpCFpdUslwoFWdNhCSOgHPUWgvVAE3TlcRLrkXY+vqAKCBl2Wr5vyUxlEGRsVykAii0z+uO2EaCF9CbKRgRux16/GJS5LRymA+n4tSoTBSpLzjwtNe3lDmc/75qr0G0MOd6/1I7IJ9c+MXKfMW4UiRFnbm4go7//AD1Z2+3r1zHAjQBpIxqABY7c7Ku7+clbgBvtD8VdjNexmxxlF1vFOQTGqL1DE51JTpBKGz8s9fED6KfMCsTc7IVsWGUjpkjUZF3nzX3ewBGyvHMIjPyZGbX0IK50XEqIZFPEXx73QeGwWYfqiFedBGyudTGrws1pAGHFzDxdJRx/YjyNOlj/r6eVAHwo6qw0ubT94/oz1NvZojCgteIyoMqJX8PQ0M+IRBBemn8nQ2h9T8aWx3ql/EDUR7gahtQq7E+HAK6jBfmTVUnrj7jR7+Yn4cR688880oSxCYNkxyqpW+eXdT8nVcF8ZPZewCWxJGaTqpsq1BiRXkmrDZT9juAQFvHBXNCs7gVJVLY1DeBFjZflS25EZwKWYcLeebwA1WiGfNZKYeksH7osIfyKP6PJ0VrkYnOzRhcRWQMWtcqZ53WhB3XW85x2eid9NuFP2oh0Ep8YEoim8DSCWKOc1uPXaSSQl4vYPN3AvvjAUuT9xc0QnsUvYxex3Zd84UW1gL+WOPP23o/f/mms2YymKbsufPAupuLm4MQRFR+ai10bH8hJ9/YH0l5NdKmvOk3h2uUZ2j/X2LG/pLbeF0tBVJ+T0I3anPJnSnzq6goLsLYUcH9DaxQKvTpMgoTRsVYaqrJX7M+0toufWxe4slcHLjkzbHArAyN3SPe1Cwkj1XdlogcUdRv4PAzp2XEwiNOGCuxNNJXKxGqrae4TqlQe0xOTfH6Cj2Vrz4GdlzXdpcinktz1Fi0DmIxVmKxXpJOe+fkpWR+Oz7pOpRVll4Nvg53LVt7Ei+aQe0AezUsMI8mrVGEWT4ddpGa829s6wpo4Qqf4bpJ42r/AuIYVDxbDBBHhGbkf/MamXRq4C4zdy26OIdYPV447zk37l7xuX+xKsszWG7Omba6d31gSknnIMtlWRq4ujzuU8dxrbQttO5kT2OU0USMyQqDe7WOt7K8oxajb6XnHELG25dBqCdWHCZGHgxqiVd6juTlNuA63YPRobMIddmq5DGhULJJxRz4r0R4IHZGNv0ezJYDSWCcWL2bGTEEmaZVEJuy/Ry7xqJ3bNWJla6o+YhdUKfCY44SE1vL/1bDig1z7MyXAydQqrDxW5Cc2Gt8P8YDI3AsxdHCpcfMVO+yB8Dg0YZo9p9/Vdl3lmBY3Bf7IaOS0L/kJRKxkIqT+nuAqqkH6XF/uflWwz9L1+I0x9H4qie9NVzwelmVvl6ydxKrngXocigK7BGmwfGTewclbl7GqWh2iyqm73fvZo9eSupnEQT37u8AEdOoVoNGEZGaW8oJ1KhdgNUWqC025xFvR3oLtm63LuGtHZnMp7UakWdOkrEtDCX7JZ8G3j/sBOtixjN6oNWLuVn1P2RRd8MKH6H56WvnAupt5+2460AOj6foCIL3AFaKw0aHWoz7sBXRZ84Zg3oerhEZErCDxuCmo2XiqoDWSAwK3khuhoMHC7RJFAQSA60w0NooJPJMA2jRTa3kMHDncV0vU6kCTeprIJ6IZWr7qEGkrQ5axHS+KUOM/4S9aZM+drHzzs9O7Mjdbw+s6aC7cOD43acXrwbDO8J8sODeSzZjmMlahve0Z24PBEdZCRJqMM0CZR5tQWCEHC2NeGZLzPIi7UvF2P5fLiKu0IhDAxGpxskn7emCs3YljFdngzSzIxEFQXANdbXDXvQh5cfwqDlk0o7anJKUvVmWkatOHwBIhpSg0aVG8GoE0aMq5g9+H5k1zQt57zcOsljW1WTq4wrYipg1gg/oyrEwkkYdfqU/rCFFTfEOrpWOnVkwuRxuzLw5mjVx3Fjb+zOZHLfBXkx+ZCDouEKOHg3uEt3KIDjNaUmL1MZxvv/NtaEuKZtygmOhjN9kR+o65yB6PYZkotpeGxm/bTReNsYLkxIEUIjDloHrPcJMXA3tjwpVSjX2ivgIKJ+e5OUg610SpDSLzB+av4hN4GVOjqH/BlpQ0fiK3nKUpU0I2PwZHAG6kzoNDQO0WUbw8EQUkMXrDu7pp3hKb1A+mUK5w3b7/1t36NbFKZLAHhrLsDf60Bp6QD38VM1K8DNpl1y4A5ZEJ91T5BGt9ySad0JCG4XsqhcXAzk2kdCDTpHXBXEpT52GmLQ6TSfoSqawcs9wmNF3jRy7OF+WrCVrb5rvhafvZocdKTKAsj7kdWEtGfMK5qcxURVFVwxqed5F0DxLT9C+YsjFsaYQoUdL4X3+Qqw8yHkCjBSqK3Ojrs+4OzNeII9Nx802JP2yXDn3SUg+iW6AzOhGps6GnnKcgGPMi63iuE/5nGC5s+nkQIp65kN4q824alJWPF9Z8xlZUkZxlrA1eXz0cXPqFvsj9Ceji/6qYEnJgbIpg8Ihh5RhkEW0j47XGRPuKi+/eu7mi/kowHIQNkQQmh3+ixpaE219lWJxjJeykVDlR9viX/xrBuT6A8JitBAKRNjjEOdMHcMx2thTnXR722M9h2l4ouAFZyrJ9FOBGMA5fyYBXAPu/oMl4AT4jTfI5r/OyDGp8cwupiYigoCYSa2gM//6TKKkb1fsM8qZACcfK+64iz+woPx6ctAv29tA+E/uX5FBaA6Hc5GDrNM0Rv6Vjh3GrmvYirNn6aS39t2eYzrEyZ7jX6fNqG+oydxY9DdE1SfTW2HKZjAdUKhuU95QRyu2WoGHT/zTvans5NPpAH609pGxPliYaT4FFraB77TyRTZiHH0Ucu1M20OPJzrZMxEPjewWIK+P7X26g0qg1myAStJwYs7uzIPVosYsOeUhu81yVaNXYQyGLpQ+jz0hAzJWSVaE8UwIzx35RTZUBAghQcqTzw8TA70HuOeWO0ziOwKfo2RSYERggdMAxGAATf8QWt28tc8et5Jggok21yH3gleFNB+k4EYKiwIOyQn6ogj0femWhRJ14UsVfWlaF5jiQLHhxlknwD0Xd59ROE8Iq54FFFoB9A7J1H8fRd94j66OgL/9mKbwixHlrhHktnq66r8HpUiWrt1gezbLREOJPGJVvjHG1FAH2wN9HAd4MkfHd1uSTsf76GVgIVdszjiaQdj3XolqbZ4Syw2+UuF4j/PC4DfAtGsPoaUVOxrKwA5/j5jhJmwdL1eHfdbmg99kzc+jq0WJ6MmCINHjsQY7Ww/hrEfgiajU6JKVCiaWVY9fDaojWaNNFdaROd7J/pNVEpVOCnsFC+d9vZEb8v07/4EfduTiA6yqV7Ak9+Gc7gsw+ljglM8kDX1bBJDGymhQimerIYXEcJCaVmGL/0riA6JgT6sLTo3NlWRRext2nw+HLf40a0vYhDEdpNRpZUEdyEjBDc6/7uMXorsWwT/vn1OBJ9llVY6yTHw3Ia39FYhtcTKZM/apM8vFCOOcSTPN8/4KkZlD/j4NiOXz8/P/6dAAABvwJ/Bf0K/hXyK/RX2K/wXxG/In9F/Yr+FfMr9lfcr/hfCb8SfyX9Sv6V8iv1V9qv9F8ZvzJ/Zf3K/pXzK/dX3q/8XwW/Cn8V/Sr+VfKr9FfZr/JfFb8qf1X9qv5V86v2V92v+l8Nvxp/Nf1q/tXyq/VX26/2Xx2/On91/er+1fOr91ffr/5fA78Gfw39Gv418mv019iv8V8TvyZ/Tf2a/jXza/bX3K/5Xwu/Fn8t/Vr+tfJr9dfar/VfG782f2392v6182v3196v/V8Hvw5/Hf06/nXy6/TX2a/zXxe/Ln9d/br+dfPr9tfdr/tfD78efz39ev718uv119uv918fvz5/ff36/gXQ9Vv/3v3PlzXzcfEIONt3DoPrJp8v9rEuTlAb3Vez1SSN7+dX6saKl9Fkl+bA5o3tG++kjMzt/PKPHX3LawH9S7oK5nGx4OYPH1vvZk/ri2iq51L3z782NeRjUSkVlxUxhdSOp13f4c0aP+bj1I9v9YZZSGg7xwr1VMpd9wYp6kmqF10y6ksY8AGMHET0adXg9yGff8EjwvkGCI9KDVhASn9LIQtxLXuGbG/k3dheh4xLmLAjVTEK5QRzU0HUtvj8QxdfY8zlOykhwie48gzHqe7UsFH1OFCCwqFh+WBQlTCQhExiM/rlGUwYOr8/FO44E9uE0gsU7uKLyZU/nxbmSt1MF34AUWsexXL3h8UAUXfsTjFRaxQUHMZWp0vdYPvy7IZF+3l9XFdbq69lPWqllDuPwQv2WfiwUWvC1MM80T7llT+PVxRKW5+sYFFr2gApdRdIKI9VkkWdlxBECogU7jAFh4IerYfJdHJ/T4Gh9tC/+UaF4yT4MlMes2jy7A2XptYOvZfbK3d+VeBFhcP31k6p/oX4g2VFAZMMruTybgyEbrCbalV1R+uLBpgCKMM7uHe/3KOgFjO95gdmHpqs9sXe+Nl54Dl3X++NaJ6W3tdGj0Qj963FrvltosSuGS1cZuUDIKnCC1PkdSWoaQwxZf7oscfP7BGVyQR83j9XESxjFwNqHS5Aq/51wNZbnGIUgH99ehXXV7Fs9gwIsw7n2gEhFNSSdtbMuxPAoIF0ye+2udVlqU35WX4mJa72lN7NA8SazKqTvszlIS8DvzYim8euwq7Z9kGfdaamOYlPdbDaEVOMoJKzuEDDbmO9vMoruPBhLBDc7U+r7NKg4iuzIGjOVi9pHIBbyCuqPU38VFcnShzFnREumkKG+Jz7R5nDRpZelGv91eAfFUxnKnBQ7Dw5b1vRKiQh3EkzNnyQueQ+PUSXO+NSAWxzU2CIzUyT+h+j6Vo4VyIlngbWlkWiTBwIV2/CIfz5abfZOnGeqjCnual4MWP+h41EOv3espZdf+xQItoFIjqyPem8ZBw52Xmm2EMMxiyQs5nBVK2P2tuDlQZo0JXZ102YJCwh04eEcBzhejJTB6YR6yAv9SXKXayBCJYey9cU6J/hgT9nfk4e7Lh8cjdO/qAWU4e44uD61SLgwooj70kf7xB9V6fZfBU66Zda4WEA1kz2G1AbieSIoK9QMsz7uxv8Dq+1pe+Oq7VuMMde+vyvteQLuPD+I29XxF0ft5v2MYAYcRo6X6W8gicAndt1oHzvi9p6P6k4pjdKkunNbFy+ZC/7KWT5IXrwzi+X7psAyE7A3EauUIipAMglFuHwdijEcDlXsAtH72jngI3qihSJqKJCs8LdkLt6kdh6uCQg3NCw/onyeBlUyshgwf1+bve0gjtmr1c6jdE/vUY1lldk1KMXzeba0NlmMECLx4BeJlvT+HUag1fD4t1MXqTOA1na+fx2/B5POsUr9gXwT33wLxZ427dRQlnbCMhNZmJB5rRd8lDB+lAjAUEbBXSqHmaCD9dLbuEbZoJsbE6FZX26iZk6px4kRx3Ic9wyPxBgA48RZT6AHeNaeS/Q7AidjjCtrQeqmx3ofBCPyRHoCSUlCE1CXzYkcqqXSUWm7qC8wlK0aegEZzporjwyVsdXExIPhSG6G1R0gkSPXXv6gH9WDYkpvc+2WYuQl1bNriz8rVjOfE03/+EdqOFoqj5F1bjuj/RqWa+cZevcG/VGto9+O7XKOJC9qubWtfZovevQT5dgyypYKKrp362evXhAZbuW4ma7nhv+uGZiwGbk8rY/71oPZH66X5VqQKS6P1N/iUNhQIAGdHi4qBi6zHO4MySDWAyQbgc0Gihr4qQhLePKzK2yLvPrpLbwrOI/aSBK5ZzrcrTHGvLrKcvmVnIh1t8N4dSbraCc1xCQ76ju2h1ClmZEia2Nuaw3RpXMwDf4rUzpGDK37JfDudpMQtBUH4uPB1IvPRSO/yM705JDvqs3vmWmlMFDTMuX8KFl+WCuDl6D5bCqYz61Mdde4o9uSDocRh3x6Mt1qgOc/feSeKegKN5XI6YJ34/2sult3gEfoHGHoilKeT0SG8E3IPVEHK78AxKHxcHIqJ8879414Cbblei8IA0w7PM3n1q7o5Iwf8t/GxILAr1gwbpQpBUjOSNkpsi5HuKFO9kHB9BGtNkf8R9tu2ObTS4TREem9SUFzDxVsva01MpA/U4UNza9Y6OeaDztAt2GPUccUpvB3SLvCmrqfFitARjg1uj2mK2afk/kZz+Ys/hOXNBhY1soykKQrEeCpkjm4ZoIsK4HhEzHkiapvmlQjqDpS3spZDT9TIoF92Odnx7fVI0M88Puu0I72oF/95KO+Qh1HmC8AZkQmLWtWbMhD+GQGRuzd4ko/k4hp/s3aM1SHSRN9TYPihP1SChuLWw5FqrUtMuZua5FvBySRuV4j4HqGzvjb6iPChEqw4o+i+ZdjMkvJluXNyAZmnAnxYHRu7Yr3WqDHb9oQyOSHaYWM3ITtdYPvwut2RwhYjftlfE5eLZvOiQDNhhvDoYnLOsQC2NYfuy9SuFDuIgWaS8zwC6D4d7AKLstc/lMqkXHfhJ0g4ErbA1/fLaEcffUGbTYzQeo7DKaB4l0OR/njbpjqe+0oiZTaNz+iIFzGh8iER8piI9tcBN123SghVvNBrURp2JiNGsnkZo3artKn3inB4it9c2X4rcj2lOlze02bHPoUmSE4h3Xbg++12eZwgk34/gaHjStd9HBfFdjFn1Toy5JF6hw4ktAu8d3xTrPwndZvUhZoDf1EHo+wg7zT78CR7yjMwuPbYAVawwlgkqxKcRYC/X2FuYdS7QdPGXQVNiNqtHGms9jl1GiMHduULNsuSZbZR0GqGmJrb0KhgpFe6utwGdaOQ6sC66283FZ6LApPEhwZLJvFQrxfCC7k7VVoOmGa6B0dJ1WzZXflQV/4XR4VZ0nrM1DfEEH4L7XfFbLAKOtmA0bq5c+rK+DRyngSOQIfry7yM2Pe4eO1B9L0ao8JE1H6IxnXWnXVl/T7JFXOHbf3NW/5vbnWRvYhzHV68W6nytT6kpAtooJk1vbEgxrZ4/iSe0vMOc4ktNogbTwtyvTF5x6LIC+v/zE0dX1+0Isx++Zi357CQqTI4CKdkvZhZ0uCaxg8J0GraTEKQ4649ARN1fjQ/Fkfu5grr+0JiZ9FlZUxOaTdIDycp8aD7Xcj8d1owx2lACuFOi/v77/AVZN64pSEflv/keSN7RXwlGX73whSdAsiKY5pXMFE2VD1jP67SxooySwc3N6fDraUfOYdsrA9BnxHKcWbTFNJ2/hrvM5dyihbMmJWx8kLjaafWPoXwVSfDcDoZmB/uZybHNUr5+emxt3RyuHj5iZEgL3nZPf9e7ps3JjV5LJBUuBDjPq2IH9JYwrZBkPUTLi9SwOyHPupuTKQf+qp82Vm0CMJHYt1039dk/k1cZvlaC5wVt1xT+6iVCxVbJbtDNu8CCAif5qEsmu1EEHi6r5ehnK/n5E0mt9fOhDRWugf0tEFo5A65+a03Ie2y6cs5oNBqP7HBU=
*/