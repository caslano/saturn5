#ifndef BOOST_METAPARSE_V1_CPP11_LAST_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_LAST_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/nth_of_c.hpp>

#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/v1/error/index_out_of_range.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      struct last_of
      {
        typedef last_of type;

        template <class S, class Pos>
        struct apply : impl::nth_of_c<sizeof...(Ps) - 1, S, Pos, Ps...> {};
      };

      template <>
      struct last_of<> : fail<error::index_out_of_range<0, -1, 0>> {};
    }
  }
}

#endif


/* last_of.hpp
xpWJmCDw4Im+5orf35c03G+ms2033dCHz++bcOZnJtpqKVEGerpd91qCZ28nO7rJir8ULmBcVUUwGm4IKrfCo+uDKoiHRKADozrkaPWO5ISigBJFK7UzhhsOp+RUulo+ZWZrUC13MJHDDRZeKWP5pa0icQF6cIfnmL6nFLccSfI9/fT25ASUmhE7bTqfOoTz6Wojiuwng0Bf3hoP4d5PuBRuoJQaOB7Mdk8Dodvo9YrODAPF0dyIYmVaLDWANiqRKTpdVpopQHyHHLUiv5+GCTwC0V5FdftDMAr/3gAm2u4Rw3wcj2ImHdt01/dLjhd7Qz6vr1gYCxqIS9pYmRRY36Jt7kOVInVX/yWG9+uqPiK3s/jcIvWs7XDLK0nSM0D4McxmSQzRsD5d7D6Yo7u+vsdwH8SYd9jFb370ma4bIeZVN6/G4O5yN9wIz2YuG8TNa1Ch++QAFmKhkWexETVjTBgl+sJaZGftJ8EPdKLarq0m9+T4GSTkwTW6xZJQogHlP5yHaPJSaJK3wGMOYW8lXXSiI/WSlSZak09vF/ky2FveQSUlZmAv2qtRVbW6T8Op+Q2x3jgC12MRdDhqhLHh/WEDcRYZD4Vw6AsjNPQlIRo63v6FJun/nuGI6c1JriTKhzmqMR+vUX+OE6PvlZvXA3rX6K69QIMx+UqzX6P6ZojoTCcxHQxHIR6klzCj6w7d9Ry8AEj6UEN9LyOZ
*/