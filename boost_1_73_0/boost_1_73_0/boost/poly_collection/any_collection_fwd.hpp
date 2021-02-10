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
KMHcxXUon9zK/GcxtPAQ7vLJnVqiJn+TNqdX/HKrwyDqTHPTrCodMO7wwaLYGzJwC5GzzY+IRCHJF3kfu6aZDjjtI2pD7Me+jnqmvU37Qr2LBrwC64Dvo9XhxgkJPBC6Wlsd4/BOPU2SwIOBT5uhKJFwdjbor5mdtbTfcYGFdh75LHfTJIi6Uxfyk0dwNhHlPItLlXx05j16jq1RG8uotSriVM9lMWhl00NMi17nrJJysbG77E6oOrzKJwcrrP/vfH303K3sdGn4uJ/7436O4744y3zizxfp30zVjrQ5Ejwlq7IZk1/v/Ss+eLP38jge7x+6drN5HbR4pJz2Bw/oh+Xz//78tEEPJxZH5GOXr2VrC8M2v2kWZ24HTrlUrSK68Qj4olbmFz6t/RE9cJFd+Ax0Qk4Yi/diaPC5EVJhLT1FPcG7HObGZdOajQ9Ff9WKOH51gDoRR7gbHxy6O9XWEuqUKxQ8ubuMjH+4vg2h24D9X9zhQtS8hvlhhPorbvRRe9aMGzJbCa1iloZ9zrSvACHqhgNP59+CSptv/3dU2Osv47Jmvg4VQBHd6se34ONrt+UXI5EPOsjfpuhPRGzNNC8EzpLm3XkVuK9F7WYufXcAXT384dlSZ/h2nJzcW3DiKe/ujMKL/s2Uc2J4
*/