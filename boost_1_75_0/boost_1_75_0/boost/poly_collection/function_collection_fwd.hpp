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
7R2KQYl55hvoiRZT2mi0A0V5CBwMOs/m23A0EzZ7nt4+cNjkvRhduGU1+eet23fnQ7EU1dul3TKTKnI0tkMNJzI6iSBUEaK6psntRemi7ei2h/Vt7TExKoGKoDqHlGPh+cNEWybf8WuHXzZNrIMnEkd9KoNKz+8qQjajIBSXL60A1LUkVj2n5y6YGsEsQ2qhR8E1Ujyf31rNNmTFIVrH4mh7xfDIDAajfctvy34hGP70SmBb+qi9y7rDcDfXVIUVsH7nhCI7bGicO2vb7MwrUbniEu+AYPyczaNx2WPbpSAz3kRc1+VUC3aLzwEOKTwviEK9jk1yg996q3eTtLdBgyWTCF/bFXsx0s+/k5qgqo+XdjaX4XppEdXE4Fy38i3dgKiGdiu0lubT8a/VnV4oVJbgFhANkY+SqZV45j1x19hYf4NGa4PLGB61YA//RsGfMLxAPTo/LklzLX+anJy8XmnuGebT6uPjE00rVu8ZYG6u2N8xMNBhUW77uWSwcVtRwXmZS5nNrHnvzEVMLVElQGMCm5OG8B7NEJ5r+ur7ZjqUWiRR9ISQ0YSS6VVMGqxbZpp/a+B449c1TCWzBlMjutu2gi9FOMuNU7Cff/DEda2R9/MQY/Dt1zDbEtlED+w0URGFxvrTxUb2SdIL6MMvzBWYiIe94/HG3NT8HOBgsWNuo0Ns59zh+l5v+VWbu3WkSJD9C2VZQ6OohMHx
*/