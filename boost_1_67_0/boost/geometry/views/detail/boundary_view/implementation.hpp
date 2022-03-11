// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, 2018, Oracle and/or its affiliates.

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
#include <utility>
#include <vector>

#include <boost/core/addressof.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/iterators/flatten_iterator.hpp>

#include <boost/geometry/util/range.hpp>

#include <boost/geometry/views/closeable_view.hpp>
#include <boost/geometry/views/detail/boundary_view/interface.hpp>

#include <boost/geometry/algorithms/num_interior_rings.hpp>


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
            typename boost::remove_reference
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
            typename boost::remove_reference
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
            = boost::is_convertible<OtherPolygon, Polygon>::value;

        BOOST_MPL_ASSERT_MSG((is_convertible),
                             NOT_CONVERTIBLE,
                             (types<OtherPolygon>));
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
    typedef typename boost::mpl::if_
        <
            boost::is_const<MultiPolygon>,
            typename boost::range_value<MultiPolygon>::type const,
            typename boost::range_value<MultiPolygon>::type
        >::type polygon_type;

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