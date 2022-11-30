// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/member_with_tag.hpp
/// \brief member_with_tag<tag,relation> metafunction

#ifndef BOOST_BIMAP_RELATION_SUPPORT_MEMBER_WITH_TAG_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_MEMBER_WITH_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/member_at.hpp>
#include <boost/bimap/detail/debug/static_error.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>

/** \struct boost::bimaps::relation::support::member_with_tag

\brief Metafunction to convert user tags to the member_at idiom.

\code

template< class Tag, class Relation >
struct member_with_tag
{
    typedef member_at::{side} type;
};

\endcode

We have to allow that all the metafunctions that works with tags
and retrieves data from a Relation will work with member_at idiom
even if the type was tagged. This will be great for the user,
because he can choose to tag a member after he is using the
relation and the code will still work.

If we perform this check in every metafunction it will be very
tedious and error prone, so instead of that all metafunctions
that works with relations first call this metafunction that
convert the tag to a member_at tag.

See also member_at, is_tag_of_member_at_left, is_tag_of_member_at_right.
\ingroup relation_group
                                                                    **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

template
<
    class Tag,
    class Relation,
    class Enable = void
>
struct member_with_tag
{
    BOOST_BIMAP_STATIC_ERROR( MEMBER_WITH_TAG_FAILURE, (Relation,Tag) );
};

template< class Relation >
struct member_with_tag
<
    member_at::left, Relation, void
>
{
    typedef member_at::left type;
};

template< class Relation >
struct member_with_tag
<
    member_at::right, Relation, void
>
{
    typedef member_at::right type;
};

template< class Relation >
struct member_with_tag
<
    member_at::info, Relation, void
>
{
    typedef member_at::info type;
};


template< class Tag, class Relation >
struct member_with_tag
<
    Tag, Relation,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        mpl::and_
        <
            mpl::not_< is_same<Tag,member_at::left> >,
            is_same
            <
                Tag,
                BOOST_DEDUCED_TYPENAME Relation::left_tag
            >
        >

    >::type
>
{
    typedef member_at::left type;
};

template< class Tag, class Relation >
struct member_with_tag
<
    Tag,
    Relation,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        mpl::and_
        <
            mpl::not_< is_same<Tag,member_at::right> >,
            is_same
            <
                Tag,
                BOOST_DEDUCED_TYPENAME Relation::right_tag
            >
        >

    >::type
>
{
    typedef member_at::right type;
};

template< class Tag, class Relation >
struct member_with_tag
<
    Tag, Relation,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        mpl::and_
        <
            mpl::not_< is_same<Tag,member_at::info> >,
            is_same
            <
                Tag,
                BOOST_DEDUCED_TYPENAME Relation::info_tag
            >
        >

    >::type
>
{
    typedef member_at::info type;
};

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_RELATION_SUPPORT_MEMBER_WITH_TAG_HPP



/* member_with_tag.hpp
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
*/