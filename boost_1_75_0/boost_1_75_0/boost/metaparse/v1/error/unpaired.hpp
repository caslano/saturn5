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
TjSFpB5CxSENlikAi90/Xt8Fkh0MkmLfsIc4JEO7QEK2DQen2OYboQWpEEBXOYN+nG54AvTI49Ix8uBYW8DeexYIz8vIS81WiWy/AptUZwVtqNhuqIeJVLYLFdswOjBGx50Qk+5kU2Mf3BXHpsaGZBacMQLlUOLPP0DTOdi0QeG2fZUaHtONOYMW9oFw3wsIvh5M3uHkB2JuUU8x1+CBa6fblHFJgQJR4iFv0mQTJuEnV4ULq1T5J6eQc29SCpx5q/XO6dXuS5EPe6EEiZVbBuKOEnlYAFjQHtBYcEQAWTDUdScf7MPrAJ2j9pZz+l2Y6bfTNZ3Z48fG+QdcikNmPVErx0o+NinvhC1jKvV10+I46Wu5nMoZXIflB6/G4TGAKpJuxwKlcVg2M3cgHyllhwDMVw9pYGKmdRhc17mkDfayH/kAc+EAc8AAi1Zfux5fmxl87aZD2gAbxrtgUVrhfxll1ls5U33rQKaK2N+5kmWjnc2y0fZ5Qt2bVWTAWMFjVBUPZwKntK4JMytJbzdjwUvj67uisHCc5xI2Yd3kRj8PyKUXa2hu+jixBB6QjI/sitKpfsMqjPWi5DFgdPdy0G6oWpZfw4c5mUmbwNmE5bWhRdvBDeLJvS52VuQcTAtEqbzOF373+gWUeLb8Xb4UCv2eguUusR9Iabm/E0lmcElbXLTHkyqQAyeWVT/sCXiK4Zuijn+ZGnxxjqLg
*/