#ifndef BOOST_METAPARSE_V1_TOKEN_HPP
#define BOOST_METAPARSE_V1_TOKEN_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/space.hpp>
#include <boost/metaparse/v1/repeated.hpp>
#include <boost/metaparse/v1/first_of.hpp>

#include <boost/mpl/void.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct token : first_of<P, repeated<space> > {};
    }
  }
}

#endif


/* token.hpp
vAuO/76M9qvE39Rrom0UHafh79oem2Aa42yfMG5E5rjcPCOj30XJ1/xFpknZs/Dcc708QWg/Lvyekbb4cRD/fZSbO6Tg1jPezuGowu/mhDbUK58WH0481y0I22M/UVk0Eg/K06Gmtz0KFtWqtNf6aJ9OvOeyrNh7/UeMW1rbsgtv43JNFnvf/V31wvfdFlb4PCw8J0thPbExLOCcgvbEeS4b8jzuzwvYmpewJy/lSZzJVF7G
*/