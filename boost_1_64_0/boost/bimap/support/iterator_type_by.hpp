// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/iterator_type_by.hpp
/// \brief Metafunctions to access the iterator types of a bimap

#ifndef BOOST_BIMAP_SUPPORT_ITERATOR_TYPE_BY_HPP
#define BOOST_BIMAP_SUPPORT_ITERATOR_TYPE_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>
#include <boost/bimap/relation/detail/static_access_builder.hpp>

/** \struct boost::bimaps::support::iterator_type_by

\brief Metafunction to obtain the iterator type of the map view by one of the sides.
These metafunctions can be used outside the bimap framework for other bimap 
signature compatible classes.
\code

template< class Tag, class Bimap >
struct iterator_type_by
{
    typedef -unspecified- type;
};

template< class Tag, class Bimap >
struct const_iterator_type_by
{
    typedef -unspecified- type;
};

template< class Tag, class Bimap >
struct reverse_iterator_type_by
{
    typedef -unspecified- type;
};

template< class Tag, class Bimap >
struct const_reverse_iterator_type_by
{
    typedef -unspecified- type;
};

template< class Tag, class Bimap >
struct local_iterator_type_by
{
    typedef -unspecified- type;
};

template< class Tag, class Bimap >
struct const_local_iterator_type_by
{
    typedef -unspecified- type;
};

\endcode

See also member_at.
\ingroup bimap_group
                                                                    **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace support {

// Implementation of iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    iterator_type_by,
    left_iterator,
    right_iterator
)

// Implementation of const iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    const_iterator_type_by,
    left_const_iterator,
    right_const_iterator
)


// Implementation of reverse iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    reverse_iterator_type_by,
    left_reverse_iterator,
    right_reverse_iterator
)

// Implementation of const reverse iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    const_reverse_iterator_type_by,
    left_const_reverse_iterator,
    right_const_reverse_iterator
)


// Implementation of local iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    local_iterator_type_by,
    left_local_iterator,
    right_local_iterator
)

// Implementation of const local iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    const_local_iterator_type_by,
    left_const_local_iterator,
    right_const_local_iterator
)

} // namespace support
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_SUPPORT_ITERATOR_TYPE_BY_HPP


/* iterator_type_by.hpp
aKGrfqc0tbYs7sVREId3hAlOBAR5x4h5+Iwp4rzqtRTlY+FPw//zYvjW4FFxNHxvh0huqSz4GGN+2oK3djZAH5v5wg/nlay7VR9LJc98KkWgD/tNmxae/F9RtUBl7l48ui1d1wd5Zxpukw91CqrRqTDAwSJDvbtGBJCWUB0jY8rEJ2zoPjV48DMWCvMT5ub8BjWmJUxMCDETOMvZ5ydkSPo341eF0hNyLPcsuDe8GNkqYxvwaDL5WQxwSuIJmHF9fywUsSUiyKk4rWRxsyhgT7k3qSJeD4kG3HKgm0lArfAVqGT29MJbisFS9mY4p/SxSGnLaJjGQP7Yn5Hm6SxP+Q/OTaQOmegK9g7zB/NjZMgYxDrg+4X3jyAH8MOxnmjQfiRyVyxNeGp4JnESgevoxLorYmsxFyvYQ7nk8dcD+a/eRIqu3SpeK5YjvNqbBp9PC7zMSkKPQLqWmK4K/w+hHTT9D7YRMe6qmBRtySuLsiPhk9I1AxK8vRISOscTw2h22peWzMdNxqh/tK1s1JWxm/QpiOR5HhPkUqjSqlQh4WgLI1FumpEd2xssXw==
*/