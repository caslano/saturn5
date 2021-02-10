#ifndef BOOST_METAPARSE_V1_IMPL_ONE_OF_HPP
#define BOOST_METAPARSE_V1_IMPL_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/none_of_the_expected_cases_found.hpp>
#include <boost/metaparse/v1/fail.hpp>

#include <boost/metaparse/v1/cpp98/impl/one_of_fwd_op.hpp>

#include <boost/mpl/fold.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Parsers>
        struct one_of
        {
          typedef one_of type;

          template <class S, class Pos>
          struct apply :
            boost::mpl::fold<
              Parsers,
              fail<error::none_of_the_expected_cases_found>::apply<S, Pos>,
              one_of_fwd_op<S, Pos>
            >::type
          {};
        };
      }
    }
  }
}

#endif


/* one_of.hpp
wfmofwlJzpVGM85qIXaXICubOdZGcbEi/A4bDM9Hn0gF27NVY68ByXEG12Vha+giRRYlbjOhsMkLDQppr0EK2iKk+FavIENuaoVgJPCylFuotV1TfUgLRa1JtXMBWqC9R2D+DLhIwX8AWZuqNlCIHt0rxMoBXz8vHl/jm2U8vV/AhquCv5VEZl+J5ucqE+9jJGp0nrDcmIpO2m1kVZkcjADbwuS2PJW2DP6iaA/8qROVUJrLhE1Jmwk75TXuzr9Ng1KuXLHmPErkem1h94p7QvpNgz1aFSIp6xS9hmMYBN272TK+n4ddy24+W8SBHZ+lZglOgcCDHHmqm/AWvKRWZQhLvsHUStqOHro/2+UrZpm10wZ/fRcecdtTslNuh+nG/IKqyHbgXM8zg8opby0LOdfwhijA07k0BLJxuQRRKWlkIssJs1o2dNtvpMPupDYh/NFVhz3TNPyrFRUnj1MLQfflZrG8nz112FWSYEXhD8EHa8woOJaggVNTA3Dm9qwYrcNJwtbBLqXNHZ7kHoT7jz/jpv1h2/75SfvapOQ81z+sZUpRS4C0+KeF9nY+iLxHP7fowcEBwfGf+xtQSwMECgAAAAgALWdKUn2C0/iGAgAAQgUAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9k
*/