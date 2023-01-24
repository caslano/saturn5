// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/map_type_by.hpp
/// \brief Metafunction to access the map view types of a bimap

#ifndef BOOST_BIMAP_SUPPORT_MAP_TYPE_BY_HPP
#define BOOST_BIMAP_SUPPORT_MAP_TYPE_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::support::map_type_by

\brief Metafunction to obtain the map view type of a bimap indexed by one of the sides.

The tag parameter can be either a user defined tag or \c member_at::{side}.
The returned type is signature-compatible with std::pair.

\code

template< class Tag, class Bimap >
struct map_type_by
{
    typedef typename Bimap::{side}_map_type type;
};

\endcode

See also member_at.
\ingroup bimap_group
                                                                    **/

namespace boost {
namespace bimaps {
namespace support {

// Implementation of map type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    map_type_by,
    left_map,
    right_map
)



} // namespace support
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_SUPPORT_MAP_TYPE_BY_HPP


/* map_type_by.hpp
lMhsXCNqe17qWviogboerwHqurqmKeq6MuS8ZGneaWvTZOnHxquMFOLdfYZV7n0QV7lmIS0SKB2UHq8FUZWn9vEilWqL9MfPtEgUj92+nCvAgLo/rA6qYIisYLVWwVtcwWoDWQJ9oVhvP6y3MmEy0acBLqZPnP7HZLDpq6j7WchDP2tLOdYmlrKVADq370yaz195Pn7EYmZ+xOUfMg/PFzY2Imjdm/aHIEqMPWVtcnHEonQJWhQdr7PuJ43XgfYakaZz+V9oxOS8c0oH40HmHcHHKwYWKP4nyQJBKD7Y2b3amEzvmYsgwpbfMuMfa5PkvUvThHM2xuUykPiqH62mgn22wlnIHe0E9QuDqK2A7rA1D6YrIrVpU5Y8bDXMYb9GENfV5dsiFxk4mFGjzIYS4QF7yo/EELx20vqfMATNzHrSP/921uuuRqwyNUBykw6rqHYmG1uLTdtVZDgn7wG6CqDXtoJM5EGyaqwmmVbrRl7EsL7puu+0znF6hiVRz1gk/r9mWD5qGcywCC6F5PVUwZQAi7KZ0bxkADKZS8mUXAoxYcodY0ifkcn5aWxLmUsJ1fGZAfT3ifstpRVlztEy5XAm9GKv25oXtKKNkyNZwtdCGnFEkhmgpUbBnyQbe5dio8JC7tA4LTuqz5DniWeeR18dKyyiSGGRHQHaivktifLZdSyFcuzWM4Ha180qK1RkMvSbFBUJPxgULOVa
*/