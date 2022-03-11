// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/is_tag_of_member_at.hpp
/// \brief is_tag_of_member_at<tag,relation> metafunction

#ifndef BOOST_BIMAP_RELATION_SUPPORT_IS_TAG_OF_MEMBER_AT_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_IS_TAG_OF_MEMBER_AT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/member_at.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/bimap/relation/support/member_with_tag.hpp>

/** \struct boost::bimaps::relation::support::is_tag_of_member_at_left

\brief Metafunction to test if a user tag is refering to the left member.

\code

template< class Tag, class Relation >
struct is_tag_of_member_at_left : {true_|false_} {};

\endcode

This metafunction is somewhat redundant with member_with_tag, but it is included
because it is a lot easier to metaprogram with it. The result type is the
same that:

\code

 is_same< member_with_tag<Tag,Relation>::type , member_at::left >::type

\endcode

See also member_with_tag, member_at, is_tag_of_member_at_right.
\ingroup relation_group
                                                                             **/


/** \struct boost::bimaps::relation::support::is_tag_of_member_at_right

\brief Metafunction to test if a user tag is refering to the left member.

\code

template< class Tag, class Relation >
struct is_tag_of_member_at_right : {true_|false_} {};

\endcode

This metafunction is somewhat redundat with member_with_tag, but it is included
because it is a lot easier to metaprogram with it. The result type is the
same that:

\code

 is_same< member_with_tag<Tag,Relation>::type , member_at::right >::type

\endcode

See also member_with_tag, member_at, is_tag_of_member_at_left.
\ingroup relation_group
                                                                             **/


#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

// Metafunction is_tag_of_member_at_left
// Easiear metaprogramming

template
<
    class Tag,
    class Relation,
    class Enable = void
>
struct is_tag_of_member_at_left :
    ::boost::mpl::false_ {};

template< class Tag, class Relation >
struct is_tag_of_member_at_left
<
    Tag, Relation,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        is_same
        <
            BOOST_DEDUCED_TYPENAME member_with_tag<Tag,Relation>::type,
            member_at::left
        >

    >::type
> :
    ::boost::mpl::true_ {};

// Metafunction is_tag_of_member_at_right
// Easiear metaprogramming

template
<
    class Tag,
    class Relation,
    class Enable = void
>
struct is_tag_of_member_at_right :
    ::boost::mpl::false_ {};

template< class Tag, class Relation >
struct is_tag_of_member_at_right
<
    Tag, Relation,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        is_same
        <
            BOOST_DEDUCED_TYPENAME member_with_tag<Tag,Relation>::type,
            member_at::right
        >

    >::type
> :
    ::boost::mpl::true_ {};


// Metafunction is_tag_of_member_at_info
// Easiear metaprogramming

template
<
    class Tag,
    class Relation,
    class Enable = void
>
struct is_tag_of_member_at_info :
    ::boost::mpl::false_ {};

template< class Tag, class Relation >
struct is_tag_of_member_at_info
<
    Tag, Relation,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        is_same
        <
            BOOST_DEDUCED_TYPENAME member_with_tag<Tag,Relation>::type,
            member_at::info
        >

    >::type
> :
    ::boost::mpl::true_ {};

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_RELATION_SUPPORT_IS_TAG_OF_MEMBER_AT_HPP



/* is_tag_of_member_at.hpp
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
*/