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
GakXZdpJ81xudan5eSccOYZWtnzsWJgoNOOufjBesoM30buEVMjLugZJzYu9BChSXsoo0Qs1wDVZ8uNV+V3wuNbaGx2pTzOrwlq2gpd2fqmpgs27iu+AWjn7fq5rupzjtR5Ud3dOHNiZSPKLMKMCZRza3S2sgRt66DWjgVQqWfQDdeyy7X8Tf9mmvidlFDnClnm89pVoUh07n778OtxGUvw1dWQe2IANROrWzxHUc1H51XayPxZ96JizJTWlpCJKhw0M/XfY1KJk6Vx2QvezGkpi7AJB8/FiI9WOY2pODGtEOm7voHgml4nOZcHryYGI3kPKymygDJinW56ffL2ZcY3FyA+zqSu8ac0WeEAnhY2nZmyjDUUEYaPZmnC3PRrC2euJWtJ/FQlZGdMuEcg4ozIg91iAMgGABQfE9WJNNLIbOCVMMLtQ30W73cYiYgJueaP4hf6jTQ8M2l44b5bAkdvqHbXsvEosdLZ6+7w3fWhf6OTFpb8SpnIJ4LiGZAtOQqxuO+4P+oR3knnERnFelsFP7qk5mVYFFufNUwXXj7R1ETkcLDsPZYjgxA==
*/