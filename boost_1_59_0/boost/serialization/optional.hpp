/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8

// (C) Copyright 2002-4 Pavel Vozenilek .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Provides non-intrusive serialization for boost::optional.

#ifndef BOOST_SERIALIZATION_OPTIONAL_HPP_
#define BOOST_SERIALIZATION_OPTIONAL_HPP_

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>

#include <boost/optional.hpp>

#include <boost/serialization/item_version_type.hpp>
#include <boost/serialization/library_version_type.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/serialization/detail/is_default_constructible.hpp>

// function specializations must be defined in the appropriate
// namespace - boost::serialization
namespace boost {
namespace serialization {

template<class Archive, class T>
void save(
    Archive & ar,
    const boost::optional< T > & t,
    const unsigned int /*version*/
){
    // It is an inherent limitation to the serialization of optional.hpp
    // that the underlying type must be either a pointer or must have a
    // default constructor.  It's possible that this could change sometime
    // in the future, but for now, one will have to work around it.  This can
    // be done by serialization the optional<T> as optional<T *>
    #if ! defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
        BOOST_STATIC_ASSERT(
            boost::serialization::detail::is_default_constructible<T>::value
            || boost::is_pointer<T>::value
        );
    #endif
    const bool tflag = t.is_initialized();
    ar << boost::serialization::make_nvp("initialized", tflag);
    if (tflag){
        ar << boost::serialization::make_nvp("value", *t);
    }
}

template<class Archive, class T>
void load(
    Archive & ar,
    boost::optional< T > & t,
    const unsigned int version
){
    bool tflag;
    ar >> boost::serialization::make_nvp("initialized", tflag);
    if(! tflag){
        t.reset();
        return;
    }

    if(0 == version){
        boost::serialization::item_version_type item_version(0);
        boost::serialization::library_version_type library_version(
            ar.get_library_version()
        );
        if(boost::serialization::library_version_type(3) < library_version){
            ar >> BOOST_SERIALIZATION_NVP(item_version);
        }
    }
    if(! t.is_initialized())
        t = T();
    ar >> boost::serialization::make_nvp("value", *t);
}

template<class Archive, class T>
void serialize(
    Archive & ar,
    boost::optional< T > & t,
    const unsigned int version
){
    boost::serialization::split_free(ar, t, version);
}

template<class T>
struct version<boost::optional<T> > {
    BOOST_STATIC_CONSTANT(int, value = 1);
};

} // serialization
} // boost

#endif // BOOST_SERIALIZATION_OPTIONAL_HPP_

/* optional.hpp
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
*/