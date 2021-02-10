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
SlK0B2JLiQIAACYGAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTM0NFVUBQABtkgkYOVV224aMRB9t8Q/jIh4iSDm1krZLEgRREnUNCDYpI+V2R1YK4u9sr2k/H3HXm5S+wXty2KPx+cyMxaxQ+tSYXHMYqnWmn4+cP+pTWbH7ClJ5uEDjw8Ji/n5JOZ1MrtiscGy2FMoE06A0mmO6ceouUfbrBF476YH/W4XZt8abCocRpBU2IbuLbzqHZ30utAbRsPbiHIevycNtkSzQxOB19axYcPX4gMbbKKVQ+U6L6g2Lo/gawgpTJ3UKoK00PYiK9mX6FF+OZ67bXE+mEpbaivrS2tZoBJbHPlPbzAc3kGaC2PRjdaVUvs70KXPHFlnhNoQfoP1+oPhF6qC9+yrcagBleMKJoX0HFZmyOI0bMYUdrm0YJD2FrSiLUKGq2oDaxSuMghOgygK/QmV9Wvih0wasqbNPgRogf4egXVmoCtXVg6katMFqTYBcfK2ePmZPCyT6fMCdsJIsSpIxYGCGhcoSfA5EtcFHrPcuZJOjtvYl2N8aj98Spd73o4EoTL4Synb0JmGahJKfZmwKWk3Zpe6Rq35jykv9CaQ1edxqrdbD3sodVPpTm2wTSup0qLKsFlr
*/