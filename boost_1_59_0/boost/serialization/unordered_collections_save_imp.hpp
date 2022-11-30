#ifndef BOOST_SERIALIZATION_UNORDERED_COLLECTIONS_SAVE_IMP_HPP
#define BOOST_SERIALIZATION_UNORDERED_COLLECTIONS_SAVE_IMP_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// hash_collections_save_imp.hpp: serialization for stl collections

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// (C) Copyright 2014 Jim Bell
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// helper function templates for serialization of collections

#include <boost/config.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/version.hpp>
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
inline void save_unordered_collection(Archive & ar, const Container &s)
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
	ar << BOOST_SERIALIZATION_NVP(count);
	ar << BOOST_SERIALIZATION_NVP(bucket_count);
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

#endif //BOOST_SERIALIZATION_UNORDERED_COLLECTIONS_SAVE_IMP_HPP

/* unordered_collections_save_imp.hpp
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
*/