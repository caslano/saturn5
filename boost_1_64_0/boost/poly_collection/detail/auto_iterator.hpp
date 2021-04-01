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
TJV+Vupp98rZHkZxX2u8rMf/7SI5kKVkg2c24sZTAgE1JZ4LO97pFWyBPw3R26PEO05mIvmddg+qDiRd1K1gYQjfwE/TF+6fDebn02HL3MBekwBWJdUNGsN9uekYlVTt69896fKlzlM4BkRTCIyJbz7/oEBcxB49PGFvgeQ+x1/FFbz9UWxgmE3PRb1FncF4aUV8A8VsM91wlaby11PEiTSvCbNCXCSYx//jMqKF6L/HFjBCYxjKy3r4QAFUhSMCfUm3rub7Gmmp7tMve/hmJHYJdUwVDpe8hWvJBSg4K7jKvkIYOlepFy9rcbpLSRcPy4vxF3enj/Tj0Lc44c4pGyxoECZwHctdMypvNyahmEQOac0fgcm375XNZTweNW5gFOC38eeBbOyfjofyNwowNlSKDXEPxGgwa8OQhH3SXkuH+WtIwWEXskLepdGbOzjRhe7l49qBRqjSNlTgQWn4xAJ3AX3qWo/ef9/Sg/OltzE3c42fGn6iGnBNMStH9R9xWEoMVWg3H5cb5EvzU/8ePfcMKUvL7ZkvdYXVcbsdYI3Hc8cMky+CMAvS8A==
*/