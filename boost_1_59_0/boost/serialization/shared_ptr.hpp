#ifndef BOOST_SERIALIZATION_SHARED_PTR_HPP
#define BOOST_SERIALIZATION_SHARED_PTR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// shared_ptr.hpp: serialization for boost shared pointer

// (C) Copyright 2004 Robert Ramey and Martin Ecker
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstddef> // NULL
#include <memory>

#include <boost/config.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/integral_c_tag.hpp>

#include <boost/detail/workaround.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/serialization/shared_ptr_helper.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/tracking.hpp>

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// boost:: shared_ptr serialization traits
// version 1 to distinguish from boost 1.32 version. Note: we can only do this
// for a template when the compiler supports partial template specialization

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    namespace boost {
    namespace serialization{
        template<class T>
        struct version< ::boost::shared_ptr< T > > {
            typedef mpl::integral_c_tag tag;
            #if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3206))
            typedef typename mpl::int_<1> type;
            #else
            typedef mpl::int_<1> type;
            #endif
            BOOST_STATIC_CONSTANT(int, value = type::value);
        };
        // don't track shared pointers
        template<class T>
        struct tracking_level< ::boost::shared_ptr< T > > {
            typedef mpl::integral_c_tag tag;
            #if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3206))
            typedef typename mpl::int_< ::boost::serialization::track_never> type;
            #else
            typedef mpl::int_< ::boost::serialization::track_never> type;
            #endif
            BOOST_STATIC_CONSTANT(int, value = type::value);
        };
    }}
    #define BOOST_SERIALIZATION_SHARED_PTR(T)
#else
    // define macro to let users of these compilers do this
    #define BOOST_SERIALIZATION_SHARED_PTR(T)                         \
    BOOST_CLASS_VERSION(                                              \
        ::boost::shared_ptr< T >,                                     \
        1                                                             \
    )                                                                 \
    BOOST_CLASS_TRACKING(                                             \
        ::boost::shared_ptr< T >,                                     \
        ::boost::serialization::track_never                           \
    )                                                                 \
    /**/
#endif

namespace boost {
namespace serialization{

struct null_deleter {
    void operator()(void const *) const {}
};

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// serialization for boost::shared_ptr

// Using a constant means that all shared pointers are held in the same set.
// Thus we detect handle multiple pointers to the same value instances
// in the archive.
void * const shared_ptr_helper_id = 0;

template<class Archive, class T>
inline void save(
    Archive & ar,
    const boost::shared_ptr< T > &t,
    const unsigned int /* file_version */
){
    // The most common cause of trapping here would be serializing
    // something like shared_ptr<int>.  This occurs because int
    // is never tracked by default.  Wrap int in a trackable type
    BOOST_STATIC_ASSERT((tracking_level< T >::value != track_never));
    const T * t_ptr = t.get();
    ar << boost::serialization::make_nvp("px", t_ptr);
}

#ifdef BOOST_SERIALIZATION_SHARED_PTR_132_HPP
template<class Archive, class T>
inline void load(
    Archive & ar,
    boost::shared_ptr< T > &t,
    const unsigned int file_version
){
    // something like shared_ptr<int>.  This occurs because int
    // is never tracked by default.  Wrap int in a trackable type
    BOOST_STATIC_ASSERT((tracking_level< T >::value != track_never));
    T* r;
    if(file_version < 1){
        ar.register_type(static_cast<
            boost_132::detail::sp_counted_base_impl<T *, null_deleter > *
        >(NULL));
        boost_132::shared_ptr< T > sp;
        ar >> boost::serialization::make_nvp("px", sp.px);
        ar >> boost::serialization::make_nvp("pn", sp.pn);
        // got to keep the sps around so the sp.pns don't disappear
        boost::serialization::shared_ptr_helper<boost::shared_ptr> & h =
            ar.template get_helper< shared_ptr_helper<boost::shared_ptr> >(
                shared_ptr_helper_id
            );
        h.append(sp);
        r = sp.get();
    }
    else{
        ar >> boost::serialization::make_nvp("px", r);
    }
    shared_ptr_helper<boost::shared_ptr> & h =
        ar.template get_helper<shared_ptr_helper<boost::shared_ptr> >(
            shared_ptr_helper_id
        );
    h.reset(t,r);
}
#else

template<class Archive, class T>
inline void load(
    Archive & ar,
    boost::shared_ptr< T > &t,
    const unsigned int /*file_version*/
){
    // The most common cause of trapping here would be serializing
    // something like shared_ptr<int>.  This occurs because int
    // is never tracked by default.  Wrap int in a trackable type
    BOOST_STATIC_ASSERT((tracking_level< T >::value != track_never));
    T* r;
    ar >> boost::serialization::make_nvp("px", r);

    boost::serialization::shared_ptr_helper<boost::shared_ptr> & h =
        ar.template get_helper<shared_ptr_helper<boost::shared_ptr> >(
            shared_ptr_helper_id
        );
    h.reset(t,r);
}
#endif

template<class Archive, class T>
inline void serialize(
    Archive & ar,
    boost::shared_ptr< T > &t,
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

} // namespace serialization
} // namespace boost

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// std::shared_ptr serialization traits
// version 1 to distinguish from boost 1.32 version. Note: we can only do this
// for a template when the compiler supports partial template specialization

#ifndef BOOST_NO_CXX11_SMART_PTR
#include <boost/static_assert.hpp>

// note: we presume that any compiler/library which supports C++11
// std::pointers also supports template partial specialization
// trap here if such presumption were to turn out to wrong!!!
#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_STATIC_ASSERT(false);
#endif

namespace boost {
namespace serialization{
    template<class T>
    struct version< ::std::shared_ptr< T > > {
        typedef mpl::integral_c_tag tag;
        typedef mpl::int_<1> type;
        BOOST_STATIC_CONSTANT(int, value = type::value);
    };
    // don't track shared pointers
    template<class T>
    struct tracking_level< ::std::shared_ptr< T > > {
        typedef mpl::integral_c_tag tag;
        typedef mpl::int_< ::boost::serialization::track_never> type;
        BOOST_STATIC_CONSTANT(int, value = type::value);
    };
}}
// the following just keeps older programs from breaking
#define BOOST_SERIALIZATION_SHARED_PTR(T)

namespace boost {
namespace serialization{

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// serialization for std::shared_ptr

template<class Archive, class T>
inline void save(
    Archive & ar,
    const std::shared_ptr< T > &t,
    const unsigned int /* file_version */
){
    // The most common cause of trapping here would be serializing
    // something like shared_ptr<int>.  This occurs because int
    // is never tracked by default.  Wrap int in a trackable type
    BOOST_STATIC_ASSERT((tracking_level< T >::value != track_never));
    const T * t_ptr = t.get();
    ar << boost::serialization::make_nvp("px", t_ptr);
}

template<class Archive, class T>
inline void load(
    Archive & ar,
    std::shared_ptr< T > &t,
    const unsigned int /*file_version*/
){
    // The most common cause of trapping here would be serializing
    // something like shared_ptr<int>.  This occurs because int
    // is never tracked by default.  Wrap int in a trackable type
    BOOST_STATIC_ASSERT((tracking_level< T >::value != track_never));
    T* r;
    ar >> boost::serialization::make_nvp("px", r);
    //void (* const id)(Archive &, std::shared_ptr< T > &, const unsigned int) = & load;
    boost::serialization::shared_ptr_helper<std::shared_ptr> & h =
        ar.template get_helper<
            shared_ptr_helper<std::shared_ptr>
        >(
            shared_ptr_helper_id
        );
    h.reset(t,r);
}

template<class Archive, class T>
inline void serialize(
    Archive & ar,
    std::shared_ptr< T > &t,
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

} // namespace serialization
} // namespace boost

#endif // BOOST_NO_CXX11_SMART_PTR

#endif // BOOST_SERIALIZATION_SHARED_PTR_HPP

/* shared_ptr.hpp
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
*/