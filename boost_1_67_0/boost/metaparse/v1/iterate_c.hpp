#ifndef BOOST_METAPARSE_V1_ITERATE_C_HPP
#define BOOST_METAPARSE_V1_ITERATE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/iterate_impl.hpp>

#include <boost/mpl/deque.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, int N>
      struct iterate_c : impl::iterate_impl<N, P, boost::mpl::deque<> > {};
    }
  }
}

#endif


/* iterate_c.hpp
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
*/