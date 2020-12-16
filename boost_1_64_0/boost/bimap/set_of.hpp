// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file set_of.hpp
/// \brief Include support for set constrains for the bimap container

#ifndef BOOST_BIMAP_SET_OF_HPP
#define BOOST_BIMAP_SET_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/detail/user_interface_config.hpp>

#include <functional>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/na.hpp>

#include <boost/concept_check.hpp>

#include <boost/bimap/detail/concept_tags.hpp>

#include <boost/bimap/detail/generate_index_binder.hpp>
#include <boost/bimap/detail/generate_view_binder.hpp>
#include <boost/bimap/detail/generate_relation_binder.hpp>

#include <boost/bimap/tags/support/value_type_of.hpp>

#include <boost/multi_index/ordered_index.hpp>

#include <boost/bimap/views/map_view.hpp>
#include <boost/bimap/views/set_view.hpp>

namespace boost {
namespace bimaps {

/// \brief Set Type Specification
/**
This struct is used to specify a set specification.
It is not a container, it is just a metaprogramming facility to
express the type of a set. Generally, this specification will
be used in other place to create a container.
It has the same syntax that an std::set instantiation, except
that the allocator cannot be specified. The rationale behind
this difference is that the allocator is not part of the set
type specification, rather it is a container configuration
parameter.
The first parameter is the type of the objects in the set, and
the second one is a Functor that compares them.
Bimap binding metafunctions can be used with this class in
the following way:

\code
using namespace support;

BOOST_STATIC_ASSERT( is_set_type_of< set_of<Type> >::value )

BOOST_STATIC_ASSERT
(
     is_same
     <
        set_of<Type,KeyCompare>::index_bind
        <
            KeyExtractor,
            Tag

        >::type,

        ordered_unique< tag<Tag>, KeyExtractor, KeyCompare >

    >::value
)

typedef bimap
<
    set_of<Type>, RightKeyType

> bimap_with_left_type_as_set;

BOOST_STATIC_ASSERT
(
    is_same
    <
        set_of<Type>::map_view_bind
        <
            member_at::left,
            bimap_with_left_type_as_set

        >::type,

        map_view< member_at::left, bimap_with_left_type_as_set >

    >::value
)

\endcode

See also set_of_relation.
                                                                        **/

template
<
    class KeyType,
    class KeyCompare = std::less< BOOST_DEDUCED_TYPENAME 
        ::boost::bimaps::tags::support::value_type_of<KeyType>::type >
>
struct set_of : public ::boost::bimaps::detail::set_type_of_tag
{
    /// User type, can be tagged
    typedef KeyType user_type;

    /// Type of the object that will be stored in the set
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

        typedef set_of type;
    };

    BOOST_BIMAP_GENERATE_INDEX_BINDER_1CP(

        // binds to
        multi_index::ordered_unique,

        // with
        key_compare
    )

    BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(

        // binds to
        views::map_view
    )

    BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(

        // binds to
        views::set_view
    )

    typedef mpl::bool_<false> mutable_key;
};


/// \brief Set Of Relation Specification
/**
This struct is similar to set_of but it is bind logically to a
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

See also set_of, is_set_type_of_relation.
                                                                **/

template< class KeyCompare = std::less< _relation > >
struct set_of_relation : public ::boost::bimaps::detail::set_type_of_relation_tag
{
    /// Functor that compare two keys
    typedef KeyCompare key_compare;

    BOOST_BIMAP_GENERATE_RELATION_BINDER_1CP(

        // binds to
        set_of,

        // with
        key_compare
    )

    typedef mpl::bool_<false>  left_mutable_key;
    typedef mpl::bool_<false> right_mutable_key;
};

} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_SET_OF_HPP


/* set_of.hpp
fYI2jgMUR7RGRj83yR3o8e5KkctuB/l31rQjud/M9lxXJcjvjGGe/smyf5XReMz+g51lTfW/QVuWye70TxjkOa/Wz4ti+nnO7eX30h39DfpknLYt/8TvRt3etmhDmZSOFaZ71SMhM5xk9mjzmujOaxn1l/ma+ao+L779Dea0yVqZe6jOgjRlJq9D95B/qOa9oZ/TjDJa+8Vr285ultHtvQv/7dQv48S3RLpT2nMUh2Ug9aVPIduUxpGn5bVhkty+/uD5Pk+V/ePJP0hbpinu9ltLefXT1L08Dx3oOQZ114+1d6d7jHUp+rKYQjLhmufI84anBnnutcj9Oc9zHZGkfy8M0qcDMvr5/c0DPMaWZH1+QvVtCDL6+v/Es0+k6NPzo8Hej34ce4KfZXz+wmVH7cRLU4dy2U3M8BxP5f77LpVLU+27Ksm9ljxAdfyU5r2tLzcrPSNQ0w7076J7PMfkJDkd7w30rEP9eLsvw2BPLUFb9kv09QwZfVqyeF1qdmZ1B5Vphvg2wzFK+16lgaWE+t5ZyJ6ktNi9DM+xOFw11d9XVuc+8cXL7O2nKZq9faRTe98jU9gLNHv9UfH8jXv4twDfB9u2hfswaY83Lj4uKSnJcJ+3cDi9/3nup4ZLFGUxh/zv57Nvz3sjQ0WYMMVsj3IO+d+nvG7ZKdZpm8itos6z70Uk86B+v0akbRf5PyP7x8tz3VfIv5/x2TfP9VY7ZVCqZuvPWZT/waI/DCb51kpdZ92nSWap8VqMyySD4l2iXzeIOMZQHMtEGS8n+SSe68NO/ivkdCfKc48L5B9pfNbN78zrSGatPp2a+V0Teu71dZ51f8FtSH1XP0jxhhrOi8bCvxvJv2N61r2EwrcVZfEzyTcWZXGQ7NeIs+51JH+DyfyBzzOGa/f29pI9UuzbjSL7IdOz8ADy/9F4LOZ8P07p6OQxrgRzWWaT/x5lH37ppe733UVu85W6zsOTuA3+1jNCvlOjORs6Rk+AO0cwgu88rRmhjhuz8wuM77+xzLWGZz7sd4X3feQ7bp5prUrn3+l6YYwDV4BIKwTVtJbPsRinlWViRX+vGu3SrYPxjM7mDPLAYabJ75DYGSk8T1Tnm6Pojq/mvThDt4Z7LdPk7IbHks0UxzeK3eLreXbDMmmUllNWs7OZzfDXrRGSZP+4TPLXrM1n6PZ6u46keZ5mHYC8JCdJMr9e67kOmJHobvuvUl7+bDEcz7nfH6HnPK7I8288J1HuZ94UTy9Fk5buLMNpGU912FSb3lRteu8d6XnWgzrU1M/SUSSjf7+IPZcPKM9R9sPQN6K2n61UnrkiT8+QTKiYK6RT2t6zPCmdCRxx1aHd7EwgYQztF4j9n5foGTF40weI8f4pys8Zq+G7jN93TenZC+S2oJnXtKZ0fCP7a/YHE8n/K0Xyj5fb0krPtpYo++d5+tPsWfXffS3nU67/RG1bHDnS80wALVoj04ny2VJT//o2HUx165DTEiu/1zpQWr7X78GL92cK+Z/RzwtE/Hdm8u9D1P1jqsMIEf84ykelaBd7SH6ZrczyE531xCCuh8jtG1tde9VWiudHq91y3qo+qwE9y9t0rzk40+PMJJbLUIxxn1G8Adq6SND2s7U8fmnqQrdfe2aUp4y+n33DY4dmrNStmUZSPE3qnDNlkUycItepnO+mlN5wbb7jteN2vGe+Y7ntiDE3nJ4TrEmvPt/7RxuML0naPH2Y6fGsJM63aGfNR3qkOYVlRHq2jjLcYxbPSR9DcYi29xDJ+4nwHcleRWNJOMLdR/ZfFbP96O/5eWp7G0XxD7ME8zhylvI1x+pvCbGq4+JccosV66MMsk+0G84/OZ2P0nN2Gc0=
*/