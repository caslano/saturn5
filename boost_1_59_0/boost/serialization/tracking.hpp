#ifndef BOOST_SERIALIZATION_TRACKING_HPP
#define BOOST_SERIALIZATION_TRACKING_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// tracking.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/integral_c_tag.hpp>

#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/tracking_enum.hpp>
#include <boost/serialization/type_info_implementation.hpp>

namespace boost {
namespace serialization {

struct basic_traits;

// default tracking level
template<class T>
struct tracking_level_impl {
    template<class U>
    struct traits_class_tracking {
        typedef typename U::tracking type;
    };
    typedef mpl::integral_c_tag tag;
    // note: at least one compiler complained w/o the full qualification
    // on basic traits below
    typedef
        typename mpl::eval_if<
            is_base_and_derived<boost::serialization::basic_traits, T>,
            traits_class_tracking< T >,
        //else
        typename mpl::eval_if<
            is_pointer< T >,
            // pointers are not tracked by default
            mpl::int_<track_never>,
        //else
        typename mpl::eval_if<
            // for primitives
            typename mpl::equal_to<
                implementation_level< T >,
                mpl::int_<primitive_type>
            >,
            // is never
            mpl::int_<track_never>,
            // otherwise its selective
            mpl::int_<track_selectively>
    >  > >::type type;
    BOOST_STATIC_CONSTANT(int, value = type::value);
};

template<class T>
struct tracking_level :
    public tracking_level_impl<const T>
{
};

template<class T, enum tracking_type L>
inline bool operator>=(tracking_level< T > t, enum tracking_type l)
{
    return t.value >= (int)l;
}

} // namespace serialization
} // namespace boost


// The STATIC_ASSERT is prevents one from setting tracking for a primitive type.
// This almost HAS to be an error.  Doing this will effect serialization of all
// char's in your program which is almost certainly what you don't want to do.
// If you want to track all instances of a given primitive type, You'll have to
// wrap it in your own type so its not a primitive anymore.  Then it will compile
// without problem.
#define BOOST_CLASS_TRACKING(T, E)           \
namespace boost {                            \
namespace serialization {                    \
template<>                                   \
struct tracking_level< T >                   \
{                                            \
    typedef mpl::integral_c_tag tag;         \
    typedef mpl::int_< E> type;              \
    BOOST_STATIC_CONSTANT(                   \
        int,                                 \
        value = tracking_level::type::value  \
    );                                       \
    /* tracking for a class  */              \
    BOOST_STATIC_ASSERT((                    \
        mpl::greater<                        \
            /* that is a prmitive */         \
            implementation_level< T >,       \
            mpl::int_<primitive_type>        \
        >::value                             \
    ));                                      \
};                                           \
}}

#endif // BOOST_SERIALIZATION_TRACKING_HPP

/* tracking.hpp
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
*/