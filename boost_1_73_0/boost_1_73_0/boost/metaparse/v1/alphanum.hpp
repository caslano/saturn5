#ifndef BOOST_METAPARSE_V1_ALPHANUM_HPP
#define BOOST_METAPARSE_V1_ALPHANUM_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/digit.hpp>
#include <boost/metaparse/v1/letter.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef one_of<letter, digit> alphanum;
    }
  }
}

#endif


/* alphanum.hpp
MtJv9Y+MPL76N0beW62vI4+tNtWRR1aPqSOPq2LqDh5Q3VRHVl8drCNLr767jiy5ek4dWW/1/XVksdXr6shKq1+uIxutfo2PYvU7dbQIqf6wjrKl6o/qaAqqPgnXPLYLrgW4/gGuRbi+ANcSXHFszmV8QsMEmk9oWGpEvIBVJOwA5vWzqLSMOWsdx1RGSTXB8/o/apnKAUzms5nLjxRdx7Ua7zqWeL7KYedLmNZ1Z4U957mT3NDvAOcRlX5nKAg=
*/