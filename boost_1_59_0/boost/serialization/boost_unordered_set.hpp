#ifndef  BOOST_SERIALIZATION_BOOST_UNORDERED_SET_HPP
#define BOOST_SERIALIZATION_BOOST_UNORDERED_SET_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// unordered_set.hpp: serialization for boost unordered_set templates

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// (C) Copyright 2014 Jim Bell
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#include <boost/unordered_set.hpp>

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
    const boost::unordered_set<Key, HashFcn, EqualKey, Allocator> &t,
    const unsigned int /*file_version*/
){
    boost::serialization::stl::save_unordered_collection<
        Archive,
        boost::unordered_set<Key, HashFcn, EqualKey, Allocator>
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
    boost::unordered_set<Key, HashFcn, EqualKey, Allocator> &t,
    const unsigned int /*file_version*/
){
    boost::serialization::stl::load_unordered_collection<
        Archive,
        boost::unordered_set<Key, HashFcn, EqualKey, Allocator>,
        boost::serialization::stl::archive_input_unordered_set<
            Archive,
            boost::unordered_set<Key, HashFcn, EqualKey, Allocator>
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
    boost::unordered_set<Key, HashFcn, EqualKey, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
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
    const boost::unordered_multiset<Key, HashFcn, EqualKey, Allocator> &t,
    const unsigned int /*file_version*/
){
    boost::serialization::stl::save_unordered_collection<
        Archive,
        boost::unordered_multiset<Key, HashFcn, EqualKey, Allocator>
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
    boost::unordered_multiset<Key, HashFcn, EqualKey, Allocator> &t,
    const unsigned int /*file_version*/
){
    boost::serialization::stl::load_unordered_collection<
        Archive,
        boost::unordered_multiset<Key, HashFcn, EqualKey, Allocator>,
        boost::serialization::stl::archive_input_unordered_multiset<
            Archive,
            boost::unordered_multiset<Key, HashFcn, EqualKey, Allocator>
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
    boost::unordered_multiset<Key, HashFcn, EqualKey, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#endif // BOOST_SERIALIZATION_BOOST_UNORDERED_SET_HPP

/* boost_unordered_set.hpp
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
*/