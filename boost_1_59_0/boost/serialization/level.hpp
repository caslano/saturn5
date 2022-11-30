#ifndef BOOST_SERIALIZATION_LEVEL_HPP
#define BOOST_SERIALIZATION_LEVEL_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// level.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/type_traits/is_fundamental.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/integral_c_tag.hpp>

#include <boost/serialization/level_enum.hpp>

namespace boost {
namespace serialization {

struct basic_traits;

// default serialization implementation level
template<class T>
struct implementation_level_impl {
    template<class U>
    struct traits_class_level {
        typedef typename U::level type;
    };

    typedef mpl::integral_c_tag tag;
    // note: at least one compiler complained w/o the full qualification
    // on basic traits below
    typedef
        typename mpl::eval_if<
            is_base_and_derived<boost::serialization::basic_traits, T>,
            traits_class_level< T >,
        //else
        typename mpl::eval_if<
            is_fundamental< T >,
            mpl::int_<primitive_type>,
        //else
        typename mpl::eval_if<
            is_class< T >,
            mpl::int_<object_class_info>,
        //else
        typename mpl::eval_if<
            is_array< T >,
                mpl::int_<object_serializable>,
        //else
        typename mpl::eval_if<
            is_enum< T >,
                mpl::int_<primitive_type>,
        //else
            mpl::int_<not_serializable>
        >
        >
        >
        >
        >::type type;
        // vc 7.1 doesn't like enums here
    BOOST_STATIC_CONSTANT(int, value = type::value);
};

template<class T>
struct implementation_level :
    public implementation_level_impl<const T>
{
};

template<class T, int L>
inline bool operator>=(implementation_level< T > t, enum level_type l)
{
    return t.value >= (int)l;
}

} // namespace serialization
} // namespace boost

// specify the level of serialization implementation for the class
// require that class info saved when versioning is used
#define BOOST_CLASS_IMPLEMENTATION(T, E)                 \
    namespace boost {                                    \
    namespace serialization {                            \
    template <>                                          \
    struct implementation_level_impl< const T >                     \
    {                                                    \
        typedef mpl::integral_c_tag tag;                 \
        typedef mpl::int_< E > type;                     \
        BOOST_STATIC_CONSTANT(                           \
            int,                                         \
            value = implementation_level_impl::type::value    \
        );                                               \
    };                                                   \
    }                                                    \
    }
    /**/

#endif // BOOST_SERIALIZATION_LEVEL_HPP

/* level.hpp
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
*/