#ifndef BOOST_SERIALIZATION_VALARAY_HPP
#define BOOST_SERIALIZATION_VALARAY_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// valarray.hpp: serialization for stl vector templates

// (C) Copyright 2005 Matthias Troyer .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <valarray>
#include <boost/config.hpp>
#include <boost/core/addressof.hpp>

#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/collections_load_imp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/array_wrapper.hpp>

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
// valarray< T >

template<class Archive, class U>
void save( Archive & ar, const STD::valarray<U> &t, const unsigned int /*file_version*/ )
{
    const collection_size_type count(t.size());
    ar << BOOST_SERIALIZATION_NVP(count);
    if (t.size()){
        // explict template arguments to pass intel C++ compiler
        ar << serialization::make_array<const U, collection_size_type>(
            static_cast<const U *>( boost::addressof(t[0]) ),
            count
        );
    }
}

template<class Archive, class U>
void load( Archive & ar, STD::valarray<U> &t,  const unsigned int /*file_version*/ )
{
    collection_size_type count;
    ar >> BOOST_SERIALIZATION_NVP(count);
    t.resize(count);
    if (t.size()){
        // explict template arguments to pass intel C++ compiler
        ar >> serialization::make_array<U, collection_size_type>(
            static_cast<U *>( boost::addressof(t[0]) ),
            count
        );
    }
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class U>
inline void serialize( Archive & ar, STD::valarray<U> & t, const unsigned int file_version)
{
    boost::serialization::split_free(ar, t, file_version);
}

} } // end namespace boost::serialization

#include <boost/serialization/collection_traits.hpp>

BOOST_SERIALIZATION_COLLECTION_TRAITS(STD::valarray)
#undef STD

#endif // BOOST_SERIALIZATION_VALARAY_HPP

/* valarray.hpp
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
*/