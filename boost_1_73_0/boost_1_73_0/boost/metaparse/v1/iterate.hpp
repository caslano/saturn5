#ifndef BOOST_METAPARSE_V1_ITERATE_HPP
#define BOOST_METAPARSE_V1_ITERATE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/iterate_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class N>
      struct iterate : iterate_c<P, N::type::value> {};
    }
  }
}

#endif


/* iterate.hpp
dS+nPftGMq1jAdOziXCnCEXerEXiMTFna1LNeAYmnTMfIze1qsdxDNdlWWJIGUiIei6is5hA97VYVClyScxsi2E+1L5BT8PGPZx9vlpuhMlEwp5CzJQzF5E2I9IeysBnmnOZrppb2yMVGA0nDDEtu39mqCPZKVsEvLiPJJPtMUNvNRKO1+Q7bao9RcTMUY5mo2fE1A6y0d+o3stHshkz2aGjOThJXJQbjqeNcLRLHFpiTBztohOhiLk0ZHVE/e4=
*/