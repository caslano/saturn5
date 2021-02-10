/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ADL_SWAP_HPP
#define BOOST_MULTI_INDEX_DETAIL_ADL_SWAP_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>

namespace boost{

namespace multi_index{

namespace detail{

template<typename T>
void adl_swap(T& x,T& y)
{

#if !defined(BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL)
  using std::swap;
  swap(x,y);
#else
  std::swap(x,y);
#endif

}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* adl_swap.hpp
5/OW8MKlgfAb/axwQZfRbMLYrAYy63VK8s6DgzHzy5U3QJ5JP0YRh07Z4IwZYsnuwxyeQWNo8ywXWZprnhxZqpScxg9IKthW9h8n4sAHc8zDdrvdqCY2lPQQhaTInK2QlqGoSvCx9l9QSwMECgAAAAgALWdKUio9/5+eBgAAahcAACMACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjExNTYuY1VUBQABtkgkYOVXbVPbRhD+7l+xcYaMBAIbkmYaDGmNMcQNsRhjJsOEjEa2zta1suTRnQA38N+7eydZsrFjnJf2Q5UJevHts8++3O5eZfPHXSXYhJWXo/47eOFdSZzH0Z+sLxevdpx70P9Q6hrvq5RUIBe5d0xYLXIPhhJxUi0H9Ow4qxRdEzf6UyHJa4ce8QuKkWQjGk9iPvQlGA0Tdt+8+RW2Ya+6V7Xg2A05C+BCsrDH4qEFB5768rvv3t3tCPbWAibBDXZSqK7PBYhoIG/dmAE+B7zPQsE8cAV4TPRj3sMXHoL0GQx4wKBhn1+12qcW3Pq87xPIJEpA+FESeOC7Nwxi1mf8RmOM3VhCNEBxBPe4kAiYSB6FO6ibgWTxSBAGqXcDEYF74/LA7aEiV4Iv5VjsVyr9JA6QfcWL+qLSz8zf
*/