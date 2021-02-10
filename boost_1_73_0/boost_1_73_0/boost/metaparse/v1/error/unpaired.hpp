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
CqEp6HsGP8EHN/anZjqipG2LQaey2A24I9NtTPRv7/95r3v9mx97a7r1o7fPo6+nNN4+x18j9ym48ETb16mLzh/3b1BLAwQKAAAACAAtZ0pScF6VVGQDAAAWBgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzNTNVVAUAAbZIJGB1VX+P2kYQ/d+Sv8PEzUkQHWd+KK0a+VCTg6hIrY4Cl1MqVLTY42MVs2vtrqHWXb57Z9bmQJFqZLM7bzzzZucNJA6tS4XFcZBIlWv6+ob1UZvMjoPPq3mwmK4WQRKfjUnc+AU/wRLNAU3PygyDxGBZ1ARnwglQOt1h+u02qtFG4yDXWgd7fiQx4xyl9acwd4VE5dowqd+Myex20oJB2lvQirYIGW6rJ8hRuMogOA2iKPQRKstriw4yaTB12tTeQAvk9yhY7x505crKgVTX9IJUTz7i3cPij81qulxNZgs4CCPFtiAWbQoq16ckumdLYn3ZVJUrCTjtEiX26M8MMn1UhRbZNeSyQDhKt6PkcNebUHYu88SAWPUkkJn9KFYTghI4VIdxcEnu9mr+OIkL/eRTNniS6v1eqAx06aRWt5HSvabKa1pJlRZVhpEn+iGOr36/X65m8w9XRHF+v1jFpXC7mDMP
*/