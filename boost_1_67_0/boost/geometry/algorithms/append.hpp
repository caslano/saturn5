// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_APPEND_HPP
#define BOOST_GEOMETRY_ALGORITHMS_APPEND_HPP


#include <boost/range.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/num_interior_rings.hpp>
#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/geometries/variant.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace append
{

template <typename Geometry, typename Point>
struct append_no_action
{
    static inline void apply(Geometry& , Point const& ,
                int = 0, int = 0)
    {
    }
};

template <typename Geometry, typename Point>
struct append_point
{
    static inline void apply(Geometry& geometry, Point const& point,
                int = 0, int = 0)
    {
        typename geometry::point_type<Geometry>::type copy;
        geometry::detail::conversion::convert_point_to_point(point, copy);
        traits::push_back<Geometry>::apply(geometry, copy);
    }
};


template <typename Geometry, typename Range>
struct append_range
{
    typedef typename boost::range_value<Range>::type point_type;

    static inline void apply(Geometry& geometry, Range const& range,
                int = 0, int = 0)
    {
        for (typename boost::range_iterator<Range const>::type
            it = boost::begin(range);
             it != boost::end(range);
             ++it)
        {
            append_point<Geometry, point_type>::apply(geometry, *it);
        }
    }
};


template <typename Polygon, typename Point>
struct point_to_polygon
{
    typedef typename ring_type<Polygon>::type ring_type;
    typedef typename ring_return_type<Polygon>::type exterior_ring_type;
    typedef typename interior_return_type<Polygon>::type interior_ring_range_type;

    static inline void apply(Polygon& polygon, Point const& point,
                int ring_index, int = 0)
    {
        if (ring_index == -1)
        {
            exterior_ring_type ext_ring = exterior_ring(polygon);
            append_point<ring_type, Point>::apply(
                        ext_ring, point);
        }
        else if (ring_index < int(num_interior_rings(polygon)))
        {
            interior_ring_range_type int_rings = interior_rings(polygon);
            append_point<ring_type, Point>::apply(
                        range::at(int_rings, ring_index), point);
        }
    }
};


template <typename Polygon, typename Range>
struct range_to_polygon
{
    typedef typename ring_type<Polygon>::type ring_type;
    typedef typename ring_return_type<Polygon>::type exterior_ring_type;
    typedef typename interior_return_type<Polygon>::type interior_ring_range_type;

    static inline void apply(Polygon& polygon, Range const& range,
                int ring_index, int = 0)
    {
        if (ring_index == -1)
        {
            exterior_ring_type ext_ring = exterior_ring(polygon);
            append_range<ring_type, Range>::apply(
                        ext_ring, range);
        }
        else if (ring_index < int(num_interior_rings(polygon)))
        {
            interior_ring_range_type int_rings = interior_rings(polygon);
            append_range<ring_type, Range>::apply(
                        range::at(int_rings, ring_index), range);
        }
    }
};


}} // namespace detail::append
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

namespace splitted_dispatch
{

template <typename Tag, typename Geometry, typename Point>
struct append_point
    : detail::append::append_no_action<Geometry, Point>
{};

template <typename Geometry, typename Point>
struct append_point<linestring_tag, Geometry, Point>
    : detail::append::append_point<Geometry, Point>
{};

template <typename Geometry, typename Point>
struct append_point<ring_tag, Geometry, Point>
    : detail::append::append_point<Geometry, Point>
{};


template <typename Polygon, typename Point>
struct append_point<polygon_tag, Polygon, Point>
        : detail::append::point_to_polygon<Polygon, Point>
{};


template <typename Tag, typename Geometry, typename Range>
struct append_range
    : detail::append::append_no_action<Geometry, Range>
{};

template <typename Geometry, typename Range>
struct append_range<linestring_tag, Geometry, Range>
    : detail::append::append_range<Geometry, Range>
{};

template <typename Geometry, typename Range>
struct append_range<ring_tag, Geometry, Range>
    : detail::append::append_range<Geometry, Range>
{};


template <typename Polygon, typename Range>
struct append_range<polygon_tag, Polygon, Range>
        : detail::append::range_to_polygon<Polygon, Range>
{};

} // namespace splitted_dispatch


// Default: append a range (or linestring or ring or whatever) to any geometry
template
<
    typename Geometry, typename RangeOrPoint,
    typename TagRangeOrPoint = typename tag<RangeOrPoint>::type
>
struct append
    : splitted_dispatch::append_range<typename tag<Geometry>::type, Geometry, RangeOrPoint>
{};

// Specialization for point to append a point to any geometry
template <typename Geometry, typename RangeOrPoint>
struct append<Geometry, RangeOrPoint, point_tag>
    : splitted_dispatch::append_point<typename tag<Geometry>::type, Geometry, RangeOrPoint>
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace append
{

template <typename MultiGeometry, typename RangeOrPoint>
struct append_to_multigeometry
{
    static inline void apply(MultiGeometry& multigeometry,
                             RangeOrPoint const& range_or_point,
                             int ring_index, int multi_index)
    {

        dispatch::append
            <
                typename boost::range_value<MultiGeometry>::type,
                RangeOrPoint
            >::apply(range::at(multigeometry, multi_index), range_or_point, ring_index);
    }
};

}} // namespace detail::append
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

namespace splitted_dispatch
{

template <typename Geometry, typename Point>
struct append_point<multi_point_tag, Geometry, Point>
    : detail::append::append_point<Geometry, Point>
{};

template <typename Geometry, typename Range>
struct append_range<multi_point_tag, Geometry, Range>
    : detail::append::append_range<Geometry, Range>
{};

template <typename MultiGeometry, typename RangeOrPoint>
struct append_point<multi_linestring_tag, MultiGeometry, RangeOrPoint>
    : detail::append::append_to_multigeometry<MultiGeometry, RangeOrPoint>
{};

template <typename MultiGeometry, typename RangeOrPoint>
struct append_range<multi_linestring_tag, MultiGeometry, RangeOrPoint>
    : detail::append::append_to_multigeometry<MultiGeometry, RangeOrPoint>
{};

template <typename MultiGeometry, typename RangeOrPoint>
struct append_point<multi_polygon_tag, MultiGeometry, RangeOrPoint>
    : detail::append::append_to_multigeometry<MultiGeometry, RangeOrPoint>
{};

template <typename MultiGeometry, typename RangeOrPoint>
struct append_range<multi_polygon_tag, MultiGeometry, RangeOrPoint>
    : detail::append::append_to_multigeometry<MultiGeometry, RangeOrPoint>
{};

} // namespace splitted_dispatch

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_variant {

template <typename Geometry>
struct append
{
    template <typename RangeOrPoint>
    static inline void apply(Geometry& geometry,
                             RangeOrPoint const& range_or_point,
                             int ring_index,
                             int multi_index)
    {
        concepts::check<Geometry>();
        dispatch::append<Geometry, RangeOrPoint>::apply(geometry,
                                                        range_or_point,
                                                        ring_index,
                                                        multi_index);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct append<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename RangeOrPoint>
    struct visitor: boost::static_visitor<void>
    {
        RangeOrPoint const& m_range_or_point;
        int m_ring_index;
        int m_multi_index;

        visitor(RangeOrPoint const& range_or_point,
                int ring_index,
                int multi_index):
            m_range_or_point(range_or_point),
            m_ring_index(ring_index),
            m_multi_index(multi_index)
        {}

        template <typename Geometry>
        void operator()(Geometry& geometry) const
        {
            append<Geometry>::apply(geometry,
                                    m_range_or_point,
                                    m_ring_index,
                                    m_multi_index);
        }
    };

    template <typename RangeOrPoint>
    static inline void apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& variant_geometry,
                             RangeOrPoint const& range_or_point,
                             int ring_index,
                             int multi_index)
    {
        boost::apply_visitor(
            visitor<RangeOrPoint>(
                range_or_point,
                ring_index,
                multi_index
            ),
            variant_geometry
        );
    }
};

} // namespace resolve_variant;


/*!
\brief Appends one or more points to a linestring, ring, polygon, multi-geometry
\ingroup append
\tparam Geometry \tparam_geometry
\tparam RangeOrPoint Either a range or a point, fullfilling Boost.Range concept or Boost.Geometry Point Concept
\param geometry \param_geometry
\param range_or_point The point or range to add
\param ring_index The index of the ring in case of a polygon:
    exterior ring (-1, the default) or  interior ring index
\param multi_index The index of the geometry to which the points are appended

\qbk{[include reference/algorithms/append.qbk]}
}
 */
template <typename Geometry, typename RangeOrPoint>
inline void append(Geometry& geometry, RangeOrPoint const& range_or_point,
                   int ring_index = -1, int multi_index = 0)
{
    resolve_variant::append<Geometry>
                   ::apply(geometry, range_or_point, ring_index, multi_index);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_APPEND_HPP

/* append.hpp
Xqk2T5WEwtK4WB/s1CzMKu9DGjbgAYEgpWS2anN6ik0o3hSWowEB4grY4rIsMizuh1ubHydndWpimVEyPIgScqgO6aQSOGuoBzB39rkNaIEkYri4FCNASKCYrfUn78aWYsE0L3h4MfEo49tbbkwSvhL88axpnSN4rk96AAAs/9OmEjWD13WAklVei8iQFAMEyLp29D7K/YxCEb3pIsgVAru2XAew/8MpgFu97h6HUyw9uxMfxrzPZtqenJahJZiR9DRk16x5LG92yBE8JwTmi4NEeYwVUrIuV2kbCp3xXY7n6QM+MbmwPl+LGapiDQ2tGbyFBULcpX979VU+UPpD1VMtrxLBmQ73sCatya6wblQxzdX7KrhdnfnPWvg3epgGoNYSO7w1sqjgse0uO7m/Qnnp0Mr6obnxwgHMmQyOL2YYsVigg9WPlPa4EZxqwYl2FEhf5TrvpZeRA9HTIcwnKJ9Sd6C/Z67cSLooSGUtS2H4A/AsAl0jyg4Fo75Q2Wqnh5Bd3T8KNzQK3VXtFfeZr5mUg5CljXsTeamU4OzHgsRwxCBg45rX/HBj2Sgk2EVgnnz6ssJYXZG695BYkjlxVdgoi9pV52B4G++CmFUgKyUskZHsfk+IhBhDTC2GWICh0KfPMh07RFKUckGVamFE/zH2FxtaBY7QhetxGLDKqeFmfqH+fCPDcGjd0n2lT8QRt3WZJv8SEZUmk1dNyoh8JxxbVlg7FCxVglGLyTiNgUqBqpUoPYiErBu3TkmcgjKymBPCHoT3ERd193N9Qsztgz3JXMMjoEVw1CSm3Ix1COsKB/69e+AUAXuD5QUqyc1KWayMoF4LlemIYrnzxwlUtYqM25o451MbX2DzrdGoFKHzp44ZmDuVn8QIJshdKgym+bqZNAW1ijrOeVd/06Bb2E4aqBvF4etsjZMuVtVqT+AEh4SG+/bzD2sh/lye1HMXtx3MDq34yD2HsQVnwyKoreUk2vFa2aKzTprLjmOJu84LKEe3geDHN8etd81hrc9NkTE3J/VVTi2DDFyKRtCiNd+FNV/hO3ca0X2fkIFJwgT9K69uldXLSqyClgdP4OmTcS8tx+PRk7IwLgJ1hH6Zu+WRM2i1lUOv1MD+/yZEuJvRYrI4hvBDrnPMj2JVjrToPLsQQT5A05wnkYnUocYEQg8D3bSJ2Wz9ebaT+3MhHOqkvAj5XETvsG6616YDwuhfdTkp5wWyTIA+rTgv3M23pzDuhJmyNqPoiF8xR4SpOrjoXFajq7nePeBpmrqQrxWnX305NfxlvIPHFz136xFLBDpoja3Y2A46s1Q8u597Jx97epaP1F31ODpOXDevX5otdkw6cp7fE8lfm2eOPUWvHtHpQv3iVh28AuT5HIJRJdc2zz3ru0efCZCGHWxgJ6+mTM6nzMvqlqykT2k1xm5ocIHk5snA6zM7p3if73uEDZOm6OGenBlDjV/s1fdrPKBi1mAEDALLXsmHvkqqKGgTZqjwaP6Toh48U3pqZ6chXeUrmYYggL/YVIjHe3yoXi/dzeblVXxL14qGr8+rOzJB3850rq15vhq/rlHj8I3sgC4vYNAfyTvDXqr/9QzDhFatuXV5kzlp8ZN7NUnSd2Hgtg9hP7XCwdn5frt6v7gJ3xa+PPm2AA6cU8lBR9uJdak6qgyhREOHFyXRs7K+Uuvp6l6frYP1tpR0X4HtISHrpu4ai8mA996zzHw7vGjeeikbG9uzdGHctNFW9aHgeNhu/0/Qo8cw8eptdPFigPqx136iskHp09n7fQqg92znoD0xd/UDLUi+bedFWXMvqIC7NWTTpfFwsP7VrskDDSmvT/vlHH9Y3K1rEX+9tnCjiwm+h0pTaY0n+fnmzThir91Vb37UfC8mJaMS02/Ypm/+XKpi52Y/96dDY6wpepfqKqlEQq6egx58gmspsmBqjlP6Z3HR6Un+wr1W2GvEXh2CwHF4K6+44+kGhiLB7ONCmQxCe4wy7F+wVfd9Fo3AeEBsI1XLNWrzIi18VFsVzkFWHH9J3QdC5KiDdpHeIZhpnI7sDCMaf4D/01JROk1WQccroeZBBXmxS0NODmVG1gxVwu6Wv7p6+Rp4OqPPUalzvRJWfG5BRBZGBXnXiRf1+Aujwb6VV7W2plvYca45S3TBvtGRE1aW5HPDkXoX9/Uqgf6ruqW6lhP2/EFX+cTRB2bGO1R0u1ZPGlvf13PftNVn3vuSat99GSi2uDC8CCtpeZq4IABV7P752H9v7YD0OvZ6DFURaFVtCgJtg0NDVpN4jSKY4mr0CKUy6iQ1HGfMzpJK75eSE1/in6mG6iSnRjZslFx5fQ4mW0ebH67dpx7NrXt4vHpto5mHcOYtrV1zHLYmw7k859/ki54zMNl6fi53hnumerd15Q/Z0+nQF9n6aSlkT+n3c/uNpZ++ulkGj+zeWrwCSEOthaNNfuy+WiyztFI9Kq6bPs6LfWHTVId47f1M/ym4+bhHqJ03V7NwmE++Epc6RC0Pz9v9I19a6V18let/a5TG+i53e5+0AxR2ELyRYJ6j8oG2flW3e+oYtH/3zqv91I2VFxCAE0KLEYghtO6QceuBPChZU3mQTiZlxciTgNIjDXqsJUC0ijhzb7JAw4va8hMLe8shl+uHnmmgIMjKcJM3ugv3C35Qp688vst2rDG3YKhnzCABWTD+aZ5LDvbnh2Sk5C5oxAg2t1XVD0A3bQ3G+jqkSp/MNLb5D9m5ux0BaDoYRYO9Npwf9hHNZPBnsCALZJEXXh1LDoG3n9LsJnSTqmFyC+QYbCCOZHj6cyATaAhV/wEl82seD8Vkj5/MIbxULUgysUiSP0rp9gPJCBk7VOmBhfvoui9mHlEUSdwfM+6IYav0P7lkZv7Y0UMhXAlfvADBA1HITMpHhJnfpS6U0FdWXBlZFjJ0zwRUZfNJe5JAagRIUov5fFSoUw4CUm5DVBcep3Nz82VlZYTx8MTIxIJxiTCOmHzwF6kwTNU0FRnmtEWsQTjagHbM4TyCkhj0OXnRGGsKZT58i+V0vbeCVeNRvxemWBxqjGhD8y9UNFdr+8uFZu27N32CcnQOKwrzimlCw+r4ZumhfsZW2YQqyqBUcFA6hUoElF8GnxWWz3U6fDidXpaq4Ssj+NCMU3qmQv153NDLxphUYse8+tB6jq9I6qO0gUkZRRWHZUBvA2dqddoiyx8gjJ7dlPYadSDN2qGiD6vWRFTBmcSPE3hNqQRP0Rn3MsNmCbB2iv1zCV8r4wB2feYA5q7wBShFB4N9z9POHXC/40JIZNTdoP6S9YnYoS0f0tjOD1jziexWJxARpNJyZTYIQzDxguO2Ff2yABnI6uK2ZIxkjPk2khfD0QiaXR8I77p/ca+Huhe7dUzOOXP4/tQJ5hZ0Fit+svX3v9NNor8xZju2QYT+mNsRKF4S+OGU2dK4pHAR4mN5ojChMK78KtmP91Tq2g2zxAi9fEbB3WLp9JjMDgEAKCXuwRh/1dNkaiKxJUyX0uG+N4u9GNlksZvdUqEt3UTqPz+fuHfoSBiFfR0uSZcwSk4qlyAS3BK/vn9+eGCswxs/fGg0NVVNlYtZe3Gn4xFTyj7NmosnOMjkF9I2dMU8ZypTgp5DUryOiIgTExMD6c+aImNjmnCiguBR41kKlp460qGvcvSyBzEqILEYELNutYqjG21jks4K9f8XW4Y2VjXhA8S6uM8f54K+YGEhZWw2t39W7O8it8cgx0DDSNPOLbaJ/1OIAau+3CuU3zT9vTERFYUZrLvgP8KxArLogo5Tqg96AyGE2GfoZ1qGre5CAaaADc8k+o1hrFINmm1IIeqx6SjrQEPt24rld4Lh91av6cPoxrKC615Ua2KvzS3zCAEXPesez53gVkQocrwDtX/xfRuWpy8m1hT2tmCJMdfHQJgJVo4WEu19Itb4MRhHRZU0R14OxrW0aGpCWr02jqRn2TVlsxA1QIxLrkXfQBXpsvuY4meznD0ICOWL6iTaW54oUs32CgVMSCLVDRN6XU4m8DArYOmQ7GujbrKpvSqgBxGIGVzL2s1+Tr7RCgJSHdpEEyCEK5VzwjCBR7S0R9B14v2q7C52R+zeNpUGaJjG14HZhq6KIQnVjs4BeryCYLiepaSJC0VaVrIpgOurqoaDm6J3CJ7wQdd9CdQTaIMZm5fW9dGg5QdfSZP9jCarDebfy/rpvEaKDeka81Jdd7U5eFmG1rqvLLgYt+zJwclJKLjV4lrz7jyZMiPTFfpxiuGdmpD6M1B0hnXt6OTUZbXNfhWtP2+tGaBFZyVZmNlufHY0RZrEHxoWpgeOf9JvUVdT91mcACdhfF2ANatolV72enZysmE6mRlYDgzEz9wlfrEyKdV7N53jRxgLfEgAYnlxKTi1ACNaEF6dswYshUoaDVxQWDa9KZrNGseVI3MOvrj9MX3zDNO4CN2MWib6/t6nTvbLxdtyzve23MCMOMvtVTg525YrbWbErvBRrHNO7HGvSsRusxL1wS6fmn8VqoUyYLMHMfupp6+Yy9/eBypsRC8C+QTjGPPk1PI+EnUpZKHfG6bPOUVV5OvkKiA9KK6oNvW5D0ulTe/lru7LPWm7x7EbG0xy9/gb84gAsXtP7rWixde69L4b1/3CVuOFPXLpmcus3POUN9zbuVeYAggNFKQ7HdzLO2nT3bttG5yxzY3ojkesNlIgqcz0YOWP5Lzro6pV53Ddjw8sNC0wmUflFitE8gIMgQgkQIrEPwI4/O6WEPbNC0TbLqEg8dVZGNiOkJ9dQEG/M59ABDAYvrYFpFAc6tVVAo8PmSEQfwKXR1V/XIkNdJrAUiVzDrYOCPlGo8v+UTJZ/aMz/qUAqaet2fMO1Ny/k7QTXUxuPvExjJFhQpuCaJ9ZM8Ufo3nedo8YXvziMRMLxpeCPyWnqg9GiE+39ghaFiVQR2XkQbDZKhtxFQngOJM1u5gajB+bCJ+m0syX9G4A/2kz6e46mMP/ZlUFa9cItuG/TUGG4dMlofMbWCApAhGgtZfJn1RfdKlK8wvx9FQiktynt/d7ykMBiX9HC4dIUInuoSiS5ZqVgKaeByglYp6g/V6PYIOqj1oHcYC6tlkptqQbQI0nvHgy8ftMrBHWIaFCmnRpPjvM085/NvnPp1guDBUY76hQ+aW+Nqfw31CSH7GjGw0jIjxHYaK1fmiJ1DSge5tHIHm4UXmt9zy7KdJGKLS+ugv5JF9FCvXkRdNNJRDdolsREIps/MRTF9T42N0+uPAFuj2F1SEjgHqAACTSJAbsAHxCVE1w4eDAGfPEIIsmhhOrXMRHFEkNRYmKOVJzSsX9rpUyEHw5A8iQK3aFaAwH9CItGdwOrCROPUxii8XMCioKu2UaXWKsGQoe6xpWjZbG5KX5q2wNDS4fZ01/uaOmeobwKHiMZkaW8YoL/xjj8X/WJczJllz8RPdH5BdWnC6YJMBWkrhACiFSWflKVcx9/9gLRclYmdGgVn6EL3nCuzH8SElp9BchJJZZLEO6TzVz4h6LLUo9/DlxPudFfPzDWUuGaWIUN7WWXT8B78plqCK4kbNbj9mxP1bmqs8IqQwJeCdBeDK0zHX908KNbA4UaZFsUnbpM4NVbRRoS4MMbRxncpgPY3C1uijsljB8FYgWVNMVi2QtRi+bhhscFC7Hj84xk/w0hUbSVIc0lgwrc7gKLLIkEOvgF8wyqYUWz7/c7nnC8j490Olz6Lbq7AFZigpaBGQDdbE/4Wa5em0B0dL2kTBerK4rcoe/prD4lOTm3nSwEJKMXgv13fwSdHI52HZsDDLeVbc6xy7MoqW4j3OMgTCHwR4SDikDvFZtt9VocwK8CxNmMxOLBVH7y1uXpUti9yo9/X0oK4zl9tn7nm1KiZ6AIs0aThVMuXA7LSfWkKOBpQfLXZnqj+TdObOBmjsuDfeZ6bx/KulmS4e6vapqWq5cXe5cnyPieZKw/ao2jxB+FRZKIeG31sbeb3he22hju2XK45Tk8cwSZF+4FPe0sgbuPiFOKUyKxJNL+WreH679mOKVlmgfG203IMDLEOUWbO33761RlraQ8IMUgNCiEdBLBlP6UzShW6R5k5SOB620Jyynj0AlWoJHtbySQvdc4PDV6rNXwvyiZhIJid2+3m92G/0RzJH1Oc1/bDLAygOOHWFkO5tYWBJ5TCvWUD0VV811qvNV1SsH2Nd6NMYduBzpOCed8/QmP4hrwLP6Uox9UewArh7Vd4Ds12apHl3pHxE2CLEW1DbCES9Dkz1xQ4tTyOOZ1f6zqKzNOqmH7yu4K6o+ieeRKyp1nUi3TW5p1mGBAH+ORrq1e4hPAnJaXJ4GEsaQa+2HNdIjhDNS/xot7nkKkIbY/Y/iltOAy7bYMz0iMWTVie1J1FnhSgo+dVSm8U0E6Xh+XzOEODfO4hytJF5TgZlCd7pgdU+ZCBkCM9KjzjMp45Wn7coRyLjrPxCTnV2HWgmYDiDJow+CJHaESA/edWckrNapzmW93LCg1VRaUYaqW6eJk/GWokjN/7DdsQ1YtuuFzMCvxQHFElYHLsYTbNoocaG0H49OPOpvM/pc5ZUa4kWNsF4Hk3SIMRzLBG4m4Ajl31jOkQSmtSS7CYqUjGq7HYcW8czaKQbmSI+ViCvZcR/p7UKX6MZMUNNIdTthOdYEH4xm0LVwa/57brwYsDy/bofBwyRhgmxRp1iwEjFMCnK6btSVVzENo2kvhK+Nwq0hBkuuSi14r4AJLPhP5kbugUb0v/VMDoHztE77sY08TJOyJo6FHRNSlHIw9elsWFQjVg+lHR5u924edV0Z23flPEqteceJTH+qBSTDd1eoB8zIp2DesDVZRlobVdJ7aolRWeDCJxUBaYUSPjb0HAP9SEXCVH+5tolOlM5ha5zgzijgYX96JXXvW+D/AJemWZSAyJowfyHPw7x/r0rZMfEn/uvAJWidGOlfTZW73P9Y2PzORKlMrcXKm7IJl1Reynorg2YjoIBnCKDAUJRAZ+NSjRnnvpg2YU97JFkLMPvQyeNceEJKPQrqzbnnWi6vqiNecyCpU29A9NZTvZGlaoawRIWW//7+RoxwbYxEDB0o/dZtL6o82Mp5LnPgzC7tu2w9qv0A/pw5i8oW2RcgetxKdM4hlIdP6vyHqyiunvbs4xG28imi9ot0B38SgAuYN7c0lFXZaudc2+xs9p2+YTU45YrKwmIZWiVLYRoPNmNAu2ZV59amXUbH2K+j2Xq9hk7KBjzi5tpmpguu6PkPON4fhc2MMnfVFFxjriRHi1ddMAAJorgBsh+Jeh867xYh7fZb8mUqJff24ALg1gRZmMJOkcm6GhNuhutnVY6uzBoHzb7wv+42DJDdLmnr9LN/sNmszs5on7hGVAnaG8av8PcCoMxRYrDBMBNo6ZzKoyIlu+KbJKzOQsOQ0PBiuy6ckUfcgcWmwYOTzcKBxXZSFJbqxfge0hpfXzkXD4A790/vs7t/k2+MCy7R/LaeCH5IkilAa7pgvsuC4QtbxTKZF2H1bo14ppLUDd0Pooiw0M9LKJUd8i7eL2mJHPTeFRKBmKxzuksJrTIAUEYUYuXraaR2ZVPtXWbWxcDe6pwdhe+ty/WKbAls36QqWr1PjgoxSFzr0prKCClV/9kqpiHrEt9A3B3tanrVZxx1qmC4Gp8q5E1ITL/pmQwfyi5dP96x/7/d/zx0geXOAK3HA18DYtC8ZBXPPiJQMfVbiAvFxbo+hqj5Y0+x0KsiUgsRvp6pYg8BfRXtCKSYNk2pdFdiucXvIXbWDSc2s/qvLamVsyZHBV9LvvQBMG5DsArpAdsAAID+AP8B+QP6B+wP+B+IP5B/oP5A/4H5A/sH7s+/P/B/EP4g/kH6g/wH5Q/qH7Q/6H8w/mD+wfqD/QfnD+4fvD/4fwj+EP4h+kP8h+QP6R+yP+R/KP5Q/qH6Q/2H5g/tH7o/9H8Y/jD+YfrD/IflD+sftj/sfzj+cP7h+sP9h+cP7x++P/x/BP4I/hH6I/xH5I/oH7E/4n8k/kj+kfoj/Ufmj+wfuT/yfxT+KP5R+qP8R+WP6h+1P+p/NP5o/tH6o/1H54/uH70/+n8M/hj+Mfpj/Mfkj+kfsz/mfyz+WP6x+mP9x+aP7R+7P/Z/HP44/nH64/zH5Y/rH7c/7n88/nj+8frj/cfnj+8fvz8Bf2hdWejM59swH6EfJgIiDBgwW9am5k+u1M5bjrrtU7Zj4mF2LJXfF+KQ6idcAHUCpyrpk8crPksh4x2eizFRhiwGNCEpPimWiu9brnGv26P3v8EKTX1SJZGfEskBKAmJuh1HdgQEC3NoJchV50nOmfWLiVE0065RVNpah9IRfvw30xHOhrWfO/ODCdRtNkD8nj3MJTE6fE7QH3EbGI6H6lJcXang4BepMvmpqWIocQ1j0uA41Pccvov8r5IBlvrNiEoom5Ftxzq/n6Q1m+iD+lskH6zlRg+qnOQPDeQFzaRMSdf6W3hf8wtHSqmogTueblWBpuelsMIPI9Ibg01UMANBNrSxqiLIqV0uEKLBUi7bM42ZR7/whQK/ynC3NnvrsWJuwD602jxZ/1s+gqm44KQgdVlho2QTh9bX4uezWvOID5BUcaF/gcnRrCpP5aLnCjJdrtYXSjLEqWReYsUzAWrzsEiedB00YL+jdIOhVDIBhGRZQMYrxZeMH4LbZJ1pSSrx6Pe8esXQWcblXHAl/R8AVoCpf6A20RbylWZ+bLYXl5bNzYiHz1kX0apLSO5W5r9t9KlgTWpqk4LSvX3YaXyXvQkl5AC9du9c4adtUQsiHiwKMe2Zk4wtD8PxgNQWc5+z7L4Cz8rLHjxuLaWpcoyajuqRAOfeWSiYLPbGOkkV/W1mj3MfKzN7sCwUHgBf7XiXFQrE8MLGqP2Mt37RiCUSuS61TFMQSmgPtVFGqylIe8xlBd2P1XoO2aLg2iVxQB3KZl6rfOHIgmyW2bpO41F895NmRSlY/ZIN24qoUG7NEjsBt5s8XU7hEjMOCQ3cUZNMhlpMybfvnl9oDewm0S9lmTEAz+t2niPZ+KzHd0G3qvPNtxEuTIpwHSrj+pHPPYgA3KtDlJ+O5ik02/Mksenlcoxg+5tInG3n880G8B21z0vNhocqQrPjGTTB05depqHQs6rznrKzV8guHFC/pg2fxzOAF5ozgW3by8M=
*/