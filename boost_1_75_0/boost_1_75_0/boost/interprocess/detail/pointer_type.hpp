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
UAeruVmny5Po0K7y8gVXVcwKcPMgBEZzLJrHdKE3RN3XHHT8eP8ztdyDsCZNkQVhj3TBuvnmR+Lge835KJkKxoR/9eyMSLUOQElJQJucmQtVKsZlbNwrDsdT14YzpK8rLckuoR7nEb6WVX7pwSY00WAZ/BXaa7zV0ly9v0djPzDi3/g/loE1m3CiE3NkSSM7tpPaixKSra5FL87xWYUf36ieBOusRoIZFGg/vezaS+xumgvfhQeIIV486HHRJ6Dd2BYysV7049RxF3D+Q+aUTwpJqLyRTEhPvXd4fuDVSA9jgng/Qj6D9V68Xr5Zh5CusXsz7KYVx32Z8sgccUqirU1jD1gWKKzc5w4azbhke4k42T3yhtzzc7oJN42pgkdOMTAMBDoSYttpQ8S3fV2GUZBtvbTjeod1t9+VMnQmUFh4Ypycv8eIVHaJXp4OwcHP5OFl7KM+vfKDpqjB09ls3UculHOu66a90LPWfWxUGdjtxWW/RtljOjaeeieLlr+06Dz/pLyo3Tl2OJjsZ1W32ziNMSvPC+dE/1576ze3iLZ4ZTITE3whX2ipmqawQH7MPZ/me6enP/xurN0+BS2MPFUnIUwsCPw+FbnGFNV0/CX/5nCsvxF+369FL+I4wmUYbUNuKQ++QjH0eZ4lG9YFHL2kODgfDhnAXhrVZUZJupBifJA6RITM42xlb8uNT7j75vui2a8MocWymVEv
*/