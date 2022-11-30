#ifndef  BOOST_SERIALIZATION_HASH_SET_HPP
#define BOOST_SERIALIZATION_HASH_SET_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// hash_set.hpp: serialization for stl hash_set templates

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_HAS_HASH
#include BOOST_HASH_SET_HEADER

#include <boost/serialization/hash_collections_save_imp.hpp>
#include <boost/serialization/hash_collections_load_imp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/detail/stack_constructor.hpp>
#include <boost/move/utility_core.hpp>

namespace boost {
namespace serialization {

namespace stl {

// hash_set input
template<class Archive, class Container>
struct archive_input_hash_set
{
    inline void operator()(
        Archive &ar,
        Container &s,
        const unsigned int v
    ){
        typedef typename Container::value_type type;
        detail::stack_construct<Archive, type> t(ar, v);
        // borland fails silently w/o full namespace
        ar >> boost::serialization::make_nvp("item", t.reference());
        std::pair<typename Container::const_iterator, bool> result =
            s.insert(boost::move(t.reference()));
        if(result.second)
            ar.reset_object_address(& (* result.first), & t.reference());
    }
};

// hash_multiset input
template<class Archive, class Container>
struct archive_input_hash_multiset
{
    inline void operator()(
        Archive &ar,
        Container &s,
        const unsigned int v
    ){
        typedef typename Container::value_type type;
        detail::stack_construct<Archive, type> t(ar, v);
        // borland fails silently w/o full namespace
        ar >> boost::serialization::make_nvp("item", t.reference());
        typename Container::const_iterator result
            = s.insert(boost::move(t.reference()));
        ar.reset_object_address(& (* result), & t.reference());
    }
};

} // stl

template<
    class Archive,
    class Key,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void save(
    Archive & ar,
    const BOOST_STD_EXTENSION_NAMESPACE::hash_set<
        Key, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int file_version
){
    boost::serialization::stl::save_hash_collection<
        Archive,
        BOOST_STD_EXTENSION_NAMESPACE::hash_set<
            Key, HashFcn, EqualKey, Allocator
        >
    >(ar, t);
}

template<
    class Archive,
    class Key,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void load(
    Archive & ar,
    BOOST_STD_EXTENSION_NAMESPACE::hash_set<
        Key, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int file_version
){
    boost::serialization::stl::load_hash_collection<
        Archive,
        BOOST_STD_EXTENSION_NAMESPACE::hash_set<
            Key, HashFcn, EqualKey, Allocator
        >,
        boost::serialization::stl::archive_input_hash_set<
            Archive,
            BOOST_STD_EXTENSION_NAMESPACE::hash_set<
                Key, HashFcn, EqualKey, Allocator
            >
        >
    >(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<
    class Archive,
    class Key,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void serialize(
    Archive & ar,
    BOOST_STD_EXTENSION_NAMESPACE::hash_set<
        Key, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

// hash_multiset
template<
    class Archive,
    class Key,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void save(
    Archive & ar,
    const BOOST_STD_EXTENSION_NAMESPACE::hash_multiset<
        Key, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int file_version
){
    boost::serialization::stl::save_hash_collection<
        Archive,
        BOOST_STD_EXTENSION_NAMESPACE::hash_multiset<
            Key, HashFcn, EqualKey, Allocator
        >
    >(ar, t);
}

template<
    class Archive,
    class Key,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void load(
    Archive & ar,
    BOOST_STD_EXTENSION_NAMESPACE::hash_multiset<
        Key, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int file_version
){
    boost::serialization::stl::load_hash_collection<
        Archive,
        BOOST_STD_EXTENSION_NAMESPACE::hash_multiset<
            Key, HashFcn, EqualKey, Allocator
        >,
        boost::serialization::stl::archive_input_hash_multiset<
            Archive,
            BOOST_STD_EXTENSION_NAMESPACE::hash_multiset<
                Key, HashFcn, EqualKey, Allocator
            >
        >
    >(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<
    class Archive,
    class Key,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void serialize(
    Archive & ar,
    BOOST_STD_EXTENSION_NAMESPACE::hash_multiset<
        Key, HashFcn, EqualKey, Allocator
    > & t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#include <boost/serialization/collection_traits.hpp>

BOOST_SERIALIZATION_COLLECTION_TRAITS(BOOST_STD_EXTENSION_NAMESPACE::hash_set)
BOOST_SERIALIZATION_COLLECTION_TRAITS(BOOST_STD_EXTENSION_NAMESPACE::hash_multiset)

#endif // BOOST_HAS_HASH
#endif // BOOST_SERIALIZATION_HASH_SET_HPP

/* hash_set.hpp
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
*/