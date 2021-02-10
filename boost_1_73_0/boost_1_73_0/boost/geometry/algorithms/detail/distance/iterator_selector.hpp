// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_ITERATOR_SELECTOR_HPP
#define BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_ITERATOR_SELECTOR_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>
#include <boost/geometry/iterators/segment_iterator.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


// class to choose between point_iterator and segment_iterator
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct iterator_selector
{
    typedef geometry::segment_iterator<Geometry> iterator_type;

    static inline iterator_type begin(Geometry& geometry)
    {
        return segments_begin(geometry);
    }

    static inline iterator_type end(Geometry& geometry)
    {
        return segments_end(geometry);
    }
};

template <typename MultiPoint>
struct iterator_selector<MultiPoint, multi_point_tag>
{
    typedef geometry::point_iterator<MultiPoint> iterator_type;

    static inline iterator_type begin(MultiPoint& multipoint)
    {
        return points_begin(multipoint);
    }

    static inline iterator_type end(MultiPoint& multipoint)
    {
        return points_end(multipoint);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_ITERATOR_SELECTOR_HPP

/* iterator_selector.hpp
7Tfty4B6QiuZ0dhLPZN2HtCHuHzzRyrW6wsnfw9IehLZxcbVJFWOnEn8SlhJ+JypSGonYxKOYukiq2Z4UJp8KilRmaTu8PbuevApoFWqopSd3JuCXGqKLKZULCVZGUm1rHzkwnoyCeBwHivn4bDwyugLcEvy0i4c+2B6kTlDYilUJmYgEp5S73P3a6sVFTZD9K3YRK4Vbbd/kfrF007uEMRC3JPJPXlDhZMBsWVACxOrhO8QBC/zYpYplwbP0YBKxy1jycksY1/AKemqsCWNN/IEbEY5Ilaeb85ox1Sr1CxeGEJH9pIUVoMIOsAoNpA5oAKNZEvjcudbio2mpcB7U/Mcb0xGIxg66YzpenxCM+GUC+jL9eRqOJ3Ql85o1BlM7mj4kTqDO3b25/Wgh9QrkFmS69xKB3JLapFnSsYbzp93tRqNU6WjrIglnXD2Qid9kV+kJ7yQ8DSZjvvh4FM5K3ZsOeOlVatJS5EVKDqE+bnzd9gdDjBdRv3BJBxPRv3O5zGtJOcZonqV8cOca1tTkceCRQKlV3reQEMldpOjXEIAhLedW73+x870ZhLuYbh8y5GwgmNvkAY95wDbtET6UcRojMRU3YEEzYokkTbA0IHvNa2gNglyuYjkBdEIAljNrrzxIqNM6jkMVlZ5
*/