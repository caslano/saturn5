#ifndef  BOOST_SERIALIZATION_SET_HPP
#define BOOST_SERIALIZATION_SET_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// set.hpp: serialization for stl set templates

// (C) Copyright 2002-2014 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <set>

#include <boost/config.hpp>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/detail/stack_constructor.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/serialization/library_version_type.hpp>

#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/move/utility_core.hpp>

namespace boost {
namespace serialization {

template<class Archive, class Container>
inline void load_set_collection(Archive & ar, Container &s)
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
        // borland fails silently w/o full namespace
        ar >> boost::serialization::make_nvp("item", t.reference());
        typename Container::iterator result =
            s.insert(hint, boost::move(t.reference()));
        const type * new_address = & (* result);
        ar.reset_object_address(new_address, & t.reference());
        hint = result;
    }
}

template<class Archive, class Key, class Compare, class Allocator >
inline void save(
    Archive & ar,
    const std::set<Key, Compare, Allocator> &t,
    const unsigned int /* file_version */
){
    boost::serialization::stl::save_collection<
        Archive, std::set<Key, Compare, Allocator>
    >(ar, t);
}

template<class Archive, class Key, class Compare, class Allocator >
inline void load(
    Archive & ar,
    std::set<Key, Compare, Allocator> &t,
    const unsigned int /* file_version */
){
    load_set_collection(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Key, class Compare, class Allocator >
inline void serialize(
    Archive & ar,
    std::set<Key, Compare, Allocator> & t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

// multiset
template<class Archive, class Key, class Compare, class Allocator >
inline void save(
    Archive & ar,
    const std::multiset<Key, Compare, Allocator> &t,
    const unsigned int /* file_version */
){
    boost::serialization::stl::save_collection<
        Archive,
        std::multiset<Key, Compare, Allocator>
    >(ar, t);
}

template<class Archive, class Key, class Compare, class Allocator >
inline void load(
    Archive & ar,
    std::multiset<Key, Compare, Allocator> &t,
    const unsigned int /* file_version */
){
    load_set_collection(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Key, class Compare, class Allocator >
inline void serialize(
    Archive & ar,
    std::multiset<Key, Compare, Allocator> & t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#include <boost/serialization/collection_traits.hpp>

BOOST_SERIALIZATION_COLLECTION_TRAITS(std::set)
BOOST_SERIALIZATION_COLLECTION_TRAITS(std::multiset)

#endif // BOOST_SERIALIZATION_SET_HPP

/* set.hpp
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
*/