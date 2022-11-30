#ifndef  BOOST_SERIALIZATION_VECTOR_HPP
#define BOOST_SERIALIZATION_VECTOR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// vector.hpp: serialization for stl vector templates

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// fast array serialization (C) Copyright 2005 Matthias Troyer
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <vector>

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/library_version_type.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/serialization/library_version_type.hpp>

#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/collections_load_imp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/array_wrapper.hpp>
#include <boost/mpl/bool_fwd.hpp>
#include <boost/mpl/if.hpp>

// default is being compatible with version 1.34.1 files, not 1.35 files
#ifndef BOOST_SERIALIZATION_VECTOR_VERSIONED
#define BOOST_SERIALIZATION_VECTOR_VERSIONED(V) (V==4 || V==5)
#endif

// function specializations must be defined in the appropriate
// namespace - boost::serialization
#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
#define STD _STLP_STD
#else
#define STD std
#endif

namespace boost {
namespace serialization {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// vector< T >

// the default versions

template<class Archive, class U, class Allocator>
inline void save(
    Archive & ar,
    const std::vector<U, Allocator> &t,
    const unsigned int /* file_version */,
    mpl::false_
){
    boost::serialization::stl::save_collection<Archive, STD::vector<U, Allocator> >(
        ar, t
    );
}

template<class Archive, class U, class Allocator>
inline void load(
    Archive & ar,
    std::vector<U, Allocator> &t,
    const unsigned int /* file_version */,
    mpl::false_
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
    t.reserve(count);
    stl::collection_load_impl(ar, t, count, item_version);
}

// the optimized versions

template<class Archive, class U, class Allocator>
inline void save(
    Archive & ar,
    const std::vector<U, Allocator> &t,
    const unsigned int /* file_version */,
    mpl::true_
){
    const collection_size_type count(t.size());
    ar << BOOST_SERIALIZATION_NVP(count);
    if (!t.empty())
        // explict template arguments to pass intel C++ compiler
        ar << serialization::make_array<const U, collection_size_type>(
            static_cast<const U *>(&t[0]),
            count
        );
}

template<class Archive, class U, class Allocator>
inline void load(
    Archive & ar,
    std::vector<U, Allocator> &t,
    const unsigned int /* file_version */,
    mpl::true_
){
    collection_size_type count(t.size());
    ar >> BOOST_SERIALIZATION_NVP(count);
    t.resize(count);
    unsigned int item_version=0;
    if(BOOST_SERIALIZATION_VECTOR_VERSIONED(ar.get_library_version())) {
        ar >> BOOST_SERIALIZATION_NVP(item_version);
    }
    if (!t.empty())
        // explict template arguments to pass intel C++ compiler
        ar >> serialization::make_array<U, collection_size_type>(
            static_cast<U *>(&t[0]),
            count
        );
  }

// dispatch to either default or optimized versions

template<class Archive, class U, class Allocator>
inline void save(
    Archive & ar,
    const std::vector<U, Allocator> &t,
    const unsigned int file_version
){
    typedef typename
    boost::serialization::use_array_optimization<Archive>::template apply<
        typename remove_const<U>::type
    >::type use_optimized;
    save(ar,t,file_version, use_optimized());
}

template<class Archive, class U, class Allocator>
inline void load(
    Archive & ar,
    std::vector<U, Allocator> &t,
    const unsigned int file_version
){
#ifdef BOOST_SERIALIZATION_VECTOR_135_HPP
    if (ar.get_library_version()==boost::serialization::library_version_type(5))
    {
      load(ar,t,file_version, boost::is_arithmetic<U>());
      return;
    }
#endif
    typedef typename
    boost::serialization::use_array_optimization<Archive>::template apply<
        typename remove_const<U>::type
    >::type use_optimized;
    load(ar,t,file_version, use_optimized());
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class U, class Allocator>
inline void serialize(
    Archive & ar,
    std::vector<U, Allocator> & t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// vector<bool>
template<class Archive, class Allocator>
inline void save(
    Archive & ar,
    const std::vector<bool, Allocator> &t,
    const unsigned int /* file_version */
){
    // record number of elements
    collection_size_type count (t.size());
    ar << BOOST_SERIALIZATION_NVP(count);
    std::vector<bool>::const_iterator it = t.begin();
    while(count-- > 0){
        bool tb = *it++;
        ar << boost::serialization::make_nvp("item", tb);
    }
}

template<class Archive, class Allocator>
inline void load(
    Archive & ar,
    std::vector<bool, Allocator> &t,
    const unsigned int /* file_version */
){
    // retrieve number of elements
    collection_size_type count;
    ar >> BOOST_SERIALIZATION_NVP(count);
    t.resize(count);
    for(collection_size_type i = collection_size_type(0); i < count; ++i){
        bool b;
        ar >> boost::serialization::make_nvp("item", b);
        t[i] = b;
    }
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Allocator>
inline void serialize(
    Archive & ar,
    std::vector<bool, Allocator> & t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // serialization
} // namespace boost

#include <boost/serialization/collection_traits.hpp>

BOOST_SERIALIZATION_COLLECTION_TRAITS(std::vector)
#undef STD

#endif // BOOST_SERIALIZATION_VECTOR_HPP

/* vector.hpp
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
*/