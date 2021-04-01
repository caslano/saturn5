#ifndef BOOST_METAPARSE_V1_UTIL_INT_TO_DIGIT_HPP
#define BOOST_METAPARSE_V1_UTIL_INT_TO_DIGIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/int_to_digit_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class N = boost::mpl::na>
        struct int_to_digit : int_to_digit_c<N::type::value> {};

        template <>
        struct int_to_digit<boost::mpl::na>
        {
          typedef int_to_digit type;

          template <class N = boost::mpl::na>
          struct apply : int_to_digit<N> {};
        };
      }
    }
  }
}

#endif


/* int_to_digit.hpp
FY5JtjvpZmB0M8E3k2jl41iizje8+WGN3tr/XdLYp5mb/7DpMt1+8slyeu+inF3Pfc0jpxSev/OIDn4qPvZu5q4GIyr/aKQM9EmkN32WdhOiRgj0J8iAzNkARpGsuU4lnBamiV1/eC9fXLpZJsdTQ3/s2v7LCP07sMHHEOa79zBwu5SUpuqaHsyN+IzjCjpFb2RJgxP3jSJEFZMFPCmFJ81X8B0VEQuTYLe/lr6jskQD+XwhBvN+l7Tddryi92EXg4mpS68y2ft4JI+YxPVb09Edvruck/5qAwiimL+6KBccMLeUm8RA7PAfW76+nRYAj1GyYKKe7AAjFnhCgq2HBf7gKts+e6jPFLKfmxE9Y7XwlfRK56l5RfGTK3rpT+8xbYirp3D5GbBswxONU9Yrdht5yrh6n7GZd7akwlvcseUH3g16IPmiptY0T7Pqg4Is3iBELOr/kdFz5XVkhVA0KLx0sx0hIpqtbMb7Mdq7msum9P+iFsH4E8AWu35KyCTp2VT7fkni6uRrVkGmN2Gh2iff2xjAwNgUVkx9a+eH707GtCufnyXM6a7W0Q==
*/