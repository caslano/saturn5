#ifndef BOOST_SERIALIZATION_VERSION_HPP
#define BOOST_SERIALIZATION_VERSION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// version.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/integral_c_tag.hpp>

#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost {
namespace serialization {

struct basic_traits;

// default version number is 0. Override with higher version
// when class definition changes.
template<class T>
struct version
{
    template<class U>
    struct traits_class_version {
        typedef typename U::version type;
    };

    typedef mpl::integral_c_tag tag;
    // note: at least one compiler complained w/o the full qualification
    // on basic traits below
    typedef
        typename mpl::eval_if<
            is_base_and_derived<boost::serialization::basic_traits,T>,
            traits_class_version< T >,
            mpl::int_<0>
        >::type type;
    BOOST_STATIC_CONSTANT(int, value = version::type::value);
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
template<class T>
const int version<T>::value;
#endif

} // namespace serialization
} // namespace boost

/* note: at first it seemed that this would be a good place to trap
 * as an error an attempt to set a version # for a class which doesn't
 * save its class information (including version #) in the archive.
 * However, this imposes a requirement that the version be set after
 * the implemention level which would be pretty confusing.  If this
 * is to be done, do this check in the input or output operators when
 * ALL the serialization traits are available.  Included the implementation
 * here with this comment as a reminder not to do this!
 */

#include <boost/mpl/less.hpp>
#include <boost/mpl/comparison.hpp>

// specify the current version number for the class
// version numbers limited to 8 bits !!!
#define BOOST_CLASS_VERSION(T, N)                                      \
namespace boost {                                                      \
namespace serialization {                                              \
template<>                                                             \
struct version<T >                                                     \
{                                                                      \
    typedef mpl::int_<N> type;                                         \
    typedef mpl::integral_c_tag tag;                                   \
    BOOST_STATIC_CONSTANT(int, value = version::type::value);          \
    BOOST_MPL_ASSERT((                                                 \
        boost::mpl::less<                                              \
            boost::mpl::int_<N>,                                       \
            boost::mpl::int_<256>                                      \
        >                                                              \
    ));                                                                \
    /*                                                                 \
    BOOST_MPL_ASSERT((                                                 \
        mpl::equal_to<                                                 \
            :implementation_level<T >,                                 \
            mpl::int_<object_class_info>                               \
        >::value                                                       \
    ));                                                                \
    */                                                                 \
};                                                                     \
}                                                                      \
}

#endif // BOOST_SERIALIZATION_VERSION_HPP

/* version.hpp
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
*/