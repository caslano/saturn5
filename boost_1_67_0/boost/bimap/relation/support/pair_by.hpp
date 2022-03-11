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