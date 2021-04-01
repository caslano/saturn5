#ifndef BOOST_METAPARSE_V1_RANGE_C_HPP
#define BOOST_METAPARSE_V1_RANGE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/util/in_range_c.hpp>
#include <boost/metaparse/v1/error/unexpected_character.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char From, char To>
      struct range_c :
        accept_when<
          one_char,
          util::in_range_c<char, From, To>,
          error::unexpected_character
        >
      {};
    }
  }
}

#endif


/* range_c.hpp
OwkN5aoLsWIjPYMti85IA3zqmFDeiSgT1CQCXX2mugSHExP/eE36Au/kRZkEVZTUXZ3XcXaGNTxOQeUHUaWqkiy+FadXDM4B+oSQkEytj80ljYbQVCfgx+a4c+S4+ofrL3x1z9d3sPiC9zoEZw5rIN/KbgHEdARL+FRwSn/ewnQLA+HOMm0OmRnE/AJMuFpTjEV73rYy3yEp4Hi9Hxt2lYULSPrbI639VUwg+jDSU37xtFIakMke3uOvhcn3j8Z4JrHrGQ5QJX/oZgEJZ0/ZEbGmhEcnBbeL9+xoOEyz3GCIC03mY8ab6Lc0vKlYhcQKyu2kYY27z3OSLHYqYPYpaFb/WE4lwoM3slpOTvlHMuaulDMC+3n7InO80V7vOw7RXRXcDGhX4RzmX/X1jbqpbQi2fZlDmquncl/E9sWJJQmtiVYMImtT1dbxpv7NTmUok9O6lsJWCMJ5iehhPDgonraIvDMiBlM2IFVxmA6xhXyr/XFJyAEEj2QT2eI1P1mSBaRqr5+KRkCrnlSCUO9DhcoP07oj3u6pL7BVy5ZtK9MISceQQ2hNTC1uqw==
*/