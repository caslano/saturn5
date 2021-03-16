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
8/WTiN1Ftl7tt9R4mT2VjY2XZzKp3CeWMzU/Ju6fUWW1oozfU9PXXYYpIpUIc5CTdzVPwOz7alSdC/F/caW6flPkJKk6Rg6HpdU5T9SR7Yjcl5POu1mClWhjLNWUlnfToadfDnGnHJkfa2fpO7Breugwd25hWMFKqiq8d8aeomjypF1RT/V5iKrX3vysJXzPtE8ObmdXv+x2MB4pyLXgfJH3pMr7OuWcg77p5XYelJ5TJ2FcR/RcVVVH15N5Trk=
*/