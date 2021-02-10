#ifndef BOOST_METAPARSE_V1_CPP98_REPEATED_ONE_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_REPEATED_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_one_of_size.hpp>
#include <boost/metaparse/v1/cpp98/impl/one_of.hpp>
#include <boost/metaparse/v1/repeated.hpp>

#include <boost/mpl/vector.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_ONE_OF_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct repeated_one_of :
        repeated<
          impl::one_of<
            boost::mpl::vector<
              BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_ONE_OF_SIZE, P)
            >
          >
        >
      {};
    }
  }
}

#endif


/* repeated_one_of.hpp
Wz6ZzaZBEEzZl9RhCMkeP0JwA4/mFabBJIDJdXh9EwYBfPuRsHujNYoeq8cmcn32jsT0jAWh/oGFy3ILNjN7JWGDkO+0qVD+K4GNkc3AYjrQEBmKl/cS5D0FGAqP+OCMzjL3KkftBsuIbkMhtjNSzDLnSnpw2EKk0wLjkzGPFiZTy7yi3J3dfb801rXOhoj3TyASpijosgcNOR/PCeBhFY5btNXyKeEblWadwuAvwJfgUQO8M7CIHzFoOXDtqnjGKt820FYJ6dZh1U5cP5QZTdwGafw80tR5LHrtYgmirIwzwijQNLG1yjXeeg1aL2ZdaWd0Dl0bsTlRCeE36iP2kzTy73ZEiaTfV4qPn78+rR+WjyN2JwSWdHzJL0dti1wr+AL1zmUhzE5HSVNSh9OyVHnvBf7m13Xtb01V+ASJWhiJcsRGjIQ54/gXn/6X1Kl7B+3bTh4bwk9/1F9QSwMECgAAAAgALWdKUjmic8O4AQAA4gIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzMzVVQFAAG2SCRgdZJfb9owFMXfLeU7XKXiparnMKpJtSykqkOl2lYQZH13nQuJGuzINjD26XfzB3io9uLEyfE5v3uvVcQQjQ44ZaqyG0ePDzwdnS/C
*/