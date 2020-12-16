//////////////////////////////////////////////////////////////////////////////
// (C) Copyright John Maddock 2000.
// (C) Copyright Ion Gaztanaga 2005-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_TYPE_TRAITS_HPP
#define BOOST_INTERPROCESS_DETAIL_TYPE_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

struct nat{};

template<class T>
struct remove_reference
{
   typedef T type;
};

template<class T>
struct remove_reference<T&>
{
   typedef T type;
};

template<class T>
struct is_reference
{
   static const bool value = false;
};

template<class T>
struct is_reference<T&>
{
   static const bool value = true;
};

template<class T>
struct is_pointer
{
   static const bool value = false;
};

template<class T>
struct is_pointer<T*>
{
   static const bool value = true;
};

template <typename T>
struct add_reference
{
    typedef T& type;
};

template<class T>
struct add_reference<T&>
{
    typedef T& type;
};

template<>
struct add_reference<void>
{
    typedef nat &type;
};

template<>
struct add_reference<const void>
{
    typedef const nat &type;
};

template <class T>
struct add_const_reference
{  typedef const T &type;   };

template <class T>
struct add_const_reference<T&>
{  typedef T& type;   };

template<class T>
struct remove_const
{
   typedef T type;
};

template<class T>
struct remove_const<const T>
{
   typedef T type;
};

template<class T>
struct remove_volatile
{
   typedef T type;
};

template<class T>
struct remove_volatile<volatile T>
{
   typedef T type;
};

template<class T>
struct remove_const_volatile
{
   typedef typename remove_const<typename remove_volatile<T>::type>::type type;
};

template <typename T, typename U>
struct is_same
{
   typedef char yes_type;
   struct no_type
   {
      char padding[8];
   };

   template <typename V>
   static yes_type is_same_tester(V*, V*);
   static no_type is_same_tester(...);

   static T *t;
   static U *u;

   static const bool value = sizeof(yes_type) == sizeof(is_same_tester(t,u));
};

template<class T, class U>
struct is_cv_same
{
   static const bool value = is_same< typename remove_const_volatile<T>::type
                                    , typename remove_const_volatile<U>::type >::value;
};

} // namespace ipcdetail
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_TYPE_TRAITS_HPP

/* type_traits.hpp
zi2jPjr78NBvHrxjfd2HWv0O6af3tqu4L/vhUf0uTN/79bbjD6avxfek9N6yxjd+v3TMhsnXt7vi9zFdIo/iPkPK75nDz0f85tqlawe/dyorb0qrI/imMqDcL3gnOyr/yuHXfRi5orhl24y7oVMT/72/njl2h+/rD56+56KzG9atvAdncNRX7r2uKltz3crEQNp7J7493fq5IdBG/co9ITpn6Gtjjhe0a/XrGxcvfPB76I+UX889ec1bXnuqZ+PTjWPjn5jxPmyxVJ6LGvz6+efnNZ5w8K45TxxpO6Ub4if3N65+8+Wz3685ufDmCxs9tmoK0rib4n+s34iTZy7r9ubtX378UraZ/We0Lcpv7x/atB5/avENWwdPTjxe5+Yl0FkpXzvXzPtV+1W7Zn7c6Ket37dp1gV6Irk/cOe96df5vD+nZXd/sPCT7lmwmVN5vvDGxK8eyG9y7Oxtm9Lfb/HY37HeQ/nd9umkZr+Z/mDd66MOmAmn7n8S36RGK/eHJi2aeDyw+t5rtzQ8cuC+W/fBnknl9mJ0wz2ZXbq80Nd/cc95TQc2wRhI9dsvOffUNVNnXeydPytq8Ze5b2KuQO7v3vrpy2m5eXcu/W7RjO3NH0BeTylbDTV33sd1SO7s+Srk9zchv78N+f1dyO+f5fdw0Fn9m+6H6WEakCfo3/J7lcFzkL1qjPTQGSv0uwC/fy2/L/OhDOV3Kn7fL7+z8XuH/G6O9G+X3y1R3n9X41HwLnOysbOfV/lLHjv5jAq6qgSo5Gg3oAqXqnglXAeD0+lXfBLuZoPDrQJGAm8BNlTyFdhe2SQMjidDMV3E8QyUeOoA0yWePIlnjsQzV+IpACYBi4GdgPOAKsxCiXcIaLrE213iDQB7S7yLJd5rJN4lwPMNcqT0rQB2A66U+NYG75Sm+6q5nOqDlkt8DT0cXxwwTo2JwET1biDdAwzsqGyPHo63HbA14mkPbA/sCLzUZP7OwBRgX2Bn4OXALsDpwG7AbOLjdPUI3vks90jvlfEweD5OX9RXPLeJinbA/sBewLSQejwo4TMovL0ee0r4y4B9gb2AafI8kJ51+aTKXbMXu5RPU79R0ZTaIJdvC2B/9R7gGNUEgHnA1kBlOmsLVGEvBt6k8gO8U7U14D0SbjvwEuBh1Y6Bfrz3UmCiSf6Urhiv3N9Kd9pyujJBPq+ln1TUVTZdk+upucntqAVwMPBGoOqXrYCTVTqBJSqdwPnANianpy1wi/A/yGVQ8YJKL/A11Z6Aqo/fAPxA+D5S/Qv4tfifEv8fxf8nYFfgeSb7J5js38Rk/wuAPYFtxf9S8e8u/vAz+gDHAfsCrwD2A+YB+wOXSbibJdxaCXcbcIDKD/A6lR/he0z4dgnfU8ChwGeAw4EHgSOAbwBHAQ8DM4B/k/A/SPgzEv5n4HigB3JsArChh/mSPMzXzMN8LYCTVH6Ak4F9gFOBo4V/ovBPE/5M4JXAHGCWyi8wB1gAzAUukXArJdwtEm4NMA/4e/G/X/y3iv8fgAXA7eL/jPi/IP4vAucBXxf/D8T/E/E/CixR5QAsBSpBWwb0e9m/DnCRql8vh2/p5fBtxf9i4LXAS8S/l/inin8acBkw38v1Vih8VwnfYuLjfjE9eF8nsFz6fSRofFCZCxgVym9AgOVZeoDl2aAAy5HBwN5KzgJHAYcCVZzDgGVqLAP+neWp3MuJ98l7zgtZK0kBH40z8p7O8p4uAZYzXQPcH/sFWN50B45Qcg84TsmnAPfLy4BZSr4DZwP7AIsoHKdjv3VfJMZJkU8JoD2SjtHy3rHAzsBxwJ7AicAJwEnAK4GTA9z/pwKVzMsG/haYC9wGnAncBZwF/AQ=
*/