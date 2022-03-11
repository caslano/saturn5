// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/map_by.hpp
/// \brief map_by<tag>(b) function

#ifndef BOOST_BIMAP_SUPPORT_MAP_BY_HPP
#define BOOST_BIMAP_SUPPORT_MAP_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/support/map_type_by.hpp>
#include <boost/bimap/relation/detail/access_builder.hpp>


#ifdef BOOST_BIMAP_ONLY_DOXYGEN_WILL_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace support {

/** \brief Gets a map view of a bidirectional map

Convertible to \c map_type_by<Tag,Bimap>::type
Instead of using \c map_type_by<Tag,Bimap>::type this functions use
\b Boost.call_traits to find the best way to return this value. To help
the user of this function the following metafunction is provided
\code

namespace result_of {

template< class Tag, class Bimap >
struct map_by( Bimap & b );

} // namespace result_of

\endcode

See also member_at, value_type_of.
\ingroup bimap_group
                                                                        **/

template< class Tag, class Bimap >
BOOST_DEDUCED_TYPENAME result_of::map_by<Tag,Bimap>::type
    map_by( Bimap & b );

} // namespace support
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_ONLY_DOXYGEN_WILL_PROCESS_THE_FOLLOWING_LINES



#ifndef BOOST_BIMAP_DOXIGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace support {

// Since it is very error-prone to directly write the hole bunch
// of relation accesor. They are buil from litle macro blocks that
// are both more readable, leading to self docummenting code and a
// lot more easier to understand and mantain.
// It is very important to note that the three building blocks have
// to laid in the same namespace in order to work. There is also
// important to keep them in order.
// The forward declaration are not necesary but they help a lot to
// the reader, as they undercover what is the signature of the
// result code.
// In the end, it is not quicker to do it in this way because you
// write a lot. But this code has no complexity at all and almost
// every word writed is for documentation.

// Result of
// -------------------------------------------------------------------------
/*
    namespace result_of {

    template< class Tag, class Bimap >
    struct map_by<Tag,Bimap>;
    {
        typedef -unspecified- type;
    };

    } // namespace result_of

*/

BOOST_BIMAP_SYMMETRIC_ACCESS_RESULT_OF_BUILDER
(
    map_by,
    map_type_by
)

// Implementation
// -------------------------------------------------------------------------

BOOST_BIMAP_SYMMETRIC_ACCESS_IMPLEMENTATION_BUILDER
(
    map_by,
    Bimap,
    b,
    return b.left,
    return b.right
)

// Interface
// --------------------------------------------------------------------------

BOOST_BIMAP_SYMMETRIC_ACCESS_INTERFACE_BUILDER
(
    map_by
)

} // namespace support
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXIGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_SUPPORT_MAP_BY_HPP


/* map_by.hpp
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
*/