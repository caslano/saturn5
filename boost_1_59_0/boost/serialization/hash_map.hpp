#ifndef  BOOST_SERIALIZATION_HASH_MAP_HPP
#define BOOST_SERIALIZATION_HASH_MAP_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// hash_map.hpp: serialization for stl hash_map templates

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_HAS_HASH
#include BOOST_HASH_MAP_HEADER

#include <boost/serialization/utility.hpp> // pair
#include <boost/serialization/hash_collections_save_imp.hpp>
#include <boost/serialization/hash_collections_load_imp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/detail/stack_constructor.hpp>
#include <boost/move/utility_core.hpp>

namespace boost {
namespace serialization {

namespace stl {

// hash_map input
template<class Archive, class Container>
struct archive_input_hash_map
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
        // note: the following presumes that the map::value_type was NOT tracked
        // in the archive.  This is the usual case, but here there is no way
        // to determine that.
        if(result.second){
            ar.reset_object_address(
                & (result.first->second),
                & t.reference().second
            );
        }
    }
};

// hash_multimap input
template<class Archive, class Container>
struct archive_input_hash_multimap
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
        // note: the following presumes that the map::value_type was NOT tracked
        // in the archive.  This is the usual case, but here there is no way
        // to determine that.
        ar.reset_object_address(
            & result->second,
            & t.reference()
        );
    }
};

} // stl

template<
    class Archive,
    class Key,
    class T,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void save(
    Archive & ar,
    const BOOST_STD_EXTENSION_NAMESPACE::hash_map<
        Key, T, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int file_version
){
    boost::serialization::stl::save_hash_collection<
        Archive,
        BOOST_STD_EXTENSION_NAMESPACE::hash_map<
            Key, T, HashFcn, EqualKey, Allocator
        >
    >(ar, t);
}

template<
    class Archive,
    class Key,
    class T,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void load(
    Archive & ar,
    BOOST_STD_EXTENSION_NAMESPACE::hash_map<
        Key, T, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int file_version
){
    boost::serialization::stl::load_hash_collection<
        Archive,
        BOOST_STD_EXTENSION_NAMESPACE::hash_map<
            Key, T, HashFcn, EqualKey, Allocator
        >,
        boost::serialization::stl::archive_input_hash_map<
            Archive,
            BOOST_STD_EXTENSION_NAMESPACE::hash_map<
                Key, T, HashFcn, EqualKey, Allocator
            >
        >
    >(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<
    class Archive,
    class Key,
    class T,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void serialize(
    Archive & ar,
    BOOST_STD_EXTENSION_NAMESPACE::hash_map<
        Key, T, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

// hash_multimap
template<
    class Archive,
    class Key,
    class T,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void save(
    Archive & ar,
    const BOOST_STD_EXTENSION_NAMESPACE::hash_multimap<
        Key, T, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int file_version
){
    boost::serialization::stl::save_hash_collection<
        Archive,
        BOOST_STD_EXTENSION_NAMESPACE::hash_multimap<
            Key, T, HashFcn, EqualKey, Allocator
        >
    >(ar, t);
}

template<
    class Archive,
    class Key,
    class T,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void load(
    Archive & ar,
    BOOST_STD_EXTENSION_NAMESPACE::hash_multimap<
        Key, T, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int file_version
){
    boost::serialization::stl::load_hash_collection<
        Archive,
        BOOST_STD_EXTENSION_NAMESPACE::hash_multimap<
            Key, T, HashFcn, EqualKey, Allocator
        >,
        boost::serialization::stl::archive_input_hash_multimap<
            Archive,
            BOOST_STD_EXTENSION_NAMESPACE::hash_multimap<
                Key, T, HashFcn, EqualKey, Allocator
            >
        >
    >(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<
    class Archive,
    class Key,
    class T,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void serialize(
    Archive & ar,
    BOOST_STD_EXTENSION_NAMESPACE::hash_multimap<
        Key, T, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#endif // BOOST_HAS_HASH
#endif // BOOST_SERIALIZATION_HASH_MAP_HPP

/* hash_map.hpp
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
*/