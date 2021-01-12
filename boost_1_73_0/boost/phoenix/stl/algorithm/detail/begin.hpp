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
hfkVIM83A/dI9VmfuseG3ye4A7qMrBaAz73JhXs/HfNeDu0XIevnyTFYiMz4UDcb52zk/O9azhk1+XJDF/Nvcr3bk08WGkuuLvfsNbeRP8jdW1H6mHlf5Wpyt0OuXS62is+rkd9GgH9qLGOSkzaKHNeKBDc9qpgy73vuoVpzptmdO+gC3JGVYCd7E/4WQd5bctdCjvzgOvb98mXC3nrcm46IxObR9g7zHKrO2qoY5DLDP2Qo
*/