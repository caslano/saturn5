#ifndef BOOST_SERIALIZATION_HASH_COLLECTIONS_SAVE_IMP_HPP
#define BOOST_SERIALIZATION_HASH_COLLECTIONS_SAVE_IMP_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// hash_collections_save_imp.hpp: serialization for stl collections

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// helper function templates for serialization of collections

#include <boost/config.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/serialization/library_version_type.hpp>

namespace boost{
namespace serialization {
namespace stl {

//////////////////////////////////////////////////////////////////////
// implementation of serialization for STL containers
//

template<class Archive, class Container>
inline void save_hash_collection(Archive & ar, const Container &s)
{
    collection_size_type count(s.size());
    const collection_size_type bucket_count(s.bucket_count());
    const item_version_type item_version(
        version<typename Container::value_type>::value
    );

    #if 0
    /* should only be necessary to create archives of previous versions
     * which is not currently supported.  So for now comment this out
     */
    boost::serialization::library_version_type library_version(
        ar.get_library_version()
    );
    // retrieve number of elements
    if(boost::serialization::library_version_type(6) != library_version){
        ar << BOOST_SERIALIZATION_NVP(count);
        ar << BOOST_SERIALIZATION_NVP(bucket_count);
    }
    else{
        // note: fixup for error in version 6.  collection size was
        // changed to size_t BUT for hashed collections it was implemented
        // as an unsigned int.  This should be a problem only on win64 machines
        // but I'll leave it for everyone just in case.
        const unsigned int c = count;
        const unsigned int bc = bucket_count;
        ar << BOOST_SERIALIZATION_NVP(c);
        ar << BOOST_SERIALIZATION_NVP(bc);
    }
    if(boost::serialization::library_version_type(3) < library_version){
        // record number of elements
        // make sure the target type is registered so we can retrieve
        // the version when we load
        ar << BOOST_SERIALIZATION_NVP(item_version);
    }
    #else
        ar << BOOST_SERIALIZATION_NVP(count);
        ar << BOOST_SERIALIZATION_NVP(bucket_count);
        ar << BOOST_SERIALIZATION_NVP(item_version);
    #endif

    typename Container::const_iterator it = s.begin();
    while(count-- > 0){
        // note borland emits a no-op without the explicit namespace
        boost::serialization::save_construct_data_adl(
            ar,
            &(*it),
            boost::serialization::version<
                typename Container::value_type
            >::value
        );
        ar << boost::serialization::make_nvp("item", *it++);
    }
}

} // namespace stl
} // namespace serialization
} // namespace boost

#endif //BOOST_SERIALIZATION_HASH_COLLECTIONS_SAVE_IMP_HPP

/* hash_collections_save_imp.hpp
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
*/