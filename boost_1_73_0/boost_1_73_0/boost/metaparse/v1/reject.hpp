#ifndef BOOST_METAPARSE_V1_REJECT_HPP
#define BOOST_METAPARSE_V1_REJECT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/reject.hpp>
#include <boost/metaparse/v1/fail_tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Msg, class Pos>
      struct reject
      {
        typedef fail_tag tag;

        typedef reject<Msg, typename Pos::type> type;
        
        typedef Pos source_position;
        typedef Msg message;
      };
    }
  }
}

#endif


/* reject.hpp
6LyZTM7KC/x4MqkWr/gMHYAWJnFimaZynsqQGi6FE5DaMyAVmLMGY6bumPI0j5gTKJanC9yOqKEVPvE7PvS6fgnJhOEVGuQpQ1ag53oqCxGyhlMB9eEdD5XUMjbeaDQm+51uw7m8vPSOan/WX/FUjKbZwLUiy6W7DUIi2sD1u3u7+92e3+vhs1uZD1xLwG04x1IYxPEmixxxDPvNkMRk6SGECVWamQHX0js42Hvh+bXxWyZmJukDcmmg+EpeqdLvdrufKd3t7sAkoeJGQywVmITrbZgWBuYM5lQYMBJJR1zBQhY/fE30nhX9TUTfLrPUB+LvHOwjqefZV7RXCvw/5KoH76WB15iW6PsRfJ4LEqjIhAkLb/63lfMfKpN/sR6WNYB3y3GCU+Y45da6mjJheTN01pxAl3SGTmJMjg6r2yBm1BSK4agK1SI3EvfqR4GgGRs+Tj7wvKgqCi5CLAbNxawqBi9E0QZ9K4c1zBnXYEpTbXPEhEZIzB/73AFaImyvwJhGP0tP9wmZcZMU004oMxIWKq0ueZGmmI49H5XJLKMiGjpegWWPavo0p1rPI+S4GsQ1XYuKoOtvTseT0Vl/3Qo6Oz2flLlF1o9ouFyGDLlcMMXjBdhIA40NUyX9UlRCNUwZE+DqRBrXCe5K
*/