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
p9KgJ4E1nvCSVOZWZGAzDrBc6icB5sYywqnv49aBTZ+ETVXbOfXw2RJ+SjPIMlieA7DTVrBGLOfyv0U+TOwt4LhGOg89PTd6qzAI8HphWjm/+/pkWRdpmb50KKgpkB9IZuXb4Q2SzVTTe6d8UbJBsH18ir0u5TWPkXXqKNionW9McweiscqPepBi0D45vjO+w5ycc5bcpxnPA+GY0pAGRJNUf/Za3yqlAJZO/LgKBwomezBs2f6VsrMMiqs74zgEhwABAgTdAsEtFA0a3CGBIMGdENxtsWAJENxtcQmuwd1tcZfg7gsLC7tb3rYz7XTaafvpnvN/5Dz3zv3ym3vuc3x9MEf+vA+oY2a1VF/WbFvPnigY99wrnz9XI/wtq3mLfhEvYJKDcDPM42JUvrJRbpppRB9MhK++StG4H1z1aplBp5aUh3CbSNcNXC0CGwM5TdmXvmhPnNjRXYm+Y80e/b6fVKP8IUIc945F2gwfXxVo2ektdLOOtSKs3Olc/k2bw+9I/rGjQCEBKvAovu8f7ynMrLC+KSp3xXWw8vo8uDK2jSS9e8fwPWkCVJKL6TyoR2UdwzSv32/yCYTRaCzjEQwq68xiAztZ0yQqTyQN3llTPjRPUN5dTu0rqqNKtCNZ4vMQeyBNu19YevQXCIgd30AMu45RR6bss3/y8IWfBmXH2kdKhJAEqhPGt3luQZVa23K/DVrb4sgvtwvW
*/