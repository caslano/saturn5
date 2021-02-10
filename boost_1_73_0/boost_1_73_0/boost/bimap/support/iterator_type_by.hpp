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
WW1z4sgR/s6v6GNr12KXBezNXZL1+apkIdtKMCKSsM913qJkaTDKCYlIYn3Oxfnt6W5phAQs2LeXo8ogz/T0y9M93T2j7tsGvAUtXjwmwf0sA8VrwVHv8BDe489Rrw1/C+ZwEYdhEN2LhGjVMASmTSERqUg+C7+D4zRlCT9IsyS4W2ZBHIEb+bBMBQQRpPEy8QSP3AWRmzzCNE7maRsegmwGccK/8TIjLvPYD6aB5xKPNriJgIVI5kGWCR8WSfw58PEhm7kZfgnkE4bxA2oHXhz5AS1KiQutm4vsIz3Dhm4pxFOplBf7SLpMM7Qnc1FZYuvexZ9pqsAl5wIQxVngiTaSBCmEyJD4rASzgXWtUKoXusFcJJ0vqYIiK6BIVdBUf4nq/Z+0gdxQycqPveVcRJkrPddFp8RIkMDczUQSuGG6Qp+9RpyrhpT2DUXAC4kgcueCtKqFESq+mmVXBBhNqHjOK05SqdbcfYQ7QVGElsQgIh8nBQUM6jKPMwE5TLjcRyUxFmGKE4yI5JHG0+yBwqGIMUgXwqMIw7UBhV5CsRXlUZamhSW02rkwbLDNM+datXTA55FlXhl9vQ+nNzipg2aObizj/MKBC3PQ1y0b1GEfR4eOZZyOHdOyiU1TtXFxk+fU4Q3oP44s3bbB
*/