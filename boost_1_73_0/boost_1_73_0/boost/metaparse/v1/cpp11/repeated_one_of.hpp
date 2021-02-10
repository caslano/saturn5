#ifndef BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/repeated.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      using repeated_one_of = repeated<one_of<Ps...>>;
    }
  }
}

#endif


/* repeated_one_of.hpp
M9Bz7dEOD9ZEJgGBmWxJuceVkDYxQ15+MC4PN7I9rNqyrAttQ5gjhVSDAAAUWHzLT+IroSD8xo11PsU9JC1eUvLBzo+xeUIpLeBXVnltLebCCMj3gWF5dYGjZVGioVDicrJ+fwNrktVRXUIC62GYSZXHdV2ogbMsYNIh0kCxkCyGvyXwweskqiq9D/smo/o+Iqg0ntdna6VX4cANOFUjNHVctdWUbsNiD/6OpSSb+MDYvIZ5aFp89nfVFsrEPSs5Ka4r+KbkFo3jCXLjJvGt1Pk0bKvdIbyerlo055Qaqqr5BcQnycBnwMrf992sUTq9K+2F/jAbSrA1bK/qH/RcipMn8LevVtl3pQVABRJtVjaC2Lth27Reo2WDcSxJn3l0mbjVCSNwdoHHcKc063nCZXscf/sLmKmSHMG8ZfE3LelZYmPuvZO6KrMv6VttJTmlN5bA5JLKtO9iQuGusQV5gTUu2oSk6YzpWQvOnEgn9YcFrTdjQejEhRbU8b0GiKOKEOnK+p21YMyFGXLZblylSy0K8wcqKbeOzCVzgJZeAy6CPO/DNhsN2HfrJV9bZZlM48cjkITzpPjsgIyHJ5m3IH1O5hdU5YXS7yoFz9wv+dse9H3ExYzWunx2pSsYhfgBu19D7+3d7/u7+/fH
*/