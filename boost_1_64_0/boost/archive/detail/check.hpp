#ifndef BOOST_ARCHIVE_DETAIL_CHECK_HPP
#define BOOST_ARCHIVE_DETAIL_CHECK_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#pragma inline_depth(511)
#pragma inline_recursion(on)
#endif

#if defined(__MWERKS__)
#pragma inline_depth(511)
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
Ty/5dZ2wI2OPgIqF7Yif4TRl8vpcZn86NtRw8vT4W06eHr/xyMQ0NMgvNYx0C14xsRxs/4rx94Eamihw/E/Sy4OW/boed7jFnvMva4bp0PFHV8IGLYoOCoRxv7+OrXp//thz9EImN8/E+qaYRgTCKLb3p8c3BMpv4hGxyz4Yj45cFhcSGBULg/b+xvzAoJUrPzA/ajz4oXjMpPiy6CVhi2N+nf5lU03hh+UQfj8+Ef5wfKzPRcfEQLv8hfnxkSvH9+a3rx//zD4Ujw6LWLHsvfWNd83o8eCH4vCxBS6EhAhe8t78d/sKbRYWHD4pPt4kv06vCDNduPzdz5P723iCQZk8Pfa/0JCJ6cntCP0tOuTd7kZPLB8bHTvpfjorQ021lsVoQW32y/hHaICwsbtF/9I3x+NwX6PYiN88Bx3iME75/YeOQwmGKRgiFg+34NMKiXs3nDIWhkT8Mh+SY+zZ2qtDVkaOT//yWMZJYwXHy7tkgQFkWpBiMWHBWu825M8fsj8+phFyd3y85cqQRbHB70YAThr/OPnx5JPj4+02afqXthsfuakVDZ16Jcx+N/3ryLo/H1848Vn/Og3pEDvxAIpfn/cydv/4DzwVH+b/Mkx0PIn/FB9bNmLsQeRhMZDkY6uL/vN4TEgEDMMLgkEXcUErw8bGA0b/vuM2tOwHRl2Mvld+1/rg8pLf//0RGrzoA9vx/j2OCRO13EQtP1ErTtSsidpxonaaqF0nareJeuZE7T1Rz56ofdHfV/6O/VlsGvGPtMO77wN45W/K5PtqTqoh/peXvdv77vdMzKQYdnwBLBYHBT9RCO8V4t8opH+ykP/NBf2T5W9/jjBK9XeNa4iI/H3jIMa+vv6R/gVfJ385z6D+cNF6/svz28GkfjRz4F1cZsykuNyLd3H5cRPx99b/9r3jC/Y3835bIP7B6ZFJscnTb96LT86Byfv7l9Zz7NmHzxth3j9W/o59wbz3mvc/h/f3c/J7YSfWN3k7J73X+DaOvLff49s96Tg6Nm940vzxY+uk4+vYvL/0Ob2dmPd+/cvP2EnLT26fD3+ev10v+s3+fbiMTNrvd/v718ubSe3wbv//ehme1C5jP7/+G8uP7//kz37y9Afy6vfu7z9dJt7Msf9D5x3/zmco/JUCjfpPlnefzoa/sH0LJo4/xDGT4scmjj+UMZPir559ePk/TMRJ70D5+56H8L9esHDkIECL0BAdjtdMpIzYiIN0kQAJkQhZIAmSIhfkjqYhL+SD/GC8cwgKReEoAkWhBJSENqOtKB1loGyUh/JRESpFZaga1aA6dB5dR+2oE3WhR6gP9aNhhMGQMHQMA8PCqGLUMboYM4wVxgYjxXhgvDH+mABMECYUE4mJxazBJGCSMdsxuzCZmDzMIUwxpgRTjqnE1GDqMZcxjZjrmHZMN6YHM4B5iRnBULA0LBvLwxphzbA2WAnWCeuB9cbOxfphA7Eh2DBsODYem4hNwqZgt2PTsOnYXOwhbCG2FFuFrcM2YluwbdhObDe2DzuIHcJicAQcE8fGCXBCnAXOCifBSXHuOF+cH84fF4iLwEXhonHxuK24VFwGLhdXgCvCleIqcOdxDbgmXAuuHdeF68cN4oZxIzgSnoJn4FXx6nhdPB9vhHfAu+Dd8NPwXnhffAA+GB+GT8An4rfi0/DZ+Dx8Ab4EX4WvwZ/HX8Y34pvxHfge/Ah+FI8jUAg0gjyBRVAmqBP4BAFBRPAmzCUEEEII8YREQiohjZBOyCTkEPIJhYQiQimhmlBPaCA0EpoIzYRWQjdhgDBMIBHpRHmiMpFD5BGFRBFRSnQiuhOnET2JPkRfoj8xhLiKmEBMIiYTs4m5xDw=
*/