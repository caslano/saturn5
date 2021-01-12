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
9ucqZnM1x/FdTucazuIHXMJ1fJvruZobuI2mkX8+xjFB+Q4Q5uFl/TZeec5nZT7EunyELbiI7fkou3Axe/NxDuKTHMKnGPRrEJxTaePkfg2C+3n343Osx6VswGXR+4PzIe/Zw/vPMl5RdmI1nsPjeS693/oUnMsE5zgpbC3KB99lnhscb3RmA3bhyTyfZ/AC9mMqB7IXh7M3c3gRr2MaJzH9H+zdC5xVcx4A8CjUFpLU9KLt
*/