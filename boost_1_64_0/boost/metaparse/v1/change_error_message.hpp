#ifndef BOOST_METAPARSE_V1_CHANGE_ERROR_MESSAGE_HPP
#define BOOST_METAPARSE_V1_CHANGE_ERROR_MESSAGE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/reject.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Msg>
      struct change_error_message
      {
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            reject<Msg, Pos>,
            typename P::template apply<S, Pos>
          >
        {};
        
        typedef change_error_message type;
      };
    }
  }
}

#endif


/* change_error_message.hpp
aOcVUvNanHrfH9CAC/bNKBfuvrVmFFoCDrSQYDKCrkj1YDXM3AFrZrx83JJxI0h2HRMkClRWOwvbO7GOF2UcL2mGcO2sRgLBdFRFK+s8btZ9PAVP3Z8jw+VOp6MarTgGISxEwWdxwu4tYNIL8pSI/nV+ax/YqgGUKnYqsNhVHEriX3gpHnsPZbM48geNhi6eH/pzTsBhM+saFTmXKlKmYuy0QJL9y5SnGhVpWNdziDXmThzeIDngOcZCv+7QLNaYX1uL31OYYUfT2Gx1D/l4/nWCkgXCRDNUT7NDpoA/v3oClaXVjXvnlrNvTXs6MboyAwS+4qwH+RXHN//taOCHxw0FNfIoVAyExeeLhJ+OTw8J/7l1nVkavN6oXBVwYkqAl8QFwncWPkldWMR/nOOS2+dBAS50yEBeelfFw9Vy4CUugxYJDoBybdb+I2+48L9pZF6n0+Gsdopz7/wsbibQZwmTaoB4AsrGvkaWaYbJ2yM8Jg4ftQ+eIsr/fqGdwFgbLequCPGVsAzS6oV860ztA/azUhKphHKy2ojK+AD8x1X6d4E4gbiphxu9Sg==
*/