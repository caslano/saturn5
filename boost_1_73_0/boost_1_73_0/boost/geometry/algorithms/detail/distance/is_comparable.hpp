// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP
#define BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP

#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/strategies/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


// metafunction to determine is a strategy is comparable or not
template <typename Strategy>
struct is_comparable
    : boost::is_same
        <
            Strategy,
            typename strategy::distance::services::comparable_type
              <
                  Strategy
              >::type
        >
{};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP

/* is_comparable.hpp
jjnkVdO84KM7px/N0GK42YNYZq55666dTM6bs8BdoJsCua/4KUiQZYlMOXB2CNCqiFusIC8sJS6jmuKB3VAo+yi9/rxOrtvZ3YX/GQekOYbuVY0oOrmPMH7hKrH4X1rBZfsv16eX7ROGxHd0mQAe69eddlcakw0XM2VFRZIPHoBYFnGGEbuUAgCTc+YKi9yiMMtevYkO/RxPSSOcsBP9d0kKZBYW8hLjnV/gf7aHr9bW2P6Ef3ans3woptWbh3Q2NrDxv8wBCNZYNRszpDhniBoe2N/hOwcmbB79MmfGaBzPndI1mEn0U93UNlKgPDvzrIoSAXpQ/r9QSwMECgAAAAgALWdKUjM1bGedBAAAdA0AABcACQBjdXJsLW1hc3Rlci9saWIvaHR0cDIuaFVUBQABtkgkYK1XXW/aSBR951dcJS8J8oaGvrS71WoR0CbaFLJ8qBupkjXYYzwrM+OdGQOJ8uP3XBsS0hpQs3WUGHvuuefOuR9DTlWiY5nQVb/T64/C7nR0E15NJrft8KpxigWlZe1aq/nzrgY16egVlr8hLtxLxK01/8jI11uH4SNVP0B9xf0YSYueIY/hOR2HPNJZCQk3LB/4cxgeI/rKsfGfFiO/hvwRbwBjZNfk91bNU09n3XO6fP/+Hf1C
*/