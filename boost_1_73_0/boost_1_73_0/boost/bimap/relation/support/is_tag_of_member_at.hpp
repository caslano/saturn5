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
VvBs0a1p/0DskchCT63oz+FkHE2Hk7PT88F0ePxIvGVRVAE6jVOD33CFJ1gOUfw1OBHkChTnCX8euMs6/HE6vnCfzIToIpjEdoB2rMPRWBIfPPObnvDYM333rSgOuzs7r7AEcKPwk05p16i+hJZMuU2Od2poU1wRy3MMrrnZDqmOqnQwqCV5o1L3bqvvE1viSY27tr+pHMsdfkl43pcpjy+mEd4Qh/qjpGq8nVhn3ftNuHKNVdek1gP9Puy14JdfoPkCW0Oc5U3fhXa/oD2lucehjD5otVpV8hi4VnjOOPj9B9EdmCpUkRWojV9twqGk4X8X3G4B9mRKNLtOhoPj4STcQnebCI/rnp2eDQm9ECqG1XBfcOPbCLG5CimknorzHmm+4K7acfiFVI7vKlyS2e5feWmobj9150p5/JV8AjdGG1trI9pk4EXfRziMxh9qJOc5jgs3R/ZhggYxf+iiBXNGrWUffrbXKghrAsIDGJ3xbslXaytpJpdsZSGWnKkif8ioauN+K0Uk1FrpfjPeanuG8+1CRk1agmq4bImXFUGbEZOyee9QvzegBn7noPG98R9QSwMECgAAAAgALWdKUgDw2E5YBwAANRMAACgACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL3By
*/