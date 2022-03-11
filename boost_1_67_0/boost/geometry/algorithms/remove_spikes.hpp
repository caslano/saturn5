// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2013 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_REMOVE_SPIKES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_REMOVE_SPIKES_HPP

#include <deque>

#include <boost/range.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/detail/point_is_spike_or_equal.hpp>
#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/clear.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>


/*
Remove spikes from a ring/polygon.
Ring (having 8 vertices, including closing vertex)
+------+
|      |
|      +--+
|      |  ^this "spike" is removed, can be located outside/inside the ring
+------+
(the actualy determination if it is removed is done by a strategy)

*/


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace remove_spikes
{


struct range_remove_spikes
{
    template <typename Range, typename SideStrategy>
    static inline void apply(Range& range, SideStrategy const& strategy)
    {
        typedef typename point_type<Range>::type point_type;

        std::size_t n = boost::size(range);
        std::size_t const min_num_points = core_detail::closure::minimum_ring_size
            <
                geometry::closure<Range>::value
            >::value - 1; // subtract one: a polygon with only one spike should result into one point
        if (n < min_num_points)
        {
            return;
        }

        std::vector<point_type> cleaned;
        cleaned.reserve(n);

        for (typename boost::range_iterator<Range const>::type it = boost::begin(range);
            it != boost::end(range); ++it)
        {
            // Add point
            cleaned.push_back(*it);

            while(cleaned.size() >= 3
                  && detail::is_spike_or_equal(range::at(cleaned, cleaned.size() - 3),
                                               range::at(cleaned, cleaned.size() - 2),
                                               range::back(cleaned),
                                               strategy))
            {
                // Remove pen-ultimate point causing the spike (or which was equal)
                cleaned.erase(cleaned.end() - 2);
            }
        }

        typedef typename std::vector<point_type>::iterator cleaned_iterator;
        cleaned_iterator cleaned_b = cleaned.begin();
        cleaned_iterator cleaned_e = cleaned.end();
        std::size_t cleaned_count = cleaned.size();

        // For a closed-polygon, remove closing point, this makes checking first point(s) easier and consistent
        if ( BOOST_GEOMETRY_CONDITION(geometry::closure<Range>::value == geometry::closed) )
        {
            --cleaned_e;
            --cleaned_count;
        }

        bool found = false;
        do
        {
            found = false;
            // Check for spike in first point
            while(cleaned_count >= 3
                  && detail::is_spike_or_equal(*(cleaned_e - 2), // prev
                                               *(cleaned_e - 1), // back
                                               *(cleaned_b),     // front
                                               strategy))
            {
                --cleaned_e;
                --cleaned_count;
                found = true;
            }
            // Check for spike in second point
            while(cleaned_count >= 3
                  && detail::is_spike_or_equal(*(cleaned_e - 1), // back
                                               *(cleaned_b),     // front
                                               *(cleaned_b + 1), // next
                                               strategy))
            {
                ++cleaned_b;
                --cleaned_count;
                found = true;
            }
        }
        while (found);

        if (cleaned_count == 2)
        {
            // Ticket #9871: open polygon with only two points.
            // the second point forms, by definition, a spike
            --cleaned_e;
            //--cleaned_count;
        }

        // Close if necessary
        if ( BOOST_GEOMETRY_CONDITION(geometry::closure<Range>::value == geometry::closed) )
        {
            BOOST_GEOMETRY_ASSERT(cleaned_e != cleaned.end());
            *cleaned_e = *cleaned_b;
            ++cleaned_e;
            //++cleaned_count;
        }

        // Copy output
        geometry::clear(range);
        std::copy(cleaned_b, cleaned_e, range::back_inserter(range));
    }
};


struct polygon_remove_spikes
{
    template <typename Polygon, typename SideStrategy>
    static inline void apply(Polygon& polygon, SideStrategy const& strategy)
    {
        typedef range_remove_spikes per_range;
        per_range::apply(exterior_ring(polygon), strategy);

        typename interior_return_type<Polygon>::type
            rings = interior_rings(polygon);

        for (typename detail::interior_iterator<Polygon>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            per_range::apply(*it, strategy);
        }
    }
};


template <typename SingleVersion>
struct multi_remove_spikes
{
    template <typename MultiGeometry, typename SideStrategy>
    static inline void apply(MultiGeometry& multi, SideStrategy const& strategy)
    {
        for (typename boost::range_iterator<MultiGeometry>::type
                it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            SingleVersion::apply(*it, strategy);
        }
    }
};


}} // namespace detail::remove_spikes
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct remove_spikes
{
    template <typename SideStrategy>
    static inline void apply(Geometry&, SideStrategy const&)
    {}
};


template <typename Ring>
struct remove_spikes<Ring, ring_tag>
    : detail::remove_spikes::range_remove_spikes
{};



template <typename Polygon>
struct remove_spikes<Polygon, polygon_tag>
    : detail::remove_spikes::polygon_remove_spikes
{};


template <typename MultiPolygon>
struct remove_spikes<MultiPolygon, multi_polygon_tag>
    : detail::remove_spikes::multi_remove_spikes
        <
            detail::remove_spikes::polygon_remove_spikes
        >
{};


} // namespace dispatch
#endif


namespace resolve_variant {

template <typename Geometry>
struct remove_spikes
{
    template <typename Strategy>
    static void apply(Geometry& geometry, Strategy const& strategy)
    {
        concepts::check<Geometry>();
        dispatch::remove_spikes<Geometry>::apply(geometry, strategy);
    }

    static void apply(Geometry& geometry, geometry::default_strategy const&)
    {
        typedef typename strategy::side::services::default_strategy
            <
                typename cs_tag<Geometry>::type
            >::type side_strategy;

        apply(geometry, side_strategy());
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct remove_spikes<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<void>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy) : m_strategy(strategy) {}

        template <typename Geometry>
        void operator()(Geometry& geometry) const
        {
            remove_spikes<Geometry>::apply(geometry, m_strategy);
        }
    };

    template <typename Strategy>
    static inline void apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& geometry,
                             Strategy const& strategy)
    {
        boost::apply_visitor(visitor<Strategy>(strategy), geometry);
    }
};

} // namespace resolve_variant


/*!
    \ingroup remove_spikes
    \tparam Geometry geometry type
    \param geometry the geometry to make remove_spikes
*/
template <typename Geometry>
inline void remove_spikes(Geometry& geometry)
{
    resolve_variant::remove_spikes<Geometry>::apply(geometry, geometry::default_strategy());
}

/*!
    \ingroup remove_spikes
    \tparam Geometry geometry type
    \tparam Strategy side strategy type
    \param geometry the geometry to make remove_spikes
    \param strategy the side strategy used by the algorithm
*/
template <typename Geometry, typename Strategy>
inline void remove_spikes(Geometry& geometry, Strategy const& strategy)
{
    resolve_variant::remove_spikes<Geometry>::apply(geometry, strategy);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_REMOVE_SPIKES_HPP

/* remove_spikes.hpp
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
*/