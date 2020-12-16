// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_NUM_POINTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_NUM_POINTS_HPP

#include <cstddef>

#include <boost/mpl/size_t.hpp>

#include <boost/range.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/algorithms/detail/counting.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>


namespace boost { namespace geometry
{

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127)
#endif


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace num_points
{


template <bool AddForOpen>
struct range_count
{
    template <typename Range>
    static inline std::size_t apply(Range const& range)
    {
        std::size_t n = boost::size(range);
        if (AddForOpen
            && n > 0
            && geometry::closure<Range>::value == open
            )
        {
            return n + 1;
        }
        return n;
    }
};

}} // namespace detail::num_points
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry,
    bool AddForOpen,
    typename Tag = typename tag_cast
        <
            typename tag<Geometry>::type, multi_tag
        >::type
>
struct num_points: not_implemented<Tag>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, point_tag>
    : detail::counting::other_count<1>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, box_tag>
    : detail::counting::other_count<(1 << geometry::dimension<Geometry>::value)>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, segment_tag>
    : detail::counting::other_count<2>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, linestring_tag>
    : detail::num_points::range_count<AddForOpen>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, ring_tag>
    : detail::num_points::range_count<AddForOpen>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, polygon_tag>
    : detail::counting::polygon_count
        <
            detail::num_points::range_count<AddForOpen>
        >
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, multi_tag>
    : detail::counting::multi_count
        <
            num_points<typename boost::range_value<Geometry>::type, AddForOpen>
        >
{};

} // namespace dispatch
#endif


namespace resolve_variant
{

template <typename Geometry>
struct num_points
{
    static inline std::size_t apply(Geometry const& geometry,
                                    bool add_for_open)
    {
        concepts::check<Geometry const>();

        return add_for_open
            ? dispatch::num_points<Geometry, true>::apply(geometry)
            : dispatch::num_points<Geometry, false>::apply(geometry);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct num_points<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor: boost::static_visitor<std::size_t>
    {
        bool m_add_for_open;

        visitor(bool add_for_open): m_add_for_open(add_for_open) {}

        template <typename Geometry>
        inline std::size_t operator()(Geometry const& geometry) const
        {
            return num_points<Geometry>::apply(geometry, m_add_for_open);
        }
    };

    static inline std::size_t
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
          bool add_for_open)
    {
        return boost::apply_visitor(visitor(add_for_open), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_calc{number of points}
\ingroup num_points
\details \details_calc{num_points, number of points}.
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\param add_for_open add one for open geometries (i.e. polygon types which are not closed)
\return \return_calc{number of points}

\qbk{[include reference/algorithms/num_points.qbk]}
*/
template <typename Geometry>
inline std::size_t num_points(Geometry const& geometry, bool add_for_open = false)
{
    return resolve_variant::num_points<Geometry>::apply(geometry, add_for_open);
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_NUM_POINTS_HPP

/* num_points.hpp
zP9j/t/ybSOGjXCPmD7iohEVI9aN2DnioREvjXhvREhBdoG74IqCrQX3FjxV8GLB2wX/KAgpjMYWVziw8GuFcwvXFtYV7i08WPhxoXVk7sixIy8eWTVyx8iGkS+PPDbyy5HpoyaMumzUtaN+OGrfqNdHnRwV7sp1TXYtdq113epqdL3u+tgVNTpv9PTRy0d/e/Qdo38++s3Rn45OHOMaM2vM6jE7xuwe89qYk2juQ8dOHbtk7Lax9WOfH3t07OmxseMKxl0wbsW42nEPj3tp3HvjQoqcRaOLLiyqKFpX9H25/aDojqK7ih4segLbr4veLjpZ9GHRR0VfFsUWO4oLi6cWlxUvKd5UvK34JmP7TnFt8W3FO5XNgr4wBn2pA7sFj2naQC0De5qxp2MfiJWLTM9rbGned07NhkfP60F4zsJzLLZB+CTNOH4gLOKx6xvew2sCdhses2EfA192HJ2BZzwax0EBrzNAMxCNviE2sg3Un3GEQ9kGGM8p2Iw4sFm9j6nYYzyfBbClYI/y+g/TLGSzyy0MngbhKHQzSEk2tsGY42TjXY53H4wdesiRAXi2wRPyDztSBe92vErB8QnYESuekffY7N7dhkebp0TIhjzAJ/gMGnoabNgzjTxG3mID0T/XPzXKABtiGOBNDZ7xiJmMkU85Mi9tsMgw8jYLPFYS/Vn8w2vwLKTd7n22G6Wf5X1O0p+VTS8XxOEt5yxs8TgqAY/xeG/Hnq7v2KK9j3GwsHtfwZ8nNlDY4dNMsoF6nzO8ewaOxKNOsGXDu8MoJVmC3vqJWgAS681j7Hgt9mQ8ks34PEXULby2IxIb7Aeg5AZ5d7QEPA7CUdCHph5HJj5FNEZEiFPZkuQrlDce9dzMwB7rVdXwmInnKERP4tfLCiwH1EbqAUpbtths72soe5/jcbTV2JBeb11EboOgXiEFSYgU6VA23S/SCivM0WDprb/YQPGYgQ31TuY5IvemHHkh051h5I7dY4NjsEv/CeKV9IgjyTvxSZY8Eu8lRS+CuJNIvQxDWsJQezAvRimm4Bm5hVdxevnhES0Vj2H64V4ajV3917Ydf2sG+7v4/vgrmDvOwLx3J/bxMPwHeAFM1mPX8Nn72Ndt9x2j6cfhc91+EthTWle7l7Hb4Hce9p9ghwbspA/Y6j5uDYMP7InwMx37reG6zzGY527BHg/fn0eYax/Zpmm7twVPfxN8Qx+vdVuqMSiqqw40oCXzUfp9ZKPMR8Sp+4au1JsCDWhSHTUt0PKvw2nEE415Rnnvj9L9zMEz/LP20IS9VxMx6rqnYCO0abxvf0uPGVqIuW95x8W0GzpKmuCjd2mhZUXj3NRPaZnyrTNTB/i6hmOIDnx2oyXzEDrUl8w3VRMxqTpgNd2n5Y3YM5dnnrT+tMYTU9/bKKdTXdM/eTbVyLPDSbSNwi9pp2/E9rxum7XTpBq1busasIeurg9tagN9mZ/wa5qniE3mq4wRMcs4228Ifn7ugYbaN9TG9K1/QIyod744N9/gv3/A8dANvA1zsZXeEPw+LyWANJ2JdvXeVk9M/Vvn90JTTdv3o3R9NY3QVcsN8fDpPUXKAenoNt7NMt26JuzwWs1f6VtPH56nbWXmOUZsN0d7bP3PeUj+yLgugS1iJvMf8K1971v9jUlHr/c/9kEDer2va7uJBtIo+x2UO/x23/+c6mX/g/RK3Y3QRblA11uXZLlAD/6kb1nPUX7wo8cIX4gNGrKMZHyIVaYBsZA6T+KZDG3ED21WV2qi/KEp6wC0A9N9V9eWurFe3b7XG648D2+R5Ynj4MOoH3gPG3o+I3W9xz+0RY8Fx+Jz3Q429HiUk3F8GI41xrFrYIe6ItI=
*/