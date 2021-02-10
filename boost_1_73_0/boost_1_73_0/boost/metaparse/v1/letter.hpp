#ifndef BOOST_METAPARSE_V1_LETTER_HPP
#define BOOST_METAPARSE_V1_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/letter_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

#include <boost/metaparse/v1/util/is_letter.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef
        accept_when<one_char, util::is_letter<>, error::letter_expected>
        letter;
    }
  }
}

#endif


/* letter.hpp
zhUYCXUaBm+jV8JEmUqPsBPeKqkS7ZFFGAaNgY95SBh9Ioy2xbbXDtUVVV+LBAlTeM5vNdw5Fp/lAkvT4XET2ALdsDxSytKm6T1kKXJzUWifyIw5W+SZAFbyAtup4HO7gkqYDNQlioTOgKcGFSyD6wgixeMTGkugLQNYLIuCl4lH+t/g1J1dSve9hb8Ll8GhlsDtbfzVchfON4G/DWmFtOKloVaYofOX8XD+RbvY7SZ71x0cJrmMeZ5JbRy72mMo63a6WL2+UIn0Bgk3vFvKZNieKeMaIsQSHJ3JusW1qa0vOrOCzI/WHNfT1bu/XU9DGI9hSBgqJVUsE6uDjeivkNE7n9Hn7/gBUEsDBAoAAAAIAC1nSlL0SkrkEgEAALMBAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTI2NFVUBQABtkgkYE1R207DMAx9z1dY5XkNAwQSyipNaMDDJtDoeJ1C69KKNqkSs9C/x72MokiOj8/xJY4i9JRpj4lQlSksX1/YBetyn4jnNH0dDDxtUqHkzCg5isUFvKE7oVv4KkehHLZ119OTw/xDXaGhic8GwAI/ZCXCWMNheYaqQE3fDrlFSdQyMwdAGd3gOBUc9lsIFZXgW50hVAZK6wl6BQvlqASV
*/