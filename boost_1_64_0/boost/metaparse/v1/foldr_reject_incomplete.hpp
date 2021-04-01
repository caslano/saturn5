#ifndef BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE_HPP
#define BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/foldr_start_with_parser.hpp>
#include <boost/metaparse/v1/first_of.hpp>
#include <boost/metaparse/v1/fail_at_first_char_expected.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr_reject_incomplete :
        foldr_start_with_parser<
          P,
          first_of<return_<State>, fail_at_first_char_expected<P> >,
          BackwardOp
        >
      {};
    }
  }
}

#endif


/* foldr_reject_incomplete.hpp
A7NxcpGbTbEFey0jJyd+opJVGNTPoxOs9Mje4L5MvwF5KRsjKRYHq9Wmn8pWJuQ0C7qsTjoHP6COuEQ4vW4Y/9/nSa0NX3L/V8fCtfnsbNZAgJSj/h1S/rcjPHJOhaKQwfpI0rDjP1Tq+uLOTRC+zggD5lCT46cP4vVoXzcEEdbg/NmQi8C6GnX/iLqW6VRJF/1nFkvLUUdYWoinXnlRtJ4bRX12CSLwq88WlsEmB+bWDnIgatkIhtmkARykRS2hbquHCBkRmu/c9rx61WiMC61lnT7jUM8aD6k1pfueINrxVoLrGufTQXUXYBtEJ3qad1y9cCO69i/ZLJCaCGzpBUPKWoFacAqpTJCjOqbsJ+SWE200Ow/5378yDMMl6NZnMtNrrhGtJjfcAM9YT/f+b90nG3Fed4Efmhp/MT2Uktxh5hz6QjIDcavkzFDMvrDHcfh03u8SkXjMeEcpMKPrI+aP0xda81GNM7ocw/IqXYW+1z5h7AFlFGE1ACsbhHmLThk7kqhu6SNA916V19Y33i9s72OQDKfo63XDUhKNCXTfem0MiKoIrnhq+Q==
*/