#ifndef BOOST_METAPARSE_V1_ENTIRE_INPUT_HPP
#define BOOST_METAPARSE_V1_ENTIRE_INPUT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/first_of.hpp>
#include <boost/metaparse/v1/empty.hpp>
#include <boost/metaparse/v1/change_error_message.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Msg = error::end_of_input_expected>
      struct entire_input :
        first_of<P, change_error_message<empty<void>, Msg> >
      {};

      template <class P>
      struct entire_input<P, error::end_of_input_expected> :
        first_of<P, empty<void> >
      {};
    }
  }
}

#endif


/* entire_input.hpp
Hp2JGRk5iZV4zX+O7TJG0OdrxTuso4OPu1WbvHmQ+t63JQYpv0aOs2Vydtj6qjP5r12Rtjlkc6k7qdD+zlMn98CKoLk8pQlrvr9HhwTJf7BJSB4/3FeAE9bWkwCZhJGInMSVQEHCRgNEZP//TzDuhWHeRJ0cP7M0FSc8KJSI2R1BpYEO5rdnTl1trryj0iHlfhJbzZg9QMXO/W3fIW6j30pHE8vqkdmTD2JIFtTrY2M9d+8jrnAm2zGT1U8znrL1aWwU7Dd0w9fyJ8EZ5xS+SwtCY52eYHp4CSjSNhmNo3PM+GNuuAqqMlDUlmoPhMMvLiKE4wL2a7I/ZEE2I/a2xxNaZ9soQAdiyO7ggEMlItmfuc+DEAlfug6JOBFlUNacQrgudzPLn5Gwe/bZFcSzzm3sRvGypSGXBNL/3m1rToQKCblznX+vZubPBClMgqe9Yk5JeJ016TUpkZZELtkePb3Yl0T1go/i1/M5ZfgVbWhxpr1DVmrVSDAbyLPN+Almm/Itd3n4VGEytM77fnmavkwe4CFDiTB9X4A812iHXLO8QZIrCMuR8vbZNA==
*/