#ifndef BOOST_SERIALIZATION_FORWARD_LIST_HPP
#define BOOST_SERIALIZATION_FORWARD_LIST_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// forward_list.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#include <forward_list>
#include <iterator>  // distance

#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/collections_load_imp.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/serialization/library_version_type.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/detail/stack_constructor.hpp>
#include <boost/serialization/detail/is_default_constructible.hpp>
#include <boost/move/utility_core.hpp>

namespace boost {
namespace serialization {

template<class Archive, class U, class Allocator>
inline void save(
    Archive & ar,
    const std::forward_list<U, Allocator> &t,
    const unsigned int /*file_version*/
){
    const collection_size_type count(std::distance(t.cbegin(), t.cend()));
    boost::serialization::stl::save_collection<
        Archive,
        std::forward_list<U, Allocator>
    >(ar, t, count);
}

namespace stl {

template<
    class Archive,
    class T,
    class Allocator
>
typename boost::disable_if<
    typename detail::is_default_constructible<
        typename std::forward_list<T, Allocator>::value_type
    >,
    void
>::type
collection_load_impl(
    Archive & ar,
    std::forward_list<T, Allocator> &t,
    collection_size_type count,
    item_version_type item_version
){
    t.clear();
    boost::serialization::detail::stack_construct<Archive, T> u(ar, item_version);
    ar >> boost::serialization::make_nvp("item", u.reference());
    t.push_front(boost::move(u.reference()));
    typename std::forward_list<T, Allocator>::iterator last;
    last = t.begin();
    ar.reset_object_address(&(*t.begin()) , & u.reference());
    while(--count > 0){
        detail::stack_construct<Archive, T> u(ar, item_version);
        ar >> boost::serialization::make_nvp("item", u.reference());
        last = t.insert_after(last, boost::move(u.reference()));
        ar.reset_object_address(&(*last) , & u.reference());
    }
}

} // stl

template<class Archive, class U, class Allocator>
inline void load(
    Archive & ar,
    std::forward_list<U, Allocator> &t,
    const unsigned int /*file_version*/
){
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
    stl::collection_load_impl(ar, t, count, item_version);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class U, class Allocator>
inline void serialize(
    Archive & ar,
    std::forward_list<U, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // serialization
} // namespace boost

#include <boost/serialization/collection_traits.hpp>

BOOST_SERIALIZATION_COLLECTION_TRAITS(std::forward_list)

#endif  // BOOST_SERIALIZATION_FORWARD_LIST_HPP

/* forward_list.hpp
+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
*/