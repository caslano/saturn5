#ifndef BOOST_METAPARSE_V1_KEEP_MIDDLE_HPP
#define BOOST_METAPARSE_V1_KEEP_MIDDLE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/nth_of.hpp>
#include <boost/metaparse/v1/transform_error_message.hpp>
#include <boost/metaparse/v1/get_col.hpp>
#include <boost/metaparse/v1/get_line.hpp>

#include <boost/metaparse/v1/error/unpaired.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P1, class P2, class P3>
      struct middle_of
      {
        typedef middle_of type;

        template <class S, class Pos>
        struct apply :
          nth_of_c<
            1,
            P1,
            P2,
            transform_error_message<
              P3,
              error::unpaired<
                get_line<Pos>::type::value,
                get_col<Pos>::type::value
              >
            >
          >::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* middle_of.hpp
tlXCmIyOWAllfUN8dHiYKNSxEpMO3vpWKHmpKXmEiYVYwDuGHYYy2hqFCji4Qwacghnx7Cz6dEKYOWFInOcq4clzWf6mqkGdxoBMM3q7LyOZDlNkxKUByuue1TbWIeQQdGjHnveCI+oiONtxDRqnWwbLIxqUob7Xvq5EWcZUYwgMb2VPtLp/eISyvCKEsoMtfq9lbjP5eZTDkwOhWLBtst2zkKfiamMBPdVcSrhPRSW+jje5ho8twj/Sl2W3/Kv/TpgxuDXcrG7hNVAiQw4KllaApwRxHAYKCWugALWNeuM4tp5XbPJgvjemyi8BEwLuBzQJtAd2zxPReoO5MQTa8fsw6YQ21PD59iLUjDHsoRIrXnSVKnn2Li+/5wdQSwMECgAAAAgALWdKUsdwikX8AAAAlwEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjY5VVQFAAG2SCRgXZFRT4MwEMff+ykuW/ZI6kDBLQ0vxsQlZixC9l7pMYjQLteK4dvbMWTqU+/a3/3zayscWldKiykTja6MXz5w+DKkbMqCgNDREChs5cAEv50IfoXZki0hR+qRAtsoZILw3A4XYCpG4qltULuJKMfGI3acS5k22m/znxaElp33ccZAK+mE8McDetl+
*/