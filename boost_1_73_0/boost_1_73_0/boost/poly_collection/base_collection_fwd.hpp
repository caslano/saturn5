/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_BASE_COLLECTION_FWD_HPP
#define BOOST_POLY_COLLECTION_BASE_COLLECTION_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <memory>

namespace boost{

namespace poly_collection{

template<typename Base,typename Allocator=std::allocator<Base>>
class base_collection;

template<typename Base,typename Allocator>
bool operator==(
  const base_collection<Base,Allocator>& x,
  const base_collection<Base,Allocator>& y);

template<typename Base,typename Allocator>
bool operator!=(
  const base_collection<Base,Allocator>& x,
  const base_collection<Base,Allocator>& y);

template<typename Base,typename Allocator>
void swap(
  base_collection<Base,Allocator>& x,base_collection<Base,Allocator>& y);

} /* namespace poly_collection */

using poly_collection::base_collection;

} /* namespace boost */

#endif

/* base_collection_fwd.hpp
3zFe9RnDxO/Xut54S1xqQm6/3esex1CW31mYPuOYz/TWRLrPLtF2hCRbky2JGSnx7nf7ph0Plglol2CNy0jy9q1VkdoXUuijqfG5esfAToLo/C0fOXPz7FwTJt4e7Fn3O0Hx6jUX/VbtwXJux0mISwoyzuSguj1V2Utn8dqnp5J15bgeh3va/adKDu0SiBd43lvn2E7rzxZrtw3z/W74xkj/9nrzWO0Dm+Zz4U0BbTKc2nfFTdm+C+wjPj0j1m4=
*/