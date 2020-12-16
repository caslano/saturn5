// Boost.Geometry Index
//
// This view makes possible to treat some simple primitives as its bounding geometry
// e.g. box, nsphere, etc.
//
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_BOUNDED_VIEW_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_BOUNDED_VIEW_HPP

#include <boost/mpl/assert.hpp>

#include <boost/geometry/algorithms/envelope.hpp>

#include <boost/geometry/strategies/index.hpp>

namespace boost { namespace geometry {

namespace index { namespace detail {


template <typename Geometry, typename BoundingGeometry, typename Strategy>
struct bounded_view_base_cs_tag
{
    typedef typename Strategy::cs_tag type;
};

template <typename Geometry, typename BoundingGeometry>
struct bounded_view_base_cs_tag<Geometry, BoundingGeometry, default_strategy>
    : geometry::cs_tag<Geometry>
{};


template
<
    typename Geometry,
    typename BoundingGeometry,
    typename Strategy,
    typename Tag = typename geometry::tag<Geometry>::type,
    typename BoundingTag = typename geometry::tag<BoundingGeometry>::type,
    typename CSTag = typename bounded_view_base_cs_tag
                        <
                            Geometry, BoundingGeometry, Strategy
                        >::type
>
struct bounded_view_base
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THOSE_GEOMETRIES,
        (types<Tag, BoundingTag, CSTag>));
};


// Segment -> Box

template <typename Segment, typename Box, typename Strategy>
struct bounded_view_base<Segment, Box, Strategy, segment_tag, box_tag, cartesian_tag>
{
public:
    typedef typename geometry::coordinate_type<Box>::type coordinate_type;

    bounded_view_base(Segment const& segment, Strategy const& )
        : m_segment(segment)
    {}
    
    template <std::size_t Dimension>
    inline coordinate_type get_min() const
    {
        return boost::numeric_cast<coordinate_type>(
                (std::min)( geometry::get<0, Dimension>(m_segment),
                            geometry::get<1, Dimension>(m_segment) ) );
    }

    template <std::size_t Dimension>
    inline coordinate_type get_max() const
    {
        return boost::numeric_cast<coordinate_type>(
                (std::max)( geometry::get<0, Dimension>(m_segment),
                            geometry::get<1, Dimension>(m_segment) ) );
    }

private:
    Segment const& m_segment;
};

template <typename Segment, typename Box, typename Strategy, typename CSTag>
struct bounded_view_base<Segment, Box, Strategy, segment_tag, box_tag, CSTag>
{
    template <typename S>
    inline void envelope(Segment const& segment, S const& strategy)
    {
        geometry::envelope(segment, m_box,
                           strategy.get_envelope_segment_strategy());
    }

    inline void envelope(Segment const& segment, default_strategy const& )
    {
        geometry::envelope(segment, m_box);
    }

public:
    typedef typename geometry::coordinate_type<Box>::type coordinate_type;

    bounded_view_base(Segment const& segment, Strategy const& strategy)
    {
        envelope(segment, strategy);
    }

    template <std::size_t Dimension>
    inline coordinate_type get_min() const
    {
        return geometry::get<min_corner, Dimension>(m_box);
    }

    template <std::size_t Dimension>
    inline coordinate_type get_max() const
    {
        return geometry::get<max_corner, Dimension>(m_box);
    }

private:
    Box m_box;
};

// Box -> Box

template <typename BoxIn, typename Box, typename Strategy, typename CSTag>
struct bounded_view_base<BoxIn, Box, Strategy, box_tag, box_tag, CSTag>
{
public:
    typedef typename geometry::coordinate_type<Box>::type coordinate_type;

    bounded_view_base(BoxIn const& box, Strategy const& )
        : m_box(box)
    {}

    template <std::size_t Dimension>
    inline coordinate_type get_min() const
    {
        return boost::numeric_cast<coordinate_type>(
                geometry::get<min_corner, Dimension>(m_box) );
    }

    template <std::size_t Dimension>
    inline coordinate_type get_max() const
    {
        return boost::numeric_cast<coordinate_type>(
                geometry::get<max_corner, Dimension>(m_box) );
    }

private:
    BoxIn const& m_box;
};

// Point -> Box

template <typename Point, typename Box, typename Strategy, typename CSTag>
struct bounded_view_base<Point, Box, Strategy, point_tag, box_tag, CSTag>
{
public:
    typedef typename geometry::coordinate_type<Box>::type coordinate_type;

    bounded_view_base(Point const& point, Strategy const& )
        : m_point(point)
    {}

    template <std::size_t Dimension>
    inline coordinate_type get_min() const
    {
        return boost::numeric_cast<coordinate_type>(
                geometry::get<Dimension>(m_point) );
    }

    template <std::size_t Dimension>
    inline coordinate_type get_max() const
    {
        return boost::numeric_cast<coordinate_type>(
                geometry::get<Dimension>(m_point) );
    }

private:
    Point const& m_point;
};


template <typename Geometry,
          typename BoundingGeometry,
          typename Strategy,
          typename Tag = typename geometry::tag<Geometry>::type,
          typename BoundingTag = typename geometry::tag<BoundingGeometry>::type>
struct bounded_view
    : bounded_view_base<Geometry, BoundingGeometry, Strategy>
{
    typedef bounded_view_base<Geometry, BoundingGeometry, Strategy> base_type;

    bounded_view(Geometry const& geometry, Strategy const& strategy)
        : base_type(geometry, strategy)
    {}
};

template <typename Geometry,
          typename BoundingGeometry,
          typename Tag,
          typename BoundingTag>
struct bounded_view<Geometry, BoundingGeometry, default_strategy, Tag, BoundingTag>
    : bounded_view_base
        <
            Geometry,
            BoundingGeometry,
            typename strategy::index::services::default_strategy<Geometry>::type
        >
{
    typedef typename strategy::index::services::default_strategy
        <
            Geometry
        >::type strategy_type;

    typedef bounded_view_base
        <
            Geometry,
            BoundingGeometry,
            strategy_type
        > base_type;

    explicit bounded_view(Geometry const& geometry, default_strategy const& )
        : base_type(geometry, strategy_type())
    {}
};


}} // namespace index::detail

// XXX -> Box

#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename Geometry, typename Box, typename Strategy, typename Tag>
struct tag< index::detail::bounded_view<Geometry, Box, Strategy, Tag, box_tag> >
{
    typedef box_tag type;
};

template <typename Geometry, typename Box, typename Strategy, typename Tag>
struct point_type< index::detail::bounded_view<Geometry, Box, Strategy, Tag, box_tag> >
{
    typedef typename point_type<Box>::type type;
};

template <typename Geometry, typename Box, typename Strategy, typename Tag, std::size_t Dimension>
struct indexed_access<index::detail::bounded_view<Geometry, Box, Strategy, Tag, box_tag>,
                      min_corner, Dimension>
{
    typedef index::detail::bounded_view<Geometry, Box, Strategy, Tag, box_tag> box_type;
    typedef typename geometry::coordinate_type<Box>::type coordinate_type;

    static inline coordinate_type get(box_type const& b)
    {
        return b.template get_min<Dimension>();
    }

    //static inline void set(box_type & b, coordinate_type const& value)
    //{
    //    BOOST_GEOMETRY_INDEX_ASSERT(false, "unable to modify a box through view");
    //}
};

template <typename Geometry, typename Box, typename Strategy, typename Tag, std::size_t Dimension>
struct indexed_access<index::detail::bounded_view<Geometry, Box, Strategy, Tag, box_tag>,
                      max_corner, Dimension>
{
    typedef index::detail::bounded_view<Geometry, Box, Strategy, Tag, box_tag> box_type;
    typedef typename geometry::coordinate_type<Box>::type coordinate_type;

    static inline coordinate_type get(box_type const& b)
    {
        return b.template get_max<Dimension>();
    }

    //static inline void set(box_type & b, coordinate_type const& value)
    //{
    //    BOOST_GEOMETRY_INDEX_ASSERT(false, "unable to modify a box through view");
    //}
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_INDEX_DETAIL_BOUNDED_VIEW_HPP

/* bounded_view.hpp
Mmv7WFFmbR+3l1nbx/wya/uYXWZtH3ll1vYxvczaPpLLrO1jcpm1fYxzubmuVy431/XK5ea6XpVZ20e3Ms/20QHdvX20QXdvH83Q3dtHE3T39hFUVnP7MO8TObJWX3snmNPvbB+lD1RrH0Vz8zNqcZ9whvOrsS3U1G6Dg+3t2m1nVy3b7e5faJu5nuteWduMy5CjiXCoMQ6sbVO3ddMsj/XoVsuYnu+Dht9vfJryfwJyFTINyUPmIUuQ1chGpAJ5HnkDOYIcQ/6G/ISE8PAXg7RHeiADkTHI1UgmUoiUIMuQ+5CHkW3IS8h+5D3kOCLjkpKGCL2GQjbpuiO8NmN+oYDnhI2ua9mHG/W1R7e7t1xuut3tcbm57ksbrdfBRzdar4P3b7ReB0s3Wq+Dt2y0XgdnbbReB7M3Wq+DU11uOh3jXG46HUNcbjodF7vcdDo6utx0Olq63HQ6GrvcdDp8XG46HacetF4HP3G56XS863LT6XjT5abTsdvlptPxtMtNp6Pc5abTca/LTadjqctNp2P+g9brYIG4mdfBDK33VXqS6OZ1cDS6+3XwMq1fLGvL2K/jmCUL4C1S7RdK+x20ya796suKRzteLu14vArz3r+9HUv7JQ2/rP3GP+xqv1EPW9tv0MPW9vtdubX9flFubb+V5db2+3a5tf2+Wm5tv78pt7bfLeXW9ltWbm2/d5Vb2++t5db2O6fc2n5nlFvb73Xl1vZ7Zbm1/Q5zubnu/+XW9tup3Np+W5Vb229YubX9+pVb2+/pTdb2++kma/t9f5O1/R7YZG2/L2+ytt/tm6ztd7O4me13Lbp7+1yO7rV96vc/5+49T13fD9R1Tvu5et9i/z7B2/uour9H8va+qFC958mbOHn7kpueXxvVeULpzz8lVtT9PY/9e4x//vufur7Pqev7mbq+97N/b+ntPZLX93vq/U+Mrznmgh+1TyI6f4fyt0O+gTd4DHaAH8Ou0PjWvJt8G99b9D7ybfxlog+Ub+QvF32EfCt/hejj5Fv5SaJPhl+hXyd6MjyFnin6dHgaPVf0PFiFPkv02fA79JtFnw9/QL9N9NvhT+jLRV8BHXC16PdAX7he9DLoD8tFfxgGwq2iPwGD4TOiPwsbwhdEfxGGwldFfw02hvtFPwDD4GHRj8AI+KHoH8Eo+LHon8Bo+KXoJ2AMPC36t7AF/En0n2EsxGalB8HWsLHoTWAcjBa9GWwLW4tOWbBGgzkOwZiG1I8hRrxSPzrgz2BH2AF2gl3h9bAb7AJ7i94HdoWXiT4QxsPLRR8Be8ArRB8He8FJok+GveF1oifDvjBT9OmwP8wVPQ8OgLNEnw0vgzeLPh8OgreJfjscApeLvgIOg6tFvwdeDteLXgYTYLnoD8NRcKvoT8Ax8BnRn4VXwBdEfxEmwldFfw2Oh/tFPwAnwsOiH4GT4IeifwST4MeifwKvgV+KfgJOhadF/xZeB38S/WeYAqkfSg+C02Bj0ZvAdBgtejOYCVuL3gZmwQtElzUC5NlcPVNz3HONgCNyPTkKG8EPYRSshE3h+zBW9FbwXdhOdDP+3WeI/3cS/z6J//cS/yGJ/6CKH13i36/iRzffq/rKs6k8bxO/WutgotT3G2XtoV/BlnAebAv3wo7wZrm+lfDvKnGfAhfCaaJnwUUwT/RieBucJ/pCuBguEX0FvAOuFn0dXAo3iv4IXA4rRH8GlsLnRX8F3gXfEP0gXAWPiP4BXA2Pif4ZXAP/Jvq38D74k+j+PuQNDIGGHg7XwxjRW8MNsL3oneFG2EP0vrAcDhR9OHwEjhF9PNwCrxY9GW6FmaLnwApYKPpc+BQsEf02uA0uE30lfAbeJ/oGuAM=
*/