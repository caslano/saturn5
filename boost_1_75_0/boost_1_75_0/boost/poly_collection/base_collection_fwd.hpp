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
xy21zmbC8XEXOFma+8YvaGJK4huUblbHVP5n7jlbJmULyp08jHaryQXGDEM9csgPKNL54BvnpXLJDWGA6fj8MCoOyA+QV8ZvD8IOhj5SdxRNZnz9BZhRPyjOcf6+ngeaCpi09MlYr+nDOad3KJHceYPhpxM4Qd59gwNzTJfslEHXiIAq+rx6WBpi1F9OnlDfAYxKJCt+gTdaYC5lVSrL1sxEUvahtYWlVIBr3ZhY6+bBx14G73BoHRcriBRHohV6uHym0NqYB8uVkwu9TwLXS/+spv5hzzmc4kcio8zJJeRum4ZolLqS5Op5jN9k+hhk01vblHn1u8rIAOPpaMG7Sze5H7bqFuhV7n8cbjpf+GfWoagSBREOBhbIyWhMcwJvfJ44jSqbzcPqcOtDnh8F7S/JRpWtMxk+uhv+HMWLDMpY/Xaer/guFtPfutWkI17WBxuE84xczMKOvcAFFA2Kv1czGI0at4ZLokdTN/OZhUCj6JYT7b/fJ3YVF2TV+tsWX5svm/rkPE9H71Qc0xvhrAg8ZrKcyCzdb3kJIv0tlfKNgiQvM/bPrrSv4eX+GhoSxBucd27M1+aTNnqfcVads5RprDTaGCWslgEFJGJ5fmYECc809RhB433Px/B+Odpso8XZp81qSXDQ8EYekLlY/OktBIMG/8BhRwOVftBGV563Jhg88N0WVXSYvgUnG4i/VBo/36P5dijpplak
*/