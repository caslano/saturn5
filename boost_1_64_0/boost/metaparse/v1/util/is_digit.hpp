#ifndef BOOST_METAPARSE_V1_UTIL_IS_DIGIT_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_DIGIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/in_range_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class C = boost::mpl::na>
        struct is_digit : in_range_c<char, '0', '9'>::apply<C> {};

        template <>
        struct is_digit<boost::mpl::na>
        {
          typedef is_digit type;

          template <class C = boost::mpl::na>
          struct apply : is_digit<C> {};
        };
      }
    }
  }
}

#endif


/* is_digit.hpp
+KaqK56vtiFNmxRSLFCgAlWximhFrRUFJIpItK1EmdNNN9EY3Iea+tm01NCNEOvXZJNNNzbZxjbcnFOGjmlhaCvrXHHMsa1qYd32YrpZt06rFrL//76PvDQpFHVzH+/+fjxe7j333HPPvfecc8899/VS+pvewVtsCfr7xWrAzb+Q84/flvsST87GHofSR+yMX7sSP3+2HY/GeQC51Ym8GSaUNt0Enj7FYNByXlzuuhK0nE98F3+S+oNd7f4q9XkuunXfvQ7I+24T6FuLx0X73ODfcuSt40XP+6/gfuGjeAueDQTfnAcE83gbK0F99K0tIPzKDq7fItqn5+FRR3EYvhnkShQ81jZ0/9Ok9LdfA1Unm1H3VS/9GzW0x9vpz6FAmVRn5v1V2mu0zLfy7fOcB48tRmmY0RNbLvCgv+eh2l+3MR4uh/7Ob3C9/RKlt12EzhQ/g9KyMXi7nXnjLwW5zZSn3S+iv6cOMP7vEWApmHME8O0vxnrrAlzhYjQ0hrJpw9eKqC+5P6cp9MSR9N9fi8fPH0NdxDNg/U4BqtJKkPulv+Hnvtl4m8whs1PvP8x2G7cB37oX8vh9M8br3QU4x4u0T48H3BUfB30rPg64U1ijuRI/GxYxvnNVIeibwfMyMmzj3xyYLxdb0V8THt8x0T/0NGr8oAE1gh+hPOC56RXbyb8f4ee37CCtlqQ9SOfFETyGuWEt4x0pLZZxi/J3OhULv4/OXPtVE/TlYxOw3m6gf/J4tNHCk8Iumi4/CdE+bUfdN6K871IBpO3noHT7OlDwi1Ir8DGu+exB1L2L1vAEUu+5GyDPcApcmgtanuAO97OfpD15FgpyJ3L+PQMED14EMvKo2h7j0n35PuqPh0Fk5VG0n2kGxK8FyMBR4Msvn+R5KI+Si5+jv66N849Op1xOmuu5Xz3j2LHAdwNqnLTYCv79HAW3XEN/Zz/jHc9F3Sqekd7PWXfWyRwPE+0Nol+/i/LlDICcUp2H/nKeNrxSgvHgcc19bvrXPs3z3zDQ/4jov8qfH7GjM7svx9tn6Lz48pfxc85PLKZOIxnJSEYykpGMZCQjGclIRjKSkYxkJCMZyUhGMpKRjGQkIxnJSEYykpGMZCQjGclIRjKSkYxkJCMZyUhGMpKRjGQkIxnJSEYykpGMZCQjGclIRjKSkYxkJCMZyUhGMpKRjGQkIxnJSEYykpGMZCQjGclIRjKSkYz0v5H8sb5IuNQUmh745kyTO+YtqYn5PLUxv7su5nXi3V4r3fyJZDKyoyRxZOBUgvhLUORBkRtgTrzba6Sn7hMgl/+ss/PQ7SktlQFFaW1WdBd8nOjKLv/Ze6z/xt3vr75zzcHqbznGZDJJk+9MJi+OhO2mkDOCv0MTyo2E3ab6kgD+Wqkp0P+1Se7AsvWT3Mnik/8w3R3Z4QT+qG8oaI/57TFLjXTvtImmyA57rL/5T0lT0oR8nz1WVCc1yfnlJuTm92+xoaUVHaaYf6jyZEe0fhBwXntska1WqslAAMQLbDXS3DQMTxLDtr0ahgEFA4a1MCsG9P7dIzMw7NqrIuhXEDhrpV8cmQ2BE7MhE8GKXdaYFxjc0fpusCJ2bz+xvhP174l5B7dJJTFf97a4u3lvEtkxT0vZ6knuSk9r2Z2TMFD92yR7OQsqUXAPcnwDMiAh7p/kBpfQxx5LzDdU6TFH/T0x/8C210oEYjcqAqNzrcDobAFGzODuba/Zm/cJFCgBSjQiAAFBjE8JkrfnsNNOS9TXi3IQiYZHJHIwg8juDCIxlLnkgsce9UuixyUxf/+219yghShtrQKlbS1RisbsCg6U3EPCB2VIgBCnwtk8dtxWFPX2gd7I9rKofyg=
*/