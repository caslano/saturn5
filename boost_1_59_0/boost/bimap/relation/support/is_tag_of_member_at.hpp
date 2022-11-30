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

\brief Metafunction to test if a user tag is referring to the left member.

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

\brief Metafunction to test if a user tag is referring to the left member.

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