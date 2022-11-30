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
// of relation accesor. They are built from little macro blocks that
// are both more readable, leading to self docummenting code and a
// lot more easier to understand and maintain.
// It is very important to note that the three building blocks have
// to laid in the same namespace in order to work. There is also
// important to keep them in order.
// The forward declaration are not necessary but they help a lot to
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