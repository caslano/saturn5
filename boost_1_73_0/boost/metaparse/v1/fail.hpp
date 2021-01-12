#ifndef BOOST_METAPARSE_V1_FAIL_HPP
#define BOOST_METAPARSE_V1_FAIL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/reject.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Msg>
      struct fail
      {
        typedef fail type;
        
        template <class S, class Pos>
        struct apply : reject<Msg, Pos> {};
      };
    }
  }
}

#endif


/* fail.hpp
TS7liVzG1nyebfkys/kqX+Nr/BtXcj3f4Rau5nd8j/sf5fiHB/AjHs2PWZ0b2Yyf8Q/8nKdzE3tyM3tzGy/j17yG23kTd/BefsM53MWn+COX8ie+xt18l0X2t/2wGL9hcRY92vrOMizJY3gAa7AsW/FgnsVy7M5DOJDlOZQVOZaVeB0rczKP4DQeyZk8hk+xGp/j8VzBmvyRtVj8GMdLPJH12In12ZWN2Y9NOJxNmcNmHM/m
*/