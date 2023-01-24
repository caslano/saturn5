// Copyright (C) 2003, 2008 Fernando Luis Cacciola Carballal.
// Copyright (C) 2016 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  fernando_cacciola@hotmail.com
//  akrzemi1@gmail.com

#ifndef BOOST_OPTIONAL_OPTIONAL_DETAIL_OPTIONAL_FACTORY_SUPPORT_AJK_12FEB2016_HPP
#define BOOST_OPTIONAL_OPTIONAL_DETAIL_OPTIONAL_FACTORY_SUPPORT_AJK_12FEB2016_HPP

// Daniel Wallin discovered that bind/apply.hpp badly interacts with the apply<>
// member template of a factory as used in the optional<> implementation.
// He proposed this simple fix which is to move the call to apply<> outside
// namespace boost.
namespace boost_optional_detail
{
  template <class T, class Factory>
  inline void construct(Factory const& factory, void* address)
  {
    factory.BOOST_NESTED_TEMPLATE apply<T>(address);
  }
}

namespace boost
{
  class in_place_factory_base ;
  class typed_in_place_factory_base ;
}

#endif // header guard

/* optional_factory_support.hpp
T7z+yQmYx872wuHS4u56ObO+KN/VqH4hHMSBE+BhvK4MnbkCtg6IEfILeCcLjO5KnMgvn5gPFAW2mgbdlzxcdxvU6u9O9IBWLlxVnOUiScX9uHrsfl79UZ7QHNdrkOZe4j6rLpcdt/8B9ZeiLXNOva+cHzQfopQm2ZB8u+Jt2GT8WaT8L5j2213D0/Po3cRK43WmZKDzRPgPaYpjkmFQm4FGf34LtcRRy2bZdii8hR3AavYLpcR74Db9ji3JAg5bgRcxLSERj1vgixKcMKG4Nrg17syKXyp5roep/MlHT6Gk3sqFYaM8VHAZsHw+VNtueCywzbupB/6q/OGlXrM6FrvucGZFxXyn4yc6aBZXxsTw52mFCX8vyH8xqqywu9V9cUMVkNhjQ6Pnl6Eel1uH+f4+yTx1PSTb3fgbzWONqS2rQdS0vd4J6FyRtv5uPxHuBC0vljycnB3hg3aU2Zm48fvZKZSW46vrk5d6ox3Jg5D81Dj7nIUZrm0C1ryjCbXnNrhk3uUr93qXeO91n7kA3LGzO64YqlIFu1ydbAbsuFfz1apN8hut01kpIG10Nsju/kDGENXKJWc6C6WHg3hJwmKPb9lFJQQz/dQ3CGixsKjdsTF2mwgPaICNdKp0l+a7O18oLC00tt1rJpsmPzVk540vrM0D0EyxbznujtXtzwkVrWRKFteGqlOTfUfqkpXtPLsGoKVvw3bBrpVS
*/