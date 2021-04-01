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
Z8d8PkILdUK3cjEJ4I0VYnq/LCup6IayhMd0zfIUw2a1bMxRe/d3l5hCHU2vNZSpc3c3g0/wS6YhtZ9tjIjgzkBNzO6zg3ZQihykmg0BdzUZD468cGuPw+BCwHkPWB5diRjfqIXG5PnMuThgoI6Q5gXUYVtTK6vjUWnb4tlJgQcmPPQOg39jhElSGp8lGnAUUIBHf2q2mULeIbCRxMnxtNIKJTRB8tSnUZk5zTGRoyEmk9xY5I4vTuTbDJDFZFAXuTGxfCmIqaTBkFsssWs5agl1L3d9JlWhaCy0/zM3eqJVeZqvABwrfuJcp+uhw2u/1bSCA0yUsYYNqKn1sUbUIhZ4jlWuKkQyI47Kqg26Mxg8IfCmGmvVPGy2WrQP8qaN9T3mGYgu8wwZ6wl1q9Wnq5TrpsHOeAYGFgm8ea7pcv/NeDnOkb9gAkn6TwayYdRPlx64kWHqczjfwqujpB+CyhCq9UYvxkN5r4asHm1EBE1mtj26joPBBukETINbKrKFr6plT06nFtUd1XDD9CFy/TLjFwOv/Cg+IAye1cQ9jkHPls28eH/JbeD5SQ==
*/