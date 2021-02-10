/* Copyright 2016 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_AUTO_ITERATOR_HPP
#define BOOST_POLY_COLLECTION_DETAIL_AUTO_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/iterator/iterator_adaptor.hpp>

namespace boost{

namespace poly_collection{

namespace detail{

/* auto_iterator<Iterator> (for want of a better name) behaves like Iterator
 * save for the fact that it derefs to Iterator& rather than
 * Iterator::reference. This is useful to "lift" std algorithms so that
 * user-defined predicates are passed iterators that can then be dereferenced
 * internally.
 */

template<typename Iterator>
class auto_iterator:
  public boost::iterator_adaptor<auto_iterator<Iterator>,Iterator,Iterator>
{
public:
  auto_iterator()=default;
  auto_iterator(const Iterator& it):auto_iterator::iterator_adaptor_{it}{}
  auto_iterator(const auto_iterator&)=default;
  auto_iterator& operator=(const auto_iterator&)=default;

private:
  friend class boost::iterator_core_access;

  Iterator& dereference()const noexcept
  {
    return const_cast<auto_iterator*>(this)->base_reference();
  }
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* auto_iterator.hpp
MUzjCX15Eh6rJHj1qg3fAoEneob8dsj4T/UX8w0X+i4kzQ0LoidpqGrj6bsavsls0Qyc7mt8E0t9xNMoFP2Ger30c+Nwd6btz/GDSS1I97vjfHze+BdQSwMECgAAAAgALWdKUlATGWERBAAA+gkAACEACQBjdXJsLW1hc3Rlci90ZXN0cy91bml0L3VuaXQxNjIxLmNVVAUAAbZIJGCtVm1v2zYQ/q5fcXPRwEo0K0tXYE2yoV5e1qCpE8TKsmAuBJo6RWwlUSCpvKDxf9+RkmLHcRZsqIJY5PGe5473Zofr3+/xYB1efGL3H9NDb4c4VfILcrNaO47vofkj1ITeLxkJYQ65j314GXIPfQeJWyu7dh3HLxmaWN/sR2iRk9guSUIwi9yT1Z0SV5mB/p4PP7179wv8CFubW5sB7LNSYA5jg+UU1VUAu4mTvM/Y7e1A428BoAGWD1qqKBMatEzNDVMItM4Fx1JjAkxDgporMaWNKMFkCKnIEfZOTi+PRn8EcJMJnlmSO1mDzmSdJ5CxawSFHMV1w1ExZUCmBCfyRGhDhLURshyQbQSDqtCWw5pnuZbArpnI2ZQMMQOZMZXeDkNeq5y8DxPJdci76w8yUzzc5JKcKNgdyMqAkVBrDMBqBlDIRKT2TQEhYVVP
*/