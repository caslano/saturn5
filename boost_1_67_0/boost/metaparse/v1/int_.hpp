#ifndef BOOST_METAPARSE_V1_INT__HPP
#define BOOST_METAPARSE_V1_INT__HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/digit_val.hpp>
#include <boost/metaparse/v1/foldl1.hpp>
#include <boost/metaparse/v1/impl/next_digit.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef foldl1<digit_val, boost::mpl::int_<0>, impl::next_digit> int_;
    }
  }
}

#endif


/* int_.hpp
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
*/