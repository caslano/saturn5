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
/qOGD1lcsI8k45vfYO0VHbOF8+jiPTfmziP2nnXJ7wm21ybBOMqfN1zpsXA46mOmRtDHTI7I+x6HrYN190Chzb38Lbh2bCtP4Q625zfsxx+YyV0cwx/5F/7EOTThnKexL5/nflzFotzCYtzGESLv+xM2CMpRWmQE5XB9mXKoD9uwHM/gIezL8hzBwziJFTiHKXyEFfkSK/FjVuZnPJLbqA7531vwcZEiSom0YP7n7evaNvbg
*/