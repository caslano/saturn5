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
P8WzzmVS2m0/Worketfc1biR2pdDWxfdtWftJ0kmSCOjf2fMpmc11O8Li7bTi+JYrUmHZk5P/qE2uU9x+xPvybepvsdo+ot+DOzt2acSRP/l8u5B7a+Ptm3p1rlz6VmBde7/vjfaY/9Xs4bqQnlSFKP94WAwlvwLqd5PwT6U7KO95DLQv7/bj9KnC2Wg24e7n9IVqsmfflxJzqR49OsM8R79hvK/w3qjZYfpHmvltXXvsTaiOJpqxwvdvuJGSkczjYw+P3dTnlvALuVZ2v8YynnRjAO6/aDXKC3t5fxq9uqvozKLrXMfdRtkdPvacfr369Oe7S9O31deo3JrrqlD/Zh+INNjHE3W12EvypPDdB+0jMaezoiD2yvJ34wZQoBYQ02h9Pa1yvMSOc/tKK2XNPWjH8+nj/TMM9ezGAefo/xcr+mX+r57nOcdsow+zz9kesxxEvXvDn/Pd3iiPp7tnvP2VH0d+FF9N5bbt2aPeASVTZimbPR5yvZMbxzSoimbRHrOfs34ql9DrBjp+T7Ur5lm87vLaJ0drO7BUzzzMScqleucYhJnK9d6nMenyv7ryR9tSM53rDs/95D/AG254Nab3N/6UJ47a9q3Pj/V+rKDjL4v/Uz5aeS5b8DPaUL+M9E6w8Vcvpj6RZx4v60mmWTqE9MQdiHZ29gM9xV4vn+eZIoV51p9+WX2FU7o1uqnTNbq9iGsW5fX6hN4rR44zr1Wj9eu1UW9fjWRyhMzj+ZcD2q47mIuEzGJ752ar985zAMe626ha3QCtVXFbM09jMKfML0P+adxda+5B4+nOjdaC4u8hlIaMtCGe1r1688wzvtP9JyTNl/U8x5LlE19Jz9C8eeKucArJBcq7hzMpnK8FTsYNnFW9GeS2apfg4o49mTR70WM15fcDl+jNB82XV/G0zN+NV1f9iH/9laz9eV94+peX1aMq3t9eWhc3Wu+QeT/i+maL4n839Ov+USd/UzlbrcF4dvl6h5BFpXbi9bRliKrqrfbn9zK6lzXfUdxnUT9HxPrulMT617XdR1vODZq9ikTqI6mmK6RUiiOIP1aQtTRHArfwGq2NjhN/l6if7am/tha/M5tD8U/3xpoaWZV2+tWcvOlthiFuB4i+2u2uvamq+k5Pkb3VMSznh3vKueWyhDTtcHt3CbM5vRjXG1WE14uz0zy/4u1rjn0jon0DNM5dA+Ko4npHLo/+ReIOfQksrf20s1rRXyx9Lzhitmcdtm4uua0YBbVsX4eKfrx/RT/O5a6fjs2jmQG6udtYgyKpPqbaI3GOKue+fQkt3TTeVo6pXuOYjZXmUr+YXXODbZQ3qajX00wnRvcMK7uucF28g/Qv49FmxlNz+gidMZkUB+IEPmYSvaWYn46jeSbG7+L+Z3jR2Uz+Z/6Ln5niPFv3M9OFu/iyunG++aQMf2NO/xMf+MOv3/db9zVM8/A4a6ICpy6LcEosAnyNW2Kmq+KEvq1L+VN1QFUznljOYTm9It8DxV+Kdw2tHOHMHAt+b/NbVS8s8VvoeeTf4DsL+r5OvjXkH+m7C/Go5nwv578E9lfOz7Pgv8y8i+X/UUfCgWXk/9m6Vs/cyxJ3K4fIL8eFhv+awDTCKYxTARMS5homA4w3WASYfgZ6vgj9KWvp3iCuX9px48QcAP5t5b9xTuqCbiK/J/gPGj7Vzi4kvzvUuqjvyNQ6KYq17WZQm1fGOkKeNyGPTewHOzkbDPTXPrLcU4OhQ+u9tKev9Givq+uyaF9cX5Pq2FixHxyOdnXKupcauN0p32VuKPcmuzzxTulKdkb0LM60LNKuf2pcbcW48Jisk+TdMnMEfOVW8lvp8J9D2G1v7vz5d/LOfU=
*/