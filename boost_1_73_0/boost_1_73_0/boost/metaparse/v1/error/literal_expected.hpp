#ifndef BOOST_METAPARSE_V1_ERROR_LITERAL_EXPECTED_HPP
#define BOOST_METAPARSE_V1_ERROR_LITERAL_EXPECTED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace error
      {
        template <char C>
        struct literal_expected
        {
          typedef literal_expected type;

          static std::string get_value()
          {
            return std::string("Expected: ") + C;
          }
        };
      }
    }
  }
}

#endif



/* literal_expected.hpp
bZQk9O07CKPQFS6ttCbxnUbaoX1w6jjq3lRpisbkVXHlmL2HqSRhusGac2PEHuGryhA6xmrhGHTZsN+HGexU5rTshUXadTQOnF7NyMtgBAOS04BCfSIl6Fby1EJJNGjMIFca/Mh0utAZ9EkhNAVdz+BPuHUDf2ymI0rathi0Khu66XZk2o2J/u38P+9Vp3v1prOiWzd6/TT4dUzj9dPwV+S+A2eeaPsyddHpm/4fUEsDBAoAAAAIAC1nSlI6fF7sZwMAABkGAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTM1MVVUBQABtkgkYHVVf4/aRhD9fyV/h4mbk6A6zvxQWjXyobYHUYlaHQEup1aoaLHHhxWza+2uodZdvntm1uZAkWpksztvPPNm5w3EDq1LpMWxiHOVafr6gvVRm9SOxYfVXCymq4XofRRxdLbHUeMqfoAlmgOans1TFLHBsqgJTqWToHSyw+TLbVijDcci01qLPT/iiHGO0vpTmLsiR+XaMInfjMnsdrkFg7S3oBVtEVLcVk+QoXSVQXAaZFHoI1SW1xYdpLnBxGlTewMtkN+jYL170JUrKwe5uqYXcvXkI949LP7crKbL1WS2gIM0udwWxKJNQeX6lET3bImtL5uqciUB
*/