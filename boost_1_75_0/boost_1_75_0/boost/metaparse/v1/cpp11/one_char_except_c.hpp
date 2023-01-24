#ifndef BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_C_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/unexpected_character.hpp>
#include <boost/metaparse/v1/cpp11/impl/is_none_c.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char... Cs>
      struct one_char_except_c :
        accept_when<
          one_char,
          impl::is_none_c<Cs...>,
          error::unexpected_character
        >
      {};
    }
  }
}

#endif


/* one_char_except_c.hpp
V4xvD0h0poAes2L247tKmExDOtdj5KuYvdwp8tqnc177UGrdp7jpm5ltAgjEDiYwBBXCmWqLln5U5/xike9BqL0nTHaptDV2aCvWT1rVsniT4a7Soq3sjD+rvd/FtnLVfv/PNktjd7/cMoy0X3wU+LxFd1Tmt9ftCqcDaLehQBy1xq5Wp1vdWxZcDzM5RS7budApq6kD5Ik6Ph2s27QonX+j9DV3gly2XlbT/ekkJHSmz83VjsJqstWsPBoqSY+WpEZLHHKkAbAjDaRDicWWxbC3yeGou0dv4pn1GTI7Sm850pYuu1tC/SMt6LlsjWjWRXYtjWBmz6RR24xjq6cP8rmkwLjup4jbunCScmmq9sMxTNxfVaBMTiWBSNIbgmUNRbYGLYax8Kp9Nnbrbg0N4v5s2J8DT7OHDnBetB4+yOTT0BtePQNfPe5wSw6QGJVz3DHaf4dCNrJzVva/DE2RF3ehen1eP6CjcH7u1LYMARpCSQNcg+bBOMtQ9zqSo2yH8ZTgMJSCShNMBdWnJ5+d4MYcHy5wIa93CFyhvMwwkgozNzPx41mUNKgdWcoydEeOVP0EU3BX/bJwoHYtdEWuvNqzvzIc4VgZgF3YGur0hX6BKH6sEaQOvyiIh/+H2v0YDK/0ilaBXNur3BcdazPhOMfwUycNKwwR2GDGrnlvEYbEPkrgRZQUUtP0RlUEwNgrR9b/FCm0VANSuv75
*/