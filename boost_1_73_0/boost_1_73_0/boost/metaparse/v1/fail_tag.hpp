#ifndef BOOST_METAPARSE_V1_FAIL_TAG_HPP
#define BOOST_METAPARSE_V1_FAIL_TAG_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <boost/metaparse/v1/fwd/get_message.hpp>
#include <boost/metaparse/v1/fwd/get_position.hpp>

#include <iostream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      struct fail_tag { typedef fail_tag type; };

      template <>
      struct get_message_impl<fail_tag>
      {
        template <class A>
        struct apply { typedef typename A::message type; };
      };

      template <>
      struct get_position_impl<fail_tag>
      {
        template <class A>
        struct apply : A::source_position {};
      };
    }
  }
}

#endif



/* fail_tag.hpp
Ex553LZXrX3pgszIiiek58ZteuCQnMInHkXS5KhDDwNd71fM1WsZkmwwXVAlaPQ+TDYDg/7ztOPLy6FRXL+B9LlhxyAX1tEbxue2qphsU9AwSY6+TO7m4+nwKBQwnczmScLf0CXnjJy9NozWHYjN7TcTv6af6FTZQu1xXVionSWbW727HtzfziI0teOXljoie4owZntGjIStc1vgEAaiim+bE5Igr/7woi8WerUxeViLcF92TUO4EKXSGBoyhFg117en7EJ6CVdwcz/7evswmd7OrufjyfeH+fjb7afJ/Vxk6Jx1Ie1IpAH6Yp0luxqT/a/MP1BLAwQKAAAACAAtZ0pS9O8UMyQCAABUBAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEyMzlVVAUAAbZIJGDlVNtu2zAMfReQfyBcBAW6ar4k62bBC1C0QdutbYLE7evgynRsxJECS0mWDvv3UXaaYtgn7MU2JfKQ5/DAiUVjZWZwxJJKFZpeS9zvdJObEbtN02n7gJtxyvgrS/z3y8Tv8k/YCcyx2WLDTZUjSxpc13u6zzObgdKyRLn86u3ReB2iH34MIQoCmHxn15lFAekGzyGI4VFv6SIMIByKYSwo5eYhZR24ADcpN23gF9kS2X1G
*/