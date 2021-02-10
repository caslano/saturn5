// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file unconstrained_set_of.hpp
/// \brief Include support for set constrains for the bimap container

#ifndef BOOST_BIMAP_UNCONSTRAINED_SET_OF_HPP
#define BOOST_BIMAP_UNCONSTRAINED_SET_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/detail/user_interface_config.hpp>

#include <boost/mpl/bool.hpp>

#include <boost/concept_check.hpp>

#include <boost/bimap/detail/concept_tags.hpp>

#include <boost/bimap/tags/support/value_type_of.hpp>

#include <boost/bimap/detail/generate_index_binder.hpp>
#include <boost/bimap/detail/generate_view_binder.hpp>
#include <boost/bimap/detail/generate_relation_binder.hpp>

#include <boost/bimap/views/unconstrained_map_view.hpp>
#include <boost/bimap/views/unconstrained_set_view.hpp>

namespace boost {
namespace bimaps {

/// \brief Set Type Specification
/**
This struct is used to specify a set specification.
It is not a container, it is just a metaprogramming facility to
express the type of a set. Generally, this specification will
be used in other place to create a container.
The first parameter is the type of the objects in the set.

\code

using namespace support;

BOOST_STATIC_ASSERT( is_set_type_of< unconstrained_set_of<Type> >::value )

\endcode

See also unconstrained_set_of_relation.
                                                                        **/

template
<
    class KeyType
>
struct unconstrained_set_of : public ::boost::bimaps::detail::set_type_of_tag
{
    /// User type, can be tagged
    typedef KeyType user_type;

    /// Type of the object that will be stored in the container
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::tags::support::
        value_type_of<user_type>::type value_type;

    struct lazy_concept_checked
    {
        BOOST_CLASS_REQUIRE ( value_type,
                              boost, AssignableConcept );

        typedef unconstrained_set_of type;
    };

    BOOST_BIMAP_GENERATE_INDEX_BINDER_FAKE

    BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(

        // binds to
        views::unconstrained_map_view
    )

    BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(

        // binds to
        views::unconstrained_set_view
    )

    typedef mpl::bool_<true> mutable_key;
};

/// \brief Set Of Relation Specification
/**
This struct is similar to unconstrained_set_of but it is bind
logically to a relation. It is used in the bimap instantiation to
specify the desired type of the main view.

See also unconstrained_set_of, is_set_type_of_relation.
                                                                **/

struct unconstrained_set_of_relation : public ::boost::bimaps::detail::set_type_of_relation_tag
{

    BOOST_BIMAP_GENERATE_RELATION_BINDER_0CP(

        // binds to
        unconstrained_set_of
    )

    typedef mpl::bool_<true>  left_mutable_key;
    typedef mpl::bool_<true> right_mutable_key;
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace detail {

template<class T>
struct is_unconstrained_set_of :
    ::boost::mpl::false_ {};

template<class T>
struct is_unconstrained_set_of< unconstrained_set_of<T> > :
    ::boost::mpl::true_ {};

} // namespace detail

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

} // namespace bimaps
} // namespace boost


/** \struct boost::bimaps::detail::is_unconstrained_set_of
\brief Trait to check if a type is unconstrained_set_of.
\code
template< class T >
struct is_unconstrained_set_of;
\endcode
                                                                            **/


#endif // BOOST_BIMAP_UNCONSTRAINED_SET_OF_HPP


/* unconstrained_set_of.hpp
syJp1lY07GLacyL29jbo+8RRAj4CmyopUFAOLdhVnBPveLfX7jZC+Wsj2PG+Qew2oKYuMy0SaqKykuRD1IoSScLR67EO50onrFEhctlzPAHtGlkkLHj3ARmvJsKKNalzb8B5GMa737CR5X8/A1cSHxr4tHGBy8foX5Ori2g6uXp/dn48nZw+YbKpZ4xejY1WA5HknSxwrg1A47cC2mRLKqRM5PcJulP5jEd8Ms97wkmjRKb+kpBjLGC3qQZy5dBzVeBwBq3D5z0djEYD1AU2aoeihbY7vssuRGFbHzcKq624SJQljOu12wEXV8eqBatjhHB6ffMzTUAvL66nKwVt1Rlp0aZc+jc+X1xOIzwQiFXHWywWobwXgGcZxjofNqUQxrdqI5JPi/vn5OrXi+tJQAfvVrY+w/F2Or18Ozk+nVwFnWD8b9ren72fsK8B+YToHLYDCuSLB4teFzkC6mJAhx79lSVtEe9t4OuKDYMIxG5ueURaQyjD/p3I3BNNZex3GbOreMzHiOaPhOn1cYIWnRtgit7gj85jvlvKG/KOrWmCmDxk9JxpwiHDA8iYjLcXF5Wy8sGqvI9l2bUxF/cpF+DgYLySm2mkurPC+bS5+ebUlVFvr1HbHz9cd5of23DK+2tRLjSYGYEdyrrB
*/