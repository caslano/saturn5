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