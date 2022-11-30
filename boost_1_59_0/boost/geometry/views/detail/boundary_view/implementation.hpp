// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_VIEWS_DETAIL_BOUNDARY_VIEW_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_VIEWS_DETAIL_BOUNDARY_VIEW_IMPLEMENTATION_HPP

#include <cstddef>
#include <algorithm>
#include <iterator>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/core/addressof.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>

#include <boost/geometry/algorithms/num_interior_rings.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/iterators/flatten_iterator.hpp>
#include <boost/geometry/util/range.hpp>
#include <boost/geometry/views/closeable_view.hpp>
#include <boost/geometry/views/detail/boundary_view/interface.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace boundary_views
{


template
<
    typename Polygon,
    typename Value = typename ring_type<Polygon>::type,
    typename Reference = typename ring_return_type<Polygon>::type,
    typename Difference = typename boost::range_difference
        <
            typename std::remove_reference
                <
                    typename interior_return_type<Polygon>::type
                >::type
        >::type
>
class polygon_rings_iterator
    : public boost::iterator_facade
        <
            polygon_rings_iterator<Polygon, Value, Reference, Difference>,
            Value,
            boost::random_access_traversal_tag,
            Reference,
            Difference
        >
{
    typedef typename boost::range_size
        <
            typename std::remove_reference
                <
                    typename interior_return_type<Polygon>::type
                >::type
        >::type size_type;

public:
    // default constructor
    polygon_rings_iterator()
        : m_polygon(NULL)
        , m_index(0)
    {}

    // for begin
    polygon_rings_iterator(Polygon& polygon)
        : m_polygon(boost::addressof(polygon))
        , m_index(0)
    {}

    // for end
    polygon_rings_iterator(Polygon& polygon, bool)
        : m_polygon(boost::addressof(polygon))
        , m_index(static_cast<size_type>(num_rings(polygon)))
    {}

    template
    <
        typename OtherPolygon,
        typename OtherValue,
        typename OtherReference,
        typename OtherDifference
    >
    polygon_rings_iterator(polygon_rings_iterator
                           <
                               OtherPolygon,
                               OtherValue,
                               OtherReference,
                               OtherDifference
                           > const& other)
        : m_polygon(other.m_polygon)
        , m_index(other.m_index)
    {
        static const bool is_convertible
            = std::is_convertible<OtherPolygon, Polygon>::value;

        BOOST_GEOMETRY_STATIC_ASSERT((is_convertible),
            "OtherPolygon has to be convertible to Polygon.",
            OtherPolygon, Polygon);
    }

private:
    friend class boost::iterator_core_access;

    template
    <
        typename OtherPolygon,
        typename OtherValue,
        typename OtherReference,
        typename OtherDifference
    >
    friend class polygon_rings_iterator;


    static inline std::size_t num_rings(Polygon const& polygon)
    {
        return geometry::num_interior_rings(polygon) + 1;
    }

    inline Reference dereference() const
    {
        if (m_index == 0)
        {
            return exterior_ring(*m_polygon);
        }
        return range::at(interior_rings(*m_polygon), m_index - 1);
    }

    template
    <
        typename OtherPolygon,
        typename OtherValue,
        typename OtherReference,
        typename OtherDifference
    >
    inline bool equal(polygon_rings_iterator
                      <
                          OtherPolygon,
                          OtherValue,
                          OtherReference,
                          OtherDifference
                      > const& other) const
    {
        BOOST_GEOMETRY_ASSERT(m_polygon == other.m_polygon);
        return m_index == other.m_index;
    }

    inline void increment()
    {
        ++m_index;
    }

    inline void decrement()
    {
        --m_index;
    }

    template
    <
        typename OtherPolygon,
        typename OtherValue,
        typename OtherReference,
        typename OtherDifference
    >
    inline Difference distance_to(polygon_rings_iterator
                                  <
                                      OtherPolygon,
                                      OtherValue,
                                      OtherReference,
                                      OtherDifference
                                  > const& other) const
    {
        return static_cast<Difference>(other.m_index)
            - static_cast<Difference>(m_index);
    }

    inline void advance(Difference n)
    {
        m_index += n;
    }

private:
    Polygon* m_polygon;
    size_type m_index;
};


template <typename Ring>
class ring_boundary : closeable_view<Ring, closure<Ring>::value>::type
{
private:
    typedef typename closeable_view<Ring, closure<Ring>::value>::type base_type;

public:
    typedef typename base_type::iterator iterator;
    typedef typename base_type::const_iterator const_iterator;
    
    typedef linestring_tag tag_type;

    explicit ring_boundary(Ring& ring)
        : base_type(ring) {}

    iterator begin() { return base_type::begin(); }
    iterator end() { return base_type::end(); }
    const_iterator begin() const { return base_type::begin(); }
    const_iterator end() const { return base_type::end(); }
};


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct num_rings
{};

template <typename Polygon>
struct num_rings<Polygon, polygon_tag>
{
    static inline std::size_t apply(Polygon const& polygon)
    {
        return geometry::num_interior_rings(polygon) + 1;
    }
};

template <typename MultiPolygon>
struct num_rings<MultiPolygon, multi_polygon_tag>
{
    static inline std::size_t apply(MultiPolygon const& multipolygon)
    {
        return geometry::num_interior_rings(multipolygon)
            + static_cast<std::size_t>(boost::size(multipolygon));
    }
};


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct views_container_initializer
{};

template <typename Polygon>
struct views_container_initializer<Polygon, polygon_tag>
{
    template <typename BoundaryView>
    static inline void apply(Polygon const& polygon, BoundaryView* views)
    {
        typedef polygon_rings_iterator<Polygon> rings_iterator_type;

        std::uninitialized_copy(rings_iterator_type(polygon),
                                rings_iterator_type(polygon, true),
                                views);
    }
};

template <typename MultiPolygon>
class views_container_initializer<MultiPolygon, multi_polygon_tag>
{
    typedef std::conditional_t
        <
            std::is_const<MultiPolygon>::value,
            typename boost::range_value<MultiPolygon>::type const,
            typename boost::range_value<MultiPolygon>::type
        > polygon_type;

    typedef polygon_rings_iterator<polygon_type> inner_iterator_type;

    struct polygon_rings_begin
    {
        static inline inner_iterator_type apply(polygon_type& polygon)
        {
            return inner_iterator_type(polygon);
        }
    };

    struct polygon_rings_end
    {
        static inline inner_iterator_type apply(polygon_type& polygon)
        {
            return inner_iterator_type(polygon, true);
        }
    };

    typedef flatten_iterator
        <
            typename boost::range_iterator<MultiPolygon>::type,
            inner_iterator_type,
            typename std::iterator_traits<inner_iterator_type>::value_type,
            polygon_rings_begin,
            polygon_rings_end,
            typename std::iterator_traits<inner_iterator_type>::reference
        > rings_iterator_type;

public:
    template <typename BoundaryView>
    static inline void apply(MultiPolygon const& multipolygon,
                             BoundaryView* views)
    {
        rings_iterator_type first(boost::begin(multipolygon),
                                  boost::end(multipolygon));
        rings_iterator_type last(boost::end(multipolygon));

        std::uninitialized_copy(first, last, views);
    }
};


template <typename Areal>
class areal_boundary
{
    typedef boundary_view<typename ring_type<Areal>::type> boundary_view_type;
    typedef views_container_initializer<Areal> exception_safe_initializer;

    template <typename T>
    struct automatic_deallocator
    {
        automatic_deallocator(T* ptr) : m_ptr(ptr) {}

        ~automatic_deallocator()
        {
            operator delete(m_ptr);
        }

        inline void release() { m_ptr = NULL; }

        T* m_ptr;
    };

    inline void initialize_views(Areal const& areal)
    {
        // initialize number of rings
        std::size_t n_rings = num_rings<Areal>::apply(areal);

        if (n_rings == 0)
        {
            return;
        }

        // allocate dynamic memory
        boundary_view_type* views_ptr = static_cast
            <
                boundary_view_type*
            >(operator new(sizeof(boundary_view_type) * n_rings));

        // initialize; if exceptions are thrown by constructors
        // they are handled automatically by automatic_deallocator
        automatic_deallocator<boundary_view_type> deallocator(views_ptr);
        exception_safe_initializer::apply(areal, views_ptr);
        deallocator.release();

        // now initialize member variables safely
        m_views = views_ptr;
        m_num_rings = n_rings;
    }

    // disallow copies and/or assignments
    areal_boundary(areal_boundary const&);
    areal_boundary& operator=(areal_boundary const&);

public:
    typedef boundary_view_type* iterator;
    typedef boundary_view_type const* const_iterator;

    typedef multi_linestring_tag tag_type;

    explicit areal_boundary(Areal& areal)
        : m_views(NULL)
        , m_num_rings(0)
    {
        initialize_views(areal);
    }

    ~areal_boundary()
    {
        boundary_view_type* last = m_views + m_num_rings;
        for (boundary_view_type* it = m_views; it != last; ++it)
        {
            it->~boundary_view_type();
        }
        operator delete(m_views);
    }

    inline iterator begin() { return m_views; }
    inline iterator end() { return m_views + m_num_rings; }
    inline const_iterator begin() const { return m_views; }
    inline const_iterator end() const { return m_views + m_num_rings; }

private:
    boundary_view_type* m_views;
    std::size_t m_num_rings;
};


}} // namespace detail::boundary_view
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace detail_dispatch
{


template <typename Ring>
struct boundary_view<Ring, ring_tag>
    : detail::boundary_views::ring_boundary<Ring>
{
    explicit boundary_view(Ring& ring)
        : detail::boundary_views::ring_boundary<Ring>(ring)
    {}
};

template <typename Polygon>
struct boundary_view<Polygon, polygon_tag>
    : detail::boundary_views::areal_boundary<Polygon>
{
    explicit boundary_view(Polygon& polygon)
        : detail::boundary_views::areal_boundary<Polygon>(polygon)
    {}
};

template <typename MultiPolygon>
struct boundary_view<MultiPolygon, multi_polygon_tag>
    : detail::boundary_views::areal_boundary<MultiPolygon>
{
    explicit boundary_view(MultiPolygon& multipolygon)
        : detail::boundary_views::areal_boundary
            <
                MultiPolygon
            >(multipolygon)
    {}
};


} // namespace detail_dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_VIEWS_DETAIL_BOUNDARY_VIEW_IMPLEMENTATION_HPP

/* implementation.hpp
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
*/