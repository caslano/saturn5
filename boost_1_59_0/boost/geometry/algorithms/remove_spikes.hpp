// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2013 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_REMOVE_SPIKES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_REMOVE_SPIKES_HPP

#include <deque>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>

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