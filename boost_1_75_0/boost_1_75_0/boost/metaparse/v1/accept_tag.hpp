#ifndef BOOST_METAPARSE_V1_ACCEPT_TAG_HPP
#define BOOST_METAPARSE_V1_ACCEPT_TAG_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_remaining.hpp>
#include <boost/metaparse/v1/fwd/get_position.hpp>
#include <boost/metaparse/v1/fwd/get_result.hpp>


namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      struct accept_tag { typedef accept_tag type; };

      template <>
      struct get_position_impl<accept_tag>
      {
        template <class A>
        struct apply : A::source_position {};
      };

      template <>
      struct get_remaining_impl<accept_tag>
      {
        template <class A>
        struct apply : A::remaining {};
      };

      template <>
      struct get_result_impl<accept_tag>
      {
        template <class A>
        struct apply { typedef typename A::result type; };
      };
    }
  }
}

#endif


/* accept_tag.hpp
Vda+QGJRIUB77icp5li1dpe+YYaCujvkD98kgXjPO2Zsl/j2m2aqtPsyv7D5HWI6G96h3+/w42v8+Dy//hT/vYgfQ+/wWMMEHo81LjUpl9f9ZzKZRzru4Y3aD1Gge3cR6I7151uhKkSZBDO2o+JRgzFxz29Tf2TK27ARe7CoweR3eNmtXhA0co8xyicX/Y0RsyvYNZmuybpriZewa4zcFmWa/Fexa5m6a89eGouFSW31bAnQMjRIMHoRhg7omilOZkZHNLTTRTRoAYm62Ae3VC5qOKaIGo4Q5UwLtv81kR8Vq863iXj9p1erdb6h6ix2gtnD83QmuDIaXdIvxAFDgYXO9YnE6xfKb1cArw9UYYUKZ3iETU8+gNYzlrAQG+Rq7N4NjpbcpGY2T45aMAPLXrgFuzfcJy2cE83ul8/hxXiksw3ljmbwEktuNk0mCOymJmBQvOOiZcTu67A+ySl2faUzuJ1x++nA6NlGRQbWC58PrGLgPmCiUtgHGJe8usGqa9IKjPiAYMQHVEbslQIH1GdjMfpvrNj5KhRY574gcJBGP8hGHy5Gz1YDBLGFSxe4TcfmD+KjwakHGZtXBJtXBJtX7PPnW3nB5jGUCzrPxD7Rgp/Ifikm6mKkeFQOUUjc9yi/ctSjcojx7Mr6VjoOQQVlXYrgDkd5M+7cpQC9CVD77e72MYU6aL9ErgXA4qUqAw5UqF0RS1Fyo75p
*/