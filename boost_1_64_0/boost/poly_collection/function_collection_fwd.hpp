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
QBF1f+Fa8CIJ575Dv50c2s25j1N2kIQlwWeIoXYn3wMg8TDnP2KgD+OcDdwDZbTezP1vIKyo1W+5exCzsW8t553PeV/lGmhfTJnkmY7hzWmMdxnjYyTHXBEJ5Ma3TZSJ/XzOsWnCZ+L5THYvY3+eVbW/xhyoxFwBCZ7PZHgmU8PzrSj7DS9OI+7Ml6p4puThWCTqmavwnK4ZAxgZx/GDaIOd67l5btp7gLDAiFSBuSbPsko8yxqo5TmSlbkL2/ilzG8uJS5zeE7E+zy65nCvLNf/Pc8GMYzkc8znMsxpEEgyr3qAfT9nXsO2ZZQ5ESwPsO8Zrsdr1285h+OMjzGvQfevmdP8hjkvW98vmatxnJlrjj3L9fmsASH2Z3YyL+T4YeTR+jjXSBBn9PO6m20Pxw2HeS6xg/M4xs5nRVT/jHPu437wYxg9aIYZ7q3M7eBNE45Rws39nRh9nvfct4brd3G98E7Si/AE0BIl3g+RT8TN9zTX2U6YY5zDtpVty6PkAeFohRujyPJZCOY4YfoV+5B6gjRC4z2UhzsJwx0cs5X7buT6IeLNNoK2vYSb+yTHiBOCiD/IHBcB0ttGOJJs/bvZIpYmbUjLjt2k+/N8toWwcmyRrQ1F4mcIkm7w3821NnOvn3I9tik+C6CF13V8FkQnTLwfZjvA1oPau9i3iTLIto5wd93DtW4nvLy2oTvAORi6hy26+CwX5nziaUySJ4TZSXrbfw7C2h8h/uR7FMNIRQkHhlE9nn6km2sXeZuivHNsaBdxg5P0sxBe6/3EafzcJPdGnrAEx8sf8a0nTWuibP/O3rkHxlHUcXzTJlKwYPqkImKEoqgVk/Rh0UovrzZp8ziT9IWFyzW5NrF5XJMLbaVg1Kr1HRUV8RWxKCpqVFTUolFBi1YNiloVNWpR1KIBUUHx8dnb7+zO7e2F+rdWl8vt7zszv9f85jezszfYzOGawtcmuMq+wvx7Ahz3DnJt5e9jfE5zjXwNPX2V71yHuQ5wTYM/yhWH1sj3c/nsxqffzb00Vy1XB2WPcf8mLgcZS+Ehgx1OHgfPZ+mP+M7fS7lux6aP8n0110n+3o5dlv6S+qbwJz6vxXaH4b98EhwyL3N9HFmvQ5+3c53kOob9aj/CxedNfM7FJsdvwgZ8nuBKcz/G51w+j0NvvBFdjKPLw+gAW1wE9jo+H6I/j5xANq5zucb4fpSr8QfUxbWE68Td8MOV5rqZflXO1c51kMtB3zeBKUeOST4f5VpIvdNfpCxXL1c917VcS45QN5+98FJ7GzxgtzjXmlsoS13b+TwOf130kVux+xE+T3BdBP4Q32/G5ksO88nlcO/d2P4IZUr5jHGN4esZrnO56j9P3XehO665bmyCvoLP+/hcM4Usv0KnfL6b8jej//vuQQ6uOdj1vp9hX67M99EDVz1yF3+fi8+L+Dz322CPwcvtyIm9u/g8xFVKP7+HWDDufofv7Xw/xLWae11ca1ze0fvDk3y/h/L3Uh65S+FhinpvIea8nuserhXI28HVjn634rMHuBZyTd9GfXwuOwaWOo9Rz0Gu1fA7h+vgEXTJdZirCz7XcL2ea5JyK9DfHK5baWuUqwN+9lH/fR8Eh80O3ISd0OvtH+CirsNch9xrHN64Orgyn6RNrrlc7VwruE5yjXGdgD6Fr96Kbhu5HsaPj6PPND5dzN9HptAf97fzORcfu46/L4Je715gxvl8N58XgZ3gM83nHDD3gH+U64RbL/fix9Ed/XArPtd7L/cZo9KMcQsvJM+oIB9hbB4vw0d4xnKctaOHuVYvIufhGcwcrnHux87leQt/N3Id5/s4nw9xLeF+L9cIdR7icym6WMEzodU=
*/