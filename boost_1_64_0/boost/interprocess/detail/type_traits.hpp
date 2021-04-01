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
saDgcBRW8qU9MCPuMdLQL5Yf0u85kHiZMQe4B9U2I9f07KJApKNQzqhizFGLziKV2t468CB951iuPvuwOg5bFPPc5eeSj8BDK6AU+2PUA76EexHIcDS3lFOuX9k1cyuCb6EnwEOzYzh8ynmZ9WnWcrKSPwtyqWc7DbZuJQRRTxOaa8/YPloVVCHrcPJD1Svo0/AYXhlGB53SfnVEb5+5T37mJdgsh1wt/633DSEkP3xsJZHGAkDz2XjuGi2hzbRkljhSHc86eSOqC6eFDI/pC6I1oCRLXiViHpkJOtSGJL2Kl5xVEQC6acMx0cgOK6hExOv06eNtKxM36/Zz9/QjJcDt2YElX7FlfNt9dhy+cEYVjw6lOBnxu93PMl9+Dy4TxOuXmKCHEdHWJti+wJol36pWk3wOMSNvfGUVZ8/WNOogigw706CNn6nlgsT4wNY65obOqnM2886d95CgoqQvO+hGCNppvZmr/tS/IQgV3V7FGh3CCdtp62j91Pbrywt1R056zbNZHS1/AQf3mUZvyE6I63etdNr0tXSkn2iFJnjrPVFxth212o6ykA==
*/