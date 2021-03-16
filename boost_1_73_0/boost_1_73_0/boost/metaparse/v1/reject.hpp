#ifndef BOOST_METAPARSE_V1_REJECT_HPP
#define BOOST_METAPARSE_V1_REJECT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/reject.hpp>
#include <boost/metaparse/v1/fail_tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Msg, class Pos>
      struct reject
      {
        typedef fail_tag tag;

        typedef reject<Msg, typename Pos::type> type;
        
        typedef Pos source_position;
        typedef Msg message;
      };
    }
  }
}

#endif


/* reject.hpp
ra5/ozp+pYqjVbxIxTEqjlVxsYprqbi2iuNUXEfFVf5sSpLHVzWQ8QEVh2rIeJM6vipZxmtVnFlPxpXqfCF1/Eh9Gcer2CSq8zVR/ngZB1WcqvKfofLdofxHlD+1kbqe4oPqeFAdn6HOF6/yD6rYNFT+GOVXcWYdFevjqvzSVXwgQd1/XeVX93Ncnf+AOp4aq3gVZ6r4gIp3qDhV5XtEHT+ueVV/jqt4rTpfprr/VOUPqfKtVPEmdb4Z6nzpuj4=
*/