/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_ANY_COLLECTION_FWD_HPP
#define BOOST_POLY_COLLECTION_ANY_COLLECTION_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <memory>

namespace boost{

namespace poly_collection{

namespace detail{
template<typename Concept> struct any_model;
}

template<typename Concept>
using any_collection_value_type=
  typename detail::any_model<Concept>::value_type;

template<
  typename Concept,
  typename Allocator=std::allocator<any_collection_value_type<Concept>>
>
class any_collection;

template<typename Concept,typename Allocator>
bool operator==(
  const any_collection<Concept,Allocator>& x,
  const any_collection<Concept,Allocator>& y);

template<typename Concept,typename Allocator>
bool operator!=(
  const any_collection<Concept,Allocator>& x,
  const any_collection<Concept,Allocator>& y);

template<typename Concept,typename Allocator>
void swap(
  any_collection<Concept,Allocator>& x,any_collection<Concept,Allocator>& y);

} /* namespace poly_collection */

using poly_collection::any_collection;

} /* namespace boost */

#endif

/* any_collection_fwd.hpp
PXtn0ycfwE2AbsjrqEdePSOumVJEwcX9jrv1Xhja7CpPfrhQi1T4VBtGq2An8Yms0StoX0Lpaau11Y00mwTeJkR1Z0V7u4oUWFtYjoknPJbcDQuBiUTMI9wkpd5+iPZagqaIKAYxxa+5WnWuYn/wGhlrqB829QW9+4PSTyJbAPpToJ7H54yBiIl/39EiO+iSYa7veYg9Mo2hNcBl3cOr4Bq69dB8o6fU7GrBfsr+HFXOavCDvlh28tOZlBkjt1/i7AcUZPw0rMBzMH0kiZwzO8Hn9fWA93wKShGuFCkg0K+MJu+Cprps2mlSOaxWGeLDRYieKvEbGPi+K3LIUbF5oSK2NtP04iTd4ew93fdcbEx4vk/kIaH8DHRn//o5mCkPV0vWapWJFIPYc5Wt9olOVYCRcg3o4mq3CLFX3W2oLI5mYXXnxw2a32wdbTYXmBLzfy+A6IJtIXWlrOZRnW+YUZV+Z/G0MuRWB9YeBFC1t8T5mFFMploFvedGGSJ7UaQKf37CijxiHwpwltouXNxKaN1OfcTKQ+6JyFmTZAkjh68XIECSPgUkyWC9/A==
*/