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
CwPs72UkGeIJEndUh+r7JHcpk/WD6xQjkHIo9UiVMF6+E6/+QabxkL+Z4oPlL8xf7T/alfkHxTOetLrrdktYeGyg/EH91rixH3G77VTuQ9TPZ3v/pX9cVHCYrIvb1OPP5GNmwc5315bvqMyzf7glMshsS9uGdPcJviRy66GttyPq97plntZyHyAEE69COuN3zQMDw5V1q6a9J2l36NIeMKQlPLVNHMjKP/KejQuhDOE+FZcS
*/