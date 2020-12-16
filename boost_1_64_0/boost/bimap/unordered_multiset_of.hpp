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
GgVxwc2mvFjJLYTdvptO5S3k7DBVkhzaNbmdIrn9Qs4XZrEkh/ZLbu+S3EEh54BZI8mhH5DbEZJ7V8gFwmyS5NDeye0lkjsr5EJhdkpyoez2NMkdFXLhMPsluXB2e5/kXhNykTAvSnJN2O0jkjsp5KJg3pDk0BfI7XOSOy3komHeIzlvcitRXG7zc51uo1g3u3OU4TpDayQ36DTq5eFWY0nzcHvakuHhpiiDPONThnnGp2R6xqeM8YzPmuUZn3Wy5BaG37+GDkf7z2Q9VqOWtHKkT1R/p0t+OzNVnVSLpziahDnsLRzVy30tJNOOZU6pMraapxy+vg57V0evzg7fIQ6flvhpsEu2K8s6RvKz7DXRDntD5/9e+L+Rw97Kkezn8OrhaBfgiOmoiT9lJMcfUePn8Gvh8GtI/zdyRDZyeEexziuWHaPGP+4Gh22Cyy+C/SrUeKzNSReXt2OkF/wxh5sI3T3it6fit6HTuH+ZjV21YHv+no76Ta8OZC8l+26hi2gOjWVJPJYdHuV+rzeHGQwTB7mofHUsK40rjcNLMLs0Xj0X78JjGo9hLNtejGEDyd6ZZLvJY5KQjRbjTgbZUy1m+Rb6BOvQddJFyncK7N0433I+d492BbwBpg1MNkwC5Go985mg5jNIm0+W7SLyeZzsvYzyCVntb55fJPu16nc/kL/fltcg87yKOc3Osa6AT2Mu0xm8B0yGXNoMkdf47LzpRfAyfEdVkNytVnWOuoPsj/BZthpPhpJseV/U4zxySxB7SEsL6K42vWu6y2UjwncT68QSjt/ot9lpYDD6zF7UX+0Y7k+FixOpr7D7PtW9quYA9VV2/5DdMRZkOHuYDf9Dj52fwxbgGAidYrJs4Fjuj9VLqw85bNU3O+xe+OG9w8fH4efnsAdQ32XZWFXWOs4Z53hfra478bvunU5y3ZaK6jTWdVcIYpzkvqrty/tg7871HAx7Wh2/0143zhVxET9gFkwqZA/NFHWfkB0r2rc8T2eZIirv3chjIOLa7Mxn1FBX/ti9M9wfgLstFnoOfEI1foNUv8ZuPzW+aWp8jV3lVd95vavNF2raeC+8UCi/MG1hymF64h+Z10n5NGjjnFeWixHtt4rss7TzKG7/N5HfWG6/atgkkvWi9jpH6BdwtpENyGfteOxfOPPqH+Pf0L8dCqNx42D4pcC9EGaL0y9oLJWD6l4t3NPUMiX3e9gdcTnwI3fyk3Wv7uY2ttu4LIeqbaxWamOHdG3sqPZ9QXnxIvsc0hmFMlB1RpF9o86+W7LL9bRmgisR42BCYPrD9Ea8gbOkeqK3i+G7heWai3rqQvZ4w3rqSH6xXE8cFjXiLMc0tJcPYagcvXuiaXKfZT/LBNWvvcPbT+sXqfrZQ4Rffcdr/btJlDHKDHnRlGFfnT17lnGZ5k3kilUfCHMN4q3mMhVfNWZ9e+Hafs5yQ6mfr0PeLsJQvwxNUvNN7qETuS83E31Z+MWyn78Fft6Nr6g/h0v9uQfnKS3bJfiY8xsN4M1gCOTOijy5vunn/AJo9nQolLboxjBuA62K6LcNNs4rh+8r9GzBj9uH6jee/LypH5ep/ZjcfMmtQuilkL55K9afU0t4HOH15iNFvC9F/tDiNdtpny2NFeWQTaf+95diugtO78g08sunZx1SUFasz5H3d+jdq8A2i+LvgzWKl/vOArlZLa1RN4Wol2GYWP+BdHE+79/av7u31RYC0wQVFdWE3pmTcM8WxjW21zSiemV3X4R9gMJehLwtlOqV/TqzHzy8ql/wttnCScQihx80meO1Vj/vCPEhP4qD07Yc/ruc8S8+hDQFwYQgkpBg43kRz5k57AGEfYTCLkS4YIQ=
*/