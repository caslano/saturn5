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
yHEgv7DganR4Ife45Kh8hQ5U3sc5MPVPHuJ+9lN4sYm7UPQmYwR9kK/yCTr/aRHy/FQeJ3e0KeDZfF/0ODd0msQd7AjuS3rZ+UJ7kM1nUZzFcL8TmYOxmpJ3tMGUb7n/LNcc+efZaQ66xtwL5kCOzqOzgRZnAeQhbmH93OEVIY98I+8wNLnEmXRn5KgvdwWs4+AWeM3Z+rVOnME04B4WGhXqQf5IVeQbWrWD3h9NYKxYeI8+
*/