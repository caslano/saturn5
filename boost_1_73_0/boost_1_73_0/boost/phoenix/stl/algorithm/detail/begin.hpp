// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2015 John Fletcher.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_DETAIL_BEGIN_HPP
#define BOOST_PHOENIX_ALGORITHM_DETAIL_BEGIN_HPP

//#include <boost/range/result_iterator.hpp> is deprecated
#include <boost/range/iterator.hpp>
#include <boost/range/begin.hpp>

namespace boost { namespace phoenix {
namespace detail
{
  template<class R>
  typename range_iterator<R>::type
  begin_(R& r)
  {
      return boost::begin(r);
  }
}
}}

#endif

/* begin.hpp
9vXHDZGDiONaBdkUcdMlSr5eiUpjFOxPNKYoNkb/lL/LDT8Z1xDk08l87IMbgrlknMajA9PoeS7h3rArxVlb/KiU30MsYoGRZyyT8b2Cnge1xG8d1Zf4GLtpyzmP8PYF7zgujyF4mny8UeF971IBO6hU8D6D2vpmgz4vXLI75XLhX4mp0x3gUKo3s0Gf2xBf5vPo9xGOgCaq0+zrZVTpGJLhgPECNotgLdaxKpsTIfHis9ScpQtnLeZeZSlvEmM=
*/