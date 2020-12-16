//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_DETAIL_META_UTILS_CORE_HPP
#define BOOST_MOVE_DETAIL_META_UTILS_CORE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//Small meta-typetraits to support move

namespace boost {
namespace move_detail {

template<typename T>
struct voider { typedef void type; };

//////////////////////////////////////
//             if_c
//////////////////////////////////////
template<bool C, typename T1, typename T2>
struct if_c
{
   typedef T1 type;
};

template<typename T1, typename T2>
struct if_c<false,T1,T2>
{
   typedef T2 type;
};

//////////////////////////////////////
//             if_
//////////////////////////////////////
template<typename T1, typename T2, typename T3>
struct if_ : if_c<0 != T1::value, T2, T3>
{};

//////////////////////////////////////
//          enable_if_c
//////////////////////////////////////
struct enable_if_nat{};

template <bool B, class T = enable_if_nat>
struct enable_if_c
{
   typedef T type;
};

template <class T>
struct enable_if_c<false, T> {};

//////////////////////////////////////
//           enable_if
//////////////////////////////////////
template <class Cond, class T = enable_if_nat>
struct enable_if : enable_if_c<Cond::value, T> {};

//////////////////////////////////////
//          disable_if_c
//////////////////////////////////////
template <bool B, class T = enable_if_nat>
struct disable_if_c
   : enable_if_c<!B, T>
{};

//////////////////////////////////////
//          disable_if
//////////////////////////////////////
template <class Cond, class T = enable_if_nat>
struct disable_if : enable_if_c<!Cond::value, T> {};

//////////////////////////////////////
//          integral_constant
//////////////////////////////////////
template<class T, T v>
struct integral_constant
{
   static const T value = v;
   typedef T value_type;
   typedef integral_constant<T, v> type;

     operator T() const { return value; }
   T operator()() const { return value; }
};

typedef integral_constant<bool, true >  true_type;
typedef integral_constant<bool, false > false_type;


//////////////////////////////////////
//             is_same
//////////////////////////////////////
template<class T, class U>
struct is_same
{
   static const bool value = false;
};
 
template<class T>
struct is_same<T, T>
{
   static const bool value = true;
};

//////////////////////////////////////
//        enable_if_same
//////////////////////////////////////
template <class T, class U, class R = enable_if_nat>
struct enable_if_same : enable_if<is_same<T, U>, R> {};

//////////////////////////////////////
//        disable_if_same
//////////////////////////////////////
template <class T, class U, class R = enable_if_nat>
struct disable_if_same : disable_if<is_same<T, U>, R> {};

}  //namespace move_detail {
}  //namespace boost {

#endif //#ifndef BOOST_MOVE_DETAIL_META_UTILS_CORE_HPP

/* meta_utils_core.hpp
L5UXealc5EEKMZBXevAob8RBobytz3sPUieVHLROKj54nVR0kDrJc5A6yXuQOml390HidzSjHKQmYa3hoDtrQSn3jPpKrTlQrqv0D+8w/Luf/7qPLf+c8TbIP6488o/rYDG43c8dPGHh4MxDxEoPCsu+7PGig8ThaL47eJ1UcpA6yXuQOmnEQeuk0oPXSSMPSidd9rj/oM2sow4Ww7ts9+iDRHmBg0R5W7t9B62byt4VgN79sPwzheWfyc774wzLzi627OzYEYJeHbtocieo7NezYroPGl0rEPv1PfnClbzh+ROjZD1fyXq+cCVveFagTc092H6wqV3H/lM7654z1ev9UFf3I7cRoxaMUQrE5A/WC1aiF6xEL1iJnj+4Ix7emWjqwJ4C/TbvJPuUEE6zwHSyzeuW67BxBbL+uIs3YNqx993v3IahTX7a2rfYD5wGWQ5rOEItFKHkj8gOzdrkEesCBwPvX6xaLtI5Ri0YoxSIyR+8iyvfJTuTdE9vYC0ZJNUQvvzAoWU8aO1udVF68spEm0293+J9uV2ETnh8zkRXj7M1spEbx5ZVj43DPrS9D9UbEWqhCCV/RN5QvVAFeqEK9EIV6HlCh9qHsVxU6di/FJtvWEt2xT1yTeRhNQd+TeT/7cfyN3Y3HaXV6mhpqqkvGucwB7aNdRnuCImam/11LeSDyF9HqcGm+RSEl50mWFdkmka8OMJ4SKB9swhhbEIz4Lh+Ml3b1Hd1MWVnaXeAnVANSELyofnvSJuCcOJbUoMkeI77lvSeRIcWHDaDPWiiw6aQ362WsykxNZNb3nwGTje1043U+i/eSDs3nMVfRGLWqJ64f5lZGOWFFHbOmJ74OQt9yTVsUFZHjDUTrx7C68LmFCQwqqBJIaOFnnr9KqnAmnHsssoXmkPJaN+MIpqNlviSP/wPGh3m+U9FvJCIi+WC8T4rPtf/SbV1Hu0C8zwkkS6OOD70/Hg1eSYXM5UP4VTgbOYaN87svma4sgo26h3l4iz/ESsCg+BRCWVDCSX56IGiLhP+isLwH2HAHz2VUvKxOQWATfMnj2OYDcfv7qhCv3STbHL0+mKmjfVl+OcZ5sG+A8O3OkS8ki8+UhFxCeq2MP+oeZIaMCdeWtifshJY5/QP9H4b+6cfapzYyj3/f7x9vtcFn6SWM6MP0sqDfXiyj/z9YwblnXseHOyto3tEPLHxNCujZaV0XIuc+tf5yMUEPD00+sltjxw+O9pMPTZWvqEEHC7mTzQrf7ufo1HdZz49jPPCJxD8kYloKc6b7Tkxy59ytcRM05ahgZX6/UeYZ5NHUnvC6Tlx93CuT0V96KHc82MPTwT+svymGlg4hCIAJBtQ+XDM7nBESqNVilTNSJw1tk7InSBHCQ1vN+LFePVmpgH2aQbXJ1jcKW/t6JvDX5onNoMs3X1818udQJBqkNxHN5tT1hyqfk6cjvjQUzg4J17nwZUCHucB2tlU0thYE5Wk8s0eYVAuk5BLipHMVAxJZfQUomKme1hSU7gw6oPpPioOo3MaE0mD36KCt9I6bp/dDyO42ume5GEW+q0wo4rC59+PtcYHRkfEZY2P94w4sPFBdSO68LsFb8l6Ve48aKIQuoxnLIVUIKSI/xW6vzfK/O9Yh7+pchLtWpt76DYI+vWA5fWMjVKTkxO0uMfgzlorJdVuleFxyzjTNdSrXirs20maFFNupg947TFcCJHVPJN7t4tzEd9oWtqoH7pROhu1LuOTQHfCaSgwvbT1KRJJl8JTfHt4qXE5ikL+CFbTlII7sMPd8fC21uZtLoLO8tR4ivaICWTEY0LY8x6GkFYJjXpgb5p9e0Xc+oPFvB7q/YAXgD0kw3E=
*/