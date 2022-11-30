#ifndef  BOOST_SERIALIZATION_MAP_HPP
#define BOOST_SERIALIZATION_MAP_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// serialization/map.hpp:
// serialization for stl map templates

// (C) Copyright 2002-2014 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <map>

#include <boost/config.hpp>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/serialization/library_version_type.hpp>
#include <boost/serialization/detail/stack_constructor.hpp>

#include <boost/serialization/utility.hpp>
#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/move/utility_core.hpp>

namespace boost {
namespace serialization {

////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// implementation of serialization for map and mult-map STL containers

template<class Archive, class Container>
inline void load_map_collection(Archive & ar, Container &s)
{
    s.clear();
    const boost::serialization::library_version_type library_version(
        ar.get_library_version()
    );
    // retrieve number of elements
    item_version_type item_version(0);
    collection_size_type count;
    ar >> BOOST_SERIALIZATION_NVP(count);
    if(boost::serialization::library_version_type(3) < library_version){
        ar >> BOOST_SERIALIZATION_NVP(item_version);
    }
    typename Container::iterator hint;
    hint = s.begin();
    while(count-- > 0){
        typedef typename Container::value_type type;
        detail::stack_construct<Archive, type> t(ar, item_version);
        ar >> boost::serialization::make_nvp("item", t.reference());
        typename Container::iterator result =
            s.insert(hint, boost::move(t.reference()));
        ar.reset_object_address(& (result->second), & t.reference().second);
        hint = result;
        ++hint;
    }
}

// map
template<class Archive, class Type, class Key, class Compare, class Allocator >
inline void save(
    Archive & ar,
    const std::map<Key, Type, Compare, Allocator> &t,
    const unsigned int /* file_version */
){
    boost::serialization::stl::save_collection<
        Archive,
        std::map<Key, Type, Compare, Allocator>
    >(ar, t);
}

template<class Archive, class Type, class Key, class Compare, class Allocator >
inline void load(
    Archive & ar,
    std::map<Key, Type, Compare, Allocator> &t,
    const unsigned int /* file_version */
){
    load_map_collection(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Type, class Key, class Compare, class Allocator >
inline void serialize(
    Archive & ar,
    std::map<Key, Type, Compare, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

// multimap
template<class Archive, class Type, class Key, class Compare, class Allocator >
inline void save(
    Archive & ar,
    const std::multimap<Key, Type, Compare, Allocator> &t,
    const unsigned int /* file_version */
){
    boost::serialization::stl::save_collection<
        Archive,
        std::multimap<Key, Type, Compare, Allocator>
    >(ar, t);
}

template<class Archive, class Type, class Key, class Compare, class Allocator >
inline void load(
    Archive & ar,
    std::multimap<Key, Type, Compare, Allocator> &t,
    const unsigned int /* file_version */
){
    load_map_collection(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Type, class Key, class Compare, class Allocator >
inline void serialize(
    Archive & ar,
    std::multimap<Key, Type, Compare, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // serialization
} // namespace boost

#endif // BOOST_SERIALIZATION_MAP_HPP

/* map.hpp
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
*/