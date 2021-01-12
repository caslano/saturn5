#ifndef BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_C_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <char C>
        struct is_whitespace_c : boost::mpl::false_ {};

        template <> struct is_whitespace_c<' '> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\r'> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\n'> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\t'> : boost::mpl::true_ {};
      }
    }
  }
}

#endif


/* is_whitespace_c.hpp
sDOGYlf8ELvhIeyOp7AXXsfe2IAfQh/shoHYB4PQhP0xGkNwBJpwOobiYgzDNRiOpzASH2IU5qFCo9EdzVgcJ+MUnILJOBU34jTMygpJwuI4CyvibKyOc9AX5+EBXIp3cSU24wf9HgbgahyIa3AsrsVx+D5OxxT8GD/Aw7gRP8dNyHrmZra8J4YJBE9CboJFtpOtpMuF2zAf7sByuBMr4i6shR9hA/wYW+Ae7IR7MQD34yA8
*/