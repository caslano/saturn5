#ifndef BOOST_SERIALIZATION_SHARED_PTR_132_HPP
#define BOOST_SERIALIZATION_SHARED_PTR_132_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// shared_ptr.hpp: serialization for boost shared pointer

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// note: totally unadvised hack to gain access to private variables
// in shared_ptr and shared_count. Unfortunately its the only way to
// do this without changing shared_ptr and shared_count
// the best we can do is to detect a conflict here
#include <boost/config.hpp>

#include <list>
#include <cstddef> // NULL

#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/void_cast.hpp>

// mark base class as an (uncreatable) base class
#include <boost/serialization/detail/shared_ptr_132.hpp>

/////////////////////////////////////////////////////////////
// Maintain a couple of lists of loaded shared pointers of the old previous
// version (1.32)

namespace boost_132 {
namespace serialization {
namespace detail {

struct null_deleter {
    void operator()(void const *) const {}
};

} // namespace detail
} // namespace serialization
} // namespace boost_132

/////////////////////////////////////////////////////////////
// sp_counted_base_impl serialization

namespace boost {
namespace serialization {

template<class Archive, class P, class D>
inline void serialize(
    Archive & /* ar */,
    boost_132::detail::sp_counted_base_impl<P, D> & /* t */,
    const unsigned int /*file_version*/
){
    // register the relationship between each derived class
    // its polymorphic base
    boost::serialization::void_cast_register<
        boost_132::detail::sp_counted_base_impl<P, D>,
        boost_132::detail::sp_counted_base
    >(
        static_cast<boost_132::detail::sp_counted_base_impl<P, D> *>(NULL),
        static_cast<boost_132::detail::sp_counted_base *>(NULL)
    );
}

template<class Archive, class P, class D>
inline void save_construct_data(
    Archive & ar,
    const
    boost_132::detail::sp_counted_base_impl<P, D> *t,
    const unsigned int /* file_version */
){
    // variables used for construction
    ar << boost::serialization::make_nvp("ptr", t->ptr);
}

template<class Archive, class P, class D>
inline void load_construct_data(
    Archive & ar,
    boost_132::detail::sp_counted_base_impl<P, D> * t,
    const unsigned int /* file_version */
){
    P ptr_;
    ar >> boost::serialization::make_nvp("ptr", ptr_);
    // ::new(t)boost_132::detail::sp_counted_base_impl<P, D>(ptr_,  D());
    // placement
    // note: the original ::new... above is replaced by the one here.  This one
    // creates all new objects with a null_deleter so that after the archive
    // is finished loading and the shared_ptrs are destroyed - the underlying
    // raw pointers are NOT deleted.  This is necessary as they are used by the
    // new system as well.
    ::new(t)boost_132::detail::sp_counted_base_impl<
        P,
        boost_132::serialization::detail::null_deleter
    >(
        ptr_,  boost_132::serialization::detail::null_deleter()
    ); // placement new
    // compensate for that fact that a new shared count always is
    // initialized with one. the add_ref_copy below will increment it
    // every time its serialized so without this adjustment
    // the use and weak counts will be off by one.
    t->use_count_ = 0;
}

} // serialization
} // namespace boost

/////////////////////////////////////////////////////////////
// shared_count serialization

namespace boost {
namespace serialization {

template<class Archive>
inline void save(
    Archive & ar,
    const boost_132::detail::shared_count &t,
    const unsigned int /* file_version */
){
    ar << boost::serialization::make_nvp("pi", t.pi_);
}

template<class Archive>
inline void load(
    Archive & ar,
    boost_132::detail::shared_count &t,
    const unsigned int /* file_version */
){
    ar >> boost::serialization::make_nvp("pi", t.pi_);
    if(NULL != t.pi_)
        t.pi_->add_ref_copy();
}

} // serialization
} // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE(boost_132::detail::shared_count)

/////////////////////////////////////////////////////////////
// implement serialization for shared_ptr< T >

namespace boost {
namespace serialization {

template<class Archive, class T>
inline void save(
    Archive & ar,
    const boost_132::shared_ptr< T > &t,
    const unsigned int /* file_version */
){
    // only the raw pointer has to be saved
    // the ref count is maintained automatically as shared pointers are loaded
    ar.register_type(static_cast<
        boost_132::detail::sp_counted_base_impl<T *, boost::checked_deleter< T > > *
    >(NULL));
    ar << boost::serialization::make_nvp("px", t.px);
    ar << boost::serialization::make_nvp("pn", t.pn);
}

template<class Archive, class T>
inline void load(
    Archive & ar,
    boost_132::shared_ptr< T > &t,
    const unsigned int /* file_version */
){
    // only the raw pointer has to be saved
    // the ref count is maintained automatically as shared pointers are loaded
    ar.register_type(static_cast<
        boost_132::detail::sp_counted_base_impl<T *, boost::checked_deleter< T > > *
    >(NULL));
    ar >> boost::serialization::make_nvp("px", t.px);
    ar >> boost::serialization::make_nvp("pn", t.pn);
}

template<class Archive, class T>
inline void serialize(
    Archive & ar,
    boost_132::shared_ptr< T > &t,
    const unsigned int file_version
){
    // correct shared_ptr serialization depends upon object tracking
    // being used.
    BOOST_STATIC_ASSERT(
        boost::serialization::tracking_level< T >::value
        != boost::serialization::track_never
    );
    boost::serialization::split_free(ar, t, file_version);
}

} // serialization
} // namespace boost

// note: change below uses null_deleter
// This macro is used to export GUIDS for shared pointers to allow
// the serialization system to export them properly. David Tonge
#define BOOST_SHARED_POINTER_EXPORT_GUID(T, K)                     \
    typedef boost_132::detail::sp_counted_base_impl<               \
        T *,                                                       \
        boost::checked_deleter< T >                                \
    > __shared_ptr_ ## T;                                          \
    BOOST_CLASS_EXPORT_GUID(__shared_ptr_ ## T, "__shared_ptr_" K) \
    BOOST_CLASS_EXPORT_GUID(T, K)                                  \
    /**/

#define BOOST_SHARED_POINTER_EXPORT(T)                             \
    BOOST_SHARED_POINTER_EXPORT_GUID(                              \
        T,                                                         \
        BOOST_PP_STRINGIZE(T)                                      \
    )                                                              \
    /**/

#endif // BOOST_SERIALIZATION_SHARED_PTR_132_HPP

/* shared_ptr_132.hpp
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
*/