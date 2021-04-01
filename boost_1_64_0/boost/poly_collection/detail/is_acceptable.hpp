/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_ACCEPTABLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_ACCEPTABLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <type_traits>

namespace boost{

namespace poly_collection{

namespace detail{

/* This can be further specialized by Model when the std type trait classes
 * fail to give the right info (as it can happen with class templates whose
 * nominally existing operators do not compile for certain instantiations).
 */

template<typename T,typename Model,typename=void>
struct is_acceptable:std::integral_constant<
  bool,
  Model::template is_implementation<T>::value&&
  std::is_move_constructible<typename std::decay<T>::type>::value&&
  (std::is_move_assignable<typename std::decay<T>::type>::value||
   std::is_nothrow_move_constructible<typename std::decay<T>::type>::value)
>{};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_acceptable.hpp
888CESA2Ao4Q5Hfw77ngS85w3ry4Ogz1M+EvN/7lzUcYVwlu49bYoz7fQrGq6Vg6cjezqRwhkW7b5HLHubY91bdFvp4/HJxg2sGHv1YDcCf2XxvHxP+hK59wD/c+kwx99r37jBb8/4B+zbMWes3eCk6efGiHQfGBt+mtz9MkPnEX5goB45J3+T9XLpdeng74UM7zKpoSwZA0ZJraj0+KhAlVXN11w7t1fYUbfj3UEmbSLh963SDRwwwYbIaubjNBqjckniGNOnpDujpYktOhwrQYl/hV/AscPEmBulzml3vWUkIAZihdVlCimjqgI9PlKDydZ8p0oF0YHa7vvPlv5RHnNV8Qw4Pka44p4g4RTkSeBFIWuoh6IsmCbWoeqX8JYVg78rP4SabJyxBh/X3Y8vBTwCPu50vTXCV2/2SRnwYrYtrFGd1bLXRApTL3bnJQfqxewlWx0TSvOPSz+etaWdu3dNzBfAZer/nH/j9f6DPYltVkRqEn23S0L5/WYm9IVLZvDOlUNCmJoeSKYjaQHyTc2cXc9nfUmfaw4omb+gU+4j9rZaEg9eURHw==
*/