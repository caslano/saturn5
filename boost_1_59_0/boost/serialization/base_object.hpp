#ifndef BOOST_SERIALIZATION_BASE_OBJECT_HPP
#define BOOST_SERIALIZATION_BASE_OBJECT_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// base_object.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// if no archive headers have been included this is a no op
// this is to permit BOOST_EXPORT etc to be included in a
// file declaration header

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_polymorphic.hpp>

#include <boost/static_assert.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/force_include.hpp>
#include <boost/serialization/void_cast_fwd.hpp>

namespace boost {
namespace serialization {

namespace detail
{
    // get the base type for a given derived type
    // preserving the const-ness
    template<class B, class D>
    struct base_cast
    {
        typedef typename
        mpl::if_<
            is_const<D>,
            const B,
            B
        >::type type;
        BOOST_STATIC_ASSERT(is_const<type>::value == is_const<D>::value);
    };

    // only register void casts if the types are polymorphic
    template<class Base, class Derived>
    struct base_register
    {
        struct polymorphic {
            static void const * invoke(){
                Base const * const b = 0;
                Derived const * const d = 0;
                return & void_cast_register(d, b);
            }
        };
        struct non_polymorphic {
            static void const * invoke(){
                return 0;
            }
        };
        static void const * invoke(){
            typedef typename mpl::eval_if<
                is_polymorphic<Base>,
                mpl::identity<polymorphic>,
                mpl::identity<non_polymorphic>
            >::type type;
            return type::invoke();
        }
    };

} // namespace detail
template<class Base, class Derived>
typename detail::base_cast<Base, Derived>::type &
base_object(Derived &d)
{
    BOOST_STATIC_ASSERT(( is_base_and_derived<Base,Derived>::value));
    BOOST_STATIC_ASSERT(! is_pointer<Derived>::value);
    typedef typename detail::base_cast<Base, Derived>::type type;
    detail::base_register<type, Derived>::invoke();
    return access::cast_reference<type, Derived>(d);
}

} // namespace serialization
} // namespace boost

#endif // BOOST_SERIALIZATION_BASE_OBJECT_HPP

/* base_object.hpp
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
*/