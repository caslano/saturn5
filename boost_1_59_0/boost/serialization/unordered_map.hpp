#ifndef  BOOST_SERIALIZATION_UNORDERED_MAP_HPP
#define BOOST_SERIALIZATION_UNORDERED_MAP_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// serialization/unordered_map.hpp:
// serialization for stl unordered_map templates

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// (C) Copyright 2014 Jim Bell
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#include <unordered_map>

#include <boost/serialization/utility.hpp>
#include <boost/serialization/unordered_collections_save_imp.hpp>
#include <boost/serialization/unordered_collections_load_imp.hpp>
#include <boost/serialization/archive_input_unordered_map.hpp>
#include <boost/serialization/split_free.hpp>

namespace boost {
namespace serialization {

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
    const std::unordered_map<Key, T, HashFcn, EqualKey, Allocator> &t,
    const unsigned int /*file_version*/
){
    boost::serialization::stl::save_unordered_collection<
        Archive,
        std::unordered_map<Key, T, HashFcn, EqualKey, Allocator>
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
    std::unordered_map<Key, T, HashFcn, EqualKey, Allocator> &t,
    const unsigned int /*file_version*/
){
    boost::serialization::stl::load_unordered_collection<
        Archive,
        std::unordered_map<Key, T, HashFcn, EqualKey, Allocator>,
        boost::serialization::stl::archive_input_unordered_map<
            Archive,
            std::unordered_map<Key, T, HashFcn, EqualKey, Allocator>
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
    std::unordered_map<Key, T, HashFcn, EqualKey, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

// unordered_multimap
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
    const std::unordered_multimap<Key, T, HashFcn, EqualKey, Allocator> &t,
    const unsigned int /*file_version*/
){
    boost::serialization::stl::save_unordered_collection<
        Archive,
        std::unordered_multimap<Key, T, HashFcn, EqualKey, Allocator>
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
    std::unordered_multimap<Key, T, HashFcn, EqualKey, Allocator> &t,
    const unsigned int /*file_version*/
){
    boost::serialization::stl::load_unordered_collection<
        Archive,
        std::unordered_multimap<Key, T, HashFcn, EqualKey, Allocator>,
        boost::serialization::stl::archive_input_unordered_multimap<
            Archive,
            std::unordered_multimap<Key, T, HashFcn, EqualKey, Allocator>
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
    std::unordered_multimap<Key, T, HashFcn, EqualKey, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#endif // BOOST_SERIALIZATION_UNORDERED_MAP_HPP

/* unordered_map.hpp
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
*/