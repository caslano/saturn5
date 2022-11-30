#ifndef BOOST_SERIALIZATION_SLIST_HPP
#define BOOST_SERIALIZATION_SLIST_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// slist.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_HAS_SLIST
#include BOOST_SLIST_HEADER

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
    const BOOST_STD_EXTENSION_NAMESPACE::slist<U, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::stl::save_collection<
        Archive,
        BOOST_STD_EXTENSION_NAMESPACE::slist<U, Allocator>
    >(ar, t);
}

namespace stl {

template<
    class Archive,
    class T,
    class Allocator
>
typename boost::disable_if<
    typename detail::is_default_constructible<
        typename BOOST_STD_EXTENSION_NAMESPACE::slist<T, Allocator>::value_type
    >,
    void
>::type
collection_load_impl(
    Archive & ar,
    BOOST_STD_EXTENSION_NAMESPACE::slist<T, Allocator> &t,
    collection_size_type count,
    item_version_type item_version
){
    t.clear();
    boost::serialization::detail::stack_construct<Archive, T> u(ar, item_version);
    ar >> boost::serialization::make_nvp("item", u.reference());
    t.push_front(boost::move(u.reference()));
    typename BOOST_STD_EXTENSION_NAMESPACE::slist<T, Allocator>::iterator last;
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
    BOOST_STD_EXTENSION_NAMESPACE::slist<U, Allocator> &t,
    const unsigned int file_version
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
    if(detail::is_default_constructible<U>()){
        t.resize(count);
        typename BOOST_STD_EXTENSION_NAMESPACE::slist<U, Allocator>::iterator hint;
        hint = t.begin();
        while(count-- > 0){
            ar >> boost::serialization::make_nvp("item", *hint++);
        }
    }
    else{
        t.clear();
        boost::serialization::detail::stack_construct<Archive, U> u(ar, item_version);
        ar >> boost::serialization::make_nvp("item", u.reference());
        t.push_front(boost::move(u.reference()));
        typename BOOST_STD_EXTENSION_NAMESPACE::slist<U, Allocator>::iterator last;
        last = t.begin();
        ar.reset_object_address(&(*t.begin()) , & u.reference());
        while(--count > 0){
            detail::stack_construct<Archive, U> u(ar, item_version);
            ar >> boost::serialization::make_nvp("item", u.reference());
            last = t.insert_after(last, boost::move(u.reference()));
            ar.reset_object_address(&(*last) , & u.reference());
        }
    }
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class U, class Allocator>
inline void serialize(
    Archive & ar,
    BOOST_STD_EXTENSION_NAMESPACE::slist<U, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // serialization
} // namespace boost

#include <boost/serialization/collection_traits.hpp>

BOOST_SERIALIZATION_COLLECTION_TRAITS(BOOST_STD_EXTENSION_NAMESPACE::slist)

#endif  // BOOST_HAS_SLIST
#endif  // BOOST_SERIALIZATION_SLIST_HPP

/* slist.hpp
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
*/