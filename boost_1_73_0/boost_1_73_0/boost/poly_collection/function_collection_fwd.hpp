/* Copyright 2016 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_FUNCTION_COLLECTION_FWD_HPP
#define BOOST_POLY_COLLECTION_FUNCTION_COLLECTION_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <memory>

namespace boost{

namespace poly_collection{

namespace detail{
template<typename Signature> struct function_model;
}

template<typename Signature>
using function_collection_value_type=
  typename detail::function_model<Signature>::value_type;

template<
  typename Signature,
  typename Allocator=std::allocator<function_collection_value_type<Signature>>
>
class function_collection;

template<typename Signature,typename Allocator>
bool operator==(
  const function_collection<Signature,Allocator>& x,
  const function_collection<Signature,Allocator>& y);

template<typename Signature,typename Allocator>
bool operator!=(
  const function_collection<Signature,Allocator>& x,
  const function_collection<Signature,Allocator>& y);

template<typename Signature,typename Allocator>
void swap(
  function_collection<Signature,Allocator>& x,
  function_collection<Signature,Allocator>& y);

} /* namespace poly_collection */

using poly_collection::function_collection;

} /* namespace boost */

#endif

/* function_collection_fwd.hpp
Tn/r6aozffq6xy4uBfidZXsjoN5htVu17WZ5sVlSDtx50LCZdlq/JwfKF8UVTHycJSV9mDvG3op0XXPlwHbnAFuiz36BO0Z9QmpGnN3qmft9n/syUx1eOlPGOPbU1Jcy0ix27/3FBaPc82YTj15yP2fXbYFzPuaD0zz0l0M8OOHTn2m3h6LcZ/hpwmekaFsRLY7YvM1Bu8k1qO+Yvzygr2X68PLDlPVUDdf+B61c3CiXMsoljbIVeclJMnPgiWw=
*/