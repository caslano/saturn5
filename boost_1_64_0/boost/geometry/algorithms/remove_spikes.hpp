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
VMG2Uw9FRCMYInrnlH6VjrgKBDSgl0l1z0lBew4C37fBCEJqnQBRD2FjFKJzUiAlQGjlKAi9ORHjzMoRjJfNQAj3Vw5g3HIGQjjMOj3PVy9ketlSw58xlFc2PI0JFw1PwZomPovnlQqgWSAGRiOMeFI1grQpCBdpoCBUvEAOCD3pWNcAiIGLAjBTA52ecHKb9IHYfCG9epjVLU1ie+2skK57Gwjj31AIZhCr0veap0pnkCY5JOOUUKpkc0jHkzoxDUAviEi9JhrCLM8ZAIw40xIKsD3PSS+QesyL9FLlnAsh42KxkJZ0jGAQbN/DQzgbDYKZXxsE28MVwheH9CgE8pdvgtCA5mkwlk1GcsMmETBhAGoFT1lBUrgUkBKuZkL1EJzqIN6ypNOzfTZsYkDCGPEQOj2VRmvnAEp5hliA9vDb2LpJro/laE889M4B0O7drninoQG1KJlvemGqhnxGxKjAq7/iWYUJNNUAQTQ3pKrQrzFM8+GYpSRbAxjVpBbtBtJIhgJAGUgASHWpEPKpApS3eiQ+379EJkm3LuU0CDe5QhBmRW8jV2/EfqoclLUQMSvulgWGWYm3IFh8ZupjYaFP2GSLCmpwxfXKEYznyY/ijnwwamHwsffYGlRikXktcSCIA0sCvp3xRg3tLIoM4R8BoRXZRsMbo0stiPFxO6i22Kk/AjHDyhEoOL1Sjf0V5GfiTS4OyvwnCKXrayMoM5q1IEZ7+vg9jQlJ1Aj4AnoxRSPGOqa4ZQ2gT8iqQfQG4v0FGnGSxJa5AGjK5ilih6WBcDHGBsNFvBpMpw5E7hzVCGoLh0ZQfj+NYAUF8TXiHf0awKgznZ6yxQrBzIxVekaB6fT+KRzH/jA5RWzUDKITVu9CcRFMGJsGcN5dhWjQWqfBClODlCZdsY3tt99GGmgTpPpRq67bSmfeOYaQ2xxByBVUzhxOuykEqdw0RLa3wUVINyo4GFKDaggXmq8hVGh+jiCUg0ZQwfwaQQXzawQXzK8hXJy9hpBx9kEHv82k7W+/zTbSOarGMPKl0nPSpRCUoADAuCN0ekZIOnMoQ67TMyKl0jMCpdJT4qQAlMHRCEr8FIATPkRHKEcv4VFREAQBNYimU4gwYxobiCRmS6WmpiSRk4fYFXhSKo2zUJCYry6shvOIHbarAxE7+RWkrT83xV1WQZjVZAAwemB5B2JbEtLn2wQPifDpVvT5VvT5VgTvjAz7WPNMo4FUL/oZfnWMtfi0GA0hYnNN+tTPiMMHcox42KvTExYzTz/oRj7HhnwkbtJ3B9LgMZ2esFA6PeH41m9yA+7HVGFwBIF+aabic9UsBh4Pqc/RwcjdQxZEjF8KDBOoZTHEmTsjjPxAWBwQEKsXZrW7wDCr1wbTPIOg0kvVQ4RC5whqH53FiKUmB8SnJuI61hDm7I4CcZJHE4mkOzYKQCjeVWUQzJkiFtGXOnoNgrG3BUK84SgHECdGGQR11omvAvZ8eVCgSc8FBRoMFxRolu7zN6aWvRQ2ggnvNAgqvFNDmNGZARDxoAZAxYMW0Qeo6W6XOLPkz7helMqZcoAUby7OF2+++BOOOCzlTzgiXtbiyLiO1rDdDhP9Jl79tBjG9rb6+CXsjkmvzmaRDlcM4tRBItVZBpCeLN4rWgA4ntNO1OYo4DYFjmliUVgDqAWWAiG3/xrBLKwZQG8oHTDm6cUDMp2eWbfTAGLYq9MTYxGT/qREPA00ADRaKJ5CGcjcdkM6M80BPsd0eFosXWEoAJxwszomiKTjIp2e8SFqADFLztMP+mRPaHUjskN7Yv+DTk9sJW91ccB4AwHF5oN0XFuCiTuGgZm3ZtSLxfbCAGsVkixihCfF7EY=
*/