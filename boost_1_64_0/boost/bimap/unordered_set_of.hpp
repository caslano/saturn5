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
Cw7heaNpmPMiTFK9w0RP4TA1f71sGDVfHyLMHynMNsg37Am1PT41UDItjdHy+0K0gY3UBgZR3cUgjrMwe9R4qGxCQ729EFcP1zyoFP7bYLZQf615hd4f7H7I7b6f6oTd31HdQ2q2IaYcp5++XqKmcr3UjK53vahhJ6thl8TXO6z6bcVHYX8YZrcw7MbvtEBr3fMmRCbeaWlWMVcg+yCrqtMoR7zTvN3jMfVpX0lf6yHxzit32eGfRvZ8Go/XF2vH5+06+5PFxnoVL/HYFsGJbwqzGPlbU0pjW1FJTl52ggVxiDFq5mzpPJzl6tZrtbVUe4dwoyvMZfdOg2lMVsuJnqtJ+wFeeLblQNGc9t1S2hPN085yYUZpF/vsL3JabVL6j5TWTz/t5dKfleMS9uFA3jAZzveKK/24mJ5TMXNuvpFuXZbxYT2VWl2Uf6ln+vT6c+X3+MV8Pt/Gw7qA/cF0pO28K20VOdOL8NrD9xNyK4x0RbNchlhjJs5x2tupe6X0XeVysZeqyv/JI69ZIq47LMHivUcqrytk3VnO/j45B8+ZjnM3177JQYe1gcPu7ShS9YcHs8yw6WIs2iG756nujWvW8xgCd7jB/X7XWq3K224LdOp0w9gh6y4W++KLylx7nnL4D93hs/z9/DOc4W0m4SeUSXrXOHxMrgifAtVvToVrPs44vE3i6EVxODRxFLnjCK9PHJEGcexW48ALuD5xXJrjGce37jhO1SeOdwziSMkTcezHOviycRzgOOQ6qeI4bNX3ivB+JuHvpPChmjRcRPi9NJfognU2wvr78Ps4tFkwZBY5/fPUuescChvG7idgaB4zzj13bcF+35KfLl4HlOZDhuLg58eif/6J2nk3+NvGSeOAmP+1oXSnWkmPIt5pDeB2X+TlTR3rtX5G67UTkm7xYD6nqyB/7uNwOyuNM2H0vlPfb6Iv03tqXZn2vbVNsstzct8Cz+/z+7d1PpjGpyr6XgbPy+nT/PweiDLQAYgw/B4Q+m4pnHz2zTL8LhHfhefzQOEvf4PksvqQg/XfHKH8iO+MeHxvPE2407OpPNK5PIbNc0U8EAN6EtgcdJZHlFl5ZBfkz84vm5lrVC6Y/y0Hp1BYP18uJ44rw7ychMxQs3Ji/6XS2U1VvP7s5pd59G4jt2B2e3mBqw+G8TkI7Q9XkJz3ZkuWl3ym06CK3Ek2mN2yK51ut0OuQsj6woSSrLeQpbNakl3lFWaZJWQdMC1kWXa7lWSXQXa6kA2EiSFZL1WW3LaS7CLIThCyoTBxsiy7PUWy5ZDNFLLhMD3kNLDbKZK9DrIDhWwkTAbJ+qmy5PZXks3xCrWkCdkomFEk20DI0jpzLtxQtgmWcCEbDZMty7JbGsl2RxoaefEZClaeXN9ojeoZT6yH29OWRA83RUnxcOur9PKMT0nzjE/J8IzPOsgzPuswDze0TMnNObc4q9XLWVwa55pz4BuPchtO0LfhIioju6YNp1DZR4szSTvMAHJLFG6+MNeTW5hwc8DcoXMLhNnFbnJbuo+ea1PlyO2oTi4cZrtGjs8LdXKRMHsgJ85R2e1HkkvQnBcekONjt9i5Ij7Rdo7Icuw2mOQixXlhpmddWbIM2tJkg7Y0zaAt5Rm0pUKDtlRk0JZKDdpShUFbqtK1myxN+1jg0T42zhd9HufEfD5N4U96LVf628Ok8WwulVmyYsedd7ntFM511YMq6wtTTbJJkO0GWfeYdjvJhlgipPFsBcl2h+xjOMXGu1sa13aSfIDmzHqd3KbZ7SDJNSS3Ij7H7kZ5a6e6URtsSHInyG02uyWQXKzmzDqJ3FKFHLlT2NNCLhKmA7mdUc/PyS2awmapZ/TUBmM=
*/