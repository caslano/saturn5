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
LaR2AIorjznvILry+45G5awMlhuxlG98LszzPBZXGJUhuSjblOXQBcgU+kmzukvApbhwbrcNuFYFJG8ieZLW7MpGekI4b/n0JsNWqPZLBMRyYGyQtz71Q1VLm4tfDbnZ1Jm6AApK0PKkpVf4qEl70CMSTP21d+Yr4qZmKbT6fKcmKEdjaFAJLfoGWcnMThZF2XUEZucXvuTZQKRInxcm0jCChbOL9TMWpZGuArBo8dG/Z1knXqIpskYsp+mnLcfSgLKvQiCZNJhcbIzOA+OkkHMwM0PSTpKz/fIae2EsVufhC+YvnBqt4LP9hfe2Oi36WOQLwPuonDowWPHPdJRf35MJWu+CXWQ723Kc13KW7bQC5PUn98a1F6bwIzQKrEukC1XoxBTcFed0b1Z/MYXhAvQfcC55g4ISZc0Mu/ESzlbWNJij66sH/nNa8gmq9q4OqMFqyAG4TUk5EeogV9ieIWlCek+5yjNX67gvCbxfsl7PqMEyxp4VdAbm+ky51UTrB1cmZTaeeda3PiffUj/2yCbIWK/rzJies/LF7l0skBWIZ11/CLmBUX834g==
*/