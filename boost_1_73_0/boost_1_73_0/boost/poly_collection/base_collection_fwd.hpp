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
IRIxTanWhfppMIiqMkP1g1hGahC9tN9P9eZrJ/coYsOeSBaatKRKcZsM0qaNjEViZhiCYFGFmVCpva8GqfJ4IEtSPMuMFniCq7ZsTuudPbaBUYGKhTaTkrkyqR5TufkGCB+NSlKVORLBB4BiCZttqvKYlw246fwlxc7TxuDvHs2+3phkjmKoM13TfN2hkCmhbPo0926Wdx59mq5W04V3T8vfabq4N2If5otLHL1AspJ4XZRcIXlJYlNkgse7nD9uDKx3Io+yKubUMYcXpTz6s592rFfxQKXMHY6aHaWZFhHN7lYfIwlAlQsdKK6roruVIu5Zf1mEZ0vD1gZ0FSw/XFh/fyUa0I6k5Z5jEHeLueddrb1g7U1XnikiwUEkjUxwOV9Pf4PabHV/6y2D6Z13g0QRTldTlDI8FrA9f3A+f6GfqeN0Lg7tuu1uiidIHuOFOE6kzBpolSvxkOPMGrSsdFHpz+ubKdpG6mtT1cerxbV38+Xf6CPNlS4g3NIuLCBme9uE7rYbNnXbil7Rey+122aR8by7u+/1Gq0tL/FqBBu+keVTt0lmW68/Rh2/HoV+PR75dej69fmpXyeJX5+eYY78mjt+PYl3mBO/PuPt/pABk3QOyQ3PAcPFQGOQ4YAySLugOYidTfw6gpQD
*/