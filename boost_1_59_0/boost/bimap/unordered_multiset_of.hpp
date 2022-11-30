// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file unordered_multiset_of.hpp
/// \brief Include support for unordered_multiset constrains for the bimap container

#ifndef BOOST_BIMAP_UNORDERED_MULTISET_OF_HPP
#define BOOST_BIMAP_UNORDERED_MULTISET_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/detail/user_interface_config.hpp>

#include <cstdlib>
#include <functional>
#include <boost/functional/hash.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/concept_check.hpp>

#include <boost/bimap/detail/concept_tags.hpp>

#include <boost/bimap/tags/support/value_type_of.hpp>

#include <boost/bimap/detail/generate_index_binder.hpp>
#include <boost/bimap/detail/generate_view_binder.hpp>
#include <boost/bimap/detail/generate_relation_binder.hpp>

#include <boost/multi_index/hashed_index.hpp>

#include <boost/bimap/views/unordered_multimap_view.hpp>
#include <boost/bimap/views/unordered_multiset_view.hpp>

namespace boost {
namespace bimaps {


/// \brief Set Type Specification
/**
This struct is used to specify an unordered_multiset specification.
It is not a container, it is just a metaprogramming facility to
express the type of a set. Generally, this specification will
be used in other place to create a container.
It has the same syntax that an tr1::unordered_multiset instantiation,
except that the allocator cannot be specified. The rationale behind
this difference is that the allocator is not part of the
unordered_multiset type specification, rather it is a container
configuration parameter.
The first parameter is the type of the objects in the set, the
second one is a Hash Functor that takes objects of this type, and
the third one is a Functor that compares them for equality.
Bimap binding metafunctions can be used with this class in
the following way:

\code
using namespace support;

BOOST_STATIC_ASSERT( is_set_type_of< unordered_multiset_of<Type> >::value )

BOOST_STATIC_ASSERT
(
     is_same
     <
        compute_index_type
        <
            unordered_multiset_of<Type,HashFunctor,EqualKey>,
            KeyExtractor,
            Tag

        >::type
        ,
        hashed_nonunique< tag<Tag>, KeyExtractor, HashFunctor, EqualKey >

    >::value
)

typedef bimap
<
    unordered_multiset_of<Type>, RightKeyType

> bimap_with_left_type_as_unordered_multiset;

BOOST_STATIC_ASSERT
(
    is_same
    <
        compute_map_view_type
        <
            member_at::left,
            bimap_with_left_type_as_unordered_multiset

        >::type,

        unordered_multimap_view
        <
            member_at::left,
            bimap_with_left_type_as_unordered_multiset
        >

    >::value
)

\endcode

See also unordered_multiset_of_relation.
                                                                        **/

template
<
    class KeyType,
    class HashFunctor   = hash< BOOST_DEDUCED_TYPENAME 
        ::boost::bimaps::tags::support::value_type_of<KeyType>::type >,
    class EqualKey      = std::equal_to< BOOST_DEDUCED_TYPENAME 
        ::boost::bimaps::tags::support::value_type_of<KeyType>::type >
>
struct unordered_multiset_of : public ::boost::bimaps::detail::set_type_of_tag
{
    /// User type, can be tagged
    typedef KeyType user_type;

    /// Type of the object that will be stored in the container
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::tags::support::
        value_type_of<user_type>::type value_type;

    /// Hash Functor that takes value_type objects
    typedef HashFunctor     hasher;

    /// Functor that compare two value_type objects for equality
    typedef EqualKey        key_equal;

    struct lazy_concept_checked
    {
        BOOST_CLASS_REQUIRE ( value_type,
                              boost, AssignableConcept );

        BOOST_CLASS_REQUIRE3( hasher, std::size_t, value_type,
                              boost, UnaryFunctionConcept );

        BOOST_CLASS_REQUIRE4( key_equal, bool, value_type, value_type,
                              boost, BinaryFunctionConcept );

        typedef unordered_multiset_of type;
    };

    BOOST_BIMAP_GENERATE_INDEX_BINDER_2CP(

        // binds to
        multi_index::hashed_non_unique,

        // with
        hasher,
        key_equal
    )

    BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(

        // binds to
        views::unordered_multimap_view
    )

    BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(

        // binds to
        views::unordered_multiset_view
    )

    typedef mpl::bool_<false> mutable_key;
};


/// \brief Set Of Relation Specification
/**
This struct is similar to unordered_multiset_of but it is bind logically
to a relation. It is used in the bimap instantiation to specify the
desired type of the main view. This struct implements internally
a metafunction named bind_to that manages the quite complicated
task of finding the right type of the set for the relation.

\code
template<class Relation>
struct bind_to
{
    typedef -unspecified- type;
};
\endcode

See also unordered_multiset_of, is_set_type_of_relation.
                                                                **/

template
<
    class HashFunctor   = hash< _relation >,
    class EqualKey      = std::equal_to< _relation >
>
struct unordered_multiset_of_relation : public ::boost::bimaps::detail::set_type_of_relation_tag
{
    /// Hash Functor that takes value_type objects
    typedef HashFunctor     hasher;

    /// Functor that compare two value_type objects for equality
    typedef EqualKey        key_equal;


    BOOST_BIMAP_GENERATE_RELATION_BINDER_2CP(

        // binds to
        unordered_multiset_of,

        // with
        hasher,
        key_equal
    )

    typedef mpl::bool_<false>  left_mutable_key;
    typedef mpl::bool_<false> right_mutable_key;
};


} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_UNORDERED_MULTISET_OF_HPP


/* unordered_multiset_of.hpp
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
*/