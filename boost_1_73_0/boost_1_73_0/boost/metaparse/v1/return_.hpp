#ifndef BOOST_METAPARSE_V1_RETURN__HPP
#define BOOST_METAPARSE_V1_RETURN__HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_result.hpp>


#include <iostream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class C>
      struct return_
      {
        typedef return_ type;
        
        template <class S, class Pos>
        struct apply : accept<C, S, Pos> {};
      };
    }
  }
}

#endif


/* return_.hpp
UlBtAdUB1V5QXVEdAtUL1TFQ/VGdAJWOKgY6jxGokkGNQdUB1EWo0kBNQZUB6lJUU0DluvxAzXX5gQq5/ECVu/xAXe7yA7XU5QdqucsP1E0uP1C3ufxA3e3yA7XW5Vcb2j+XH6gNLj9QT7r8QG1x+YHa5vIDtcvlB2q/yw/UAZcfqPdcfqA+dvmB+tTlB+qYyw/UDy4/UL+6/ED96fIDZX/HIeQXh3tANj9Qcag6xOE+k80vDncMbH6gWqCaEoc=
*/