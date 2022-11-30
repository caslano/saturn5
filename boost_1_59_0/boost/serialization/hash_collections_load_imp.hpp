#ifndef BOOST_SERIALIZATION_HASH_COLLECTIONS_LOAD_IMP_HPP
#define BOOST_SERIALIZATION_HASH_COLLECTIONS_LOAD_IMP_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
# pragma warning (disable : 4786) // too long name, harmless warning
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// hash_collections_load_imp.hpp: serialization for loading stl collections

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// helper function templates for serialization of hashed collections
#include <boost/config.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/serialization/library_version_type.hpp>

namespace boost{
namespace serialization {
namespace stl {

//////////////////////////////////////////////////////////////////////
// implementation of serialization for STL containers
//
template<class Archive, class Container, class InputFunction>
inline void load_hash_collection(Archive & ar, Container &s)
{
    collection_size_type count;
    collection_size_type bucket_count;
    boost::serialization::item_version_type item_version(0);
    boost::serialization::library_version_type library_version(
        ar.get_library_version()
    );
    // retrieve number of elements
    if(boost::serialization::library_version_type(6) != library_version){
        ar >> BOOST_SERIALIZATION_NVP(count);
        ar >> BOOST_SERIALIZATION_NVP(bucket_count);
    }
    else{
        // note: fixup for error in version 6.  collection size was
        // changed to size_t BUT for hashed collections it was implemented
        // as an unsigned int.  This should be a problem only on win64 machines
        // but I'll leave it for everyone just in case.
        unsigned int c;
        unsigned int bc;
        ar >> BOOST_SERIALIZATION_NVP(c);
        count = c;
        ar >> BOOST_SERIALIZATION_NVP(bc);
        bucket_count = bc;
    }
    if(boost::serialization::library_version_type(3) < library_version){
        ar >> BOOST_SERIALIZATION_NVP(item_version);
    }
    s.clear();
    #if ! defined(__MWERKS__)
    s.resize(bucket_count);
    #endif
    InputFunction ifunc;
    while(count-- > 0){
        ifunc(ar, s, item_version);
    }
}

} // namespace stl
} // namespace serialization
} // namespace boost

#endif //BOOST_SERIALIZATION_HASH_COLLECTIONS_LOAD_IMP_HPP

/* hash_collections_load_imp.hpp
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
*/