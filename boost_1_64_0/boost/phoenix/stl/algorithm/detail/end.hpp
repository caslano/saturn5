// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2015 John Fletcher.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_DETAIL_END_HPP
#define BOOST_PHOENIX_ALGORITHM_DETAIL_END_HPP

//#include <boost/range/result_iterator.hpp> is deprecated
#include <boost/range/iterator.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace phoenix {
namespace detail
{
  template<class R>
  typename range_iterator<R>::type
  end_(R& r)
  {
      return boost::end(r);
  }
}
}}

#endif

/* end.hpp
Ri/gl9VK/Vis9aamAgrOm1XABRwOeCMnCTes7cmzwvnc7/uN1y+3xvdfM8M7w9QnadmBe0lMCexrFq3er2QWMzvK8QIRH4y1xVKAKMLXkNEFQUDXlFAKHhC/iag3+GEmeABGbS5So/HDQGr8Zr/GRC+16rI81M2hm9rztBaRXVe79MCo1h5YqBHszRvxwyCN2GFdxx3AFKSHzT7ocwq8DXW0hD/IL4MERSQUBhtWUliJvbQc/SX4K9DDkVLn6zyUs4sf0mpq11i3gfTuwgCQBlyFmnM1h2p6MWfGJHo2oLzHgp3rMyDRtRxBPhsVQcudV6igcvA+ygJtCDWlRxpCx8W9h+krKmmeK0HLG6ZIOZhbhkZlXiiVKlSJyBvo3/3RifKFRIN3iQTD7ZHajuAVh943UzgUao3JpnmyPqS9JQqCRZQwM0QeZVkhq0orWOBT1uBoVRjKFjQTCVvNIdHfRwbX9HPCkt1RUFbDN0qjajIlZqNAN5Xb8yrJ9WD5Izzqe0baOBENL9//jtm0zIUDwnGnFe3cNzQW5n06mNsvEoKRU1uMuPwGBU7S1A==
*/