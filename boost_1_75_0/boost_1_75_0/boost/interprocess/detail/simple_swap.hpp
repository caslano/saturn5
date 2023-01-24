#ifndef BOOST_INTERPROCESS_DETAIL_SWAP_HPP
#define BOOST_INTERPROCESS_DETAIL_SWAP_HPP
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost { namespace interprocess {

template<class T>
void simple_swap(T&x, T&y)
{  T tmp(x); x = y; y = tmp;  }

}}  //namespace boost{ namespace interprocess {

#endif //#ifndef BOOST_INTERPROCESS_DETAIL_SWAP_HPP

/* simple_swap.hpp
Saj9+4rd9gobL86m7Txf2yHqSzEOqofm64GSph6UdtaoUQtUmXP/yag1qsJxszmQSxRRGvoqc+BNue3Pg0jayM99SPcN78o27NfkGYYshGeSXlo/eUtxbcok9QupwHjFeD3yaxU2FTO2peQqEucd1Pl4gKshV/dyDIkze9w+Vhb/RoQZoALRHWjnCpdg36Jlhsisxgyec100pt+qsKtY2Blh6MIRQ7eqHJn9LBrNLImq5vHvxEKRJvYF/r/DipOKarQYSHxUmZarEmrZDFqz4/bFPwK1jhjjsb1H9Ii5Dlwi+X4s1iicMfaQ/ojeZ3W1TQtC0u+TDLT5CMoHVibtgy4g6kPtQOgS21SiO2Lo8MMzn5BVboxJL+L6MBjwQfJKnA1FnwhsXsMRDqAT1kJE10ij/fF9b6yEAGv3xDBZXf6hHI2OF42fj3oD5MRuyfcTDr8yQxRXjcljcCDfm3/OI8cckNzjIxd5gryhnnbIBjIm7F9/NMlfE3yFIhr05nl/HIYjPQBwbKVbXmSteqYWpnLEN+aXtNIHuC6o6o85GVxDf/pkwDYuYsiA1aYMwKdW2D0DXPJ+tlUwMZrj8Ob7M8RzptWmt0vn9ZfJWLbp/aBA/VUfpWZT+z1TyK0qhHHlUM9OAOGMu3EK+XgFSo2pVGg2C2ccSrhI3vOWXkUkndzGBcZbXiCHybGj5vuB964sw6H6XFm3epLZrAvd
*/