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
B4LDxff+GOfHN5UajwRMx7tztOd982wymQ3KYNH5hKGvCkE/w71mtI8WQgCDW8J67HGvdx+TIv2+r+RY6s5JuIfVpXFT+tnTRaPNd7sU+Cy+rtO3+caJbkmpcX5ovWc2uhNhw5sbWzipEdCIRk+X4Isv/39W6Wl3stv8ruXfvHxz3w/znIPnvtPvQn47OFKGo2c4GadILxHOyrznNdr2y1LHifG3bFsr23bX2j6VbVNj/N17W9HhnsdMHuiLnb5kHnJbdW1EprUhPc8aqfIPqYsRbH+tNmC/P+qc0Rosr787VPHjbAPH/iakwjtJwwtiPPEF2JYsvtjAO90ab5LCW/d4LH75Bo1n4Km7oToebmFS9OihwjnVmhMU573Ffca4OLr+9xtjziPg+jr2G2XtC5cp310cxZDTrVqN/a6UiaPMOSbKqofu6x7XcOzv5U0qM8e39fPC7VRfu666yZhIz7318I3k/tG2+sZqkTEHn0vVv8mxdYjT1slt4vAUUI3xsM9eWc9PPeDF6cpklpi0+oHn3dlc9ush+zfe063smnpLty5nfylli3EZ2YJ6T9qqknjiqpeqR45y6BS+uDkyzOpueakxZfwT5YcRXSlqAtJ5ul8IE+0IzREaT/e3YQit3Lubm3VjADikCHwbEUNO+au5Op5wohqSriMVY6J7G5XFUIwptfmAu+8G1fGG23gRUNU/qoCxHUM2Zxdll/QgneTDGAhdG08kWu9pmAOODGfaWq3vJ9aNCd+dLQonxdt2US2jbjh5HwNb9pd2NZ6QdvsejpgBVnZ1FJUUFdZy4npN1zAB6o4tY6qytPJlDaZuRmuYO8b+tpXq06T6GGe6zfrchIbkFFnKRBEtW4wxdRS1/vmaPOr7mhDSMVDEaF+H0C7C2qje7uALCodQ6BjR2IBn4Y7x/MIEk6c5vXa+j8ceB2wHxyf/PHveg3YGhTOfbMDHQDYi+h8KjKHFzIJQJKdaPmO+F75Nhx02xnqnuwaLRzBGtexAnQ5DBzFP0V4Sun+SC+6hLtWq2dYdXNuUV59uUHQf7uBhuzBcOl8WaPkBZDXiyTZ9nYF6RLKQBCa4aX8/aLFPh61vd70xSp9XxfrdY+x40H3H8zn81vhB/kFt0JZDfIP9/folwFSXfESD04zxwnxB0eBcA27G9eeYsiHk3jhfyRh+1ORmdN/bXyOJbHbahWsfGFB0X+55j2gwI35qvTjxyjptX7Xm3fsApfT3UjESslbv6DsSpa0xCz3QU7F+WeFvXUGcapzP5iTOnKrgs6dR/Yf2IHooDurcgV4xJnwfUySxkR2K7seDkwoxrO8VHOPGjVERKsQ5LsQBrl/C0df/vVAvCF319u/LdjQC9iqeHKCNGZRdDa8MzW2bQbTWEdkEl+bIvrYv9FTWABRDsEbmu8tO0NZAHJ8pTE92iG+wl4RXdLA4xdeTNF8E+cK40+DrKcrG4o+ULewJ+MZTtOisWKMGWyZhGl8jXT/DmpMoIVrvWSbM+R7cqfpasE867Ed6zIKUdnSo9fxAy+Psu3E/DsYM/If1LEMq5J2EtibyBv2PsZ9Hxx/b+tTawwfbpA0e5+qZaNdfjePxveKhDun4GNsZw33d8ho9Rgqvs4Y2e2fLh/DMlfsaA+jqwXMfR+x9bj7ZvYexaqDv3sTKMfa7U6ISdLSHn/pw1PdPIrzzPXjKFCt+jhxl45nvtPjZGM+7c63vDl7kw5Hlal12RjhzEYr29pyIWrRb371l4H93r4VfuIS8M95t3trJr4J9qvTO+mblr8fYud9EdUfd7mvdf1vlwGHDOua23xX4OwfuvgfwRncOLJHS3UuBIyDSSSo7cyk5fLENles=
*/