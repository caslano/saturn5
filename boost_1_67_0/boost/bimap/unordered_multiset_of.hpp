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