#ifndef BOOST_SERIALIZATION_TYPE_INFO_IMPLEMENTATION_HPP
#define BOOST_SERIALIZATION_TYPE_INFO_IMPLEMENTATION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// type_info_implementation.hpp: interface for portable version of type_info

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/static_assert.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/serialization/traits.hpp>

namespace boost {
namespace serialization {

// note that T and const T are folded into const T so that
// there is only one table entry per type
template<class T>
struct type_info_implementation {
    template<class U>
    struct traits_class_typeinfo_implementation {
      typedef typename U::type_info_implementation::type type;
    };
    // note: at least one compiler complained w/o the full qualification
    // on basic traits below
    typedef
        typename mpl::eval_if<
            is_base_and_derived<boost::serialization::basic_traits, T>,
            traits_class_typeinfo_implementation< T >,
        //else
            mpl::identity<
                typename extended_type_info_impl< T >::type
            >
        >::type type;
};

} // namespace serialization
} // namespace boost

// define a macro to assign a particular derivation of extended_type_info
// to a specified a class.
#define BOOST_CLASS_TYPE_INFO(T, ETI)              \
namespace boost {                                  \
namespace serialization {                          \
template<>                                         \
struct type_info_implementation< T > {             \
    typedef ETI type;                              \
};                                                 \
template<>                                         \
struct type_info_implementation< const T > {       \
    typedef ETI type;                              \
};                                                 \
}                                                  \
}                                                  \
/**/

#endif /// BOOST_SERIALIZATION_TYPE_INFO_IMPLEMENTATION_HPP

/* type_info_implementation.hpp
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
*/