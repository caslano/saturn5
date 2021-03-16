#ifndef BOOST_METAPARSE_V1_DIGIT_VAL_HPP
#define BOOST_METAPARSE_V1_DIGIT_VAL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/digit.hpp>
#include <boost/metaparse/v1/transform.hpp>

#include <boost/metaparse/v1/util/digit_to_int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef transform<digit, util::digit_to_int<> > digit_val;
    }
  }
}

#endif


/* digit_val.hpp
yj+eI/68gk0EyI12OVXMTk/mvI/PUSRZMn2PUvEPAjqvHEcAvf+D7NWnLrJdz7aNz95p4B5ZjYfBM/nmDM8XZ+G18nXVHv2It1Z74coLxLU+Ky8M1+GCwUcngsUPE8jktDuI1ehXDe16RHgpZhQS1JoZtD2rkTFlBpOKFyGv6w339kX7+rd0DUT092zP9B7ujv7BgXg40Zvswl0jDTXjK7o39XT3RyLA3TU0HOrc7BEQ74oODER7I/39CsFm/aU=
*/