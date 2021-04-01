#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_PUSH_FRONT_C_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_PUSH_FRONT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_front_c;

        template <
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, int C),
          char Ch
        >
        struct push_front_c<
          string<BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, C)>,
          Ch
        > :
          string<
            Ch,
            BOOST_PP_ENUM_PARAMS(
              BOOST_PP_DEC(BOOST_METAPARSE_LIMIT_STRING_SIZE),
              C
            )
          >
        {};
      }
    }
  }
}

#endif


/* push_front_c.hpp
0YR6099Fh4S1DNqeuz0WkHlFeo9v1wV3GMIYyaE0vutjgehvTOnyHWs7DSirsJRkhn42TygVZNwURPqHTKO6l1sA/POWctS1+ILmC9JjsY7Z3CeVBtYBpg87DntwnDWgpOQWYShhJEINfKm0dSF9ITu1h+TdhF0XnUy8/s636qL+DU3cUEzhM5fIPDxaYU7r3RB6PUyLexVBB7CdScm6Bahr4TWxL0AfQJNY5h0d++LGhHWEHL2mJQeBvE0bBLnwq5+4gSyTTXRKzgDoIWoi2shBEQcZLNWvWoLvcCo9pWyLbqGoqIoYsXBOBg6Z+9xPapI4NnzEkZd3hY0k15EX/rh4uwXChUSAFuew1tbNuMr/1LOXSiiN5bhtkTlcfTw7+ttNbAb6XRK/RUkilJ7PSs53trQY9Py540qA5jJhe+BHr2x+Ps6vv5p+VvPELz9rGnUspk113recD5grpHwWaClCDajt/8YJlgy5N704eUz2jFaJEl0dBqg2WGcbHyW30VtDk/iZsWrpD8PP8A9xd+Dpzzcq6FVvzy7w+yHu/afwvVbp+Qh2TJmM+Q==
*/