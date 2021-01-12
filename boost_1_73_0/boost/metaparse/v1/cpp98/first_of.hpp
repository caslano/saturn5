#ifndef BOOST_METAPARSE_V1_CPP98_FIRST_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_FIRST_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/nth_of_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct first_of :
        nth_of_c<
          0,
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE, P)
        >
      {};
    }
  }
}

#endif


/* first_of.hpp
VdiVu7MvqzKNezCP1Xg+9+K1TOHtrMXFrMOnWJeFfeaEMgjMKaHPnDsqKN7JO1mNi5jCe7kv72Mz3s9WfIhH8GEezUfYi49xCJ/gMC5mlB/5YfnPieT8GG66OkxjA6Zzf47gwRzFjjyNnTmaR3EMBzCbQ5jLC5nHOziRD3AyH+bp3MAlIlZegD+F9Owl7gvpaR3S04YN2JbNeDBbsx3bswN7sRMH83COZGeO5RE8nV05jd14
*/