// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file multiset_of.hpp
/// \brief Include support for multiset constrains for the bimap container

#ifndef BOOST_BIMAP_MULTISET_OF_HPP
#define BOOST_BIMAP_MULTISET_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/detail/user_interface_config.hpp>

#include <functional>
#include <boost/mpl/bool.hpp>

#include <boost/concept_check.hpp>

#include <boost/bimap/detail/concept_tags.hpp>

#include <boost/bimap/tags/support/value_type_of.hpp>

#include <boost/bimap/detail/generate_index_binder.hpp>
#include <boost/bimap/detail/generate_view_binder.hpp>
#include <boost/bimap/detail/generate_relation_binder.hpp>

#include <boost/multi_index/ordered_index.hpp>

#include <boost/bimap/views/multimap_view.hpp>
#include <boost/bimap/views/multiset_view.hpp>

namespace boost {
namespace bimaps {

/// \brief Set Type Specification
/**
This struct is used to specify a multiset specification.
It is not a container, it is just a metaprogramming facility to
express the type of a set. Generally, this specification will
be used in other place to create a container.
It has the same syntax that an std::set instantiation, except
that the allocator cannot be specified. The rationale behind
this difference is that the allocator is not part of the set
type specification, rather it is a container configuration
parameter.
The first parameter is the type of the objects in the multiset,
and the second one is a Functor that compares them.
Bimap binding metafunctions can be used with this class in
the following way:

\code
using namespace support;

BOOST_STATIC_ASSERT( is_set_type_of< multiset_of<Type> >::value )

BOOST_STATIC_ASSERT
(
     is_same
     <
        compute_index_type
        <
            multiset_of<Type,KeyCompare>,
            KeyExtractor,
            Tag

        >::type
        ,
        ordered_nonunique< tag<Tag>, KeyExtractor, KeyCompare >

    >::value
)

typedef bimap
<
    multiset_of<Type>, RightKeyType

> bimap_with_left_type_as_multiset;

BOOST_STATIC_ASSERT
(
    is_same
    <
        compute_map_view_type
        <
            member_at::left,
            bimap_with_left_type_as_multiset

        >::type,
        multimap_view< member_at::left, bimap_with_left_type_as_multiset >

    >::value
)

\endcode

See also multiset_of_relation.
                                                                        **/

template
<
    class KeyType,
    class KeyCompare = std::less< BOOST_DEDUCED_TYPENAME
        ::boost::bimaps::tags::support::value_type_of<KeyType>::type >
>
struct multiset_of : public ::boost::bimaps::detail::set_type_of_tag
{
    /// User type, can be tagged
    typedef KeyType user_type;

    /// Type of the object that will be stored in the multiset
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::tags::support::
        value_type_of<user_type>::type value_type;

    /// Functor that compare two keys
    typedef KeyCompare key_compare;

    struct lazy_concept_checked
    {
        BOOST_CLASS_REQUIRE ( value_type,
                              boost, AssignableConcept );

        BOOST_CLASS_REQUIRE4( key_compare, bool, value_type, value_type,
                              boost, BinaryFunctionConcept );

        typedef multiset_of type;
    };

    BOOST_BIMAP_GENERATE_INDEX_BINDER_1CP(

        // binds to
        multi_index::ordered_non_unique,

        // with
        key_compare
    )

    BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(

        // binds to
        views::multimap_view
    )

    BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(

        // binds to
        views::multiset_view
    )

    typedef mpl::bool_<false> mutable_key;
};


/// \brief Set Of Relation Specification
/**
This struct is similar to multiset_of but it is bind logically to a
relation. It is used in the bimap instantiation to specify the
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

See also multiset_of, is_set_type_of_relation.
                                                                **/

template< class KeyCompare = std::less< _relation > >
struct multiset_of_relation : public ::boost::bimaps::detail::set_type_of_relation_tag
{
    /// Functor that compare two keys
    typedef KeyCompare key_compare;


    BOOST_BIMAP_GENERATE_RELATION_BINDER_1CP(

        // binds to
        multiset_of,

        // with
        key_compare
    )

    typedef mpl::bool_<false>  left_mutable_key;
    typedef mpl::bool_<false> right_mutable_key;
};

} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_MULTISET_OF_HPP

/* multiset_of.hpp
ryvulZTeVpp4zkrxtHfG0Bt/XaY+b3f1a008MY3d5ZdK9XDR+bdfXfFkU3rCKB61bRVxPLYWzpjs3l6oiLrimE9paURxtOY49jXmOvBK5CbqbFmoB1uwcb547B5A6Wks1irhl1mrTNPNEQrF3lq55n1o54jKrNA7AY4FnfOZ3b35faj7jnuFukcmxmtVtqPo52+RvZ/VPc9ZIN4f75LfXNF/EVZ8Q1Rpy3eBeI+kFJTc41T3QVr3eNU9Suseq7pvANXfcmyPdJt72WxXWc9/33sFsvxvmtMcMqszvptzQtQZly/cToEoQ3Gvr1TsS6CcONwgt5u4DxTldosXd62FG5WNdl7bhb893wBpBb3BRpA9lMbtgH/HYDQnGjGY2jm3BzXMWNEe5pH/RKqLNNgN5r8cJkIxWAux3ylv932wAvFuCgK/J38/2NNJ/meyv+sryYv3YzH8g/rSbxpIPgv2HmSvleXjsuNSRfzfkL/VIj9f9n9B9RfvqRmJBbHuceBSOo3psn/3gni3/y8DaG6NOhL+ya4nuGXKM2h/UpZJKUjSyjTt54rHY17J84Yb6DkTbT0szaS8zEiQ3+OfU9l9YJXymiDPu1pTXvspUvi47Hh3XfiLshD+qbK/xbOsYuWyakBl5ZDzGVfQHTFI+Xykvz6fkEly+z9N+YyQ/RPk8u6ZwfvYcn2lastyi0edoM7itOk42t+jTpKQVk08n1CdBGrrNjk7IUWSyejnEU9qQQLL8Nz8bZKZYzz/53dEYX/Kt01ux/KctiuV/aNWTbkluuv+TXpGiabc5LoJGsDvf9k/QVsmp7lMNH0hzu2/KcPAP9Htf3ygR1+JQxpEHq+jNDaR/ePlNL5M8TfUpjFVW949KY2tNXWrz0fLQfp0FsZq/Ok53mLM6zqY93VVHaTUjtuKb50upPjexj0Jm1jT/dqX3HykZ2jSMJPibCzenafpmU9Y1TXMMsrHWHtd67XbqTzD5P7aXZ6Tf0X9vZddU97x7nY3lp7xvKY/6ssqybP9xunL/CiVRyNtvcVJfWCAvt7hn+D2r6G8Y+4n+ev7bDjJ+GjqVd/Xovrz+lTqs/Jz3ud6l/urvt8Hecqk4DmatOzI8OzT+vF6jYGMPr3fSGNdBadHXvNfoPp7zSqPp3J+kgbo2zH8U93rus/Jf4Yil4fcnzZ7jrXJsn9b7q+a8krU5nMrv5fk8tKPk+WUjkBNWejbUJdBFI/p3kMJ9ZfOYqyooed+oqhtfRz5NxXry8FU/mu9jPYigtX8ufq5l91yya4+J2Wwvk7QY6Q+14769QBF9pfnC7eQv49F7pPyOzLP6B2Z5F7z9qU6GaipE/n99sAg8TtZUZZynb3O7ddwf4Xb1SqqD4c8D0iU83CX55woWfafYJSHZPcexj6Kv5m2v3d3p9GP2lWwZhzXzwMu6NseZPTzpoX9PN/1+n6YRGNTA838TH4nzaPyaq4ZV/TPiRng2Zf1MqkDScZjzyqYx9phVK832xtgvNXtS4k4Fqjlwm2tKJ3s+CX+fKET+wLl+VMvh+VeL3UOvWEgj7+8D1dGMoXehvtbPF8IojALFcP9LX7WL/14/OHn/J7CnFXk+aPcLpb09RgL4vXl1CLdoywT9TIfiPevNKbESfsoPFbI9aEflwqM6qy7dsyZxmOXPN+V51wf0/i7VO4n3eW9uhaU3ySb5v2a4o5/wCCP92KC3PY+HCDar/DXvyP2Unk11LzT5LIYO9BznqrvA19xeRrvU/KcZrDoJ2JuL++HfpBG461mzJD3EDtSWVTJbUO8y4LBxuQ/D/Z0SlNfst/lK48hcr5u47qRxxC57OZTf2qiybe+HQV4xpEij5U2o3c=
*/