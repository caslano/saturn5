#ifndef  BOOST_SERIALIZATION_UNORDERED_SET_HPP
#define BOOST_SERIALIZATION_UNORDERED_SET_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// unordered_set.hpp: serialization for stl unordered_set templates

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// (C) Copyright 2014 Jim Bell
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#include <unordered_set>

#include <boost/serialization/unordered_collections_save_imp.hpp>
#include <boost/serialization/unordered_collections_load_imp.hpp>
#include <boost/serialization/archive_input_unordered_set.hpp>
#include <boost/serialization/split_free.hpp>

namespace boost {
namespace serialization {

template<
    class Archive,
    class Key,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void save(
    Archive & ar,
    const std::unordered_set<
        Key, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int /*file_version*/
){
    boost::serialization::stl::save_unordered_collection<
        Archive,
        std::unordered_set<Key, HashFcn, EqualKey, Allocator>
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
    std::unordered_set<
        Key, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int /*file_version*/
){
    boost::serialization::stl::load_unordered_collection<
        Archive,
        std::unordered_set<Key, HashFcn, EqualKey, Allocator>,
        stl::archive_input_unordered_set<
            Archive,
            std::unordered_set<
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
    std::unordered_set<
        Key, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int file_version
){
    split_free(ar, t, file_version);
}

// unordered_multiset
template<
    class Archive,
    class Key,
    class HashFcn,
    class EqualKey,
    class Allocator
>
inline void save(
    Archive & ar,
    const std::unordered_multiset<
        Key, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int /*file_version*/
){
    stl::save_unordered_collection<
        Archive,
        std::unordered_multiset<Key, HashFcn, EqualKey, Allocator>
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
    std::unordered_multiset<
        Key, HashFcn, EqualKey, Allocator
    > &t,
    const unsigned int /*file_version*/
){
    boost::serialization::stl::load_unordered_collection<
        Archive,
        std::unordered_multiset<Key, HashFcn, EqualKey, Allocator>,
        boost::serialization::stl::archive_input_unordered_multiset<
            Archive,
            std::unordered_multiset<Key, HashFcn, EqualKey, Allocator>
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
    std::unordered_multiset<Key, HashFcn, EqualKey, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#endif // BOOST_SERIALIZATION_UNORDERED_SET_HPP

/* unordered_set.hpp
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
*/