// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file vector_of.hpp
/// \brief Include support for vector constrains for the bimap container

#ifndef BOOST_BIMAP_VECTOR_OF_HPP
#define BOOST_BIMAP_VECTOR_OF_HPP

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

#include <boost/multi_index/random_access_index.hpp>

#include <boost/bimap/views/vector_map_view.hpp>
#include <boost/bimap/views/vector_set_view.hpp>

namespace boost {
namespace bimaps {


/// \brief Set Type Specification
/**
This struct is used to specify a set specification.
It is not a container, it is just a metaprogramming facility to
express the type of a set. Generally, this specification will
be used in other place to create a container.
It has the same syntax that an std::vector instantiation, except
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

BOOST_STATIC_ASSERT( is_set_type_of< vector_of<Type> >::value )

BOOST_STATIC_ASSERT
(
     is_same
     <
        vector_of<Type>::index_bind
        <
            KeyExtractor,
            Tag

        >::type,

        random_access< tag<Tag>, KeyExtractor >

    >::value
)

typedef bimap
<
    vector_of<Type>, RightKeyType

> bimap_with_left_type_as_vector;

BOOST_STATIC_ASSERT
(
    is_same
    <
        vector_of<Type>::map_view_bind
        <
            member_at::left,
            bimap_with_left_type_as_vector

        >::type,

        vector_map_view< member_at::left, bimap_with_left_type_as_vector >

    >::value
)

\endcode

See also vector_of_relation.
                                                                        **/

template< class Type >
struct vector_of : public ::boost::bimaps::detail::set_type_of_tag
{
    /// User type, can be tagged
    typedef Type user_type;

    /// Type of the object that will be stored in the vector
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::tags::support::
        value_type_of<user_type>::type value_type;


    struct lazy_concept_checked
    {
        BOOST_CLASS_REQUIRE ( value_type,
                              boost, AssignableConcept );

        typedef vector_of type;
    };

    BOOST_BIMAP_GENERATE_INDEX_BINDER_0CP_NO_EXTRACTOR(

        // binds to
        multi_index::random_access
    )

    BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(

        // binds to
        views::vector_map_view
    )

    BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(

        // binds to
        views::vector_set_view
    )

    typedef mpl::bool_<true> mutable_key;
};


/// \brief Set Of Relation Specification
/**
This struct is similar to vector_of but it is bind logically to a
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

See also vector_of, is_set_type_of_relation.
                                                                **/

struct vector_of_relation : public ::boost::bimaps::detail::set_type_of_relation_tag
{
    BOOST_BIMAP_GENERATE_RELATION_BINDER_0CP(

        // binds to
        vector_of
    )

    typedef mpl::bool_<true>  left_mutable_key;
    typedef mpl::bool_<true> right_mutable_key;
};


} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_VECTOR_OF_HPP


/* vector_of.hpp
yG26KkduP1DYGE0b7ERyZWpYcgul99Bk0S7H6Op4n0WuY4wNsahj6f30EcV5t0i3HeZTya0J1805duM8U/l/LbmVcLl+w25yuf4guRVzef3EbmFSP36V3O5CeqcI9yiYM+S+Dmf044R7NEwTet/mI33jabzzVcy/IbW2gtoFyW3TtHv+drvU7n+lNnST1YY77fLYOJnqpLHmboYvpc2meY9XkFwLr0jLBbv8Hu/FsnKbX79QtGGUDb/vKXy5VW7rD5JcoFrW5BZJcpVWua3vk+Jrwm4tSW6RVa6nCEpLP04Lj8EcVr7H0ZrCLrFSfOzWnMIOh5z0fpfDslsUyY1T75mQ23KKr71IcyTMp1LYQu4n7UiurZXCsluj+fw7Tun9f5HCNtaM6T9T2EkKx0duIRT2Bs18wEp9Z7M1V/mDpp9tozhniz4VbTDWd9b1szWad3CV0KVdjeeLu1W8nxDMa7avKPxnXinKCrtzPrsIfn703pri01CsleiTIe57x/P495u8X15McUz1fsdyvZd6b21wJbczPo8OJPt4nwzcp3avwaaLfY2e5O9PZ28OrFlOlKnru+oj/r7OrUj+lhT7ny9Tz9Oqb3LYcW+jE+9dsL9vubqmrN5J60Z271wu4l2KI2GK2l+9f8IyuyHzIK2bb77W39u/rX8bby9bjH8MRLNtDluu5psnyF+1lD91LfznBZR/w2+g3Ex1u4Hv+8LHaYeknM7znAbbTQ/5d8ODq2/Dk6vXG8Z3gp61WRM+tEK9Q3NTUz4xz+D9HVGGiRXq2fqyR5wyffg8PYn9S93+8dg/gIhzm8iKf3jjf7eLr7+jBb5A19oZNp7DblOfP27pOw77BIfNF0FI3otDqS7aejukhstbOkjOz4eq+7AlbzsaZDoaBOAGgEUb9pKa3pwlC2gPgN3DK9m9x5JgR8c+FjmdG+D3oGsf7HNHU2/bAG8rUuaf7N/Pv7W3D+4Q+LfDvkdX5LZE+60bbtdjKvk3Atzu+5Hd27CeJtCY8KamjM+rz7fW4MEhuOLgfPw4/1w8tfpPvt4+aKhP4MMNXZo57JjrG8YbXemanzjj7YN1dUO4bdXpvocR/94h7DAG3/Q7cZlv+h2FP8YkWmsHWj3X5eFW43V5lFWzLie3s+IeBNa3LBerqG60jiC3LEXICZ34+0TYBcLNVw4bS3sqeNeKbwKSzBp3OPHManf8ceoey9kK7Z7Kt/i3M7+ZnUFl+30PZiyx235Jz03eMfuD5ByM+V2d7pfeecb3rhtq1gw8/X3OzEltkcGh3ZzuX/wuamOXw7Mv/Z29M4Gvorjj+HsJgQQCJAEChAABAgRIOEJAEITIoVxK5JCggRByQDAXSUCuYkSkWClixWotKgooampREVBQEVFRqWClFBExVK1HURARUan2++b93ubl8cJRrb12Pp9/vu+/O7M7OzszOzvZ/e31x1Y/tWB1y98R3+laXrQ7f9GXR9u/8uavBkbHv9frOepxJ9fyNXfkjFpf49N3nlnV7vu7li9exZggwbV84ua5q8P2Rj44bMFHE/JOpt5LuzD5ueTyzKj3Uo/HhxRFV1zX4yTb+dAsD1iV2zp2/oneUSejwhttmLyfvinCtfzkpG+/qhPy/BtTc3/1delVT85nHszkf+Mt02+LX7Ip51Djv5d/GdeKm869Ia7lL4Y22JKelPRCv6BOvae3GEyZpJn4kaFZQ3ddcTi/Y9s7bpo3++EvzXe9WT4n4o5t26ZHjd1937QNFR2u7kk9N/Gf6D/i+KkLe755+8eHXs50Zr7O+MOUT/O9mXXyJg6/4WDIoqLYDin38/6qKZ+jA0ZGz4hbuuTZJn2XhlR89wn39qY=
*/