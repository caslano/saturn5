// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPLICATES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPLICATES_HPP


#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>

#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template <typename Range, typename Point>
inline void append_with_duplicates(Range& range, Point const& point)
{
#ifdef BOOST_GEOMETRY_DEBUG_INTERSECTION
    std::cout << "  add: ("
        << geometry::get<0>(point) << ", " << geometry::get<1>(point) << ")"
        << std::endl;
#endif
    geometry::append(range, point);
}

template <typename Range, typename Point, typename EqPPStrategy>
inline void append_no_duplicates(Range& range, Point const& point,
                                 EqPPStrategy const& strategy)
{
    if ( boost::empty(range)
      || ! geometry::detail::equals::equals_point_point(geometry::range::back(range),
                                                        point,
                                                        strategy) )
    {
#ifdef BOOST_GEOMETRY_DEBUG_INTERSECTION
        std::cout << "  add: ("
            << geometry::get<0>(point) << ", " << geometry::get<1>(point) << ")"
            << std::endl;
#endif
        geometry::append(range, point);
    }
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPLICATES_HPP

/* append_no_duplicates.hpp
aTX061sCmbnMNs8PoB+zYS5kRWzz+ET4hsyNSeDJF0lfnjhGcPYeOqXQcHba6yAqtdPeCp7VohcZzUyEcg1SZGojcmGb8IWYJ1WLd6KAwO8jyxhiF+MgJEPvgia05REI/JGUB2jLk2JkbAxcgLExUxDvE2DZSv9uvUhhhJfp1ieDxwUuB5woyYdWwvZNZZLTR0QS7q55iujWi9tQ4ghsBySZ3vMVIvUd7m7QRviaytARnY5FJO01sG6VYzbGXocx9moEF10Pr+8HuiP/PvDsBvdbVhY6cWhZDpCyjKYayvuhKHsl5Qn8CBZO4RfIJcUq0vq/Dvq/Jn7/Qwo7Sf9/Ax635I3SE9I0/ygGTdly/Y5NeK5AzCgdFv3yxBQhhIIyMQmZT/g51M7vCEIHMf4nJJd/A/w1gFsseTW9RdjhAA9YCA+4dvUfoOxyKSoSavBSpArJaTJKg/Umrcp1wTFoH7D1W0PJdSqdAz3wlW8v/B2jZaWEbN5F+D7bc9iJbi+Hv+wl8Ge9jC/BapQn5IpHcb6ULa/DXI4kBY1vtEGbjEbj+6LlSFCil8llJYInJdGr0bB5OyFBeQ06gHcKfnxiWLuMQe37GeBpSPRG5MR0A5uc9LbsxThJkAZg/bPD9IP9w5QiopQqestwSKkbmeP0jQC8bhPQiuujcRsypwkv4hQf/5DNAo23cgQCryby8Z8YGaZ1c95xoLelh3A2
*/