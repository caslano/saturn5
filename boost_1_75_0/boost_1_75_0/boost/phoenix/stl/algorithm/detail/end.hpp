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
aRBwbmJTrdxO6j2AXOJH5P/UuMhMti41j507viXA5umUFm369SZYP4qwkk1pwfiUHk8HbypfUh8bRm/CPXujltb/+aayib7O5ulFtKCTv9zwy3jthVsj2FAyDdCFYegu5q7sGyanxhKyUGSBDaQmjskNYfyR3vqEhWUK9O15HsPwES0XK7kv+BP8i5Fxd/Dj25L5TkHQsdJ1yWlg6TIkWOGGxvm4L+kfbwwiWOF+Vg8ZdHoJc/4ELiXIga6lxo7ALyk3E+f2KqZbDlb8Xb789Po+4xiSDahvCLE9O6Q4cVV/J/SZaKSUIAWKWiibuHqlEb1y6MEjSkRnuWXZpwg7F3isCEsb3f9l16TSO8xzOb3EdqJHjoTR0UTuAMtdrzGi85Achgy7DUhgENFHpunGDbRkXb5wKh8TcaKkYRJNJ+qa5IWXgdZ2lPsbiZcbxHSFGeHX2Ce+HkLFpyG5u8Wn7Sfpz4gKU1S9OABVI1fm+hwA29gPfM3u1jS3+bfmCgS3+UeraU5VtGJQs1IdiYZvHs47mwjlt8SROn51JLi88CVqZaWwG4tlyTd7Yrz92Qgaw+4Y0DLBxauU5j+oXBrpNvXzZZJ7I4HutnKaOw4X2jtji1cvrJUygVBhxBzZfabe9jSblVJypcRqAk3K8f7A+7Lgi8SotIemTCbgaUBi4ybsOo8+NqUyyGRwc+wyjB6bvzaScAVahSZMsH5t
*/