#ifndef BOOST_METAPARSE_V1_ERROR_UNPAIRED_HPP
#define BOOST_METAPARSE_V1_ERROR_UNPAIRED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/vector.hpp>

#include <iostream>
#include <string>
#include <sstream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace error
      {
        template <int Line, int Col, class Msg = boost::mpl::na>
        struct unpaired
        {
          typedef unpaired type;

          static std::string get_value()
          {
            std::ostringstream s;
            s << Msg::get_value() << " (see " << Line << ":" << Col << ")";
            return s.str();
          }
        };

        template <int Line, int Col>
        struct unpaired<Line, Col, boost::mpl::na>
        {
          typedef unpaired type;

          template <class Msg = boost::mpl::na>
          struct apply : unpaired<Line, Col, Msg> {};
        };
      }
    }
  }
}

#endif


/* unpaired.hpp
9//MBDo80/5vJtDhSeb/PGH88KT2Fybww3n72gQ6/GWgb02gw18revXPnUyH7/HaAd3wPZDuRyfQodybJshFvbprAt21cOkJdPh8Pzvh+fAXAd46gR8+37kJdPh8ywl0yO/RCXTI79cm0KG+PD2BDu3tQxPo8Pk+NoEO/cYnJowzyv3kBH7ot5+bwA/16u8n8MP3eH4i3YsT6b4xke7/JtDh/L7qLdPovn8i3esn0t08ke7uiXR2It39E+hQn3c=
*/