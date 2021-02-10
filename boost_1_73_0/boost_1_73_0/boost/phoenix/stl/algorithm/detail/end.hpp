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
OFh5x0zFMLWnrCoUtsQxa8fvrR1VTm8VslQJ9SX7QQnDWvSLTMyx6FzkpPY1EgS/c/FaI91lnQ7Gb500DfG6hS64Oj6EbFPzNVjc/qTm3STjHzQwuxQhMNW4qid9FaGLnG4FpbqlQya0cF7ZOlMIMgQCh8yhclODBKdRQg+eispRQ7C54jkVgRrEkoqn6vQwQ32smCWqPg1R7al4LlBrCBTNc6OzlIkfiEvFReDd3Kt7qsRU7cEf4c0Yv1uEgRfIi0xc4cukR/NgQ5TMLBb2rOymepra5pGZcjtrqqzk6nldcFNsBaSo7aJDS7Nk+8VPP4nsOm6wO4ZfqWpNeZAuhcug5d3l0C5/4w2ILGV32THsBwYxlymOuH31Zm4EXhecCWqE7PMwN+v4TazB3gG8/oAp6EdvedKd1axa/ABWuaGbNKdzHGx1HTwMelnp+C8u984vC65fmETL97cpUxO7kxKCp4LxBKyGhNK4PN87vTg8OGfg3C7Pz07YAP6w7e2dF2z4eu+cnRyfHjRY16ZclzVwdASRByRJ8jSne28O0J+iDjh69ODN3vEJDpPsm/H9g4shDqPMm9HTs8uDCwKCUmzG0e+evb2kR4rT5un5u1NYdiknOF27vGVAvH17eLJ3JGdgMqVGHsyc8ozS
*/