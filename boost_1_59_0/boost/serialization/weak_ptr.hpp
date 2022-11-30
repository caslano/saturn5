#ifndef BOOST_SERIALIZATION_WEAK_PTR_HPP
#define BOOST_SERIALIZATION_WEAK_PTR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// weak_ptr.hpp: serialization for boost weak pointer

// (C) Copyright 2004 Robert Ramey and Martin Ecker
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/weak_ptr.hpp>
#include <boost/serialization/shared_ptr.hpp>

namespace boost {
namespace serialization{

template<class Archive, class T>
inline void save(
    Archive & ar,
    const boost::weak_ptr< T > &t,
    const unsigned int /* file_version */
){
    const boost::shared_ptr< T > sp = t.lock();
    ar << boost::serialization::make_nvp("weak_ptr", sp);
}

template<class Archive, class T>
inline void load(
    Archive & ar,
    boost::weak_ptr< T > &t,
    const unsigned int /* file_version */
){
    boost::shared_ptr< T > sp;
    ar >> boost::serialization::make_nvp("weak_ptr", sp);
    t = sp;
}

template<class Archive, class T>
inline void serialize(
    Archive & ar,
    boost::weak_ptr< T > &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#ifndef BOOST_NO_CXX11_SMART_PTR
#include <memory>

namespace boost {
namespace serialization{

template<class Archive, class T>
inline void save(
    Archive & ar,
    const std::weak_ptr< T > &t,
    const unsigned int /* file_version */
){
    const std::shared_ptr< T > sp = t.lock();
    ar << boost::serialization::make_nvp("weak_ptr", sp);
}

template<class Archive, class T>
inline void load(
    Archive & ar,
    std::weak_ptr< T > &t,
    const unsigned int /* file_version */
){
    std::shared_ptr< T > sp;
    ar >> boost::serialization::make_nvp("weak_ptr", sp);
    t = sp;
}

template<class Archive, class T>
inline void serialize(
    Archive & ar,
    std::weak_ptr< T > &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#endif // BOOST_NO_CXX11_SMART_PTR

#endif // BOOST_SERIALIZATION_WEAK_PTR_HPP

/* weak_ptr.hpp
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
*/