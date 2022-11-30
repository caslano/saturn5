#ifndef BOOST_ARCHIVE_DETAIL_CHECK_HPP
#define BOOST_ARCHIVE_DETAIL_CHECK_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#if !defined(__clang__)
#pragma inline_depth(255)
#pragma inline_recursion(on)
#endif
#endif

#if defined(__MWERKS__)
#pragma inline_depth(255)
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// check.hpp: interface for serialization system.

// (C) Copyright 2009 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_const.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/serialization/static_warning.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/wrapper.hpp>

namespace boost {
namespace archive {
namespace detail {

// checks for objects

template<class T>
inline void check_object_level(){
    typedef
        typename mpl::greater_equal<
            serialization::implementation_level< T >,
            mpl::int_<serialization::primitive_type>
        >::type typex;

    // trap attempts to serialize objects marked
    // not_serializable
    BOOST_STATIC_ASSERT(typex::value);
}

template<class T>
inline void check_object_versioning(){
    typedef
        typename mpl::or_<
            typename mpl::greater<
                serialization::implementation_level< T >,
                mpl::int_<serialization::object_serializable>
            >,
            typename mpl::equal_to<
                serialization::version< T >,
                mpl::int_<0>
            >
        > typex;
    // trap attempts to serialize with objects that don't
    // save class information in the archive with versioning.
    BOOST_STATIC_ASSERT(typex::value);
}

template<class T>
inline void check_object_tracking(){
    // presume it has already been determined that
    // T is not a const
    BOOST_STATIC_ASSERT(! boost::is_const< T >::value);
    typedef typename mpl::equal_to<
        serialization::tracking_level< T >,
        mpl::int_<serialization::track_never>
    >::type typex;
    // saving an non-const object of a type not marked "track_never)

    // may be an indicator of an error usage of the
    // serialization library and should be double checked.
    // See documentation on object tracking.  Also, see the
    // "rationale" section of the documenation
    // for motivation for this checking.

    BOOST_STATIC_WARNING(typex::value);
}

// checks for pointers

template<class T>
inline void check_pointer_level(){
    // we should only invoke this once we KNOW that T
    // has been used as a pointer!!
    typedef
        typename mpl::or_<
            typename mpl::greater<
                serialization::implementation_level< T >,
                mpl::int_<serialization::object_serializable>
            >,
            typename mpl::not_<
                typename mpl::equal_to<
                    serialization::tracking_level< T >,
                    mpl::int_<serialization::track_selectively>
                >
            >
        > typex;
    // Address the following when serializing to a pointer:

    // a) This type doesn't save class information in the
    // archive. That is, the serialization trait implementation
    // level <= object_serializable.
    // b) Tracking for this type is set to "track selectively"

    // in this case, indication that an object is tracked is
    // not stored in the archive itself - see level == object_serializable
    // but rather the existence of the operation ar >> T * is used to
    // infer that an object of this type should be tracked.  So, if
    // you save via a pointer but don't load via a pointer the operation
    // will fail on load without given any valid reason for the failure.

    // So if your program traps here, consider changing the
    // tracking or implementation level traits - or not
    // serializing via a pointer.
    BOOST_STATIC_WARNING(typex::value);
}

template<class T>
void inline check_pointer_tracking(){
    typedef typename mpl::greater<
        serialization::tracking_level< T >,
        mpl::int_<serialization::track_never>
    >::type typex;
    // serializing an object of a type marked "track_never" through a pointer
    // could result in creating more objects than were saved!
    BOOST_STATIC_WARNING(typex::value);
}

template<class T>
inline void check_const_loading(){
    typedef
        typename mpl::or_<
            typename boost::serialization::is_wrapper< T >,
            typename mpl::not_<
                typename boost::is_const< T >
            >
        >::type typex;
    // cannot load data into a "const" object unless it's a
    // wrapper around some other non-const object.
    BOOST_STATIC_ASSERT(typex::value);
}

} // detail
} // archive
} // boost

#endif // BOOST_ARCHIVE_DETAIL_CHECK_HPP

/* check.hpp
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
*/