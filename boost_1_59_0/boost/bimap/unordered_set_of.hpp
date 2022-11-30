// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file unordered_set_of.hpp
/// \brief Include support for unordered_set constrains for the bimap container

#ifndef BOOST_BIMAP_UNORDERED_SET_OF_HPP
#define BOOST_BIMAP_UNORDERED_SET_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/detail/user_interface_config.hpp>

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

#include <boost/bimap/views/unordered_map_view.hpp>
#include <boost/bimap/views/unordered_set_view.hpp>

namespace boost {
namespace bimaps {

/// \brief Set Type Specification
/**
This struct is used to specify an unordered_set specification.
It is not a container, it is just a metaprogramming facility to
express the type of a set. Generally, this specification will
be used in other place to create a container.
It has the same syntax that an tr1::unordered_set instantiation,
except that the allocator cannot be specified. The rationale behind
this difference is that the allocator is not part of the
unordered_set type specification, rather it is a container
configuration parameter.
The first parameter is the type of the objects in the set, the
second one is a Hash Functor that takes objects of this type, and
the third one is a Functor that compares them for equality.
Bimap binding metafunctions can be used with this class in
the following way:

\code
using namespace support;

BOOST_STATIC_ASSERT( is_set_type_of< unordered_set_of<Type> >::value )

BOOST_STATIC_ASSERT
(
     is_same
     <
        unordered_set_of<Type,HashFunctor,EqualKey>::index_bind
        <
            KeyExtractor,
            Tag

        >::type,

        hashed_unique< tag<Tag>, KeyExtractor, HashFunctor, EqualKey >

    >::value
)

typedef bimap
<
    unordered_set_of<Type>, RightKeyType

> bimap_with_left_type_as_unordered_set;

BOOST_STATIC_ASSERT
(
    is_same
    <
        unordered_set_of<Type>::map_view_bind
        <
            member_at::left,
            bimap_with_left_type_as_unordered_set

        >::type,

        unordered_map_view
        <
            member_at::left,
            bimap_with_left_type_as_unordered_set
        >

    >::value
)

\endcode

See also unordered_set_of_relation.
                                                                        **/

template
<
    class KeyType,
    class HashFunctor   = hash< BOOST_DEDUCED_TYPENAME 
        ::boost::bimaps::tags::support::value_type_of<KeyType>::type >,
    class EqualKey      = std::equal_to< BOOST_DEDUCED_TYPENAME 
        ::boost::bimaps::tags::support::value_type_of<KeyType>::type >
>
struct unordered_set_of : public ::boost::bimaps::detail::set_type_of_tag
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

        typedef unordered_set_of type; 
    };

    BOOST_BIMAP_GENERATE_INDEX_BINDER_2CP(

        // binds to
        multi_index::hashed_unique,

        // with
        hasher,
        key_equal
    )

    BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(

        // binds to
        views::unordered_map_view
    )

    BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(

        // binds to
        views::unordered_set_view
    )

    typedef mpl::bool_<false> mutable_key;
};


/// \brief Set Of Relation Specification
/**
This struct is similar to unordered_set_of but it is bind logically to
a relation. It is used in the bimap instantiation to specify the
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

See also unordered_set_of, is_set_type_of_relation.
                                                                **/

template
<
    class HashFunctor   = hash< _relation >,
    class EqualKey      = std::equal_to< _relation >
>
struct unordered_set_of_relation : public ::boost::bimaps::detail::set_type_of_relation_tag
{
    /// Hash Functor that takes value_type objects
    typedef HashFunctor     hasher;

    /// Functor that compare two value_type objects for equality
    typedef EqualKey        key_equal;


    BOOST_BIMAP_GENERATE_RELATION_BINDER_2CP(

        // binds to
        unordered_set_of,

        // with
        hasher,
        key_equal
    )

    typedef mpl::bool_<false>  left_mutable_key;
    typedef mpl::bool_<false> right_mutable_key;
};


} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_UNORDERED_SET_OF_HPP


/* unordered_set_of.hpp
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
*/