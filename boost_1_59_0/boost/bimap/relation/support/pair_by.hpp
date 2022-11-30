// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/pair_by.hpp
/// \brief pair_by<member>(r) function

#ifndef BOOST_BIMAP_RELATION_SUPPORT_PAIR_BY_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_PAIR_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/support/pair_type_by.hpp>
#include <boost/bimap/relation/detail/access_builder.hpp>

#ifdef BOOST_BIMAP_ONLY_DOXYGEN_WILL_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

/** \brief Gets a pair view of the relation.

\ingroup relation_group
                                                                        **/

template< class Tag, class Relation >
BOOST_DEDUCED_TYPENAME result_of::pair_by<Tag,Relation>::type
    pair_by( Relation & rel );

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_ONLY_DOXYGEN_WILL_PROCESS_THE_FOLLOWING_LINES


#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace relation {
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

    template< class Tag, class Relation >
    struct pair_by<Tag,Relation>;
    {
        typedef -unspecified- type;
    };

    } // namespace result_of
*/

BOOST_BIMAP_SYMMETRIC_ACCESS_RESULT_OF_BUILDER
(
    pair_by,
    pair_type_by
)



// Implementation
// -------------------------------------------------------------------------

BOOST_BIMAP_SYMMETRIC_ACCESS_IMPLEMENTATION_BUILDER
(
    pair_by,
    Relation,
    rel,
    return rel.get_left_pair(),
    return rel.get_right_pair()
)

// Interface
// --------------------------------------------------------------------------

BOOST_BIMAP_SYMMETRIC_ACCESS_INTERFACE_BUILDER
(
    pair_by
)

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_DOXIGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_RELATION_SUPPORT_PAIR_BY_HPP

/* pair_by.hpp
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
*/