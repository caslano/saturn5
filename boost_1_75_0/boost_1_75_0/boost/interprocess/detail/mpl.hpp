//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2016.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_MPL_HPP
#define BOOST_INTERPROCESS_DETAIL_MPL_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <cstddef>

namespace boost {
namespace interprocess {
namespace ipcdetail {

template <class T, T val>
struct integral_constant
{
   static const T value = val;
   typedef integral_constant<T,val> type;
};

template< bool C_ >
struct bool_ : integral_constant<bool, C_>
{
   static const bool value = C_;
};

typedef bool_<true>        true_;
typedef bool_<false>       false_;

typedef true_  true_type;
typedef false_ false_type;

typedef char yes_type;
struct no_type
{
   char padding[8];
};

template <bool B, class T = void>
struct enable_if_c {
  typedef T type;
};

template <class T>
struct enable_if_c<false, T> {};

template <class Cond, class T = void>
struct enable_if : public enable_if_c<Cond::value, T> {};

template <class Cond, class T = void>
struct disable_if : public enable_if_c<!Cond::value, T> {};

template<
      bool C
    , typename T1
    , typename T2
    >
struct if_c
{
    typedef T1 type;
};

template<
      typename T1
    , typename T2
    >
struct if_c<false,T1,T2>
{
    typedef T2 type;
};

template<
      typename T1
    , typename T2
    , typename T3
    >
struct if_
{
   typedef typename if_c<0 != T1::value, T2, T3>::type type;
};


template<std::size_t S>
struct ls_zeros
{
   static const std::size_t value = (S & std::size_t(1)) ? 0 : (1u + ls_zeros<(S >> 1u)>::value);
};

template<>
struct ls_zeros<0>
{
   static const std::size_t value = 0;
};

template<>
struct ls_zeros<1>
{
   static const std::size_t value = 0;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_MPL_HPP


/* mpl.hpp
tL4kRJHFthbpXIOKKBNf8PX2IZw7fjf9Q7ZGqWoGpy1ACZF/8EAlvuWkgG5zdaBahps97TpAmJHDNK62zrG6Bdn4qfLRfErs9fe7LyrM3rDRzczIti/P1v4S6yu9KSK2Mt8LVi1zzFlnjPgkQsQbSrn/piXrCCO6f2vcOY5YkQCa2ro3iH3v/idTRmiTrOo4QdhKPOlr2Z57Rvx6R34DLJP8ZMFl/LnpQaX6VqCBGvSi+kliULzaHh04MXB+lopaVpzOExkQ4PkrRTix9lsw1biCb/cZ1zTvbx4Pa/5DF8qAAwH9b6XLXx7N/1kwp7rVQ8vqzNgwYGCdcsmD+a6tpFQmRCBvYCFjBYX90Vcnto9u+IN7PCq/1bqFEcSyCudJTFfQfLffRw+dUr2Od5tsMGcuGM4GpiQx497R0cMK3lour7DDV+MHQf2NoGAfdAc396slX2xLXW8x0T/x/gY0i4Ops9zd/qt5NH2d/BiESfaXn4iFm4aAnbd84sHOM8IboLJT0GuQfZrPJHwtUflolj29w2M6OZw+1wppaW4ijUXQFkG/enFvWUBMBKMlX1dm38RRtp00itFfrmxD7teKb8pH5k9VdS0Z7yFI2cyozsaaKbUhPTw0rPBQN7zAN9xPx0+jogzcAjW9uOxuQNnKzHqa6oSnbkrKRXW9SAopvPnjwFaNn9ds05qK7z1n2nPQQIGzhAi8lYcBnST4
*/