//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012.
// (C) Copyright Gennaro Prota 2003 - 2004.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_POINTER_TYPE_HPP
#define BOOST_INTERPROCESS_DETAIL_POINTER_TYPE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/type_traits.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

struct two {char _[2];};

namespace pointer_type_imp {

template <class U> static two  test(...);
template <class U> static char test(typename U::pointer* = 0);

}  //namespace pointer_type_imp {

template <class T>
struct has_pointer_type
{
    static const bool value = sizeof(pointer_type_imp::test<T>(0)) == 1;
};

namespace pointer_type_imp {

template <class T, class D, bool = has_pointer_type<D>::value>
struct pointer_type
{
    typedef typename D::pointer type;
};

template <class T, class D>
struct pointer_type<T, D, false>
{
    typedef T* type;
};

}  //namespace pointer_type_imp {

template <class T, class D>
struct pointer_type
{
    typedef typename pointer_type_imp::pointer_type<T,
        typename remove_reference<D>::type>::type type;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_POINTER_TYPE_HPP


/* pointer_type.hpp
YNz/xbEicH4ggXkjYvSBuTa6oePv41dybd95J8grOas1ITlK2wKo+mCmUR2si7iNV8T+0AM8Q8R8BcPknTAonLe/h3Eo0wAKgxeKQO/ko/OtNyhAOqsXqXQVnwpHagomd+LkuhHLsMrOT0Bs+8Y0lxRt88NPCMThcHgr5VU2YMyGxc6EYYU9nxNYGBnY0dzPoODCEQagZnFY7Wt+hP1lrL8ThclCsuSnHKf/dFHx6l4pHJpjYsdQQEgE47Ic4rh/wyq0Lk9XrWLgphYwedwlirNKTHfgQaPWfP9SsR0DDMTn1PLJu00NNVxOk9Lj/TA/Vu4wb5KWDG2zJB4VUVSuYfmhNx0Gy79wdmJ/gqyVFJMvhNgrD3UQw/ocw9x0TtU8Re3NiOO2cQWg4/5AjxvlhyE41Bb1lw22Xg+6EFjkch4XJqBCPPpdmRSsDVv0LsRi6ifEDn3GOVG7Dmp4lqZ61KJ+5o7uBdOwd8GEbExazYvSZ0dm6o4EK6HhHuvbAKF4060pw38I8dJQdl7TRIycu06ABLuJ3FoZWTsGOJX0K6Joe8Ik32mJtmx+Ag==
*/