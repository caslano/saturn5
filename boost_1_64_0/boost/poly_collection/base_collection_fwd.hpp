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
mHtYQo1vzybYTBE/wFVd5XqzGMe0hGrrMlCoyttM3HVKa3/4hvdUt/AZbm1z8Ypzq6FauxGRGHLhiP5Ml9bVvaliiCgsYEfM6hhwpZcGH5+YsUNnwsJ9dG4oLiTfajnO6iY+ACCyIDOe6lN6hOROYm/ipgQuaEfYyjaR6AhTM9Pjed6vc5rcwDg4DjTNmhdNrMwjMTCt5H3WvtCp4RZP8VUfeu4K2OHiUJzFJXeq7sfolIHIWAxQk0JugGG8Osx1EG+43Qe/WBvF/n3HvsX2cC3iF5cu2MlRJSQBlVTpnpNtqDBvq8nOWtF+Bcq0Y5Nk1v3NNOcavWQICqgPZfv9sXxjSa/jJ3LrfVkJmwaeCSNZ/lhHV82a9COYFNuNk6UC8L6qjjZJOnn+Gxfdel72AfoFWackepUpG+VSUZCptQORgQlqheDoB6ifoLXh4E6COrNVkaHFeRcWKp/pVbeam4hcyDKxy5KBCMiCA2zqHW5yRUnHsgqSqZmt/W04ZPBs0zgo8+4+/NhM7UL+5XJtJdjpBWihiNscsXrlFFPaZy20pdPMrnKUzlKLZg==
*/